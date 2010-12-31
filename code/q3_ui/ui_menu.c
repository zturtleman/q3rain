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

MAIN MENU

=======================================================================
 */

#define MAX_MENU_SCENES 3

#include "ui_local.h"

#define ID_SINGLEPLAYER 10
#define ID_MULTIPLAYER 11
#define ID_OPTIONS 12
#define ID_DEMOS 13
#define ID_EXIT 14

#define MAIN_BANNER_MODEL			"models/mapobjects/banner/banner5.md3"
#define MAIN_MENU_VERTICAL_SPACING		34
#define MAIN_MENU_HORIZONTAL_SPACING    128

typedef struct {
    menuframework_s menu;

    menutext_s singleplayer;
    menutext_s multiplayer;
    menutext_s options;
    menutext_s demos;
    menutext_s exit;

    int currentScene;
    float fade;
    qboolean up;

    int servers;
    int players;
    char* motd;
    qboolean loggedin;
} mainmenu_t;


static mainmenu_t s_main;

typedef struct {
    menuframework_s menu;
    char errorMessage[4096];
} errorMessage_t;

static errorMessage_t s_errorMessage;

/*
=================
MainMenu_ExitAction
=================
 */
static void MainMenu_ExitAction(qboolean result) {
    if (!result) {
        return;
    }
    UI_PopMenu();
    UI_CreditMenu();
}

/*
=================
Main_MenuEvent
=================
 */
void Main_MenuEvent(void* ptr, int event) {
    if (event != QM_ACTIVATED) {
        return;
    }

    switch (((menucommon_s*) ptr)->id) {
        case ID_SINGLEPLAYER:
            UI_SPLevelMenu();
            break;

        case ID_MULTIPLAYER:
            UI_ArenaServersMenu();
            break;

        case ID_OPTIONS:
            UI_SetupMenu();
            break;

        case ID_DEMOS:
            UI_DemosMenu();
            break;

        case ID_EXIT:
            UI_ConfirmMenu("Exit " PRODUCT_NAME "?", 0, MainMenu_ExitAction);
            break;
    }
}

/*
===============
MainMenu_Cache
===============
 */
void MainMenu_Cache(void) {
    int i;
    for (i = 0; i < MAX_MENU_SCENES; i++) {
        trap_R_RegisterShaderNoMip(va("gfx/scenes/%i", i));
    }
    trap_Cmd_ExecuteText(EXEC_INSERT, "fetchnews");
    trap_Cmd_ExecuteText(EXEC_INSERT, "fetchmotd");
    trap_Cmd_ExecuteText(EXEC_INSERT, "fetchplayers");
    trap_Cmd_ExecuteText(EXEC_INSERT, "fetchservers");
}

sfxHandle_t ErrorMessage_Key(int key) {
    trap_Cvar_Set("com_errorMessage", "");
    UI_MainMenu();
    return (menu_null_sound);
}

/*
===============
Main_MenuDraw
TTimo: this function is common to the main menu and errorMessage menu
===============
 */

static void Main_MenuDraw(void) {
    refdef_t refdef;
    refEntity_t ent;
    vec3_t origin;
    vec3_t angles;
    float adjust;
    float x, y, w, h;
    vec4_t color;
    qboolean connected = qtrue;
    vec4_t oldColor = {0.8, 0.8, 0.8, 1};

    // FIXME dont call on every update...
    s_main.servers = (int) trap_Cvar_VariableValue("ma_servers");
    s_main.players = (int) trap_Cvar_VariableValue("ma_players");
    s_main.motd = UI_Cvar_VariableString("ma_motd");

    if (!s_main.motd || !Q_stricmp(s_main.motd, "")) {
        s_main.motd = "Failed to connect to master server";
        connected = qfalse;
    }

    // options the refdef

    memset(&refdef, 0, sizeof ( refdef));

    refdef.rdflags = RDF_NOWORLDMODEL;

    AxisClear(refdef.viewaxis);

    x = 0;
    y = 0;
    w = 640;
    h = 120;
    UI_AdjustFrom640(&x, &y, &w, &h);
    refdef.x = x;
    refdef.y = y;
    refdef.width = w;
    refdef.height = h;

    adjust = 0; // JDC: Kenneth asked me to stop this 1.0 * sin( (float)uis.realtime / 1000 );
    refdef.fov_x = 60 + adjust;
    refdef.fov_y = 19.6875 + adjust;

    refdef.time = uis.realtime;

    origin[0] = 300;
    origin[1] = 0;
    origin[2] = -32;

    trap_R_ClearScene();

    // add the model

    memset(&ent, 0, sizeof (ent));

    /*adjust = 5.0 * sin((float) uis.realtime / 5000);
    VectorSet(angles, 0, 180 + adjust, 0);
    AnglesToAxis(angles, ent.axis);
    ent.hModel = s_main.bannerModel;
    VectorCopy(origin, ent.origin);
    VectorCopy(origin, ent.lightingOrigin);
    ent.renderfx = RF_LIGHTING_ORIGIN | RF_NOSHADOW;
    VectorCopy(ent.origin, ent.oldorigin);*/

    x = 0;
    y = 0;
    w = 640;
    h = 64;
    UI_FillRect(x, y, w, h, color_black);

    x = 16;
    y = 16;
    UI_DrawProportionalString(x, y, "Hazewood", UI_LEFT, color_green);


    x = 196;
    y = 28;
    if (connected) {
        UI_DrawProportionalString(x, y, va("%s", s_main.motd), UI_LEFT | UI_TINYFONT, color_white);
    } else {
        UI_DrawProportionalString(x, y, va("%s", s_main.motd), UI_LEFT | UI_TINYFONT, color_red);
    }

    x = 640 - 196 + 48;
    y = 12;
    if (s_main.servers > 0) {
        UI_DrawProportionalString(x, y, va("%i Servers", s_main.servers), UI_LEFT | UI_SMALLERFONT, color_blue);
    } else {
        UI_DrawProportionalString(x, y, va("%i Servers", s_main.servers), UI_LEFT | UI_SMALLERFONT, color_red);
    }

    y = 36;
    if (s_main.players > 0) {
        UI_DrawProportionalString(x, y, va("%i Players", s_main.players), UI_LEFT | UI_SMALLERFONT, color_blue);
    } else {
        UI_DrawProportionalString(x, y, va("%i Players", s_main.players), UI_LEFT | UI_SMALLERFONT, color_red);
    }

    x = 0;
    y = 480 - 64;
    w = 640;
    h = 64;
    UI_FillRect(x, y, w, h, color_black);

    x = 0;
    y = 64;
    w = 640;
    h = 480 - 128;

    if (!s_main.up) {
        s_main.fade -= ((float) uis.frametime) / 10.0f;
    } else {
        s_main.fade += ((float) uis.frametime) / 10.0f;
    }
    if (s_main.fade >= 1200.0f) {
        s_main.up = qfalse;
        s_main.currentScene++;
        if (s_main.currentScene >= MAX_MENU_SCENES) {
            s_main.currentScene = 0;
        }
    }
    if (s_main.fade <= -100.0f) {
        s_main.up = qtrue;
    }

    Vector4Copy(oldColor, color);

    UI_DrawHandlePic(x, y, w, h, trap_R_RegisterShaderNoMip(va("gfx/scenes/%i", s_main.currentScene)));

    color[3] = s_main.fade / 1000.0f;
    if (color[3] > 1) {
        color[3] = 1;
    }
    if (color[3] < 0) {
        color[3] = 0;
    }
    trap_R_SetColor(color);
    UI_DrawNamedPic(x, y, w, h, "gfx/colors/blue.jpg");

    trap_R_SetColor(oldColor);

    trap_R_AddRefEntityToScene(&ent);

    trap_R_RenderScene(&refdef);

    if (strlen(s_errorMessage.errorMessage)) {
        UI_DrawProportionalString_AutoWrapped(320, 192, 600, 20, s_errorMessage.errorMessage, UI_CENTER | UI_SMALLFONT | UI_DROPSHADOW, menu_text_color);
    } else {
        Menu_Draw(&s_main.menu);
    }
}

/*
===============
UI_MainMenu

The main menu only comes up when not in a game,
so make sure that the attract loop server is down
and that local cinematics are killed
===============
 */
void UI_MainMenu(void) {
    int x, y;
    int style = UI_LEFT | UI_DROPSHADOW | UI_SMALLERFONT;

    trap_Cvar_Set("sv_killserver", "1");

    memset(&s_main, 0, sizeof (mainmenu_t));
    memset(&s_errorMessage, 0, sizeof (errorMessage_t));

    MainMenu_Cache();

    trap_Cvar_VariableStringBuffer("com_errorMessage", s_errorMessage.errorMessage, sizeof (s_errorMessage.errorMessage));
    if (strlen(s_errorMessage.errorMessage)) {
        s_errorMessage.menu.draw = Main_MenuDraw;
        s_errorMessage.menu.key = ErrorMessage_Key;
        s_errorMessage.menu.fullscreen = qtrue;
        s_errorMessage.menu.wrapAround = qtrue;
        s_errorMessage.menu.showlogo = qtrue;

        trap_Key_SetCatcher(KEYCATCH_UI);
        uis.menusp = 0;
        UI_PushMenu(&s_errorMessage.menu);

        return;
    }

    trap_S_StartBackgroundTrack("music/mainmenu.ogg", "");

    s_main.menu.draw = Main_MenuDraw;
    s_main.menu.fullscreen = qtrue;
    s_main.menu.wrapAround = qtrue;
    s_main.menu.showlogo = qfalse;

    s_main.fade = -100.0f;
    s_main.up = qtrue;

    x = 40;
    s_main.multiplayer.generic.type = MTYPE_PTEXT;
    s_main.multiplayer.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
    s_main.multiplayer.generic.x = x;
    s_main.multiplayer.generic.y = 440;
    s_main.multiplayer.generic.id = ID_MULTIPLAYER;
    s_main.multiplayer.generic.callback = Main_MenuEvent;
    s_main.multiplayer.string = "Multiplayer";
    s_main.multiplayer.color = color_blue;
    s_main.multiplayer.style = style;

    x += MAIN_MENU_HORIZONTAL_SPACING;
    s_main.singleplayer.generic.type = MTYPE_PTEXT;
    s_main.singleplayer.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
    s_main.singleplayer.generic.x = x;
    s_main.singleplayer.generic.y = 440;
    s_main.singleplayer.generic.id = ID_SINGLEPLAYER;
    s_main.singleplayer.generic.callback = Main_MenuEvent;
    s_main.singleplayer.string = "Singleplayer";
    s_main.singleplayer.color = color_blue;
    s_main.singleplayer.style = style;

    x += MAIN_MENU_HORIZONTAL_SPACING;
    s_main.options.generic.type = MTYPE_PTEXT;
    s_main.options.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
    s_main.options.generic.x = x;
    s_main.options.generic.y = 440;
    s_main.options.generic.id = ID_OPTIONS;
    s_main.options.generic.callback = Main_MenuEvent;
    s_main.options.string = "Options";
    s_main.options.color = color_blue;
    s_main.options.style = style;

    x += MAIN_MENU_HORIZONTAL_SPACING;
    s_main.demos.generic.type = MTYPE_PTEXT;
    s_main.demos.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
    s_main.demos.generic.x = x;
    s_main.demos.generic.y = 440;
    s_main.demos.generic.id = ID_DEMOS;
    s_main.demos.generic.callback = Main_MenuEvent;
    s_main.demos.string = "Demos";
    s_main.demos.color = color_blue;
    s_main.demos.style = style;

    x += MAIN_MENU_HORIZONTAL_SPACING;
    s_main.exit.generic.type = MTYPE_PTEXT;
    s_main.exit.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
    s_main.exit.generic.x = x;
    s_main.exit.generic.y = 440;
    s_main.exit.generic.id = ID_EXIT;
    s_main.exit.generic.callback = Main_MenuEvent;
    s_main.exit.string = "Exit";
    s_main.exit.color = color_blue;
    s_main.exit.style = style;

    Menu_AddItem(&s_main.menu, &s_main.multiplayer);
    Menu_AddItem(&s_main.menu, &s_main.singleplayer);
    Menu_AddItem(&s_main.menu, &s_main.options);
    Menu_AddItem(&s_main.menu, &s_main.demos);
    Menu_AddItem(&s_main.menu, &s_main.exit);

    s_main.servers = (int) trap_Cvar_VariableValue("ma_servers");
    s_main.players = (int) trap_Cvar_VariableValue("ma_players");
    s_main.motd = UI_Cvar_VariableString("ma_motd");

    trap_Key_SetCatcher(KEYCATCH_UI);
    uis.menusp = 0;
    UI_PushMenu(&s_main.menu);

}
