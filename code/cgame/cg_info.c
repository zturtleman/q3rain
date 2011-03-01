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
// cg_info.c -- display information while data is being loading

#include "cg_local.h"

#define MAX_LOADING_PLAYER_ICONS	16
#define MAX_LOADING_ITEM_ICONS		26

static int loadingPlayerIconCount;
static int loadingItemIconCount;
static qhandle_t loadingPlayerIcons[MAX_LOADING_PLAYER_ICONS];
static qhandle_t loadingItemIcons[MAX_LOADING_ITEM_ICONS];

/*
 ===================
 CG_DrawLoadingIcons
 ===================
 */
static void CG_DrawLoadingIcons(void) {
  int n;
  int x, y;

  for (n = 0; n < loadingPlayerIconCount; n++) {
    x = 32 + n * 78;
    y = 324 - 40;
    CG_DrawPic(x, y, 64, 64, loadingPlayerIcons[n]);
  }

  for (n = 0; n < loadingItemIconCount; n++) {
    y = 400 - 40;
    if (n >= 13) {
      y -= 40;
    }
    x = 32 + n % 13 * 48;
    CG_DrawPic(x, y, 32, 32, loadingItemIcons[n]);
  }
}

/*
 ======================
 CG_LoadingString

 ======================
 */
void CG_LoadingString(const char *s) {
  Q_strncpyz(cg.infoScreenText, s, sizeof(cg.infoScreenText));

  trap_UpdateScreen();
}

/*
 ===================
 CG_LoadingItem
 ===================
 */
void CG_LoadingItem(int itemNum) {
  gitem_t *item;

  item = &bg_itemlist[itemNum];

  if (item->icon && loadingItemIconCount < MAX_LOADING_ITEM_ICONS) {
    loadingItemIcons[loadingItemIconCount++] = trap_R_RegisterShaderNoMip(item->icon);
  }

  CG_LoadingString(item->pickup_name);
}

/*
 ===================
 CG_LoadingClient
 ===================
 */
void CG_LoadingClient(int clientNum) {
  const char *info;
  char *skin;
  char personality[MAX_QPATH];
  char model[MAX_QPATH];
  char iconName[MAX_QPATH];

  info = CG_ConfigString(CS_PLAYERS + clientNum);

  if (loadingPlayerIconCount < MAX_LOADING_PLAYER_ICONS) {
    Q_strncpyz(model, Info_ValueForKey(info, "model"), sizeof(model));
    skin = Q_strrchr(model, '/');
    if (skin) {
      *skin++ = '\0';
    } else {
      skin = "default";
    }

    Com_sprintf(iconName, MAX_QPATH, "models/players/%s/icon_%s.tga", model, skin);

    loadingPlayerIcons[loadingPlayerIconCount] = trap_R_RegisterShaderNoMip(iconName);
    if (!loadingPlayerIcons[loadingPlayerIconCount]) {
      Com_sprintf(iconName, MAX_QPATH, "models/players/characters/%s/icon_%s.tga", model, skin);
      loadingPlayerIcons[loadingPlayerIconCount] = trap_R_RegisterShaderNoMip(iconName);
    }
    if (!loadingPlayerIcons[loadingPlayerIconCount]) {
      Com_sprintf(iconName, MAX_QPATH, "models/players/%s/icon_%s.tga", DEFAULT_MODEL, "default");
      loadingPlayerIcons[loadingPlayerIconCount] = trap_R_RegisterShaderNoMip(iconName);
    }
    if (loadingPlayerIcons[loadingPlayerIconCount]) {
      loadingPlayerIconCount++;
    }
  }

  Q_strncpyz(personality, Info_ValueForKey(info, "n"), sizeof(personality));
  Q_CleanStr(personality);

  if (cgs.gametype == GT_SINGLE_PLAYER) {
    trap_S_RegisterSound(va("sound/player/announce/%s.wav", personality), qtrue);
  }

  CG_LoadingString(personality);
}

/*
 ====================
 CG_DrawInformation

 Draw all the status / pacifier stuff during level loading
 ====================
 */
void CG_DrawInformation(void) {
  const char *s;
  const char *info;
  const char *sysInfo;
  const char *gt;
  int y, i;
  int value;
  qhandle_t levelshot, overlay;
  char buf[1024];
  qboolean pure, cheats;
  int size = 10;

  info = CG_ConfigString(CS_SERVERINFO);
  sysInfo = CG_ConfigString(CS_SYSTEMINFO);

  s = Info_ValueForKey(info, "mapname");
  levelshot = trap_R_RegisterShaderNoMip(va("levelshots/%s", s));
  overlay = trap_R_RegisterShaderNoMip("levelshots/overlay.png");
  if (!levelshot) {
    levelshot = trap_R_RegisterShaderNoMip("menu/art/unknownmap");
  }
  trap_R_SetColor(NULL);
  CG_DrawPic(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, levelshot);

  // draw the icons of things as they are loaded
  //CG_DrawLoadingIcons();

  // the first 150 rows are reserved for the client connection
  // screen to write into
  if (cg.infoScreenText[0]) {
    CG_DrawStringExt(32, 96, va("Loading %s...", cg.infoScreenText), colorWhite, qfalse, qfalse, size, size * 2, 512);
  } else {
    CG_DrawStringExt(32, 96, "Awaiting snapshot...", colorWhite, qtrue, qfalse, size, size * 2, 64);
  }

  //CG_ParseMapData(s);

  // don't print server lines if playing a local game
  trap_Cvar_VariableStringBuffer("sv_running", buf, sizeof(buf));
  if (!atoi(buf)) {
    // game type
    switch (cgs.gametype) {
      case GT_FFA:
        gt = "FFA";
        break;
      case GT_SINGLE_PLAYER:
        gt = "SP";
        break;
      case GT_ASSASSINS:
        gt = "ASS"; // :D
        break;
      case GT_TEAMDEATHMATCH:
        gt = "TDM";
        break;
      case GT_TEAMSURVIVOR:
        gt = "TS";
        break;
      case GT_FREEZETAG:
        gt = "FT";
        break;
      default:
        gt = "Unknown,";
        break;
    }
    pure = cheats = qfalse;
    // pure/cheat server
    s = Info_ValueForKey(sysInfo, "sv_pure");
    if (s[0] == '1') {
      pure = qtrue;
    }
    s = Info_ValueForKey(sysInfo, "sv_cheats");
    if (s[0] == '1') {
      cheats = qtrue;
    }
    if (pure && cheats) {
      s = "Pure + Cheats";
    } else if (pure && !cheats) {
      s = "Pure";
    } else if (!pure && cheats) {
      s = "Unpure + Cheats";
    } else if (!pure && !cheats) {
      s = "Unpure";
    }
    // server hostname
    Q_strncpyz(buf, Info_ValueForKey(info, "sv_hostname"), 1024);
    Q_CleanStr(buf);
    CG_DrawStringExt(32, 32, va("%s (%s, %s)", buf, gt, s), colorWhite, qfalse, qfalse, size, size * 2, 64);

    // server-specific message of the day
    s = CG_ConfigString(CS_MOTD);
    if (s[0]) {
      CG_DrawStringExt(32, 64, s, colorWhite, qfalse, qfalse, size, size * 2, 512);
    }
  }

  // map-specific message (long map name)
  s = CG_ConfigString(CS_MESSAGE);
  if (s[0]) {
    CG_DrawStringExt(32, 400, s, colorWhite, qfalse, qfalse, size, size * 2, 256);
  }
  s = CG_ConfigString(CS_LOCATION);
  if (s[0]) {
    CG_DrawStringExt(32, 400 + size * 3, s, colorWhite, qfalse, qfalse, size, size * 2, 256);
  }

  s = CG_ConfigString(CS_TEMPERATURE);
  i = atoi(s);
  // maps should set their temp in °C
  // FIXME needs ° in charset
  if (!Q_stricmp(cg_temperatureUnit.string, "F")) {
    i = i * (9.0 / 5.0) + 32;
    s = va("%i Degrees F", i);
  } else if (!Q_stricmp(cg_temperatureUnit.string, "K")) {
    s = va("%i Degrees K", i + 273);
  } else {
    s = va("%i Degrees C", i);
  }
  CG_DrawStringExt(448, 400, s, colorWhite, qfalse, qfalse, size, size * 2, 1024);

  s = CG_ConfigString(CS_WEATHER);
  if (s[0]) {
    CG_DrawStringExt(448, 400 + size * 3, s, colorWhite, qfalse, qfalse, size, size * 2, 256);
  }
}

