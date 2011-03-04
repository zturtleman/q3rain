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

/*
 ===============
 G_DamageFeedback

 Called just before a snapshot is sent to the given player.
 Totals up all damage and generates both the player_state_t
 damage values to that client for pain blends and kicks, and
 global pain sound events for all clients.
 ===============
 */
void P_DamageFeedback(gentity_t *player) {
  gclient_t *client;
  float count;
  vec3_t angles;

  client = player->client;
  if (client->ps.pm_type == PM_DEAD) {
    return;
  }

  // total points of damage shot at the player this frame
  count = client->damage_blood + client->damage_armor;
  if (count == 0) {
    return; // didn't take any damage
  }

  if (count > 255) {
    count = 255;
  }

  // send the information to the client

  // world damage (falling, slime, etc) uses a special code
  // to make the blend blob centered instead of positional
  if (client->damage_fromWorld) {
    client->ps.damagePitch = 255;
    client->ps.damageYaw = 255;

    client->damage_fromWorld = qfalse;
  } else {
    vectoangles(client->damage_from, angles);
    client->ps.damagePitch = angles[PITCH] / 360.0 * 256;
    client->ps.damageYaw = angles[YAW] / 360.0 * 256;
  }

  // play an apropriate pain sound
  if ((level.time > player->pain_debounce_time) && !(player->flags & FL_GODMODE) && client->lasthurt_mod != MOD_BLEED) {
    player->pain_debounce_time = level.time + 700;
    G_AddEvent(player, EV_PAIN, player->health);
    client->ps.damageEvent++;
  }

  client->ps.damageCount = count;

  //
  // clear totals
  //
  client->damage_blood = 0;
  client->damage_armor = 0;
  client->damage_knockback = 0;
}

static void P_KickBack(gentity_t *player, int pitch, int yaw, int damage) {
  gclient_t *client;

  client = player->client;
  client->ps.damagePitch = pitch;
  client->ps.damageYaw = yaw;
  client->damage_fromWorld = qfalse;
  client->ps.damageCount = damage;
  client->ps.damageEvent = ((int) level.time / 100) + 100;
}

/*
 =============
 P_WorldEffects

 Check for lava / slime contents and drowning
 =============
 */
void P_WorldEffects(gentity_t *ent) {
  qboolean divesuit;
  int waterlevel;

  if (ent->client->noclip) {
    ent->client->airOutTime = level.time + 12000; // don't need air
    return;
  }

  waterlevel = ent->waterlevel;

  divesuit = ent->client->ps.powerups[PW_DIVESUIT] > level.time;

  //
  // check for drowning
  //
  if (waterlevel == 3) {
    if (divesuit) {
      ent->client->airOutTime = level.time + 10000;
    }

    // if out of air, start drowning
    if (ent->client->airOutTime < level.time) {
      // drown!
      //ent->client->airOutTime += 1000;
      ent->client->airOutTime += 500;
      if (ent->health > 0) {
        //ent->damage += 2;
        ent->damage = 5;
        if (ent->damage > 15)
          ent->damage = 15;

        // play a gurp sound instead of a normal pain sound
        if (ent->health <= ent->damage) {
          G_Sound(ent, CHAN_VOICE, G_SoundIndex("*drown.wav"));
        } else if (rand() & 1) {
          G_Sound(ent, CHAN_VOICE, G_SoundIndex("sound/player/gurp1.wav"));
        } else {
          G_Sound(ent, CHAN_VOICE, G_SoundIndex("sound/player/gurp2.wav"));
        }

        // don't play a normal pain sound
        ent->pain_debounce_time = level.time + 200;
        if (ent->watertype & (CONTENTS_MOOR) && ent->health > 0) {
          G_Damage(ent, NULL, NULL, NULL, NULL, ent->damage, DAMAGE_NO_ARMOR, MOD_MOOR);
        } else if (ent->watertype & (CONTENTS_WATER) && ent->health > 0) {
          G_Damage(ent, NULL, NULL, NULL, NULL, ent->damage, DAMAGE_NO_ARMOR, MOD_WATER);
        }
      }
    }
  } else {
    ent->client->airOutTime = level.time + 12000;
    ent->damage = 2;
  }

  //
  // check for sizzle damage (move to pmove?)
  //
  if (waterlevel && (ent->watertype & (CONTENTS_LAVA | CONTENTS_SLIME))) {
    if (ent->health > 0 && ent->pain_debounce_time <= level.time) {
      if (ent->watertype & CONTENTS_LAVA) {
        G_Damage(ent, NULL, NULL, NULL, NULL, 30 * waterlevel, 0, MOD_LAVA);
      }
      if (ent->watertype & CONTENTS_SLIME) {
        G_Damage(ent, NULL, NULL, NULL, NULL, 10 * waterlevel, 0, MOD_SLIME);
      }
    }
  }
}

/*
 ===============
 G_SetClientSound
 ===============
 */
void G_SetClientSound(gentity_t *ent) {
  if (ent->waterlevel && (ent->watertype & (CONTENTS_LAVA | CONTENTS_SLIME))) {
    ent->client->ps.loopSound = level.snd_fry;
  } else {
    ent->client->ps.loopSound = 0;
  }
}

//==============================================================

/*
 ==============
 ClientImpacts
 ==============
 */
void ClientImpacts(gentity_t *ent, pmove_t *pm) {
  int i, j;
  trace_t trace;
  gentity_t *other;

  memset(&trace, 0, sizeof(trace));
  for (i = 0; i < pm->numtouch; i++) {
    for (j = 0; j < i; j++) {
      if (pm->touchents[j] == pm->touchents[i]) {
        break;
      }
    }
    if (j != i) {
      continue; // duplicated
    }
    other = &g_entities[pm->touchents[i]];

    if ((ent->r.svFlags & SVF_BOT) && (ent->touch)) {
      ent->touch(ent, other, &trace);
    }

    if (!other->touch) {
      continue;
    }

    other->touch(other, ent, &trace);
  }

}

/*
 ============
 G_TouchTriggers

 Find all trigger entities that ent's current position touches.
 Spectators will only interact with teleporters.
 ============
 */
void G_TouchTriggers(gentity_t *ent) {
  int i, num;
  int touch[MAX_GENTITIES];
  gentity_t *hit;
  trace_t trace;
  vec3_t mins, maxs;
  static vec3_t range = { 40, 40, 52 };
  qboolean bomb = qfalse;

  if (!ent->client) {
    return;
  }

  // dead clients don't activate triggers!
  if (ent->client->ps.stats[STAT_HEALTH] <= 0) {
    return;
  }

  VectorSubtract(ent->client->ps.origin, range, mins);
  VectorAdd(ent->client->ps.origin, range, maxs);

  num = trap_EntitiesInBox(mins, maxs, touch, MAX_GENTITIES);

  // can't use ent->absmin, because that has a one unit pad
  VectorAdd(ent->client->ps.origin, ent->r.mins, mins);
  VectorAdd(ent->client->ps.origin, ent->r.maxs, maxs);

  for (i = 0; i < num; i++) {
    hit = &g_entities[touch[i]];

    if (!hit->touch && !ent->touch) {
      continue;
    }
    if (!(hit->r.contents & CONTENTS_TRIGGER)) {
      continue;
    }

    // ignore most entities if a spectator
    if (ent->client->sess.sessionTeam == TEAM_SPECTATOR) {
      if (hit->s.eType != ET_TELEPORT_TRIGGER && hit->touch != Touch_DoorTrigger) {
        continue;
      }
    }

    // use seperate code for determining if an item is picked up
    // so you don't have to actually contact its bounding box
    if (hit->s.eType == ET_ITEM) {
      if (!BG_PlayerTouchesItem(&ent->client->ps, &hit->s, level.time)) {
        continue;
      }
    } else {
      if (!trap_EntityContact(mins, maxs, hit)) {
        continue;
      }
    }

    memset(&trace, 0, sizeof(trace));

    if (hit->touch) {
      if ((hit->flags & FL_BOMB) && bomb) {
        continue;
      }
      hit->touch(hit, ent, &trace);
    }

    if (hit->flags & FL_BOMB) {
      bomb = qtrue;
    }

    if ((ent->r.svFlags & SVF_BOT) && (ent->touch)) {
      ent->touch(ent, hit, &trace);
    }
  }

  if (!bomb) {
    ent->pickupTime = -1;
  }

  // if we didn't touch a jump pad this pmove frame
  if (ent->client->ps.jumppad_frame != ent->client->ps.pmove_framecount) {
    ent->client->ps.jumppad_frame = 0;
    ent->client->ps.jumppad_ent = 0;
  }
}

/*
 =================
 SpectatorThink
 =================
 */
void SpectatorThink(gentity_t *ent, usercmd_t *ucmd) {
  pmove_t pm;
  gclient_t *client;

  client = ent->client;

  if (client->sess.spectatorState != SPECTATOR_FOLLOW) {
    client->ps.pm_type = PM_SPECTATOR;
    client->ps.speed = 400; // faster than normal

    // set up for pmove
    memset(&pm, 0, sizeof(pm));
    pm.ps = &client->ps;
    pm.cmd = *ucmd;
    pm.tracemask = MASK_PLAYERSOLID & ~CONTENTS_BODY; // spectators can fly through bodies
    pm.trace = trap_Trace;
    pm.pointcontents = trap_PointContents;

    // perform a pmove
    Pmove(&pm);
    // save results of pmove
    VectorCopy(client->ps.origin, ent->s.origin);

    G_TouchTriggers(ent);
    trap_UnlinkEntity(ent);
  }

  client->oldbuttons = client->buttons;
  client->buttons = ucmd->buttons;

  // attack button cycles through spectators
  if ((client->buttons & BUTTON_ATTACK) && !(client->oldbuttons & BUTTON_ATTACK)) {
    Cmd_FollowCycle_f(ent, 1);
  }
}

/*
 =================
 ClientInactivityTimer

 Returns qfalse if the client is dropped
 =================
 */
qboolean ClientInactivityTimer(gclient_t *client) {
  if (!g_inactivity.integer) {
    // give everyone some time, so if the operator sets g_inactivity during
    // gameplay, everyone isn't kicked
    client->inactivityTime = level.time + 60 * 1000;
    client->inactivityWarning = qfalse;
  } else if (client->pers.cmd.forwardmove || client->pers.cmd.rightmove || client->pers.cmd.upmove || (client->pers.cmd.buttons & BUTTON_ATTACK)) {
    client->inactivityTime = level.time + g_inactivity.integer * 1000;
    client->inactivityWarning = qfalse;
  } else if (!client->pers.localClient) {
    if (level.time > client->inactivityTime) {
      trap_DropClient(client - level.clients, "Dropped due to inactivity");
      return qfalse;
    }
    if (level.time > client->inactivityTime - 10000 && !client->inactivityWarning) {
      client->inactivityWarning = qtrue;
      trap_SendServerCommand(client - level.clients, "cp \"^1Ten seconds until inactivity drop!\n\"");
    }
  }
  return qtrue;
}

/*
 ==================
 ClientTimerActions

 Actions that happen once a second
 ==================
 */
void ClientTimerActions(gentity_t *ent, int msec) {
  gclient_t *client;

  client = ent->client;
  client->timeResidual += msec;

  while (client->timeResidual >= 1000) {
    client->timeResidual -= 1000;
    if (ent->health > client->ps.stats[STAT_MAX_HEALTH]) {
      ent->health = 100;
    }

    if (client->ps.stats[STAT_ARMOR] > client->ps.stats[STAT_MAX_HEALTH]) {
      client->ps.stats[STAT_ARMOR] = 100;
    }
  }
}

/*
 ====================
 ClientIntermissionThink
 ====================
 */
void ClientIntermissionThink(gclient_t *client) {
  client->ps.eFlags &= ~EF_TALK;
  client->ps.eFlags &= ~EF_FIRING;

  // the level will exit when everyone wants to or after timeouts

  // swap and latch button actions
  client->oldbuttons = client->buttons;
  client->buttons = client->pers.cmd.buttons;
  if (client->buttons & (BUTTON_ATTACK | BUTTON_USE_HOLDABLE) & (client->oldbuttons ^ client->buttons)) {
    // this used to be an ^1 but once a player says ready, it should stick
    client->readyToExit = 1;
  }
}

/*
 ================
 ClientEvents

 Events will be passed on to the clients for presentation,
 but any server game effects are handled here
 ================
 */
void ClientEvents(gentity_t *ent, int oldEventSequence) {
  int i, j;
  int event;
  gclient_t *client;
  int damage;
  vec3_t dir;
  vec3_t origin, angles;
  //	qboolean	fired;
  gitem_t *item;
  gentity_t *drop;
  float f;
  int factor = 100;

  client = ent->client;

  if (oldEventSequence < client->ps.eventSequence - MAX_PS_EVENTS) {
    oldEventSequence = client->ps.eventSequence - MAX_PS_EVENTS;
  }

  for (i = oldEventSequence; i < client->ps.eventSequence; i++) {
    event = client->ps.events[i & (MAX_PS_EVENTS - 1)];

    switch (event) {
      case EV_FALL_SHORT:
      case EV_FALL_MEDIUM:
      case EV_FALL_FAR:
        if (ent->s.eType != ET_PLAYER) {
          break; // not in the player model
        }
        if (g_dmflags.integer & DF_NO_FALLING) {
          break;
        }
        if (ent->flags & FL_GODMODE) {
          return;
        }
        //Com_Printf("delta = %i\n", ent->client->ps.fallDelta);
        damage = ent->client->ps.fallDelta;
        f = (float) (ent->client->ps.legsfactor / 10);
        if (f < 1.0) {
          f = 1.0;
        }
        f += (float) damage / 100;
        VectorSet(dir, 0, 0, 1);
        ent->client->ps.legsfactor = (int) (f * 10);
        ent->pain_debounce_time = level.time + 200; // no normal pain sound
        G_Damage(ent, NULL, NULL, NULL, NULL, damage, 0, MOD_FALLING);
        if (ent->client->ps.powerups[PW_ADRENALINE] > 0) {
          factor /= 2;
        }
        ent->client->ps.jumpCooldown = ent->client->ps.levelTime + (damage * factor);
        break;

      case EV_FIRE_WEAPON:
        FireWeapon(ent);
        break;

      case EV_USE_ITEM1: // teleporter
        item = NULL;
        j = 0;

        if (item) {
          drop = Drop_Item(ent, item, 0);
          // decide how many seconds it has left
          drop->count = (ent->client->ps.powerups[j] - level.time) / 1000;
          if (drop->count < 1) {
            drop->count = 1;
          }

          ent->client->ps.powerups[j] = 0;
        }

        SelectSpawnPoint(ent->client->ps.origin, origin, angles, qfalse, qfalse, qfalse, qfalse);
        TeleportPlayer(ent, origin, angles);
        break;

      case EV_USE_ITEM2: // medkit
        ent->health = ent->client->ps.stats[STAT_MAX_HEALTH];

        break;

      default:
        break;
    }
  }

}

/*
 =============
 ThrowWeapon
 WEAPONDROP
 XRAY FMJ
 =============
 */

void ThrowWeapon(gentity_t *ent) {
  gclient_t *client;
  usercmd_t *ucmd;
  gitem_t *xr_item;
  gentity_t *xr_drop;
  byte i;
  qboolean dead;
  int ammo, clipammo;

  client = ent->client;
  ucmd = &ent->client->pers.cmd;

  dead = client->ps.stats[STAT_HEALTH] > 0;

  if (!dead) {
    if (client->ps.weaponstate != WEAPON_READY) {
      return;
    }
    if (client->ps.weapon == WP_KNIFE || client->ps.weapon == WP_NONE || client->ps.weapon == WP_HANDS || (ucmd->buttons & BUTTON_ATTACK)) {
      return;
    }
  }

  xr_item = BG_FindItemForWeapon(client->ps.weapon);

  //amount = client->ps.ammo[client->ps.weapon]; // XRAY save amount
  clipammo = client->ps.ammo[client->ps.weapon];
  ammo = client->clipammo[client->ps.weapon];
  if (ammo == 0) {
    ammo = -1;
  }
  if (clipammo == 0) {
    clipammo = -1;
  }
  client->ps.ammo[client->ps.weapon] = 0;
  client->clipammo[client->ps.weapon] = 0;

  client->ps.stats[STAT_WEAPONS] &= ~(1 << client->ps.weapon);
  client->ps.weapon = WP_NONE;
  for (i = WP_NUM_WEAPONS - 1; i > 0; i--) {
    if (client->ps.stats[STAT_WEAPONS] & (1 << i)) {
      client->ps.weapon = i;
      break;
    }
  }
  client->ps.weaponTime = 300;

  xr_drop = dropWeapon(ent, xr_item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM);
  xr_drop->ammo = ammo;
  xr_drop->clipammo = clipammo;
  //Com_Printf("dn: ammo: %i clipammo: %i\n", xr_drop->ammo, xr_drop->clipammo);
}

void BotTestSolid(vec3_t origin);

/*
 ==============
 SendPendingPredictableEvents
 ==============
 */
void SendPendingPredictableEvents(playerState_t *ps) {
  gentity_t *t;
  int event, seq;
  int extEvent, number;

  // if there are still events pending
  if (ps->entityEventSequence < ps->eventSequence) {
    // create a temporary entity for this event which is sent to everyone
    // except the client who generated the event
    seq = ps->entityEventSequence & (MAX_PS_EVENTS - 1);
    event = ps->events[seq] | ((ps->entityEventSequence & 3) << 8);
    // set external event to zero before calling BG_PlayerStateToEntityState
    extEvent = ps->externalEvent;
    ps->externalEvent = 0;
    // create temporary entity for event
    t = G_TempEntity(ps->origin, event);
    number = t->s.number;
    BG_PlayerStateToEntityState(ps, &t->s, qtrue);
    t->s.number = number;
    t->s.eType = ET_EVENTS + event;
    t->s.eFlags |= EF_PLAYER_EVENT;
    t->s.otherEntityNum = ps->clientNum;
    // send to everyone except the client who generated the event
    t->r.svFlags |= SVF_NOTSINGLECLIENT;
    t->r.singleClient = ps->clientNum;
    // set back external event
    ps->externalEvent = extEvent;
  }
}

static void G_ExplodeClient(gclient_t *client, gentity_t *ent) {
  ent->client->ps.weaponTime = 200;
  ent->client->ps.weaponstate = WEAPON_READY;
  // dont splode when there are no nades :X
  if (client->clipammo[WP_HE] > 0) {
    FireGrenade(ent, 0, MOD_NADELOVE);
    client->clipammo[WP_HE] = 0;
  } else {
    return;
  }
}

/*
 ==============
 ClientThink

 This will be called once for each client frame, which will
 usually be a couple times for each server frame on fast clients.

 If "g_synchronousClients 1" is set, this will be called exactly
 once for each server frame, which makes for smooth demo recording.
 ==============
 */
void ClientThink_real(gentity_t *ent) {
  gclient_t *client;
  pmove_t pm;
  int oldEventSequence;
  int msec;
  int adrenaline, bleed;
  usercmd_t *ucmd;

  client = ent->client;

  // don't think if the client is not yet connected (and thus not yet spawned in)
  if (client->pers.connected != CON_CONNECTED) {
    return;
  }
  // mark the time, so the connection sprite can be removed
  ucmd = &ent->client->pers.cmd;

  // sanity check the command time to prevent speedup cheating
  if (ucmd->serverTime > level.time + 200) {
    ucmd->serverTime = level.time + 200;
    //		G_Printf("serverTime <<<<<\n" );
  }
  if (ucmd->serverTime < level.time - 1000) {
    ucmd->serverTime = level.time - 1000;
    //		G_Printf("serverTime >>>>>\n" );
  }

  msec = ucmd->serverTime - client->ps.commandTime;
  // following others may result in bad times, but we still want
  // to check for follow toggles
  if (msec < 1 && client->sess.spectatorState != SPECTATOR_FOLLOW) {
    return;
  }
  if (msec > 200) {
    msec = 200;
  }

  if (pmove_msec.integer < 8) {
    trap_Cvar_Set("pmove_msec", "8");
  } else if (pmove_msec.integer > 33) {
    trap_Cvar_Set("pmove_msec", "33");
  }

  if (pmove_fixed.integer || client->pers.pmoveFixed) {
    ucmd->serverTime = ((ucmd->serverTime + pmove_msec.integer - 1) / pmove_msec.integer) * pmove_msec.integer;
    //if (ucmd->serverTime - client->ps.commandTime <= 0)
    //	return;
  }

  //
  // check for exiting intermission
  //
  if (level.intermissiontime) {
    ClientIntermissionThink(client);
    return;
  }

  // spectators don't do much
  if (client->sess.sessionTeam == TEAM_SPECTATOR) {
    if (client->sess.spectatorState == SPECTATOR_SCOREBOARD) {
      return;
    }
    SpectatorThink(ent, ucmd);
    return;
  }

  // check for inactivity timer, but never drop the local client of a non-dedicated server
  if (!ClientInactivityTimer(client)) {
    return;
  }

  // clear the rewards if time
  if (level.time > client->rewardTime) {
    client->ps.eFlags &= ~(EF_AWARD_IMPRESSIVE | EF_AWARD_EXCELLENT | EF_AWARD_GAUNTLET);
  }

  if (client->noclip) {
    client->ps.pm_type = PM_NOCLIP;
  } else if (client->ps.stats[STAT_HEALTH] <= 0) {
    client->ps.pm_type = PM_DEAD;
    if (g_gametype.integer == GT_FREEZETAG) {
      client->ps.pm_type = PM_FROZEN;
    }
  } else if (level.cutscene) {
    client->ps.pm_type = PM_CUTSCENE;
  } else {
    client->ps.pm_type = PM_NORMAL;
  }

  client->ps.gravity = g_gravity.value;

  // set speed
  //client->ps.speed = g_speed.value; // LEGSHOTS

  adrenaline = client->ps.powerups[PW_ADRENALINE] > level.time;

  //Com_Printf("legsfactor = %i\n", client->ps.legsfactor);
  if (adrenaline) {
    client->ps.speed = client->ps.maxspeed * 1.3;
  } else {
    client->ps.speed = (int) ((float) client->ps.maxspeed / ((float) client->ps.legsfactor / 10));
  }

  client->ps.speed += client->ps.sprintAdd;

  bleed = client->ps.powerups[PW_BLEED];
  if (client->ps.wounds > 0 && bleed <= level.time) {
    G_Damage(ent, NULL, NULL, NULL, NULL, 1, DAMAGE_NO_KNOCKBACK | DAMAGE_NO_ARMOR, MOD_BLEED);
    client->ps.powerups[PW_BLEED] = level.time + (BLEEDTIME / client->ps.wounds);
  }

  ent->client->ps.levelTime = level.time;

  if (client->ps.grenadetime <= ent->client->ps.levelTime) {
    if (client->ps.grenadetime != -1337) {
      G_ExplodeClient(client, ent);
      client->ps.grenadetime = -1337;
    }
  }

  // TODO move to botlib
  if (ent->r.svFlags & SVF_BOT) {
    int ammo;
    ammo = client->clipammo[client->ps.weapon];
    //Com_Printf("ammo = %i\n", ammo);
    if (ammo == 0) {
      if (!Cmd_Reload(ent)) {
        //trap_EA_SelectWeapon(ent->s.clientNum, client->ps.weapon - 1);
        //trap_EA_Say(ent->s.clientNum, "no ammo D:\n");
      }
    }
  }

  // set up for pmove
  oldEventSequence = client->ps.eventSequence;

  memset(&pm, 0, sizeof(pm));

  if (ent->flags & FL_FORCE_GESTURE) {
    ent->flags &= ~FL_FORCE_GESTURE;
    ent->client->pers.cmd.buttons |= BUTTON_GESTURE;
  }

  pm.ps = &client->ps;
  pm.cmd = *ucmd;
  if (pm.ps->pm_type == PM_DEAD) {
    pm.tracemask = MASK_PLAYERSOLID & ~CONTENTS_BODY;
  } else if (ent->r.svFlags & SVF_BOT) {
    pm.tracemask = MASK_PLAYERSOLID | CONTENTS_BOTCLIP;
  } else {
    pm.tracemask = MASK_PLAYERSOLID;
  }
  pm.trace = trap_Trace;
  pm.pointcontents = trap_PointContents;
  pm.debugLevel = g_debugMove.integer;
  pm.noFootsteps = (g_dmflags.integer & DF_NO_FOOTSTEPS) > 0;

  pm.pmove_fixed = pmove_fixed.integer | client->pers.pmoveFixed;
  pm.pmove_msec = pmove_msec.integer;

  VectorCopy(client->ps.origin, client->oldOrigin);

  Pmove(&pm);

  // save results of pmove
  if (ent->client->ps.eventSequence != oldEventSequence) {
    ent->eventTime = level.time;
  }
  if (g_smoothClients.integer) {
    BG_PlayerStateToEntityStateExtraPolate(&ent->client->ps, &ent->s, ent->client->ps.commandTime, qtrue);
  } else {
    BG_PlayerStateToEntityState(&ent->client->ps, &ent->s, qtrue);
  }
  SendPendingPredictableEvents(&ent->client->ps);

  if (!(ent->client->ps.eFlags & EF_FIRING)) {
    client->fireHeld = qfalse; // for grapple
  }

  // use the snapped origin for linking so it matches client predicted versions
  VectorCopy(ent->s.pos.trBase, ent->r.currentOrigin);

  VectorCopy(pm.mins, ent->r.mins);
  VectorCopy(pm.maxs, ent->r.maxs);

  ent->waterlevel = pm.waterlevel;
  ent->watertype = pm.watertype;

  // execute client events
  ClientEvents(ent, oldEventSequence);

  // link entity now, after any personal teleporters have been used
  trap_LinkEntity(ent);
  if (!ent->client->noclip) {
    G_TouchTriggers(ent);
  }

  // NOTE: now copy the exact origin over otherwise clients can be snapped into solid
  VectorCopy(ent->client->ps.origin, ent->r.currentOrigin);

  //test for solid areas in the AAS file
  BotTestAAS(ent->r.currentOrigin);

  // touch other objects
  ClientImpacts(ent, &pm);

  // save results of triggers and client events
  if (ent->client->ps.eventSequence != oldEventSequence) {
    ent->eventTime = level.time;
  }

  // swap and latch button actions
  client->oldbuttons = client->buttons;
  client->buttons = ucmd->buttons;
  client->latched_buttons |= client->buttons & ~client->oldbuttons;

  // FIXME
  /*if (client->ps.stats[STAT_HEALTH] > 0 && client->ps.stats[STAT_HEALTH] <= 20 && (level.time % 53 == 0) && (client->ps.powerups[PW_ADRENALINE] == 0)) {
   P_KickBack(ent, (int) crandom()*10, (int) crandom()*10, 3);
   }*/

  if (level.roundState == ROUND_SPAWNING && level.numSpawnedClients < level.numPlayingClients) {
    //    if (client->ps.stats[STAT_HEALTH] > 0) {
    //      Com_Printf("killing client\n");
    //      G_Damage(ent, NULL, NULL, NULL, NULL, 10000, DAMAGE_NO_PROTECTION, MOD_SUICIDE);
    //    }
    Com_Printf("respawning client, stat is %i/%i\n", level.numSpawnedClients, level.numPlayingClients);
    respawn(ent);
    return;
  }

  // check for respawning
  if (client->ps.stats[STAT_HEALTH] <= 0) {
    // wait for the attack button to be pressed
    if (level.time > client->respawnTime && g_gametype.integer != GT_FREEZETAG && g_gametype.integer != GT_ASSASSINS) {
      if (g_gametype.integer == GT_TEAMSURVIVOR) {
        if (level.roundState != ROUND_SPAWNING || level.roundState != ROUND_WARMUP) {
          return;
        }
      }
      // forcerespawn is to prevent users from waiting out powerups
      if (g_forcerespawn.integer > 0 && (level.time - client->respawnTime) > g_forcerespawn.integer * 1000) {
        respawn(ent);
        return;
      }

      // pressing attack or use is the normal respawn method
      if (ucmd->buttons & (BUTTON_ATTACK | BUTTON_USE_HOLDABLE)) {
        respawn(ent);
      }
    }
    return;
  } else if (g_gametype.integer == GT_TEAMSURVIVOR && level.roundState == ROUND_SPAWNING) {
    respawn(ent);
    return;
  }

  // perform once-a-second actions
  ClientTimerActions(ent, msec);
}

/*
 ==================
 ClientThink

 A new command has arrived from the client
 ==================
 */
void ClientThink(int clientNum) {
  gentity_t *ent;

  ent = g_entities + clientNum;
  trap_GetUsercmd(clientNum, &ent->client->pers.cmd);

  // mark the time we got info, so we can display the
  // phone jack if they don't get any for a while
  ent->client->lastCmdTime = level.time;

  if (!(ent->r.svFlags & SVF_BOT) && !g_synchronousClients.integer) {
    ClientThink_real(ent);
  }
}

void G_RunClient(gentity_t *ent) {
  if (!(ent->r.svFlags & SVF_BOT) && !g_synchronousClients.integer) {
    return;
  }
  ent->client->pers.cmd.serverTime = level.time;
  ClientThink_real(ent);
}

/*
 ==================
 SpectatorClientEndFrame

 ==================
 */
void SpectatorClientEndFrame(gentity_t *ent) {
  gclient_t *cl;

  // if we are doing a chase cam or a remote view, grab the latest info
  if (ent->client->sess.spectatorState == SPECTATOR_FOLLOW) {
    int clientNum, flags;

    clientNum = ent->client->sess.spectatorClient;

    // team follow1 and team follow2 go to whatever clients are playing
    if (clientNum == -1) {
      clientNum = level.follow1;
    } else if (clientNum == -2) {
      clientNum = level.follow2;
    }
    if (clientNum >= 0) {
      cl = &level.clients[clientNum];
      if (cl->pers.connected == CON_CONNECTED && cl->sess.sessionTeam != TEAM_SPECTATOR) {
        flags = (cl->ps.eFlags & ~(EF_VOTED | EF_TEAMVOTED)) | (ent->client->ps.eFlags & (EF_VOTED | EF_TEAMVOTED));
        ent->client->ps = cl->ps;
        ent->client->ps.pm_flags |= PMF_FOLLOW;
        ent->client->ps.eFlags = flags;
        return;
      } else {
        // drop them to free spectators unless they are dedicated camera followers
        if (ent->client->sess.spectatorClient >= 0) {
          ent->client->sess.spectatorState = SPECTATOR_FREE;
          ClientBegin(ent->client - level.clients);
        }
      }
    }
  }

  if (ent->client->sess.spectatorState == SPECTATOR_SCOREBOARD) {
    ent->client->ps.pm_flags |= PMF_SCOREBOARD;
  } else {
    ent->client->ps.pm_flags &= ~PMF_SCOREBOARD;
  }
}

/*
 ==============
 ClientEndFrame

 Called at the end of each server frame for each connected client
 A fast client will have multiple ClientThink for each ClientEdFrame,
 while a slow client may have multiple ClientEndFrame between ClientThink.
 ==============
 */
void ClientEndFrame(gentity_t *ent) {
  int i;
  clientPersistant_t *pers;

  if (ent->client->sess.sessionTeam == TEAM_SPECTATOR) {
    SpectatorClientEndFrame(ent);
    return;
  }

  pers = &ent->client->pers;

  // turn off any expired powerups
  for (i = 0; i < MAX_POWERUPS; i++) {
    if (i == PW_SNOWBOARD) {
      continue;
    }
    if (ent->client->ps.powerups[i] < level.time) {
      ent->client->ps.powerups[i] = 0;
    }
  }
  if (ent->client->ps.powerups[PW_ADRENALINE] < level.time) {
    ent->client->ps.powerups[PW_ADRENALINE] = 0;
  }

  // save network bandwidth
#if 0
  if (!g_synchronousClients->integer && ent->client->ps.pm_type == PM_NORMAL) {
    // FIXME: this must change eventually for non-sync demo recording
    VectorClear(ent->client->ps.viewangles);
  }
#endif

  //
  // If the end of unit layout is displayed, don't give
  // the player any normal movement attributes
  //
  if (level.intermissiontime) {
    return;
  }

  // burn from lava, etc
  P_WorldEffects(ent);

  // apply all the damage taken this frame
  P_DamageFeedback(ent);

  // add the EF_CONNECTION flag if we haven't gotten commands recently
  if (level.time - ent->client->lastCmdTime > 1000) {
    ent->s.eFlags |= EF_CONNECTION;
  } else {
    ent->s.eFlags &= ~EF_CONNECTION;
  }

  //Update the Ammo Amount in weapon RELOADING
  ent->client->ps.stats[STAT_AMMO] = ent->client->clipammo[ent->client->ps.weapon];

  ent->client->ps.stats[STAT_HEALTH] = ent->health; // FIXME: get rid of ent->health...

  G_SetClientSound(ent);

  // set the latest infor
  if (g_smoothClients.integer) {
    BG_PlayerStateToEntityStateExtraPolate(&ent->client->ps, &ent->s, ent->client->ps.commandTime, qtrue);
  } else {
    BG_PlayerStateToEntityState(&ent->client->ps, &ent->s, qtrue);
  }
  SendPendingPredictableEvents(&ent->client->ps);

  // set the bit for the reachability area the client is currently in
  //	i = trap_AAS_PointReachabilityAreaIndex( ent->client->ps.origin );
  //	ent->client->areabits[i >> 3] |= 1 << (i & 7);
}

