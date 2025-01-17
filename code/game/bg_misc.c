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
// bg_misc.c -- both games misc functions, all completely stateless

#include "../qcommon/q_shared.h"
#include "bg_public.h"

#undef MISSIONPACK

/*QUAKED item_***** ( 0 0 0 ) (-16 -16 -16) (16 16 16) suspended
 DO NOT USE THIS CLASS, IT JUST HOLDS GENERAL INFORMATION.
 The suspended flag will allow items to hang in the air, otherwise they are dropped to the next surface.

 If an item is the target of another entity, it will not spawn in until fired.

 An item fires all of its targets when it is picked up.  If the toucher can't carry it, the targets won't be fired.

 "notfree" if set to 1, don't spawn in free for all games
 "notteam" if set to 1, don't spawn in team games
 "notsingle" if set to 1, don't spawn in single player games
 "wait"	override the default wait before respawning.  -1 = never respawn automatically, which can be used with targeted spawning.
 "random" random number of plus or minus seconds varied from the respawn time
 "count" override quantity or duration on most items.
 */

gitem_t bg_itemlist[] = { { NULL, NULL, { NULL, NULL, NULL, NULL }, /* icon */NULL, /* pickup */NULL, 0, 0, 0,
/* precache */"",
/* sounds */"" }, // leave index 0 alone

    //
    // ARMOR
    //

    /*QUAKED item_armor_shard (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "item_armor_shard", "sound/misc/ar1_pkup.wav", { "models/powerups/armor/shard.md3", "models/powerups/armor/shard_sphere.md3", NULL, NULL },
    /* icon */"icons/iconr_shard",
    /* pickup */"Armor Shard", 5, IT_ARMOR, 0,
    /* precache */"",
    /* sounds */"" },

    /*QUAKED item_armor_combat (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "item_armor_combat", "sound/misc/ar2_pkup.wav", { "models/powerups/armor/armor_yel.md3", NULL, NULL, NULL },
    /* icon */"icons/iconr_yellow",
    /* pickup */"Armor", 50, IT_ARMOR, 0,
    /* precache */"",
    /* sounds */"" },

    /*QUAKED item_armor_body (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "item_armor_body", "sound/misc/ar2_pkup.wav", { "models/powerups/armor/armor_red.md3", NULL, NULL, NULL },
    /* icon */"icons/iconr_red",
    /* pickup */"Heavy Armor", 100, IT_ARMOR, 0,
    /* precache */"",
    /* sounds */"" },

    //
    // health
    //
    /*QUAKED item_health_small (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "item_health_small", "sound/items/s_health.wav", { "models/powerups/health/small_cross.md3", "models/powerups/health/small_sphere.md3", NULL, NULL },
    /* icon */"icons/iconh_green",
    /* pickup */"5 Health", 5, IT_HEALTH, 0,
    /* precache */"",
    /* sounds */"" },

    /*QUAKED item_health (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "item_health", "sound/items/n_health.wav", { "models/powerups/health/medium_cross.md3", "models/powerups/health/medium_sphere.md3", NULL, NULL },
    /* icon */"icons/iconh_yellow",
    /* pickup */"25 Health", 25, IT_HEALTH, 0,
    /* precache */"",
    /* sounds */"" },

    /*QUAKED item_health_large (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "item_health_large",
        "sound/items/l_health.wav",
        { "models/powerups/health/large_cross.md3", "models/powerups/health/large_sphere.md3", NULL, NULL },
        "icons/iconh_red", /* icon */
        "50 Health", /* pickup */
        50,
        IT_HEALTH,
        0,
        "",/* precache */
        "" /* sounds */
    },

    /*QUAKED item_health_mega (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "item_health_mega", // classname
        "sound/items/m_health.wav",
        { "models/powerups/health/mega_cross.md3", "models/powerups/health/mega_sphere.md3", NULL, NULL },
        "icons/iconh_mega",
        "Mega Health",
        100,
        IT_HEALTH,
        0,/* pickup */
        "", // precache
        "" // sounds
    },

    /*QUAKED item_bandage (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "item_bandage", "sound/items/m_health.wav", { "models/powerups/health/mega_cross.md3", NULL, NULL, NULL }, "icons/iconh_mega", // icon
        "Bandage", // text
        1,
        IT_HEALTH,
        0,
        "", // precache
        "" // sounds
    },

    //
    // WEAPONS
    //

    /*QUAKED weapon_barrett (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "weapon_barrett", "sound/misc/w_pkup.wav", { "models/weapons2/railgun/railgun.md3", NULL, NULL, NULL },
    /* icon */"icons/iconw_railgun",
    /* pickup */"Barrett M82A1", 10, IT_WEAPON, WP_BARRETT,
    /* precache */"",
    /* sounds */"" },

    /*QUAKED weapon_intervention (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "weapon_intervention", "sound/misc/w_pkup.wav", { "models/weapons/intervention/intervention.md3", NULL, NULL, NULL },
    /* icon */"icons/iconw_railgun",
    /* pickup */"M200 Intervention", 7, IT_WEAPON, WP_INTERVENTION,
    /* precache */"",
    /* sounds */"" },

    /*QUAKED weapon_knife (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "weapon_knife", "sound/misc/w_pkup.wav", { "models/weapons/kbar/kbar.md3", NULL, NULL, NULL },
    /* icon */"icons/iconw_gauntlet",
    /* pickup */"K-Bar", -1, IT_WEAPON, WP_KNIFE,
    /* precache */"",
    /* sounds */"" },

    /*QUAKED weapon_hands (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "weapon_hands", "sound/misc/w_pkup.wav", { "models/weapons2/gauntlet/gauntlet.md3", NULL, NULL, NULL },
    /* icon */"icons/iconw_gauntlet",
    /* pickup */"Hands", -1, IT_WEAPON, WP_HANDS,
    /* precache */"",
    /* sounds */"" },

    /*QUAKED weapon_injector (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "weapon_injector", "sound/misc/w_pkup.wav", { "models/weapons2/gauntlet/gauntlet.md3", NULL, NULL, NULL },
    /* icon */"icons/iconw_gauntlet",
    /* pickup */"Injector", 0, IT_WEAPON, WP_INJECTOR,
    /* precache */"",
    /* sounds */"" },

    /*QUAKED weapon_crossbow (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "weapon_crossbow", // classname
        "sound/misc/w_pkup.wav", // pickup sound
        { "models/weapons/crossbow/crossbow.md3", NULL, NULL, NULL }, // models
        "icons/iconw_railgun", // icon
        "Crossbow", // name
        3, // count
        IT_WEAPON, // type
        WP_CROSSBOW, // weapon
        "", // precache
        "" // sounds
    },

    /*QUAKED weapon_acr (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "weapon_acr", // classname
        "sound/misc/w_pkup.wav",
        { "models/weapons/acr/acr.md3", NULL, NULL, NULL },
        /* icon */"icons/iconw_machinegun",
        /* pickup */"Remington ACR",
        30,
        IT_WEAPON,
        WP_ACR,
        /* precache */"",
        /* sounds */"" },

    /*QUAKED weapon_he (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "weapon_he", // classname
        "sound/misc/w_pkup.wav",
        { "models/weapons2/grenadel/grenadel.md3", NULL, NULL, NULL },
        /* icon */"icons/iconw_grenade",
        /* pickup */"HE Grenade",
        2,
        IT_WEAPON,
        WP_HE,
        /* precache */"",
        /* sounds */"sound/weapons/grenade/hgrenb1a.wav sound/weapons/grenade/hgrenb2a.wav" },

    /*QUAKED weapon_walther (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "weapon_walther", "sound/misc/w_pkup.wav", { "models/weapons/p22/p22.md3", NULL, NULL, NULL },
    /* icon */"icons/iconw_gauntlet",
    /* pickup */"Walther P22", 10, IT_WEAPON, WP_WALTHER,
    /* precache */"",
    /* sounds */"" },

    /*QUAKED weapon_bomb (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "weapon_bomb", "sound/misc/w_pkup.wav",
    //{ "models/weapons2/grenadel/grenadel.md3",
        { "models/weapons/c4/c4.md3", NULL, NULL, NULL },
        /* icon */"icons/iconw_grenade",
        /* pickup */"C4",
        1,
        IT_WEAPON,
        WP_BOMB,
        /* precache */"",
        /* sounds */"sound/weapons/grenade/hgrenb1a.wav sound/weapons/grenade/hgrenb2a.wav" },

    /*QUAKED weapon_nuke (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "weapon_nuke", "sound/misc/w_pkup.wav", { "models/weapons2/rocketl/rocketl.md3", NULL, NULL, NULL }, "icons/iconw_rocket", /* icon */
    "Nuke", /* pickup */
    1, IT_WEAPON, WP_NUKE, "", /* precache */
    "", /* sounds */
    },

    /*QUAKED weapon_snowboard (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    { "weapon_snowboard", "sound/misc/w_pkup.wav", { "models/weapons2/rocketl/rocketl.md3", NULL, NULL, NULL }, "icons/iconw_rocket", /* icon */
    "Snowboard", /* pickup */
    -1, IT_WEAPON, WP_SNOWBOARD, "", /* precache */
    "", /* sounds */
    },

    // end of list marker
    { NULL } };

int bg_numItems = sizeof(bg_itemlist) / sizeof(bg_itemlist[0]) - 1;

/*
 ==============
 BG_FindItemForPowerup
 ==============
 */
gitem_t *BG_FindItemForPowerup(powerup_t pw) {
  int i;

  for (i = 0; i < bg_numItems; i++) {
    if ((bg_itemlist[i].giType == IT_POWERUP || bg_itemlist[i].giType == IT_TEAM || bg_itemlist[i].giType == IT_PERSISTANT_POWERUP) && bg_itemlist[i].giTag
        == pw) {
      return &bg_itemlist[i];
    }
  }

  return NULL;
}

/*
 ==============
 BG_FindItemForHoldable
 ==============
 */
gitem_t *BG_FindItemForHoldable(holdable_t pw) {
  int i;

  for (i = 0; i < bg_numItems; i++) {
    if (bg_itemlist[i].giType == IT_HOLDABLE && bg_itemlist[i].giTag == pw) {
      return &bg_itemlist[i];
    }
  }

  Com_Error(ERR_DROP, "HoldableItem not found");

  return NULL;
}

/*
 ===============
 BG_FindItemForWeapon

 ===============
 */
gitem_t *BG_FindItemForWeapon(weapon_t weapon) {
  gitem_t *it;

  for (it = bg_itemlist + 1; it->classname; it++) {
    if (it->giType == IT_WEAPON && it->giTag == weapon) {
      return it;
    }
  }

  Com_Error(ERR_DROP, "Couldn't find item for weapon %i", weapon);
  return NULL;
}

/*
 ===============
 BG_FindItem

 ===============
 */
gitem_t *BG_FindItem(const char *pickupName) {
  gitem_t *it;

  for (it = bg_itemlist + 1; it->classname; it++) {
    if (!Q_stricmp(it->pickup_name, pickupName))
      return it;
  }

  return NULL;
}

/*
 ============
 BG_PlayerTouchesItem

 Items can be picked up without actually touching their physical bounds to make
 grabbing them easier
 ============
 */
qboolean BG_PlayerTouchesItem(playerState_t *ps, entityState_t *item, int atTime) {
  vec3_t origin;

  BG_EvaluateTrajectory(&item->pos, atTime, origin);

  // we are ignoring ducked differences here
  if (ps->origin[0] - origin[0] > 44 || ps->origin[0] - origin[0] < -50 || ps->origin[1] - origin[1] > 36 || ps->origin[1] - origin[1] < -36 || ps->origin[2]
      - origin[2] > 36 || ps->origin[2] - origin[2] < -36) {
    return qfalse;
  }

  return qtrue;
}

/*
 ================
 BG_CanItemBeGrabbed

 Returns false if the item should not be picked up.
 This needs to be the same for client side prediction and server use.
 ================
 */
qboolean BG_CanItemBeGrabbed(int gametype, const entityState_t *ent, const playerState_t *ps) {
  gitem_t *item;

  if (ent->modelindex < 1 || ent->modelindex >= bg_numItems) {
    Com_Error(ERR_DROP, "BG_CanItemBeGrabbed: index out of range");
  }

  item = &bg_itemlist[ent->modelindex];

  switch (item->giType) {
    case IT_WEAPON:
      return qtrue; // weapons are always picked up

    case IT_AMMO:
      if (ps->ammo[item->giTag] >= 200) {
        return qfalse; // can't hold any more
      }
      return qtrue;

    case IT_ARMOR:
      if (ps->stats[STAT_ARMOR] >= ps->stats[STAT_MAX_HEALTH] * 2) {
        return qfalse;
      }
      return qtrue;

    case IT_HEALTH:
      return qtrue;

    case IT_POWERUP:
      return qtrue; // powerups are always picked up

    case IT_TEAM: // team items, such as flags
      return qfalse;

    case IT_HOLDABLE:
      // can only hold one item at a time
      if (ps->stats[STAT_HOLDABLE_ITEM]) {
        return qfalse;
      }
      return qtrue;

    case IT_BAD:
      Com_Error(ERR_DROP, "BG_CanItemBeGrabbed: IT_BAD");
    default:
#ifndef Q3_VM
#ifndef NDEBUG
      Com_Printf("BG_CanItemBeGrabbed: unknown enum %d\n", item->giType);
#endif
#endif
      break;
  }

  return qfalse;
}

//======================================================================

/*
 ================
 BG_EvaluateTrajectory

 ================
 */
void BG_EvaluateTrajectory(const trajectory_t *tr, int atTime, vec3_t result) {
  float deltaTime;
  float phase;

  switch (tr->trType) {
    case TR_STATIONARY:
    case TR_INTERPOLATE:
      VectorCopy(tr->trBase, result);
      break;
    case TR_LINEAR:
      deltaTime = (atTime - tr->trTime) * 0.001; // milliseconds to seconds
      VectorMA(tr->trBase, deltaTime, tr->trDelta, result);
      break;
    case TR_SINE:
      deltaTime = (atTime - tr->trTime) / (float) tr->trDuration;
      phase = sin(deltaTime * M_PI * 2);
      VectorMA(tr->trBase, phase, tr->trDelta, result);
      break;
    case TR_LINEAR_STOP:
      if (atTime > tr->trTime + tr->trDuration) {
        atTime = tr->trTime + tr->trDuration;
      }
      deltaTime = (atTime - tr->trTime) * 0.001; // milliseconds to seconds
      if (deltaTime < 0) {
        deltaTime = 0;
      }
      VectorMA(tr->trBase, deltaTime, tr->trDelta, result);
      break;
    case TR_GRAVITY:
      deltaTime = (atTime - tr->trTime) * 0.001; // milliseconds to seconds
      VectorMA(tr->trBase, deltaTime, tr->trDelta, result);
      result[2] -= 0.5 * DEFAULT_GRAVITY * deltaTime * deltaTime; // FIXME: local gravity...
      break;
    default:
      Com_Error(ERR_DROP, "BG_EvaluateTrajectory: unknown trType: %i", tr->trTime);
      break;
  }
}

/*
 ================
 BG_EvaluateTrajectoryDelta

 For determining velocity at a given time
 ================
 */
void BG_EvaluateTrajectoryDelta(const trajectory_t *tr, int atTime, vec3_t result) {
  float deltaTime;
  float phase;

  switch (tr->trType) {
    case TR_STATIONARY:
    case TR_INTERPOLATE:
      VectorClear(result);
      break;
    case TR_LINEAR:
      VectorCopy(tr->trDelta, result);
      break;
    case TR_SINE:
      deltaTime = (atTime - tr->trTime) / (float) tr->trDuration;
      phase = cos(deltaTime * M_PI * 2); // derivative of sin = cos
      phase *= 0.5;
      VectorScale(tr->trDelta, phase, result);
      break;
    case TR_LINEAR_STOP:
      if (atTime > tr->trTime + tr->trDuration) {
        VectorClear(result);
        return;
      }
      VectorCopy(tr->trDelta, result);
      break;
    case TR_GRAVITY:
      deltaTime = (atTime - tr->trTime) * 0.001; // milliseconds to seconds
      VectorCopy(tr->trDelta, result);
      result[2] -= DEFAULT_GRAVITY * deltaTime; // FIXME: local gravity...
      break;
    default:
      Com_Error(ERR_DROP, "BG_EvaluateTrajectoryDelta: unknown trType: %i", tr->trTime);
      break;
  }
}

char *eventnames[] = { "EV_NONE",

"EV_FOOTSTEP", "EV_FOOTSTEP_METAL", "EV_FOOTSPLASH", "EV_FOOTWADE", "EV_SWIM",

"EV_STEP_4", "EV_STEP_8", "EV_STEP_12", "EV_STEP_16",

"EV_FALL_SHORT", "EV_FALL_MEDIUM", "EV_FALL_FAR",

"EV_JUMP_PAD", // boing sound at origin, jump sound on player

    "EV_JUMP",
    "EV_WATER_TOUCH", // foot touches
    "EV_WATER_LEAVE", // foot leaves
    "EV_WATER_UNDER", // head touches
    "EV_WATER_CLEAR", // head leaves

    "EV_ITEM_PICKUP", // normal item pickups are predictable
    "EV_GLOBAL_ITEM_PICKUP", // powerup / team sounds are broadcast to everyone

    "EV_NOAMMO",
    "EV_CHANGE_WEAPON",
    "EV_FIRE_WEAPON",

    "EV_USE_ITEM0",
    "EV_USE_ITEM1",
    "EV_USE_ITEM2",
    "EV_USE_ITEM3",
    "EV_USE_ITEM4",
    "EV_USE_ITEM5",
    "EV_USE_ITEM6",
    "EV_USE_ITEM7",
    "EV_USE_ITEM8",
    "EV_USE_ITEM9",
    "EV_USE_ITEM10",
    "EV_USE_ITEM11",
    "EV_USE_ITEM12",
    "EV_USE_ITEM13",
    "EV_USE_ITEM14",
    "EV_USE_ITEM15",

    "EV_ITEM_RESPAWN",
    "EV_ITEM_POP",
    "EV_PLAYER_TELEPORT_IN",
    "EV_PLAYER_TELEPORT_OUT",

    "EV_GRENADE_BOUNCE", // eventParm will be the soundindex

    "EV_GENERAL_SOUND",
    "EV_GLOBAL_SOUND", // no attenuation
    "EV_GLOBAL_TEAM_SOUND",

    "EV_BULLET_HIT_FLESH",
    "EV_BULLET_HIT_WALL",

    "EV_MISSILE_HIT",
    "EV_MISSILE_MISS",
    "EV_MISSILE_MISS_METAL",
    "EV_RAILTRAIL",
    "EV_SHOTGUN",
    "EV_BULLET", // otherEntity is the shooter

    "EV_PAIN",
    "EV_DEATH1",
    "EV_DEATH2",
    "EV_DEATH3",
    "EV_OBITUARY",

    "EV_POWERUP_QUAD",
    "EV_POWERUP_BATTLESUIT",
    "EV_POWERUP_REGEN",

    "EV_GIB_PLAYER", // gib a previously living player
    "EV_SCOREPLUM", // score plum

    "EV_DEBUG_LINE",
    "EV_STOPLOOPINGSOUND",
    "EV_TAUNT",
    "EV_TAUNT_YES",
    "EV_TAUNT_NO",
    "EV_TAUNT_FOLLOWME",
    "EV_TAUNT_GETFLAG",
    "EV_TAUNT_GUARDBASE",
    "EV_TAUNT_PATROL",

    "EV_WALLJUMP",
    "EV_GRAB",
    "EV_FALL_MINIMAL",

    "EV_NUKE_1",
    "EV_NUKE_2",
    "EV_NUKE_3",
    "EV_NUKE_4",
    "EV_NUKE_5",
    "EV_NUKE_6",
    "EV_NUKE_7",

    "EV_SHRAPNEL_IMPACT", };

/*
 ===============
 BG_AddPredictableEventToPlayerstate

 Handles the sequence numbers
 ===============
 */

void trap_Cvar_VariableStringBuffer(const char *var_name, char *buffer, int bufsize);

void BG_AddPredictableEventToPlayerstate(int newEvent, int eventParm, playerState_t *ps) {

#ifdef _DEBUG
  {
    char buf[256];
    trap_Cvar_VariableStringBuffer("showevents", buf, sizeof (buf));
    if (atof(buf) != 0) {
#ifdef QAGAME
      Com_Printf(" game event svt %5d -> %5d: num = %20s parm %d\n", ps->pmove_framecount/*ps->commandTime*/, ps->eventSequence, eventnames[newEvent], eventParm);
#else
      Com_Printf("Cgame event svt %5d -> %5d: num = %20s parm %d\n", ps->pmove_framecount/*ps->commandTime*/, ps->eventSequence, eventnames[newEvent], eventParm);
#endif
    }
  }
#endif
  ps->events[ps->eventSequence & (MAX_PS_EVENTS - 1)] = newEvent;
  ps->eventParms[ps->eventSequence & (MAX_PS_EVENTS - 1)] = eventParm;
  ps->eventSequence++;
}

/*
 ========================
 BG_TouchJumpPad
 ========================
 */
void BG_TouchJumpPad(playerState_t *ps, entityState_t *jumppad) {
  vec3_t angles;
  float p;
  int effectNum;

  // spectators don't use jump pads
  if (ps->pm_type != PM_NORMAL) {
    return;
  }

  // if we didn't hit this same jumppad the previous frame
  // then don't play the event sound again if we are in a fat trigger
  if (ps->jumppad_ent != jumppad->number) {

    vectoangles(jumppad->origin2, angles);
    p = fabs(AngleNormalize180(angles[PITCH]));
    if (p < 45) {
      effectNum = 0;
    } else {
      effectNum = 1;
    }
    BG_AddPredictableEventToPlayerstate(EV_JUMP_PAD, effectNum, ps);
  }
  // remember hitting this jumppad this frame
  ps->jumppad_ent = jumppad->number;
  ps->jumppad_frame = ps->pmove_framecount;
  // give the player the velocity from the jumppad
  VectorCopy(jumppad->origin2, ps->velocity);
}

/*
 ========================
 BG_PlayerStateToEntityState

 This is done after each set of usercmd_t on the server,
 and after local prediction on the client
 ========================
 */
void BG_PlayerStateToEntityState(playerState_t *ps, entityState_t *s, qboolean snap) {
  int i;

  if (ps->pm_type == PM_INTERMISSION || ps->pm_type == PM_SPECTATOR) {
    s->eType = ET_INVISIBLE;
  } else if (ps->stats[STAT_HEALTH] <= GIB_HEALTH) {
    s->eType = ET_INVISIBLE;
  } else {
    s->eType = ET_PLAYER;
  }

  s->number = ps->clientNum;

  s->pos.trType = TR_INTERPOLATE;
  VectorCopy(ps->origin, s->pos.trBase);
  if (snap) {
    SnapVector(s->pos.trBase);
  }
  // set the trDelta for flag direction
  VectorCopy(ps->velocity, s->pos.trDelta);

  s->apos.trType = TR_INTERPOLATE;
  VectorCopy(ps->viewangles, s->apos.trBase);
  if (snap) {
    SnapVector(s->apos.trBase);
  }

  s->angles2[YAW] = ps->movementDir;
  s->legsAnim = ps->legsAnim;
  s->torsoAnim = ps->torsoAnim;
  s->clientNum = ps->clientNum; // ET_PLAYER looks here instead of at number
  // so corpses can also reference the proper config
  s->eFlags = ps->eFlags;
  if (ps->stats[STAT_HEALTH] <= 0) {
    s->eFlags |= EF_DEAD;
  } else {
    s->eFlags &= ~EF_DEAD;
  }

  if (ps->externalEvent) {
    s->event = ps->externalEvent;
    s->eventParm = ps->externalEventParm;
  } else if (ps->entityEventSequence < ps->eventSequence) {
    int seq;

    if (ps->entityEventSequence < ps->eventSequence - MAX_PS_EVENTS) {
      ps->entityEventSequence = ps->eventSequence - MAX_PS_EVENTS;
    }
    seq = ps->entityEventSequence & (MAX_PS_EVENTS - 1);
    s->event = ps->events[seq] | ((ps->entityEventSequence & 3) << 8);
    s->eventParm = ps->eventParms[seq];
    ps->entityEventSequence++;
  }

  s->weapon = ps->weapon;
  s->groundEntityNum = ps->groundEntityNum;

  s->powerups = 0;
  for (i = 0; i < MAX_POWERUPS; i++) {
    if (ps->powerups[i]) {
      s->powerups |= 1 << i;
    }
  }

  s->loopSound = ps->loopSound;
  s->generic1 = ps->generic1;

  s->stamina = ps->stamina;
  s->bleeding = ps->wounds;
}

/*
 ========================
 BG_PlayerStateToEntityStateExtraPolate

 This is done after each set of usercmd_t on the server,
 and after local prediction on the client
 ========================
 */
void BG_PlayerStateToEntityStateExtraPolate(playerState_t *ps, entityState_t *s, int time, qboolean snap) {
  int i;

  if (ps->pm_type == PM_INTERMISSION || ps->pm_type == PM_SPECTATOR) {
    s->eType = ET_INVISIBLE;
  } else if (ps->stats[STAT_HEALTH] <= GIB_HEALTH) {
    s->eType = ET_INVISIBLE;
  } else {
    s->eType = ET_PLAYER;
  }

  s->number = ps->clientNum;

  s->pos.trType = TR_LINEAR_STOP;
  VectorCopy(ps->origin, s->pos.trBase);
  if (snap) {
    SnapVector(s->pos.trBase);
  }
  // set the trDelta for flag direction and linear prediction
  VectorCopy(ps->velocity, s->pos.trDelta);
  // set the time for linear prediction
  s->pos.trTime = time;
  // set maximum extra polation time
  s->pos.trDuration = 50; // 1000 / sv_fps (default = 20)

  s->apos.trType = TR_INTERPOLATE;
  VectorCopy(ps->viewangles, s->apos.trBase);
  if (snap) {
    SnapVector(s->apos.trBase);
  }

  s->angles2[YAW] = ps->movementDir;
  s->legsAnim = ps->legsAnim;
  s->torsoAnim = ps->torsoAnim;
  s->clientNum = ps->clientNum; // ET_PLAYER looks here instead of at number
  // so corpses can also reference the proper config
  s->eFlags = ps->eFlags;
  if (ps->stats[STAT_HEALTH] <= 0) {
    s->eFlags |= EF_DEAD;
  } else {
    s->eFlags &= ~EF_DEAD;
  }

  if (ps->externalEvent) {
    s->event = ps->externalEvent;
    s->eventParm = ps->externalEventParm;
  } else if (ps->entityEventSequence < ps->eventSequence) {
    int seq;

    if (ps->entityEventSequence < ps->eventSequence - MAX_PS_EVENTS) {
      ps->entityEventSequence = ps->eventSequence - MAX_PS_EVENTS;
    }
    seq = ps->entityEventSequence & (MAX_PS_EVENTS - 1);
    s->event = ps->events[seq] | ((ps->entityEventSequence & 3) << 8);
    s->eventParm = ps->eventParms[seq];
    ps->entityEventSequence++;
  }

  s->weapon = ps->weapon;
  s->groundEntityNum = ps->groundEntityNum;

  s->powerups = 0;
  for (i = 0; i < MAX_POWERUPS; i++) {
    if (ps->powerups[i]) {
      s->powerups |= 1 << i;
    }
  }

  s->loopSound = ps->loopSound;
  s->generic1 = ps->generic1;

  s->stamina = ps->stamina;
  s->bleeding = ps->wounds;
}

/*
 ========================
 BG_NameForWeapon
 ========================
 */
char *BG_NameForWeapon(int weap) {
  gitem_t *it;

  for (it = bg_itemlist + 1; it->classname; it++) {
    if (it->giType == IT_WEAPON && it->giTag == weap) {
      return it->pickup_name;
    }
  }
  return NULL;
}
