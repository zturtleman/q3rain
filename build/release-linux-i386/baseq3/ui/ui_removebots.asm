code
proc UI_RemoveBotsMenu_SetBotNames 1032 12
ADDRLP4 0
CNSTI4 0
ASGNI4
ADDRGP4 $73
JUMPV
LABELV $70
ADDRGP4 removeBotsMenuInfo+1396
INDIRI4
ADDRLP4 0
INDIRI4
ADDI4
CNSTI4 2
LSHI4
ADDRGP4 removeBotsMenuInfo+1628
ADDP4
INDIRI4
CNSTI4 544
ADDI4
ARGI4
ADDRLP4 4
ARGP4
CNSTI4 1024
ARGI4
ADDRGP4 trap_GetConfigString
CALLI4
pop
ADDRLP4 4
ARGP4
ADDRGP4 $79
ARGP4
ADDRLP4 1028
ADDRGP4 Info_ValueForKey
CALLP4
ASGNP4
ADDRLP4 0
INDIRI4
CNSTI4 5
LSHI4
ADDRGP4 removeBotsMenuInfo+1404
ADDP4
ARGP4
ADDRLP4 1028
INDIRP4
ARGP4
CNSTI4 32
ARGI4
ADDRGP4 Q_strncpyz
CALLV
pop
ADDRLP4 0
INDIRI4
CNSTI4 5
LSHI4
ADDRGP4 removeBotsMenuInfo+1404
ADDP4
ARGP4
ADDRGP4 Q_CleanStr
CALLP4
pop
LABELV $71
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $73
ADDRLP4 0
INDIRI4
CNSTI4 7
GEI4 $82
ADDRGP4 removeBotsMenuInfo+1396
INDIRI4
ADDRLP4 0
INDIRI4
ADDI4
ADDRGP4 removeBotsMenuInfo+1392
INDIRI4
LTI4 $70
LABELV $82
LABELV $69
endproc UI_RemoveBotsMenu_SetBotNames 1032 12
proc UI_RemoveBotsMenu_DeleteEvent 4 8
ADDRFP4 4
INDIRI4
CNSTI4 3
EQI4 $84
ADDRGP4 $83
JUMPV
LABELV $84
ADDRGP4 $86
ARGP4
ADDRGP4 removeBotsMenuInfo+1396
INDIRI4
ADDRGP4 removeBotsMenuInfo+1400
INDIRI4
ADDI4
CNSTI4 2
LSHI4
ADDRGP4 removeBotsMenuInfo+1628
ADDP4
INDIRI4
ARGI4
ADDRLP4 0
ADDRGP4 va
CALLP4
ASGNP4
CNSTI4 2
ARGI4
ADDRLP4 0
INDIRP4
ARGP4
ADDRGP4 trap_Cmd_ExecuteText
CALLV
pop
LABELV $83
endproc UI_RemoveBotsMenu_DeleteEvent 4 8
proc UI_RemoveBotsMenu_BotEvent 0 0
ADDRFP4 4
INDIRI4
CNSTI4 3
EQI4 $91
ADDRGP4 $90
JUMPV
LABELV $91
CNSTI4 72
ADDRGP4 removeBotsMenuInfo+1400
INDIRI4
MULI4
ADDRGP4 removeBotsMenuInfo+712+68
ADDP4
ADDRGP4 color_orange
ASGNP4
ADDRGP4 removeBotsMenuInfo+1400
ADDRFP4 0
INDIRP4
CNSTI4 8
ADDP4
INDIRI4
CNSTI4 20
SUBI4
ASGNI4
CNSTI4 72
ADDRGP4 removeBotsMenuInfo+1400
INDIRI4
MULI4
ADDRGP4 removeBotsMenuInfo+712+68
ADDP4
ADDRGP4 color_white
ASGNP4
LABELV $90
endproc UI_RemoveBotsMenu_BotEvent 0 0
proc UI_RemoveBotsMenu_BackEvent 0 0
ADDRFP4 4
INDIRI4
CNSTI4 3
EQI4 $101
ADDRGP4 $100
JUMPV
LABELV $101
ADDRGP4 UI_PopMenu
CALLV
pop
LABELV $100
endproc UI_RemoveBotsMenu_BackEvent 0 0
proc UI_RemoveBotsMenu_UpEvent 4 0
ADDRFP4 4
INDIRI4
CNSTI4 3
EQI4 $104
ADDRGP4 $103
JUMPV
LABELV $104
ADDRGP4 removeBotsMenuInfo+1396
INDIRI4
CNSTI4 0
LEI4 $106
ADDRLP4 0
ADDRGP4 removeBotsMenuInfo+1396
ASGNP4
ADDRLP4 0
INDIRP4
ADDRLP4 0
INDIRP4
INDIRI4
CNSTI4 1
SUBI4
ASGNI4
ADDRGP4 UI_RemoveBotsMenu_SetBotNames
CALLV
pop
LABELV $106
LABELV $103
endproc UI_RemoveBotsMenu_UpEvent 4 0
proc UI_RemoveBotsMenu_DownEvent 4 0
ADDRFP4 4
INDIRI4
CNSTI4 3
EQI4 $111
ADDRGP4 $110
JUMPV
LABELV $111
ADDRGP4 removeBotsMenuInfo+1396
INDIRI4
CNSTI4 7
ADDI4
ADDRGP4 removeBotsMenuInfo+1392
INDIRI4
GEI4 $113
ADDRLP4 0
ADDRGP4 removeBotsMenuInfo+1396
ASGNP4
ADDRLP4 0
INDIRP4
ADDRLP4 0
INDIRP4
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
ADDRGP4 UI_RemoveBotsMenu_SetBotNames
CALLV
pop
LABELV $113
LABELV $110
endproc UI_RemoveBotsMenu_DownEvent 4 0
proc UI_RemoveBotsMenu_GetBots 1056 12
CNSTI4 0
ARGI4
ADDRLP4 4
ARGP4
CNSTI4 1024
ARGI4
ADDRGP4 trap_GetConfigString
CALLI4
pop
ADDRLP4 4
ARGP4
ADDRGP4 $119
ARGP4
ADDRLP4 1036
ADDRGP4 Info_ValueForKey
CALLP4
ASGNP4
ADDRLP4 1036
INDIRP4
ARGP4
ADDRLP4 1040
ADDRGP4 atoi
CALLI4
ASGNI4
ADDRLP4 1032
ADDRLP4 1040
INDIRI4
ASGNI4
ADDRGP4 removeBotsMenuInfo+1392
CNSTI4 0
ASGNI4
ADDRLP4 0
CNSTI4 0
ASGNI4
ADDRGP4 $124
JUMPV
LABELV $121
ADDRLP4 0
INDIRI4
CNSTI4 544
ADDI4
ARGI4
ADDRLP4 4
ARGP4
CNSTI4 1024
ARGI4
ADDRGP4 trap_GetConfigString
CALLI4
pop
ADDRLP4 4
ARGP4
ADDRGP4 $125
ARGP4
ADDRLP4 1044
ADDRGP4 Info_ValueForKey
CALLP4
ASGNP4
ADDRLP4 1044
INDIRP4
ARGP4
ADDRLP4 1048
ADDRGP4 atoi
CALLI4
ASGNI4
ADDRLP4 1028
ADDRLP4 1048
INDIRI4
ASGNI4
ADDRLP4 1028
INDIRI4
CNSTI4 0
NEI4 $126
ADDRGP4 $122
JUMPV
LABELV $126
ADDRGP4 removeBotsMenuInfo+1392
INDIRI4
CNSTI4 2
LSHI4
ADDRGP4 removeBotsMenuInfo+1628
ADDP4
ADDRLP4 0
INDIRI4
ASGNI4
ADDRLP4 1052
ADDRGP4 removeBotsMenuInfo+1392
ASGNP4
ADDRLP4 1052
INDIRP4
ADDRLP4 1052
INDIRP4
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $122
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $124
ADDRLP4 0
INDIRI4
ADDRLP4 1032
INDIRI4
LTI4 $121
LABELV $118
endproc UI_RemoveBotsMenu_GetBots 1056 12
export UI_RemoveBots_Cache
proc UI_RemoveBots_Cache 0 4
ADDRGP4 $132
ARGP4
ADDRGP4 trap_R_RegisterShaderNoMip
CALLI4
pop
ADDRGP4 $133
ARGP4
ADDRGP4 trap_R_RegisterShaderNoMip
CALLI4
pop
ADDRGP4 $134
ARGP4
ADDRGP4 trap_R_RegisterShaderNoMip
CALLI4
pop
ADDRGP4 $135
ARGP4
ADDRGP4 trap_R_RegisterShaderNoMip
CALLI4
pop
ADDRGP4 $136
ARGP4
ADDRGP4 trap_R_RegisterShaderNoMip
CALLI4
pop
LABELV $131
endproc UI_RemoveBots_Cache 0 4
proc UI_RemoveBotsMenu_Init 24 12
ADDRGP4 removeBotsMenuInfo
ARGP4
CNSTI4 0
ARGI4
CNSTI4 5724
ARGI4
ADDRGP4 memset
CALLP4
pop
ADDRGP4 removeBotsMenuInfo+280
CNSTI4 0
ASGNI4
ADDRGP4 removeBotsMenuInfo+276
CNSTI4 1
ASGNI4
ADDRGP4 UI_RemoveBots_Cache
CALLV
pop
ADDRGP4 UI_RemoveBotsMenu_GetBots
CALLV
pop
ADDRGP4 UI_RemoveBotsMenu_SetBotNames
CALLV
pop
ADDRGP4 removeBotsMenuInfo+1392
INDIRI4
CNSTI4 7
GEI4 $143
ADDRLP4 12
ADDRGP4 removeBotsMenuInfo+1392
INDIRI4
ASGNI4
ADDRGP4 $144
JUMPV
LABELV $143
ADDRLP4 12
CNSTI4 7
ASGNI4
LABELV $144
ADDRLP4 4
ADDRLP4 12
INDIRI4
ASGNI4
ADDRGP4 removeBotsMenuInfo+288
CNSTI4 10
ASGNI4
ADDRGP4 removeBotsMenuInfo+288+12
CNSTI4 320
ASGNI4
ADDRGP4 removeBotsMenuInfo+288+16
CNSTI4 16
ASGNI4
ADDRGP4 removeBotsMenuInfo+288+60
ADDRGP4 $152
ASGNP4
ADDRGP4 removeBotsMenuInfo+288+68
ADDRGP4 color_white
ASGNP4
ADDRGP4 removeBotsMenuInfo+288+64
CNSTI4 1
ASGNI4
ADDRGP4 removeBotsMenuInfo+360
CNSTI4 6
ASGNI4
ADDRGP4 removeBotsMenuInfo+360+4
ADDRGP4 $132
ASGNP4
ADDRGP4 removeBotsMenuInfo+360+44
CNSTU4 16384
ASGNU4
ADDRGP4 removeBotsMenuInfo+360+12
CNSTI4 87
ASGNI4
ADDRGP4 removeBotsMenuInfo+360+16
CNSTI4 74
ASGNI4
ADDRGP4 removeBotsMenuInfo+360+76
CNSTI4 466
ASGNI4
ADDRGP4 removeBotsMenuInfo+360+80
CNSTI4 332
ASGNI4
ADDRGP4 removeBotsMenuInfo+448
CNSTI4 6
ASGNI4
ADDRGP4 removeBotsMenuInfo+448+4
ADDRGP4 $173
ASGNP4
ADDRGP4 removeBotsMenuInfo+448+44
CNSTU4 16384
ASGNU4
ADDRGP4 removeBotsMenuInfo+448+12
CNSTI4 200
ASGNI4
ADDRGP4 removeBotsMenuInfo+448+16
CNSTI4 128
ASGNI4
ADDRGP4 removeBotsMenuInfo+448+76
CNSTI4 64
ASGNI4
ADDRGP4 removeBotsMenuInfo+448+80
CNSTI4 128
ASGNI4
ADDRGP4 removeBotsMenuInfo+536
CNSTI4 6
ASGNI4
ADDRGP4 removeBotsMenuInfo+536+44
CNSTU4 260
ASGNU4
ADDRGP4 removeBotsMenuInfo+536+12
CNSTI4 200
ASGNI4
ADDRGP4 removeBotsMenuInfo+536+16
CNSTI4 128
ASGNI4
ADDRGP4 removeBotsMenuInfo+536+8
CNSTI4 10
ASGNI4
ADDRGP4 removeBotsMenuInfo+536+48
ADDRGP4 UI_RemoveBotsMenu_UpEvent
ASGNP4
ADDRGP4 removeBotsMenuInfo+536+76
CNSTI4 64
ASGNI4
ADDRGP4 removeBotsMenuInfo+536+80
CNSTI4 64
ASGNI4
ADDRGP4 removeBotsMenuInfo+536+60
ADDRGP4 $201
ASGNP4
ADDRGP4 removeBotsMenuInfo+624
CNSTI4 6
ASGNI4
ADDRGP4 removeBotsMenuInfo+624+44
CNSTU4 260
ASGNU4
ADDRGP4 removeBotsMenuInfo+624+12
CNSTI4 200
ASGNI4
ADDRGP4 removeBotsMenuInfo+624+16
CNSTI4 192
ASGNI4
ADDRGP4 removeBotsMenuInfo+624+8
CNSTI4 11
ASGNI4
ADDRGP4 removeBotsMenuInfo+624+48
ADDRGP4 UI_RemoveBotsMenu_DownEvent
ASGNP4
ADDRGP4 removeBotsMenuInfo+624+76
CNSTI4 64
ASGNI4
ADDRGP4 removeBotsMenuInfo+624+80
CNSTI4 64
ASGNI4
ADDRGP4 removeBotsMenuInfo+624+60
ADDRGP4 $219
ASGNP4
ADDRLP4 0
CNSTI4 0
ASGNI4
ADDRLP4 8
CNSTI4 120
ASGNI4
ADDRGP4 $223
JUMPV
LABELV $220
CNSTI4 72
ADDRLP4 0
INDIRI4
MULI4
ADDRGP4 removeBotsMenuInfo+712
ADDP4
CNSTI4 9
ASGNI4
CNSTI4 72
ADDRLP4 0
INDIRI4
MULI4
ADDRGP4 removeBotsMenuInfo+712+44
ADDP4
CNSTU4 260
ASGNU4
CNSTI4 72
ADDRLP4 0
INDIRI4
MULI4
ADDRGP4 removeBotsMenuInfo+712+8
ADDP4
ADDRLP4 0
INDIRI4
CNSTI4 20
ADDI4
ASGNI4
CNSTI4 72
ADDRLP4 0
INDIRI4
MULI4
ADDRGP4 removeBotsMenuInfo+712+12
ADDP4
CNSTI4 264
ASGNI4
CNSTI4 72
ADDRLP4 0
INDIRI4
MULI4
ADDRGP4 removeBotsMenuInfo+712+16
ADDP4
ADDRLP4 8
INDIRI4
ASGNI4
CNSTI4 72
ADDRLP4 0
INDIRI4
MULI4
ADDRGP4 removeBotsMenuInfo+712+48
ADDP4
ADDRGP4 UI_RemoveBotsMenu_BotEvent
ASGNP4
CNSTI4 72
ADDRLP4 0
INDIRI4
MULI4
ADDRGP4 removeBotsMenuInfo+712+60
ADDP4
ADDRLP4 0
INDIRI4
CNSTI4 5
LSHI4
ADDRGP4 removeBotsMenuInfo+1404
ADDP4
ASGNP4
CNSTI4 72
ADDRLP4 0
INDIRI4
MULI4
ADDRGP4 removeBotsMenuInfo+712+68
ADDP4
ADDRGP4 color_orange
ASGNP4
CNSTI4 72
ADDRLP4 0
INDIRI4
MULI4
ADDRGP4 removeBotsMenuInfo+712+64
ADDP4
CNSTI4 16
ASGNI4
LABELV $221
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
ADDRLP4 8
ADDRLP4 8
INDIRI4
CNSTI4 20
ADDI4
ASGNI4
LABELV $223
ADDRLP4 0
INDIRI4
ADDRLP4 4
INDIRI4
LTI4 $220
ADDRGP4 removeBotsMenuInfo+1216
CNSTI4 6
ASGNI4
ADDRGP4 removeBotsMenuInfo+1216+4
ADDRGP4 $135
ASGNP4
ADDRGP4 removeBotsMenuInfo+1216+44
CNSTU4 260
ASGNU4
ADDRGP4 removeBotsMenuInfo+1216+8
CNSTI4 12
ASGNI4
ADDRGP4 removeBotsMenuInfo+1216+48
ADDRGP4 UI_RemoveBotsMenu_DeleteEvent
ASGNP4
ADDRGP4 removeBotsMenuInfo+1216+12
CNSTI4 320
ASGNI4
ADDRGP4 removeBotsMenuInfo+1216+16
CNSTI4 320
ASGNI4
ADDRGP4 removeBotsMenuInfo+1216+76
CNSTI4 128
ASGNI4
ADDRGP4 removeBotsMenuInfo+1216+80
CNSTI4 64
ASGNI4
ADDRGP4 removeBotsMenuInfo+1216+60
ADDRGP4 $136
ASGNP4
ADDRGP4 removeBotsMenuInfo+1304
CNSTI4 6
ASGNI4
ADDRGP4 removeBotsMenuInfo+1304+4
ADDRGP4 $133
ASGNP4
ADDRGP4 removeBotsMenuInfo+1304+44
CNSTU4 260
ASGNU4
ADDRGP4 removeBotsMenuInfo+1304+8
CNSTI4 13
ASGNI4
ADDRGP4 removeBotsMenuInfo+1304+48
ADDRGP4 UI_RemoveBotsMenu_BackEvent
ASGNP4
ADDRGP4 removeBotsMenuInfo+1304+12
CNSTI4 192
ASGNI4
ADDRGP4 removeBotsMenuInfo+1304+16
CNSTI4 320
ASGNI4
ADDRGP4 removeBotsMenuInfo+1304+76
CNSTI4 128
ASGNI4
ADDRGP4 removeBotsMenuInfo+1304+80
CNSTI4 64
ASGNI4
ADDRGP4 removeBotsMenuInfo+1304+60
ADDRGP4 $134
ASGNP4
ADDRGP4 removeBotsMenuInfo
ARGP4
ADDRGP4 removeBotsMenuInfo+360
ARGP4
ADDRGP4 Menu_AddItem
CALLV
pop
ADDRGP4 removeBotsMenuInfo
ARGP4
ADDRGP4 removeBotsMenuInfo+288
ARGP4
ADDRGP4 Menu_AddItem
CALLV
pop
ADDRGP4 removeBotsMenuInfo
ARGP4
ADDRGP4 removeBotsMenuInfo+448
ARGP4
ADDRGP4 Menu_AddItem
CALLV
pop
ADDRGP4 removeBotsMenuInfo
ARGP4
ADDRGP4 removeBotsMenuInfo+536
ARGP4
ADDRGP4 Menu_AddItem
CALLV
pop
ADDRGP4 removeBotsMenuInfo
ARGP4
ADDRGP4 removeBotsMenuInfo+624
ARGP4
ADDRGP4 Menu_AddItem
CALLV
pop
ADDRLP4 0
CNSTI4 0
ASGNI4
ADDRGP4 $288
JUMPV
LABELV $285
ADDRGP4 removeBotsMenuInfo
ARGP4
CNSTI4 72
ADDRLP4 0
INDIRI4
MULI4
ADDRGP4 removeBotsMenuInfo+712
ADDP4
ARGP4
ADDRGP4 Menu_AddItem
CALLV
pop
LABELV $286
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $288
ADDRLP4 0
INDIRI4
ADDRLP4 4
INDIRI4
LTI4 $285
ADDRGP4 removeBotsMenuInfo
ARGP4
ADDRGP4 removeBotsMenuInfo+1216
ARGP4
ADDRGP4 Menu_AddItem
CALLV
pop
ADDRGP4 removeBotsMenuInfo
ARGP4
ADDRGP4 removeBotsMenuInfo+1304
ARGP4
ADDRGP4 Menu_AddItem
CALLV
pop
ADDRGP4 removeBotsMenuInfo+1396
CNSTI4 0
ASGNI4
ADDRGP4 removeBotsMenuInfo+1400
CNSTI4 0
ASGNI4
ADDRGP4 removeBotsMenuInfo+712+68
ADDRGP4 color_white
ASGNP4
LABELV $137
endproc UI_RemoveBotsMenu_Init 24 12
export UI_RemoveBotsMenu
proc UI_RemoveBotsMenu 0 4
ADDRGP4 UI_RemoveBotsMenu_Init
CALLV
pop
ADDRGP4 removeBotsMenuInfo
ARGP4
ADDRGP4 UI_PushMenu
CALLV
pop
LABELV $296
endproc UI_RemoveBotsMenu 0 4
bss
align 4
LABELV removeBotsMenuInfo
skip 5724
import UI_RankStatusMenu
import RankStatus_Cache
import UI_SignupMenu
import Signup_Cache
import UI_LoginMenu
import Login_Cache
import UI_RankingsMenu
import Rankings_Cache
import Rankings_DrawPassword
import Rankings_DrawName
import Rankings_DrawText
import UI_InitGameinfo
import UI_SPUnlockMedals_f
import UI_SPUnlock_f
import UI_GetAwardLevel
import UI_LogAwardData
import UI_NewGame
import UI_GetCurrentGame
import UI_CanShowTierVideo
import UI_ShowTierVideo
import UI_TierCompleted
import UI_SetBestScore
import UI_GetBestScore
import UI_GetNumBots
import UI_GetBotInfoByName
import UI_GetBotInfoByNumber
import UI_GetNumSPTiers
import UI_GetNumSPArenas
import UI_GetNumArenas
import UI_GetSpecialArenaInfo
import UI_GetArenaInfoByMap
import UI_GetArenaInfoByNumber
import UI_NetworkOptionsMenu
import UI_NetworkOptionsMenu_Cache
import UI_SoundOptionsMenu
import UI_SoundOptionsMenu_Cache
import UI_DisplayOptionsMenu
import UI_DisplayOptionsMenu_Cache
import UI_SaveConfigMenu
import UI_SaveConfigMenu_Cache
import UI_LoadConfigMenu
import UI_LoadConfig_Cache
import UI_TeamOrdersMenu_Cache
import UI_TeamOrdersMenu_f
import UI_TeamOrdersMenu
import UI_AddBotsMenu
import UI_AddBots_Cache
import trap_SetPbClStatus
import trap_VerifyCDKey
import trap_SetCDKey
import trap_GetCDKey
import trap_MemoryRemaining
import trap_LAN_GetPingInfo
import trap_LAN_GetPing
import trap_LAN_ClearPing
import trap_LAN_ServerStatus
import trap_LAN_GetPingQueueCount
import trap_LAN_GetServerInfo
import trap_LAN_GetServerAddressString
import trap_LAN_GetServerCount
import trap_GetConfigString
import trap_GetGlconfig
import trap_GetClientState
import trap_GetClipboardData
import trap_Key_SetCatcher
import trap_Key_GetCatcher
import trap_Key_ClearStates
import trap_Key_SetOverstrikeMode
import trap_Key_GetOverstrikeMode
import trap_Key_IsDown
import trap_Key_SetBinding
import trap_Key_GetBindingBuf
import trap_Key_KeynumToStringBuf
import trap_S_RegisterSound
import trap_S_StartLocalSound
import trap_CM_LerpTag
import trap_UpdateScreen
import trap_R_DrawStretchPic
import trap_R_SetColor
import trap_R_RenderScene
import trap_R_AddLightToScene
import trap_R_AddPolyToScene
import trap_R_AddRefEntityToScene
import trap_R_ClearScene
import trap_R_RegisterShaderNoMip
import trap_R_RegisterSkin
import trap_R_RegisterModel
import trap_FS_Seek
import trap_FS_GetFileList
import trap_FS_FCloseFile
import trap_FS_Write
import trap_FS_Read
import trap_FS_FOpenFile
import trap_Cmd_ExecuteText
import trap_Argv
import trap_Argc
import trap_Cvar_InfoStringBuffer
import trap_Cvar_Create
import trap_Cvar_Reset
import trap_Cvar_SetValue
import trap_Cvar_VariableStringBuffer
import trap_Cvar_VariableValue
import trap_Cvar_Set
import trap_Cvar_Update
import trap_Cvar_Register
import trap_Milliseconds
import trap_Error
import trap_Print
import UI_SPSkillMenu_Cache
import UI_SPSkillMenu
import UI_SPPostgameMenu_f
import UI_SPPostgameMenu_Cache
import UI_SPArena_Start
import UI_SPLevelMenu_ReInit
import UI_SPLevelMenu_f
import UI_SPLevelMenu
import UI_SPLevelMenu_Cache
import uis
import m_entersound
import UI_StartDemoLoop
import UI_Cvar_VariableString
import UI_Argv
import UI_ForceMenuOff
import UI_PopMenu
import UI_PushMenu
import UI_SetActiveMenu
import UI_IsFullscreen
import UI_DrawTextBox
import UI_AdjustFrom640
import UI_CursorInRect
import UI_DrawChar
import UI_DrawString
import UI_ProportionalStringWidth
import UI_DrawProportionalString_AutoWrapped
import UI_DrawProportionalString
import UI_ProportionalSizeScale
import UI_DrawBannerString
import UI_LerpColor
import UI_SetColor
import UI_UpdateScreen
import UI_DrawRect
import UI_FillRect
import UI_DrawHandlePic
import UI_DrawNamedPic
import UI_ClampCvar
import UI_ConsoleCommand
import UI_Refresh
import UI_MouseEvent
import UI_KeyEvent
import UI_Shutdown
import UI_Init
import UI_RegisterClientModelname
import UI_PlayerInfo_SetInfo
import UI_PlayerInfo_SetModel
import UI_DrawPlayer
import DriverInfo_Cache
import GraphicsOptions_Cache
import UI_GraphicsOptionsMenu
import ServerInfo_Cache
import UI_ServerInfoMenu
import UI_BotSelectMenu_Cache
import UI_BotSelectMenu
import ServerOptions_Cache
import StartServer_Cache
import UI_StartServerMenu
import ArenaServers_Cache
import UI_ArenaServersMenu
import SpecifyServer_Cache
import UI_SpecifyServerMenu
import SpecifyLeague_Cache
import UI_SpecifyLeagueMenu
import Preferences_Cache
import UI_PreferencesMenu
import PlayerSettings_Cache
import UI_PlayerSettingsMenu
import PlayerModel_Cache
import UI_PlayerModelMenu
import UI_CDKeyMenu_f
import UI_CDKeyMenu_Cache
import UI_CDKeyMenu
import UI_ModsMenu_Cache
import UI_ModsMenu
import UI_CinematicsMenu_Cache
import UI_CinematicsMenu_f
import UI_CinematicsMenu
import Demos_Cache
import UI_DemosMenu
import Controls_Cache
import UI_ControlsMenu
import UI_DrawConnectScreen
import TeamMain_Cache
import UI_TeamMainMenu
import UI_SetupMenu
import UI_SetupMenu_Cache
import UI_Message
import UI_ConfirmMenu_Style
import UI_ConfirmMenu
import ConfirmMenu_Cache
import UI_InGameMenu
import InGame_Cache
import UI_CreditMenu
import UI_UpdateCvars
import UI_RegisterCvars
import UI_MainMenu
import MainMenu_Cache
import MenuField_Key
import MenuField_Draw
import MenuField_Init
import MField_Draw
import MField_CharEvent
import MField_KeyDownEvent
import MField_Clear
import ui_medalSounds
import ui_medalPicNames
import ui_medalNames
import text_color_highlight
import text_color_normal
import text_color_disabled
import listbar_color
import list_color
import name_color
import color_dim
import color_red
import color_orange
import color_blue
import color_yellow
import color_white
import color_black
import menu_dim_color
import menu_black_color
import menu_red_color
import menu_highlight_color
import menu_dark_color
import menu_grayed_color
import menu_text_color
import weaponChangeSound
import menu_null_sound
import menu_buzz_sound
import menu_out_sound
import menu_move_sound
import menu_in_sound
import ScrollList_Key
import ScrollList_Draw
import Bitmap_Draw
import Bitmap_Init
import Menu_DefaultKey
import Menu_SetCursorToItem
import Menu_SetCursor
import Menu_ActivateItem
import Menu_ItemAtCursor
import Menu_Draw
import Menu_AdjustCursor
import Menu_AddItem
import Menu_Focus
import Menu_Cache
import ui_ioq3
import ui_cdkeychecked
import ui_cdkey
import ui_server16
import ui_server15
import ui_server14
import ui_server13
import ui_server12
import ui_server11
import ui_server10
import ui_server9
import ui_server8
import ui_server7
import ui_server6
import ui_server5
import ui_server4
import ui_server3
import ui_server2
import ui_server1
import ui_marks
import ui_drawCrosshairNames
import ui_drawCrosshair
import ui_brassTime
import ui_browserShowEmpty
import ui_browserShowFull
import ui_browserSortKey
import ui_browserGameType
import ui_browserMaster
import ui_spSelection
import ui_spSkill
import ui_spVideos
import ui_spAwards
import ui_spScores5
import ui_spScores4
import ui_spScores3
import ui_spScores2
import ui_spScores1
import ui_botsFile
import ui_arenasFile
import ui_ctf_friendly
import ui_ctf_timelimit
import ui_ctf_capturelimit
import ui_team_friendly
import ui_team_timelimit
import ui_team_fraglimit
import ui_tourney_timelimit
import ui_tourney_fraglimit
import ui_ffa_timelimit
import ui_ffa_fraglimit
import BG_PlayerTouchesItem
import BG_PlayerStateToEntityStateExtraPolate
import BG_PlayerStateToEntityState
import BG_TouchJumpPad
import BG_AddPredictableEventToPlayerstate
import BG_EvaluateTrajectoryDelta
import BG_EvaluateTrajectory
import BG_CanItemBeGrabbed
import BG_FindItemForHoldable
import BG_FindItemForPowerup
import BG_FindItemForWeapon
import BG_FindItem
import bg_numItems
import bg_itemlist
import Pmove
import PM_UpdateViewAngles
import Com_Printf
import Com_Error
import Info_NextPair
import Info_Validate
import Info_SetValueForKey_Big
import Info_SetValueForKey
import Info_RemoveKey_big
import Info_RemoveKey
import Info_ValueForKey
import Com_TruncateLongString
import va
import Q_CountChar
import Q_CleanStr
import Q_PrintStrlen
import Q_strcat
import Q_strncpyz
import Q_stristr
import Q_strrchr
import Q_strupr
import Q_strlwr
import Q_stricmpn
import Q_strncmp
import Q_stricmp
import Q_isintegral
import Q_isanumber
import Q_isalpha
import Q_isupper
import Q_islower
import Q_isprint
import Com_RandomBytes
import Com_SkipCharset
import Com_SkipTokens
import Com_sprintf
import Com_HexStrToInt
import Parse3DMatrix
import Parse2DMatrix
import Parse1DMatrix
import SkipRestOfLine
import SkipBracedSection
import COM_MatchToken
import COM_ParseWarning
import COM_ParseError
import COM_Compress
import COM_ParseExt
import COM_Parse
import COM_GetCurrentParseLine
import COM_BeginParseSession
import COM_DefaultExtension
import COM_StripExtension
import COM_GetExtension
import COM_SkipPath
import Com_Clamp
import Q_isnan
import PerpendicularVector
import AngleVectors
import MatrixMultiply
import MakeNormalVectors
import RotateAroundDirection
import RotatePointAroundVector
import ProjectPointOnPlane
import PlaneFromPoints
import AngleDelta
import AngleNormalize180
import AngleNormalize360
import AnglesSubtract
import AngleSubtract
import LerpAngle
import AngleMod
import BoundsIntersectPoint
import BoundsIntersectSphere
import BoundsIntersect
import BoxOnPlaneSide
import SetPlaneSignbits
import AxisCopy
import AxisClear
import AnglesToAxis
import vectoangles
import Q_crandom
import Q_random
import Q_rand
import Q_acos
import Q_log2
import VectorRotate
import Vector4Scale
import VectorNormalize2
import VectorNormalize
import CrossProduct
import VectorInverse
import VectorNormalizeFast
import DistanceSquared
import Distance
import VectorLengthSquared
import VectorLength
import VectorCompare
import AddPointToBounds
import ClearBounds
import RadiusFromBounds
import NormalizeColor
import ColorBytes4
import ColorBytes3
import _VectorMA
import _VectorScale
import _VectorCopy
import _VectorAdd
import _VectorSubtract
import _DotProduct
import ByteToDir
import DirToByte
import ClampShort
import ClampChar
import Q_rsqrt
import Q_fabs
import axisDefault
import vec3_origin
import g_color_table
import colorDkGrey
import colorMdGrey
import colorLtGrey
import colorWhite
import colorCyan
import colorMagenta
import colorYellow
import colorBlue
import colorGreen
import colorRed
import colorBlack
import bytedirs
import Hunk_Alloc
import FloatSwap
import LongSwap
import ShortSwap
import acos
import fabs
import abs
import tan
import atan2
import cos
import sin
import sqrt
import floor
import ceil
import memcpy
import memset
import memmove
import sscanf
import Q_snprintf
import Q_vsnprintf
import strtol
import _atoi
import atoi
import strtod
import _atof
import atof
import toupper
import tolower
import strncpy
import strstr
import strchr
import strcmp
import strcpy
import strcat
import strlen
import rand
import srand
import qsort
lit
align 1
LABELV $219
byte 1 109
byte 1 101
byte 1 110
byte 1 117
byte 1 47
byte 1 97
byte 1 114
byte 1 116
byte 1 47
byte 1 97
byte 1 114
byte 1 114
byte 1 111
byte 1 119
byte 1 115
byte 1 95
byte 1 118
byte 1 101
byte 1 114
byte 1 116
byte 1 95
byte 1 98
byte 1 111
byte 1 116
byte 1 0
align 1
LABELV $201
byte 1 109
byte 1 101
byte 1 110
byte 1 117
byte 1 47
byte 1 97
byte 1 114
byte 1 116
byte 1 47
byte 1 97
byte 1 114
byte 1 114
byte 1 111
byte 1 119
byte 1 115
byte 1 95
byte 1 118
byte 1 101
byte 1 114
byte 1 116
byte 1 95
byte 1 116
byte 1 111
byte 1 112
byte 1 0
align 1
LABELV $173
byte 1 109
byte 1 101
byte 1 110
byte 1 117
byte 1 47
byte 1 97
byte 1 114
byte 1 116
byte 1 47
byte 1 97
byte 1 114
byte 1 114
byte 1 111
byte 1 119
byte 1 115
byte 1 95
byte 1 118
byte 1 101
byte 1 114
byte 1 116
byte 1 95
byte 1 48
byte 1 0
align 1
LABELV $152
byte 1 82
byte 1 69
byte 1 77
byte 1 79
byte 1 86
byte 1 69
byte 1 32
byte 1 66
byte 1 79
byte 1 84
byte 1 83
byte 1 0
align 1
LABELV $136
byte 1 109
byte 1 101
byte 1 110
byte 1 117
byte 1 47
byte 1 97
byte 1 114
byte 1 116
byte 1 47
byte 1 100
byte 1 101
byte 1 108
byte 1 101
byte 1 116
byte 1 101
byte 1 95
byte 1 49
byte 1 0
align 1
LABELV $135
byte 1 109
byte 1 101
byte 1 110
byte 1 117
byte 1 47
byte 1 97
byte 1 114
byte 1 116
byte 1 47
byte 1 100
byte 1 101
byte 1 108
byte 1 101
byte 1 116
byte 1 101
byte 1 95
byte 1 48
byte 1 0
align 1
LABELV $134
byte 1 109
byte 1 101
byte 1 110
byte 1 117
byte 1 47
byte 1 97
byte 1 114
byte 1 116
byte 1 47
byte 1 98
byte 1 97
byte 1 99
byte 1 107
byte 1 95
byte 1 49
byte 1 0
align 1
LABELV $133
byte 1 109
byte 1 101
byte 1 110
byte 1 117
byte 1 47
byte 1 97
byte 1 114
byte 1 116
byte 1 47
byte 1 98
byte 1 97
byte 1 99
byte 1 107
byte 1 95
byte 1 48
byte 1 0
align 1
LABELV $132
byte 1 109
byte 1 101
byte 1 110
byte 1 117
byte 1 47
byte 1 97
byte 1 114
byte 1 116
byte 1 47
byte 1 97
byte 1 100
byte 1 100
byte 1 98
byte 1 111
byte 1 116
byte 1 102
byte 1 114
byte 1 97
byte 1 109
byte 1 101
byte 1 0
align 1
LABELV $125
byte 1 115
byte 1 107
byte 1 105
byte 1 108
byte 1 108
byte 1 0
align 1
LABELV $119
byte 1 115
byte 1 118
byte 1 95
byte 1 109
byte 1 97
byte 1 120
byte 1 99
byte 1 108
byte 1 105
byte 1 101
byte 1 110
byte 1 116
byte 1 115
byte 1 0
align 1
LABELV $86
byte 1 99
byte 1 108
byte 1 105
byte 1 101
byte 1 110
byte 1 116
byte 1 107
byte 1 105
byte 1 99
byte 1 107
byte 1 32
byte 1 37
byte 1 105
byte 1 10
byte 1 0
align 1
LABELV $79
byte 1 110
byte 1 0
