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
// cg_weapons.c -- events and effects dealing with weapons
#include "cg_local.h"
#undef MISSIONPACK

/*
==========================
CG_MachineGunEjectBrass
==========================
 */
static void CG_MachineGunEjectBrass(centity_t *cent) {
    localEntity_t *le;
    refEntity_t *re;
    vec3_t velocity, xvelocity;
    vec3_t offset, xoffset;
    float waterScale = 1.0f;
    vec3_t v[3];

    if (cg_brassTime.integer <= 0) {
        return;
    }

    le = CG_AllocLocalEntity();
    re = &le->refEntity;

    velocity[0] = 0;
    velocity[1] = -70 + 40 * crandom();
    velocity[2] = 100;

    le->leType = LE_FRAGMENT;
    le->startTime = cg.time;
    le->endTime = le->startTime + cg_brassTime.integer + (cg_brassTime.integer / 4) * random();

    le->pos.trType = TR_GRAVITY;
    le->pos.trTime = cg.time - (rand()&15);

    AnglesToAxis(cent->lerpAngles, v);

    offset[0] = 8;
    offset[1] = -4;
    offset[2] = 24;

    xoffset[0] = offset[0] * v[0][0] + offset[1] * v[1][0] + offset[2] * v[2][0];
    xoffset[1] = offset[0] * v[0][1] + offset[1] * v[1][1] + offset[2] * v[2][1];
    xoffset[2] = offset[0] * v[0][2] + offset[1] * v[1][2] + offset[2] * v[2][2];
    VectorAdd(cent->lerpOrigin, xoffset, re->origin);

    VectorCopy(re->origin, le->pos.trBase);

    if (CG_PointContents(re->origin, -1) & CONTENTS_WATER) {
        waterScale = 0.10f;
    }

    xvelocity[0] = velocity[0] * v[0][0] + velocity[1] * v[1][0] + velocity[2] * v[2][0];
    xvelocity[1] = velocity[0] * v[0][1] + velocity[1] * v[1][1] + velocity[2] * v[2][1];
    xvelocity[2] = velocity[0] * v[0][2] + velocity[1] * v[1][2] + velocity[2] * v[2][2];
    VectorScale(xvelocity, waterScale, le->pos.trDelta);

    AxisCopy(axisDefault, re->axis);
    re->hModel = cgs.media.machinegunBrassModel;

    le->bounceFactor = 0.4 * waterScale;

    le->angles.trType = TR_LINEAR;
    le->angles.trTime = cg.time;
    le->angles.trBase[0] = rand()&31;
    le->angles.trBase[1] = rand()&31;
    le->angles.trBase[2] = rand()&31;
    le->angles.trDelta[0] = 2;
    le->angles.trDelta[1] = 1;
    le->angles.trDelta[2] = 0;

    le->leFlags = LEF_TUMBLE;
    le->leBounceSoundType = LEBS_BRASS;
    le->leMarkType = LEMT_NONE;
}

/*
==========================
CG_ShotgunEjectBrass
==========================
 */
static void CG_ShotgunEjectBrass(centity_t *cent) {
    localEntity_t *le;
    refEntity_t *re;
    vec3_t velocity, xvelocity;
    vec3_t offset, xoffset;
    vec3_t v[3];
    int i;

    if (cg_brassTime.integer <= 0) {
        return;
    }

    for (i = 0; i < 2; i++) {
        float waterScale = 1.0f;

        le = CG_AllocLocalEntity();
        re = &le->refEntity;

        velocity[0] = 60 + 60 * crandom();
        if (i == 0) {
            velocity[1] = 40 + 10 * crandom();
        } else {
            velocity[1] = -40 + 10 * crandom();
        }
        velocity[2] = 100 + 50 * crandom();

        le->leType = LE_FRAGMENT;
        le->startTime = cg.time;
        le->endTime = le->startTime + cg_brassTime.integer * 3 + cg_brassTime.integer * random();

        le->pos.trType = TR_GRAVITY;
        le->pos.trTime = cg.time;

        AnglesToAxis(cent->lerpAngles, v);

        offset[0] = 8;
        offset[1] = 0;
        offset[2] = 24;

        xoffset[0] = offset[0] * v[0][0] + offset[1] * v[1][0] + offset[2] * v[2][0];
        xoffset[1] = offset[0] * v[0][1] + offset[1] * v[1][1] + offset[2] * v[2][1];
        xoffset[2] = offset[0] * v[0][2] + offset[1] * v[1][2] + offset[2] * v[2][2];
        VectorAdd(cent->lerpOrigin, xoffset, re->origin);
        VectorCopy(re->origin, le->pos.trBase);
        if (CG_PointContents(re->origin, -1) & CONTENTS_WATER) {
            waterScale = 0.10f;
        }

        xvelocity[0] = velocity[0] * v[0][0] + velocity[1] * v[1][0] + velocity[2] * v[2][0];
        xvelocity[1] = velocity[0] * v[0][1] + velocity[1] * v[1][1] + velocity[2] * v[2][1];
        xvelocity[2] = velocity[0] * v[0][2] + velocity[1] * v[1][2] + velocity[2] * v[2][2];
        VectorScale(xvelocity, waterScale, le->pos.trDelta);

        AxisCopy(axisDefault, re->axis);
        re->hModel = cgs.media.shotgunBrassModel;
        le->bounceFactor = 0.3f;

        le->angles.trType = TR_LINEAR;
        le->angles.trTime = cg.time;
        le->angles.trBase[0] = rand()&31;
        le->angles.trBase[1] = rand()&31;
        le->angles.trBase[2] = rand()&31;
        le->angles.trDelta[0] = 1;
        le->angles.trDelta[1] = 0.5;
        le->angles.trDelta[2] = 0;

        le->leFlags = LEF_TUMBLE;
        le->leBounceSoundType = LEBS_BRASS;
        le->leMarkType = LEMT_NONE;
    }
}

/*
==========================
CG_RailTrail
==========================
 */
void CG_RailTrail(clientInfo_t *ci, vec3_t start, vec3_t end) {
    vec3_t axis[36], move, move2, next_move, vec, temp;
    float len;
    int i, j, skip;

    localEntity_t *le;
    refEntity_t *re;

#define RADIUS   4
#define ROTATION 1
#define SPACING  5

    start[2] -= 4;

    le = CG_AllocLocalEntity();
    re = &le->refEntity;

    le->leType = LE_FADE_RGB;
    le->startTime = cg.time;
    le->endTime = cg.time + cg_railTrailTime.value;
    le->lifeRate = 1.0 / (le->endTime - le->startTime);

    re->shaderTime = cg.time / 1000.0f;
    re->reType = RT_RAIL_CORE;
    re->customShader = cgs.media.railCoreShader;

    VectorCopy(start, re->origin);
    VectorCopy(end, re->oldorigin);

    re->shaderRGBA[0] = ci->color1[0] * 255;
    re->shaderRGBA[1] = ci->color1[1] * 255;
    re->shaderRGBA[2] = ci->color1[2] * 255;
    re->shaderRGBA[3] = 255;

    le->color[0] = ci->color1[0] * 0.75;
    le->color[1] = ci->color1[1] * 0.75;
    le->color[2] = ci->color1[2] * 0.75;
    le->color[3] = 1.0f;

    AxisClear(re->axis);

    if (cg_oldRail.integer) {
        // nudge down a bit so it isn't exactly in center
        re->origin[2] -= 8;
        re->oldorigin[2] -= 8;
        return;
    }

    VectorCopy(start, move);
    VectorSubtract(end, start, vec);
    len = VectorNormalize(vec);
    PerpendicularVector(temp, vec);
    for (i = 0; i < 36; i++) {
        RotatePointAroundVector(axis[i], vec, temp, i * 10); //banshee 2.4 was 10
    }

    VectorMA(move, 20, vec, move);
    VectorCopy(move, next_move);
    VectorScale(vec, SPACING, vec);

    skip = -1;

    j = 18;
    for (i = 0; i < len; i += SPACING) {
        if (i != skip) {
            skip = i + SPACING;
            le = CG_AllocLocalEntity();
            re = &le->refEntity;
            le->leFlags = LEF_PUFF_DONT_SCALE;
            le->leType = LE_MOVE_SCALE_FADE;
            le->startTime = cg.time;
            le->endTime = cg.time + (i >> 1) + 300;
            le->lifeRate = 1.0 / (le->endTime - le->startTime);

            re->shaderTime = cg.time / 2000.0f;
            re->reType = RT_SPRITE;
            re->radius = 1.1f;
            re->customShader = cgs.media.railRingsShader;

            re->shaderRGBA[0] = ci->color2[0] * 255;
            re->shaderRGBA[1] = ci->color2[1] * 255;
            re->shaderRGBA[2] = ci->color2[2] * 255;
            re->shaderRGBA[3] = 255;

            le->color[0] = ci->color2[0] * 0.75;
            le->color[1] = ci->color2[1] * 0.75;
            le->color[2] = ci->color2[2] * 0.75;
            le->color[3] = 1.0f;

            le->pos.trType = TR_LINEAR;
            le->pos.trTime = cg.time;

            VectorCopy(move, move2);
            VectorMA(move2, RADIUS, axis[j], move2);
            VectorCopy(move2, le->pos.trBase);

            le->pos.trDelta[0] = axis[j][0]*6;
            le->pos.trDelta[1] = axis[j][1]*6;
            le->pos.trDelta[2] = axis[j][2]*6;
        }

        VectorAdd(move, vec, move);

        j = (j + ROTATION) % 36;
    }
}

/*
==========================
CG_RocketTrail
==========================
 */
static void CG_RocketTrail(centity_t *ent, const weaponInfo_t *wi) {
    int step;
    vec3_t origin, lastPos;
    int t;
    int startTime, contents;
    int lastContents;
    entityState_t *es;
    vec3_t up;
    localEntity_t *smoke;

    if (cg_noProjectileTrail.integer) {
        return;
    }

    up[0] = 0;
    up[1] = 0;
    up[2] = 0;

    step = 50;

    es = &ent->currentState;
    startTime = ent->trailTime;
    t = step * ((startTime + step) / step);

    BG_EvaluateTrajectory(&es->pos, cg.time, origin);
    contents = CG_PointContents(origin, -1);

    // if object (e.g. grenade) is stationary, don't toss up smoke
    if (es->pos.trType == TR_STATIONARY) {
        ent->trailTime = cg.time;
        return;
    }

    BG_EvaluateTrajectory(&es->pos, ent->trailTime, lastPos);
    lastContents = CG_PointContents(lastPos, -1);

    ent->trailTime = cg.time;

    if (contents & (CONTENTS_WATER | CONTENTS_SLIME | CONTENTS_LAVA)) {
        if (contents & lastContents & CONTENTS_WATER) {
            CG_BubbleTrail(lastPos, origin, 8);
        }
        return;
    }

    for (; t <= ent->trailTime; t += step) {
        BG_EvaluateTrajectory(&es->pos, t, lastPos);

        smoke = CG_SmokePuff(lastPos, up,
                wi->trailRadius,
                1, 1, 1, 0.33f,
                wi->wiTrailTime,
                t,
                0,
                0,
                cgs.media.smokePuffShader);
        // use the optimized local entity add
        smoke->leType = LE_SCALE_FADE;
    }

}

/*
==========================
CG_PlasmaTrail
==========================
 */
static void CG_PlasmaTrail(centity_t *cent, const weaponInfo_t *wi) {
    localEntity_t *le;
    refEntity_t *re;
    entityState_t *es;
    vec3_t velocity, xvelocity, origin;
    vec3_t offset, xoffset;
    vec3_t v[3];
    int t, startTime, step;

    float waterScale = 1.0f;

    if (cg_noProjectileTrail.integer || cg_oldPlasma.integer) {
        return;
    }

    step = 50;

    es = &cent->currentState;
    startTime = cent->trailTime;
    t = step * ((startTime + step) / step);

    BG_EvaluateTrajectory(&es->pos, cg.time, origin);

    le = CG_AllocLocalEntity();
    re = &le->refEntity;

    velocity[0] = 60 - 120 * crandom();
    velocity[1] = 40 - 80 * crandom();
    velocity[2] = 100 - 200 * crandom();

    le->leType = LE_MOVE_SCALE_FADE;
    le->leFlags = LEF_TUMBLE;
    le->leBounceSoundType = LEBS_NONE;
    le->leMarkType = LEMT_NONE;

    le->startTime = cg.time;
    le->endTime = le->startTime + 600;

    le->pos.trType = TR_GRAVITY;
    le->pos.trTime = cg.time;

    AnglesToAxis(cent->lerpAngles, v);

    offset[0] = 2;
    offset[1] = 2;
    offset[2] = 2;

    xoffset[0] = offset[0] * v[0][0] + offset[1] * v[1][0] + offset[2] * v[2][0];
    xoffset[1] = offset[0] * v[0][1] + offset[1] * v[1][1] + offset[2] * v[2][1];
    xoffset[2] = offset[0] * v[0][2] + offset[1] * v[1][2] + offset[2] * v[2][2];

    VectorAdd(origin, xoffset, re->origin);
    VectorCopy(re->origin, le->pos.trBase);

    if (CG_PointContents(re->origin, -1) & CONTENTS_WATER) {
        waterScale = 0.10f;
    }

    xvelocity[0] = velocity[0] * v[0][0] + velocity[1] * v[1][0] + velocity[2] * v[2][0];
    xvelocity[1] = velocity[0] * v[0][1] + velocity[1] * v[1][1] + velocity[2] * v[2][1];
    xvelocity[2] = velocity[0] * v[0][2] + velocity[1] * v[1][2] + velocity[2] * v[2][2];
    VectorScale(xvelocity, waterScale, le->pos.trDelta);

    AxisCopy(axisDefault, re->axis);
    re->shaderTime = cg.time / 1000.0f;
    re->reType = RT_SPRITE;
    re->radius = 0.25f;
    re->customShader = cgs.media.railRingsShader;
    le->bounceFactor = 0.3f;

    re->shaderRGBA[0] = wi->flashDlightColor[0] * 63;
    re->shaderRGBA[1] = wi->flashDlightColor[1] * 63;
    re->shaderRGBA[2] = wi->flashDlightColor[2] * 63;
    re->shaderRGBA[3] = 63;

    le->color[0] = wi->flashDlightColor[0] * 0.2;
    le->color[1] = wi->flashDlightColor[1] * 0.2;
    le->color[2] = wi->flashDlightColor[2] * 0.2;
    le->color[3] = 0.25f;

    le->angles.trType = TR_LINEAR;
    le->angles.trTime = cg.time;
    le->angles.trBase[0] = rand()&31;
    le->angles.trBase[1] = rand()&31;
    le->angles.trBase[2] = rand()&31;
    le->angles.trDelta[0] = 1;
    le->angles.trDelta[1] = 0.5;
    le->angles.trDelta[2] = 0;

}

/*
==========================
CG_GrappleTrail
==========================
 */
void CG_GrappleTrail(centity_t *ent, const weaponInfo_t *wi) {
    vec3_t origin;
    entityState_t *es;
    vec3_t forward, up;
    refEntity_t beam;

    es = &ent->currentState;

    BG_EvaluateTrajectory(&es->pos, cg.time, origin);
    ent->trailTime = cg.time;

    memset(&beam, 0, sizeof ( beam));
    //FIXME adjust for muzzle position
    VectorCopy(cg_entities[ ent->currentState.otherEntityNum ].lerpOrigin, beam.origin);
    beam.origin[2] += 26;
    AngleVectors(cg_entities[ ent->currentState.otherEntityNum ].lerpAngles, forward, NULL, up);
    VectorMA(beam.origin, -6, up, beam.origin);
    VectorCopy(origin, beam.oldorigin);

    if (Distance(beam.origin, beam.oldorigin) < 64)
        return; // Don't draw if close

    beam.reType = RT_LIGHTNING;
    beam.customShader = cgs.media.lightningShader;

    AxisClear(beam.axis);
    beam.shaderRGBA[0] = 0xff;
    beam.shaderRGBA[1] = 0xff;
    beam.shaderRGBA[2] = 0xff;
    beam.shaderRGBA[3] = 0xff;
    trap_R_AddRefEntityToScene(&beam);
}

/*
==========================
CG_GrenadeTrail
==========================
 */
static void CG_GrenadeTrail(centity_t *ent, const weaponInfo_t *wi) {
    CG_RocketTrail(ent, wi);
}

/*
==========================
CG_ExplosionParticles
SPARK
==========================
 */
void CG_ExplosionParticles(int weapon, vec3_t origin) {
    int number; // number of particles
    int jump; // amount to nudge the particles trajectory vector up by
    int speed; // speed of particles
    int light; // amount of light for each particle
    vec4_t lColor; // color of light for each particle
    qhandle_t shader; // shader to use for the particles
    int index;
    vec3_t randVec, tempVec;
    vec3_t up;
    // set defaults
    number = 32;
    jump = 50;
    speed = 300;
    light = 50;
    lColor[0] = 1.0f;
    lColor[1] = 1.0f;
    lColor[2] = 1.0f;
    lColor[3] = 1.0f; // alpha

    switch (weapon) {
        case WP_NUKE:
            return;
            break;
        case WP_HE:
            shader = cgs.media.sha_spark;
            number = 128;
            jump = 100;
            speed = 400;
            light = 0;
            lColor[0] = 1.0f;
            lColor[1] = 0.56f;
            lColor[2] = 0.0f;
            break;
        default:
            return;
    }

    for (index = 0; index < number; index++) {
        localEntity_t *le;
        refEntity_t *re;
        int msec;

        le = CG_AllocLocalEntity(); //allocate a local entity
        re = &le->refEntity;
        le->leFlags = LEF_PUFF_DONT_SCALE; //don't change the particle size
        le->leType = LE_MOVE_SCALE_FADE; // particle should fade over time
        le->startTime = cg.time - random()*100; // set the start time of the particle to the current time
        le->endTime = cg.time + 3000 + random() * 250; //set the end time
        le->lifeRate = 1.0 / (le->endTime - le->startTime);
        re = &le->refEntity;
        re->shaderTime = cg.time / 5.0f;
        re->reType = RT_SPRITE;
        re->rotation = 0;
        re->radius = 3;
        re->customShader = shader;
        re->shaderRGBA[0] = 0xff;
        re->shaderRGBA[1] = 0xff;
        re->shaderRGBA[2] = 0xff;
        re->shaderRGBA[3] = 0xff;
        le->light = light;
        VectorCopy(lColor, le->lightColor);
        le->color[3] = 1.0;
        le->pos.trType = TR_GRAVITY; // moves in a gravity affected arc
        le->pos.trTime = cg.time;
        VectorCopy(origin, le->pos.trBase);

        tempVec[0] = crandom()*2; //between 1 and -1
        tempVec[1] = crandom()*2;
        tempVec[2] = crandom();
        // dont let them go down too much, most nades explode on the ground
        if (tempVec[2] < -0.5f) {
            tempVec[2] *= -1.0f;
        }
        VectorNormalize(tempVec);
        VectorScale(tempVec, speed, randVec);
        randVec[2] += jump; //nudge the particles up a bit
        VectorCopy(randVec, le->pos.trDelta);
        up[0] = crandom()*10;
        up[1] = crandom()*10;
        up[2] = crandom()*7.5f;
        msec = 1000+crandom()*1000;
        if (msec < 0) {
            msec *= -1;
        } else if (msec == 0) {
            msec = 1000;
        }
        // smoke dat shit up
        CG_MakeExplosion(origin, up, cgs.media.dishFlashModel, cgs.media.grenadeSmokeShader, msec, qtrue);
    }

}

/*
=================
CG_RegisterWeapon

The server says this item is used on this level
=================
 */
void CG_RegisterWeapon(int weaponNum) {
    weaponInfo_t *weaponInfo;
    gitem_t *item, *ammo;
    char path[MAX_QPATH];
    vec3_t mins, maxs;
    int i;

    weaponInfo = &cg_weapons[weaponNum];

    if (weaponNum == 0) {
        return;
    }

    if (weaponInfo->registered) {
        return;
    }

    memset(weaponInfo, 0, sizeof ( *weaponInfo));
    weaponInfo->registered = qtrue;

    for (item = bg_itemlist + 1; item->classname; item++) {
        if (item->giType == IT_WEAPON && item->giTag == weaponNum) {
            weaponInfo->item = item;
            break;
        }
    }
    if (!item->classname) {
        CG_Error("Couldn't find weapon %i", weaponNum);
    }
    CG_RegisterItemVisuals(item - bg_itemlist);

    // load cmodel before model so filecache works
    weaponInfo->weaponModel = trap_R_RegisterModel(item->world_model[0]);

    // calc midpoint for rotation
    trap_R_ModelBounds(weaponInfo->weaponModel, mins, maxs);
    for (i = 0; i < 3; i++) {
        weaponInfo->weaponMidpoint[i] = mins[i] + 0.5 * (maxs[i] - mins[i]);
    }

    weaponInfo->weaponIcon = trap_R_RegisterShader(item->icon);
    weaponInfo->ammoIcon = trap_R_RegisterShader(item->icon);

    for (ammo = bg_itemlist + 1; ammo->classname; ammo++) {
        if (ammo->giType == IT_AMMO && ammo->giTag == weaponNum) {
            break;
        }
    }
    if (ammo->classname && ammo->world_model[0]) {
        weaponInfo->ammoModel = trap_R_RegisterModel(ammo->world_model[0]);
    }

    strcpy(path, item->world_model[0]);
    COM_StripExtension(path, path, sizeof (path));
    strcat(path, "_flash.md3");
    weaponInfo->flashModel = trap_R_RegisterModel(path);

    strcpy(path, item->world_model[0]);
    COM_StripExtension(path, path, sizeof (path));
    strcat(path, "_barrel.md3");
    weaponInfo->barrelModel = trap_R_RegisterModel(path);

    strcpy(path, item->world_model[0]);
    COM_StripExtension(path, path, sizeof (path));
    strcat(path, "_hand.md3");
    weaponInfo->handsModel = trap_R_RegisterModel(path);

    if (!weaponInfo->handsModel) {
        weaponInfo->handsModel = trap_R_RegisterModel("models/weapons2/shotgun/shotgun_hand.md3");
    }

    weaponInfo->loopFireSound = qfalse;

    switch (weaponNum) {
            /*case WP_SHOTGUN:
                    MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
                    weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/shotgun/sshotf1b.wav", qfalse );
                    weaponInfo->ejectBrassFunc = CG_ShotgunEjectBrass;
                    break;*/

            // RAIN WEAPONS

        case WP_KNIFE:
            weaponInfo->flashSound[0] = trap_S_RegisterSound("sound/weapons/melee/fstatck.wav", qfalse);
            break;

        case WP_HANDS:
            weaponInfo->flashSound[0] = trap_S_RegisterSound("sound/weapons/melee/fstatck.wav", qfalse);
            break;

        case WP_BARRETT:
            MAKERGB(weaponInfo->flashDlightColor, 1, 0.5f, 0);
            weaponInfo->flashSound[0] = trap_S_RegisterSound("sound/weapons/railgun/railgf1a.wav", qfalse);
            cgs.media.railExplosionShader = trap_R_RegisterShader("railExplosion");
            cgs.media.railRingsShader = trap_R_RegisterShader("railDisc");
            cgs.media.railCoreShader = trap_R_RegisterShader("railCore");
            break;

        case WP_INTERVENTION:
            MAKERGB(weaponInfo->flashDlightColor, 1, 0.5f, 0);
            weaponInfo->flashSound[0] = trap_S_RegisterSound("sound/weapons/railgun/railgf1a.wav", qfalse);
            cgs.media.railExplosionShader = trap_R_RegisterShader("railExplosion");
            cgs.media.railRingsShader = trap_R_RegisterShader("railDisc");
            cgs.media.railCoreShader = trap_R_RegisterShader("railCore");
            break;

        case WP_CROSSBOW:
            weaponInfo->flashSound[0] = trap_S_RegisterSound("sound/weapons/railgun/railgf1a.wav", qfalse);
            cgs.media.railExplosionShader = trap_R_RegisterShader("railExplosion");
            cgs.media.railRingsShader = trap_R_RegisterShader("railDisc");
            cgs.media.railCoreShader = trap_R_RegisterShader("railCore");
            break;

        case WP_HE:
            weaponInfo->missileModel = trap_R_RegisterModel("models/ammo/grenade1.md3");
            //weaponInfo->missileTrailFunc = CG_GrenadeTrail;
            //weaponInfo->wiTrailTime = 700;
            //weaponInfo->trailRadius = 32;
            weaponInfo->flashSound[0] = trap_S_RegisterSound("sound/weapons/grenade/grenlf1a.wav", qfalse);
            cgs.media.grenadeExplosionShader = trap_R_RegisterShader("grenadeExplosion");
            cgs.media.grenadeSmokeShader = trap_R_RegisterShader("grenadeSmoke");
            break;

        case WP_NUKE:
            weaponInfo->missileModel = trap_R_RegisterModel("models/ammo/grenade1.md3");
            weaponInfo->flashSound[0] = trap_S_RegisterSound("sound/weapons/grenade/grenlf1a.wav", qfalse);
            cgs.media.grenadeExplosionShader = trap_R_RegisterShader("grenadeExplosion");
            cgs.media.nukeSmokeShader = trap_R_RegisterShader("nukeSmoke");
            cgs.media.flameShader = trap_R_RegisterShader("nukeFlame");
            break;

        case WP_ACR:
            MAKERGB(weaponInfo->flashDlightColor, 1, 1, 0);
            weaponInfo->flashSound[0] = trap_S_RegisterSound("sound/weapons/machinegun/machgf1b.wav", qfalse);
            weaponInfo->flashSound[1] = trap_S_RegisterSound("sound/weapons/machinegun/machgf2b.wav", qfalse);
            weaponInfo->flashSound[2] = trap_S_RegisterSound("sound/weapons/machinegun/machgf3b.wav", qfalse);
            weaponInfo->flashSound[3] = trap_S_RegisterSound("sound/weapons/machinegun/machgf4b.wav", qfalse);
            weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
            cgs.media.bulletExplosionShader = trap_R_RegisterShader("bulletExplosion");
            break;

        case WP_BOMB:
            //weaponInfo->missileModel = trap_R_RegisterModel("models/ammo/grenade1.md3");
            weaponInfo->missileModel = trap_R_RegisterModel("models/weapons/c4/c4.md3");
            weaponInfo->flashSound[0] = trap_S_RegisterSound("sound/weapons/grenade/grenlf1a.wav", qfalse);
            break;

        case WP_WALTHER:
            MAKERGB(weaponInfo->flashDlightColor, 1, 1, 0);
            weaponInfo->flashSound[0] = trap_S_RegisterSound("sound/weapons/machinegun/machgf1b.wav", qfalse);
            weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
            cgs.media.bulletExplosionShader = trap_R_RegisterShader("bulletExplosion");
            break;

        case WP_INJECTOR:
            weaponInfo->flashSound[0] = trap_S_RegisterSound("sound/weapons/melee/fstatck.wav", qfalse);
            break;

            // end rain weapons

        default:
            MAKERGB(weaponInfo->flashDlightColor, 1, 1, 1);
            weaponInfo->flashSound[0] = trap_S_RegisterSound("sound/weapons/rocket/rocklf1a.wav", qfalse);
            break;
    }
}

/*
=================
CG_RegisterItemVisuals

The server says this item is used on this level
=================
 */
void CG_RegisterItemVisuals(int itemNum) {
    itemInfo_t *itemInfo;
    gitem_t *item;

    if (itemNum < 0 || itemNum >= bg_numItems) {
        CG_Error("CG_RegisterItemVisuals: itemNum %d out of range [0-%d]", itemNum, bg_numItems - 1);
    }

    itemInfo = &cg_items[ itemNum ];
    if (itemInfo->registered) {
        return;
    }

    item = &bg_itemlist[ itemNum ];

    memset(itemInfo, 0, sizeof ( &itemInfo));
    itemInfo->registered = qtrue;

    itemInfo->models[0] = trap_R_RegisterModel(item->world_model[0]);

    itemInfo->icon = trap_R_RegisterShader(item->icon);

    if (item->giType == IT_WEAPON) {
        CG_RegisterWeapon(item->giTag);
    }

    //
    // powerups have an accompanying ring or sphere
    //
    if (item->giType == IT_POWERUP || item->giType == IT_HEALTH ||
            item->giType == IT_ARMOR || item->giType == IT_HOLDABLE) {
        if (item->world_model[1]) {
            itemInfo->models[1] = trap_R_RegisterModel(item->world_model[1]);
        }
    }
}


/*
========================================================================================

VIEW WEAPON

========================================================================================
 */

/*
=================
CG_MapTorsoToWeaponFrame

=================
 */
static int CG_MapTorsoToWeaponFrame(clientInfo_t *ci, int frame) {

    // change weapon
    if (frame >= ci->animations[TORSO_DROP].firstFrame
            && frame < ci->animations[TORSO_DROP].firstFrame + 9) {
        return frame - ci->animations[TORSO_DROP].firstFrame + 6;
    }

    // stand attack
    if (frame >= ci->animations[TORSO_ATTACK].firstFrame
            && frame < ci->animations[TORSO_ATTACK].firstFrame + 6) {
        return 1 + frame - ci->animations[TORSO_ATTACK].firstFrame;
    }

    // stand attack 2
    if (frame >= ci->animations[TORSO_ATTACK2].firstFrame
            && frame < ci->animations[TORSO_ATTACK2].firstFrame + 6) {
        return 1 + frame - ci->animations[TORSO_ATTACK2].firstFrame;
    }

    return 0;
}

/*
==============
CG_CalculateWeaponPosition
==============
 */
static void CG_CalculateWeaponPosition(vec3_t origin, vec3_t angles) {
    float scale;
    int delta;
    float fracsin;

    VectorCopy(cg.refdef.vieworg, origin);
    VectorCopy(cg.refdefViewAngles, angles);

    // on odd legs, invert some angles
    if (cg.bobcycle & 1) {
        scale = -cg.xyspeed;
    } else {
        scale = cg.xyspeed;
    }

    // gun angles from bobbing
    angles[ROLL] += scale * cg.bobfracsin * 0.005;
    angles[YAW] += scale * cg.bobfracsin * 0.01;
    angles[PITCH] += cg.xyspeed * cg.bobfracsin * 0.005;

    // drop the weapon when landing
    delta = cg.time - cg.landTime;
    if (delta < LAND_DEFLECT_TIME) {
        origin[2] += cg.landChange * 0.25 * delta / LAND_DEFLECT_TIME;
    } else if (delta < LAND_DEFLECT_TIME + LAND_RETURN_TIME) {
        origin[2] += cg.landChange * 0.25 *
                (LAND_DEFLECT_TIME + LAND_RETURN_TIME - delta) / LAND_RETURN_TIME;
    }

#if 0
    // drop the weapon when stair climbing
    delta = cg.time - cg.stepTime;
    if (delta < STEP_TIME / 2) {
        origin[2] -= cg.stepChange * 0.25 * delta / (STEP_TIME / 2);
    } else if (delta < STEP_TIME) {
        origin[2] -= cg.stepChange * 0.25 * (STEP_TIME - delta) / (STEP_TIME / 2);
    }
#endif

    // idle drift
    scale = cg.xyspeed + 20;
    fracsin = sin(cg.time * 0.001);
    angles[ROLL] += scale * fracsin * 0.01;
    angles[YAW] += scale * fracsin * 0.01;
    angles[PITCH] += scale * fracsin * 0.01;
}

/*
===============
CG_LightningBolt

Origin will be the exact tag point, which is slightly
different than the muzzle point used for determining hits.
The cent should be the non-predicted cent if it is from the player,
so the endpoint will reflect the simulated strike (lagging the predicted
angle)
===============
 */
static void CG_LightningBolt(centity_t *cent, vec3_t origin) {
    trace_t trace;
    refEntity_t beam;
    vec3_t forward;
    vec3_t muzzlePoint, endPoint;

    return; /*

	memset( &beam, 0, sizeof( beam ) );

	// CPMA  "true" lightning
	if ((cent->currentState.number == cg.predictedPlayerState.clientNum) && (cg_trueLightning.value != 0)) {
		vec3_t angle;
		int i;

		for (i = 0; i < 3; i++) {
			float a = cent->lerpAngles[i] - cg.refdefViewAngles[i];
			if (a > 180) {
				a -= 360;
			}
			if (a < -180) {
				a += 360;
			}

			angle[i] = cg.refdefViewAngles[i] + a * (1.0 - cg_trueLightning.value);
			if (angle[i] < 0) {
				angle[i] += 360;
			}
			if (angle[i] > 360) {
				angle[i] -= 360;
			}
		}

		AngleVectors(angle, forward, NULL, NULL );
		VectorCopy(cent->lerpOrigin, muzzlePoint );
//		VectorCopy(cg.refdef.vieworg, muzzlePoint );
	} else {
		// !CPMA
		AngleVectors( cent->lerpAngles, forward, NULL, NULL );
		VectorCopy(cent->lerpOrigin, muzzlePoint );
	}

	// FIXME: crouch
	muzzlePoint[2] += DEFAULT_VIEWHEIGHT;

	VectorMA( muzzlePoint, 14, forward, muzzlePoint );

	// project forward by the lightning range
	VectorMA( muzzlePoint, LIGHTNING_RANGE, forward, endPoint );

	// see if it hit a wall
	CG_Trace( &trace, muzzlePoint, vec3_origin, vec3_origin, endPoint, 
		cent->currentState.number, MASK_SHOT );

	// this is the endpoint
	VectorCopy( trace.endpos, beam.oldorigin );

	// use the provided origin, even though it may be slightly
	// different than the muzzle origin
	VectorCopy( origin, beam.origin );

	beam.reType = RT_LIGHTNING;
	beam.customShader = cgs.media.lightningShader;
	trap_R_AddRefEntityToScene( &beam );

	// add the impact flare if it hit something
	if ( trace.fraction < 1.0 ) {
		vec3_t	angles;
		vec3_t	dir;

		VectorSubtract( beam.oldorigin, beam.origin, dir );
		VectorNormalize( dir );

		memset( &beam, 0, sizeof( beam ) );
		beam.hModel = cgs.media.lightningExplosionModel;

		VectorMA( trace.endpos, -16, dir, beam.origin );

		// make a random orientation
		angles[0] = rand() % 360;
		angles[1] = rand() % 360;
		angles[2] = rand() % 360;
		AnglesToAxis( angles, beam.axis );
		trap_R_AddRefEntityToScene( &beam );
	}*/
}
/*

static void CG_LightningBolt( centity_t *cent, vec3_t origin ) {
        trace_t		trace;
        refEntity_t		beam;
        vec3_t			forward;
        vec3_t			muzzlePoint, endPoint;

        if ( cent->currentState.weapon != WP_LIGHTNING ) {
                return;
        }

        memset( &beam, 0, sizeof( beam ) );

        // find muzzle point for this frame
        VectorCopy( cent->lerpOrigin, muzzlePoint );
        AngleVectors( cent->lerpAngles, forward, NULL, NULL );

        // FIXME: crouch
        muzzlePoint[2] += DEFAULT_VIEWHEIGHT;

        VectorMA( muzzlePoint, 14, forward, muzzlePoint );

        // project forward by the lightning range
        VectorMA( muzzlePoint, LIGHTNING_RANGE, forward, endPoint );

        // see if it hit a wall
        CG_Trace( &trace, muzzlePoint, vec3_origin, vec3_origin, endPoint,
                cent->currentState.number, MASK_SHOT );

        // this is the endpoint
        VectorCopy( trace.endpos, beam.oldorigin );

        // use the provided origin, even though it may be slightly
        // different than the muzzle origin
        VectorCopy( origin, beam.origin );

        beam.reType = RT_LIGHTNING;
        beam.customShader = cgs.media.lightningShader;
        trap_R_AddRefEntityToScene( &beam );

        // add the impact flare if it hit something
        if ( trace.fraction < 1.0 ) {
                vec3_t	angles;
                vec3_t	dir;

                VectorSubtract( beam.oldorigin, beam.origin, dir );
                VectorNormalize( dir );

                memset( &beam, 0, sizeof( beam ) );
                beam.hModel = cgs.media.lightningExplosionModel;

                VectorMA( trace.endpos, -16, dir, beam.origin );

                // make a random orientation
                angles[0] = rand() % 360;
                angles[1] = rand() % 360;
                angles[2] = rand() % 360;
                AnglesToAxis( angles, beam.axis );
                trap_R_AddRefEntityToScene( &beam );
        }
}
 */

/*
===============
CG_SpawnRailTrail

Origin will be the exact tag point, which is slightly
different than the muzzle point used for determining hits.
===============
 */
static void CG_SpawnRailTrail(centity_t *cent, vec3_t origin) {
    clientInfo_t *ci;

    if (!cent->pe.railgunFlash) {
        return;
    }
    cent->pe.railgunFlash = qtrue;
    ci = &cgs.clientinfo[ cent->currentState.clientNum ];
    CG_RailTrail(ci, origin, cent->pe.railgunImpact);
}


/*
======================
CG_MachinegunSpinAngle
======================
 */
#define		SPIN_SPEED	0//.9
#define		COAST_TIME	10//1000

static float CG_MachinegunSpinAngle(centity_t *cent) {
    int delta;
    float angle;
    float speed;

    delta = cg.time - cent->pe.barrelTime;
    if (cent->pe.barrelSpinning) {
        angle = cent->pe.barrelAngle + delta * SPIN_SPEED;
    } else {
        if (delta > COAST_TIME) {
            delta = COAST_TIME;
        }

        speed = 0.5 * (SPIN_SPEED + (float) (COAST_TIME - delta) / COAST_TIME);
        angle = cent->pe.barrelAngle + delta * speed;
    }

    if (cent->pe.barrelSpinning == !(cent->currentState.eFlags & EF_FIRING)) {
        cent->pe.barrelTime = cg.time;
        cent->pe.barrelAngle = AngleMod(angle);
        cent->pe.barrelSpinning = !!(cent->currentState.eFlags & EF_FIRING);
    }

    return angle;
}

/*
========================
CG_AddWeaponWithPowerups
========================
 */
static void CG_AddWeaponWithPowerups(refEntity_t *gun, int powerups) {
        trap_R_AddRefEntityToScene(gun);
}

/*
=============
CG_AddPlayerWeapon

Used for both the view weapon (ps is valid) and the world modelother character models (ps is NULL)
The main player will have this called for BOTH cases, so effects like light and
sound should only be done on the world model case.
=============
 */
void CG_AddPlayerWeapon(refEntity_t *parent, playerState_t *ps, centity_t *cent, int team) {
    refEntity_t gun;
    refEntity_t barrel;
    refEntity_t flash;
    vec3_t angles;
    weapon_t weaponNum;
    weaponInfo_t *weapon;
    centity_t *nonPredictedCent;
    orientation_t lerped;

    weaponNum = cent->currentState.weapon;

    CG_RegisterWeapon(weaponNum);
    weapon = &cg_weapons[weaponNum];

    // add the weapon
    memset(&gun, 0, sizeof ( gun));
    VectorCopy(parent->lightingOrigin, gun.lightingOrigin);
    gun.shadowPlane = parent->shadowPlane;
    gun.renderfx = parent->renderfx;

    // set custom shading for railgun refire rate
    if (ps) {
        int weapon;
        weapon = cg.predictedPlayerState.weapon;
        if ((weapon == WP_BARRETT || weapon == WP_ACR)
                && cg.predictedPlayerState.weaponstate == WEAPON_FIRING) {
            float f;

            f = (float) cg.predictedPlayerState.weaponTime / 1500;
            gun.shaderRGBA[1] = 0;
            gun.shaderRGBA[0] =
                    gun.shaderRGBA[2] = 255 * (1.0 - f);
        } else {
            gun.shaderRGBA[0] = 255;
            gun.shaderRGBA[1] = 255;
            gun.shaderRGBA[2] = 255;
            gun.shaderRGBA[3] = 255;
        }
    }

    gun.hModel = weapon->weaponModel;
    if (!gun.hModel) {
        return;
    }

    if (!ps) {
        // add weapon ready sound
        cent->pe.lightningFiring = qfalse;
        if ((cent->currentState.eFlags & EF_FIRING) && weapon->firingSound) {
            // lightning gun and guantlet make a different sound when fire is held down
            trap_S_AddLoopingSound(cent->currentState.number, cent->lerpOrigin, vec3_origin, weapon->firingSound);
            cent->pe.lightningFiring = qtrue;
        } else if (weapon->readySound) {
            trap_S_AddLoopingSound(cent->currentState.number, cent->lerpOrigin, vec3_origin, weapon->readySound);
        }
    }

    trap_R_LerpTag(&lerped, parent->hModel, parent->oldframe, parent->frame,
            1.0 - parent->backlerp, "tag_weapon");
    VectorCopy(parent->origin, gun.origin);

    VectorMA(gun.origin, lerped.origin[0], parent->axis[0], gun.origin);

    // Make weapon appear left-handed for 2 and centered for 3
    if (ps && cg_drawGun.integer == 2)
        VectorMA(gun.origin, -lerped.origin[1], parent->axis[1], gun.origin);
    else if (!ps || cg_drawGun.integer != 3)
        VectorMA(gun.origin, lerped.origin[1], parent->axis[1], gun.origin);

    VectorMA(gun.origin, lerped.origin[2], parent->axis[2], gun.origin);

    MatrixMultiply(lerped.axis, ((refEntity_t *) parent)->axis, gun.axis);
    gun.backlerp = parent->backlerp;

    CG_AddWeaponWithPowerups(&gun, cent->currentState.powerups);

    // add the spinning barrel
    if (weapon->barrelModel) {
        memset(&barrel, 0, sizeof ( barrel));
        VectorCopy(parent->lightingOrigin, barrel.lightingOrigin);
        barrel.shadowPlane = parent->shadowPlane;
        barrel.renderfx = parent->renderfx;

        barrel.hModel = weapon->barrelModel;
        angles[YAW] = 0;
        angles[PITCH] = 0;
        angles[ROLL] = CG_MachinegunSpinAngle(cent);
        AnglesToAxis(angles, barrel.axis);

        CG_PositionRotatedEntityOnTag(&barrel, &gun, weapon->weaponModel, "tag_barrel");

        CG_AddWeaponWithPowerups(&barrel, cent->currentState.powerups);
    }

    // make sure we aren't looking at cg.predictedPlayerEntity for LG
    nonPredictedCent = &cg_entities[cent->currentState.clientNum];

    // if the index of the nonPredictedCent is not the same as the clientNum
    // then this is a fake player (like on teh single player podiums), so
    // go ahead and use the cent
    if ((nonPredictedCent - cg_entities) != cent->currentState.clientNum) {
        nonPredictedCent = cent;
    }
    // impulse flash
    if (cg.time - cent->muzzleFlashTime > MUZZLE_FLASH_TIME && !cent->pe.railgunFlash) {
        return;
    }

    memset(&flash, 0, sizeof ( flash));
    VectorCopy(parent->lightingOrigin, flash.lightingOrigin);
    flash.shadowPlane = parent->shadowPlane;
    flash.renderfx = parent->renderfx;

    flash.hModel = weapon->flashModel;
    if (!flash.hModel) {
        return;
    }
    angles[YAW] = 0;
    angles[PITCH] = 0;
    angles[ROLL] = crandom() * 10;
    AnglesToAxis(angles, flash.axis);

    CG_PositionRotatedEntityOnTag(&flash, &gun, weapon->weaponModel, "tag_flash");
    trap_R_AddRefEntityToScene(&flash);

    if (ps || cg.renderingThirdPerson ||
            cent->currentState.number != cg.predictedPlayerState.clientNum) {
        // add lightning bolt
        CG_LightningBolt(nonPredictedCent, flash.origin);

        // add rail trail
        CG_SpawnRailTrail(cent, flash.origin);

        if (weapon->flashDlightColor[0] || weapon->flashDlightColor[1] || weapon->flashDlightColor[2]) {
            trap_R_AddLightToScene(flash.origin, 300 + (rand()&31), weapon->flashDlightColor[0],
                    weapon->flashDlightColor[1], weapon->flashDlightColor[2]);
        }
    }
}

/*
==============
CG_AddViewWeapon

Add the weapon, and flash for the player's view
==============
 */
void CG_AddViewWeapon(playerState_t *ps) {
    refEntity_t hand;
    centity_t *cent;
    clientInfo_t *ci;
    float fovOffset;
    vec3_t angles;
    weaponInfo_t *weapon;
    float x, y, z;

    if (ps->persistant[PERS_TEAM] == TEAM_SPECTATOR) {
        return;
    }

    if (ps->pm_type == PM_INTERMISSION) {
        return;
    }

    // no gun if in third person view or a camera is active
    //if ( cg.renderingThirdPerson || cg.cameraMode) {
    if (cg.renderingThirdPerson) {
        return;
    }


    // allow the gun to be completely removed
    if (!cg_drawGun.integer) {
        vec3_t origin;

        if (cg.predictedPlayerState.eFlags & EF_FIRING) {
            // special hack for lightning gun...
            VectorCopy(cg.refdef.vieworg, origin);
            VectorMA(origin, -8, cg.refdef.viewaxis[2], origin);
            CG_LightningBolt(&cg_entities[ps->clientNum], origin);
        }
        return;
    }

    // don't draw if testing a gun model
    if (cg.testGun) {
        return;
    }

    // drop gun lower at higher fov
    if (cg_fov.integer > 90) {
        fovOffset = -0.2 * (cg_fov.integer - 90);
    } else {
        fovOffset = 0;
    }

    cent = &cg.predictedPlayerEntity; // &cg_entities[cg.snap->ps.clientNum];
    CG_RegisterWeapon(ps->weapon);
    weapon = &cg_weapons[ ps->weapon ];

    memset(&hand, 0, sizeof (hand));

    // set up gun position
    CG_CalculateWeaponPosition(hand.origin, angles);

    x = cg_gun_x.value;
    y = cg_gun_y.value;
    z = cg_gun_z.value;
    if (ps->weapon == WP_KNIFE) {
        z = 3;
        y = -4.5f;
        x = 12;
    }
    VectorMA(hand.origin, x, cg.refdef.viewaxis[0], hand.origin);
    VectorMA(hand.origin, y, cg.refdef.viewaxis[1], hand.origin);
    VectorMA(hand.origin, (z + fovOffset), cg.refdef.viewaxis[2], hand.origin);

    AnglesToAxis(angles, hand.axis);

    // map torso animations to weapon animations
    if (cg_gun_frame.integer) {
        // development tool
        hand.frame = hand.oldframe = cg_gun_frame.integer;
        hand.backlerp = 0;
    } else {
        // get clientinfo for animation map
        ci = &cgs.clientinfo[ cent->currentState.clientNum ];
        hand.frame = CG_MapTorsoToWeaponFrame(ci, cent->pe.torso.frame);
        hand.oldframe = CG_MapTorsoToWeaponFrame(ci, cent->pe.torso.oldFrame);
        hand.backlerp = cent->pe.torso.backlerp;
    }

    hand.hModel = weapon->handsModel;
    hand.renderfx = RF_DEPTHHACK | RF_FIRST_PERSON | RF_MINLIGHT;

    // add everything onto the hand
    CG_AddPlayerWeapon(&hand, ps, &cg.predictedPlayerEntity, ps->persistant[PERS_TEAM]);
}

/*
==============================================================================

WEAPON SELECTION

==============================================================================
 */

/*
===================
CG_DrawWeaponSelect
===================
 */
void CG_DrawWeaponSelect(void) {
    int i;
    int bits;
    int count;
    int x, y, w;
    char *name;
    float *color;

    // don't display if dead
    if (cg.predictedPlayerState.stats[STAT_HEALTH] <= 0) {
        return;
    }

    color = CG_FadeColor(cg.weaponSelectTime, WEAPON_SELECT_TIME);
    if (!color) {
        return;
    }
    trap_R_SetColor(color);

    // showing weapon select clears pickup item display, but not the blend blob
    cg.itemPickupTime = 0;

    // count the number of weapons owned
    bits = cg.snap->ps.stats[ STAT_WEAPONS ];
    count = 0;
    for (i = 1; i < MAX_WEAPONS; i++) {
        if (bits & (1 << i)) {
            count++;
        }
    }

    x = 320 - count * 20;
    y = 380;

    for (i = 1; i < MAX_WEAPONS; i++) {
        if (!(bits & (1 << i))) {
            continue;
        }

        CG_RegisterWeapon(i);

        // draw weapon icon
        CG_DrawPic(x, y, 32, 32, cg_weapons[i].weaponIcon);

        // draw selection marker
        if (i == cg.weaponSelect) {
            CG_DrawPic(x - 4, y - 4, 40, 40, cgs.media.selectShader);
        }

        // no ammo cross on top
        /*if ( !cg.snap->ps.ammo[ i ] ) {
                CG_DrawPic( x, y, 32, 32, cgs.media.noammoShader );
        }*/

        x += 40;
    }

    // draw the selected name
    if (cg_weapons[ cg.weaponSelect ].item) {
        name = cg_weapons[ cg.weaponSelect ].item->pickup_name;
        if (name) {
            w = CG_DrawStrlen(name) * BIGCHAR_WIDTH;
            x = (SCREEN_WIDTH - w) / 2;
            CG_DrawBigStringColor(x, y - 22, name, color);
        }
    }

    trap_R_SetColor(NULL);
}

/*
===============
CG_WeaponSelectable
===============
 */
static qboolean CG_WeaponSelectable(int i) {
    /*if ( !cg.snap->ps.ammo[i] ) {
            return qfalse;
    }*/
    if (!(cg.snap->ps.stats[ STAT_WEAPONS ] & (1 << i))) {
        return qfalse;
    }

    return qtrue;
}

/*
===============
CG_NextWeapon_f
===============
 */
void CG_NextWeapon_f(void) {
    int i;
    int original;

    if (!cg.snap) {
        return;
    }
    if (cg.snap->ps.pm_flags & PMF_FOLLOW) {
        return;
    }

    cg.weaponSelectTime = cg.time;
    original = cg.weaponSelect;

    for (i = 0; i < MAX_WEAPONS; i++) {
        cg.weaponSelect++;
        if (cg.weaponSelect == MAX_WEAPONS) {
            cg.weaponSelect = 0;
        }
        /*if ( cg.weaponSelect == WP_GAUNTLET ) {
                continue;		// never cycle to gauntlet
        }*/
        if (CG_WeaponSelectable(cg.weaponSelect)) {
            break;
        }
    }
    if (i == MAX_WEAPONS) {
        cg.weaponSelect = original;
    }
}

/*
===============
CG_PrevWeapon_f
===============
 */
void CG_PrevWeapon_f(void) {
    int i;
    int original;

    if (!cg.snap) {
        return;
    }
    if (cg.snap->ps.pm_flags & PMF_FOLLOW) {
        return;
    }

    cg.weaponSelectTime = cg.time;
    original = cg.weaponSelect;

    for (i = 0; i < MAX_WEAPONS; i++) {
        cg.weaponSelect--;
        if (cg.weaponSelect == -1) {
            cg.weaponSelect = MAX_WEAPONS - 1;
        }
        /*if ( cg.weaponSelect == WP_GAUNTLET ) {
                continue;		// never cycle to gauntlet
        }*/
        if (CG_WeaponSelectable(cg.weaponSelect)) {
            break;
        }
    }
    if (i == MAX_WEAPONS) {
        cg.weaponSelect = original;
    }
}

/*
===============
CG_Weapon_f
===============
 */
void CG_Weapon_f(void) {
    int num;

    if (!cg.snap) {
        return;
    }
    if (cg.snap->ps.pm_flags & PMF_FOLLOW) {
        return;
    }

    num = atoi(CG_Argv(1));

    if (num < 1 || num > MAX_WEAPONS - 1) {
        return;
    }

    cg.weaponSelectTime = cg.time;

    if (!(cg.snap->ps.stats[STAT_WEAPONS] & (1 << num))) {
        return; // don't have the weapon
    }

    cg.weaponSelect = num;
}

/*
===================
CG_OutOfAmmoChange

The current weapon has just run out of ammo
===================
 */
void CG_OutOfAmmoChange(void) {
    /*int i;

    cg.weaponSelectTime = cg.time;

    for ( i = MAX_WEAPONS-1 ; i > 0 ; i-- ) {
            if ( CG_WeaponSelectable( i ) ) {
                    cg.weaponSelect = i;
                    break;
            }
    }*/
}



/*
===================================================================================================

WEAPON EVENTS

===================================================================================================
 */

/*
================
CG_FireWeapon

Caused by an EV_FIRE_WEAPON event
================
 */

void CG_FireWeapon(centity_t *cent) {
    entityState_t *ent;
    int c;
    weaponInfo_t *weap;

    ent = &cent->currentState;
    if (ent->weapon == WP_NONE) {
        return;
    }
    if (ent->weapon >= WP_NUM_WEAPONS) {
        CG_Error("CG_FireWeapon: ent->weapon >= WP_NUM_WEAPONS");
        return;
    }
    weap = &cg_weapons[ ent->weapon ];

    // mark the entity as muzzle flashing, so when it is added it will
    // append the flash to the weapon model
    cent->muzzleFlashTime = cg.time;

    // play a sound
    for (c = 0; c < 4; c++) {
        if (!weap->flashSound[c]) {
            break;
        }
    }
    if (c > 0) {
        c = rand() % c;
        if (weap->flashSound[c]) {
            trap_S_StartSound(NULL, ent->number, CHAN_WEAPON, weap->flashSound[c]);
        }
    }

    // do brass ejection
    if (weap->ejectBrassFunc && cg_brassTime.integer > 0) {
        weap->ejectBrassFunc(cent);
    }
}

/*
=================
CG_MissileHitWall

Caused by an EV_MISSILE_MISS event, or directly by local bullet tracing
=================
 */
void CG_MissileHitWall(int weapon, int clientNum, vec3_t origin, vec3_t dir, impactSound_t soundType) {
    qhandle_t mod;
    qhandle_t mark;
    qhandle_t shader;
    sfxHandle_t sfx;
    float radius;
    float light;
    vec3_t lightColor;
    localEntity_t *le;
    int r;
    int msec;
    qboolean alphaFade;
    qboolean isSprite;
    int duration, offset;

    mark = 0;
    radius = 32;
    sfx = 0;
    mod = 0;
    shader = 0;
    light = 0;
    lightColor[0] = 1;
    lightColor[1] = 1;
    lightColor[2] = 0;

    // set defaults
    isSprite = qfalse;
    duration = 600;

    switch (weapon) {
        default:
            // RAIN WEAPONS
        case WP_BARRETT:
            mod = cgs.media.bulletFlashModel;
            shader = cgs.media.bulletExplosionShader;
            sfx = cgs.media.sfx_plasmaexp;
            mark = cgs.media.bulletMarkShader;
            radius = 8;
            break;
        case WP_INTERVENTION:
            mod = cgs.media.bulletFlashModel;
            shader = cgs.media.bulletExplosionShader;
            sfx = cgs.media.sfx_plasmaexp;
            mark = cgs.media.bulletMarkShader;
            radius = 8;
            break;
        case WP_HE:
            mod = cgs.media.dishFlashModel;
            shader = cgs.media.grenadeExplosionShader;
            sfx = cgs.media.sfx_rockexp;
            mark = cgs.media.burnMarkShader;
            radius = 64;
            light = 300;
            isSprite = qtrue;
            break;
        case WP_ACR:
            mod = cgs.media.bulletFlashModel;
            shader = cgs.media.bulletExplosionShader;
            mark = cgs.media.bulletMarkShader;
            r = rand() & 3;
            if (r == 0) {
                sfx = cgs.media.sfx_ric1;
            } else if (r == 1) {
                sfx = cgs.media.sfx_ric2;
            } else {
                sfx = cgs.media.sfx_ric3;
            }
            radius = 2;
            break;
        case WP_WALTHER:
            mod = cgs.media.bulletFlashModel;
            shader = cgs.media.bulletExplosionShader;
            mark = cgs.media.bulletMarkShader;
            r = rand() & 3;
            if (r == 0) {
                sfx = cgs.media.sfx_ric1;
            } else if (r == 1) {
                sfx = cgs.media.sfx_ric2;
            } else {
                sfx = cgs.media.sfx_ric3;
            }
            radius = 2;
            break;
        case WP_NUKE:
            mod = cgs.media.dishFlashModelBig;
            shader = cgs.media.grenadeExplosionShader;
            sfx = cgs.media.sfx_rockexp;
            mark = cgs.media.burnMarkShader;
            radius = 512;
            light = 3000;
            isSprite = qtrue;
            lightColor[0] = 1;
            lightColor[1] = 0.4;
            lightColor[2] = 0.3;
            break;
        case WP_BOMB:
            mod = cgs.media.dishFlashModel;
            shader = cgs.media.grenadeExplosionShader;
            sfx = cgs.media.sfx_bombexp;
            mark = cgs.media.burnMarkShader;
            radius = 256;
            light = 2000;
            isSprite = qtrue;
            lightColor[0] = 1;
            lightColor[1] = 0.4;
            lightColor[2] = 0.3;
            break;
        case -1 :
            mod = cgs.media.bulletFlashModel;
            shader = cgs.media.bulletExplosionShader;
            mark = cgs.media.bulletMarkShader;
            r = rand() & 3;
            if (r == 0) {
                sfx = cgs.media.sfx_ric1;
            } else if (r == 1) {
                sfx = cgs.media.sfx_ric2;
            } else {
                sfx = cgs.media.sfx_ric3;
            }
            radius = 2;
            break;
        case -2 :
            mod = cgs.media.bulletFlashModel;
            shader = cgs.media.bulletExplosionShader;
            sfx = cgs.media.sfx_ric1;
            mark = cgs.media.bulletMarkShader;
            radius = 8;
            break;
    }

    if (sfx) {
        trap_S_StartSound(origin, ENTITYNUM_WORLD, CHAN_AUTO, sfx);
    }

    //
    // create the explosion
    //
    if (mod) {
        if (weapon != WP_NUKE) {
            if (weapon == WP_BOMB) {
                int i = 0;
                vec3_t up;
                while (i < 128) {
                    msec = 5000+crandom()*1000;
                    if (msec < 0) {
                        msec *= -1;
                    } else if (msec == 0) {
                        msec = 1000;
                    }
                    up[0] = crandom()*10;
                    up[1] = crandom()*10;
                    up[2] = crandom()*7.5f;
                    CG_MakeExplosion(origin, up, cgs.media.dishFlashModel, cgs.media.grenadeSmokeShader, msec, qtrue);
                    i++;
                }
            }
            le = CG_MakeExplosion(origin, dir, mod, shader, duration, isSprite);
        } else {
            le = CG_AllocLocalEntity();
            offset = rand() & 63;
            msec = 1000+crandom()*1000;
            if (msec < 0) {
                msec *= -1;
            } else if (msec == 0) {
                msec = 1000;
            }
            le->leType = LE_SPRITE_EXPLOSION;
            le->refEntity.hModel = mod;
            le->refEntity.customShader = shader;
            le->startTime = cg.time - offset;
            le->endTime = le->startTime + msec;
            le->refEntity.shaderTime = le->startTime / 1000.0f;
            VectorCopy(origin, le->refEntity.origin);
            VectorCopy(origin, le->refEntity.oldorigin);
            le->color[0] = le->color[1] = le->color[2] = 1.0;
        }
        le->light = light;
        VectorCopy(lightColor, le->lightColor);
    }

    //
    // impact mark
    //
    alphaFade = (mark == cgs.media.energyMarkShader); // plasma fades alpha, all others fade color
    /*if ( weapon == WP_RAILGUN ) {
            float	*color;

            // colorize with client color
            color = cgs.clientinfo[clientNum].color2;
            CG_ImpactMark( mark, origin, dir, random()*360, color[0],color[1], color[2],1, alphaFade, radius, qfalse );
    } else {*/
    CG_ImpactMark(mark, origin, dir, random()*360, 1, 1, 1, 1, alphaFade, radius, qfalse);
    //}

    CG_ExplosionParticles(weapon, origin);

}

/*
=================
CG_MissileHitPlayer
=================
 */
void CG_MissileHitPlayer(int weapon, vec3_t origin, vec3_t dir, int entityNum) {
    CG_Bleed(origin, entityNum);

    // some weapons will make an explosion with the blood, while
    // others will just make the blood
    switch (weapon) {
        case WP_HE:
            /*case WP_ROCKET_LAUNCHER:
                    CG_MissileHitWall( weapon, 0, origin, dir, IMPACTSOUND_FLESH );
                    break;*/
        default:
            break;
    }

    CG_ExplosionParticles(weapon, origin);
}



/*
============================================================================

SHOTGUN TRACING

============================================================================
 */

/*
================
CG_ShotgunPellet
================
 */
static void CG_ShotgunPellet(vec3_t start, vec3_t end, int skipNum) {
    trace_t tr;
    int sourceContentType, destContentType;

    CG_Trace(&tr, start, NULL, NULL, end, skipNum, MASK_SHOT);

    sourceContentType = trap_CM_PointContents(start, 0);
    destContentType = trap_CM_PointContents(tr.endpos, 0);

    // FIXME: should probably move this cruft into CG_BubbleTrail
    if (sourceContentType == destContentType) {
        if (sourceContentType & CONTENTS_WATER) {
            CG_BubbleTrail(start, tr.endpos, 32);
        }
    } else if (sourceContentType & CONTENTS_WATER) {
        trace_t trace;

        trap_CM_BoxTrace(&trace, end, start, NULL, NULL, 0, CONTENTS_WATER);
        CG_BubbleTrail(start, trace.endpos, 32);
    } else if (destContentType & CONTENTS_WATER) {
        trace_t trace;

        trap_CM_BoxTrace(&trace, start, end, NULL, NULL, 0, CONTENTS_WATER);
        CG_BubbleTrail(tr.endpos, trace.endpos, 32);
    }

    if (tr.surfaceFlags & SURF_NOIMPACT) {
        return;
    }

    if (cg_entities[tr.entityNum].currentState.eType == ET_PLAYER) {
        //CG_MissileHitPlayer( WP_SHOTGUN, tr.endpos, tr.plane.normal, tr.entityNum );
    } else {
        if (tr.surfaceFlags & SURF_NOIMPACT) {
            // SURF_NOIMPACT will not make a flame puff or a mark
            return;
        }
        if (tr.surfaceFlags & SURF_METALSTEPS) {
            //CG_MissileHitWall( WP_SHOTGUN, 0, tr.endpos, tr.plane.normal, IMPACTSOUND_METAL );
        } else {
            //CG_MissileHitWall( WP_SHOTGUN, 0, tr.endpos, tr.plane.normal, IMPACTSOUND_DEFAULT );
        }
    }
}

/*
================
CG_ShotgunPattern

Perform the same traces the server did to locate the
hit splashes
================
 */
static void CG_ShotgunPattern(vec3_t origin, vec3_t origin2, int seed, int otherEntNum) {
    int i;
    float r, u;
    vec3_t end;
    vec3_t forward, right, up;

    // derive the right and up vectors from the forward vector, because
    // the client won't have any other information
    VectorNormalize2(origin2, forward);
    PerpendicularVector(right, forward);
    CrossProduct(forward, right, up);

    // generate the "random" spread pattern
    for (i = 0; i < DEFAULT_SHOTGUN_COUNT; i++) {
        r = Q_crandom(&seed) * DEFAULT_SHOTGUN_SPREAD * 16;
        u = Q_crandom(&seed) * DEFAULT_SHOTGUN_SPREAD * 16;
        VectorMA(origin, 8192 * 16, forward, end);
        VectorMA(end, r, right, end);
        VectorMA(end, u, up, end);

        CG_ShotgunPellet(origin, end, otherEntNum);
    }
}

/*
==============
CG_ShotgunFire
==============
 */
void CG_ShotgunFire(entityState_t *es) {
    vec3_t v;
    int contents;

    VectorSubtract(es->origin2, es->pos.trBase, v);
    VectorNormalize(v);
    VectorScale(v, 32, v);
    VectorAdd(es->pos.trBase, v, v);
    if (cgs.glconfig.hardwareType != GLHW_RAGEPRO) {
        // ragepro can't alpha fade, so don't even bother with smoke
        vec3_t up;

        contents = trap_CM_PointContents(es->pos.trBase, 0);
        if (!(contents & CONTENTS_WATER)) {
            VectorSet(up, 0, 0, 8);
            CG_SmokePuff(v, up, 32, 1, 1, 1, 0.33f, 900, cg.time, 0, LEF_PUFF_DONT_SCALE, cgs.media.shotgunSmokePuffShader);
        }
    }
    CG_ShotgunPattern(es->pos.trBase, es->origin2, es->eventParm, es->otherEntityNum);
}

/*
============================================================================

BULLETS

============================================================================
 */

/*
===============
CG_Tracer
===============
 */
void CG_Tracer(vec3_t source, vec3_t dest) {
    vec3_t forward, right;
    polyVert_t verts[4];
    vec3_t line;
    float len, begin, end;
    vec3_t start, finish;
    vec3_t midpoint;

    // tracer
    VectorSubtract(dest, source, forward);
    len = VectorNormalize(forward);

    // start at least a little ways from the muzzle
    if (len < 100) {
        return;
    }
    begin = 50 + random() * (len - 60);
    end = begin + cg_tracerLength.value;
    if (end > len) {
        end = len;
    }
    VectorMA(source, begin, forward, start);
    VectorMA(source, end, forward, finish);

    line[0] = DotProduct(forward, cg.refdef.viewaxis[1]);
    line[1] = DotProduct(forward, cg.refdef.viewaxis[2]);

    VectorScale(cg.refdef.viewaxis[1], line[1], right);
    VectorMA(right, -line[0], cg.refdef.viewaxis[2], right);
    VectorNormalize(right);

    VectorMA(finish, cg_tracerWidth.value, right, verts[0].xyz);
    verts[0].st[0] = 0;
    verts[0].st[1] = 1;
    verts[0].modulate[0] = 255;
    verts[0].modulate[1] = 255;
    verts[0].modulate[2] = 255;
    verts[0].modulate[3] = 255;

    VectorMA(finish, -cg_tracerWidth.value, right, verts[1].xyz);
    verts[1].st[0] = 1;
    verts[1].st[1] = 0;
    verts[1].modulate[0] = 255;
    verts[1].modulate[1] = 255;
    verts[1].modulate[2] = 255;
    verts[1].modulate[3] = 255;

    VectorMA(start, -cg_tracerWidth.value, right, verts[2].xyz);
    verts[2].st[0] = 1;
    verts[2].st[1] = 1;
    verts[2].modulate[0] = 255;
    verts[2].modulate[1] = 255;
    verts[2].modulate[2] = 255;
    verts[2].modulate[3] = 255;

    VectorMA(start, cg_tracerWidth.value, right, verts[3].xyz);
    verts[3].st[0] = 0;
    verts[3].st[1] = 0;
    verts[3].modulate[0] = 255;
    verts[3].modulate[1] = 255;
    verts[3].modulate[2] = 255;
    verts[3].modulate[3] = 255;

    trap_R_AddPolyToScene(cgs.media.tracerShader, 4, verts);

    midpoint[0] = (start[0] + finish[0]) * 0.5;
    midpoint[1] = (start[1] + finish[1]) * 0.5;
    midpoint[2] = (start[2] + finish[2]) * 0.5;

    // add the tracer sound
    trap_S_StartSound(midpoint, ENTITYNUM_WORLD, CHAN_AUTO, cgs.media.tracerSound);

}

/*
======================
CG_CalcMuzzlePoint
======================
 */
static qboolean CG_CalcMuzzlePoint(int entityNum, vec3_t muzzle) {
    vec3_t forward;
    centity_t *cent;
    int anim;

    if (entityNum == cg.snap->ps.clientNum) {
        VectorCopy(cg.snap->ps.origin, muzzle);
        muzzle[2] += cg.snap->ps.viewheight;
        AngleVectors(cg.snap->ps.viewangles, forward, NULL, NULL);
        VectorMA(muzzle, 14, forward, muzzle);
        return qtrue;
    }

    cent = &cg_entities[entityNum];
    if (!cent->currentValid) {
        return qfalse;
    }

    VectorCopy(cent->currentState.pos.trBase, muzzle);

    AngleVectors(cent->currentState.apos.trBase, forward, NULL, NULL);
    anim = cent->currentState.legsAnim & ~ANIM_TOGGLEBIT;
    if (anim == LEGS_WALKCR || anim == LEGS_IDLECR) {
        muzzle[2] += CROUCH_VIEWHEIGHT;
    } else {
        muzzle[2] += DEFAULT_VIEWHEIGHT;
    }

    VectorMA(muzzle, 14, forward, muzzle);

    return qtrue;

}

/*
======================
CG_Bullet

Renders bullet effects.
======================
 */
void CG_Bullet(vec3_t end, int sourceEntityNum, vec3_t normal, qboolean flesh, int fleshEntityNum) {
    trace_t trace;
    int sourceContentType, destContentType;
    vec3_t start;

    // if the shooter is currently valid, calc a source point and possibly
    // do trail effects
    if (sourceEntityNum >= 0 && cg_tracerChance.value > 0) {
        if (CG_CalcMuzzlePoint(sourceEntityNum, start)) {
            sourceContentType = trap_CM_PointContents(start, 0);
            destContentType = trap_CM_PointContents(end, 0);

            // do a complete bubble trail if necessary
            if ((sourceContentType == destContentType) && (sourceContentType & CONTENTS_WATER)) {
                CG_BubbleTrail(start, end, 32);
            }// bubble trail from water into air
            else if ((sourceContentType & CONTENTS_WATER)) {
                trap_CM_BoxTrace(&trace, end, start, NULL, NULL, 0, CONTENTS_WATER);
                CG_BubbleTrail(start, trace.endpos, 32);
            }// bubble trail from air into water
            else if ((destContentType & CONTENTS_WATER)) {
                trap_CM_BoxTrace(&trace, start, end, NULL, NULL, 0, CONTENTS_WATER);
                CG_BubbleTrail(trace.endpos, end, 32);
            }

            // draw a tracer
            if (random() < cg_tracerChance.value) {
                CG_Tracer(start, end);
            }
        }
    }

    // impact splash and mark
    if (flesh) {
        CG_Bleed(end, fleshEntityNum);
    } else {
        CG_MissileHitWall(-1, 0, end, normal, IMPACTSOUND_DEFAULT);
    }

}
