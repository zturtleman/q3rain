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

AUTHORIZATION MENU

=======================================================================
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

typedef struct {
    menuframework_s menu;

    menutext_s banner;
    menubitmap_s frame;

    menufield_s nickname;
    menufield_s password;

    menubitmap_s accept;
    menubitmap_s back;
} authMenuInfo_t;

static authMenuInfo_t authMenuInfo;

/*
===============
UI_AuthMenu_Event
===============
 */
static void UI_AuthMenu_Event(void *ptr, int event) {
    char *msg;

    if (event != QM_ACTIVATED) {
        return;
    }

    switch (((menucommon_s*) ptr)->id) {
        case ID_ACCEPT:
            if (authMenuInfo.nickname.field.buffer[0] && authMenuInfo.password.field.buffer[0]) {
                msg = va("auth %s %s\n", authMenuInfo.nickname.field.buffer, authMenuInfo.password.field.buffer);
                trap_Cmd_ExecuteText(EXEC_INSERT, msg);
            }
            UI_PopMenu();
            break;

        case ID_BACK:
            UI_PopMenu();
            break;
    }
}

/*
===============
UI_AuthMenu_CheckNickname
===============
 */
static int UI_AuthMenu_CheckNickname(const char *key) {
    char ch;

    if (strlen(key) < 4) {
        return 1;
    }

    while ((ch = *key++)) {
        switch (ch) {
            case '^':
                return 2;
            case ' ':
                return 2;
            default:
                continue;
        }
    }

    return 0;
}

/*
===============
UI_AuthMenu_CheckPassword
===============
 */
static int UI_AuthMenu_CheckPassword(const char *key) {
    char ch;

    if (strlen(key) < 4) {
        return 1;
    }

    while ((ch = *key++)) {
        switch (ch) {
            case '^':
                return 2;
            case '@':
                return 2;
            case '"':
                return 2;
            case ' ':
                return 2;
            default:
                continue;
        }
    }

    return 0;
}

/*
=================
UI_AuthMenu_DrawNickname
=================
 */
#define AUTH_LEFT 320-128

static void UI_AuthMenu_DrawNickname(void *self) {
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

    x = AUTH_LEFT;
    y = 240 - 16;
    UI_FillRect(x, y, 16 * BIGCHAR_WIDTH, BIGCHAR_HEIGHT, listbar_color);
    UI_DrawString(x, y, f->field.buffer, style, color);

    // draw cursor if we have focus
    if (focus) {
        if (trap_Key_GetOverstrikeMode()) {
            c = 11;
        } else {
            c = 10;
        }

        style &= ~UI_PULSE;
        style |= UI_BLINK;

        UI_DrawChar(x + f->field.cursor * BIGCHAR_WIDTH, y, c, style, color_white);
    }

    val = UI_AuthMenu_CheckNickname(f->field.buffer);
    if (val == 0) {
        UI_DrawProportionalString(320, 376, "Nickname valid", UI_CENTER | UI_SMALLFONT, color_yellow);
    } else if (val == 1) {
        UI_DrawProportionalString(320, 376, "Nickname too short", UI_CENTER | UI_SMALLFONT, color_red);
    } else if (val == 2) {
        UI_DrawProportionalString(320, 376, "Nickname contains invalid characters", UI_CENTER | UI_SMALLFONT, color_red);
    }

    UI_DrawProportionalString(320, 240 - 42, "Nickname:", UI_CENTER | UI_SMALLFONT, color_yellow);
}

/*
=================
UI_AuthMenu_DrawPassword
=================
 */
static void UI_AuthMenu_DrawPassword(void *self) {
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

    x = AUTH_LEFT;
    y = 240 + 48 - 16;
    UI_FillRect(x, y, 16 * BIGCHAR_WIDTH, BIGCHAR_HEIGHT, listbar_color);
    UI_DrawString(x, y, f->field.buffer, style, color);

    // draw cursor if we have focus
    if (focus) {
        if (trap_Key_GetOverstrikeMode()) {
            c = 11;
        } else {
            c = 10;
        }

        style &= ~UI_PULSE;
        style |= UI_BLINK;

        UI_DrawChar(x + f->field.cursor * BIGCHAR_WIDTH, y, c, style, color_white);
    }

    val = UI_AuthMenu_CheckPassword(f->field.buffer);
    if (val == 1) {
        UI_DrawProportionalString(320, 376 + 32, "Password too short", UI_CENTER | UI_SMALLFONT, color_red);
    } else if (val == 2) {
        UI_DrawProportionalString(320, 376 + 32, "Password contains invalid characters", UI_CENTER | UI_SMALLFONT, color_red);
    }

    UI_DrawProportionalString(320, 248, "Password:", UI_CENTER | UI_SMALLFONT, color_yellow);
}

/*
=================
UI_AuthMenu_Cache
=================
 */
void UI_AuthMenu_Cache(void) {
    trap_R_RegisterShaderNoMip(ART_ACCEPT0);
    trap_R_RegisterShaderNoMip(ART_ACCEPT1);
    trap_R_RegisterShaderNoMip(ART_BACK0);
    trap_R_RegisterShaderNoMip(ART_BACK1);
    trap_R_RegisterShaderNoMip(ART_FRAME);
}

/*
===============
UI_AuthMenu_Init
===============
 */
static void UI_AuthMenu_Init(void) {
    UI_AuthMenu_Cache();

    memset(&authMenuInfo, 0, sizeof (authMenuInfo));
    authMenuInfo.menu.wrapAround = qtrue;
    authMenuInfo.menu.fullscreen = qtrue;

    authMenuInfo.banner.generic.type = MTYPE_BTEXT;
    authMenuInfo.banner.generic.x = 320;
    authMenuInfo.banner.generic.y = 16;
    authMenuInfo.banner.string = "AUTHORIZATION";
    authMenuInfo.banner.color = color_white;
    authMenuInfo.banner.style = UI_CENTER;

    authMenuInfo.frame.generic.type = MTYPE_BITMAP;
    authMenuInfo.frame.generic.name = ART_FRAME;
    authMenuInfo.frame.generic.flags = QMF_INACTIVE;
    authMenuInfo.frame.generic.x = 142;
    authMenuInfo.frame.generic.y = 118;
    authMenuInfo.frame.width = 359;
    authMenuInfo.frame.height = 256;

    authMenuInfo.nickname.generic.type = MTYPE_FIELD;
    authMenuInfo.nickname.generic.name = "Nickname:";
    authMenuInfo.nickname.generic.x = AUTH_LEFT;
    authMenuInfo.nickname.generic.y = 240 - 16;
    authMenuInfo.nickname.field.widthInChars = 16;
    authMenuInfo.nickname.field.maxchars = 16;
    authMenuInfo.nickname.generic.ownerdraw = UI_AuthMenu_DrawNickname;

    authMenuInfo.password.generic.type = MTYPE_FIELD;
    authMenuInfo.password.generic.name = "Password:";
    authMenuInfo.password.generic.flags = QMF_SILENT;
    authMenuInfo.password.generic.x = AUTH_LEFT;
    authMenuInfo.password.generic.y = 240 + 32 - 16;
    authMenuInfo.password.field.widthInChars = 16;
    authMenuInfo.password.field.maxchars = 16;
    authMenuInfo.password.generic.ownerdraw = UI_AuthMenu_DrawPassword;

    authMenuInfo.accept.generic.type = MTYPE_BITMAP;
    authMenuInfo.accept.generic.name = ART_ACCEPT0;
    authMenuInfo.accept.generic.flags = QMF_RIGHT_JUSTIFY | QMF_PULSEIFFOCUS;
    authMenuInfo.accept.generic.id = ID_ACCEPT;
    authMenuInfo.accept.generic.callback = UI_AuthMenu_Event;
    authMenuInfo.accept.generic.x = 640;
    authMenuInfo.accept.generic.y = 480 - 64;
    authMenuInfo.accept.width = 128;
    authMenuInfo.accept.height = 64;
    authMenuInfo.accept.focuspic = ART_ACCEPT1;

    authMenuInfo.back.generic.type = MTYPE_BITMAP;
    authMenuInfo.back.generic.name = ART_BACK0;
    authMenuInfo.back.generic.flags = QMF_LEFT_JUSTIFY | QMF_PULSEIFFOCUS;
    authMenuInfo.back.generic.id = ID_BACK;
    authMenuInfo.back.generic.callback = UI_AuthMenu_Event;
    authMenuInfo.back.generic.x = 0;
    authMenuInfo.back.generic.y = 480 - 64;
    authMenuInfo.back.width = 128;
    authMenuInfo.back.height = 64;
    authMenuInfo.back.focuspic = ART_BACK1;

    Menu_AddItem(&authMenuInfo.menu, &authMenuInfo.banner);
    Menu_AddItem(&authMenuInfo.menu, &authMenuInfo.frame);
    Menu_AddItem(&authMenuInfo.menu, &authMenuInfo.nickname);
    Menu_AddItem(&authMenuInfo.menu, &authMenuInfo.password);
    Menu_AddItem(&authMenuInfo.menu, &authMenuInfo.accept);
    if (uis.menusp) {
        Menu_AddItem(&authMenuInfo.menu, &authMenuInfo.back);
    }

    /*trap_GetCDKey(authMenuInfo.nickname.field.buffer, authMenuInfo.nickname.field.maxchars + 1);
    if (trap_VerifyCDKey(authMenuInfo.nickname.field.buffer, NULL) == qfalse) {
        authMenuInfo.nickname.field.buffer[0] = 0;
    }*/
}

/*
===============
UI_AuthMenu
===============
 */
void UI_AuthMenu(void) {
    UI_AuthMenu_Init();
    UI_PushMenu(&authMenuInfo.menu);
}

/*
===============
UI_AuthMenu_f
===============
 */
void UI_AuthMenu_f(void) {
    UI_AuthMenu();
}
