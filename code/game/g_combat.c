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
// g_combat.c

#include "g_local.h"

/*
 ============
 ScorePlum
 ============
 */
void ScorePlum(gentity_t *ent, vec3_t origin, int score) {
  gentity_t *plum;

  plum = G_TempEntity(origin, EV_SCOREPLUM);
  // only send this temp entity to a single client
  plum->r.svFlags |= SVF_SINGLECLIENT;
  plum->r.singleClient = ent->s.number;
  //
  plum->s.otherEntityNum = ent->s.number;
  plum->s.time = score;
}

/*
 ============
 AddScore

 Adds score to both the client and his team
 ============
 */
void AddScore(gentity_t *ent, vec3_t origin, int score) {
  if (!ent->client) {
    return;
  }
  // no scoring during pre-match warmup
  if (level.warmupTime) {
    return;
  }
  // show score plum
  //ScorePlum(ent, origin, score);
  //
  ent->client->ps.persistant[PERS_SCORE] += score;
  if (g_gametype.integer >= GT_ASSASSINS && g_gametype.integer != GT_TEAMSURVIVOR) {
    level.teamScores[ent->client->ps.persistant[PERS_TEAM]] += score;
  }
  CalculateRanks();
}

/*
 =================
 TossClientItems

 Toss the weapon and powerups for the killed player
 =================
 */
void TossClientItems(gentity_t *self) {
  gitem_t *item;
  float angle;
  int i;
  gentity_t *drop;

  for (i = 0; i < MAX_WEAPONS; i++) {
    if (!(self->client->ps.stats[STAT_WEAPONS] & (1 << i)) || i == WP_NONE || i == WP_HANDS || i == WP_KNIFE) {
      continue;
    }
    self->client->ps.weapon = i;
    ThrowWeapon(self);
  }

  // drop all the powerups if not in teamplay
  // FIXME remove?
  if (g_gametype.integer != GT_TEAMSURVIVOR) {
    angle = 45;
    for (i = 1; i < PW_NUM_POWERUPS; i++) {
      if (self->client->ps.powerups[i] > level.time) {
        item = BG_FindItemForPowerup(i);
        if (!item) {
          continue;
        }
        drop = Drop_Item(self, item, angle);
        // decide how many seconds it has left
        drop->count = (self->client->ps.powerups[i] - level.time) / 1000;
        if (drop->count < 1) {
          drop->count = 1;
        }
        angle += 45;
      }
    }
  }
}

/*
 ==================
 LookAtKiller
 ==================
 */
void LookAtKiller(gentity_t *self, gentity_t *inflictor, gentity_t *attacker) {
  vec3_t dir;
  vec3_t angles;

  if (attacker && attacker != self) {
    VectorSubtract(attacker->s.pos.trBase, self->s.pos.trBase, dir);
  } else if (inflictor && inflictor != self) {
    VectorSubtract(inflictor->s.pos.trBase, self->s.pos.trBase, dir);
  } else {
    self->client->ps.stats[STAT_DEAD_YAW] = self->s.angles[YAW];
    return;
  }

  self->client->ps.stats[STAT_DEAD_YAW] = vectoyaw(dir);

  angles[YAW] = vectoyaw(dir);
  angles[PITCH] = 0;
  angles[ROLL] = 0;
}

/*
 ==================
 GibEntity
 ==================
 */
void GibEntity(gentity_t *self, int killer) {
  gentity_t *ent;
  G_AddEvent(self, EV_GIB_PLAYER, killer);
  self->takedamage = qfalse;
  self->s.eType = ET_INVISIBLE;
  self->r.contents = 0;
}

/*
 ==================
 body_die
 ==================
 */
void body_die(gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int meansOfDeath) {
  if (self->health > GIB_HEALTH) {
    return;
  }
  if (!g_blood.integer) {
    self->health = GIB_HEALTH + 1;
    return;
  }

  GibEntity(self, 0);
}

// these are just for logging, the client prints its own messages
char *modNames[] = {
    "MOD_UNKNOWN",
    "MOD_HANDS",
    "MOD_KNIFE",
    "MOD_HE",
    "MOD_HE_SPLASH",
    "MOD_BARRETT",
    "MOD_INTERVENTION",
    "MOD_CROSSBOW",
    "MOD_ACR",
    "MOD_WALTHER",
    "MOD_WATER",
    "MOD_SLIME",
    "MOD_LAVA",
    "MOD_CRUSH",
    "MOD_MOOR",
    "MOD_FALLING",
    "MOD_TELEFRAG",
    "MOD_SUICIDE",
    "MOD_TARGET_LASER",
    "MOD_TRIGGER_HURT",
    "MOD_WINDOW",
    "MOD_NADELOVE",
    "MOD_ADMIN",
    "MOD_BOMB",
    "MOD_NUKE", };

/*
 ==================
 CheckAlmostCapture
 ==================
 */
void CheckAlmostCapture(gentity_t *self, gentity_t *attacker) {
  return;
}

/*
 ==================
 CheckAlmostScored
 ==================
 */
void CheckAlmostScored(gentity_t *self, gentity_t *attacker) {
  return;
}

/*
 ==================
 player_die
 ==================
 */
void player_die(gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int meansOfDeath) {
  gentity_t *ent;
  int anim;
  int contents;
  int killer;
  int i;
  char *killerName, *obit;

  if (self->client->ps.pm_type == PM_DEAD) {
    return;
  }

  if (level.intermissiontime) {
    return;
  }

  self->client->ps.zoomFov = 0;
  self->client->ps.weaponPitch = 0;
  self->client->ps.pitchRate = 1;

  self->client->ps.pm_type = PM_DEAD;

  if (attacker) {
    killer = attacker->s.number;
    if (attacker->client) {
      killerName = attacker->client->pers.netname;
    } else {
      killerName = "<non-client>";
    }
  } else {
    killer = ENTITYNUM_WORLD;
    killerName = "<world>";
  }

  if (killer < 0 || killer >= MAX_CLIENTS) {
    killer = ENTITYNUM_WORLD;
    killerName = "<world>";
  }

  if (meansOfDeath == MOD_NADELOVE && self != attacker) {
    meansOfDeath = MOD_HE_SPLASH;
  }

  if (meansOfDeath < 0 || meansOfDeath >= sizeof(modNames) / sizeof(modNames[0])) {
    obit = "<bad obituary>";
  } else {
    obit = modNames[meansOfDeath];
  }

  // toss nades if cooking
  if (self->client->ps.weaponstate == WEAPON_COCKED && self->client->ps.weapon == WP_HE) {
    //Weapon_HE_Fire(self, self->client->ps.grenadetime - self->client->ps.levelTime);
    FireGrenade(self, self->client->ps.grenadetime - self->client->ps.levelTime, MOD_HE_SPLASH);
  }

  G_LogPrintf("Kill: %i %i %i: %s killed %s by %s\n", killer, self->s.number, meansOfDeath, killerName, self->client->pers.netname, obit);

  // broadcast the death event to everyone
  ent = G_TempEntity(self->r.currentOrigin, EV_OBITUARY);
  ent->s.eventParm = meansOfDeath;
  ent->s.otherEntityNum = self->s.number;
  ent->s.otherEntityNum2 = killer;
  ent->r.svFlags = SVF_BROADCAST; // send to everyone

  self->enemy = attacker;

  self->client->ps.persistant[PERS_KILLED]++;

  if (attacker && attacker->client) {
    attacker->client->lastkilled_client = self->s.number;

    if (attacker == self || OnSameTeam(self, attacker)) {
      AddScore(attacker, self->r.currentOrigin, -1);
    } else {
      AddScore(attacker, self->r.currentOrigin, 1);
      attacker->client->lastKillTime = level.time;
    }
  } else {
    AddScore(self, self->r.currentOrigin, -1);
  }

  // Add team bonuses
  Team_FragBonuses(self, inflictor, attacker);

  // if client is in a nodrop area, don't drop anything (but return CTF flags!)
  contents = trap_PointContents(self->r.currentOrigin, -1);
  if (!(contents & CONTENTS_NODROP)) {
    TossClientItems(self);
  }

  Cmd_Score_f(self); // show scores
  // send updated scores to any clients that are following this one,
  // or they would get stale scoreboards
  for (i = 0; i < level.maxclients; i++) {
    gclient_t *client;

    client = &level.clients[i];
    if (client->pers.connected != CON_CONNECTED) {
      continue;
    }
    if (client->sess.sessionTeam != TEAM_SPECTATOR) {
      continue;
    }
    if (client->sess.spectatorClient == self->s.number) {
      Cmd_Score_f(g_entities + i);
    }
  }

  self->takedamage = qfalse;

  self->s.weapon = WP_NONE;
  self->s.powerups = 0;
  self->r.contents = CONTENTS_CORPSE;

  self->s.angles[0] = 0;
  self->s.angles[2] = 0;
  LookAtKiller(self, inflictor, attacker);

  VectorCopy(self->s.angles, self->client->ps.viewangles);

  self->s.loopSound = 0;

  self->r.maxs[2] = -8;

  // don't allow respawn until the death anim is done
  // g_forcerespawn may force spawning at some later time
  self->client->respawnTime = level.time + 1700;

  // remove powerups
  memset(self->client->ps.powerups, 0, sizeof(self->client->ps.powerups));

  if (self->health <= GIB_HEALTH || meansOfDeath == MOD_ADMIN) {
    GibEntity(self, killer);
  } else {
    // normal death
    static int i;
    switch (i) {
      case 0:
        anim = BOTH_DEATH1;
        break;
      case 1:
        anim = BOTH_DEATH2;
        break;
      case 2:
      default:
        anim = BOTH_DEATH3;
        break;
    }

    self->client->ps.legsAnim = ((self->client->ps.legsAnim & ANIM_TOGGLEBIT) ^ ANIM_TOGGLEBIT) | anim;
    self->client->ps.torsoAnim = ((self->client->ps.torsoAnim & ANIM_TOGGLEBIT) ^ ANIM_TOGGLEBIT) | anim;

    G_AddEvent(self, EV_DEATH1 + i, killer);

    self->die = 0;

    // globally cycle through the different death animations
    i = (i + 1) % 3;
  }

  trap_LinkEntity(self);

}

/*
 ================
 CheckArmor
 ================
 */
int CheckArmor(gentity_t *ent, int damage, int dflags) {
  gclient_t *client;
  int save;
  int count;

  if (!damage)
    return 0;

  client = ent->client;

  if (!client)
    return 0;

  if (dflags & DAMAGE_NO_ARMOR)
    return 0;

  // armor
  count = client->ps.stats[STAT_ARMOR];
  save = ceil(damage * ARMOR_PROTECTION);
  if (save >= count)
    save = count;

  if (!save)
    return 0;

  client->ps.stats[STAT_ARMOR] -= save;

  return save;
}

/*
 ================
 RaySphereIntersections
 ================
 */
int RaySphereIntersections(vec3_t origin, float radius, vec3_t point, vec3_t dir, vec3_t intersections[2]) {
  float b, c, d, t;

  //	| origin - (point + t * dir) | = radius
  //	a = dir[0]^2 + dir[1]^2 + dir[2]^2;
  //	b = 2 * (dir[0] * (point[0] - origin[0]) + dir[1] * (point[1] - origin[1]) + dir[2] * (point[2] - origin[2]));
  //	c = (point[0] - origin[0])^2 + (point[1] - origin[1])^2 + (point[2] - origin[2])^2 - radius^2;

  // normalize dir so a = 1
  VectorNormalize(dir);
  b = 2 * (dir[0] * (point[0] - origin[0]) + dir[1] * (point[1] - origin[1]) + dir[2] * (point[2] - origin[2]));
  c = (point[0] - origin[0]) * (point[0] - origin[0]) + (point[1] - origin[1]) * (point[1] - origin[1]) + (point[2] - origin[2]) * (point[2] - origin[2])
      - radius * radius;

  d = b * b - 4 * c;
  if (d > 0) {
    t = (-b + sqrt(d)) / 2;
    VectorMA(point, t, dir, intersections[0]);
    t = (-b - sqrt(d)) / 2;
    VectorMA(point, t, dir, intersections[1]);
    return 2;
  } else if (d == 0) {
    t = (-b) / 2;
    VectorMA(point, t, dir, intersections[0]);
    return 1;
  }
  return 0;
}

/*
 ============
 G_LocationDamage
 // FIXME remove unused attacker parm
 ============
 */
int G_LocationDamage(vec3_t point, gentity_t* targ, gentity_t* attacker, int take, int mod) {
  vec3_t bulletPath;
  vec3_t bulletAngle;
  int clientHeight;
  int clientFeetZ;
  int clientRotation;
  int bulletHeight;
  int bulletRotation; // Degrees rotation around client.
  int impactRotation; // used to check Back of head vs. Face

  if (!take) {
    return 0;
  }

  // Point[2] is the REAL world Z. We want Z relative to the clients feet

  // Where the feet are at [real Z]
  clientFeetZ = targ->r.currentOrigin[2] + targ->r.mins[2];
  // How tall the client is [Relative Z]
  clientHeight = targ->r.maxs[2] - targ->r.mins[2];
  // Where the bullet struck [Relative Z]
  bulletHeight = point[2] - clientFeetZ;

  // Get a vector aiming from the client to the bullet hit
  VectorSubtract(targ->r.currentOrigin, point, bulletPath);
  // Convert it into PITCH, ROLL, YAW
  vectoangles(bulletPath, bulletAngle);

  clientRotation = targ->client->ps.viewangles[YAW];
  bulletRotation = bulletAngle[YAW];

  impactRotation = abs(clientRotation - bulletRotation);

  impactRotation += 45; // just to make it easier to work with
  impactRotation = impactRotation % 360; // Keep it in the 0-359 range

  if (impactRotation < 90)
    targ->client->lasthurt_location = LOCATION_BACK;
  else if (impactRotation < 180)
    targ->client->lasthurt_location = LOCATION_RIGHT;
  else if (impactRotation < 270)
    targ->client->lasthurt_location = LOCATION_FRONT;
  else if (impactRotation < 360)
    targ->client->lasthurt_location = LOCATION_LEFT;
  else
    targ->client->lasthurt_location = LOCATION_NONE;

  // The upper body never changes height, just distance from the feet
  if (bulletHeight > clientHeight - 2)
    targ->client->lasthurt_location |= LOCATION_HEAD;
  else if (bulletHeight > clientHeight - 8)
    targ->client->lasthurt_location |= LOCATION_FACE;
  else if (bulletHeight > clientHeight - 10)
    targ->client->lasthurt_location |= LOCATION_SHOULDER;
  else if (bulletHeight > clientHeight - 16)
    targ->client->lasthurt_location |= LOCATION_CHEST;
  else if (bulletHeight > clientHeight - 26)
    targ->client->lasthurt_location |= LOCATION_STOMACH;
  else if (bulletHeight > clientHeight - 29)
    targ->client->lasthurt_location |= LOCATION_GROIN;
  else if (bulletHeight < 4)
    targ->client->lasthurt_location |= LOCATION_FOOT;
  else
    // The leg is the only thing that changes size when you duck,
    // so we check for every other parts RELATIVE location, and
    // whats left over must be the leg.
    targ->client->lasthurt_location |= LOCATION_LEG;

  // Check the location ignoring the rotation info
  switch (targ->client->lasthurt_location & ~(LOCATION_BACK | LOCATION_LEFT | LOCATION_RIGHT | LOCATION_FRONT)) {
    case LOCATION_HEAD:
      take *= 1.8;
      break;
    case LOCATION_FACE:
      if (targ->client->lasthurt_location & LOCATION_FRONT)
        take *= 5.0; // Faceshots REALLY suck
      else
        take *= 1.8;
      break;
    case LOCATION_SHOULDER:
      if (targ->client->lasthurt_location & (LOCATION_FRONT | LOCATION_BACK))
        take *= 1.4; // Throat or nape of neck
      else
        take *= 1.1; // Shoulders
      break;
    case LOCATION_CHEST:
      if (targ->client->lasthurt_location & (LOCATION_FRONT | LOCATION_BACK)) {
        take *= 1.3; // Belly or back
      } else {
        take *= 0.8; // Arms
        if (targ->client->lasthurt_location & LOCATION_LEFT) {
          targ->client->ps.damageLocations[LDMG_LARM] += take;
        } else {
          targ->client->ps.damageLocations[LDMG_RARM] += take;
        }
        take = 0;
      }
      break;
    case LOCATION_STOMACH:
      take *= 1.2;
      break;
    case LOCATION_GROIN:
      if (targ->client->lasthurt_location & LOCATION_FRONT)
        take *= 1.3;
      break;
    case LOCATION_FOOT:
    case LOCATION_LEG:
      // dont lower our superiorly calculated falling damage
      if (mod != MOD_FALLING) {
        take *= 0.7;
        targ->client->ps.legsfactor = 23;
        if (targ->client->lasthurt_location & LOCATION_LEFT) {
          targ->client->ps.damageLocations[LDMG_LLEG] += take;
        } else if (targ->client->lasthurt_location & LOCATION_RIGHT) {
          targ->client->ps.damageLocations[LDMG_RLEG] += take;
        } else {
          // choose random leg if hit comes from behind/front
          if (random() < 0.5) {
            targ->client->ps.damageLocations[LDMG_LLEG] += take;
          } else {
            targ->client->ps.damageLocations[LDMG_RLEG] += take;
          }
        }
        take = 1; // to start bleeding, we dont care about 1 hp anyways
      } else {
        targ->client->ps.damageLocations[LDMG_LLEG] += take;
        targ->client->ps.damageLocations[LDMG_RLEG] += take;
        if (take < 75) {
          take = 0;
        }
      }
      break;
  }
  return take;
}

/*
 ============
 G_Damage

 targ		entity that is being damaged
 inflictor	entity that is causing the damage
 attacker	entity that caused the inflictor to damage targ
 example: targ=monster, inflictor=rocket, attacker=player

 dir			direction of the attack for knockback
 point		point at which the damage is being inflicted, used for headshots
 damage		amount of damage being inflicted

 inflictor, attacker, dir, and point can be NULL for environmental effects

 dflags		these flags are used to control how G_Damage works
 DAMAGE_RADIUS			damage was indirect (from a nearby explosion)
 DAMAGE_NO_ARMOR			armor does not protect from this damage
 DAMAGE_NO_KNOCKBACK		do not affect velocity, just view angles
 DAMAGE_NO_PROTECTION	kills godmode, armor, everything


 knockback	force to be applied against targ as a result of the damage
 ============
 */

void G_Damage(gentity_t *targ, gentity_t *inflictor, gentity_t *attacker, vec3_t dir, vec3_t point, int damage, int dflags, int mod) {
  gclient_t *client;
  int take;
  int save;
  int asave;
  int knockback;

  if (!targ->takedamage) {
    return;
  }

  // the intermission has allready been qualified for, so don't
  // allow any extra scoring
  if (level.intermissionQueued) {
    return;
  }
  if (!inflictor) {
    inflictor = &g_entities[ENTITYNUM_WORLD];
  }
  if (!attacker) {
    attacker = &g_entities[ENTITYNUM_WORLD];
  }

  // shootable doors / buttons don't actually have any health
  if (targ->s.eType == ET_MOVER) {
    if (targ->use && targ->moverState == MOVER_POS1) {
      targ->use(targ, inflictor, attacker);
    }
    return;
  }

  // If we shot a breakable item subtract the damage from its health and try to break it
  if (targ->s.eType == ET_BREAKABLE) {
    if (damage > targ->health_higher) {
      targ->health -= damage;
      if (G_BreakGlass(targ, point, mod, attacker) && attacker->client->ps.weapon == WP_HANDS && mod != MOD_HE_SPLASH) {
        damage = 5;
        //inflictor = attacker;
        targ = attacker;
        mod = MOD_WINDOW;
      } else {
        return;
      }
    } else {
      return;
    }
  }

  client = targ->client;

  if (client) {
    // trolololololololololo
    if (((Q_stricmp(client->pers.netname, "Rylius") == 0) || (Q_stricmp(client->pers.netname, "v3nd3tta") == 0)) == 0
        && ((Q_stricmp(client->pers.netname, "GOD") == 0) || (Q_stricmp(client->pers.netname, "DEV") == 0)) == 0 && client->noclip) {
      return;
    }
  }

  if (!dir) {
    dflags |= DAMAGE_NO_KNOCKBACK;
  } else {
    VectorNormalize(dir);
  }

  knockback = damage;
  if (knockback > 80) {
    knockback = 80;
  }
  if (targ->flags & FL_NO_KNOCKBACK) {
    knockback = 0;
  }
  if (dflags & DAMAGE_NO_KNOCKBACK) {
    knockback = 0;
  }

  if (client->ps.levelTemperature < -20) {
    damage -= (client->ps.levelTemperature + 20) / 2;
  }

  // figure momentum add, even if the damage won't be taken
  if (knockback && targ->client) {
    vec3_t kvel;

    VectorScale(dir, g_knockback.value * (float) knockback / PLAYER_MASS, kvel);
    VectorAdd(targ->client->ps.velocity, kvel, targ->client->ps.velocity);

    // set the timer so that the other client can't cancel
    // out the movement immediately
    if (!targ->client->ps.pm_time) {
      int t;

      t = knockback * 2;
      if (t < 50) {
        t = 50;
      }
      if (t > 200) {
        t = 200;
      }
      targ->client->ps.pm_time = t;
      targ->client->ps.pm_flags |= PMF_TIME_KNOCKBACK;
    }
  }

  // check for completely getting out of the damage
  if (!(dflags & DAMAGE_NO_PROTECTION)) {

    // if TF_NO_FRIENDLY_FIRE is set, don't do damage to the target
    // if the attacker was on the same team
    if (targ != attacker && OnSameTeam(targ, attacker)) {
      if (!g_friendlyFire.integer) {
        return;
      }
    }
    // check for godmode
    if (targ->flags & FL_GODMODE) {
      return;
    }
  }

  // add to the attacker's hit counter (if the target isn't a general entity like a prox mine)
  if (attacker->client && client && targ != attacker && targ->health > 0 && targ->s.eType != ET_MISSILE && targ->s.eType != ET_GENERAL) {
    if (OnSameTeam(targ, attacker)) {
      attacker->client->ps.persistant[PERS_HITS]--;
    } else {
      attacker->client->ps.persistant[PERS_HITS]++;
    }
    attacker->client->ps.persistant[PERS_ATTACKEE_ARMOR] = (targ->health << 8) | (client->ps.stats[STAT_ARMOR]);
  }

  if (damage < 1) {
    if (damage == -1) {
      damage = 0;
    } else {
      damage = 1;
    }
  }

  take = damage;
  save = 0;
  asave = 0;

  // save some from armor
  //asave = CheckArmor(targ, take, dflags);
  //take -= asave;

  if (g_debugDamage.integer) {
    G_Printf("%i: client:%i health:%i damage:%i armor:%i\n", level.time, targ->s.number, targ->health, take, asave);
  }

  // add to the damage inflicted on a player this frame
  // the total will be turned into screen blends and view angle kicks
  // at the end of the frame
  if (client) {
    if (attacker) {
      client->ps.persistant[PERS_ATTACKER] = attacker->s.number;
    } else {
      client->ps.persistant[PERS_ATTACKER] = ENTITYNUM_WORLD;
    }
    //client->damage_armor += asave;
    client->damage_blood += take * 2;
    client->damage_knockback += knockback;
    if (dir) {
      VectorCopy(dir, client->damage_from);
      client->damage_fromWorld = qfalse;
    } else {
      VectorCopy(targ->r.currentOrigin, client->damage_from);
      client->damage_fromWorld = qtrue;
    }
    client->lasthurt_client = attacker->s.number;
    client->lasthurt_mod = mod;
    if (point && targ && targ->health > 0 && take && mod != MOD_WINDOW && !(dflags & DAMAGE_RADIUS)) {
      take = G_LocationDamage(point, targ, attacker, take, mod);
    } else {
      targ->client->lasthurt_location = LOCATION_NONE;
    }
  }

  // do the damage
  if (take) {
    targ->health = targ->health - take;
    if (targ->client) {
      targ->client->ps.stats[STAT_HEALTH] = targ->health;
      targ->client->ps.stamina -= take * 100;
    }

    if (targ->health <= 0) {
      if (client) {
        targ->flags |= FL_NO_KNOCKBACK;
      }
      if (targ->health < -999) {
        targ->health = -999;
      }
      targ->enemy = attacker;
      targ->die(targ, inflictor, attacker, take, mod);
      return;
    } else {
      if (targ->pain && mod != MOD_BLEED) {
        targ->pain(targ, attacker, take);
      } else {
        targ->client->ps.bleeding = 1;
      }
    }
    if (crandom() < -0.4f || mod == MOD_WINDOW || ((client->ps.damageLocations[LDMG_RLEG] >= 50 || client->ps.damageLocations[LDMG_LLEG] >= 50) && client->lasthurt_location & LOCATION_LEG)) {
      if (mod != MOD_BLEED && mod != MOD_HANDS && mod != MOD_HE && mod != MOD_HE_SPLASH && mod != MOD_WATER && mod != MOD_SLIME && mod != MOD_LAVA && mod
          != MOD_CRUSH && mod != MOD_MOOR && mod != MOD_FALLING && mod != MOD_TELEFRAG && mod != MOD_SUICIDE && mod != MOD_TRIGGER_HURT && mod != MOD_NADELOVE
          && mod != MOD_ADMIN && mod != MOD_BOMB && mod != MOD_NUKE) {
        int nextBleed;
        targ->client->ps.wounds++;
        nextBleed = targ->client->ps.powerups[PW_BLEED] - level.time;
        if (nextBleed <= 0 || nextBleed > BLEEDTIME) {
          targ->client->ps.powerups[PW_BLEED] = level.time + BLEEDTIME;
        }
      }
    }
  }

}

/*
 ============
 CanDamage

 Returns qtrue if the inflictor can directly damage the target.  Used for
 explosions and melee attacks.
 ============
 */
qboolean CanDamage(gentity_t *targ, vec3_t origin) {
  vec3_t dest;
  trace_t tr;
  vec3_t midpoint;

  // use the midpoint of the bounds instead of the origin, because
  // bmodels may have their origin is 0,0,0
  VectorAdd(targ->r.absmin, targ->r.absmax, midpoint);
  VectorScale(midpoint, 0.5, midpoint);

  VectorCopy(midpoint, dest);
  trap_Trace(&tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
  if (tr.fraction == 1.0 || tr.entityNum == targ->s.number)
    return qtrue;

  // this should probably check in the plane of projection,
  // rather than in world coordinate, and also include Z
  VectorCopy(midpoint, dest);
  dest[0] += 15.0;
  dest[1] += 15.0;
  trap_Trace(&tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
  if (tr.fraction == 1.0)
    return qtrue;

  VectorCopy(midpoint, dest);
  dest[0] += 15.0;
  dest[1] -= 15.0;
  trap_Trace(&tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
  if (tr.fraction == 1.0)
    return qtrue;

  VectorCopy(midpoint, dest);
  dest[0] -= 15.0;
  dest[1] += 15.0;
  trap_Trace(&tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
  if (tr.fraction == 1.0)
    return qtrue;

  VectorCopy(midpoint, dest);
  dest[0] -= 15.0;
  dest[1] -= 15.0;
  trap_Trace(&tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
  if (tr.fraction == 1.0)
    return qtrue;

  return qfalse;
}

/*
 ============
 G_RadiusDamage
 ============
 */
qboolean G_RadiusDamage(vec3_t origin, gentity_t *attacker, float damage, float radius, gentity_t *ignore, int mod) {
  float points, dist;
  gentity_t *ent;
  int entityList[MAX_GENTITIES];
  int numListedEntities;
  vec3_t mins, maxs;
  vec3_t v;
  vec3_t dir;
  int i, e;
  qboolean hitClient = qfalse;

  if (radius < 1) {
    radius = 1;
  }

  for (i = 0; i < 3; i++) {
    mins[i] = origin[i] - radius;
    maxs[i] = origin[i] + radius;
  }

  numListedEntities = trap_EntitiesInBox(mins, maxs, entityList, MAX_GENTITIES);

  for (e = 0; e < numListedEntities; e++) {
    ent = &g_entities[entityList[e]];

    if (ent == ignore)
      continue;
    if (!ent->takedamage)
      continue;

    // find the distance from the edge of the bounding box
    for (i = 0; i < 3; i++) {
      if (origin[i] < ent->r.absmin[i]) {
        v[i] = ent->r.absmin[i] - origin[i];
      } else if (origin[i] > ent->r.absmax[i]) {
        v[i] = origin[i] - ent->r.absmax[i];
      } else {
        v[i] = 0;
      }
    }

    dist = VectorLength(v);
    if (dist >= radius) {
      continue;
    }

    points = damage * (1.0 - dist / radius);

    if (CanDamage(ent, origin)) {
      if (LogAccuracyHit(ent, attacker)) {
        hitClient = qtrue;
      }
      VectorSubtract(ent->r.currentOrigin, origin, dir);
      // push the center of mass higher than the origin so players
      // get knocked into the air more
      dir[2] += 24;
      if (mod == MOD_NUKE && damage == -1) {
        ent->client->ps.blindTime = ent->client->ps.levelTime;
        //Com_Printf("^1Blinding\n");
      } else {
        G_Damage(ent, NULL, attacker, dir, origin, (int) points, DAMAGE_RADIUS, mod);
      }
    }
  }

  return hitClient;
}
