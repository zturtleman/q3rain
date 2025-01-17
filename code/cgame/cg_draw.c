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
// cg_draw.c -- draw all of the graphical elements during
// active (after loading) gameplay

#include "cg_local.h"

int drawTeamOverlayModificationCount = -1;

int sortedTeamPlayers[TEAM_MAXOVERLAY];
int numSortedTeamPlayers;

char systemChat[256];
char teamChat1[256];
char teamChat2[256];

killfeed_t killfeed;

/*
 ==============
 CG_DrawField

 Draws large numbers for status bar and powerups
 ==============
 */
static void CG_DrawField(int x, int y, int width, int value) {
  char num[16], *ptr;
  int l;
  int frame;

  if (width < 1) {
    return;
  }

  // draw number string
  if (width > 5) {
    width = 5;
  }

  switch (width) {
    case 1:
      value = value > 9 ? 9 : value;
      value = value < 0 ? 0 : value;
      break;
    case 2:
      value = value > 99 ? 99 : value;
      value = value < -9 ? -9 : value;
      break;
    case 3:
      value = value > 999 ? 999 : value;
      value = value < -99 ? -99 : value;
      break;
    case 4:
      value = value > 9999 ? 9999 : value;
      value = value < -999 ? -999 : value;
      break;
  }

  Com_sprintf(num, sizeof(num), "%i", value);
  l = strlen(num);
  if (l > width)
    l = width;
  x += 2 + CHAR_WIDTH * (width - l);

  ptr = num;
  while (*ptr && l) {
    if (*ptr == '-')
      frame = STAT_MINUS;
    else
      frame = *ptr - '0';

    CG_DrawPic(x, y, CHAR_WIDTH, CHAR_HEIGHT, cgs.media.numberShaders[frame]);
    x += CHAR_WIDTH;
    ptr++;
    l--;
  }
}

/*
 ================
 CG_Draw3DModel

 ================
 */
void CG_Draw3DModel(float x, float y, float w, float h, qhandle_t model, qhandle_t skin, vec3_t origin, vec3_t angles) {
  refdef_t refdef;
  refEntity_t ent;

  if (!cg_draw3dIcons.integer || !cg_drawIcons.integer) {
    return;
  }

  CG_AdjustFrom640(&x, &y, &w, &h);

  memset(&refdef, 0, sizeof(refdef));

  memset(&ent, 0, sizeof(ent));
  AnglesToAxis(angles, ent.axis);
  VectorCopy(origin, ent.origin);
  ent.hModel = model;
  ent.customSkin = skin;
  ent.renderfx = RF_NOSHADOW; // no stencil shadows

  refdef.rdflags = RDF_NOWORLDMODEL;

  AxisClear(refdef.viewaxis);

  refdef.fov_x = 30;
  refdef.fov_y = 30;

  refdef.x = x;
  refdef.y = y;
  refdef.width = w;
  refdef.height = h;

  refdef.time = cg.time;

  trap_R_ClearScene();
  trap_R_AddRefEntityToScene(&ent);
  trap_R_RenderScene(&refdef);
}

/*
 ================
 CG_DrawHead

 Used for both the status bar and the scoreboard
 ================
 */
void CG_DrawHead(float x, float y, float w, float h, int clientNum, vec3_t headAngles) {
  clipHandle_t cm;
  clientInfo_t *ci;
  float len;
  vec3_t origin;
  vec3_t mins, maxs;

  ci = &cgs.clientinfo[clientNum];

  if (cg_draw3dIcons.integer) {
    cm = ci->headModel;
    if (!cm) {
      return;
    }

    // offset the origin y and z to center the head
    trap_R_ModelBounds(cm, mins, maxs);

    origin[2] = -0.5 * (mins[2] + maxs[2]);
    origin[1] = 0.5 * (mins[1] + maxs[1]);

    // calculate distance so the head nearly fills the box
    // assume heads are taller than wide
    len = 0.7 * (maxs[2] - mins[2]);
    origin[0] = len / 0.268; // len / tan( fov/2 )

    // allow per-model tweaking
    VectorAdd(origin, ci->headOffset, origin);

    CG_Draw3DModel(x, y, w, h, ci->headModel, ci->headSkin, origin, headAngles);
  } else if (cg_drawIcons.integer) {
    CG_DrawPic(x, y, w, h, ci->modelIcon);
  }

  // if they are deferred, draw a cross out
  if (ci->deferred) {
    CG_DrawPic(x, y, w, h, cgs.media.deferShader);
  }
}

/*
 ================
 CG_DrawFlagModel

 Used for both the status bar and the scoreboard
 ================
 */
void CG_DrawFlagModel(float x, float y, float w, float h, int team, qboolean force2D) {
  qhandle_t cm;
  float len;
  vec3_t origin, angles;
  vec3_t mins, maxs;
  qhandle_t handle;

  if (!force2D && cg_draw3dIcons.integer) {

    VectorClear(angles);

    cm = cgs.media.redFlagModel;

    // offset the origin y and z to center the flag
    trap_R_ModelBounds(cm, mins, maxs);

    origin[2] = -0.5 * (mins[2] + maxs[2]);
    origin[1] = 0.5 * (mins[1] + maxs[1]);

    // calculate distance so the flag nearly fills the box
    // assume heads are taller than wide
    len = 0.5 * (maxs[2] - mins[2]);
    origin[0] = len / 0.268; // len / tan( fov/2 )

    angles[YAW] = 60 * sin(cg.time / 2000.0);
    ;

    if (team == TEAM_RED) {
      handle = cgs.media.redFlagModel;
    } else if (team == TEAM_BLUE) {
      handle = cgs.media.blueFlagModel;
    } else if (team == TEAM_FREE) {
      handle = cgs.media.neutralFlagModel;
    } else {
      return;
    }
    CG_Draw3DModel(x, y, w, h, handle, 0, origin, angles);
  } else if (cg_drawIcons.integer) {
    gitem_t *item;

    if (team == TEAM_RED) {
      item = BG_FindItemForPowerup(PW_REDFLAG);
    } else if (team == TEAM_BLUE) {
      item = BG_FindItemForPowerup(PW_BLUEFLAG);
    } else if (team == TEAM_FREE) {
      item = BG_FindItemForPowerup(PW_NEUTRALFLAG);
    } else {
      return;
    }
    if (item) {
      CG_DrawPic(x, y, w, h, cg_items[ITEM_INDEX(item)].icon);
    }
  }
}

/*
 ================
 CG_DrawStatusBarHead

 ================
 */
static void CG_DrawStatusBarHead(float x) {
  vec3_t angles;
  float size, stretch;
  float frac;

  VectorClear(angles);

  if (cg.damageTime && cg.time - cg.damageTime < DAMAGE_TIME) {
    frac = (float) (cg.time - cg.damageTime) / DAMAGE_TIME;
    size = ICON_SIZE * 1.25 * (1.5 - frac * 0.5);

    stretch = size - ICON_SIZE * 1.25;
    // kick in the direction of damage
    x -= stretch * 0.5 + cg.damageX * stretch * 0.5;

    cg.headStartYaw = 180 + cg.damageX * 45;

    cg.headEndYaw = 180 + 20 * cos(crandom() * M_PI);
    cg.headEndPitch = 5 * cos(crandom() * M_PI);

    cg.headStartTime = cg.time;
    cg.headEndTime = cg.time + 100 + random() * 2000;
  } else {
    if (cg.time >= cg.headEndTime) {
      // select a new head angle
      cg.headStartYaw = cg.headEndYaw;
      cg.headStartPitch = cg.headEndPitch;
      cg.headStartTime = cg.headEndTime;
      cg.headEndTime = cg.time + 100 + random() * 2000;

      cg.headEndYaw = 180 + 20 * cos(crandom() * M_PI);
      cg.headEndPitch = 5 * cos(crandom() * M_PI);
    }

    size = ICON_SIZE * 1.25;
  }

  // if the server was frozen for a while we may have a bad head start time
  if (cg.headStartTime > cg.time) {
    cg.headStartTime = cg.time;
  }

  frac = (cg.time - cg.headStartTime) / (float) (cg.headEndTime - cg.headStartTime);
  frac = frac * frac * (3 - 2 * frac);
  angles[YAW] = cg.headStartYaw + (cg.headEndYaw - cg.headStartYaw) * frac;
  angles[PITCH] = cg.headStartPitch + (cg.headEndPitch - cg.headStartPitch) * frac;

  CG_DrawHead(x, 480 - size, size, size, cg.snap->ps.clientNum, angles);
}

/*
 ================
 CG_DrawStatusBarFlag

 ================
 */
static void CG_DrawStatusBarFlag(float x, int team) {
  CG_DrawFlagModel(x, 480 - ICON_SIZE, ICON_SIZE, ICON_SIZE, team, qfalse);
}

/*
 ================
 CG_DrawTeamBackground

 ================
 */
void CG_DrawTeamBackground(int x, int y, int w, int h, float alpha, int team) {
  vec4_t hcolor;

  hcolor[3] = alpha;
  if (team == TEAM_RED) {
    hcolor[0] = 1;
    hcolor[1] = 0;
    hcolor[2] = 0;
  } else if (team == TEAM_BLUE) {
    hcolor[0] = 0;
    hcolor[1] = 0;
    hcolor[2] = 1;
  } else {
    return;
  }
  trap_R_SetColor(hcolor);
  CG_DrawPic(x, y, w, h, cgs.media.teamStatusBar);
  trap_R_SetColor(NULL);
}

#define BLINDTIME 7500
#define DAMAGETIME 2000

/*
 ================
 CG_DrawDamagePic

 ================
 */
static void CG_DrawDamagePic(void) {
  float x, y, w, h, t;
  playerState_t *ps;
  int health, time;
  float *color;

  if (cg.renderingThirdPerson) {
    return;
  }

  ps = &cg.snap->ps;
  health = ps->stats[STAT_HEALTH];

  if (health > 0) {
    x = y = 0;
    w = 640;
    h = 480;
    CG_AdjustFrom640(&x, &y, &w, &h);

    if (cg_blood.integer == 1) {
      t = cg.time - cg.damageTime;
      if (t > 0 && t < DAMAGETIME && cg.damageValue > 0) {
        color = CG_FadeColorTime(cg.damageTime, DAMAGETIME, DAMAGETIME / 2);
        trap_R_SetColor(color);
        trap_R_DrawStretchPic(x, y, w, h, 1, 1, 0, 0, cgs.media.viewBloodShader);
        trap_R_SetColor(NULL);
      }
      if (health < 60) {
        trap_R_DrawStretchPic(x, y, w, h, 1, 1, 0, 0, cgs.media.viewBloodSpurts);
      } else if (health < 80) {
        trap_R_DrawStretchPic(x, y, w, h, 1, 1, 0, 0, cgs.media.sha_fewBloodSpurts);
      }
      if (cg.predictedPlayerState.powerups[PW_ADRENALINE] == 0) {
        if (health <= 20) {
          trap_R_DrawStretchPic(x, y, w, h, 1, 1, 0, 0, cgs.media.viewNearDeathShader);
        } else if (health <= 40) {
          trap_R_DrawStretchPic(x, y, w, h, 1, 1, 0, 0, cgs.media.viewLowHealthShader);
        }
      }
    }

    if (ps->zoomFov > 0 && !cg_scopeType.integer) {
      trap_R_DrawStretchPic(x, y, w, h, 1, 1, 0, 0, cgs.media.sha_viewScope);
    }

    if (ps->blindTime > 0) {
      color = CG_FadeColorTime(ps->blindTime, BLINDTIME, BLINDTIME - 2500);
      if (!color) {
        ps->blindTime = 0;
        return;
      }
      trap_R_SetColor(NULL);
      CG_FillRect(0, 0, 640, 480, color);
    }
  }
}

/*
 ================
 CG_DrawStatusBar

 ================
 */
static void CG_DrawStatusBar(void) {
  int color, value;
  centity_t *cent;
  playerState_t *ps;
  vec4_t hcolor;
  vec3_t origin;

  static float colors[5][4] = {
  //		{ 0.2, 1.0, 0.2, 1.0 } , { 1.0, 0.2, 0.2, 1.0 }, {0.5, 0.5, 0.5, 1} };
      { 1.0f, 0.69f, 0.0f, 1.0f }, // yellow
      { 1.0f, 0.2f, 0.2f, 1.0f }, // red
      { 0.5f, 0.5f, 0.5f, 1.0f }, // grey
      { 1.0f, 1.0f, 1.0f, 1.0f }, // red
      { 0.0f, 0.75f, 0.0f, 1.0f } }; // green

  if (cg_drawStatus.integer == 0) {
    return;
  }

  // draw the team background
  CG_DrawTeamBackground(0, 420, 640, 60, 0.33f, cg.snap->ps.persistant[PERS_TEAM]);

  cent = &cg_entities[cg.snap->ps.clientNum];
  ps = &cg.snap->ps;

  if (cg.predictedPlayerState.powerups[PW_REDFLAG]) {
    CG_DrawStatusBarFlag(185 + CHAR_WIDTH * 3 + TEXT_ICON_SPACE + ICON_SIZE, TEAM_RED);
  } else if (cg.predictedPlayerState.powerups[PW_BLUEFLAG]) {
    CG_DrawStatusBarFlag(185 + CHAR_WIDTH * 3 + TEXT_ICON_SPACE + ICON_SIZE, TEAM_BLUE);
  } else if (cg.predictedPlayerState.powerups[PW_NEUTRALFLAG]) {
    CG_DrawStatusBarFlag(185 + CHAR_WIDTH * 3 + TEXT_ICON_SPACE + ICON_SIZE, TEAM_FREE);
  }

  //
  // health
  //
  value = ps->stats[STAT_HEALTH];
  if (value > 75) {
    trap_R_SetColor(colors[4]); // green
  } else if (value > 50) {
    trap_R_SetColor(colors[0]); // yellow
  } else {
    trap_R_SetColor(colors[1]); // red
  }
  CG_DrawField(185, 432, 3, value);
  trap_R_SetColor(NULL);

  // stamina
  value = (int) ps->stamina / 100;
  if (value > 75) {
    trap_R_SetColor(colors[4]); // green
  } else if (value > 25) {
    trap_R_SetColor(colors[0]); // yellow
  } else {
    trap_R_SetColor(colors[1]); // red
  }
  CG_DrawField(16, 432, 3, value);
  trap_R_SetColor(NULL);

  // ammo
  if (cent->currentState.weapon) {
    value = ps->ammo[cent->currentState.weapon];
    if (value > -1) {
      switch (cent->currentState.weapon) {
        case WP_ACR:
          value = value / 30;
          break;
        case WP_BARRETT:
          value = value / 10;
          break;
        case WP_INTERVENTION:
          value = value / 7;
          break;
        case WP_CROSSBOW:
          value = value / 1;
          break;
        case WP_WALTHER:
          value = value / 10;
          break;
      }
      if (value >= 0) {
        color = 4; // green
      } else {
        color = 1; // red
      }
      trap_R_SetColor(colors[color]);
      CG_DrawField(488, 432, 3, value);
      trap_R_SetColor(NULL);
    }
  }
  value = ps->stats[STAT_AMMO];
  if (value > 0) {
    //Draw the Text
    trap_R_SetColor(colors[0]);
    CG_DrawField(488, 384, 3, value);
    trap_R_SetColor(NULL);
    CG_DrawPic(488 + (CHAR_WIDTH * 3 + TEXT_ICON_SPACE), 384, ICON_SIZE, ICON_SIZE, cg_weapons[cg.predictedPlayerState.weapon].weaponIcon);
  }

}

/*
 ===========================================================================================

 UPPER RIGHT CORNER

 ===========================================================================================
 */

/*
 ================
 CG_DrawAttacker

 ================
 */
static float CG_DrawAttacker(float y) {
  int t;
  float size;
  vec3_t angles;
  const char *info;
  const char *name;
  int clientNum;

  if (cg.predictedPlayerState.stats[STAT_HEALTH] <= 0) {
    return y;
  }

  if (!cg.attackerTime) {
    return y;
  }

  clientNum = cg.predictedPlayerState.persistant[PERS_ATTACKER];
  if (clientNum < 0 || clientNum >= MAX_CLIENTS || clientNum == cg.snap->ps.clientNum) {
    return y;
  }

  t = cg.time - cg.attackerTime;
  if (t > ATTACKER_HEAD_TIME) {
    cg.attackerTime = 0;
    return y;
  }

  size = ICON_SIZE * 1.25;

  angles[PITCH] = 0;
  angles[YAW] = 180;
  angles[ROLL] = 0;
  CG_DrawHead(640 - size, y, size, size, clientNum, angles);

  info = CG_ConfigString(CS_PLAYERS + clientNum);
  name = Info_ValueForKey(info, "n");
  y += size;
  CG_DrawBigString(640 - (Q_PrintStrlen(name) * BIGCHAR_WIDTH), y, name, 0.5);

  return y + BIGCHAR_HEIGHT + 2;
}

/*
 ==================
 CG_DrawSnapshot
 ==================
 */
static float CG_DrawSnapshot(float y) {
  char *s;
  int w;

  s = va("time:%i snap:%i cmd:%i", cg.snap->serverTime, cg.latestSnapshotNum, cgs.serverCommandSequence);
  w = CG_DrawStrlen(s) * BIGCHAR_WIDTH;

  CG_DrawBigString(635 - w, y + 2, s, 1.0F);

  return y + BIGCHAR_HEIGHT + 4;
}

/*
 ==================
 CG_DrawFPS
 ==================
 */
#define	FPS_FRAMES	4

static float CG_DrawFPS(float y) {
  char *s;
  int w;
  static int previousTimes[FPS_FRAMES];
  static int index;
  int i, total;
  int fps;
  static int previous;
  int t, frameTime;

  // don't use serverTime, because that will be drifting to
  // correct for internet lag changes, timescales, timedemos, etc
  t = trap_Milliseconds();
  frameTime = t - previous;
  previous = t;

  previousTimes[index % FPS_FRAMES] = frameTime;
  index++;
  if (index > FPS_FRAMES) {
    // average multiple frames together to smooth changes out a bit
    total = 0;
    for (i = 0; i < FPS_FRAMES; i++) {
      total += previousTimes[i];
    }
    if (!total) {
      total = 1;
    }
    fps = 1000 * FPS_FRAMES / total;

    s = va("%ifps", fps);
    w = CG_DrawStrlen(s) * BIGCHAR_WIDTH;

    CG_DrawBigString(635 - w, y + 2, s, 1.0F);
  }

  return y + BIGCHAR_HEIGHT + 4;
}

/*
 =================
 CG_DrawTimer
 =================
 */
static float CG_DrawTimer(float y) {
  char *s;
  int w;
  int mins, seconds, tens;
  int msec;

  msec = cg.time - cgs.levelStartTime;

  seconds = msec / 1000;
  mins = seconds / 60;
  seconds -= mins * 60;
  tens = seconds / 10;
  seconds -= tens * 10;

  s = va("%i:%i%i", mins, tens, seconds);
  w = CG_DrawStrlen(s) * BIGCHAR_WIDTH;

  CG_DrawBigString(635 - w, y + 2, s, 1.0F);

  return y + BIGCHAR_HEIGHT + 4;
}

/*
 =================
 CG_DrawTeamOverlay
 =================
 */

static float CG_DrawTeamOverlay(float y, qboolean right, qboolean upper) {
  int x, w, h, xx;
  int i, j, len;
  const char *p;
  vec4_t hcolor;
  int pwidth, lwidth;
  int plyrs;
  char st[16];
  clientInfo_t *ci;
  gitem_t *item;
  int ret_y, count;

  if (!cg_drawTeamOverlay.integer) {
    return y;
  }

  if (cg.snap->ps.persistant[PERS_TEAM] != TEAM_RED && cg.snap->ps.persistant[PERS_TEAM] != TEAM_BLUE) {
    return y; // Not on any team
  }

  plyrs = 0;

  // max player name width
  pwidth = 0;
  count = (numSortedTeamPlayers > 8) ? 8 : numSortedTeamPlayers;
  for (i = 0; i < count; i++) {
    ci = cgs.clientinfo + sortedTeamPlayers[i];
    if (ci->infoValid && ci->team == cg.snap->ps.persistant[PERS_TEAM]) {
      plyrs++;
      len = CG_DrawStrlen(ci->name);
      if (len > pwidth)
        pwidth = len;
    }
  }

  if (!plyrs)
    return y;

  if (pwidth > TEAM_OVERLAY_MAXNAME_WIDTH)
    pwidth = TEAM_OVERLAY_MAXNAME_WIDTH;

  // max location name width
  lwidth = 0;
  for (i = 1; i < MAX_LOCATIONS; i++) {
    p = CG_ConfigString(CS_LOCATIONS + i);
    if (p && *p) {
      len = CG_DrawStrlen(p);
      if (len > lwidth)
        lwidth = len;
    }
  }

  if (lwidth > TEAM_OVERLAY_MAXLOCATION_WIDTH)
    lwidth = TEAM_OVERLAY_MAXLOCATION_WIDTH;

  w = (pwidth + lwidth + 4 + 7) * SMALLERCHAR_WIDTH;

  if (right)
    x = 640 - w;
  else
    x = 0;

  h = plyrs * SMALLERCHAR_HEIGHT;

  if (upper) {
    ret_y = y + h;
  } else {
    y -= h;
    ret_y = y;
  }

  if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_RED) {
    hcolor[0] = 1.0f;
    hcolor[1] = 0.0f;
    hcolor[2] = 0.0f;
    hcolor[3] = 0.33f;
  } else { // if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE )
    hcolor[0] = 0.0f;
    hcolor[1] = 0.0f;
    hcolor[2] = 1.0f;
    hcolor[3] = 0.33f;
  }
  trap_R_SetColor(hcolor);
  CG_DrawPic(x, y, w, h, cgs.media.teamStatusBar);
  trap_R_SetColor(NULL);

  for (i = 0; i < count; i++) {
    ci = cgs.clientinfo + sortedTeamPlayers[i];
    if (ci->infoValid && ci->team == cg.snap->ps.persistant[PERS_TEAM]) {

      hcolor[0] = hcolor[1] = hcolor[2] = hcolor[3] = 1.0;

      xx = x + SMALLERCHAR_WIDTH;

      CG_DrawStringExt(xx, y, ci->name, hcolor, qfalse, qfalse, SMALLERCHAR_WIDTH, SMALLERCHAR_HEIGHT, TEAM_OVERLAY_MAXNAME_WIDTH);

      if (lwidth) {
        p = CG_ConfigString(CS_LOCATIONS + ci->location);
        if (!p || !*p)
          p = "unknown";
        len = CG_DrawStrlen(p);
        if (len > lwidth)
          len = lwidth;

        //				xx = x + SMALLERCHAR_WIDTH * 2 + SMALLERCHAR_WIDTH * pwidth +
        //					((lwidth/2 - len/2) * SMALLERCHAR_WIDTH);
        xx = x + SMALLERCHAR_WIDTH * 2 + SMALLERCHAR_WIDTH * pwidth;
        CG_DrawStringExt(xx, y, p, hcolor, qfalse, qfalse, SMALLERCHAR_WIDTH, SMALLERCHAR_HEIGHT, TEAM_OVERLAY_MAXLOCATION_WIDTH);
      }

      CG_GetColorForHealth(ci->health, ci->armor, hcolor);

      Com_sprintf(st, sizeof(st), "%3i %3i", ci->health, ci->armor);

      xx = x + SMALLERCHAR_WIDTH * 3 + SMALLERCHAR_WIDTH * pwidth + SMALLERCHAR_WIDTH * lwidth;

      CG_DrawStringExt(xx, y, st, hcolor, qfalse, qfalse, SMALLERCHAR_WIDTH, SMALLERCHAR_HEIGHT, 0);

      // draw weapon icon
      xx += SMALLERCHAR_WIDTH * 3;

      if (cg_weapons[ci->curWeapon].weaponIcon) {
        CG_DrawPic(xx, y, SMALLERCHAR_WIDTH, SMALLERCHAR_HEIGHT, cg_weapons[ci->curWeapon].weaponIcon);
      } else {
        CG_DrawPic(xx, y, SMALLERCHAR_WIDTH, SMALLERCHAR_HEIGHT, cgs.media.deferShader);
      }

      // Draw powerup icons
      if (right) {
        xx = x;
      } else {
        xx = x + w - SMALLERCHAR_WIDTH;
      }
      for (j = 0; j <= PW_NUM_POWERUPS; j++) {
        if (ci->powerups & (1 << j)) {

          item = BG_FindItemForPowerup(j);

          if (item) {
            CG_DrawPic(xx, y, SMALLERCHAR_WIDTH, SMALLERCHAR_HEIGHT, trap_R_RegisterShader(item->icon));
            if (right) {
              xx -= SMALLERCHAR_WIDTH;
            } else {
              xx += SMALLERCHAR_WIDTH;
            }
          }
        }
      }

      y += SMALLERCHAR_HEIGHT;
    }
  }

  return ret_y;
  //#endif
}

/*
 =================
 CG_CleanKillfeed
 =================
 */
void CG_CleanKillfeed(void) {
  int i;
  for (i = 0; i < cg_killfeedHeight.integer; i++) {
    if (killfeed.times[i] + (cg_killfeedTime.value * 1000) < cg.time) {
      killfeed.attackers[i][0] = 0;
      killfeed.targets[i][0] = 0;
      killfeed.mods[i] = -1;
      killfeed.times[i] = 0;
    }
  }
  CG_KillfeedSort();
}

/*
 =================
 CG_WeaponFromMod
 Returns the weapon id from its mod
 =================
 */
int CG_WeaponFromMod(int mod) {
  switch (mod) {
    case MOD_ACR:
      return WP_ACR;
    case MOD_BARRETT:
      return WP_BARRETT;
    case MOD_INTERVENTION:
      return WP_INTERVENTION;
    case MOD_HE:
    case MOD_HE_SPLASH:
      return WP_HE;
    case MOD_WALTHER:
      return WP_WALTHER;
    case MOD_CROSSBOW:
      return WP_CROSSBOW;
    case MOD_KNIFE:
      return WP_KNIFE;
    case MOD_HANDS:
      return WP_HANDS;
    case MOD_BOMB:
      return WP_BOMB;
    case MOD_SNOWBOARD:
      return WP_SNOWBOARD;
    default:
      return -1;
  }
}

/*
 =================
 CG_NameForMod
 Returns either a weapon name or a death message string
 =================
 */
char *CG_NameForMod(int mod) {
  if (BG_NameForWeapon(CG_WeaponFromMod(mod)) != NULL) {
    return BG_NameForWeapon(CG_WeaponFromMod(mod));
  } else {
    switch (mod) {
      case MOD_ADMIN:
        return "Admin";
      case MOD_BLEED:
        return "Bleed";
      case MOD_CRUSH:
        return "Crush";
      case MOD_FALLING:
        return "Cratered";
      case MOD_LAVA:
        return "Lava";
      case MOD_MOOR:
        return "Moor";
      case MOD_NADELOVE:
        return "Exploded";
      case MOD_NUKE:
        return "Nuke";
      case MOD_SHRAPNEL:
        return "Shrapnel";
      case MOD_SLIME:
        return "Slime";
      case MOD_SUICIDE:
        return "Suicide";
      case MOD_TARGET_LASER:
        return "Laser";
      case MOD_TELEFRAG:
        return "Telefrag";
      case MOD_TRIGGER_HURT:
        return "Trigger";
      case MOD_UNKNOWN:
        return "Unknown";
      case MOD_WATER:
        return "Drowned";
      case MOD_WINDOW:
        return "Glass";
    }
  }
  return "";
}

/*
 =================
 CG_DrawKillfeed
 =================
 */
void CG_DrawKillfeed(void) {
  int i, mod;
  int x, y, w, h;
  int lineHeight = 24;
  float *color;
  if (!cg_killfeed.integer) {
    return;
  }
  x = 16;
  w = 6;
  h = 12;
  for (i = 0; i < cg_killfeedHeight.integer; i++) {
    if (!killfeed.attackers[i][0]) {
      continue;
    }
    color = CG_FadeColorTime(killfeed.times[i], cg_killfeedTime.value * 1000, (cg_killfeedTime.value * 1000) / 2);
    if (color[3] <= 0) {
      continue;
    }
    mod = killfeed.mods[i];
    y = 39 + (i * lineHeight);
    if (cg_killfeed.integer == 1) {
      CG_DrawStringExtAlpha(x, y, killfeed.attackers[i], qfalse, w, h, 0, color[3]);
    } else if (cg_killfeed.integer == 2) {
      if (killfeed.targets[i][0]) {
        CG_DrawStringExtAlpha(x, y, killfeed.attackers[i], qfalse, w, h, 0, color[3]);
      } else {
        CG_DrawStringExtAlpha(x, y, va("^7%s ^1X", killfeed.attackers[i]), qfalse, w, h, 0, color[3]);
      }
    } else if (cg_killfeed.integer >= 3) {
      CG_DrawStringExtAlpha(x, y, va("^7%s ^7[%s^7] %s", killfeed.attackers[i], CG_NameForMod(mod), killfeed.targets[i]), qfalse, w, h, 0, color[3]);
    }
    if (cg_killfeed.integer == 1) {
      CG_DrawPic(144, y - 1, 48, 16, cgs.media.sha_mods[mod]);
    }
    if (killfeed.targets[i][0]) {
      if (cg_killfeed.integer == 1) {
        CG_DrawStringExtAlpha(x + 192, y, killfeed.targets[i], qfalse, w, h, 0, color[3]);
      } else if (cg_killfeed.integer == 2) {
        CG_DrawStringExtAlpha(x + (Q_PrintStrlen(killfeed.attackers[i]) * w), y, va("^7 --> %s", killfeed.targets[i]), qfalse, w, h, 0, color[3]);
      }
    }
    trap_R_SetColor(NULL);
  }
  CG_CleanKillfeed();
}

/*
 =====================
 CG_DrawUpperRight
 =====================
 */
static void CG_DrawUpperRight(stereoFrame_t stereoFrame) {
  float y;

  y = 0;

  if (cg_drawSnapshot.integer) {
    y = CG_DrawSnapshot(y);
  }
  if (cg_drawFPS.integer && (stereoFrame == STEREO_CENTER || stereoFrame == STEREO_RIGHT)) {
    y = CG_DrawFPS(y);
  }
  if (cg_drawTimer.integer) {
    y = CG_DrawTimer(y);
  }
  if (cg_drawAttacker.integer) {
    y = CG_DrawAttacker(y);
  }

}

/*
 ===========================================================================================

 LOWER RIGHT CORNER

 ===========================================================================================
 */

/*
 =================
 CG_DrawScores

 Draw the small two score display
 =================
 */
static float CG_DrawScores(float y) {
  const char *s;
  int s1, s2, score;
  int x, w;
  vec4_t color;
  float y1;

  qboolean spectator;

  s1 = cgs.scores1;
  s2 = cgs.scores2;

  y -= BIGCHAR_HEIGHT + 8;

  y1 = y;

  //qboolean spectator;

  x = 640;
  score = cg.snap->ps.persistant[PERS_SCORE];
  spectator = (cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR);

  // always show your score in the second box if not in first place
  if (s1 != score) {
    s2 = score;
  }
  if (s2 != SCORE_NOT_PRESENT) {
    s = va("%2i", s2);
    w = CG_DrawStrlen(s) * BIGCHAR_WIDTH + 8;
    x -= w;
    if (!spectator && score == s2 && score != s1) {
      color[0] = 1.0f;
      color[1] = 0.0f;
      color[2] = 0.0f;
      color[3] = 0.33f;
      CG_FillRect(x, y - 4, w, BIGCHAR_HEIGHT + 8, color);
      CG_DrawPic(x, y - 4, w, BIGCHAR_HEIGHT + 8, cgs.media.selectShader);
    } else {
      color[0] = 0.5f;
      color[1] = 0.5f;
      color[2] = 0.5f;
      color[3] = 0.33f;
      CG_FillRect(x, y - 4, w, BIGCHAR_HEIGHT + 8, color);
    }
    CG_DrawBigString(x + 4, y, s, 1.0F);

    // first place
    if (s1 != SCORE_NOT_PRESENT) {
      s = va("%2i", s1);
      w = CG_DrawStrlen(s) * BIGCHAR_WIDTH + 8;
      x -= w;
      if (!spectator && score == s1) {
        color[0] = 0.0f;
        color[1] = 0.0f;
        color[2] = 1.0f;
        color[3] = 0.33f;
        CG_FillRect(x, y - 4, w, BIGCHAR_HEIGHT + 8, color);
        CG_DrawPic(x, y - 4, w, BIGCHAR_HEIGHT + 8, cgs.media.selectShader);
      } else {
        color[0] = 0.5f;
        color[1] = 0.5f;
        color[2] = 0.5f;
        color[3] = 0.33f;
        CG_FillRect(x, y - 4, w, BIGCHAR_HEIGHT + 8, color);
      }
      CG_DrawBigString(x + 4, y, s, 1.0F);
    }

    if (cgs.fraglimit) {
      s = va("%2i", cgs.fraglimit);
      w = CG_DrawStrlen(s) * BIGCHAR_WIDTH + 8;
      x -= w;
      CG_DrawBigString(x + 4, y, s, 1.0F);
    }

  }

  return y1 - 8;
}

/*
 ================
 CG_DrawPowerups
 ================
 */
static float CG_DrawPowerups(float y) {
  int sorted[MAX_POWERUPS];
  int sortedTime[MAX_POWERUPS];
  int i, j, k;
  int active;
  playerState_t *ps;
  int t;
  gitem_t *item;
  int x;
  int color;
  float size;
  float f;
  static float colors[2][4] = { { 0.2f, 1.0f, 0.2f, 1.0f }, { 1.0f, 0.2f, 0.2f, 1.0f } };

  ps = &cg.snap->ps;

  if (ps->stats[STAT_HEALTH] <= 0) {
    return y;
  }

  // sort the list by time remaining
  active = 0;
  for (i = 0; i < MAX_POWERUPS; i++) {
    if (!ps->powerups[i]) {
      continue;
    }
    t = ps->powerups[i] - cg.time;
    // ZOID--don't draw if the power up has unlimited time (999 seconds)
    // This is true of the CTF flags
    if (t < 0 || t > 999000) {
      continue;
    }

    // insert into the list
    for (j = 0; j < active; j++) {
      if (sortedTime[j] >= t) {
        for (k = active - 1; k >= j; k--) {
          sorted[k + 1] = sorted[k];
          sortedTime[k + 1] = sortedTime[k];
        }
        break;
      }
    }
    sorted[j] = i;
    sortedTime[j] = t;
    active++;
  }

  // draw the icons and timers
  x = 640 - ICON_SIZE - CHAR_WIDTH * 2;
  for (i = 0; i < active; i++) {
    item = BG_FindItemForPowerup(sorted[i]);

    if (item) {

      color = 1;

      y -= ICON_SIZE;

      trap_R_SetColor(colors[color]);
      CG_DrawField(x, y, 2, sortedTime[i] / 1000);

      t = ps->powerups[sorted[i]];
      if (t - cg.time >= POWERUP_BLINKS * POWERUP_BLINK_TIME) {
        trap_R_SetColor(NULL);
      } else {
        vec4_t modulate;

        f = (float) (t - cg.time) / POWERUP_BLINK_TIME;
        f -= (int) f;
        modulate[0] = modulate[1] = modulate[2] = modulate[3] = f;
        trap_R_SetColor(modulate);
      }

      if (cg.powerupActive == sorted[i] && cg.time - cg.powerupTime < PULSE_TIME) {
        f = 1.0 - (((float) cg.time - cg.powerupTime) / PULSE_TIME);
        size = ICON_SIZE * (1.0 + (PULSE_SCALE - 1.0) * f);
      } else {
        size = ICON_SIZE;
      }

      CG_DrawPic(640 - size, y + ICON_SIZE / 2 - size / 2, size, size, trap_R_RegisterShader(item->icon));
    }
  }
  trap_R_SetColor(NULL);

  return y;
}

/*
 =====================
 CG_DrawLowerRight

 =====================
 */
static void CG_DrawLowerRight(void) {
  float y;

  y = 480 - ICON_SIZE;

  y = CG_DrawScores(y);
  y = CG_DrawPowerups(y);
}

/*
 ===================
 CG_DrawPickupItem
 ===================
 */
static int CG_DrawPickupItem(int y) {
  int value;
  float *fadeColor;

  if (cg.snap->ps.stats[STAT_HEALTH] <= 0) {
    return y;
  }

  y -= ICON_SIZE;

  value = cg.itemPickup;
  if (value) {
    fadeColor = CG_FadeColor(cg.itemPickupTime, 3000);
    if (fadeColor) {
      CG_RegisterItemVisuals(value);
      trap_R_SetColor(fadeColor);
      CG_DrawPic(8, y, ICON_SIZE, ICON_SIZE, cg_items[value].icon);
      CG_DrawBigString(ICON_SIZE + 16, y + (ICON_SIZE / 2 - BIGCHAR_HEIGHT / 2), bg_itemlist[value].pickup_name, fadeColor[0]);
      trap_R_SetColor(NULL);
    }
  }

  return y;
}

vec4_t orange = { 1, 0.43f, 0, 1 };
vec4_t red = { 1, 0, 0, 1 };
vec4_t green = { 0, 1, 0, 1 };

static void DamageColor(int dmg, float *color) {
  if (dmg < 25) {
    Vector4Copy(green, color);
  } else if (dmg < 50) {
    Vector4Copy(orange, color);
  } else {
    Vector4Copy(red, color);
  }
}
/*
 ================
 CG_DrawLimbStatus
 ================
 */
static void CG_DrawLimbStatus() {
  int rleg, lleg, rarm, larm;
  vec4_t color;
  int x = 16, y = 352;
  rleg = cg.snap->ps.damageLocations[LDMG_RLEG];
  lleg = cg.snap->ps.damageLocations[LDMG_LLEG];
  rarm = cg.snap->ps.damageLocations[LDMG_RARM];
  larm = cg.snap->ps.damageLocations[LDMG_LARM];
  DamageColor(rarm, color);
  CG_DrawStringExt(x, y, va("R (%i)", rarm), color, qtrue, qfalse, 8, 16, 8);
  DamageColor(larm, color);
  CG_DrawStringExt(x + 64, y, va("L (%i)", larm), color, qtrue, qfalse, 8, 16, 8);
  DamageColor(rleg, color);
  CG_DrawStringExt(x, y + 32, va("R (%i)", rleg), color, qtrue, qfalse, 8, 16, 8);
  DamageColor(lleg, color);
  CG_DrawStringExt(x + 64, y + 32, va("L (%i)", lleg), color, qtrue, qfalse, 8, 16, 8);
}

/*
 =====================
 CG_DrawLowerLeft

 =====================
 */
static void CG_DrawLowerLeft(void) {
  float y;
  y = 480 - ICON_SIZE;
  y = CG_DrawPickupItem(y);
  CG_DrawLimbStatus();
}

//===========================================================================================

/*
 =================
 CG_DrawTeamInfo
 =================
 */
static void CG_DrawTeamInfo(void) {
  int w, h;
  int i, len;
  vec4_t hcolor;
  int chatHeight;

#define CHATLOC_Y 420 // bottom end
#define CHATLOC_X 0

  if (cg_teamChatHeight.integer < TEAMCHAT_HEIGHT)
    chatHeight = cg_teamChatHeight.integer;
  else
    chatHeight = TEAMCHAT_HEIGHT;
  if (chatHeight <= 0)
    return; // disabled

  if (cgs.teamLastChatPos != cgs.teamChatPos) {
    if (cg.time - cgs.teamChatMsgTimes[cgs.teamLastChatPos % chatHeight] > cg_teamChatTime.integer) {
      cgs.teamLastChatPos++;
    }

    h = (cgs.teamChatPos - cgs.teamLastChatPos) * SMALLERCHAR_HEIGHT;

    w = 0;

    for (i = cgs.teamLastChatPos; i < cgs.teamChatPos; i++) {
      len = CG_DrawStrlen(cgs.teamChatMsgs[i % chatHeight]);
      if (len > w)
        w = len;
    }
    w *= SMALLERCHAR_WIDTH;
    w += SMALLERCHAR_WIDTH * 2;

    if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_RED) {
      hcolor[0] = 1.0f;
      hcolor[1] = 0.0f;
      hcolor[2] = 0.0f;
      hcolor[3] = 0.33f;
    } else if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE) {
      hcolor[0] = 0.0f;
      hcolor[1] = 0.0f;
      hcolor[2] = 1.0f;
      hcolor[3] = 0.33f;
    } else {
      hcolor[0] = 0.0f;
      hcolor[1] = 1.0f;
      hcolor[2] = 0.0f;
      hcolor[3] = 0.33f;
    }

    trap_R_SetColor(hcolor);
    CG_DrawPic(CHATLOC_X, CHATLOC_Y - h, 640, h, cgs.media.teamStatusBar);
    trap_R_SetColor(NULL);

    hcolor[0] = hcolor[1] = hcolor[2] = 1.0f;
    hcolor[3] = 1.0f;

    for (i = cgs.teamChatPos - 1; i >= cgs.teamLastChatPos; i--) {
      CG_DrawStringExt(CHATLOC_X + SMALLERCHAR_WIDTH, CHATLOC_Y - (cgs.teamChatPos - i) * SMALLERCHAR_HEIGHT, cgs.teamChatMsgs[i % chatHeight], hcolor, qfalse, qfalse, SMALLERCHAR_WIDTH, SMALLERCHAR_HEIGHT, 0);
    }
  }
}

/*
 ===================
 CG_DrawHoldableItem
 ===================
 */
static void CG_DrawHoldableItem(void) {
  int value;

  value = cg.snap->ps.stats[STAT_HOLDABLE_ITEM];
  if (value) {
    CG_RegisterItemVisuals(value);
    CG_DrawPic(640 - ICON_SIZE, (SCREEN_HEIGHT - ICON_SIZE) / 2, ICON_SIZE, ICON_SIZE, cg_items[value].icon);
  }

}

/*
 ===================
 CG_DrawReward
 ===================
 */
static void CG_DrawReward(void) {
  float *color;
  int i, count;
  float x, y;
  char buf[32];

  if (!cg_drawRewards.integer) {
    return;
  }

  color = CG_FadeColor(cg.rewardTime, REWARD_TIME);
  if (!color) {
    if (cg.rewardStack > 0) {
      for (i = 0; i < cg.rewardStack; i++) {
        cg.rewardSound[i] = cg.rewardSound[i + 1];
        cg.rewardShader[i] = cg.rewardShader[i + 1];
        cg.rewardCount[i] = cg.rewardCount[i + 1];
      }
      cg.rewardTime = cg.time;
      cg.rewardStack--;
      color = CG_FadeColor(cg.rewardTime, REWARD_TIME);
      trap_S_StartLocalSound(cg.rewardSound[0], CHAN_ANNOUNCER);
    } else {
      return;
    }
  }

  trap_R_SetColor(color);

  /*
   count = cg.rewardCount[0]/10;				// number of big rewards to draw

   if (count) {
   y = 4;
   x = 320 - count * ICON_SIZE;
   for ( i = 0 ; i < count ; i++ ) {
   CG_DrawPic( x, y, (ICON_SIZE*2)-4, (ICON_SIZE*2)-4, cg.rewardShader[0] );
   x += (ICON_SIZE*2);
   }
   }

   count = cg.rewardCount[0] - count*10;		// number of small rewards to draw
   */

  if (cg.rewardCount[0] >= 10) {
    y = 56;
    x = 320 - ICON_SIZE / 2;
    CG_DrawPic(x, y, ICON_SIZE - 4, ICON_SIZE - 4, cg.rewardShader[0]);
    Com_sprintf(buf, sizeof(buf), "%d", cg.rewardCount[0]);
    x = (SCREEN_WIDTH - SMALLCHAR_WIDTH * CG_DrawStrlen(buf)) / 2;
    CG_DrawStringExt(x, y + ICON_SIZE, buf, color, qfalse, qtrue, SMALLCHAR_WIDTH, SMALLCHAR_HEIGHT, 0);
  } else {

    count = cg.rewardCount[0];

    y = 56;
    x = 320 - count * ICON_SIZE / 2;
    for (i = 0; i < count; i++) {
      CG_DrawPic(x, y, ICON_SIZE - 4, ICON_SIZE - 4, cg.rewardShader[0]);
      x += ICON_SIZE;
    }
  }
  trap_R_SetColor(NULL);
}

/*
 ===============================================================================

 LAGOMETER

 ===============================================================================
 */

#define	LAG_SAMPLES		128

typedef struct {
int frameSamples[LAG_SAMPLES];
int frameCount;
int snapshotFlags[LAG_SAMPLES];
int snapshotSamples[LAG_SAMPLES];
int snapshotCount;
} lagometer_t;

lagometer_t lagometer;

/*
 ==============
 CG_AddLagometerFrameInfo

 Adds the current interpolate / extrapolate bar for this frame
 ==============
 */
void CG_AddLagometerFrameInfo(void) {
  int offset;

  offset = cg.time - cg.latestSnapshotTime;
  lagometer.frameSamples[lagometer.frameCount & (LAG_SAMPLES - 1)] = offset;
  lagometer.frameCount++;
}

/*
 ==============
 CG_AddLagometerSnapshotInfo

 Each time a snapshot is received, log its ping time and
 the number of snapshots that were dropped before it.

 Pass NULL for a dropped packet.
 ==============
 */
void CG_AddLagometerSnapshotInfo(snapshot_t *snap) {
  // dropped packet
  if (!snap) {
    lagometer.snapshotSamples[lagometer.snapshotCount & (LAG_SAMPLES - 1)] = -1;
    lagometer.snapshotCount++;
    return;
  }

  // add this snapshot's info
  lagometer.snapshotSamples[lagometer.snapshotCount & (LAG_SAMPLES - 1)] = snap->ping;
  lagometer.snapshotFlags[lagometer.snapshotCount & (LAG_SAMPLES - 1)] = snap->snapFlags;
  lagometer.snapshotCount++;
}

/*
 ==============
 CG_DrawDisconnect

 Should we draw something differnet for long lag vs no packets?
 ==============
 */
static void CG_DrawDisconnect(void) {
  float x, y;
  int cmdNum;
  usercmd_t cmd;
  const char *s;
  int w;

  // draw the phone jack if we are completely past our buffers
  cmdNum = trap_GetCurrentCmdNumber() - CMD_BACKUP + 1;
  trap_GetUserCmd(cmdNum, &cmd);
  if (cmd.serverTime <= cg.snap->ps.commandTime || cmd.serverTime > cg.time) { // special check for map_restart
    return;
  }

  // also add text in center of screen
  s = "Connection Interrupted";
  w = CG_DrawStrlen(s) * BIGCHAR_WIDTH;
  CG_DrawBigString(320 - w / 2, 100, s, 1.0F);

  // blink the icon
  if ((cg.time >> 9) & 1) {
    return;
  }

  x = 640 - 48;
  y = 480 - 48;

  CG_DrawPic(x, y, 48, 48, trap_R_RegisterShader("gfx/2d/net.tga"));
}

#define	MAX_LAGOMETER_PING	900
#define	MAX_LAGOMETER_RANGE	300

/*
 ==============
 CG_DrawLagometer
 ==============
 */
static void CG_DrawLagometer(void) {
  int a, x, y, i;
  float v;
  float ax, ay, aw, ah, mid, range;
  int color;
  float vscale;

  if (!cg_lagometer.integer || cgs.localServer) {
    CG_DrawDisconnect();
    return;
  }

  x = cg_lagometerX.integer;
  y = cg_lagometerY.integer;
  aw = 64;
  ah = 64;

  trap_R_SetColor(NULL);
  CG_DrawPic(x, y, ah, aw, cgs.media.lagometerShader);

  ax = x;
  ay = y;
  CG_AdjustFrom640(&ax, &ay, &aw, &ah);

  color = -1;
  range = ah / 3;
  mid = ay + range;

  vscale = range / MAX_LAGOMETER_RANGE;

  // draw the frame interpoalte / extrapolate graph
  for (a = 0; a < aw; a++) {
    i = (lagometer.frameCount - 1 - a) & (LAG_SAMPLES - 1);
    v = lagometer.frameSamples[i];
    v *= vscale;
    if (v > 0) {
      if (color != 1) {
        color = 1;
        trap_R_SetColor(g_color_table[ColorIndex(COLOR_YELLOW)]);
      }
      if (v > range) {
        v = range;
      }
      trap_R_DrawStretchPic(ax + aw - a, mid - v, 1, v, 0, 0, 0, 0, cgs.media.whiteShader);
    } else if (v < 0) {
      if (color != 2) {
        color = 2;
        trap_R_SetColor(g_color_table[ColorIndex(COLOR_BLUE)]);
      }
      v = -v;
      if (v > range) {
        v = range;
      }
      trap_R_DrawStretchPic(ax + aw - a, mid, 1, v, 0, 0, 0, 0, cgs.media.whiteShader);
    }
  }

  // draw the snapshot latency / drop graph
  range = ah / 2;
  vscale = range / MAX_LAGOMETER_PING;

  for (a = 0; a < aw; a++) {
    i = (lagometer.snapshotCount - 1 - a) & (LAG_SAMPLES - 1);
    v = lagometer.snapshotSamples[i];
    if (v > 0) {
      if (lagometer.snapshotFlags[i] & SNAPFLAG_RATE_DELAYED) {
        if (color != 5) {
          color = 5; // YELLOW for rate delay
          trap_R_SetColor(g_color_table[ColorIndex(COLOR_YELLOW)]);
        }
      } else {
        if (color != 3) {
          color = 3;
          trap_R_SetColor(g_color_table[ColorIndex(COLOR_GREEN)]);
        }
      }
      v = v * vscale;
      if (v > range) {
        v = range;
      }
      trap_R_DrawStretchPic(ax + aw - a, ay + ah - v, 1, v, 0, 0, 0, 0, cgs.media.whiteShader);
    } else if (v < 0) {
      if (color != 4) {
        color = 4; // RED for dropped snapshots
        trap_R_SetColor(g_color_table[ColorIndex(COLOR_RED)]);
      }
      trap_R_DrawStretchPic(ax + aw - a, ay + ah - range, 1, range, 0, 0, 0, 0, cgs.media.whiteShader);
    }
  }

  trap_R_SetColor(NULL);

  if (cg_nopredict.integer || cg_synchronousClients.integer) {
    CG_DrawBigString(ax, ay, "snc", 1.0);
  }

  CG_DrawDisconnect();
}

/*
 ===============================================================================

 CENTER PRINTING

 ===============================================================================
 */

/*
 ==============
 CG_CenterPrint

 Called for important messages that should stay in the center of the screen
 for a few moments
 ==============
 */
void CG_CenterPrint(const char *str, int y, int charWidth) {
  char *s;

  Q_strncpyz(cg.centerPrint, str, sizeof(cg.centerPrint));

  cg.centerPrintTime = cg.time;
  cg.centerPrintY = y;
  cg.centerPrintCharWidth = charWidth;

  // count the number of lines for centering
  cg.centerPrintLines = 1;
  s = cg.centerPrint;
  while (*s) {
    if (*s == '\n')
      cg.centerPrintLines++;
    s++;
  }
}

/*
 ===================
 CG_DrawCenterString
 ===================
 */
static void CG_DrawCenterString(void) {
  char *start;
  int l;
  int x, y, w;
  float *color;

  if (!cg.centerPrintTime) {
    return;
  }

  color = CG_FadeColor(cg.centerPrintTime, 1000 * cg_centertime.value);
  if (!color) {
    return;
  }

  trap_R_SetColor(color);

  start = cg.centerPrint;

  y = cg.centerPrintY - cg.centerPrintLines * BIGCHAR_HEIGHT / 2;

  while (1) {
    char linebuffer[1024];

    for (l = 0; l < 50; l++) {
      if (!start[l] || start[l] == '\n') {
        break;
      }
      linebuffer[l] = start[l];
    }
    linebuffer[l] = 0;

    w = cg.centerPrintCharWidth * CG_DrawStrlen(linebuffer);

    x = (SCREEN_WIDTH - w) / 2;

    CG_DrawStringExt(x, y, linebuffer, color, qfalse, qtrue, cg.centerPrintCharWidth, (int) (cg.centerPrintCharWidth * 1.5), 0);

    y += cg.centerPrintCharWidth * 1.5;
    while (*start && (*start != '\n')) {
      start++;
    }
    if (!*start) {
      break;
    }
    start++;
  }

  trap_R_SetColor(NULL);
}

/*
 ================================================================================

 CROSSHAIR

 ================================================================================
 */

/*
 =================
 CG_DrawCrosshair
 =================
 */
static void CG_DrawCrosshair(void) {
  qhandle_t hShader;
  float x, y, alpha, f, w, h;
  int ca;

  if (!cg_drawCrosshair.integer) {
    return;
  }

  if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR) {
    return;
  }

  if (cg.renderingThirdPerson) {
    return;
  }

  if ((cg.snap->ps.weapon == WP_BARRETT || cg.snap->ps.weapon == WP_CROSSBOW || cg.snap->ps.weapon == WP_INTERVENTION || cg.snap->ps.weapon == WP_BOMB)
      && cg.snap->ps.zoomFov <= 0) {
    return;
  }

  if (cg.snap->ps.sprintAdd > 10) {
    return;
  }

  if (cg.snap->ps.stats[STAT_HEALTH] <= 20) {
    return;
  }

  // set color based on health
  if (cg_crosshairHealth.integer) {
    vec4_t hcolor;

    CG_ColorForHealth(hcolor);
    trap_R_SetColor(hcolor);
  } else {
    trap_R_SetColor(NULL);
  }

  w = h = cg_crosshairSize.value;

  // pulse the size of the crosshair when picking up items
  f = cg.time - cg.itemPickupBlendTime;
  if (f > 0 && f < ITEM_BLOB_TIME) {
    f /= ITEM_BLOB_TIME;
    w *= (1 + f);
    h *= (1 + f);
  }

  x = cg_crosshairX.integer;
  y = cg_crosshairY.integer;
  CG_AdjustFrom640(&x, &y, &w, &h);

  ca = cg_drawCrosshair.integer;
  if (ca < 0) {
    ca = 0;
  }
  hShader = cgs.media.crosshairShader[ca % NUM_CROSSHAIRS];

  trap_R_DrawStretchPic(x + cg.refdef.x + 0.5 * (cg.refdef.width - w), y + cg.refdef.y + 0.5 * (cg.refdef.height - h), w, h, 0, 0, 1, 1, hShader);
}

/*
 =================
 CG_DrawCrosshair3D
 =================
 */
static void CG_DrawCrosshair3D(void) {
  float w, h;
  qhandle_t hShader;
  float f;
  int ca;

  trace_t trace;
  vec3_t endpos;
  float stereoSep, zProj, maxdist, xmax;
  char rendererinfos[128];
  refEntity_t ent;

  if (!cg_drawCrosshair.integer) {
    return;
  }

  if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR) {
    return;
  }

  if (cg.renderingThirdPerson) {
    return;
  }

  if ((cg.snap->ps.weapon == WP_BARRETT || cg.snap->ps.weapon == WP_CROSSBOW || cg.snap->ps.weapon == WP_INTERVENTION || cg.snap->ps.weapon == WP_BOMB)
      && cg.snap->ps.zoomFov <= 0) {
    return;
  }

  if (cg.snap->ps.sprintAdd > 10) {
    return;
  }

  if (cg.snap->ps.stats[STAT_HEALTH] <= 20) {
    return;
  }

  w = h = cg_crosshairSize.value;

  // pulse the size of the crosshair when picking up items
  f = cg.time - cg.itemPickupBlendTime;
  if (f > 0 && f < ITEM_BLOB_TIME) {
    f /= ITEM_BLOB_TIME;
    w *= (1 + f);
    h *= (1 + f);
  }

  ca = cg_drawCrosshair.integer;
  if (ca < 0) {
    ca = 0;
  }
  hShader = cgs.media.crosshairShader[ca % NUM_CROSSHAIRS];

  // Use a different method rendering the crosshair so players don't see two of them when
  // focusing their eyes at distant objects with high stereo separation
  // We are going to trace to the next shootable object and place the crosshair in front of it.

  // first get all the important renderer information
  trap_Cvar_VariableStringBuffer("r_zProj", rendererinfos, sizeof(rendererinfos));
  zProj = atof(rendererinfos);
  trap_Cvar_VariableStringBuffer("r_stereoSeparation", rendererinfos, sizeof(rendererinfos));
  stereoSep = zProj / atof(rendererinfos);

  xmax = zProj * tan(cg.refdef.fov_x * M_PI / 360.0f);

  // let the trace run through until a change in stereo separation of the crosshair becomes less than one pixel.
  maxdist = cgs.glconfig.vidWidth * stereoSep * zProj / (2 * xmax);
  VectorMA(cg.refdef.vieworg, maxdist, cg.refdef.viewaxis[0], endpos);
  CG_Trace(&trace, cg.refdef.vieworg, NULL, NULL, endpos, 0, MASK_SHOT);

  memset(&ent, 0, sizeof(ent));
  ent.reType = RT_SPRITE;
  ent.renderfx = RF_DEPTHHACK | RF_CROSSHAIR;

  VectorCopy(trace.endpos, ent.origin);

  // scale the crosshair so it appears the same size for all distances
  ent.radius = w / 640 * xmax * trace.fraction * maxdist / zProj;
  ent.customShader = hShader;

  trap_R_AddRefEntityToScene(&ent);
}

/*
 =================
 CG_ScanForCrosshairEntity
 =================
 */
static void CG_ScanForCrosshairEntity(void) {
  trace_t trace;
  vec3_t start, end;
  int content;
  int range = 512;

  if (cg.snap->ps.zoomFov <= 95) {
    range *= 2;
  } else if (cg.snap->ps.zoomFov <= 85) {
    range *= 3;
  } else if (cg.snap->ps.zoomFov <= 65) {
    range *= 5;
  }

  VectorCopy(cg.refdef.vieworg, start);
  VectorMA(start, range, cg.refdef.viewaxis[0], end);

  CG_Trace(&trace, start, vec3_origin, vec3_origin, end, cg.snap->ps.clientNum, CONTENTS_SOLID | CONTENTS_BODY);
  if (trace.entityNum >= MAX_CLIENTS) {
    return;
  }

  // if the player is in fog, don't show it
  content = trap_CM_PointContents(trace.endpos, 0);
  if (content & CONTENTS_FOG) {
    return;
  }

  // update the fade timer
  cg.crosshairClientNum = trace.entityNum;
  cg.crosshairClientTime = cg.time;
}

/*
 =====================
 CG_DrawCrosshairNames
 =====================
 */
static void CG_DrawCrosshairNames(void) {
  float *color;
  char *name;
  float w;

  if (!cg_drawCrosshair.integer) {
    return;
  }
  if (!cg_drawCrosshairNames.integer) {
    return;
  }
  if (cg.renderingThirdPerson) {
    return;
  }
  if (cg.snap->ps.blindTime > cg.snap->ps.levelTime) {
    return;
  }

  // scan the known entities to see if the crosshair is sighted on one
  CG_ScanForCrosshairEntity();

  // draw the name of the player being looked at
  color = CG_FadeColor(cg.crosshairClientTime, 1000);
  if (!color) {
    trap_R_SetColor(NULL);
    return;
  }

  name = cgs.clientinfo[cg.crosshairClientNum].name;
  w = CG_DrawStrlen(name) * BIGCHAR_WIDTH;
  CG_DrawBigString(320 - w / 2, 170, name, color[3] * 0.5f);
  trap_R_SetColor(NULL);
}

//==============================================================================

/*
 =================
 CG_DrawSpectator
 =================
 */
static void CG_DrawSpectator(void) {
  CG_DrawBigString(320 - 9 * 8, 440, "SPECTATOR", 1.0F);
}

/*
 =================
 CG_DrawVote
 =================
 */
static void CG_DrawVote(void) {
  char *s;
  int sec;

  if (!cgs.voteTime) {
    return;
  }

  // play a talk beep whenever it is modified
  if (cgs.voteModified) {
    cgs.voteModified = qfalse;
    trap_S_StartLocalSound(cgs.media.talkSound, CHAN_LOCAL_SOUND);
  }

  sec = (VOTE_TIME - (cg.time - cgs.voteTime)) / 1000;
  if (sec < 0) {
    sec = 0;
  }
  s = va("VOTE(%i):%s yes:%i no:%i", sec, cgs.voteString, cgs.voteYes, cgs.voteNo);
  CG_DrawSmallString(0, 58, s, 1.0F);
}

/*
 =================
 CG_DrawTeamVote
 =================
 */
static void CG_DrawTeamVote(void) {
  char *s;
  int sec, cs_offset;

  if (cgs.clientinfo->team == TEAM_RED)
    cs_offset = 0;
  else if (cgs.clientinfo->team == TEAM_BLUE)
    cs_offset = 1;
  else
    return;

  if (!cgs.teamVoteTime[cs_offset]) {
    return;
  }

  // play a talk beep whenever it is modified
  if (cgs.teamVoteModified[cs_offset]) {
    cgs.teamVoteModified[cs_offset] = qfalse;
    trap_S_StartLocalSound(cgs.media.talkSound, CHAN_LOCAL_SOUND);
  }

  sec = (VOTE_TIME - (cg.time - cgs.teamVoteTime[cs_offset])) / 1000;
  if (sec < 0) {
    sec = 0;
  }
  s = va("TEAMVOTE(%i):%s yes:%i no:%i", sec, cgs.teamVoteString[cs_offset], cgs.teamVoteYes[cs_offset], cgs.teamVoteNo[cs_offset]);
  CG_DrawSmallString(0, 90, s, 1.0F);
}

static qboolean CG_DrawScoreboard(void) {
#ifdef MISSIONPACK
  static qboolean firstTime = qtrue;
  float fade, *fadeColor;

  if (menuScoreboard) {
    menuScoreboard->window.flags &= ~WINDOW_FORCED;
  }
  if (cg_paused.integer) {
    cg.deferredPlayerLoading = 0;
    firstTime = qtrue;
    return qfalse;
  }

  // should never happen in Team Arena
  if (cgs.gametype == GT_SINGLE_PLAYER && cg.predictedPlayerState.pm_type == PM_INTERMISSION) {
    cg.deferredPlayerLoading = 0;
    firstTime = qtrue;
    return qfalse;
  }

  // don't draw scoreboard during death while warmup up
  if (cg.warmup && !cg.showScores) {
    return qfalse;
  }

  if (cg.showScores || cg.predictedPlayerState.pm_type == PM_DEAD || cg.predictedPlayerState.pm_type == PM_INTERMISSION) {
    fade = 1.0;
    fadeColor = colorWhite;
  } else {
    fadeColor = CG_FadeColor(cg.scoreFadeTime, FADE_TIME);
    if (!fadeColor) {
      // next time scoreboard comes up, don't print killer
      cg.deferredPlayerLoading = 0;
      cg.killerName[0] = 0;
      firstTime = qtrue;
      return qfalse;
    }
    fade = *fadeColor;
  }

  if (menuScoreboard == NULL) {
    if (cgs.gametype == GT_TEAMSURVIVOR) {
      menuScoreboard = Menus_FindByName("teamscore_menu");
    } else {
      menuScoreboard = Menus_FindByName("score_menu");
    }
  }

  if (menuScoreboard) {
    if (firstTime) {
      CG_SetScoreSelection(menuScoreboard);
      firstTime = qfalse;
    }
    Menu_Paint(menuScoreboard, qtrue);
  }

  // load any models that have been deferred
  if (++cg.deferredPlayerLoading > 10) {
    CG_LoadDeferredPlayers();
  }

  return qtrue;
#else
  return CG_DrawOldScoreboard();
#endif
}

/*
 =================
 CG_DrawIntermission
 =================
 */
static void CG_DrawIntermission(void) {
  if (cgs.gametype == GT_SINGLE_PLAYER) {
    CG_DrawCenterString();
    return;
  }
  cg.scoreFadeTime = cg.time;
  cg.scoreBoardShowing = CG_DrawScoreboard();
}

/*
 =================
 CG_DrawFollow
 =================
 */
static qboolean CG_DrawFollow(void) {
  float x;
  vec4_t color;
  const char *name;

  if (!(cg.snap->ps.pm_flags & PMF_FOLLOW)) {
    return qfalse;
  }
  color[0] = 1;
  color[1] = 1;
  color[2] = 1;
  color[3] = 1;

  CG_DrawBigString(320 - 9 * 8, 24, "following", 1.0F);

  name = cgs.clientinfo[cg.snap->ps.clientNum].name;

  x = 0.5 * (640 - GIANT_WIDTH * CG_DrawStrlen(name));

  CG_DrawStringExt(x, 40, name, color, qtrue, qtrue, GIANT_WIDTH, GIANT_HEIGHT, 0);

  return qtrue;
}

/*
 =================
 CG_DrawAmmoWarning
 =================
 */
static void CG_DrawAmmoWarning(void) {
  const char *s;
  int w;

  if (cg_drawAmmoWarning.integer == 0) {
    return;
  }

  if (!cg.lowAmmoWarning) {
    return;
  }

  if (cg.lowAmmoWarning == 2) {
    s = "OUT OF AMMO";
  } else {
    s = "LOW AMMO WARNING";
  }
  w = CG_DrawStrlen(s) * BIGCHAR_WIDTH;
  CG_DrawBigString(320 - w / 2, 64, s, 1.0F);
}

/*
 =================
 CG_DrawWarmup
 =================
 */
static void CG_DrawWarmup(void) {
  int w;
  int sec;
  float scale;
  int cw;
  const char *s;

  sec = cg.warmup;
  if (!sec) {
    return;
  }

  if (sec < 0) {
    s = "Waiting for players...";
    w = CG_DrawStrlen(s) * BIGCHAR_WIDTH;
    CG_DrawBigString(320 - w / 2, 24, s, 1.0F);
    cg.warmupCount = 0;
    return;
  }

  if (cgs.gametype == GT_FFA) {
    s = "Free For All";
  } else if (cgs.gametype == GT_TEAMSURVIVOR) {
    s = "Team Survivor";
  } else if (cgs.gametype == GT_TEAMDEATHMATCH) {
    s = "Team Deathmatch";
  } else if (cgs.gametype == GT_ASSASSINS) {
    s = "Assassins";
  } else if (cgs.gametype == GT_SINGLE_PLAYER) {
    s = "Mission";
  } else if (cgs.gametype == GT_FREEZETAG) {
    s = "Freeze Tag";
  } else if (cgs.gametype == GT_ZONEFIGHT) {
    s = "Zone Fight";
  } else {
    s = "wtf?";
  }
  w = CG_DrawStrlen(s);
  if (w > 640 / GIANT_WIDTH) {
    cw = 640 / w;
  } else {
    cw = GIANT_WIDTH;
  }
  CG_DrawStringExt(320 - w * cw / 2, 25, s, colorWhite, qfalse, qtrue, cw, (int) (cw * 1.1f), 0);

  sec = (sec - cg.time) / 1000;
  if (sec < 0) {
    cg.warmup = 0;
    sec = 0;
  }
  s = va("Starts in %i seconds", sec + 1);
  if (sec != cg.warmupCount) {
    cg.warmupCount = sec;
    switch (sec) {
      case 0:
        trap_S_StartLocalSound(cgs.media.count1Sound, CHAN_ANNOUNCER);
        break;
      case 1:
        trap_S_StartLocalSound(cgs.media.count2Sound, CHAN_ANNOUNCER);
        break;
      case 2:
        trap_S_StartLocalSound(cgs.media.count3Sound, CHAN_ANNOUNCER);
        break;
      default:
        break;
    }
  }
  scale = 0.45f;
  switch (cg.warmupCount) {
    case 0:
      cw = 28;
      scale = 0.54f;
      break;
    case 1:
      cw = 24;
      scale = 0.51f;
      break;
    case 2:
      cw = 20;
      scale = 0.48f;
      break;
    default:
      cw = 16;
      scale = 0.45f;
      break;
  }

  w = CG_DrawStrlen(s);
  CG_DrawStringExt(320 - w * cw / 2, 70, s, colorWhite, qfalse, qtrue, cw, (int) (cw * 1.5), 0);
}

//==================================================================================

/*
 =================
 CG_Draw2D
 =================
 */
static void CG_Draw2D(stereoFrame_t stereoFrame) {
  // if we are taking a levelshot for the menu, don't draw anything
  if (cg.levelShot) {
    return;
  }

  // ignore any cvar settings, this needs to be drawn all the time
  CG_DrawDamagePic();

  if (cg_draw2D.integer == 0) {
    return;
  }

  if (cg.snap->ps.pm_type == PM_INTERMISSION) {
    CG_DrawIntermission();
    return;
  }

  CG_DrawKillfeed();

  /*
   if (cg.cameraMode) {
   return;
   }
   */
  if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR) {
    CG_DrawSpectator();

    if (stereoFrame == STEREO_CENTER)
      CG_DrawCrosshair();

    CG_DrawCrosshairNames();
  } else {
    // don't draw any status if dead or the scoreboard is being explicitly shown
    if (!cg.showScores && cg.snap->ps.stats[STAT_HEALTH] > 0) {

      CG_DrawStatusBar();

      CG_DrawAmmoWarning();

      if (stereoFrame == STEREO_CENTER)
        CG_DrawCrosshair();
      CG_DrawCrosshairNames();
      CG_DrawWeaponSelect();
      CG_DrawHoldableItem();
      CG_DrawReward();
    }

    if (cgs.gametype == GT_TEAMSURVIVOR || cgs.gametype == GT_ASSASSINS) {
      CG_DrawTeamInfo();
    }
  }

  CG_DrawVote();
  CG_DrawTeamVote();

  CG_DrawLagometer();

  CG_DrawUpperRight(stereoFrame);
  CG_DrawLowerLeft();

  if (!CG_DrawFollow()) {
    CG_DrawWarmup();
  }

  // don't draw center string if scoreboard is up
  cg.scoreBoardShowing = CG_DrawScoreboard();
  if (!cg.scoreBoardShowing) {
    CG_DrawCenterString();
  }
}

static void CG_DrawTourneyScoreboard(void) {
  CG_DrawOldTourneyScoreboard();
}

/*
 =====================
 CG_DrawActive

 Perform all drawing needed to completely fill the screen
 =====================
 */
void CG_DrawActive(stereoFrame_t stereoView) {
  // optionally draw the info screen instead
  if (!cg.snap) {
    CG_DrawInformation();
    return;
  }

  // optionally draw the tournement scoreboard instead
  if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR && (cg.snap->ps.pm_flags & PMF_SCOREBOARD)) {
    CG_DrawTourneyScoreboard();
    return;
  }

  // clear around the rendered view if sized down
  CG_TileClear();

  if (stereoView != STEREO_CENTER)
    CG_DrawCrosshair3D();

  // draw 3D view
  trap_R_RenderScene(&cg.refdef);

  if (cg.snap->ps.zoomFov > 0 && cg_scopeType.integer) {
    trap_R_RenderScene(&cg.zoomRefdef);
  }

  // draw status bar and other floating elements
  CG_Draw2D(stereoView);
}

