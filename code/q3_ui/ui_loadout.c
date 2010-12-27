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
#include "ui_local.h"

/*
===============================================================================

WEAPON LOADOUT SCREEN

===============================================================================
 */


#include "ui_local.h"


#define ART_FRAME		"menu/art/cut_frame"
#define ART_ACCEPT0		"menu/art/accept_0"
#define ART_ACCEPT1		"menu/art/accept_1"
#define ART_BACK0		"menu/art/back_0"
#define ART_BACK1		"menu/art/back_1"

#define ID_NICKNAME		10
#define ID_PASSWORD             11
#define ID_ACCEPT		12
#define ID_BACK			13

#define ID_BARRETT 20
#define ID_HE 21
#define ID_INTERVENTION 22
#define ID_CROSSBOW 23
#define ID_WALTHER 24
#define ID_ACR 25
#define ID_BOMB 26
#define ID_INJECTOR 27

#define WEAPON_SPACING 24

typedef struct {
    menuframework_s menu;

    menutext_s banner;
    menubitmap_s frame;

    menutext_s barrett;
    menutext_s intervention;
    menutext_s crossbow;
    menutext_s acr;

    menutext_s walther;

    menutext_s he;

    menutext_s bomb;
    menutext_s injector;

    menubitmap_s accept;
    menubitmap_s back;
} loadoutMenuInfo_t;

static loadoutMenuInfo_t loadoutMenuInfo;

/*
===============
UI_LoadoutMenu_Event
===============
 */
static void UI_LoadoutMenu_Event(void *ptr, int event) {
    char *msg;

    if (event != QM_ACTIVATED) {
        return;
    }

    switch (((menucommon_s*) ptr)->id) {
        case ID_BARRETT:
            msg = va("seta cg_primary %i\n", WP_BARRETT);
            trap_Cmd_ExecuteText(EXEC_INSERT, msg);
            break;
        case ID_INTERVENTION:
            msg = va("seta cg_primary %i\n", WP_INTERVENTION);
            trap_Cmd_ExecuteText(EXEC_INSERT, msg);
            break;
        case ID_CROSSBOW:
            msg = va("seta cg_primary %i\n", WP_CROSSBOW);
            trap_Cmd_ExecuteText(EXEC_INSERT, msg);
            break;
        case ID_ACR:
            msg = va("seta cg_primary %i\n", WP_ACR);
            trap_Cmd_ExecuteText(EXEC_INSERT, msg);
            break;

        case ID_WALTHER:
            msg = va("seta cg_pistol %i\n", WP_WALTHER);
            trap_Cmd_ExecuteText(EXEC_INSERT, msg);
            break;

        case ID_HE:
            msg = va("seta cg_grenade %i\n", WP_HE);
            trap_Cmd_ExecuteText(EXEC_INSERT, msg);
            break;

        case ID_BOMB:
            msg = va("seta cg_misc %i\n", WP_BOMB);
            trap_Cmd_ExecuteText(EXEC_INSERT, msg);
            break;
        case ID_INJECTOR:
            msg = va("seta cg_misc %i\n", WP_INJECTOR);
            trap_Cmd_ExecuteText(EXEC_INSERT, msg);
            break;

        case ID_ACCEPT:
            UI_PopMenu();
            break;

        case ID_BACK:
            UI_PopMenu();
            break;
    }
}

/*
=================
UI_LoadoutMenu_DrawNickname
=================
 */

static void UI_LoadoutMenu_DrawWeapons(void *self) {
    menufield_s *f;
    qboolean focus;
    int style;
    char c;
    float *color;
    int x, y;
    int val;

    f = (menufield_s *) self;

    focus = (f->generic.parent->cursor == f->generic.menuPosition);

    style = UI_LEFT;
    if (focus) {
        color = color_yellow;
    } else {
        color = color_orange;
    }
}

/*
=================
UI_LoadoutMenu_Cache
=================
 */
void UI_LoadoutMenu_Cache(void) {
    trap_R_RegisterShaderNoMip(ART_ACCEPT0);
    trap_R_RegisterShaderNoMip(ART_ACCEPT1);
    trap_R_RegisterShaderNoMip(ART_BACK0);
    trap_R_RegisterShaderNoMip(ART_BACK1);
    trap_R_RegisterShaderNoMip(ART_FRAME);
}

/*
=================
UI_LoadoutMenu_Draw
=================
 */
static void UI_LoadoutMenu_Draw(void) {
    Menu_Draw(&loadoutMenuInfo.menu);
}

/*
===============
UI_LoadoutMenu_Init
===============
 */
static void UI_LoadoutMenu_Init(void) {
    int y;
    UI_LoadoutMenu_Cache();

    memset(&loadoutMenuInfo, 0, sizeof (loadoutMenuInfo));
    loadoutMenuInfo.menu.wrapAround = qtrue;
    loadoutMenuInfo.menu.fullscreen = qfalse;

    loadoutMenuInfo.banner.generic.type = MTYPE_BTEXT;
    loadoutMenuInfo.banner.generic.x = 320;
    loadoutMenuInfo.banner.generic.y = 16;
    loadoutMenuInfo.banner.string = "WEAPONS";
    loadoutMenuInfo.banner.color = color_white;
    loadoutMenuInfo.banner.style = UI_CENTER;

    loadoutMenuInfo.frame.generic.type = MTYPE_BITMAP;
    loadoutMenuInfo.frame.generic.name = ART_FRAME;
    loadoutMenuInfo.frame.generic.flags = QMF_INACTIVE;
    loadoutMenuInfo.frame.generic.x = 32;
    loadoutMenuInfo.frame.generic.y = 24;
    loadoutMenuInfo.frame.width = 576;
    loadoutMenuInfo.frame.height = 432;

    y = 64;
    loadoutMenuInfo.barrett.generic.type = MTYPE_PTEXT;
    loadoutMenuInfo.barrett.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
    loadoutMenuInfo.barrett.generic.callback = UI_LoadoutMenu_Event;
    loadoutMenuInfo.barrett.generic.id = ID_BARRETT;
    loadoutMenuInfo.barrett.generic.x = 32;
    loadoutMenuInfo.barrett.generic.y = y;
    loadoutMenuInfo.barrett.string = "Barrett M82A1";
    loadoutMenuInfo.barrett.color = color_white;
    loadoutMenuInfo.barrett.style = UI_LEFT | UI_SMALLFONT;

    y += WEAPON_SPACING;
    loadoutMenuInfo.intervention.generic.type = MTYPE_PTEXT;
    loadoutMenuInfo.intervention.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
    loadoutMenuInfo.intervention.generic.callback = UI_LoadoutMenu_Event;
    loadoutMenuInfo.intervention.generic.id = ID_INTERVENTION;
    loadoutMenuInfo.intervention.generic.x = 32;
    loadoutMenuInfo.intervention.generic.y = y;
    loadoutMenuInfo.intervention.string = "Cheytac M200 Intervention";
    loadoutMenuInfo.intervention.color = color_white;
    loadoutMenuInfo.intervention.style = UI_LEFT | UI_SMALLFONT;

    y += WEAPON_SPACING;
    loadoutMenuInfo.crossbow.generic.type = MTYPE_PTEXT;
    loadoutMenuInfo.crossbow.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
    loadoutMenuInfo.crossbow.generic.callback = UI_LoadoutMenu_Event;
    loadoutMenuInfo.crossbow.generic.id = ID_CROSSBOW;
    loadoutMenuInfo.crossbow.generic.x = 32;
    loadoutMenuInfo.crossbow.generic.y = y;
    loadoutMenuInfo.crossbow.string = "Crossbow";
    loadoutMenuInfo.crossbow.color = color_white;
    loadoutMenuInfo.crossbow.style = UI_LEFT | UI_SMALLFONT;

    y += WEAPON_SPACING;
    loadoutMenuInfo.acr.generic.type = MTYPE_PTEXT;
    loadoutMenuInfo.acr.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
    loadoutMenuInfo.acr.generic.callback = UI_LoadoutMenu_Event;
    loadoutMenuInfo.acr.generic.id = ID_ACR;
    loadoutMenuInfo.acr.generic.x = 32;
    loadoutMenuInfo.acr.generic.y = y;
    loadoutMenuInfo.acr.string = "Remington ACR";
    loadoutMenuInfo.acr.color = color_white;
    loadoutMenuInfo.acr.style = UI_LEFT | UI_SMALLFONT;

    y += WEAPON_SPACING*2;
    loadoutMenuInfo.walther.generic.type = MTYPE_PTEXT;
    loadoutMenuInfo.walther.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
    loadoutMenuInfo.walther.generic.callback = UI_LoadoutMenu_Event;
    loadoutMenuInfo.walther.generic.id = ID_WALTHER;
    loadoutMenuInfo.walther.generic.x = 32;
    loadoutMenuInfo.walther.generic.y = y;
    loadoutMenuInfo.walther.string = "Walther P22";
    loadoutMenuInfo.walther.color = color_white;
    loadoutMenuInfo.walther.style = UI_LEFT | UI_SMALLFONT;

    y += WEAPON_SPACING*2;
    loadoutMenuInfo.he.generic.type = MTYPE_PTEXT;
    loadoutMenuInfo.he.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
    loadoutMenuInfo.he.generic.callback = UI_LoadoutMenu_Event;
    loadoutMenuInfo.he.generic.id = ID_HE;
    loadoutMenuInfo.he.generic.x = 32;
    loadoutMenuInfo.he.generic.y = y;
    loadoutMenuInfo.he.string = "High-Explosive Grenade";
    loadoutMenuInfo.he.color = color_white;
    loadoutMenuInfo.he.style = UI_LEFT | UI_SMALLFONT;

    y += WEAPON_SPACING*2;
    loadoutMenuInfo.bomb.generic.type = MTYPE_PTEXT;
    loadoutMenuInfo.bomb.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
    loadoutMenuInfo.bomb.generic.callback = UI_LoadoutMenu_Event;
    loadoutMenuInfo.bomb.generic.id = ID_BOMB;
    loadoutMenuInfo.bomb.generic.x = 32;
    loadoutMenuInfo.bomb.generic.y = y;
    loadoutMenuInfo.bomb.string = "C4 Device";
    loadoutMenuInfo.bomb.color = color_white;
    loadoutMenuInfo.bomb.style = UI_LEFT | UI_SMALLFONT;

    y += WEAPON_SPACING;
    loadoutMenuInfo.injector.generic.type = MTYPE_PTEXT;
    loadoutMenuInfo.injector.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
    loadoutMenuInfo.injector.generic.callback = UI_LoadoutMenu_Event;
    loadoutMenuInfo.injector.generic.id = ID_INJECTOR;
    loadoutMenuInfo.injector.generic.x = 32;
    loadoutMenuInfo.injector.generic.y = y;
    loadoutMenuInfo.injector.string = "Adrenaline Injector";
    loadoutMenuInfo.injector.color = color_white;
    loadoutMenuInfo.injector.style = UI_LEFT | UI_SMALLFONT;

    loadoutMenuInfo.accept.generic.type = MTYPE_BITMAP;
    loadoutMenuInfo.accept.generic.name = ART_ACCEPT0;
    loadoutMenuInfo.accept.generic.flags = QMF_RIGHT_JUSTIFY | QMF_PULSEIFFOCUS;
    loadoutMenuInfo.accept.generic.id = ID_ACCEPT;
    loadoutMenuInfo.accept.generic.callback = UI_LoadoutMenu_Event;
    loadoutMenuInfo.accept.generic.x = 640;
    loadoutMenuInfo.accept.generic.y = 480 - 64;
    loadoutMenuInfo.accept.width = 128;
    loadoutMenuInfo.accept.height = 64;
    loadoutMenuInfo.accept.focuspic = ART_ACCEPT1;

    loadoutMenuInfo.back.generic.type = MTYPE_BITMAP;
    loadoutMenuInfo.back.generic.name = ART_BACK0;
    loadoutMenuInfo.back.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
    loadoutMenuInfo.back.generic.id = ID_BACK;
    loadoutMenuInfo.back.generic.callback = UI_LoadoutMenu_Event;
    loadoutMenuInfo.back.generic.x = 0;
    loadoutMenuInfo.back.generic.y = 480 - 64;
    loadoutMenuInfo.back.width = 128;
    loadoutMenuInfo.back.height = 64;
    loadoutMenuInfo.back.focuspic = ART_BACK1;

    loadoutMenuInfo.frame.generic.ownerdraw = UI_LoadoutMenu_DrawWeapons;

    Menu_AddItem(&loadoutMenuInfo.menu, &loadoutMenuInfo.banner);
    Menu_AddItem(&loadoutMenuInfo.menu, &loadoutMenuInfo.frame);

    Menu_AddItem(&loadoutMenuInfo.menu, &loadoutMenuInfo.barrett);
    Menu_AddItem(&loadoutMenuInfo.menu, &loadoutMenuInfo.intervention);
    Menu_AddItem(&loadoutMenuInfo.menu, &loadoutMenuInfo.crossbow);
    Menu_AddItem(&loadoutMenuInfo.menu, &loadoutMenuInfo.acr);

    Menu_AddItem(&loadoutMenuInfo.menu, &loadoutMenuInfo.walther);

    Menu_AddItem(&loadoutMenuInfo.menu, &loadoutMenuInfo.he);

    Menu_AddItem(&loadoutMenuInfo.menu, &loadoutMenuInfo.bomb);
    Menu_AddItem(&loadoutMenuInfo.menu, &loadoutMenuInfo.injector);

    Menu_AddItem(&loadoutMenuInfo.menu, &loadoutMenuInfo.accept);
    Menu_AddItem(&loadoutMenuInfo.menu, &loadoutMenuInfo.back);

    UI_PushMenu(&loadoutMenuInfo.menu);

    Menu_SetCursorToItem(&loadoutMenuInfo.menu, &loadoutMenuInfo.barrett);
}

/*
===============
UI_LoadoutMenu
===============
 */
void UI_LoadoutMenu(void) {
    UI_LoadoutMenu_Init();
}

/*
===============
UI_LoadoutMenu_f
===============
 */
void UI_LoadoutMenu_f(void) {
    UI_LoadoutMenu();
}
