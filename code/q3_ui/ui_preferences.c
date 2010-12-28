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
/*
=======================================================================

GAME OPTIONS MENU

=======================================================================
 */


#include "ui_local.h"


#define ART_FRAMEL			"menu/art/frame2_l"
#define ART_FRAMER			"menu/art/frame1_r"
#define ART_BACK0			"menu/art/back_0"
#define ART_BACK1			"menu/art/back_1"

#define PREFERENCES_X_POS		360

#define ID_CROSSHAIR			127
#define ID_SYNCEVERYFRAME		128
#define ID_ALLOWDOWNLOAD		129
#define ID_BACK				130
#define ID_IDENTIFYTARGET               131

#define	NUM_CROSSHAIRS			10

typedef struct {
    menuframework_s menu;

    menutext_s banner;
    menubitmap_s framel;
    menubitmap_s framer;

    menulist_s crosshair;
    menuradiobutton_s identifytarget;
    menuradiobutton_s synceveryframe;
    menuradiobutton_s allowdownload;
    menubitmap_s back;

    qhandle_t crosshairShader[NUM_CROSSHAIRS];
} preferences_t;

static preferences_t s_preferences;

static const char *teamoverlay_names[] = {
    "off",
    "upper right",
    "lower right",
    "lower left",
    NULL
};

static void Preferences_SetMenuItems(void) {
    s_preferences.crosshair.curvalue = (int) trap_Cvar_VariableValue("cg_drawCrosshair") % NUM_CROSSHAIRS;
    s_preferences.identifytarget.curvalue = trap_Cvar_VariableValue("cg_drawCrosshairNames") != 0;
    s_preferences.synceveryframe.curvalue = trap_Cvar_VariableValue("r_finish") != 0;
    s_preferences.allowdownload.curvalue = trap_Cvar_VariableValue("cl_allowDownload") != 0;
}

static void Preferences_Event(void* ptr, int notification) {
    if (notification != QM_ACTIVATED) {
        return;
    }

    switch (((menucommon_s*) ptr)->id) {
        case ID_CROSSHAIR:
            s_preferences.crosshair.curvalue++;
            if (s_preferences.crosshair.curvalue == NUM_CROSSHAIRS) {
                s_preferences.crosshair.curvalue = 0;
            }
            trap_Cvar_SetValue("cg_drawCrosshair", s_preferences.crosshair.curvalue);
            break;

        case ID_IDENTIFYTARGET:
            trap_Cvar_SetValue("cg_drawCrosshairNames", s_preferences.identifytarget.curvalue);
            break;

        case ID_SYNCEVERYFRAME:
            trap_Cvar_SetValue("r_finish", s_preferences.synceveryframe.curvalue);
            break;

        case ID_ALLOWDOWNLOAD:
            trap_Cvar_SetValue("cl_allowDownload", s_preferences.allowdownload.curvalue);
            trap_Cvar_SetValue("sv_allowDownload", s_preferences.allowdownload.curvalue);
            break;

        case ID_BACK:
            UI_PopMenu();
            break;
    }
}

/*
=================
Crosshair_Draw
=================
 */
static void Crosshair_Draw(void *self) {
    menulist_s *s;
    float *color;
    int x, y;
    int style;
    qboolean focus;

    s = (menulist_s *) self;
    x = s->generic.x;
    y = s->generic.y;

    style = UI_SMALLFONT;
    focus = (s->generic.parent->cursor == s->generic.menuPosition);

    if (s->generic.flags & QMF_GRAYED)
        color = text_color_disabled;
    else if (focus) {
        color = text_color_highlight;
        style |= UI_PULSE;
    } else if (s->generic.flags & QMF_BLINK) {
        color = text_color_highlight;
        style |= UI_BLINK;
    } else
        color = text_color_normal;

    if (focus) {
        // draw cursor
        UI_FillRect(s->generic.left, s->generic.top, s->generic.right - s->generic.left + 1, s->generic.bottom - s->generic.top + 1, listbar_color);
        UI_DrawChar(x, y, 13, UI_CENTER | UI_BLINK | UI_SMALLFONT, color);
    }

    UI_DrawString(x - SMALLCHAR_WIDTH, y, s->generic.name, style | UI_RIGHT, color);
    if (!s->curvalue) {
        return;
    }
    UI_DrawHandlePic(x + SMALLCHAR_WIDTH, y - 4, 24, 24, s_preferences.crosshairShader[s->curvalue]);
}

static void Preferences_MenuInit(void) {
    int y;

    memset(&s_preferences, 0, sizeof (preferences_t));

    Preferences_Cache();

    s_preferences.menu.wrapAround = qtrue;
    s_preferences.menu.fullscreen = qtrue;

    s_preferences.banner.generic.type = MTYPE_BTEXT;
    s_preferences.banner.generic.x = 320;
    s_preferences.banner.generic.y = 16;
    s_preferences.banner.string = "GAME OPTIONS";
    s_preferences.banner.color = color_white;
    s_preferences.banner.style = UI_CENTER;

    s_preferences.framel.generic.type = MTYPE_BITMAP;
    s_preferences.framel.generic.name = ART_FRAMEL;
    s_preferences.framel.generic.flags = QMF_INACTIVE;
    s_preferences.framel.generic.x = 0;
    s_preferences.framel.generic.y = 78;
    s_preferences.framel.width = 256;
    s_preferences.framel.height = 329;

    s_preferences.framer.generic.type = MTYPE_BITMAP;
    s_preferences.framer.generic.name = ART_FRAMER;
    s_preferences.framer.generic.flags = QMF_INACTIVE;
    s_preferences.framer.generic.x = 376;
    s_preferences.framer.generic.y = 76;
    s_preferences.framer.width = 256;
    s_preferences.framer.height = 334;

    y = 144;
    s_preferences.crosshair.generic.type = MTYPE_TEXT;
    s_preferences.crosshair.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT | QMF_NODEFAULTINIT | QMF_OWNERDRAW;
    s_preferences.crosshair.generic.x = PREFERENCES_X_POS;
    s_preferences.crosshair.generic.y = y;
    s_preferences.crosshair.generic.name = "Crosshair:";
    s_preferences.crosshair.generic.callback = Preferences_Event;
    s_preferences.crosshair.generic.ownerdraw = Crosshair_Draw;
    s_preferences.crosshair.generic.id = ID_CROSSHAIR;
    s_preferences.crosshair.generic.top = y - 4;
    s_preferences.crosshair.generic.bottom = y + 20;
    s_preferences.crosshair.generic.left = PREFERENCES_X_POS - ((strlen(s_preferences.crosshair.generic.name) + 1) * SMALLCHAR_WIDTH);
    s_preferences.crosshair.generic.right = PREFERENCES_X_POS + 48;

    y += BIGCHAR_HEIGHT + 2;
    s_preferences.identifytarget.generic.type = MTYPE_RADIOBUTTON;
    s_preferences.identifytarget.generic.name = "Identify Target:";
    s_preferences.identifytarget.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
    s_preferences.identifytarget.generic.callback = Preferences_Event;
    s_preferences.identifytarget.generic.id = ID_IDENTIFYTARGET;
    s_preferences.identifytarget.generic.x = PREFERENCES_X_POS;
    s_preferences.identifytarget.generic.y = y;

    y += BIGCHAR_HEIGHT + 2;
    s_preferences.synceveryframe.generic.type = MTYPE_RADIOBUTTON;
    s_preferences.synceveryframe.generic.name = "Sync Every Frame:";
    s_preferences.synceveryframe.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
    s_preferences.synceveryframe.generic.callback = Preferences_Event;
    s_preferences.synceveryframe.generic.id = ID_SYNCEVERYFRAME;
    s_preferences.synceveryframe.generic.x = PREFERENCES_X_POS;
    s_preferences.synceveryframe.generic.y = y;

    y += BIGCHAR_HEIGHT + 2;
    s_preferences.allowdownload.generic.type = MTYPE_RADIOBUTTON;
    s_preferences.allowdownload.generic.name = "Automatic Downloading:";
    s_preferences.allowdownload.generic.flags = QMF_PULSEIFFOCUS | QMF_SMALLFONT;
    s_preferences.allowdownload.generic.callback = Preferences_Event;
    s_preferences.allowdownload.generic.id = ID_ALLOWDOWNLOAD;
    s_preferences.allowdownload.generic.x = PREFERENCES_X_POS;
    s_preferences.allowdownload.generic.y = y;

    y += BIGCHAR_HEIGHT + 2;
    s_preferences.back.generic.type = MTYPE_BITMAP;
    s_preferences.back.generic.name = ART_BACK0;
    s_preferences.back.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
    s_preferences.back.generic.callback = Preferences_Event;
    s_preferences.back.generic.id = ID_BACK;
    s_preferences.back.generic.x = 0;
    s_preferences.back.generic.y = 480 - 64;
    s_preferences.back.width = 128;
    s_preferences.back.height = 64;
    s_preferences.back.focuspic = ART_BACK1;

    Menu_AddItem(&s_preferences.menu, &s_preferences.banner);
    Menu_AddItem(&s_preferences.menu, &s_preferences.framel);
    Menu_AddItem(&s_preferences.menu, &s_preferences.framer);

    Menu_AddItem(&s_preferences.menu, &s_preferences.crosshair);
    Menu_AddItem(&s_preferences.menu, &s_preferences.identifytarget);
    Menu_AddItem(&s_preferences.menu, &s_preferences.synceveryframe);
    Menu_AddItem(&s_preferences.menu, &s_preferences.allowdownload);

    Menu_AddItem(&s_preferences.menu, &s_preferences.back);

    Preferences_SetMenuItems();
}

/*
===============
Preferences_Cache
===============
 */
void Preferences_Cache(void) {
    int n;

    trap_R_RegisterShaderNoMip(ART_FRAMEL);
    trap_R_RegisterShaderNoMip(ART_FRAMER);
    trap_R_RegisterShaderNoMip(ART_BACK0);
    trap_R_RegisterShaderNoMip(ART_BACK1);
    for (n = 0; n < NUM_CROSSHAIRS; n++) {
        s_preferences.crosshairShader[n] = trap_R_RegisterShaderNoMip(va("gfx/2d/crosshair%c", 'a' + n));
    }
}

/*
===============
UI_PreferencesMenu
===============
 */
void UI_PreferencesMenu(void) {
    Preferences_MenuInit();
    UI_PushMenu(&s_preferences.menu);
}
