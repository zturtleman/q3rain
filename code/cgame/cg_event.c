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
// cg_event.c -- handle entity events at snapshot or playerstate transitions

#include "cg_local.h"

//==========================================================================

/*
 ===================
 CG_PlaceString

 Also called by scoreboard drawing
 ===================
 */
const char *CG_PlaceString(int rank) {
  static char str[64];
  char *s, *t;

  if (rank & RANK_TIED_FLAG) {
    rank &= ~RANK_TIED_FLAG;
    t = "Tied for ";
  } else {
    t = "";
  }

  if (rank == 1) {
    s = S_COLOR_BLUE "1st" S_COLOR_WHITE; // draw in blue
  } else if (rank == 2) {
    s = S_COLOR_RED "2nd" S_COLOR_WHITE; // draw in red
  } else if (rank == 3) {
    s = S_COLOR_YELLOW "3rd" S_COLOR_WHITE; // draw in yellow
  } else if (rank == 11) {
    s = "11th";
  } else if (rank == 12) {
    s = "12th";
  } else if (rank == 13) {
    s = "13th";
  } else if (rank % 10 == 1) {
    s = va("%ist", rank);
  } else if (rank % 10 == 2) {
    s = va("%ind", rank);
  } else if (rank % 10 == 3) {
    s = va("%ird", rank);
  } else {
    s = va("%ith", rank);
  }

  Com_sprintf(str, sizeof(str), "%s%s", t, s);
  return str;
}

static void CG_KillfeedAppend(char attacker[32], char target[32], int mod);

/*
 =============
 CG_KillfeedShift
 =============
 */
void CG_KillfeedShift(char attacker[32], char target[32], int mod) {
  int i;
  for (i = 1; i < cg_killfeedHeight.integer; i++) {
    Q_strncpyz(killfeed.attackers[i - 1], killfeed.attackers[i], 32);
    Q_strncpyz(killfeed.targets[i - 1], killfeed.targets[i], 32);
    killfeed.mods[i - 1] = killfeed.mods[i];
    killfeed.times[i - 1] = killfeed.times[i];
  }
  if (attacker != NULL && target != NULL && mod >= 0) {
    Q_strncpyz(killfeed.attackers[cg_killfeedHeight.integer - 1], attacker, 32);
    Q_strncpyz(killfeed.targets[cg_killfeedHeight.integer - 1], target, 32);
    killfeed.mods[cg_killfeedHeight.integer - 1] = mod;
    killfeed.times[i] = cg.time;
  }
}

/*
 =============
 CG_KillfeedSort
 =============
 */
void CG_KillfeedSort(void) {
  int i;
  for (i = 1; i < cg_killfeedHeight.integer; i++) {
    if (!killfeed.attackers[i - 1][0]) {
      Q_strncpyz(killfeed.attackers[i - 1], killfeed.attackers[i], 32);
      Q_strncpyz(killfeed.targets[i - 1], killfeed.targets[i], 32);
      killfeed.mods[i - 1] = killfeed.mods[i];
      killfeed.times[i - 1] = killfeed.times[i];
      killfeed.attackers[i][0] = 0;
      killfeed.targets[i][0] = 0;
      killfeed.mods[i] = -1;
      killfeed.times[i] = 0;
    }
  }
}

/*
 =============
 CG_KillfeedAppend
 =============
 */
static void CG_KillfeedAppend(char attacker[32], char target[32], int mod) {
  int i;
  for (i = 0; i < cg_killfeedHeight.integer; i++) {
    if (!killfeed.attackers[i][0]) {
      Q_strncpyz(killfeed.attackers[i], attacker, sizeof(killfeed.attackers[i]));
      Q_strncpyz(killfeed.targets[i], target, sizeof(killfeed.targets[i]));
      killfeed.mods[i] = mod;
      killfeed.times[i] = cg.time;
      return;
    }
  }
  CG_KillfeedShift(attacker, target, mod);
}

/*
 =============
 CG_Killfeed
 =============
 */
static void CG_Killfeed(int mod, int attacker, int target, char attackerName[32], char targetName[32]) {
  int i;
  //Com_Printf("CG_Killfeed(%i, %i, %i, %s, %s)\n");
  if (attackerName == NULL || !attackerName) {
    attackerName = "";
  } else if (attacker == ENTITYNUM_WORLD) {
    Q_strncpyz(attackerName, targetName, 32);
    targetName[0] = 0;
  }
  if (targetName == NULL || !targetName) {
    targetName = "";
  }
  if (attacker == target) {
    //CG_Printf("%i (%s) killed himself by %i\n", attacker, attackerName, mod);
    targetName = "";
  } else if (mod <= -1 || attacker <= -1) {
    //CG_Printf("%i (%s) died for unknown reason\n", target, targetName);
  } else {
    //CG_Printf("%i (%s) was killed by %i (%s) using %i\n", target, targetName, attacker, attackerName, mod);
  }
  CG_KillfeedAppend(attackerName, targetName, mod);
}

/*
 =============
 CG_Obituary
 =============
 */
static void CG_Obituary(entityState_t *ent) {
  int mod;
  int target, attacker;
  char *message;
  char *message2;
  const char *targetInfo;
  const char *attackerInfo;
  char targetName[32];
  char attackerName[32];
  gender_t gender;
  clientInfo_t *ci;

  target = ent->otherEntityNum;
  attacker = ent->otherEntityNum2;
  mod = ent->eventParm;

  if (target < 0 || target >= MAX_CLIENTS) {
    CG_Error("CG_Obituary: target out of range");
  }
  ci = &cgs.clientinfo[target];

  if (attacker < 0 || attacker >= MAX_CLIENTS) {
    attacker = ENTITYNUM_WORLD;
    attackerInfo = NULL;
  } else {
    attackerInfo = CG_ConfigString(CS_PLAYERS + attacker);
  }

  targetInfo = CG_ConfigString(CS_PLAYERS + target);
  if (!targetInfo) {
    return;
  }
  Q_strncpyz(targetName, Info_ValueForKey(targetInfo, "n"), sizeof(targetName) - 2);
  strcat(targetName, S_COLOR_WHITE);

  message2 = "";

  // check for single client messages

  switch (mod) {
    case MOD_SUICIDE:
      message = "suicides";
      break;
    case MOD_FALLING:
      message = "cratered";
      break;
    case MOD_CRUSH:
      message = "was squished";
      break;
    case MOD_WATER:
      message = "went out of air";
      break;
    case MOD_SLIME:
      message = "melted";
      break;
    case MOD_LAVA:
      message = "does a back flip into the lava";
      break;
    case MOD_TARGET_LASER:
      message = "saw the light";
      break;
    case MOD_TRIGGER_HURT:
      message = "was in the wrong place";
      break;
    case MOD_MOOR:
      message = "turned into mud";
      break;
    case MOD_ADMIN:
      message = "wasn't nice to the admin";
      break;
    case MOD_NUKE:
      message = "was blasted by a nuke";
      break;
    case MOD_SHRAPNEL:
      message = "was pierced by a shrapnel";
      break;
    case MOD_BLEED:
      message = "bled to death";
      break;
    default:
      message = NULL;
      break;
  }

  if (attacker == target) {
    gender = ci->gender;
    switch (mod) {
      case MOD_HE:
        message = "was... - ^1WTF DID JUST HAPPEN?";
        break;
      case MOD_HE_SPLASH:
        message = "doesn't know how to use grenades";
        break;
      case MOD_WINDOW:
        message = "hit it too hard";
        break;
      case MOD_NADELOVE:
        if (gender == GENDER_FEMALE) {
          message = "was attached a bit too much to her grenade";
        } else {
          message = "was attached a bit too much to his grenade";
        }
        break;
      case MOD_BOMB:
        if (gender == GENDER_FEMALE) {
          message = "was blasted by her own bomb";
        } else {
          message = "was blasted by his own bomb";
        }
        break;
      case MOD_SHRAPNEL:
        if (gender == GENDER_FEMALE) {
          message = "was pierced by her own shrapnel";
        } else {
          message = "was blasted by his own shrapnel";
        }
        break;
      default:
        if (gender == GENDER_FEMALE)
          message = "killed herself";
        else
          message = "killed himself";
        break;
    }
  }

  if (message) {
    if (cg_killfeed.integer) {
      if (attacker == ENTITYNUM_WORLD) {
        CG_Killfeed(mod, attacker, target, "<world>", targetName);
      } else {
        CG_Killfeed(mod, attacker, target, targetName, "");
      }
      return;
    }
    CG_Printf("%s %s.\n", targetName, message);
    return;
  }

  // check for double client messages
  if (!attackerInfo) {
    attacker = ENTITYNUM_WORLD;
    strcpy(attackerName, "noname");
  } else {
    Q_strncpyz(attackerName, Info_ValueForKey(attackerInfo, "n"), sizeof(attackerName) - 2);
    strcat(attackerName, S_COLOR_WHITE);
    // check for kill messages about the current clientNum
    if (target == cg.snap->ps.clientNum) {
      Q_strncpyz(cg.killerName, attackerName, sizeof(cg.killerName));
    }
  }

  // check for kill messages from the current clientNum
  if (attacker == cg.snap->ps.clientNum) {
    char *s;
    s = va("You killed %s\n%s place with %i", targetName, CG_PlaceString(cg.snap->ps.persistant[PERS_RANK] + 1), cg.snap->ps.persistant[PERS_SCORE]);
    CG_CenterPrint(s, SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH);
  }

  if (attacker != ENTITYNUM_WORLD) {
    switch (mod) {
      case MOD_TELEFRAG:
        message = "tried to invade";
        message2 = "'s personal space";
        break;
      case MOD_HE:
        message = "was ^1EPICLY PWNT ^7by";
        message2 = "'s grenade";
        break;
      case MOD_HE_SPLASH:
        message = "didn't see";
        message2 = "'s grenade";
        break;
      case MOD_BARRETT:
        message = "was ripped apart by";
        message2 = "'s Barrett";
        break;
      case MOD_INTERVENTION:
        message = "was sniped down by";
        break;
      case MOD_CROSSBOW:
        message = "was sniped down by";
        break;
      case MOD_KNIFE:
        message = "was sliced by";
        break;
      case MOD_ACR:
        message = "was pinned down by";
        break;
      case MOD_WALTHER:
        message = "was shot by";
        break;
      case MOD_HANDS:
        message = "was beaten to death by";
        break;
      case MOD_BOMB:
        message = "was lacerated by";
        message2 = "'s C4";
        break;
      case MOD_SHRAPNEL:
        message = "was pierced by";
        message2 = "'s shrapnel";
        break;
      case MOD_SNOWBOARD:
        message = "was beaten to death by";
        message2 = "'s ^1snowboard";
        break;
      default:
        message = "was killed by";
        break;
    }

    if (message) {
      if (cg_killfeed.integer) {
        CG_Killfeed(mod, attacker, target, attackerName, targetName);
        return;
      }
      CG_Printf("%s %s %s%s\n", targetName, message, attackerName, message2);
      return;
    }
  }

  // we don't know what it was
  if (cg_killfeed.integer) {
    CG_Killfeed(-1, -1, target, attackerName, targetName);
    return;
  }
  CG_Printf("%s died.\n", targetName);
}

//==========================================================================

/*
 ===============
 CG_UseItem
 ===============
 */
static void CG_UseItem(centity_t *cent) {
  clientInfo_t *ci;
  int itemNum, clientNum;
  gitem_t *item;
  entityState_t *es;

  es = &cent->currentState;

  itemNum = (es->event & ~EV_EVENT_BITS) - EV_USE_ITEM0;
  if (itemNum < 0 || itemNum > HI_NUM_HOLDABLE) {
    itemNum = 0;
  }

  // print a message if the local player
  if (es->number == cg.snap->ps.clientNum) {
    if (!itemNum) {
      CG_CenterPrint("No item to use", SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH);
    } else {
      item = BG_FindItemForHoldable(itemNum);
      CG_CenterPrint(va("Use %s", item->pickup_name), SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH);
    }
  }

  switch (itemNum) {
    default:
    case HI_NONE:
      trap_S_StartSound(NULL, es->number, CHAN_BODY, cgs.media.useNothingSound);
      break;

    case HI_BOMB:
      clientNum = cent->currentState.clientNum;
      if (clientNum >= 0 && clientNum < MAX_CLIENTS) {
        // boom goes here
      }
      break;
  }

}

/*
 ================
 CG_ItemPickup

 A new item was picked up this frame
 ================
 */
static void CG_ItemPickup(int itemNum) {
  cg.itemPickup = itemNum;
  cg.itemPickupTime = cg.time;
  cg.itemPickupBlendTime = cg.time;
  if (bg_itemlist[itemNum].giType == IT_WEAPON) {
    if (cg_autoswitch.integer) {
      cg.weaponSelectTime = cg.time;
      cg.weaponSelect = bg_itemlist[itemNum].giTag;
    }
  }

}

/*
 ================
 CG_PainEvent

 Also called by playerstate transition
 ================
 */
void CG_PainEvent(centity_t *cent, int health) {
  char *snd;

  // don't do more than two pain sounds a second
  if (cg.time - cent->pe.painTime < 250) {
    return;
  }

  if (health < 25) {
    snd = "*pain25_1.wav";
  } else if (health < 50) {
    snd = "*pain50_1.wav";
  } else if (health < 75) {
    snd = "*pain75_1.wav";
  } else {
    snd = "*pain100_1.wav";
  }
  trap_S_StartSound(NULL, cent->currentState.number, CHAN_VOICE, CG_CustomSound(cent->currentState.number, snd));

  // save pain time for programitic twitch animation
  cent->pe.painTime = cg.time;
  cent->pe.painDirection ^= 1;
}

/*
 ==============
 CG_EntityEvent

 An entity has an event value
 also called by CG_CheckPlayerstateEvents
 ==============
 */
#define	DEBUGNAME(x) if(cg_debugEvents.integer){CG_Printf(x"\n");}

void CG_EntityEvent(centity_t *cent, vec3_t position) {
  entityState_t *es;
  int event;
  vec3_t dir;
  const char *s;
  int clientNum;
  clientInfo_t *ci;

  es = &cent->currentState;
  event = es->event & ~EV_EVENT_BITS;

  if (cg_debugEvents.integer) {
    CG_Printf("ent:%3i  event:%3i ", es->number, event);
  }

  if (!event) {
    DEBUGNAME("ZEROEVENT");
    return;
  }

  clientNum = es->clientNum;
  if (clientNum < 0 || clientNum >= MAX_CLIENTS) {
    clientNum = 0;
  }
  ci = &cgs.clientinfo[clientNum];

  switch (event) {
    //
    // movement generated events
    //
    case EV_FOOTSTEP:
      DEBUGNAME("EV_FOOTSTEP")
      if (cg_footsteps.integer) {
        trap_S_StartSound(NULL, es->number, CHAN_BODY, cgs.media.footsteps[ci->footsteps][rand() & 3]);
      }
      break;
    case EV_FOOTSTEP_METAL:
      DEBUGNAME("EV_FOOTSTEP_METAL")
      if (cg_footsteps.integer) {
        trap_S_StartSound(NULL, es->number, CHAN_BODY, cgs.media.footsteps[FOOTSTEP_METAL][rand() & 3]);
      }
      break;
    case EV_FOOTSPLASH:
      DEBUGNAME("EV_FOOTSPLASH")
      if (cg_footsteps.integer) {
        trap_S_StartSound(NULL, es->number, CHAN_BODY, cgs.media.footsteps[FOOTSTEP_SPLASH][rand() & 3]);
      }
      break;
    case EV_FOOTWADE:
      DEBUGNAME("EV_FOOTWADE")
      if (cg_footsteps.integer) {
        trap_S_StartSound(NULL, es->number, CHAN_BODY, cgs.media.footsteps[FOOTSTEP_SPLASH][rand() & 3]);
      }
      break;
    case EV_SWIM:
      DEBUGNAME("EV_SWIM")
      if (cg_footsteps.integer) {
        trap_S_StartSound(NULL, es->number, CHAN_BODY, cgs.media.footsteps[FOOTSTEP_SPLASH][rand() & 3]);
      }
      break;
    case EV_FALL_MINIMAL:
      DEBUGNAME("EV_FALL_MINIMAL")
      trap_S_StartSound(NULL, es->number, CHAN_AUTO, cgs.media.landSound);
      if (clientNum == cg.predictedPlayerState.clientNum) {
        cg.landChange = -16;
        cg.landTime = cg.time;
      }
      break;
    case EV_FALL_SHORT:
      DEBUGNAME("EV_FALL_SHORT")
      trap_S_StartSound(NULL, es->number, CHAN_AUTO, cgs.media.landSound);
      if (clientNum == cg.predictedPlayerState.clientNum) {
        cg.landChange = -16;
        cg.landTime = cg.time;
      }
      break;
    case EV_FALL_MEDIUM:
      DEBUGNAME("EV_FALL_MEDIUM")
      trap_S_StartSound(NULL, es->number, CHAN_AUTO, cgs.media.landSound);
      if (clientNum == cg.predictedPlayerState.clientNum) {
        cg.landChange = -24;
        cg.landTime = cg.time;
      }
      break;
    case EV_FALL_FAR:
      DEBUGNAME("EV_FALL_FAR")
      trap_S_StartSound(NULL, es->number, CHAN_AUTO, CG_CustomSound(es->number, "*fall1.wav"));
      cent->pe.painTime = cg.time;
      if (clientNum == cg.predictedPlayerState.clientNum) {
        cg.landChange = -32;
        cg.landTime = cg.time;
      }
      break;

    case EV_STEP_4:
    case EV_STEP_8:
    case EV_STEP_12:
    case EV_STEP_16: // smooth out step up transitions
      DEBUGNAME("EV_STEP")
      {
        float oldStep;
        int delta;
        int step;

        if (clientNum != cg.predictedPlayerState.clientNum) {
          break;
        }
        // if we are interpolating, we don't need to smooth steps
        if (cg.demoPlayback || (cg.snap->ps.pm_flags & PMF_FOLLOW) || cg_nopredict.integer || cg_synchronousClients.integer) {
          break;
        }
        // check for stepping up before a previous step is completed
        delta = cg.time - cg.stepTime;
        if (delta < STEP_TIME) {
          oldStep = cg.stepChange * (STEP_TIME - delta) / STEP_TIME;
        } else {
          oldStep = 0;
        }

        // add this amount
        step = 4 * (event - EV_STEP_4 + 1);
        cg.stepChange = oldStep + step;
        if (cg.stepChange > MAX_STEP_CHANGE) {
          cg.stepChange = MAX_STEP_CHANGE;
        }
        cg.stepTime = cg.time;
        break;
      }

    case EV_JUMP_PAD:
      DEBUGNAME("EV_JUMP_PAD")
      {
        localEntity_t *smoke;
        vec3_t up = { 0, 0, 1 };
        smoke = CG_SmokePuff(cent->lerpOrigin, up, 32, 1, 1, 1, 0.33f, 1000, cg.time, 0, LEF_PUFF_DONT_SCALE, cgs.media.smokePuffShader);
      }
      trap_S_StartSound(cent->lerpOrigin, -1, CHAN_VOICE, cgs.media.jumpPadSound);
      break;

    case EV_WALLJUMP:
      DEBUGNAME("EV_WALLJUMP")
      break;
    case EV_JUMP:
      DEBUGNAME("EV_JUMP")
      //trap_S_StartSound (NULL, es->number, CHAN_VOICE, CG_CustomSound( es->number, "*jump1.wav" ) );
      break;
    case EV_TAUNT:
      DEBUGNAME("EV_TAUNT")
      //trap_S_StartSound(NULL, es->number, CHAN_VOICE, CG_CustomSound(es->number, "*taunt.wav"));
      break;
    case EV_WATER_TOUCH:
      DEBUGNAME("EV_WATER_TOUCH")
      trap_S_StartSound(NULL, es->number, CHAN_AUTO, cgs.media.watrInSound);
      break;
    case EV_WATER_LEAVE:
      DEBUGNAME("EV_WATER_LEAVE")
      trap_S_StartSound(NULL, es->number, CHAN_AUTO, cgs.media.watrOutSound);
      break;
    case EV_WATER_UNDER:
      DEBUGNAME("EV_WATER_UNDER")
      trap_S_StartSound(NULL, es->number, CHAN_AUTO, cgs.media.watrUnSound);
      break;
    case EV_WATER_CLEAR:
      DEBUGNAME("EV_WATER_CLEAR")
      trap_S_StartSound(NULL, es->number, CHAN_AUTO, CG_CustomSound(es->number, "*gasp.wav"));
      break;

    case EV_ITEM_PICKUP:
      DEBUGNAME("EV_ITEM_PICKUP")
      {
        gitem_t *item;
        int index;

        index = es->eventParm; // player predicted

        if (index < 1 || index >= bg_numItems) {
          break;
        }
        item = &bg_itemlist[index];

        // powerups and team items will have a separate global sound, this one
        // will be played at prediction time
        if (item->giType == IT_POWERUP || item->giType == IT_TEAM) {
          trap_S_StartSound(NULL, es->number, CHAN_AUTO, cgs.media.n_healthSound);
        } else {
          trap_S_StartSound(NULL, es->number, CHAN_AUTO, trap_S_RegisterSound(item->pickup_sound, qfalse));
        }

        // show icon and name on status bar
        if (es->number == cg.snap->ps.clientNum) {
          CG_ItemPickup(index);
        }
      }
      break;

    case EV_GLOBAL_ITEM_PICKUP:
      DEBUGNAME("EV_GLOBAL_ITEM_PICKUP")
      {
        gitem_t *item;
        int index;

        index = es->eventParm; // player predicted

        if (index < 1 || index >= bg_numItems) {
          break;
        }
        item = &bg_itemlist[index];
        // powerup pickups are global
        if (item->pickup_sound) {
          trap_S_StartSound(NULL, cg.snap->ps.clientNum, CHAN_AUTO, trap_S_RegisterSound(item->pickup_sound, qfalse));
        }

        // show icon and name on status bar
        if (es->number == cg.snap->ps.clientNum) {
          CG_ItemPickup(index);
        }
      }
      break;

      //
      // weapon events
      //
    case EV_NOAMMO:
      DEBUGNAME("EV_NOAMMO")
      //		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.noAmmoSound );
      if (es->number == cg.snap->ps.clientNum) {
        CG_OutOfAmmoChange();
      }
      break;
    case EV_CHANGE_WEAPON:
      DEBUGNAME("EV_CHANGE_WEAPON")
      trap_S_StartSound(NULL, es->number, CHAN_AUTO, cgs.media.selectSound);
      break;
    case EV_FIRE_WEAPON:
      DEBUGNAME("EV_FIRE_WEAPON")
      CG_FireWeapon(cent);
      break;

    case EV_USE_ITEM0:
      DEBUGNAME("EV_USE_ITEM0")
      CG_UseItem(cent);
      break;
    case EV_USE_ITEM1:
      DEBUGNAME("EV_USE_ITEM1")
      CG_UseItem(cent);
      break;
    case EV_USE_ITEM2:
      DEBUGNAME("EV_USE_ITEM2")
      CG_UseItem(cent);
      break;
    case EV_USE_ITEM3:
      DEBUGNAME("EV_USE_ITEM3")
      CG_UseItem(cent);
      break;
    case EV_USE_ITEM4:
      DEBUGNAME("EV_USE_ITEM4")
      CG_UseItem(cent);
      break;
    case EV_USE_ITEM5:
      DEBUGNAME("EV_USE_ITEM5")
      CG_UseItem(cent);
      break;
    case EV_USE_ITEM6:
      DEBUGNAME("EV_USE_ITEM6")
      CG_UseItem(cent);
      break;
    case EV_USE_ITEM7:
      DEBUGNAME("EV_USE_ITEM7")
      CG_UseItem(cent);
      break;
    case EV_USE_ITEM8:
      DEBUGNAME("EV_USE_ITEM8")
      CG_UseItem(cent);
      break;
    case EV_USE_ITEM9:
      DEBUGNAME("EV_USE_ITEM9")
      CG_UseItem(cent);
      break;
    case EV_USE_ITEM10:
      DEBUGNAME("EV_USE_ITEM10")
      CG_UseItem(cent);
      break;
    case EV_USE_ITEM11:
      DEBUGNAME("EV_USE_ITEM11")
      CG_UseItem(cent);
      break;
    case EV_USE_ITEM12:
      DEBUGNAME("EV_USE_ITEM12")
      CG_UseItem(cent);
      break;
    case EV_USE_ITEM13:
      DEBUGNAME("EV_USE_ITEM13")
      CG_UseItem(cent);
      break;
    case EV_USE_ITEM14:
      DEBUGNAME("EV_USE_ITEM14")
      CG_UseItem(cent);
      break;

      //=================================================================

      //
      // other events
      //
    case EV_PLAYER_TELEPORT_IN:
      DEBUGNAME("EV_PLAYER_TELEPORT_IN")
      trap_S_StartSound(NULL, es->number, CHAN_AUTO, cgs.media.teleInSound);
      CG_SpawnEffect(position);
      break;

    case EV_PLAYER_TELEPORT_OUT:
      DEBUGNAME("EV_PLAYER_TELEPORT_OUT")
      trap_S_StartSound(NULL, es->number, CHAN_AUTO, cgs.media.teleOutSound);
      CG_SpawnEffect(position);
      break;

    case EV_ITEM_POP:
      DEBUGNAME("EV_ITEM_POP")
      trap_S_StartSound(NULL, es->number, CHAN_AUTO, cgs.media.respawnSound);
      break;
    case EV_ITEM_RESPAWN:
      DEBUGNAME("EV_ITEM_RESPAWN")
      cent->miscTime = cg.time; // scale up from this
      trap_S_StartSound(NULL, es->number, CHAN_AUTO, cgs.media.respawnSound);
      break;

    case EV_GRENADE_BOUNCE:
      DEBUGNAME("EV_GRENADE_BOUNCE")
      if (rand() & 1) {
        trap_S_StartSound(NULL, es->number, CHAN_AUTO, cgs.media.hgrenb1aSound);
      } else {
        trap_S_StartSound(NULL, es->number, CHAN_AUTO, cgs.media.hgrenb2aSound);
      }
      break;
    case EV_SCOREPLUM:
      DEBUGNAME("EV_SCOREPLUM")
      CG_ScorePlum(cent->currentState.otherEntityNum, cent->lerpOrigin, cent->currentState.time);
      break;

      //
      // missile impacts
      //
    case EV_MISSILE_HIT:
      DEBUGNAME("EV_MISSILE_HIT")
      ByteToDir(es->eventParm, dir);
      CG_MissileHitPlayer(es->weapon, position, dir, es->otherEntityNum);
      break;

    case EV_MISSILE_MISS:
      DEBUGNAME("EV_MISSILE_MISS")
      ByteToDir(es->eventParm, dir);
      CG_MissileHitWall(es->weapon, 0, position, dir, IMPACTSOUND_DEFAULT);
      break;

    case EV_MISSILE_MISS_METAL:
      DEBUGNAME("EV_MISSILE_MISS_METAL")
      ByteToDir(es->eventParm, dir);
      CG_MissileHitWall(es->weapon, 0, position, dir, IMPACTSOUND_METAL);
      break;

    case EV_RAILTRAIL:
      DEBUGNAME("EV_RAILTRAIL")
      ;
      cent->currentState.weapon = WP_NONE;

      if (es->clientNum == cg.snap->ps.clientNum && !cg.renderingThirdPerson) {
        if (cg_drawGun.integer == 2)
          VectorMA(es->origin2, 8, cg.refdef.viewaxis[1], es->origin2);
        else if (cg_drawGun.integer == 3)
          VectorMA(es->origin2, 4, cg.refdef.viewaxis[1], es->origin2);
      }

      CG_RailTrail(ci, es->origin2, es->pos.trBase);

      // if the end was on a nomark surface, don't make an explosion
      if (es->eventParm != 255) {
        ByteToDir(es->eventParm, dir);
        CG_MissileHitWall(es->weapon, es->clientNum, position, dir, IMPACTSOUND_DEFAULT);
      }
      break;

    case EV_BULLET_HIT_WALL:
      DEBUGNAME("EV_BULLET_HIT_WALL")
      ;
      ByteToDir(es->eventParm, dir);
      CG_Bullet(es->pos.trBase, es->otherEntityNum, dir, qfalse, ENTITYNUM_WORLD);
      break;

    case EV_BULLET_HIT_FLESH:
      DEBUGNAME("EV_BULLET_HIT_FLESH")
      ;
      CG_Bullet(es->pos.trBase, es->otherEntityNum, dir, qtrue, es->eventParm);
      break;

    case EV_SHOTGUN:
      DEBUGNAME("EV_SHOTGUN")
      ;
      CG_ShotgunFire(es);
      break;

    case EV_GENERAL_SOUND:
      DEBUGNAME("EV_GENERAL_SOUND")
      ;
      if (cgs.gameSounds[es->eventParm]) {
        trap_S_StartSound(NULL, es->number, CHAN_VOICE, cgs.gameSounds[es->eventParm]);
      } else {
        s = CG_ConfigString(CS_SOUNDS + es->eventParm);
        trap_S_StartSound(NULL, es->number, CHAN_VOICE, CG_CustomSound(es->number, s));
      }
      break;

    case EV_GLOBAL_SOUND: // play from the player's head so it never diminishes
      DEBUGNAME("EV_GLOBAL_SOUND")
      ;
      if (cgs.gameSounds[es->eventParm]) {
        trap_S_StartSound(NULL, cg.snap->ps.clientNum, CHAN_AUTO, cgs.gameSounds[es->eventParm]);
      } else {
        s = CG_ConfigString(CS_SOUNDS + es->eventParm);
        trap_S_StartSound(NULL, cg.snap->ps.clientNum, CHAN_AUTO, CG_CustomSound(es->number, s));
      }
      break;

    case EV_GLOBAL_TEAM_SOUND: // play from the player's head so it never diminishes
    {
      DEBUGNAME("EV_GLOBAL_TEAM_SOUND");
      break;
    }

    case EV_PAIN:
      // local player sounds are triggered in CG_CheckLocalSounds,
      // so ignore events on the player
      DEBUGNAME("EV_PAIN")
      if (cent->currentState.number != cg.snap->ps.clientNum) {
        CG_PainEvent(cent, es->eventParm);
      }
      break;

    case EV_DEATH1:
    case EV_DEATH2:
    case EV_DEATH3:
      DEBUGNAME("EV_DEATHx")
      ;
      trap_S_StartSound(NULL, es->number, CHAN_VOICE, CG_CustomSound(es->number, va("*death%i.wav", event - EV_DEATH1 + 1)));
      break;

    case EV_OBITUARY:
      DEBUGNAME("EV_OBITUARY")
      ;
      CG_Obituary(es);
      break;

      //
      // powerup events
      //
      /*case EV_POWERUP_DIVESUIT:
       DEBUGNAME("EV_POWERUP_DIVESUIT");
       break;*/

    case EV_GIB_PLAYER:
      DEBUGNAME("EV_GIB_PLAYER")
      ;
      CG_GibPlayer(cent->lerpOrigin);
      break;

    case EV_BREAK_GLASS:
      DEBUGNAME("EV_BREAK_GLASS")
      ;
      // Change cgs.media.gibSound to whatever sound you want it to use
      // I think the gib sound sounds pretty good
      trap_S_StartSound(NULL, es->number, CHAN_BODY, cgs.media.gibSound);
      CG_BreakGlass(cent->lerpOrigin);
      break;

    case EV_BREAK_FLESH:
      DEBUGNAME("EV_BREAK_FLESH")
      ;
      trap_S_StartSound(NULL, es->number, CHAN_BODY, cgs.media.gibSound);
      CG_BreakFlesh(cent->lerpOrigin);
      break;

    case EV_BREAK_WOOD:
      DEBUGNAME("EV_BREAK_WOOD")
      ;
      trap_S_StartSound(NULL, es->number, CHAN_BODY, cgs.media.gibSound);
      CG_BreakWood(cent->lerpOrigin);
      break;

    case EV_BREAK_STONE:
      DEBUGNAME("EV_BREAK_STONE")
      ;
      trap_S_StartSound(NULL, es->number, CHAN_BODY, cgs.media.gibSound);
      CG_BreakStone(cent->lerpOrigin);
      break;

    case EV_BREAK_METAL:
      DEBUGNAME("EV_BREAK_METAL")
      ;
      trap_S_StartSound(NULL, es->number, CHAN_BODY, cgs.media.gibSound);
      CG_BreakMetal(cent->lerpOrigin);
      break;

    case EV_STOPLOOPINGSOUND:
      DEBUGNAME("EV_STOPLOOPINGSOUND")
      ;
      trap_S_StopLoopingSound(es->number);
      es->loopSound = 0;
      break;

    case EV_DEBUG_LINE:
      DEBUGNAME("EV_DEBUG_LINE")
      ;
      CG_Beam(cent);
      break;

    case EV_NUKE_1:
      DEBUGNAME("EV_NUKE_1")
      ;
      CG_Nuke(position, 1);
      break;

    case EV_NUKE_2:
      DEBUGNAME("EV_NUKE_2")
      ;
      CG_Nuke(position, 2);
      break;

    case EV_NUKE_3:
      DEBUGNAME("EV_NUKE_3")
      ;
      CG_Nuke(position, 3);
      break;

    case EV_NUKE_4:
      DEBUGNAME("EV_NUKE_4")
      CG_Nuke(position, 4);
      break;

    case EV_NUKE_5:
      DEBUGNAME("EV_NUKE_5")
      CG_Nuke(position, 5);
      break;

    case EV_NUKE_6:
      DEBUGNAME("EV_NUKE_6")
      CG_Nuke(position, 6);
      break;

    case EV_NUKE_7:
      DEBUGNAME("EV_NUKE_7")
      CG_Nuke(position, 7);
      break;

    case EV_SHRAPNEL_IMPACT:
      DEBUGNAME("EV_SHRAPNEL_IMPACT")
      CG_MissileHitWall(-2, 0, position, dir, IMPACTSOUND_METAL);
      break;

    default:
      DEBUGNAME("UNKNOWN")
      CG_Error("Unknown event: %i\n", event);
      break;
  }

}

/*
 ==============
 CG_CheckEvents

 ==============
 */
void CG_CheckEvents(centity_t *cent) {
  // check for event-only entities
  if (cent->currentState.eType > ET_EVENTS) {
    if (cent->previousEvent) {
      return; // already fired
    }
    // if this is a player event set the entity number of the client entity number
    if (cent->currentState.eFlags & EF_PLAYER_EVENT) {
      cent->currentState.number = cent->currentState.otherEntityNum;
    }

    cent->previousEvent = 1;

    cent->currentState.event = cent->currentState.eType - ET_EVENTS;
  } else {
    // check for events riding with another entity
    if (cent->currentState.event == cent->previousEvent) {
      return;
    }
    cent->previousEvent = cent->currentState.event;
    if ((cent->currentState.event & ~EV_EVENT_BITS) == 0) {
      return;
    }
  }

  // calculate the position at exactly the frame time
  BG_EvaluateTrajectory(&cent->currentState.pos, cg.snap->serverTime, cent->lerpOrigin);
  CG_SetEntitySoundPosition(cent);

  CG_EntityEvent(cent, cent->lerpOrigin);
}

