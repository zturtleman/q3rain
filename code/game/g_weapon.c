/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Quake III Arena source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
 */
//
// g_weapon.c 
// perform the server side effects of a weapon firing

#include "g_local.h"

static float s_quadFactor;
static vec3_t forward, right, up;
static vec3_t muzzle;

#define NUM_NAILSHOTS 15

/*
================
G_BounceProjectile
================
 */
void G_BounceProjectile(vec3_t start, vec3_t impact, vec3_t dir, vec3_t endout) {
    vec3_t v, newv;
    float dot;

    VectorSubtract(impact, start, v);
    dot = DotProduct(v, dir);
    VectorMA(v, -2 * dot, dir, newv);

    VectorNormalize(newv);
    VectorMA(impact, 8192, newv, endout);
}

/*
===============
G_PushBack
===============
 */
void G_PushBack(gentity_t *ent, int knockback) {
    vec3_t kvel;
    vec3_t dir;

    VectorCopy(forward, dir);
    dir[0] *= -1;
    dir[1] *= -1;
    // uncomment for z-change, gives boost when used in combination with wallclimb
    //dir[2] *= -1;
    // default behaviour
    dir[2] = 0.1f;

    VectorScale(dir, g_knockback.value * (float) knockback / PLAYER_MASS, kvel);
    VectorAdd(ent->client->ps.velocity, kvel, ent->client->ps.velocity);

    // set the timer so that the other client can't cancel
    // out the movement immediately
    if (!ent->client->ps.pm_time) {
        int t;

        t = knockback * 2;
        if (t < 50) {
            t = 50;
        }
        if (t > 150) {
            t = 150;
        }
        ent->client->ps.pm_time = t;
        ent->client->ps.pm_flags |= PMF_TIME_KNOCKBACK;
    }
}

/*
===============
CheckGauntletAttack
===============
 */
qboolean CheckGauntletAttack(gentity_t *ent) {
    trace_t tr;
    vec3_t end;
    gentity_t *tent;
    gentity_t *traceEnt;
    int damage;

    // set aiming directions
    AngleVectors(ent->client->ps.viewangles, forward, right, up);

    CalcMuzzlePoint(ent, forward, right, up, muzzle);

    VectorMA(muzzle, 32, forward, end);

    trap_Trace(&tr, muzzle, NULL, NULL, end, ent->s.number, MASK_SHOT);
    if (tr.surfaceFlags & SURF_NOIMPACT) {
        return qfalse;
    }

    traceEnt = &g_entities[ tr.entityNum ];

    // send blood impact
    if (traceEnt->takedamage && traceEnt->client) {
        tent = G_TempEntity(tr.endpos, EV_MISSILE_HIT);
        tent->s.otherEntityNum = traceEnt->s.number;
        tent->s.eventParm = DirToByte(tr.plane.normal);
        tent->s.weapon = ent->s.weapon;
    }

    if (!traceEnt->takedamage) {
        return qfalse;
    }

    if (ent->client->ps.powerups[PW_QUAD]) {
        G_AddEvent(ent, EV_POWERUP_QUAD, 0);
        s_quadFactor = g_quadfactor.value;
    } else {
        s_quadFactor = 1;
    }

    damage = 50;
    G_Damage(traceEnt, ent, ent, forward, tr.endpos,
            damage, 0, MOD_GAUNTLET);

    return qtrue;
}


/*
======================================================================

MACHINEGUN

======================================================================
 */

/*
======================
SnapVectorTowards

Round a vector to integers for more efficient network
transmission, but make sure that it rounds towards a given point
rather than blindly truncating.  This prevents it from truncating 
into a wall.
======================
 */
void SnapVectorTowards(vec3_t v, vec3_t to) {
    int i;

    for (i = 0; i < 3; i++) {
        if (to[i] <= v[i]) {
            v[i] = (int) v[i];
        } else {
            v[i] = (int) v[i] + 1;
        }
    }
}

#define MACHINEGUN_SPREAD	300
#define	MACHINEGUN_DAMAGE	10
#define	MACHINEGUN_TEAM_DAMAGE	10

void Bullet_Fire(gentity_t *ent, float spread, int damage) {
    trace_t tr;
    vec3_t end;
    float r;
    float u;
    gentity_t *tent;
    gentity_t *traceEnt;
    int i, passent;

    damage *= s_quadFactor;

    r = random() * M_PI * 2.0f;
    u = sin(r) * crandom() * spread * 16;
    r = cos(r) * crandom() * spread * 16;
    VectorMA(muzzle, 8192 * 16, forward, end);
    VectorMA(end, r, right, end);
    VectorMA(end, u, up, end);

    passent = ent->s.number;
    for (i = 0; i < 10; i++) {

        trap_Trace(&tr, muzzle, NULL, NULL, end, ENTITYNUM_NONE, MASK_SHOT);
        if (tr.surfaceFlags & SURF_NOIMPACT) {
            return;
        }

        traceEnt = &g_entities[ tr.entityNum ];

        // snap the endpos to integers, but nudged towards the line
        SnapVectorTowards(tr.endpos, muzzle);

        // send bullet impact
        if (traceEnt->takedamage && traceEnt->client) {
            tent = G_TempEntity(tr.endpos, EV_BULLET_HIT_FLESH);
            tent->s.eventParm = traceEnt->s.number;
            if (LogAccuracyHit(traceEnt, ent)) {
                ent->client->accuracy_hits++;
            }
        } else {
            tent = G_TempEntity(tr.endpos, EV_BULLET_HIT_WALL);
            tent->s.eventParm = DirToByte(tr.plane.normal);
        }
        tent->s.otherEntityNum = ent->s.number;

        if (traceEnt->takedamage) {
            G_Damage(traceEnt, ent, ent, forward, tr.endpos,
                    damage, 0, MOD_MACHINEGUN);
        }
        break;
    }
}

/*
======================================================================

BFG

======================================================================
 */

void BFG_Fire(gentity_t *ent) {
    gentity_t *m;

    m = fire_bfg(ent, muzzle, forward);
    m->damage *= s_quadFactor;
    m->splashDamage *= s_quadFactor;

    //	VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );	// "real" physics
}


/*
======================================================================

SHOTGUN

======================================================================
 */

// DEFAULT_SHOTGUN_SPREAD and DEFAULT_SHOTGUN_COUNT	are in bg_public.h, because
// client predicts same spreads
#define	DEFAULT_SHOTGUN_DAMAGE	12

qboolean ShotgunPellet(vec3_t start, vec3_t end, gentity_t *ent) {
    trace_t tr;
    int damage, i, passent;
    gentity_t *traceEnt;
    vec3_t tr_start, tr_end;

    passent = ent->s.number;
    VectorCopy(start, tr_start);
    VectorCopy(end, tr_end);
    for (i = 0; i < 10; i++) {
        trap_Trace(&tr, tr_start, NULL, NULL, tr_end, ENTITYNUM_NONE, MASK_SHOT);
        traceEnt = &g_entities[ tr.entityNum ];

        // send bullet impact
        if (tr.surfaceFlags & SURF_NOIMPACT) {
            return qfalse;
        }

        if (traceEnt->takedamage) {
            damage = DEFAULT_SHOTGUN_DAMAGE * s_quadFactor;
            G_Damage(traceEnt, ent, ent, forward, tr.endpos, damage, 0, MOD_SHOTGUN);
            if (LogAccuracyHit(traceEnt, ent)) {
                return qtrue;
            }
        }
        return qfalse;
    }
    return qfalse;
}

// this should match CG_ShotgunPattern

void ShotgunPattern(vec3_t origin, vec3_t origin2, int seed, gentity_t *ent) {
    int i;
    float r, u;
    vec3_t end;
    vec3_t forward, right, up;
    int oldScore;
    qboolean hitClient = qfalse;

    // derive the right and up vectors from the forward vector, because
    // the client won't have any other information
    VectorNormalize2(origin2, forward);
    PerpendicularVector(right, forward);
    CrossProduct(forward, right, up);

    oldScore = ent->client->ps.persistant[PERS_SCORE];

    // generate the "random" spread pattern
    for (i = 0; i < DEFAULT_SHOTGUN_COUNT; i++) {
        r = Q_crandom(&seed) * DEFAULT_SHOTGUN_SPREAD * 16;
        u = Q_crandom(&seed) * DEFAULT_SHOTGUN_SPREAD * 16;
        VectorMA(origin, 8192 * 16, forward, end);
        VectorMA(end, r, right, end);
        VectorMA(end, u, up, end);
        if (ShotgunPellet(origin, end, ent) && !hitClient) {
            hitClient = qtrue;
            ent->client->accuracy_hits++;
        }
    }
}

void weapon_supershotgun_fire(gentity_t *ent) {
    gentity_t *tent;

    // send shotgun blast
    tent = G_TempEntity(muzzle, EV_SHOTGUN);
    VectorScale(forward, 4096, tent->s.origin2);
    SnapVector(tent->s.origin2);
    tent->s.eventParm = rand() & 255; // seed for spread pattern
    tent->s.otherEntityNum = ent->s.number;

    ShotgunPattern(tent->s.pos.trBase, tent->s.origin2, tent->s.eventParm, ent);
}

/*
======================================================================

GRENADE LAUNCHER

======================================================================
 */

void weapon_grenadelauncher_fire(gentity_t *ent) {
    gentity_t *m;

    // extra vertical velocity
    forward[2] += 0.2f;
    VectorNormalize(forward);

    m = fire_grenade(ent, muzzle, forward);
    m->damage *= s_quadFactor;
    m->splashDamage *= s_quadFactor;

    //	VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );	// "real" physics
}

/*
======================================================================

ROCKET

======================================================================
 */

void Weapon_RocketLauncher_Fire(gentity_t *ent) {
    gentity_t *m;

    m = fire_rocket(ent, muzzle, forward);
    m->damage *= s_quadFactor;
    m->splashDamage *= s_quadFactor;

    //	VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );	// "real" physics
}

/*
======================================================================

PLASMA GUN

======================================================================
 */

void Weapon_Plasmagun_Fire(gentity_t *ent) {
    gentity_t *m;

    m = fire_plasma(ent, muzzle, forward);
    m->damage *= s_quadFactor;
    m->splashDamage *= s_quadFactor;

    //	VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );	// "real" physics
}

/*
======================================================================

RAILGUN

======================================================================
 */


/*
=================
weapon_railgun_fire
=================
 */
#define MAX_RAIL_HITS	4	// max people the rail can hit
#define MAX_RAIL_SHOTS	2	// ie. how many times through walls
#define RAIL_WALL_MAX	64	// how big a wall can be before it won't go through

void weapon_railgun_fire(gentity_t *ent, int count) {
    vec3_t end, oldmuzzle;
    trace_t trace, trace2;
    gentity_t *tent;
    gentity_t *traceEnt;
    int damage;
    int i;
    int hits;
    int unlinked;
    gentity_t * unlinkedEntities[MAX_RAIL_HITS];
    damage = 100;

    count++;

    if (count > MAX_RAIL_SHOTS) {
        return;
    } else if (count >= 2) {
        damage = damage / 2;
    }

    VectorMA(muzzle, 8192, forward, end);

    // trace only against the solids, so the railgun will go through people
    unlinked = 0;
    hits = 0;
    do {
        trap_Trace(&trace, muzzle, NULL, NULL, end, ent->s.number, MASK_SHOT);
        if (trace.entityNum >= ENTITYNUM_MAX_NORMAL) {
            break;
        }
        traceEnt = &g_entities[ trace.entityNum ];
        if (traceEnt->takedamage) {
            if (LogAccuracyHit(traceEnt, ent)) {
                hits++;
            }
            G_Damage(traceEnt, ent, ent, forward, trace.endpos, damage, 0, MOD_RAILGUN);
        }
        if (trace.contents & CONTENTS_SOLID) {
            break;
        }
        // unlink this entity, so the next trace will go past it
        trap_UnlinkEntity(traceEnt);
        unlinkedEntities[unlinked] = traceEnt;
        unlinked++;
    } while (unlinked < MAX_RAIL_HITS);

    // link back in any entities we unlinked
    for (i = 0; i < unlinked; i++) {
        trap_LinkEntity(unlinkedEntities[i]);
    }

    // the final trace endpos will be the terminal point of the rail trail

    // snap the endpos to integers to save net bandwidth, but nudged towards the line
    SnapVectorTowards(trace.endpos, muzzle);

    // send railgun beam effect
    tent = G_TempEntity(trace.endpos, EV_RAILTRAIL);

    // set player number for custom colors on the railtrail
    tent->s.clientNum = ent->s.clientNum;

    VectorCopy(muzzle, tent->s.origin2);
    // move origin a bit to come closer to the drawn gun muzzle
    VectorMA(tent->s.origin2, 4, right, tent->s.origin2);
    VectorMA(tent->s.origin2, -1, up, tent->s.origin2);

    // no explosion at end if SURF_NOIMPACT, but still make the trail
    if (trace.surfaceFlags & SURF_NOIMPACT) {
        tent->s.eventParm = 255; // don't make the explosion at the end
    } else {
        tent->s.eventParm = DirToByte(trace.plane.normal);
    }
    tent->s.clientNum = ent->s.clientNum;

    // prepare for firing through the wall
    VectorCopy(muzzle, oldmuzzle);
    VectorCopy(trace.endpos, muzzle);
    VectorMA(muzzle, RAIL_WALL_MAX, forward, muzzle);

    if (!(trap_PointContents(muzzle, -1) & CONTENTS_SOLID)) {
        trap_Trace(&trace2, muzzle, NULL, NULL, trace.endpos, ent->s.number, MASK_SHOT);
        VectorCopy(trace2.endpos, muzzle);

        weapon_railgun_fire(ent, count);
    }

    VectorCopy(oldmuzzle, muzzle);
}


/*
=================
weapon_barrett_fire
=================
 */
#define MAX_BARRETT_HITS    4
#define MAX_BARRETT_WALLS   2
#define MAX_BARRETT_UNITS   96
#define BARRETT_DAMAGE      200
#define BARRETT_RANGE       8129
#define BARRETT_SPREAD      12

void Weapon_Barrett_Fire(gentity_t *ent, int count) {
    vec3_t end, oldmuzzle;
    trace_t trace, trace2;
    gentity_t *tent;
    gentity_t *traceEnt;
    int damage;
    int i;
    int hits;
    int unlinked;
    gentity_t * unlinkedEntities[MAX_BARRETT_HITS];
    float r;
    float u;
    int spread;

    damage = 100;
    count++;

    if (count > MAX_BARRETT_WALLS) {
        return;
    }

    spread = ent->client->pers.cmd.forwardmove + ent->client->pers.cmd.upmove + ent->client->pers.cmd.rightmove;
    spread *= BARRETT_SPREAD;

    //Com_Printf("spread = %i\n", spread);

    r = random() * M_PI * 2.0f;
    u = cos(r) * crandom() * (spread);
    r = cos(r) * crandom() * (spread);
    VectorMA(muzzle, BARRETT_RANGE, forward, end);
    if (ent->client->ps.zoomFov <= 0) {
        VectorMA(end, r, right, end);
        VectorMA(end, u, up, end);
    } else {
        if (spread != 0) {
            VectorMA(end, r, right, end);
            VectorMA(end, u, up, end);
        }
    }

    unlinked = 0;
    hits = 0;
    do {
        trap_Trace(&trace, muzzle, NULL, NULL, end, ent->s.number, MASK_SHOT);
        if (trace.entityNum >= ENTITYNUM_MAX_NORMAL) {
            break;
        }
        traceEnt = &g_entities[ trace.entityNum ];
        if (traceEnt->takedamage) {
            if (LogAccuracyHit(traceEnt, ent)) {
                hits++;
            }
            G_Damage(traceEnt, ent, ent, forward, trace.endpos, damage, 0, MOD_BARRETT);
        }
        if (trace.contents & CONTENTS_SOLID) {
            break;
        }
        // unlink this entity, so the next trace will go past it
        trap_UnlinkEntity(traceEnt);
        unlinkedEntities[unlinked] = traceEnt;
        unlinked++;
    } while (unlinked < MAX_BARRETT_HITS);

    // link back in any entities we unlinked
    for (i = 0; i < unlinked; i++) {
        trap_LinkEntity(unlinkedEntities[i]);
    }

    SnapVectorTowards(trace.endpos, muzzle);

    // send railgun beam effect
    tent = G_TempEntity(trace.endpos, EV_RAILTRAIL);

    VectorCopy(muzzle, tent->s.origin2);
    VectorMA(tent->s.origin2, 4, right, tent->s.origin2);
    VectorMA(tent->s.origin2, -1, up, tent->s.origin2);

    if (trace.surfaceFlags & SURF_NOIMPACT) {
        tent->s.eventParm = 255; // don't make the explosion at the end
    } else {
        tent->s.eventParm = DirToByte(trace.plane.normal);
    }

    // prepare for firing through the wall
    VectorCopy(muzzle, oldmuzzle);
    VectorCopy(trace.endpos, muzzle);
    VectorMA(muzzle, MAX_BARRETT_UNITS, forward, muzzle);

    if (!(trap_PointContents(muzzle, -1) & CONTENTS_SOLID)) {
        trap_Trace(&trace2, muzzle, NULL, NULL, trace.endpos, ent->s.number, MASK_SHOT);
        VectorCopy(trace2.endpos, muzzle);

        Weapon_Barrett_Fire(ent, count);
    }

    VectorCopy(oldmuzzle, muzzle);
}

/*
======================================================================

GRAPPLING HOOK
TODO remove

======================================================================
 */

void Weapon_GrapplingHook_Fire(gentity_t *ent) {
    if (!ent->client->fireHeld && !ent->client->hook)
        fire_grapple(ent, muzzle, forward);

    ent->client->fireHeld = qtrue;
}

void Weapon_HookFree(gentity_t *ent) {
    ent->parent->client->hook = NULL;
    ent->parent->client->ps.pm_flags &= ~PMF_GRAPPLE_PULL;
    G_FreeEntity(ent);
}

void Weapon_HookThink(gentity_t *ent) {
    if (ent->enemy) {
        vec3_t v, oldorigin;

        VectorCopy(ent->r.currentOrigin, oldorigin);
        v[0] = ent->enemy->r.currentOrigin[0] + (ent->enemy->r.mins[0] + ent->enemy->r.maxs[0]) * 0.5;
        v[1] = ent->enemy->r.currentOrigin[1] + (ent->enemy->r.mins[1] + ent->enemy->r.maxs[1]) * 0.5;
        v[2] = ent->enemy->r.currentOrigin[2] + (ent->enemy->r.mins[2] + ent->enemy->r.maxs[2]) * 0.5;
        SnapVectorTowards(v, oldorigin); // save net bandwidth

        G_SetOrigin(ent, v);
    }

    VectorCopy(ent->r.currentOrigin, ent->parent->client->ps.grapplePoint);
}

// TODO remove

void Weapon_LightningFire(gentity_t *ent) {
    trace_t tr;
    vec3_t end;
    gentity_t *traceEnt, *tent;
    int damage, i, passent;

    damage = 8 * s_quadFactor;

    passent = ent->s.number;
    for (i = 0; i < 10; i++) {
        VectorMA(muzzle, LIGHTNING_RANGE, forward, end);

        trap_Trace(&tr, muzzle, NULL, NULL, end, passent, MASK_SHOT);
        if (tr.entityNum == ENTITYNUM_NONE) {
            return;
        }

        traceEnt = &g_entities[ tr.entityNum ];

        if (traceEnt->takedamage) {
            G_Damage(traceEnt, ent, ent, forward, tr.endpos,
                    damage, 0, MOD_LIGHTNING);
        }

        if (traceEnt->takedamage && traceEnt->client) {
            tent = G_TempEntity(tr.endpos, EV_MISSILE_HIT);
            tent->s.otherEntityNum = traceEnt->s.number;
            tent->s.eventParm = DirToByte(tr.plane.normal);
            tent->s.weapon = ent->s.weapon;
            if (LogAccuracyHit(traceEnt, ent)) {
                ent->client->accuracy_hits++;
            }
        } else if (!(tr.surfaceFlags & SURF_NOIMPACT)) {
            tent = G_TempEntity(tr.endpos, EV_MISSILE_MISS);
            tent->s.eventParm = DirToByte(tr.plane.normal);
        }

        break;
    }
}

//======================================================================

/*
===============
LogAccuracyHit
===============
 */
qboolean LogAccuracyHit(gentity_t *target, gentity_t *attacker) {
    if (!target->takedamage) {
        return qfalse;
    }

    if (target == attacker) {
        return qfalse;
    }

    if (!target->client) {
        return qfalse;
    }

    if (!attacker->client) {
        return qfalse;
    }

    if (target->client->ps.stats[STAT_HEALTH] <= 0) {
        return qfalse;
    }

    if (OnSameTeam(target, attacker)) {
        return qfalse;
    }

    return qtrue;
}

/*
===============
CalcMuzzlePoint

set muzzle location relative to pivoting eye
===============
 */
void CalcMuzzlePoint(gentity_t *ent, vec3_t forward, vec3_t right, vec3_t up, vec3_t muzzlePoint) {
    VectorCopy(ent->s.pos.trBase, muzzlePoint);
    muzzlePoint[2] += ent->client->ps.viewheight;
    VectorMA(muzzlePoint, 14, forward, muzzlePoint);
    // snap to integer coordinates for more efficient network bandwidth usage
    SnapVector(muzzlePoint);
}

/*
===============
CalcMuzzlePointOrigin

set muzzle location relative to pivoting eye
===============
 */
void CalcMuzzlePointOrigin(gentity_t *ent, vec3_t origin, vec3_t forward, vec3_t right, vec3_t up, vec3_t muzzlePoint) {
    VectorCopy(ent->s.pos.trBase, muzzlePoint);
    muzzlePoint[2] += ent->client->ps.viewheight;
    VectorMA(muzzlePoint, 14, forward, muzzlePoint);
    // snap to integer coordinates for more efficient network bandwidth usage
    SnapVector(muzzlePoint);
}

/*
===============
Weapon_Knife_Fire

===============
 */
#define KNIFE_DAMAGE 50
#define KNIFE_RANGE 32
#define KNIFE_KNOCKBACK 25

void Weapon_Knife_Fire(gentity_t *ent) {
    trace_t tr;
    vec3_t end;
    gentity_t *tent;
    gentity_t *traceEnt;

    // set aiming directions
    AngleVectors(ent->client->ps.viewangles, forward, right, up);

    CalcMuzzlePoint(ent, forward, right, up, muzzle);

    VectorMA(muzzle, KNIFE_RANGE, forward, end);

    trap_Trace(&tr, muzzle, NULL, NULL, end, ent->s.number, MASK_SHOT);
    if (tr.surfaceFlags & SURF_NOIMPACT) {
        return;
    } else if (tr.contents & CONTENTS_SOLID) {
        G_PushBack(ent, KNIFE_KNOCKBACK);
    }

    traceEnt = &g_entities[ tr.entityNum ];

    // send blood impact
    if (traceEnt->takedamage && traceEnt->client) {
        tent = G_TempEntity(tr.endpos, EV_MISSILE_HIT);
        tent->s.otherEntityNum = traceEnt->s.number;
        tent->s.eventParm = DirToByte(tr.plane.normal);
        tent->s.weapon = ent->s.weapon;
    }

    if (!traceEnt->takedamage) {
        return;
    }

    G_Damage(traceEnt, ent, ent, forward, tr.endpos, KNIFE_DAMAGE, 0, MOD_KNIFE);
}

/*
===============
Weapon_Injector_Fire

===============
 */
#define INJECTOR_RANGE 32

void Weapon_Injector_Fire(gentity_t *ent) {
    trace_t tr;
    vec3_t end;
    gentity_t *traceEnt;
    qboolean okay = qtrue;

    AngleVectors(ent->client->ps.viewangles, forward, right, up);
    CalcMuzzlePoint(ent, forward, right, up, muzzle);
    VectorMA(muzzle, INJECTOR_RANGE, forward, end);
    trap_Trace(&tr, muzzle, NULL, NULL, end, ent->s.number, MASK_SHOT);

    traceEnt = &g_entities[tr.entityNum];

    if (tr.surfaceFlags & SURF_NOIMPACT) {
        okay = qfalse;
    }
    if (tr.contents & CONTENTS_SOLID) {
        okay = qfalse;
    }
    if (tr.entityNum == MAX_GENTITIES - 1) {
        okay = qfalse;
    }
    if (tr.contents & CONTENTS_BODY) {
        okay = qtrue;
    }

    if (okay == qtrue) {
        //Com_Printf("Weapon_Injector_Fire: Injecting entity (%i)\n", tr.entityNum);
        traceEnt->client->ps.powerups[PW_ADRENALINE] = level.time + ADRENALINE_TIME;
    } else {
        ent->client->ps.powerups[PW_ADRENALINE] = level.time + ADRENALINE_TIME;
    }
}

/*
===============
Weapon_Hands_Fire

===============
 */
#define HANDS_DAMAGE 10
#define HANDS_RANGE 32
#define HANDS_KNOCKBACK 50

void Weapon_Hands_Fire(gentity_t *ent) {
    trace_t tr;
    vec3_t end;
    gentity_t *tent;
    gentity_t *traceEnt;

    // set aiming directions
    AngleVectors(ent->client->ps.viewangles, forward, right, up);

    CalcMuzzlePoint(ent, forward, right, up, muzzle);

    VectorMA(muzzle, HANDS_RANGE, forward, end);

    trap_Trace(&tr, muzzle, NULL, NULL, end, ent->s.number, MASK_SHOT);
    if (tr.surfaceFlags & SURF_NOIMPACT) {
        return;
    } else if (tr.contents & CONTENTS_SOLID) {
        G_PushBack(ent, HANDS_KNOCKBACK);
    }

    traceEnt = &g_entities[tr.entityNum];

    // send blood impact
    if (traceEnt->takedamage && traceEnt->client) {
        tent = G_TempEntity(tr.endpos, EV_MISSILE_HIT);
        tent->s.otherEntityNum = traceEnt->s.number;
        tent->s.eventParm = DirToByte(tr.plane.normal);
        tent->s.weapon = ent->s.weapon;
    }

    if (!traceEnt->takedamage) {
        return;
    }

    G_Damage(traceEnt, ent, ent, forward, tr.endpos, HANDS_DAMAGE, 0, MOD_HANDS);
}

/*
===============
Weapon_HE_Fire

===============
 */
#define HE_DAMAGE 5
#define HE_SPLASHDAMAGE 250
#define HE_RADIUS 300

void Weapon_HE_Fire(gentity_t *ent, int time) {
    gentity_t *m;

    forward[2] += 0.2f;
    VectorNormalize(forward);

    m = fire_he(ent, muzzle, forward);
    m->damage = HE_DAMAGE;
    m->splashDamage = HE_SPLASHDAMAGE;
    m->splashRadius = HE_RADIUS;
    if (time < 0 || time > 3000) {
        time = 3000;
    }
    m->nextthink = level.time + time;
}

/*
===============
Weapon_Bomb_Fire

===============
 */
#define BOMB_SPLASHDAMAGE 500
#define BOMB_RADIUS 750

void Weapon_Bomb_Fire(gentity_t *ent) {
    gentity_t *m;

    forward[2] += 0.2f;
    VectorNormalize(forward);

    m = fire_bomb(ent, muzzle, forward);
    m->splashDamage = BOMB_SPLASHDAMAGE;
    m->splashRadius = BOMB_RADIUS;
    m->flags = FL_BOMB;
}

/*
===============
Weapon_Intervention_Fire

===============
 */
#define MAX_INTERVENTION_HITS   2
#define MAX_INTERVENTION_WALLS  1
#define MAX_INTERVENTION_UNITS  64
#define INTERVENTION_DAMAGE     100
#define INTERVENTION_RANGE      8192
#define INTERVENTION_SPREAD     8

void Weapon_Intervention_Fire(gentity_t *ent, int count) {
    vec3_t end, oldmuzzle;
    trace_t trace, trace2;
    gentity_t *tent;
    gentity_t *traceEnt;
    int damage;
    int i;
    int hits;
    int unlinked;
    gentity_t * unlinkedEntities[MAX_INTERVENTION_HITS];
    int spread;
    float u, r;
    damage = 100;

    count++;

    if (count > MAX_INTERVENTION_WALLS) {
        return;
    } else if (count >= 2) {
        damage = damage / 1.5;
    }

    spread = ent->client->pers.cmd.forwardmove + ent->client->pers.cmd.upmove + ent->client->pers.cmd.rightmove;
    spread *= INTERVENTION_SPREAD;

    r = random() * M_PI * 2.0f;
    u = cos(r) * crandom() * (spread);
    r = cos(r) * crandom() * (spread);
    VectorMA(muzzle, INTERVENTION_RANGE, forward, end);
    if (ent->client->ps.zoomFov <= 0) {
        VectorMA(end, r, right, end);
        VectorMA(end, u, up, end);
    } else {
        if (spread != 0) {
            VectorMA(end, r, right, end);
            VectorMA(end, u, up, end);
        }
    }

    unlinked = 0;
    hits = 0;
    do {
        trap_Trace(&trace, muzzle, NULL, NULL, end, ent->s.number, MASK_SHOT);
        if (trace.entityNum >= ENTITYNUM_MAX_NORMAL) {
            break;
        }
        traceEnt = &g_entities[ trace.entityNum ];
        if (traceEnt->takedamage) {
            if (LogAccuracyHit(traceEnt, ent)) {
                hits++;
            }
            G_Damage(traceEnt, ent, ent, forward, trace.endpos, damage, 0, MOD_INTERVENTION);
        }
        if (trace.contents & CONTENTS_SOLID) {
            break;
        }
        // unlink this entity, so the next trace will go past it
        trap_UnlinkEntity(traceEnt);
        unlinkedEntities[unlinked] = traceEnt;
        unlinked++;
    } while (unlinked < MAX_INTERVENTION_HITS);

    // link back in any entities we unlinked
    for (i = 0; i < unlinked; i++) {
        trap_LinkEntity(unlinkedEntities[i]);
    }

    SnapVectorTowards(trace.endpos, muzzle);

    tent = G_TempEntity(trace.endpos, EV_RAILTRAIL);

    VectorCopy(muzzle, tent->s.origin2);
    VectorMA(tent->s.origin2, 4, right, tent->s.origin2);
    VectorMA(tent->s.origin2, -1, up, tent->s.origin2);

    if (trace.surfaceFlags & SURF_NOIMPACT) {
        tent->s.eventParm = 255; // don't make the explosion at the end
    } else {
        tent->s.eventParm = DirToByte(trace.plane.normal);
    }

    // prepare for firing through the wall
    VectorCopy(muzzle, oldmuzzle);
    VectorCopy(trace.endpos, muzzle);
    VectorMA(muzzle, MAX_INTERVENTION_UNITS, forward, muzzle);

    if (!(trap_PointContents(muzzle, -1) & CONTENTS_SOLID)) {
        trap_Trace(&trace2, muzzle, NULL, NULL, trace.endpos, ent->s.number, MASK_SHOT);
        VectorCopy(trace2.endpos, muzzle);

        Weapon_Intervention_Fire(ent, count);
    }

    VectorCopy(oldmuzzle, muzzle);
}

/*
===============
Weapon_ACR_Fire

===============
 */
#define ACR_MINSPREAD 0
#define ACR_MAXSPREAD 200
#define ACR_SPREADADD 7.5f
#define ACR_DAMAGE 10
#define ACR_RANGE 8192

void Weapon_ACR_Fire(gentity_t *ent) {
    trace_t tr;
    vec3_t end;
    float r;
    float u;
    gentity_t *tent;
    gentity_t *traceEnt;
    int i, passent;

    ent->client->ps.spammed++;
    ent->client->ps.spread = ACR_MINSPREAD + (ACR_SPREADADD * (ent->client->ps.spammed - 1));
    if (ent->client->ps.spread > ACR_MAXSPREAD) {
        ent->client->ps.spread = ACR_MAXSPREAD;
    }

    r = random() * M_PI * 2.0f;
    u = sin(r) * crandom() * (ent->client->ps.spread + ACR_SPREADADD) * 16;
    r = cos(r) * crandom() * (ent->client->ps.spread + ACR_SPREADADD) * 16;
    VectorMA(muzzle, ACR_RANGE, forward, end);
    VectorMA(end, r, right, end);
    VectorMA(end, u, up, end);

    passent = ent->s.number;
    for (i = 0; i < 10; i++) {

        trap_Trace(&tr, muzzle, NULL, NULL, end, ENTITYNUM_NONE, MASK_SHOT);
        if (tr.surfaceFlags & SURF_NOIMPACT) {
            return;
        }

        traceEnt = &g_entities[tr.entityNum];

        // snap the endpos to integers, but nudged towards the line
        SnapVectorTowards(tr.endpos, muzzle);

        // send bullet impact
        if (traceEnt->takedamage && traceEnt->client) {
            tent = G_TempEntity(tr.endpos, EV_BULLET_HIT_FLESH);
            tent->s.eventParm = traceEnt->s.number;
            if (LogAccuracyHit(traceEnt, ent)) {
                ent->client->accuracy_hits++;
            }
        } else {
            tent = G_TempEntity(tr.endpos, EV_BULLET_HIT_WALL);
            tent->s.eventParm = DirToByte(tr.plane.normal);
        }
        tent->s.otherEntityNum = ent->s.number;

        if (traceEnt->takedamage) {
            G_Damage(traceEnt, ent, ent, forward, tr.endpos, ACR_DAMAGE, 0, MOD_ACR);
        }
        break;
    }
}

/*
===============
Weapon_Crossbow_Fire

===============
 */
#define CROSSBOW_RANGE  2048
#define CROSSBOW_DAMAGE 100
#define CROSSBOW_SPREAD 8

void Weapon_Crossbow_Fire(gentity_t *ent) {
    trace_t tr;
    vec3_t end;
    float r;
    float u;
    gentity_t *tent;
    gentity_t *traceEnt;
    int i, passent, spread;

    spread = ent->client->pers.cmd.forwardmove + ent->client->pers.cmd.upmove + ent->client->pers.cmd.rightmove;
    spread *= CROSSBOW_SPREAD;

    r = random() * M_PI * 2.0f;
    u = cos(r) * crandom() * (spread);
    r = cos(r) * crandom() * (spread);
    VectorMA(muzzle, CROSSBOW_RANGE, forward, end);
    if (ent->client->ps.zoomFov <= 0) {
        VectorMA(end, r, right, end);
        VectorMA(end, u, up, end);
    } else {
        if (spread != 0) {
            VectorMA(end, r, right, end);
            VectorMA(end, u, up, end);
        }
    }

    passent = ent->s.number;
    trap_Trace(&tr, muzzle, NULL, NULL, end, ENTITYNUM_NONE, MASK_SHOT);
    if (tr.surfaceFlags & SURF_NOIMPACT) {
        return;
    }
    traceEnt = &g_entities[ tr.entityNum ];
    SnapVectorTowards(tr.endpos, muzzle);
    // send bullet impact
    if (traceEnt->takedamage && traceEnt->client) {
        tent = G_TempEntity(tr.endpos, EV_BULLET_HIT_FLESH);
        tent->s.eventParm = traceEnt->s.number;
        if (LogAccuracyHit(traceEnt, ent)) {
            ent->client->accuracy_hits++;
        }
    } else {
        // if we didnt hit anything, dont show hit animation
        if (tr.fraction >= 1.0f) {
            return;
        }
        tent = G_TempEntity(tr.endpos, EV_BULLET_HIT_WALL);
        tent->s.eventParm = DirToByte(tr.plane.normal);
    }
    tent->s.otherEntityNum = ent->s.number;
    if (traceEnt->takedamage) {
        G_Damage(traceEnt, ent, ent, forward, tr.endpos, CROSSBOW_DAMAGE, 0, MOD_CROSSBOW);
    }
}

/*
===============
Weapon_Walther_Fire
===============
 */
#define WALTHER_RANGE 8192
#define WALTHER_DAMAGE 40

void Weapon_Walther_Fire(gentity_t *ent) {
    trace_t tr;
    vec3_t end;
    float r;
    float u;
    gentity_t *tent;
    gentity_t *traceEnt;
    int i, passent;

    VectorMA(muzzle, WALTHER_RANGE, forward, end);
    passent = ent->s.number;
    trap_Trace(&tr, muzzle, NULL, NULL, end, ENTITYNUM_NONE, MASK_SHOT);
    if (tr.surfaceFlags & SURF_NOIMPACT) {
        return;
    }
    traceEnt = &g_entities[ tr.entityNum ];
    SnapVectorTowards(tr.endpos, muzzle);
    // send bullet impact
    if (traceEnt->takedamage && traceEnt->client) {
        tent = G_TempEntity(tr.endpos, EV_BULLET_HIT_FLESH);
        tent->s.eventParm = traceEnt->s.number;
        if (LogAccuracyHit(traceEnt, ent)) {
            ent->client->accuracy_hits++;
        }
    } else {
        // if we didnt hit anything, dont show hit animation
        if (tr.fraction >= 1.0f) {
            return;
        }
        tent = G_TempEntity(tr.endpos, EV_BULLET_HIT_WALL);
        tent->s.eventParm = DirToByte(tr.plane.normal);
    }
    tent->s.otherEntityNum = ent->s.number;
    if (traceEnt->takedamage) {
        G_Damage(traceEnt, ent, ent, forward, tr.endpos, WALTHER_DAMAGE, 0, MOD_WALTHER);
    }
}

/*
===============
Weapon_Nuke_Fire

===============
 */
#define NUKE_STAGE1_DAMAGE 5000
#define NUKE_STAGE1_RADIUS 500

void Weapon_Nuke_Fire(gentity_t *ent) {
    gentity_t *m;

    m = fire_nuke(ent, muzzle, forward);
    m->damage = 0;
    m->splashDamage = NUKE_STAGE1_DAMAGE;
    m->splashRadius = NUKE_STAGE1_RADIUS;
}

/*
===============
FireWeapon
===============
 */
void FireWeapon(gentity_t *ent) {

    //Remove Ammo if not infinite
    if (ent->client->clipammo[ ent->client->ps.weapon ] != -1) {
        ent->client->clipammo[ ent->client->ps.weapon ]--;
    }

    // track shots taken for accuracy tracking.  Grapple is not a weapon and gauntet is just not tracked
    if (ent->s.weapon != WP_GRAPPLING_HOOK && ent->s.weapon != WP_KNIFE && ent->s.weapon != WP_HANDS) {
        ent->client->accuracy_shots++;
    }

    // set aiming directions
    AngleVectors(ent->client->ps.viewangles, forward, right, up);

    CalcMuzzlePointOrigin(ent, ent->client->oldOrigin, forward, right, up, muzzle);

    // fire the specific weapon
    switch (ent->s.weapon) {
        case WP_HANDS:
            Weapon_Hands_Fire(ent);
            break;
        case WP_KNIFE:
            Weapon_Knife_Fire(ent);
            break;
        case WP_HE:
            Weapon_HE_Fire(ent, ent->client->ps.grenadetime - ent->client->ps.levelTime);
            if (ent->client->clipammo[WP_HE] == 0) {
                ent->client->ps.stats[STAT_WEAPONS] &= ~(1 << WP_HE);
                ent->client->ps.weapon = WP_HANDS;
            }
            break;
        case WP_BARRETT:
            Weapon_Barrett_Fire(ent, 0);
            ent->client->ps.zoomFov = 0;
            break;
        case WP_INTERVENTION:
            Weapon_Intervention_Fire(ent, 0);
            ent->client->ps.zoomFov = 0;
            break;
        case WP_CROSSBOW:
            Weapon_Crossbow_Fire(ent);
            ent->client->ps.zoomFov = 0;
            break;
        case WP_ACR:
            Weapon_ACR_Fire(ent);
            break;
        case WP_WALTHER:
            Weapon_Walther_Fire(ent);
            break;
        case WP_INJECTOR:
            Weapon_Injector_Fire(ent);
            if (ent->client->clipammo[WP_INJECTOR] == 0) {
                ent->client->ps.stats[STAT_WEAPONS] &= ~(1 << WP_INJECTOR);
                ent->client->ps.weapon = WP_HANDS;
            }
            break;
        case WP_BOMB:
            Weapon_Bomb_Fire(ent);
            if (ent->client->clipammo[WP_BOMB] == 0) {
                ent->client->ps.stats[STAT_WEAPONS] &= ~(1 << WP_BOMB);
                ent->client->ps.weapon = WP_HANDS;
            }
            break;
        case WP_NUKE:
            Weapon_Nuke_Fire(ent);
            break;
        default:
            //G_Error( "Bad ent->s.weapon" );
            break;
    }

    ent->client->ps.grenadetime = -1337;
}

static void FireGrenade(gentity_t *ent, int time, int mod) {
    gentity_t *m;
    vec3_t dir;

    if (ent->client->ps.grenadetime == -1337) {
        return;
    }
    //Com_Printf("FireGrenade() time: %i\n", time);
    ent->client->clipammo[ent->client->ps.weapon]--;

    forward[2] += 0.2f;
    VectorNormalize(forward);

    m = fire_he(ent, muzzle, forward);
    m->damage = HE_DAMAGE;
    m->splashDamage = HE_SPLASHDAMAGE;
    m->splashRadius = HE_RADIUS;
    if (time < 0 || time > 3000) {
        time = 3000;
    }
    m->nextthink = level.time + time;
    m->splashMethodOfDeath = mod;

    dir[0] = 0;
    dir[1] = 0;
    dir[2] = 0;

    VectorCopy(ent->client->oldOrigin, m->s.pos.trBase);
    VectorScale(dir, 0, m->s.pos.trDelta);
    VectorCopy(ent->client->oldOrigin, m->r.currentOrigin);
}
