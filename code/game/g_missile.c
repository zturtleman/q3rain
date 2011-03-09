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
#include "g_local.h"

#define	MISSILE_PRESTEP_TIME 50

/*
 ================
 G_BounceMissile

 ================
 */
void G_BounceMissile(gentity_t *ent, trace_t *trace) {
  vec3_t velocity, old, dir;
  float dot;
  int hitTime;

  VectorCopy(ent->s.pos.trBase, old);

  // reflect the velocity on the trace plane
  hitTime = level.previousTime + (level.time - level.previousTime) * trace->fraction;
  BG_EvaluateTrajectoryDelta(&ent->s.pos, hitTime, velocity);
  dot = DotProduct(velocity, trace->plane.normal);
  VectorMA(velocity, -2 * dot, trace->plane.normal, ent->s.pos.trDelta);

  if (strcmp(ent->classname, "shrapnel") == 0) {
    G_SetOrigin(ent, trace->endpos);
    G_AddEvent(ent, EV_SHRAPNEL_IMPACT, 0);
    ent->freeAfterEvent = qtrue;
    return;
  }

  if (ent->s.eFlags & EF_BOUNCE) {
    G_AddEvent(ent, EV_GRENADE_BOUNCE, 0);
  }

  if (ent->s.eFlags & EF_BOUNCE_HALF) {
    if (trace->allsolid == qtrue) {
      G_SetOrigin(ent, trace->endpos);
      return;
    }
    G_AddEvent(ent, EV_GRENADE_BOUNCE, 0);
    // grenades shouldnt bounce that much
    if (strcmp(ent->classname, "grenade") == 0) {
      VectorScale(ent->s.pos.trDelta, 0.4, ent->s.pos.trDelta);
    } else {
      VectorScale(ent->s.pos.trDelta, 0.65, ent->s.pos.trDelta);
    }
    // check for stop
    if (trace->plane.normal[2] > 0.2 && VectorLength(ent->s.pos.trDelta) < 40) {
      G_SetOrigin(ent, trace->endpos);
      return;
    }
  }

  if (strcmp(ent->classname, "c4") == 0) {
    Com_Printf("c4 bounce\n");
    if (trace->allsolid == qtrue) {
      // bomb sticks in wall, keep it there
      G_SetOrigin(ent, old);
      return;
    }
    ent->s.angles[0] = DEG2RAD(90);
    ent->s.angles[1] = DEG2RAD(90);
    ent->s.angles[2] = DEG2RAD(90);
    ent->s.angles2[0] = DEG2RAD(90);
    ent->s.angles2[1] = DEG2RAD(90);
    ent->s.angles2[2] = DEG2RAD(90);
    if (trace->plane.normal[2] > 0.2) {
      G_SetOrigin(ent, trace->endpos);
      Com_Printf("bomb stopped\n");
      return;
    }
  }

  VectorAdd(ent->r.currentOrigin, trace->plane.normal, ent->r.currentOrigin);
  VectorCopy(ent->r.currentOrigin, ent->s.pos.trBase);
  ent->s.pos.trTime = level.time;
}

/*
 ================
 G_CreateShraphnels

 ================
 */
void G_CreateShrapnels(gentity_t *ent, vec3_t origin) {
  vec3_t random;
  int i = 0, max;
  max = (int) (crandom() * 50);
  if (max < 0) {
    max *= -1;
  }
  if (max == 0) {
    max = 10;
  }
  //Com_Printf("Creating %i shrapnels...\n", max);
  while (i < max) {
    random[0] = crandom() * 10;
    random[1] = crandom() * 10;
    random[2] = crandom() * 7.5;
    fire_shrapnel(ent, origin, random);
    i++;
  }
}

/*
 ================
 G_FadeShrapnel

 Remove shrapnel after flying around
 ================
 */
void G_FadeShrapnel(gentity_t *ent) {
  ent->inuse = qfalse;
  trap_UnlinkEntity(ent);
  G_FreeEntity(ent);
}

/*
 ================
 G_ExplodeMissile

 Explode a missile without an impact
 ================
 */
void G_ExplodeMissile(gentity_t *ent) {
  vec3_t dir;
  vec3_t origin;

  BG_EvaluateTrajectory(&ent->s.pos, level.time, origin);
  SnapVector(origin);
  G_SetOrigin(ent, origin);

  // we don't have a valid direction, so just point straight up
  dir[0] = dir[1] = 0;
  dir[2] = 1;

  ent->s.eType = ET_GENERAL;
  G_AddEvent(ent, EV_MISSILE_MISS, DirToByte(dir));

  ent->freeAfterEvent = qtrue;

  // splash damage
  if (ent->splashDamage) {
    if (G_RadiusDamage(ent->r.currentOrigin, ent->parent, ent->splashDamage, ent->splashRadius, ent, ent->splashMethodOfDeath)) {
      g_entities[ent->r.ownerNum].client->accuracy_hits++;
    }
  }

  G_CreateShrapnels(ent, origin);

  trap_LinkEntity(ent);
}

/*
 ================
 G_ExplodeBomb

 Explode a bomb
 ================
 */
void G_ExplodeBomb(gentity_t * ent) {
  vec3_t dir;
  vec3_t origin;

  BG_EvaluateTrajectory(&ent->s.pos, level.time, origin);
  SnapVector(origin);
  G_SetOrigin(ent, origin);

  // we don't have a valid direction, so just point straight up
  dir[0] = dir[1] = 0;
  dir[2] = 1;

  ent->s.eType = ET_GENERAL;
  G_AddEvent(ent, EV_MISSILE_MISS, DirToByte(dir));

  ent->freeAfterEvent = qtrue;

  // splash damage
  if (ent->splashDamage) {
    if (G_RadiusDamage(ent->r.currentOrigin, ent->parent, ent->splashDamage, ent->splashRadius, ent, ent->splashMethodOfDeath)) {
      g_entities[ent->r.ownerNum].client->accuracy_hits++;
    }
  }

  trap_LinkEntity(ent);
}

void G_NukeBlindPlayers(gentity_t * self) {
  vec3_t origin;

  BG_EvaluateTrajectory(&self->s.pos, level.time, origin);
  SnapVector(origin);

  G_RadiusDamage(origin, self, -1, 64000, self, MOD_NUKE);
}

#define STAGE_DIFF 200

/*
 ================
 G_ExplodeNuke

 Nuke Explosion stuff
 ================
 */
void G_ExplodeNuke(gentity_t * ent) {
  vec3_t dir;
  vec3_t origin;

  BG_EvaluateTrajectory(&ent->s.pos, level.time, origin);
  SnapVector(origin);
  G_SetOrigin(ent, origin);

  dir[0] = dir[1] = 0;
  dir[2] = 1;

  if (ent->count < 1) {
    ent->count++;
  }

  if (ent->count == 1) {
    G_NukeBlindPlayers(ent);
    G_RadiusDamage(ent->r.currentOrigin, ent->parent, 10000, 500, ent, ent->splashMethodOfDeath);
    ent->think = G_NukeNextStage;
    ent->nextthink = level.time + STAGE_DIFF;
    G_AddEvent(ent, EV_NUKE_1, 0);
  } else if (ent->count == 2) { //                      dmg   range
    G_RadiusDamage(ent->r.currentOrigin, ent->parent, 3000, 1000, ent, ent->splashMethodOfDeath);
    ent->think = G_NukeNextStage;
    ent->nextthink = level.time + STAGE_DIFF;
    G_AddEvent(ent, EV_NUKE_2, 0);
  } else if (ent->count == 3) { //                      dmg   range
    G_RadiusDamage(ent->r.currentOrigin, ent->parent, 1000, 2000, ent, ent->splashMethodOfDeath);
    ent->think = G_NukeNextStage;
    ent->nextthink = level.time + STAGE_DIFF;
    G_AddEvent(ent, EV_NUKE_3, 0);
  } else if (ent->count == 4) { //                      dmg   range
    G_RadiusDamage(ent->r.currentOrigin, ent->parent, 500, 4000, ent, ent->splashMethodOfDeath);
    ent->think = G_NukeNextStage;
    ent->nextthink = level.time + STAGE_DIFF;
    G_AddEvent(ent, EV_NUKE_4, 0);
  } else if (ent->count == 5) { //                      dmg   range
    G_RadiusDamage(ent->r.currentOrigin, ent->parent, 250, 8000, ent, ent->splashMethodOfDeath);
    ent->think = G_NukeNextStage;
    ent->nextthink = level.time + STAGE_DIFF;
    G_AddEvent(ent, EV_NUKE_5, 0);
  } else if (ent->count == 6) { //                      dmg   range
    G_RadiusDamage(ent->r.currentOrigin, ent->parent, 75, 16000, ent, ent->splashMethodOfDeath);
    ent->think = G_NukeNextStage;
    ent->nextthink = level.time + STAGE_DIFF;
    G_AddEvent(ent, EV_NUKE_6, 0);
  } else {
    if (ent->count > 6) {
      G_RadiusDamage(ent->r.currentOrigin, ent->parent, 50, 32000, ent, ent->splashMethodOfDeath);
      ent->freeAfterEvent = qtrue;
      G_AddEvent(ent, EV_NUKE_7, 0);
    }
  }

  trap_LinkEntity(ent);
}

void G_NukeNextStage(gentity_t * ent) {
  ent->count++;
  ent->think = G_ExplodeNuke;
  ent->nextthink = level.time + 10;
}

/*
 ================
 G_MissileDie

 Lancer - Destroy a missile
 ================
 */
void G_MissileDie(gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int mod) {
  if (inflictor == self)
    return;
  self->takedamage = qfalse;
  self->think = G_ExplodeMissile;
  self->nextthink = level.time + 10;
}

/*
 ================
 G_MissileImpact
 ================
 */
void G_MissileImpact(gentity_t *ent, trace_t * trace) {
  gentity_t *other;
  qboolean hitClient = qfalse;
  other = &g_entities[trace->entityNum];

  // check for bounce
  if (!other->takedamage && (ent->s.eFlags & (EF_BOUNCE | EF_BOUNCE_HALF | EF_STATIC))) {
    G_BounceMissile(ent, trace);
    return;
  }
  if (strcmp(ent->classname, "c4") == 0) {
    G_BounceMissile(ent, trace);
    return;
  }
  if (strcmp(ent->classname, "grenade") == 0) {
    if (other->s.eType == ET_BREAKABLE && other->takedamage && ent->damage > other->health_higher) {
      other->health = 0;
      if (G_BreakGlass(other, ent->s.origin, MOD_HE_SPLASH, NULL) == qtrue) {
        return;
      }
    }
    G_BounceMissile(ent, trace);
    return;
  }

  // impact damage
  if (other->takedamage) {
    if (ent->s.eFlags & (EF_BOUNCE | EF_BOUNCE_HALF | EF_STATIC)) {
      vec3_t velocity;
      G_Damage(other, ent, &g_entities[ent->r.ownerNum], velocity, ent->s.origin, ent->damage, 0, ent->methodOfDeath);
      if (ent->s.eFlags == EF_SHRAPNEL) {
        G_FadeShrapnel(ent);
      }
      return;
    }
    // FIXME: wrong damage direction?
    if (ent->damage) {
      vec3_t velocity;

      if (LogAccuracyHit(other, &g_entities[ent->r.ownerNum])) {
        g_entities[ent->r.ownerNum].client->accuracy_hits++;
        hitClient = qtrue;
      }
      BG_EvaluateTrajectoryDelta(&ent->s.pos, level.time, velocity);
      if (VectorLength(velocity) == 0) {
        velocity[2] = 1; // stepped on a grenade
      }
      G_Damage(other, ent, &g_entities[ent->r.ownerNum], velocity, ent->s.origin, ent->damage, 0, ent->methodOfDeath);
    }
  }

  // is it cheaper in bandwidth to just remove this ent and create a new
  // one, rather than changing the missile into the explosion?

  if (other->takedamage && other->client) {
    G_AddEvent(ent, EV_MISSILE_HIT, DirToByte(trace->plane.normal));
    ent->s.otherEntityNum = other->s.number;
  } else if (trace->surfaceFlags & SURF_METALSTEPS) {
    G_AddEvent(ent, EV_MISSILE_MISS_METAL, DirToByte(trace->plane.normal));
  } else {
    G_AddEvent(ent, EV_MISSILE_MISS, DirToByte(trace->plane.normal));
  }

  ent->freeAfterEvent = qtrue;

  // change over to a normal entity right at the point of impact
  ent->s.eType = ET_GENERAL;

  SnapVectorTowards(trace->endpos, ent->s.pos.trBase); // save net bandwidth

  G_SetOrigin(ent, trace->endpos);

  // splash damage (doesn't apply to person directly hit)
  if (ent->splashDamage) {
    if (G_RadiusDamage(trace->endpos, ent->parent, ent->splashDamage, ent->splashRadius, other, ent->splashMethodOfDeath)) {
      if (!hitClient) {
        g_entities[ent->r.ownerNum].client->accuracy_hits++;
      }
    }
  }

  trap_LinkEntity(ent);
}

/*
 ================
 G_RunMissile
 ================
 */
void G_RunMissile(gentity_t * ent) {
  vec3_t origin;
  trace_t tr;
  int passent;

  // get current position
  BG_EvaluateTrajectory(&ent->s.pos, level.time, origin);

  // if this missile bounced off an invulnerability sphere
  if (ent->target_ent) {
    passent = ent->target_ent->s.number;
  } else {
    // ignore interactions with the missile owner
    passent = ent->r.ownerNum;
  }
  // trace a line from the previous position to the current position
  trap_Trace(&tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs, origin, passent, ent->clipmask);

  if (tr.startsolid || tr.allsolid) {
    // make sure the tr.entityNum is set to the entity we're stuck in
    trap_Trace(&tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs, ent->r.currentOrigin, passent, ent->clipmask);
    tr.fraction = 0;
  } else {
    VectorCopy(tr.endpos, ent->r.currentOrigin);
  }

  trap_LinkEntity(ent);

  if (tr.fraction != 1) {
    // never explode or bounce on sky
    if (tr.surfaceFlags & SURF_NOIMPACT) {
      // If grapple, reset owner
      if (ent->parent && ent->parent->client && ent->parent->client->hook == ent) {
        ent->parent->client->hook = NULL;
      }
      G_FreeEntity(ent);
      return;
    }
    G_MissileImpact(ent, &tr);
    if (ent->s.eType != ET_MISSILE) {
      return; // exploded
    }
  }
  // check think function after bouncing
  G_RunThink(ent);
}

/*
 ================
 G_BombTouch
 ================
 */
#define BOMB_PICKUPTIME 1500
void G_BombTouch(gentity_t *ent, gentity_t *otherent, trace_t * trace) {
  if (!otherent->client) {
    return;
  }
  if (!(otherent->client->buttons & BUTTON_USE) || otherent->client->ps.stats[STAT_HEALTH] <= 0) {
    otherent->pickupTime = -1;
    return;
  }
  if (otherent->client->ps.weaponstate != WEAPON_READY) {
    return;
  }
  if (otherent->pickupTime == -1) {
    otherent->pickupTime = level.time + BOMB_PICKUPTIME;
  }
  otherent->client->ps.zoomFov = 0;
  otherent->client->ps.weaponstate = WEAPON_RAISING;
  if (otherent->pickupTime <= level.time && otherent->pickupTime != -1) {
    otherent->client->ps.stats[STAT_WEAPONS] |= (1 << WP_BOMB);
    otherent->client->clipammo[WP_BOMB]++;
    otherent->pickupTime = -1;
    otherent->client->ps.weapon = WP_BOMB;
    trap_UnlinkEntity(ent);
    G_FreeEntity(ent);
  }
}

//=============================================================================

//=============================================================================

/*
 =================
 fire_he
 =================
 */
gentity_t * fire_he(gentity_t *self, vec3_t start, vec3_t dir) {
  gentity_t *bolt;

  VectorNormalize(dir);

  bolt = G_Spawn();
  bolt->classname = "grenade";
  bolt->nextthink = level.time + 3000;
  bolt->think = G_ExplodeMissile;
  bolt->s.eType = ET_MISSILE;
  bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
  bolt->s.weapon = WP_HE;
  bolt->s.eFlags = EF_BOUNCE_HALF;
  bolt->r.ownerNum = self->s.number;
  bolt->parent = self;
  bolt->damage = 5;
  bolt->splashDamage = 250;
  bolt->splashRadius = 300;
  bolt->methodOfDeath = MOD_HE;
  bolt->splashMethodOfDeath = MOD_HE_SPLASH;
  bolt->clipmask = MASK_SHOT;
  bolt->target_ent = NULL;

  // Lancer SHOOTNADES
  bolt->health = 1; // dont use 1, else it will die if collided with other nade :D
  bolt->takedamage = qtrue;
  bolt->die = G_MissileDie;
  bolt->r.contents = CONTENTS_CORPSE;
  VectorSet(bolt->r.mins, -10, -5, 0);
  VectorCopy(bolt->r.mins, bolt->r.absmin);
  VectorSet(bolt->r.maxs, 10, 5, 6);
  VectorCopy(bolt->r.maxs, bolt->r.absmax);

  bolt->s.pos.trType = TR_GRAVITY;
  bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME; // move a bit on the very first frame
  VectorCopy(start, bolt->s.pos.trBase);
  VectorScale(dir, 1000, bolt->s.pos.trDelta);
  SnapVector(bolt->s.pos.trDelta); // save net bandwidth

  VectorCopy(start, bolt->r.currentOrigin);

  return bolt;
}

/*
 =================
 fire_shrapnel
 =================
 */
gentity_t * fire_shrapnel(gentity_t *self, vec3_t start, vec3_t dir) {
  gentity_t *bolt;
  int dmg;

  VectorNormalize(dir);

  bolt = G_Spawn();
  bolt->classname = "shrapnel";
  bolt->nextthink = level.time + 3000;
  bolt->think = G_FadeShrapnel;
  bolt->takedamage = qfalse;
  bolt->s.eType = ET_MISSILE;
  bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
  bolt->s.weapon = WP_HE;
  bolt->s.eFlags = EF_SHRAPNEL;
  bolt->r.ownerNum = self->s.number;
  bolt->parent = self;
  dmg = 40 + crandom() * 10;
  if (dmg < 30) {
    dmg = 30;
  }
  bolt->damage = dmg;
  bolt->methodOfDeath = MOD_SHRAPNEL;
  bolt->clipmask = MASK_SHOT;
  bolt->target_ent = NULL;

  start[2] += 1;

  VectorSet(bolt->r.mins, -10, -5, 6);
  VectorCopy(bolt->r.mins, bolt->r.absmin);
  VectorSet(bolt->r.maxs, 10, 5, 6);
  VectorCopy(bolt->r.maxs, bolt->r.absmax);

  bolt->s.pos.trType = TR_LINEAR;
  bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;
  VectorCopy(start, bolt->s.pos.trBase);
  VectorScale(dir, 3000, bolt->s.pos.trDelta);
  SnapVector(bolt->s.pos.trDelta);

  VectorCopy(start, bolt->r.currentOrigin);

  return bolt;
}

/*
 =================
 fire_nuke
 =================
 */
gentity_t * fire_nuke(gentity_t *self, vec3_t start, vec3_t dir) {
  gentity_t *bolt;

  VectorNormalize(dir);

  bolt = G_Spawn();
  bolt->classname = "nuke";
  bolt->nextthink = level.time + 10;
  bolt->think = G_ExplodeNuke;
  bolt->s.eType = ET_MISSILE;
  bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
  bolt->s.weapon = WP_NUKE;
  bolt->s.eFlags = EF_BOUNCE_HALF;
  bolt->r.ownerNum = self->s.number;
  bolt->parent = self;
  bolt->damage = 0;
  bolt->splashDamage = 5000;
  bolt->splashRadius = 500;
  bolt->splashMethodOfDeath = MOD_NUKE;
  bolt->clipmask = MASK_SHOT;
  bolt->target_ent = NULL;

  bolt->r.contents = CONTENTS_CORPSE;
  VectorSet(bolt->r.mins, -10, -5, 0);
  VectorCopy(bolt->r.mins, bolt->r.absmin);
  VectorSet(bolt->r.maxs, 10, 5, 6);
  VectorCopy(bolt->r.maxs, bolt->r.absmax);

  bolt->s.pos.trType = TR_GRAVITY;
  bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;
  VectorCopy(start, bolt->s.pos.trBase);
  SnapVector(bolt->s.pos.trDelta);

  VectorCopy(start, bolt->r.currentOrigin);

  bolt->count = 0;

  return bolt;
}

//=============================================================================

/*
 =================
 fire_bomb
 =================
 */
gentity_t * fire_bomb(gentity_t *self, vec3_t start, vec3_t dir) {
  gentity_t *bolt;

  VectorNormalize(dir);

  bolt = G_Spawn();
  bolt->classname = "c4";
  bolt->s.eType = ET_MISSILE;
  bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
  bolt->s.weapon = WP_BOMB;
  bolt->s.eFlags = EF_STATIC;
  bolt->r.ownerNum = self->s.number;
  bolt->parent = self;
  bolt->damage = 0;
  bolt->splashDamage = 1000;
  bolt->splashRadius = 500;
  bolt->methodOfDeath = MOD_BOMB;
  bolt->splashMethodOfDeath = MOD_BOMB;
  bolt->clipmask = MASK_SHOT;
  bolt->target_ent = NULL;

  bolt->r.contents = CONTENTS_TRIGGER;
  bolt->touch = G_BombTouch;

  VectorSet(bolt->r.mins, -6, -4, -10);
  VectorCopy(bolt->r.mins, bolt->r.absmin);
  VectorSet(bolt->r.maxs, 6, 4, 10);
  VectorCopy(bolt->r.maxs, bolt->r.absmax);

  bolt->s.pos.trType = TR_GRAVITY;
  bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME; // move a bit on the very first frame
  VectorCopy(start, bolt->s.pos.trBase);
  SnapVector(bolt->s.pos.trDelta); // save net bandwidth

  VectorCopy(start, bolt->r.currentOrigin);

  return bolt;
}

