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
// g_misc.c

#include "g_local.h"


/*QUAKED func_group (0 0 0) ?
Used to group brushes together just for editor convenience.  They are turned into normal brushes by the utilities.
 */

/*QUAKED info_camp (0 0.5 0) (-4 -4 -4) (4 4 4)
Used as a positional target for calculations in the utilities (spotlights, etc), but removed during gameplay.
 */
void SP_info_camp(gentity_t *self) {
    G_SetOrigin(self, self->s.origin);
}

/*QUAKED info_null (0 0.5 0) (-4 -4 -4) (4 4 4)
Used as a positional target for calculations in the utilities (spotlights, etc), but removed during gameplay.
 */
void SP_info_null(gentity_t *self) {
    G_FreeEntity(self);
}

/*QUAKED info_notnull (0 0.5 0) (-4 -4 -4) (4 4 4)
Used as a positional target for in-game calculation, like jumppad targets.
target_position does the same thing
 */
void SP_info_notnull(gentity_t *self) {
    G_SetOrigin(self, self->s.origin);
}

/*QUAKED light (0 1 0) (-8 -8 -8) (8 8 8) linear
Non-displayed light.
"light" overrides the default 300 intensity.
Linear checbox gives linear falloff instead of inverse square
Lights pointed at a target will be spotlights.
"radius" overrides the default 64 unit radius of a spotlight at the target point.
 */
void SP_light(gentity_t *self) {
    G_FreeEntity(self);
}

/*
=================================================================================

TELEPORTERS

=================================================================================
 */

void TeleportPlayer(gentity_t *player, vec3_t origin, vec3_t angles) {
    gentity_t *tent;

    // use temp events at source and destination to prevent the effect
    // from getting dropped by a second player event
    if (player->client->sess.sessionTeam != TEAM_SPECTATOR) {
        tent = G_TempEntity(player->client->ps.origin, EV_PLAYER_TELEPORT_OUT);
        tent->s.clientNum = player->s.clientNum;

        tent = G_TempEntity(origin, EV_PLAYER_TELEPORT_IN);
        tent->s.clientNum = player->s.clientNum;
    }

    // unlink to make sure it can't possibly interfere with G_KillBox
    trap_UnlinkEntity(player);

    VectorCopy(origin, player->client->ps.origin);
    player->client->ps.origin[2] += 1;

    // spit the player out
    AngleVectors(angles, player->client->ps.velocity, NULL, NULL);
    VectorScale(player->client->ps.velocity, 400, player->client->ps.velocity);
    player->client->ps.pm_time = 160; // hold time
    player->client->ps.pm_flags |= PMF_TIME_KNOCKBACK;

    // toggle the teleport bit so the client knows to not lerp
    player->client->ps.eFlags ^= EF_TELEPORT_BIT;

    // set angles
    SetClientViewAngle(player, angles);

    // kill anything at the destination
    if (player->client->sess.sessionTeam != TEAM_SPECTATOR) {
        G_KillBox(player);
    }

    // save results of pmove
    BG_PlayerStateToEntityState(&player->client->ps, &player->s, qtrue);

    // use the precise origin for linking
    VectorCopy(player->client->ps.origin, player->r.currentOrigin);

    if (player->client->sess.sessionTeam != TEAM_SPECTATOR) {
        trap_LinkEntity(player);
    }
}

/*QUAKED misc_teleporter_dest (1 0 0) (-32 -32 -24) (32 32 -16)
Point teleporters at these.
Now that we don't have teleport destination pads, this is just
an info_notnull
 */
void SP_misc_teleporter_dest(gentity_t *ent) {
}


//===========================================================

/*QUAKED misc_model (1 0 0) (-16 -16 -16) (16 16 16)
"model"		arbitrary .md3 file to display
 */
void SP_misc_model(gentity_t *ent) {

#if 0
    ent->s.modelindex = G_ModelIndex(ent->model);
    VectorSet(ent->mins, -16, -16, -16);
    VectorSet(ent->maxs, 16, 16, 16);
    trap_LinkEntity(ent);

    G_SetOrigin(ent, ent->s.origin);
    VectorCopy(ent->s.angles, ent->s.apos.trBase);
#else
    G_FreeEntity(ent);
#endif
}

//===========================================================

void locateCamera(gentity_t *ent) {
    vec3_t dir;
    gentity_t *target;
    gentity_t *owner;

    owner = G_PickTarget(ent->target);
    if (!owner) {
        G_Printf("Couldn't find target for misc_portal_surface\n");
        G_FreeEntity(ent);
        return;
    }
    ent->r.ownerNum = owner->s.number;

    // frame holds the rotate speed
    if (owner->spawnflags & 1) {
        ent->s.frame = 25;
    } else if (owner->spawnflags & 2) {
        ent->s.frame = 75;
    }

    // swing camera ?
    if (owner->spawnflags & 4) {
        // set to 0 for no rotation at all
        ent->s.powerups = 0;
    } else {
        ent->s.powerups = 1;
    }

    // clientNum holds the rotate offset
    ent->s.clientNum = owner->s.clientNum;

    VectorCopy(owner->s.origin, ent->s.origin2);

    // see if the portal_camera has a target
    target = G_PickTarget(owner->target);
    if (target) {
        VectorSubtract(target->s.origin, owner->s.origin, dir);
        VectorNormalize(dir);
    } else {
        G_SetMovedir(owner->s.angles, dir);
    }

    ent->s.eventParm = DirToByte(dir);
}

/*QUAKED misc_portal_surface (0 0 1) (-8 -8 -8) (8 8 8)
The portal surface nearest this entity will show a view from the targeted misc_portal_camera, or a mirror view if untargeted.
This must be within 64 world units of the surface!
 */
void SP_misc_portal_surface(gentity_t *ent) {
    VectorClear(ent->r.mins);
    VectorClear(ent->r.maxs);
    trap_LinkEntity(ent);

    ent->r.svFlags = SVF_PORTAL;
    ent->s.eType = ET_PORTAL;

    if (!ent->target) {
        VectorCopy(ent->s.origin, ent->s.origin2);
    } else {
        ent->think = locateCamera;
        ent->nextthink = level.time + 100;
    }
}

/*QUAKED misc_portal_camera (0 0 1) (-8 -8 -8) (8 8 8) slowrotate fastrotate noswing
The target for a misc_portal_director.  You can set either angles or target another entity to determine the direction of view.
"roll" an angle modifier to orient the camera around the target vector;
 */
void SP_misc_portal_camera(gentity_t *ent) {
    float roll;

    VectorClear(ent->r.mins);
    VectorClear(ent->r.maxs);
    trap_LinkEntity(ent);

    G_SpawnFloat("roll", "0", &roll);

    ent->s.clientNum = roll / 360.0 * 256;
}

/*
======================================================================

  SHOOTERS

======================================================================
 */

void Use_Shooter(gentity_t *ent, gentity_t *other, gentity_t *activator) {
    vec3_t dir;
    float deg;
    vec3_t up, right;

    // see if we have a target
    if (ent->enemy) {
        VectorSubtract(ent->enemy->r.currentOrigin, ent->s.origin, dir);
        VectorNormalize(dir);
    } else {
        VectorCopy(ent->movedir, dir);
    }

    // randomize a bit
    PerpendicularVector(up, dir);
    CrossProduct(up, dir, right);

    deg = crandom() * ent->random;
    VectorMA(dir, deg, up, dir);

    deg = crandom() * ent->random;
    VectorMA(dir, deg, right, dir);

    VectorNormalize(dir);

    switch (ent->s.weapon) {
        default:
            FireEntWeapon(ent, dir);
            break;
    }

    G_AddEvent(ent, EV_FIRE_WEAPON, 0);
}

static void InitShooter_Finish(gentity_t *ent) {
    ent->enemy = G_PickTarget(ent->target);
    ent->think = 0;
    ent->nextthink = 0;
}

void InitShooter(gentity_t *ent, int weapon) {
    if (weapon < 0) {
        G_FreeEntity(ent);
    }
    ent->use = Use_Shooter;
    ent->s.weapon = weapon;

    RegisterItem(BG_FindItemForWeapon(weapon));

    G_SetMovedir(ent->s.angles, ent->movedir);

    if (!ent->random) {
        ent->random = 1.0;
    }
    ent->random = sin(M_PI * ent->random / 180);
    // target might be a moving object, so we can't set movedir for it
    if (ent->target) {
        ent->think = InitShooter_Finish;
        ent->nextthink = level.time + 500;
    }
    trap_LinkEntity(ent);
}

/*QUAKED func_breakable (1 0 0) (-16 -16 -16) (16 16 16)
 Explodes glass
 */
void SP_func_breakable(gentity_t *ent) {
    int health, min;
    //int type;
    char *type;

    // Make it appear as the brush
    trap_SetBrushModel(ent, ent->model);
    // Lets give it 5 health if the mapper did not set its health
    G_SpawnInt("health", "5", &health);
    if (health <= 0) {
        health = 5;
    }
    G_SpawnInt("minimum", "0", &min);
    if (min < 0) {
        min = 0;
    }

    G_SpawnString("type", "glass", &type);
    ent->health = health;
    ent->health_higher = min;
    // Let it take damage
    ent->takedamage = qtrue;
    // Let it know it is a breakable object
    ent->s.eType = ET_BREAKABLE;
    ent->message = type;
    // If the mapper gave it a model, use it
    if (ent->model2) {
        ent->s.modelindex2 = G_ModelIndex(ent->model2);
    }
    // Link all ^this^ info into the ent
    trap_LinkEntity(ent);
}

/*
=================
G_BreakGlass
=================
 */
qboolean G_BreakGlass(gentity_t *ent, vec3_t point, int mod, gentity_t *activator) {
    gentity_t *tent;
    vec3_t size;
    vec3_t center;
    qboolean splashdmg;

    // Get the center of the glass
    VectorSubtract(ent->r.maxs, ent->r.mins, size);
    VectorScale(size, 0.5, size);
    VectorAdd(ent->r.mins, size, center);

    // If the glass has no more life, BREAK IT
    if (ent->health <= 0) {
        // Tell the program based on the gun if it has no splash dmg
        splashdmg = qfalse;
        if (mod == MOD_HE_SPLASH
                || mod == MOD_NUKE
                || mod == MOD_BOMB) {
            splashdmg = qtrue;
        }
        // Call the function to show the glass shards in cgame
        // center can be changed to point which will spawn the
        // where the killing bullet hit but wont work with Splash Damage weapons
        // so I just use the center of the glass
        switch (splashdmg) {
            case qtrue:
                if (!Q_stricmp(ent->message, "glass")) {
                    tent = G_TempEntity(center, EV_BREAK_GLASS);
                } else if (!Q_stricmp(ent->message, "flesh")) {
                    tent = G_TempEntity(center, EV_BREAK_FLESH);
                } else if (!Q_stricmp(ent->message, "wood")) {
                    tent = G_TempEntity(center, EV_BREAK_WOOD);
                } else if (!Q_stricmp(ent->message, "stone") || !Q_stricmp(ent->message, "concrete")) {
                    tent = G_TempEntity(center, EV_BREAK_STONE);
                } else if (!Q_stricmp(ent->message, "metal")) {
                    tent = G_TempEntity(center, EV_BREAK_METAL);
                } else {
                    tent = G_TempEntity(center, EV_BREAK_GLASS);
                }
                break;
            case qfalse:
                if (!Q_stricmp(ent->message, "glass")) {
                    tent = G_TempEntity(point, EV_BREAK_GLASS);
                } else if (!Q_stricmp(ent->message, "flesh")) {
                    tent = G_TempEntity(point, EV_BREAK_FLESH);
                } else if (!Q_stricmp(ent->message, "wood")) {
                    tent = G_TempEntity(point, EV_BREAK_WOOD);
                } else if (!Q_stricmp(ent->message, "stone") || !Q_stricmp(ent->message, "concrete")) {
                    tent = G_TempEntity(point, EV_BREAK_STONE);
                } else if (!Q_stricmp(ent->message, "metal")) {
                    tent = G_TempEntity(point, EV_BREAK_METAL);
                } else {
                    tent = G_TempEntity(point, EV_BREAK_GLASS);
                }
                break;
        }
        G_UseTargets(ent, activator);
        G_FreeEntity(ent);
        tent->s.eventParm = 0;
        return qtrue;
    } else {
        return qfalse;
    }
}

/*QUAKED shooter_rocket (1 0 0) (-16 -16 -16) (16 16 16)
Fires at either the target or the current direction.
"random" the number of degrees of deviance from the taget. (1.0 default)
 */
void SP_shooter_rocket(gentity_t *ent) {
    //InitShooter( ent, WP_ROCKET_LAUNCHER );
}

/*QUAKED shooter_plasma (1 0 0) (-16 -16 -16) (16 16 16)
Fires at either the target or the current direction.
"random" is the number of degrees of deviance from the taget. (1.0 default)
 */
void SP_shooter_plasma(gentity_t *ent) {
    InitShooter(ent, WP_ACR);
}

/*QUAKED shooter_grenade (1 0 0) (-16 -16 -16) (16 16 16)
Fires at either the target or the current direction.
"random" is the number of degrees of deviance from the taget. (1.0 default)
 */
void SP_shooter_grenade(gentity_t *ent) {
    InitShooter(ent, WP_HE);
}

/*QUAKED shooter_nuke (1 0 0) (-16 -16 -16) (16 16 16)
Fires at either the target or the current direction.
"random" is the number of degrees of deviance from the taget. (1.0 default)
 */
void SP_shooter_nuke(gentity_t *ent) {
    InitShooter(ent, WP_NUKE);
}

void SP_func_shooter(gentity_t *ent) {
    int weapon;

    G_SpawnInt("weapon", "-1", &weapon);
    InitShooter(ent, weapon);
}
