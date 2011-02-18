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
// cg_effects.c -- these functions generate localentities, usually as a result
// of event processing

#include "cg_local.h"

/*
==================
CG_BubbleTrail

Bullets shot underwater
==================
 */
void CG_BubbleTrail(vec3_t start, vec3_t end, float spacing) {
    vec3_t move;
    vec3_t vec;
    float len;
    int i;

    if (cg_noProjectileTrail.integer) {
        return;
    }

    VectorCopy(start, move);
    VectorSubtract(end, start, vec);
    len = VectorNormalize(vec);

    // advance a random amount first
    i = rand() % (int) spacing;
    VectorMA(move, i, vec, move);

    VectorScale(vec, spacing, vec);

    for (; i < len; i += spacing) {
        localEntity_t *le;
        refEntity_t *re;

        le = CG_AllocLocalEntity();
        le->leFlags = LEF_PUFF_DONT_SCALE;
        le->leType = LE_MOVE_SCALE_FADE;
        le->startTime = cg.time;
        le->endTime = cg.time + 1000 + random() * 250;
        le->lifeRate = 1.0 / (le->endTime - le->startTime);

        re = &le->refEntity;
        re->shaderTime = cg.time / 1000.0f;

        re->reType = RT_SPRITE;
        re->rotation = 0;
        re->radius = 3;
        re->customShader = cgs.media.waterBubbleShader;
        re->shaderRGBA[0] = 0xff;
        re->shaderRGBA[1] = 0xff;
        re->shaderRGBA[2] = 0xff;
        re->shaderRGBA[3] = 0xff;

        le->color[3] = 1.0;

        le->pos.trType = TR_LINEAR;
        le->pos.trTime = cg.time;
        VectorCopy(move, le->pos.trBase);
        le->pos.trDelta[0] = crandom()*5;
        le->pos.trDelta[1] = crandom()*5;
        le->pos.trDelta[2] = crandom()*5 + 6;

        VectorAdd(move, vec, move);
    }
}

/*
=====================
CG_SmokePuff

Adds a smoke puff or blood trail localEntity.
=====================
 */
localEntity_t *CG_SmokePuff(const vec3_t p, const vec3_t vel,
        float radius,
        float r, float g, float b, float a,
        float duration,
        int startTime,
        int fadeInTime,
        int leFlags,
        qhandle_t hShader) {
    static int seed = 0x92;
    localEntity_t *le;
    refEntity_t *re;
    //	int fadeInTime = startTime + duration / 2;

    le = CG_AllocLocalEntity();
    le->leFlags = leFlags;
    le->radius = radius;

    re = &le->refEntity;
    re->rotation = Q_random(&seed) * 360;
    re->radius = radius;
    re->shaderTime = startTime / 1000.0f;

    le->leType = LE_MOVE_SCALE_FADE;
    le->startTime = startTime;
    le->fadeInTime = fadeInTime;
    le->endTime = startTime + duration;
    if (fadeInTime > startTime) {
        le->lifeRate = 1.0 / (le->endTime - le->fadeInTime);
    } else {
        le->lifeRate = 1.0 / (le->endTime - le->startTime);
    }
    le->color[0] = r;
    le->color[1] = g;
    le->color[2] = b;
    le->color[3] = a;


    le->pos.trType = TR_LINEAR;
    le->pos.trTime = startTime;
    VectorCopy(vel, le->pos.trDelta);
    VectorCopy(p, le->pos.trBase);

    VectorCopy(p, re->origin);
    re->customShader = hShader;

    // rage pro can't alpha fade, so use a different shader
    if (cgs.glconfig.hardwareType == GLHW_RAGEPRO) {
        re->customShader = cgs.media.smokePuffRageProShader;
        re->shaderRGBA[0] = 0xff;
        re->shaderRGBA[1] = 0xff;
        re->shaderRGBA[2] = 0xff;
        re->shaderRGBA[3] = 0xff;
    } else {
        re->shaderRGBA[0] = le->color[0] * 0xff;
        re->shaderRGBA[1] = le->color[1] * 0xff;
        re->shaderRGBA[2] = le->color[2] * 0xff;
        re->shaderRGBA[3] = 0xff;
    }

    re->reType = RT_SPRITE;
    re->radius = le->radius;

    return le;
}

/*
==================
CG_SpawnEffect

Player teleporting in or out
==================
 */
void CG_SpawnEffect(vec3_t org) {
    localEntity_t *le;
    refEntity_t *re;

    le = CG_AllocLocalEntity();
    le->leFlags = 0;
    le->leType = LE_FADE_RGB;
    le->startTime = cg.time;
    le->endTime = cg.time + 500;
    le->lifeRate = 1.0 / (le->endTime - le->startTime);

    le->color[0] = le->color[1] = le->color[2] = le->color[3] = 1.0;

    re = &le->refEntity;

    re->reType = RT_MODEL;
    re->shaderTime = cg.time / 1000.0f;

    re->customShader = cgs.media.teleportEffectShader;
    re->hModel = cgs.media.teleportEffectModel;
    AxisClear(re->axis);

    VectorCopy(org, re->origin);
    re->origin[2] -= 24;
}

/*
==================
CG_ScorePlum
==================
 */
void CG_ScorePlum(int client, vec3_t org, int score) {
    localEntity_t *le;
    refEntity_t *re;
    vec3_t angles;
    static vec3_t lastPos;

    // only visualize for the client that scored
    if (client != cg.predictedPlayerState.clientNum || cg_scorePlum.integer == 0) {
        return;
    }

    le = CG_AllocLocalEntity();
    le->leFlags = 0;
    le->leType = LE_SCOREPLUM;
    le->startTime = cg.time;
    le->endTime = cg.time + 4000;
    le->lifeRate = 1.0 / (le->endTime - le->startTime);


    le->color[0] = le->color[1] = le->color[2] = le->color[3] = 1.0;
    le->radius = score;

    VectorCopy(org, le->pos.trBase);
    if (org[2] >= lastPos[2] - 20 && org[2] <= lastPos[2] + 20) {
        le->pos.trBase[2] -= 20;
    }

    //CG_Printf( "Plum origin %i %i %i -- %i\n", (int)org[0], (int)org[1], (int)org[2], (int)Distance(org, lastPos));
    VectorCopy(org, lastPos);


    re = &le->refEntity;

    re->reType = RT_SPRITE;
    re->radius = 16;

    VectorClear(angles);
    AnglesToAxis(angles, re->axis);
}

/*
====================
CG_MakeExplosion
====================
 */
localEntity_t *CG_MakeExplosion(vec3_t origin, vec3_t dir,
        qhandle_t hModel, qhandle_t shader,
        int msec, qboolean isSprite) {
    float ang;
    localEntity_t *ex;
    int offset;
    vec3_t tmpVec, newOrigin;

    if (msec <= 0) {
        CG_Error("CG_MakeExplosion: msec = %i", msec);
    }

    // skew the time a bit so they aren't all in sync
    offset = rand() & 63;

    ex = CG_AllocLocalEntity();
    if (isSprite) {
        ex->leType = LE_SPRITE_EXPLOSION;

        // randomly rotate sprite orientation
        ex->refEntity.rotation = rand() % 360;
        VectorScale(dir, 16, tmpVec);
        VectorAdd(tmpVec, origin, newOrigin);
    } else {
        ex->leType = LE_EXPLOSION;
        VectorCopy(origin, newOrigin);

        // set axis with random rotate
        if (!dir) {
            AxisClear(ex->refEntity.axis);
        } else {
            ang = rand() % 360;
            VectorCopy(dir, ex->refEntity.axis[0]);
            RotateAroundDirection(ex->refEntity.axis, ang);
        }
    }

    ex->startTime = cg.time - offset;
    ex->endTime = ex->startTime + msec;

    // bias the time so all shader effects start correctly
    ex->refEntity.shaderTime = ex->startTime / 1000.0f;

    ex->refEntity.hModel = hModel;
    ex->refEntity.customShader = shader;

    // set origin
    VectorCopy(newOrigin, ex->refEntity.origin);
    VectorCopy(newOrigin, ex->refEntity.oldorigin);

    ex->color[0] = ex->color[1] = ex->color[2] = 1.0;

    return ex;
}

/*
====================
CG_MakeNukeSmoke
====================
 */
localEntity_t *CG_MakeNukeSmoke(vec3_t origin, vec3_t dir, int msec) {
    float ang;
    localEntity_t *ex;
    int offset;
    vec3_t tmpVec, newOrigin;

    if (msec <= 0) {
        CG_Error("CG_MakeExplosion: msec = %i", msec);
    }

    // skew the time a bit so they aren't all in sync
    offset = rand() & 63;

    ex = CG_AllocLocalEntity();
    ex->leType = LE_SPRITE_EXPLOSION;

    // randomly rotate sprite orientation
    ex->refEntity.rotation = rand() % 360;
    VectorScale(dir, 16, tmpVec);
    VectorAdd(tmpVec, origin, newOrigin);

    ex->startTime = cg.time - offset;
    ex->endTime = ex->startTime + msec;

    // bias the time so all shader effects start correctly
    ex->refEntity.shaderTime = ex->startTime / 1000.0f;

    ex->refEntity.hModel = cgs.media.dishFlashModel;
    ex->refEntity.customShader = cgs.media.nukeSmokeShader;

    // set origin
    VectorCopy(newOrigin, ex->refEntity.origin);
    VectorCopy(newOrigin, ex->refEntity.oldorigin);

    ex->color[0] = ex->color[1] = ex->color[2] = 1.0;

    return ex;
}

void CG_Nuke(vec3_t origin, int stage) {
    int number, index, light;
    float stagefactor;
    vec3_t up, lightColor;
    localEntity_t *le, *nuke;
    refEntity_t *re;
    int offset, msec;
    vec3_t test;

    if (stage == 1) {
        int i;
        nuke = CG_AllocLocalEntity();
        re = &nuke->refEntity;
        test[0] = nuke->angles.trBase[0];
        test[1] = nuke->angles.trBase[1];
        test[2] = nuke->angles.trBase[2];
        AnglesToAxis(test, re->axis);
        VectorScale(re->axis[0], 50, re->axis[0]);
        VectorScale(re->axis[1], 50, re->axis[1]);
        VectorScale(re->axis[2], 50, re->axis[2]);
        re->nonNormalizedAxes = qtrue;
        
        re->renderfx = RF_MINLIGHT;

        nuke->leType = LE_FRAGMENT;
        nuke->startTime = cg.time;
        nuke->endTime = nuke->startTime + 60000;

        VectorCopy(origin, re->origin);
        re->hModel = cgs.media.mod_nuke;

        nuke->pos.trType = TR_GRAVITY;
        VectorCopy(origin, nuke->pos.trBase);
        VectorCopy(origin, nuke->pos.trDelta);
        nuke->pos.trTime = cg.time;

        nuke->leBounceSoundType = LEBS_NONE;
        nuke->leMarkType = LEMT_NONE;
    }

    number = 128;
    stagefactor = 1.0f;
    light = 20000;
    lightColor[0] = 1;
    lightColor[1] = 0.4;
    lightColor[2] = 0.3;

    switch (stage) {
        case 1:
            number = 512;
            stagefactor = 3.0f;
            break;
        case 2:
            number = 256;
            origin[2] += 250;
            stagefactor = 2.0f;
            break;
        case 3:
            origin[2] += 500;
            stagefactor = 1.5f;
            break;
        case 4:
            origin[2] += 750;
            break;
        case 5:
            origin[2] += 1000;
            break;
        case 6:
            origin[2] += 1250;
            number = 512;
            stagefactor = 2.0f;
            break;
        case 7:
            origin[2] += 1500;
            number = 512;
            stagefactor = 5.0f;
            break;
        default:
            break;
    }

    for (index = 0; index < number; index++) {
        int msec;
        localEntity_t *ent;
        up[0] = crandom()*10 * stagefactor;
        up[1] = crandom()*10 * stagefactor;
        if (stage != 7) {
            up[2] = crandom()*7.5f * stagefactor;
        } else {
            up[2] = crandom()*7.5f;
        }
        msec = 50000 + crandom()*50000;
        if (msec < 0) {
            msec *= -1;
        } else if (msec == 0) {
            msec = 50000;
        }
        // smoke dat shit up
        //ent = CG_MakeNukeSmoke(origin, up, msec);
    }
    for (index = 0; index < 3; index++) {
        le = CG_AllocLocalEntity();
        offset = rand() & 63;
        msec = 1000 + crandom()*1000;
        if (msec < 0) {
            msec *= -1;
        } else if (msec == 0) {
            msec = 1000;
        }
        le->leType = LE_SPRITE_EXPLOSION;
        le->refEntity.hModel = cgs.media.dishFlashModel;
        le->refEntity.customShader = cgs.media.nukeSmokeShader;
        le->startTime = cg.time - offset;
        le->endTime = le->startTime + msec;
        le->refEntity.shaderTime = le->startTime / 1000.0f;
        VectorCopy(origin, le->refEntity.origin);
        VectorCopy(origin, le->refEntity.oldorigin);
        le->color[0] = le->color[1] = le->color[2] = 1.0;
        le->light = light / stage;
        if (le->light < 5000) {
            le->light = 5000;
        }
        VectorCopy(lightColor, le->lightColor);
    }
}

/*
=================
CG_Bleed

This is the spurt of blood when a character gets hit
=================
 */
void CG_Bleed(vec3_t origin, int entityNum) {
    localEntity_t *ex;

    if (!cg_blood.integer) {
        return;
    }

    ex = CG_AllocLocalEntity();
    ex->leType = LE_EXPLOSION;

    ex->startTime = cg.time;
    ex->endTime = ex->startTime + 500;

    VectorCopy(origin, ex->refEntity.origin);
    ex->refEntity.reType = RT_SPRITE;
    ex->refEntity.rotation = rand() % 360;
    ex->refEntity.radius = 24;

    ex->refEntity.customShader = cgs.media.bloodExplosionShader;

    // don't show player's own blood in view
    /*if ( entityNum == cg.snap->ps.clientNum ) {
            ex->refEntity.renderfx |= RF_THIRD_PERSON;
    }*/
}

/*
==================
CG_LaunchGib
==================
 */
void CG_LaunchGib(vec3_t origin, vec3_t velocity, qhandle_t hModel) {
    localEntity_t *le;
    refEntity_t *re;

    le = CG_AllocLocalEntity();
    re = &le->refEntity;

    le->leType = LE_FRAGMENT;
    le->startTime = cg.time;
    le->endTime = le->startTime + 5000 + random() * 3000;

    VectorCopy(origin, re->origin);
    AxisCopy(axisDefault, re->axis);
    re->hModel = hModel;

    le->pos.trType = TR_GRAVITY;
    VectorCopy(origin, le->pos.trBase);
    VectorCopy(velocity, le->pos.trDelta);
    le->pos.trTime = cg.time;

    le->bounceFactor = 0.3f;

    le->leBounceSoundType = LEBS_BLOOD;
    le->leMarkType = LEMT_BLOOD;
}

/*
===================
CG_GibPlayer

Generated a bunch of gibs launching out from the bodies location
===================
 */
#define	GIB_VELOCITY	200
#define	GIB_JUMP		350

void CG_GibPlayer(vec3_t playerOrigin) {
    vec3_t origin, velocity;

    if (!cg_blood.integer) {
        return;
    }

    VectorCopy(playerOrigin, origin);
    velocity[0] = crandom() * GIB_VELOCITY;
    velocity[1] = crandom() * GIB_VELOCITY;
    velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
    if (rand() & 1) {
        CG_LaunchGib(origin, velocity, cgs.media.gibSkull);
    } else {
        CG_LaunchGib(origin, velocity, cgs.media.gibBrain);
    }

    // allow gibs to be turned off for speed
    if (!cg_gibs.integer) {
        return;
    }

    VectorCopy(playerOrigin, origin);
    velocity[0] = crandom() * GIB_VELOCITY;
    velocity[1] = crandom() * GIB_VELOCITY;
    velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
    CG_LaunchGib(origin, velocity, cgs.media.gibAbdomen);

    VectorCopy(playerOrigin, origin);
    velocity[0] = crandom() * GIB_VELOCITY;
    velocity[1] = crandom() * GIB_VELOCITY;
    velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
    CG_LaunchGib(origin, velocity, cgs.media.gibArm);

    VectorCopy(playerOrigin, origin);
    velocity[0] = crandom() * GIB_VELOCITY;
    velocity[1] = crandom() * GIB_VELOCITY;
    velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
    CG_LaunchGib(origin, velocity, cgs.media.gibChest);

    VectorCopy(playerOrigin, origin);
    velocity[0] = crandom() * GIB_VELOCITY;
    velocity[1] = crandom() * GIB_VELOCITY;
    velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
    CG_LaunchGib(origin, velocity, cgs.media.gibFist);

    VectorCopy(playerOrigin, origin);
    velocity[0] = crandom() * GIB_VELOCITY;
    velocity[1] = crandom() * GIB_VELOCITY;
    velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
    CG_LaunchGib(origin, velocity, cgs.media.gibFoot);

    VectorCopy(playerOrigin, origin);
    velocity[0] = crandom() * GIB_VELOCITY;
    velocity[1] = crandom() * GIB_VELOCITY;
    velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
    CG_LaunchGib(origin, velocity, cgs.media.gibForearm);

    VectorCopy(playerOrigin, origin);
    velocity[0] = crandom() * GIB_VELOCITY;
    velocity[1] = crandom() * GIB_VELOCITY;
    velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
    CG_LaunchGib(origin, velocity, cgs.media.gibIntestine);

    VectorCopy(playerOrigin, origin);
    velocity[0] = crandom() * GIB_VELOCITY;
    velocity[1] = crandom() * GIB_VELOCITY;
    velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
    CG_LaunchGib(origin, velocity, cgs.media.gibLeg);

    VectorCopy(playerOrigin, origin);
    velocity[0] = crandom() * GIB_VELOCITY;
    velocity[1] = crandom() * GIB_VELOCITY;
    velocity[2] = GIB_JUMP + crandom() * GIB_VELOCITY;
    CG_LaunchGib(origin, velocity, cgs.media.gibLeg);
}

/*
==================
CG_LaunchGib
==================
 */
void CG_LaunchExplode(vec3_t origin, vec3_t velocity, qhandle_t hModel) {
    localEntity_t *le;
    refEntity_t *re;

    le = CG_AllocLocalEntity();
    re = &le->refEntity;

    le->leType = LE_FRAGMENT;
    le->startTime = cg.time;
    le->endTime = le->startTime + 10000 + random() * 6000;

    VectorCopy(origin, re->origin);
    AxisCopy(axisDefault, re->axis);
    re->hModel = hModel;

    le->pos.trType = TR_GRAVITY;
    VectorCopy(origin, le->pos.trBase);
    VectorCopy(velocity, le->pos.trDelta);
    le->pos.trTime = cg.time;

    le->bounceFactor = 0.1f;

    le->leBounceSoundType = LEBS_BRASS;
    le->leMarkType = LEMT_NONE;
}

#define	EXP_VELOCITY	300
#define	EXP_JUMP		450

/*
===================
CG_GibPlayer

Generated a bunch of gibs launching out from the bodies location
===================
 */
void CG_BigExplode(vec3_t playerOrigin) {
    vec3_t origin, velocity;

    if (!cg_blood.integer) {
        return;
    }

    VectorCopy(playerOrigin, origin);
    velocity[0] = crandom() * EXP_VELOCITY;
    velocity[1] = crandom() * EXP_VELOCITY;
    velocity[2] = EXP_JUMP + crandom() * EXP_VELOCITY;
    CG_LaunchExplode(origin, velocity, cgs.media.smoke2);

    VectorCopy(playerOrigin, origin);
    velocity[0] = crandom() * EXP_VELOCITY;
    velocity[1] = crandom() * EXP_VELOCITY;
    velocity[2] = EXP_JUMP + crandom() * EXP_VELOCITY;
    CG_LaunchExplode(origin, velocity, cgs.media.smoke2);

    VectorCopy(playerOrigin, origin);
    velocity[0] = crandom() * EXP_VELOCITY * 1.5;
    velocity[1] = crandom() * EXP_VELOCITY * 1.5;
    velocity[2] = EXP_JUMP + crandom() * EXP_VELOCITY;
    CG_LaunchExplode(origin, velocity, cgs.media.smoke2);

    VectorCopy(playerOrigin, origin);
    velocity[0] = crandom() * EXP_VELOCITY * 2.0;
    velocity[1] = crandom() * EXP_VELOCITY * 2.0;
    velocity[2] = EXP_JUMP + crandom() * EXP_VELOCITY;
    CG_LaunchExplode(origin, velocity, cgs.media.smoke2);

    VectorCopy(playerOrigin, origin);
    velocity[0] = crandom() * EXP_VELOCITY * 2.5;
    velocity[1] = crandom() * EXP_VELOCITY * 2.5;
    velocity[2] = EXP_JUMP + crandom() * EXP_VELOCITY;
    CG_LaunchExplode(origin, velocity, cgs.media.smoke2);
}

/*
 ==================
 CG_LaunchGlass
 ==================
 */
void CG_LaunchGlass(vec3_t origin, vec3_t velocity, qhandle_t hModel) {
    localEntity_t *le;
    refEntity_t *re;

    le = CG_AllocLocalEntity();
    re = &le->refEntity;

    le->leType = LE_FRAGMENT;
    le->startTime = cg.time;
    le->endTime = le->startTime + 30000 + random() * 3000;

    VectorCopy(origin, re->origin);
    AxisCopy(axisDefault, re->axis);
    re->hModel = hModel;

    le->pos.trType = TR_GRAVITY;
    VectorCopy(origin, le->pos.trBase);
    VectorCopy(velocity, le->pos.trDelta);
    le->pos.trTime = cg.time;

    le->bounceFactor = 0.3;

    le->leFlags = LEF_TUMBLE;
    le->leBounceSoundType = LEBS_BRASS;
    le->leMarkType = LEMT_NONE;
}

/*
===================
CG_BreakGlass

Generated a bunch of glass shards launching out from the glass location
===================
 */
#define	GLASS_VELOCITY	175
#define	GLASS_JUMP	125
#define GLASS_SHARDS    16

void CG_BreakGlass(vec3_t playerOrigin) {
    vec3_t origin, velocity;
    int value;
    int count;
    int states[] = {1, 2, 3};
    int numstates = sizeof (states) / sizeof (states[0]);

    count = GLASS_SHARDS;

    // Countdown "count" so this will subtract 1 from the "count"
    // X many times. X being the "count" value
    while (count--) {
        // Generate the random number every count so every shard is a
        // of the three. If this is placed above it only gets a random
        // number every time a piece of glass is broken.
        value = states[rand() % numstates];
        VectorCopy(playerOrigin, origin);
        velocity[0] = crandom() * GLASS_VELOCITY;
        velocity[1] = crandom() * GLASS_VELOCITY;
        velocity[2] = GLASS_JUMP + crandom() * GLASS_VELOCITY;
        switch (value) {
            case 1:
                // If our random number was 1, generate the 1st shard piece
                CG_LaunchGlass(origin, velocity, cgs.media.glass01);
                break;
            case 2:
                CG_LaunchGlass(origin, velocity, cgs.media.glass02);
                break;
            case 3:
                CG_LaunchGlass(origin, velocity, cgs.media.glass03);
                break;
        }
    }
}


/*
===================
CG_BreakFlesh

Generated a bunch of flesh gibs launching out from the location
===================
 */
#define	FLESH_VELOCITY	100
#define	FLESH_JUMP	50
#define FLESH_SHARDS    8

void CG_BreakFlesh(vec3_t playerOrigin) {
    vec3_t origin, velocity;
    int value;
    int count;
    int states[] = {1, 2, 3};
    int numstates = sizeof (states) / sizeof (states[0]);

    count = FLESH_SHARDS;

    // Countdown "count" so this will subtract 1 from the "count"
    // X many times. X being the "count" value
    while (count--) {
        // Generate the random number every count so every shard is a
        // of the three. If this is placed above it only gets a random
        // number every time a piece of glass is broken.
        value = states[rand() % numstates];
        VectorCopy(playerOrigin, origin);
        velocity[0] = crandom() * FLESH_VELOCITY;
        velocity[1] = crandom() * FLESH_VELOCITY;
        velocity[2] = FLESH_JUMP + crandom() * FLESH_VELOCITY;
        switch (value) {
            case 1:
                CG_LaunchGlass(origin, velocity, cgs.media.gibArm);
                break;
            case 2:
                CG_LaunchGlass(origin, velocity, cgs.media.gibLeg);
                break;
            case 3:
                CG_LaunchGlass(origin, velocity, cgs.media.gibFoot);
                break;
        }
    }
}



/*
===================
CG_BreakWood

Generated a bunch of flesh gibs launching out from the location
===================
 */
#define	WOOD_VELOCITY	100
#define	WOOD_JUMP	50
#define WOOD_SHARDS     16

void CG_BreakWood(vec3_t playerOrigin) {
    vec3_t origin, velocity;
    int value;
    int count;
    int states[] = {1, 2, 3};
    int numstates = sizeof (states) / sizeof (states[0]);

    count = WOOD_SHARDS;

    // Countdown "count" so this will subtract 1 from the "count"
    // X many times. X being the "count" value
    while (count--) {
        // Generate the random number every count so every shard is a
        // of the three. If this is placed above it only gets a random
        // number every time a piece of glass is broken.
        value = states[rand() % numstates];
        VectorCopy(playerOrigin, origin);
        velocity[0] = crandom() * WOOD_VELOCITY;
        velocity[1] = crandom() * WOOD_VELOCITY;
        velocity[2] = WOOD_JUMP + crandom() * WOOD_VELOCITY;
        switch (value) {
            case 1:
                CG_LaunchGlass(origin, velocity, cgs.media.gibArm);
                break;
            case 2:
                CG_LaunchGlass(origin, velocity, cgs.media.gibLeg);
                break;
            case 3:
                CG_LaunchGlass(origin, velocity, cgs.media.gibFoot);
                break;
        }
    }
}



/*
===================
CG_BreakMetal

Generated a bunch of flesh gibs launching out from the location
===================
 */
#define	METAL_VELOCITY	100
#define	METAL_JUMP	50
#define METAL_SHARDS    8

void CG_BreakMetal(vec3_t playerOrigin) {
    vec3_t origin, velocity;
    int value;
    int count;
    int states[] = {1, 2, 3};
    int numstates = sizeof (states) / sizeof (states[0]);

    count = METAL_SHARDS;

    // Countdown "count" so this will subtract 1 from the "count"
    // X many times. X being the "count" value
    while (count--) {
        // Generate the random number every count so every shard is a
        // of the three. If this is placed above it only gets a random
        // number every time a piece of glass is broken.
        value = states[rand() % numstates];
        VectorCopy(playerOrigin, origin);
        velocity[0] = crandom() * METAL_VELOCITY;
        velocity[1] = crandom() * METAL_VELOCITY;
        velocity[2] = METAL_JUMP + crandom() * METAL_VELOCITY;
        switch (value) {
            case 1:
                CG_LaunchGlass(origin, velocity, cgs.media.gibArm);
                break;
            case 2:
                CG_LaunchGlass(origin, velocity, cgs.media.gibLeg);
                break;
            case 3:
                CG_LaunchGlass(origin, velocity, cgs.media.gibFoot);
                break;
        }
    }
}



/*
===================
CG_BreakStone

Generated a bunch of flesh gibs launching out from the location
===================
 */
#define	STONE_VELOCITY	100
#define	STONE_JUMP	50
#define STONE_SHARDS    16

void CG_BreakStone(vec3_t playerOrigin) {
    vec3_t origin, velocity;
    int value;
    int count;
    int states[] = {1, 2, 3};
    int numstates = sizeof (states) / sizeof (states[0]);

    count = STONE_SHARDS;

    // Countdown "count" so this will subtract 1 from the "count"
    // X many times. X being the "count" value
    while (count--) {
        // Generate the random number every count so every shard is a
        // of the three. If this is placed above it only gets a random
        // number every time a piece of glass is broken.
        value = states[rand() % numstates];
        VectorCopy(playerOrigin, origin);
        velocity[0] = crandom() * STONE_VELOCITY;
        velocity[1] = crandom() * STONE_VELOCITY;
        velocity[2] = STONE_JUMP + crandom() * STONE_VELOCITY;
        switch (value) {
            case 1:
                CG_LaunchGlass(origin, velocity, cgs.media.gibArm);
                break;
            case 2:
                CG_LaunchGlass(origin, velocity, cgs.media.gibLeg);
                break;
            case 3:
                CG_LaunchGlass(origin, velocity, cgs.media.gibFoot);
                break;
        }
    }
}
