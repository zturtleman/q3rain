export G_SpawnString
code
proc G_SpawnString 8 8
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 8
ADDRFP4 8
INDIRP4
ASGNP4
ADDRGP4 level+4512
INDIRI4
CNSTI4 0
NEI4 $54
ADDRFP4 8
INDIRP4
ADDRFP4 4
INDIRP4
ASGNP4
LABELV $54
ADDRLP4 0
CNSTI4 0
ASGNI4
ADDRGP4 $60
JUMPV
LABELV $57
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 0
INDIRI4
CNSTI4 3
LSHI4
ADDRGP4 level+4520
ADDP4
INDIRP4
ARGP4
ADDRLP4 4
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 4
INDIRI4
CNSTI4 0
NEI4 $62
ADDRFP4 8
INDIRP4
ADDRLP4 0
INDIRI4
CNSTI4 3
LSHI4
ADDRGP4 level+4520+4
ADDP4
INDIRP4
ASGNP4
CNSTI4 1
RETI4
ADDRGP4 $53
JUMPV
LABELV $62
LABELV $58
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $60
ADDRLP4 0
INDIRI4
ADDRGP4 level+4516
INDIRI4
LTI4 $57
ADDRFP4 8
INDIRP4
ADDRFP4 4
INDIRP4
ASGNP4
CNSTI4 0
RETI4
LABELV $53
endproc G_SpawnString 8 8
export G_SpawnFloat
proc G_SpawnFloat 16 12
ADDRFP4 0
INDIRP4
ARGP4
ADDRFP4 4
INDIRP4
ARGP4
ADDRLP4 0
ARGP4
ADDRLP4 8
ADDRGP4 G_SpawnString
CALLI4
ASGNI4
ADDRLP4 4
ADDRLP4 8
INDIRI4
ASGNI4
ADDRLP4 0
INDIRP4
ARGP4
ADDRLP4 12
ADDRGP4 atof
CALLF4
ASGNF4
ADDRFP4 8
INDIRP4
ADDRLP4 12
INDIRF4
ASGNF4
ADDRLP4 4
INDIRI4
RETI4
LABELV $67
endproc G_SpawnFloat 16 12
export G_SpawnInt
proc G_SpawnInt 16 12
ADDRFP4 0
INDIRP4
ARGP4
ADDRFP4 4
INDIRP4
ARGP4
ADDRLP4 0
ARGP4
ADDRLP4 8
ADDRGP4 G_SpawnString
CALLI4
ASGNI4
ADDRLP4 4
ADDRLP4 8
INDIRI4
ASGNI4
ADDRLP4 0
INDIRP4
ARGP4
ADDRLP4 12
ADDRGP4 atoi
CALLI4
ASGNI4
ADDRFP4 8
INDIRP4
ADDRLP4 12
INDIRI4
ASGNI4
ADDRLP4 4
INDIRI4
RETI4
LABELV $68
endproc G_SpawnInt 16 12
export G_SpawnVector
proc G_SpawnVector 16 20
ADDRFP4 8
ADDRFP4 8
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
ARGP4
ADDRFP4 4
INDIRP4
ARGP4
ADDRLP4 0
ARGP4
ADDRLP4 8
ADDRGP4 G_SpawnString
CALLI4
ASGNI4
ADDRLP4 4
ADDRLP4 8
INDIRI4
ASGNI4
ADDRLP4 0
INDIRP4
ARGP4
ADDRGP4 $70
ARGP4
ADDRFP4 8
INDIRP4
ARGP4
ADDRFP4 8
INDIRP4
CNSTI4 4
ADDP4
ARGP4
ADDRFP4 8
INDIRP4
CNSTI4 8
ADDP4
ARGP4
ADDRGP4 sscanf
CALLI4
pop
ADDRLP4 4
INDIRI4
RETI4
LABELV $69
endproc G_SpawnVector 16 20
data
export fields
align 4
LABELV fields
address $73
byte 4 524
byte 4 2
skip 4
address $74
byte 4 92
byte 4 4
skip 4
address $75
byte 4 540
byte 4 2
skip 4
address $76
byte 4 544
byte 4 2
skip 4
address $77
byte 4 528
byte 4 0
skip 4
address $78
byte 4 672
byte 4 1
skip 4
address $79
byte 4 648
byte 4 2
skip 4
address $80
byte 4 652
byte 4 2
skip 4
address $81
byte 4 636
byte 4 2
skip 4
address $82
byte 4 656
byte 4 2
skip 4
address $83
byte 4 804
byte 4 1
skip 4
address $84
byte 4 808
byte 4 1
skip 4
address $85
byte 4 760
byte 4 0
skip 4
address $86
byte 4 732
byte 4 0
skip 4
address $87
byte 4 0
byte 4 9
skip 4
address $88
byte 4 740
byte 4 0
skip 4
address $89
byte 4 116
byte 4 4
skip 4
address $90
byte 4 116
byte 4 5
skip 4
address $91
byte 4 660
byte 4 2
skip 4
address $92
byte 4 664
byte 4 2
skip 4
byte 4 0
skip 12
export SP_item_botroam
code
proc SP_item_botroam 0 0
LABELV $94
endproc SP_item_botroam 0 0
data
export spawns
align 4
LABELV spawns
address $95
address SP_info_player_start
address $96
address SP_info_player_deathmatch
address $97
address SP_info_player_intermission
address $98
address SP_info_null
address $99
address SP_info_notnull
address $100
address SP_info_camp
address $101
address SP_func_plat
address $102
address SP_func_button
address $103
address SP_func_door
address $104
address SP_func_static
address $105
address SP_func_rotating
address $106
address SP_func_bobbing
address $107
address SP_func_pendulum
address $108
address SP_func_train
address $109
address SP_info_null
address $110
address SP_func_timer
address $111
address SP_trigger_always
address $112
address SP_trigger_multiple
address $113
address SP_trigger_push
address $114
address SP_trigger_teleport
address $115
address SP_trigger_hurt
address $116
address SP_target_give
address $117
address SP_target_remove_powerups
address $118
address SP_target_delay
address $119
address SP_target_speaker
address $120
address SP_target_print
address $121
address SP_target_laser
address $122
address SP_target_score
address $123
address SP_target_teleporter
address $124
address SP_target_relay
address $125
address SP_target_kill
address $126
address SP_target_position
address $127
address SP_target_location
address $128
address SP_target_push
address $87
address SP_light
address $129
address SP_path_corner
address $130
address SP_misc_teleporter_dest
address $131
address SP_misc_model
address $132
address SP_misc_portal_surface
address $133
address SP_misc_portal_camera
address $134
address SP_shooter_rocket
address $135
address SP_shooter_grenade
address $136
address SP_shooter_plasma
address $137
address SP_team_CTF_redplayer
address $138
address SP_team_CTF_blueplayer
address $139
address SP_team_CTF_redspawn
address $140
address SP_team_CTF_bluespawn
address $141
address SP_item_botroam
byte 4 0
byte 4 0
export G_CallSpawn
code
proc G_CallSpawn 108 8
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $143
ADDRGP4 $145
ARGP4
ADDRGP4 G_Printf
CALLV
pop
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $143
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $148
ARGP4
ADDRLP4 8
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 8
INDIRI4
CNSTI4 0
NEI4 $146
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $146
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $151
ARGP4
ADDRLP4 12
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 12
INDIRI4
CNSTI4 0
NEI4 $149
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $149
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $154
ARGP4
ADDRLP4 16
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 16
INDIRI4
CNSTI4 0
NEI4 $152
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $152
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $157
ARGP4
ADDRLP4 20
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 20
INDIRI4
CNSTI4 0
NEI4 $155
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $155
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $160
ARGP4
ADDRLP4 24
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 24
INDIRI4
CNSTI4 0
NEI4 $158
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $158
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $163
ARGP4
ADDRLP4 28
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 28
INDIRI4
CNSTI4 0
NEI4 $161
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $161
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $166
ARGP4
ADDRLP4 32
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 32
INDIRI4
CNSTI4 0
NEI4 $164
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $164
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $169
ARGP4
ADDRLP4 36
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 36
INDIRI4
CNSTI4 0
NEI4 $167
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $167
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $172
ARGP4
ADDRLP4 40
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 40
INDIRI4
CNSTI4 0
NEI4 $170
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $170
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $175
ARGP4
ADDRLP4 44
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 44
INDIRI4
CNSTI4 0
NEI4 $173
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $173
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $178
ARGP4
ADDRLP4 48
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 48
INDIRI4
CNSTI4 0
NEI4 $176
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $176
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $181
ARGP4
ADDRLP4 52
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 52
INDIRI4
CNSTI4 0
NEI4 $179
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $179
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $184
ARGP4
ADDRLP4 56
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 56
INDIRI4
CNSTI4 0
NEI4 $182
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $182
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $187
ARGP4
ADDRLP4 60
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 60
INDIRI4
CNSTI4 0
NEI4 $185
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $185
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $190
ARGP4
ADDRLP4 64
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 64
INDIRI4
CNSTI4 0
NEI4 $188
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $188
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $193
ARGP4
ADDRLP4 68
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 68
INDIRI4
CNSTI4 0
NEI4 $191
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $191
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $196
ARGP4
ADDRLP4 72
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 72
INDIRI4
CNSTI4 0
NEI4 $194
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $194
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $199
ARGP4
ADDRLP4 76
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 76
INDIRI4
CNSTI4 0
NEI4 $197
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $197
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $202
ARGP4
ADDRLP4 80
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 80
INDIRI4
CNSTI4 0
NEI4 $200
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $200
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $205
ARGP4
ADDRLP4 84
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 84
INDIRI4
CNSTI4 0
NEI4 $203
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $203
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $208
ARGP4
ADDRLP4 88
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 88
INDIRI4
CNSTI4 0
NEI4 $206
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $206
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $211
ARGP4
ADDRLP4 92
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 92
INDIRI4
CNSTI4 0
NEI4 $209
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $209
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $214
ARGP4
ADDRLP4 96
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 96
INDIRI4
CNSTI4 0
NEI4 $212
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $212
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 $217
ARGP4
ADDRLP4 100
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 100
INDIRI4
CNSTI4 0
NEI4 $215
CNSTI4 0
RETI4
ADDRGP4 $142
JUMPV
LABELV $215
ADDRLP4 4
ADDRGP4 bg_itemlist+52
ASGNP4
ADDRGP4 $221
JUMPV
LABELV $218
ADDRLP4 4
INDIRP4
INDIRP4
ARGP4
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRLP4 104
ADDRGP4 strcmp
CALLI4
ASGNI4
ADDRLP4 104
INDIRI4
CNSTI4 0
NEI4 $223
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 4
INDIRP4
ARGP4
ADDRGP4 G_SpawnItem
CALLV
pop
CNSTI4 1
RETI4
ADDRGP4 $142
JUMPV
LABELV $223
LABELV $219
ADDRLP4 4
ADDRLP4 4
INDIRP4
CNSTI4 52
ADDP4
ASGNP4
LABELV $221
ADDRLP4 4
INDIRP4
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $218
ADDRLP4 0
ADDRGP4 spawns
ASGNP4
ADDRGP4 $228
JUMPV
LABELV $225
ADDRLP4 0
INDIRP4
INDIRP4
ARGP4
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRLP4 104
ADDRGP4 strcmp
CALLI4
ASGNI4
ADDRLP4 104
INDIRI4
CNSTI4 0
NEI4 $229
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRP4
CALLV
pop
CNSTI4 1
RETI4
ADDRGP4 $142
JUMPV
LABELV $229
LABELV $226
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 8
ADDP4
ASGNP4
LABELV $228
ADDRLP4 0
INDIRP4
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $225
ADDRGP4 $231
ARGP4
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 G_Printf
CALLV
pop
CNSTI4 0
RETI4
LABELV $142
endproc G_CallSpawn 108 8
export G_NewString
proc G_NewString 32 4
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 16
ADDRGP4 strlen
CALLI4
ASGNI4
ADDRLP4 4
ADDRLP4 16
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
ADDRLP4 4
INDIRI4
ARGI4
ADDRLP4 20
ADDRGP4 G_Alloc
CALLP4
ASGNP4
ADDRLP4 12
ADDRLP4 20
INDIRP4
ASGNP4
ADDRLP4 8
ADDRLP4 12
INDIRP4
ASGNP4
ADDRLP4 0
CNSTI4 0
ASGNI4
ADDRGP4 $236
JUMPV
LABELV $233
ADDRLP4 0
INDIRI4
ADDRFP4 0
INDIRP4
ADDP4
INDIRI1
CVII4 1
CNSTI4 92
NEI4 $237
ADDRLP4 0
INDIRI4
ADDRLP4 4
INDIRI4
CNSTI4 1
SUBI4
GEI4 $237
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
ADDRLP4 0
INDIRI4
ADDRFP4 0
INDIRP4
ADDP4
INDIRI1
CVII4 1
CNSTI4 110
NEI4 $239
ADDRLP4 28
ADDRLP4 8
INDIRP4
ASGNP4
ADDRLP4 8
ADDRLP4 28
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
ADDRLP4 28
INDIRP4
CNSTI1 10
ASGNI1
ADDRGP4 $238
JUMPV
LABELV $239
ADDRLP4 28
ADDRLP4 8
INDIRP4
ASGNP4
ADDRLP4 8
ADDRLP4 28
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
ADDRLP4 28
INDIRP4
CNSTI1 92
ASGNI1
ADDRGP4 $238
JUMPV
LABELV $237
ADDRLP4 28
ADDRLP4 8
INDIRP4
ASGNP4
ADDRLP4 8
ADDRLP4 28
INDIRP4
CNSTI4 1
ADDP4
ASGNP4
ADDRLP4 28
INDIRP4
ADDRLP4 0
INDIRI4
ADDRFP4 0
INDIRP4
ADDP4
INDIRI1
ASGNI1
LABELV $238
LABELV $234
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $236
ADDRLP4 0
INDIRI4
ADDRLP4 4
INDIRI4
LTI4 $233
ADDRLP4 12
INDIRP4
RETP4
LABELV $232
endproc G_NewString 32 4
export G_ParseField
proc G_ParseField 60 20
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 8
ADDRFP4 8
INDIRP4
ASGNP4
ADDRLP4 0
ADDRGP4 fields
ASGNP4
ADDRGP4 $245
JUMPV
LABELV $242
ADDRLP4 0
INDIRP4
INDIRP4
ARGP4
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 24
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 24
INDIRI4
CNSTI4 0
NEI4 $246
ADDRLP4 4
ADDRFP4 8
INDIRP4
ASGNP4
ADDRLP4 28
ADDRLP4 0
INDIRP4
CNSTI4 8
ADDP4
INDIRI4
ASGNI4
ADDRLP4 28
INDIRI4
CNSTI4 0
LTI4 $241
ADDRLP4 28
INDIRI4
CNSTI4 9
GTI4 $241
ADDRLP4 28
INDIRI4
CNSTI4 2
LSHI4
ADDRGP4 $261
ADDP4
INDIRP4
JUMPV
lit
align 4
LABELV $261
address $257
address $258
address $251
address $241
address $252
address $259
address $241
address $241
address $241
address $241
code
LABELV $251
ADDRFP4 4
INDIRP4
ARGP4
ADDRLP4 36
ADDRGP4 G_NewString
CALLP4
ASGNP4
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
ADDRLP4 4
INDIRP4
ADDP4
ADDRLP4 36
INDIRP4
ASGNP4
ADDRGP4 $241
JUMPV
LABELV $252
ADDRFP4 4
INDIRP4
ARGP4
ADDRGP4 $70
ARGP4
ADDRLP4 8
ARGP4
ADDRLP4 8+4
ARGP4
ADDRLP4 8+8
ARGP4
ADDRGP4 sscanf
CALLI4
pop
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
ADDRLP4 4
INDIRP4
ADDP4
ADDRLP4 8
INDIRF4
ASGNF4
ADDRLP4 40
CNSTI4 4
ASGNI4
ADDRLP4 0
INDIRP4
ADDRLP4 40
INDIRI4
ADDP4
INDIRI4
ADDRLP4 4
INDIRP4
ADDP4
ADDRLP4 40
INDIRI4
ADDP4
ADDRLP4 8+4
INDIRF4
ASGNF4
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
ADDRLP4 4
INDIRP4
ADDP4
CNSTI4 8
ADDP4
ADDRLP4 8+8
INDIRF4
ASGNF4
ADDRGP4 $241
JUMPV
LABELV $257
ADDRFP4 4
INDIRP4
ARGP4
ADDRLP4 44
ADDRGP4 atoi
CALLI4
ASGNI4
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
ADDRLP4 4
INDIRP4
ADDP4
ADDRLP4 44
INDIRI4
ASGNI4
ADDRGP4 $241
JUMPV
LABELV $258
ADDRFP4 4
INDIRP4
ARGP4
ADDRLP4 48
ADDRGP4 atof
CALLF4
ASGNF4
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
ADDRLP4 4
INDIRP4
ADDP4
ADDRLP4 48
INDIRF4
ASGNF4
ADDRGP4 $241
JUMPV
LABELV $259
ADDRFP4 4
INDIRP4
ARGP4
ADDRLP4 52
ADDRGP4 atof
CALLF4
ASGNF4
ADDRLP4 20
ADDRLP4 52
INDIRF4
ASGNF4
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
ADDRLP4 4
INDIRP4
ADDP4
CNSTF4 0
ASGNF4
ADDRLP4 56
CNSTI4 4
ASGNI4
ADDRLP4 0
INDIRP4
ADDRLP4 56
INDIRI4
ADDP4
INDIRI4
ADDRLP4 4
INDIRP4
ADDP4
ADDRLP4 56
INDIRI4
ADDP4
ADDRLP4 20
INDIRF4
ASGNF4
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
ADDRLP4 4
INDIRP4
ADDP4
CNSTI4 8
ADDP4
CNSTF4 0
ASGNF4
ADDRGP4 $241
JUMPV
LABELV $246
LABELV $243
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 16
ADDP4
ASGNP4
LABELV $245
ADDRLP4 0
INDIRP4
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $242
LABELV $241
endproc G_ParseField 60 20
data
align 4
LABELV $263
address $264
address $265
address $266
address $267
export G_SpawnGEntityFromSpawnVars
code
proc G_SpawnGEntityFromSpawnVars 40 12
ADDRLP4 20
ADDRGP4 G_Spawn
CALLP4
ASGNP4
ADDRLP4 4
ADDRLP4 20
INDIRP4
ASGNP4
ADDRLP4 0
CNSTI4 0
ASGNI4
ADDRGP4 $271
JUMPV
LABELV $268
ADDRLP4 24
ADDRLP4 0
INDIRI4
CNSTI4 3
LSHI4
ASGNI4
ADDRLP4 24
INDIRI4
ADDRGP4 level+4520
ADDP4
INDIRP4
ARGP4
ADDRLP4 24
INDIRI4
ADDRGP4 level+4520+4
ADDP4
INDIRP4
ARGP4
ADDRLP4 4
INDIRP4
ARGP4
ADDRGP4 G_ParseField
CALLV
pop
LABELV $269
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $271
ADDRLP4 0
INDIRI4
ADDRGP4 level+4516
INDIRI4
LTI4 $268
ADDRGP4 g_gametype+12
INDIRI4
CNSTI4 1
NEI4 $276
ADDRGP4 $279
ARGP4
ADDRGP4 $280
ARGP4
ADDRLP4 0
ARGP4
ADDRGP4 G_SpawnInt
CALLI4
pop
ADDRLP4 0
INDIRI4
CNSTI4 0
EQI4 $281
ADDRLP4 4
INDIRP4
ARGP4
ADDRGP4 G_FreeEntity
CALLV
pop
ADDRGP4 $262
JUMPV
LABELV $281
LABELV $276
ADDRGP4 g_gametype+12
INDIRI4
CNSTI4 3
NEI4 $283
ADDRGP4 $286
ARGP4
ADDRGP4 $280
ARGP4
ADDRLP4 0
ARGP4
ADDRGP4 G_SpawnInt
CALLI4
pop
ADDRLP4 0
INDIRI4
CNSTI4 0
EQI4 $284
ADDRLP4 4
INDIRP4
ARGP4
ADDRGP4 G_FreeEntity
CALLV
pop
ADDRGP4 $262
JUMPV
LABELV $283
ADDRGP4 $289
ARGP4
ADDRGP4 $280
ARGP4
ADDRLP4 0
ARGP4
ADDRGP4 G_SpawnInt
CALLI4
pop
ADDRLP4 0
INDIRI4
CNSTI4 0
EQI4 $290
ADDRLP4 4
INDIRP4
ARGP4
ADDRGP4 G_FreeEntity
CALLV
pop
ADDRGP4 $262
JUMPV
LABELV $290
LABELV $284
ADDRGP4 $292
ARGP4
ADDRGP4 $280
ARGP4
ADDRLP4 0
ARGP4
ADDRGP4 G_SpawnInt
CALLI4
pop
ADDRLP4 0
INDIRI4
CNSTI4 0
EQI4 $293
ADDRLP4 4
INDIRP4
ARGP4
ADDRGP4 G_FreeEntity
CALLV
pop
ADDRGP4 $262
JUMPV
LABELV $293
ADDRGP4 $297
ARGP4
CNSTP4 0
ARGP4
ADDRLP4 8
ARGP4
ADDRLP4 24
ADDRGP4 G_SpawnString
CALLI4
ASGNI4
ADDRLP4 24
INDIRI4
CNSTI4 0
EQI4 $295
ADDRGP4 g_gametype+12
INDIRI4
CNSTI4 0
LTI4 $298
ADDRGP4 g_gametype+12
INDIRI4
CNSTI4 4
GEI4 $298
ADDRLP4 16
ADDRGP4 g_gametype+12
INDIRI4
CNSTI4 2
LSHI4
ADDRGP4 $263
ADDP4
INDIRP4
ASGNP4
ADDRLP4 8
INDIRP4
ARGP4
ADDRLP4 16
INDIRP4
ARGP4
ADDRLP4 28
ADDRGP4 strstr
CALLP4
ASGNP4
ADDRLP4 12
ADDRLP4 28
INDIRP4
ASGNP4
ADDRLP4 12
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $303
ADDRLP4 4
INDIRP4
ARGP4
ADDRGP4 G_FreeEntity
CALLV
pop
ADDRGP4 $262
JUMPV
LABELV $303
LABELV $298
LABELV $295
ADDRLP4 4
INDIRP4
CNSTI4 24
ADDP4
ADDRLP4 4
INDIRP4
CNSTI4 92
ADDP4
INDIRB
ASGNB 12
ADDRLP4 4
INDIRP4
CNSTI4 488
ADDP4
ADDRLP4 4
INDIRP4
CNSTI4 92
ADDP4
INDIRB
ASGNB 12
ADDRLP4 4
INDIRP4
ARGP4
ADDRLP4 36
ADDRGP4 G_CallSpawn
CALLI4
ASGNI4
ADDRLP4 36
INDIRI4
CNSTI4 0
NEI4 $305
ADDRLP4 4
INDIRP4
ARGP4
ADDRGP4 G_FreeEntity
CALLV
pop
LABELV $305
LABELV $262
endproc G_SpawnGEntityFromSpawnVars 40 12
export G_AddSpawnVarToken
proc G_AddSpawnVarToken 16 12
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 8
ADDRGP4 strlen
CALLI4
ASGNI4
ADDRLP4 0
ADDRLP4 8
INDIRI4
ASGNI4
ADDRGP4 level+5032
INDIRI4
ADDRLP4 0
INDIRI4
ADDI4
CNSTI4 1
ADDI4
CNSTI4 4096
LEI4 $308
ADDRGP4 $311
ARGP4
ADDRGP4 G_Error
CALLV
pop
LABELV $308
ADDRLP4 4
ADDRGP4 level+5032
INDIRI4
ADDRGP4 level+5036
ADDP4
ASGNP4
ADDRLP4 4
INDIRP4
ARGP4
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ARGI4
ADDRGP4 memcpy
CALLP4
pop
ADDRLP4 12
ADDRGP4 level+5032
ASGNP4
ADDRLP4 12
INDIRP4
ADDRLP4 12
INDIRP4
INDIRI4
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ADDI4
ASGNI4
ADDRLP4 4
INDIRP4
RETP4
LABELV $307
endproc G_AddSpawnVarToken 16 12
export G_ParseSpawnVars
proc G_ParseSpawnVars 2072 8
ADDRGP4 level+4516
CNSTI4 0
ASGNI4
ADDRGP4 level+5032
CNSTI4 0
ASGNI4
ADDRLP4 0
ARGP4
CNSTI4 1024
ARGI4
ADDRLP4 2048
ADDRGP4 trap_GetEntityToken
CALLI4
ASGNI4
ADDRLP4 2048
INDIRI4
CNSTI4 0
NEI4 $318
CNSTI4 0
RETI4
ADDRGP4 $315
JUMPV
LABELV $318
ADDRLP4 0
INDIRI1
CVII4 1
CNSTI4 123
EQI4 $324
ADDRGP4 $322
ARGP4
ADDRLP4 0
ARGP4
ADDRGP4 G_Error
CALLV
pop
ADDRGP4 $324
JUMPV
LABELV $323
ADDRLP4 1024
ARGP4
CNSTI4 1024
ARGI4
ADDRLP4 2052
ADDRGP4 trap_GetEntityToken
CALLI4
ASGNI4
ADDRLP4 2052
INDIRI4
CNSTI4 0
NEI4 $326
ADDRGP4 $328
ARGP4
ADDRGP4 G_Error
CALLV
pop
LABELV $326
ADDRLP4 1024
INDIRI1
CVII4 1
CNSTI4 125
NEI4 $329
ADDRGP4 $325
JUMPV
LABELV $329
ADDRLP4 0
ARGP4
CNSTI4 1024
ARGI4
ADDRLP4 2056
ADDRGP4 trap_GetEntityToken
CALLI4
ASGNI4
ADDRLP4 2056
INDIRI4
CNSTI4 0
NEI4 $331
ADDRGP4 $328
ARGP4
ADDRGP4 G_Error
CALLV
pop
LABELV $331
ADDRLP4 0
INDIRI1
CVII4 1
CNSTI4 125
NEI4 $333
ADDRGP4 $335
ARGP4
ADDRGP4 G_Error
CALLV
pop
LABELV $333
ADDRGP4 level+4516
INDIRI4
CNSTI4 64
NEI4 $336
ADDRGP4 $339
ARGP4
ADDRGP4 G_Error
CALLV
pop
LABELV $336
ADDRLP4 1024
ARGP4
ADDRLP4 2060
ADDRGP4 G_AddSpawnVarToken
CALLP4
ASGNP4
ADDRGP4 level+4516
INDIRI4
CNSTI4 3
LSHI4
ADDRGP4 level+4520
ADDP4
ADDRLP4 2060
INDIRP4
ASGNP4
ADDRLP4 0
ARGP4
ADDRLP4 2064
ADDRGP4 G_AddSpawnVarToken
CALLP4
ASGNP4
ADDRGP4 level+4516
INDIRI4
CNSTI4 3
LSHI4
ADDRGP4 level+4520+4
ADDP4
ADDRLP4 2064
INDIRP4
ASGNP4
ADDRLP4 2068
ADDRGP4 level+4516
ASGNP4
ADDRLP4 2068
INDIRP4
ADDRLP4 2068
INDIRP4
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $324
ADDRGP4 $323
JUMPV
LABELV $325
CNSTI4 1
RETI4
LABELV $315
endproc G_ParseSpawnVars 2072 8
export SP_worldspawn
proc SP_worldspawn 16 12
ADDRGP4 $73
ARGP4
ADDRGP4 $347
ARGP4
ADDRLP4 0
ARGP4
ADDRGP4 G_SpawnString
CALLI4
pop
ADDRLP4 0
INDIRP4
ARGP4
ADDRGP4 $350
ARGP4
ADDRLP4 4
ADDRGP4 Q_stricmp
CALLI4
ASGNI4
ADDRLP4 4
INDIRI4
CNSTI4 0
EQI4 $348
ADDRGP4 $351
ARGP4
ADDRGP4 G_Error
CALLV
pop
LABELV $348
CNSTI4 20
ARGI4
ADDRGP4 $352
ARGP4
ADDRGP4 trap_SetConfigstring
CALLV
pop
ADDRGP4 $353
ARGP4
ADDRGP4 level+40
INDIRI4
ARGI4
ADDRLP4 8
ADDRGP4 va
CALLP4
ASGNP4
CNSTI4 21
ARGI4
ADDRLP4 8
INDIRP4
ARGP4
ADDRGP4 trap_SetConfigstring
CALLV
pop
ADDRGP4 $355
ARGP4
ADDRGP4 $347
ARGP4
ADDRLP4 0
ARGP4
ADDRGP4 G_SpawnString
CALLI4
pop
CNSTI4 2
ARGI4
ADDRLP4 0
INDIRP4
ARGP4
ADDRGP4 trap_SetConfigstring
CALLV
pop
ADDRGP4 $81
ARGP4
ADDRGP4 $347
ARGP4
ADDRLP4 0
ARGP4
ADDRGP4 G_SpawnString
CALLI4
pop
CNSTI4 3
ARGI4
ADDRLP4 0
INDIRP4
ARGP4
ADDRGP4 trap_SetConfigstring
CALLV
pop
CNSTI4 4
ARGI4
ADDRGP4 g_motd+16
ARGP4
ADDRGP4 trap_SetConfigstring
CALLV
pop
ADDRGP4 $357
ARGP4
ADDRGP4 $358
ARGP4
ADDRLP4 0
ARGP4
ADDRGP4 G_SpawnString
CALLI4
pop
ADDRGP4 $359
ARGP4
ADDRLP4 0
INDIRP4
ARGP4
ADDRGP4 trap_Cvar_Set
CALLV
pop
ADDRGP4 $360
ARGP4
ADDRGP4 $280
ARGP4
ADDRLP4 0
ARGP4
ADDRGP4 G_SpawnString
CALLI4
pop
ADDRGP4 $361
ARGP4
ADDRLP4 0
INDIRP4
ARGP4
ADDRGP4 trap_Cvar_Set
CALLV
pop
ADDRGP4 $362
ARGP4
ADDRGP4 $280
ARGP4
ADDRLP4 0
ARGP4
ADDRGP4 G_SpawnString
CALLI4
pop
ADDRGP4 $363
ARGP4
ADDRLP4 0
INDIRP4
ARGP4
ADDRGP4 trap_Cvar_Set
CALLV
pop
ADDRGP4 g_entities+833952
CNSTI4 1022
ASGNI4
ADDRGP4 g_entities+833952+524
ADDRGP4 $350
ASGNP4
CNSTI4 5
ARGI4
ADDRGP4 $347
ARGP4
ADDRGP4 trap_SetConfigstring
CALLV
pop
ADDRGP4 g_restarted+12
INDIRI4
CNSTI4 0
EQI4 $367
ADDRGP4 $370
ARGP4
ADDRGP4 $280
ARGP4
ADDRGP4 trap_Cvar_Set
CALLV
pop
ADDRGP4 level+16
CNSTI4 0
ASGNI4
ADDRGP4 $368
JUMPV
LABELV $367
ADDRGP4 g_doWarmup+12
INDIRI4
CNSTI4 0
EQI4 $372
ADDRGP4 level+16
CNSTI4 -1
ASGNI4
ADDRGP4 $353
ARGP4
ADDRGP4 level+16
INDIRI4
ARGI4
ADDRLP4 12
ADDRGP4 va
CALLP4
ASGNP4
CNSTI4 5
ARGI4
ADDRLP4 12
INDIRP4
ARGP4
ADDRGP4 trap_SetConfigstring
CALLV
pop
ADDRGP4 $377
ARGP4
ADDRGP4 G_LogPrintf
CALLV
pop
LABELV $372
LABELV $368
LABELV $346
endproc SP_worldspawn 16 12
export G_SpawnEntitiesFromString
proc G_SpawnEntitiesFromString 8 4
ADDRGP4 level+4512
CNSTI4 1
ASGNI4
ADDRGP4 level+4516
CNSTI4 0
ASGNI4
ADDRLP4 0
ADDRGP4 G_ParseSpawnVars
CALLI4
ASGNI4
ADDRLP4 0
INDIRI4
CNSTI4 0
NEI4 $381
ADDRGP4 $383
ARGP4
ADDRGP4 G_Error
CALLV
pop
LABELV $381
ADDRGP4 SP_worldspawn
CALLV
pop
ADDRGP4 $385
JUMPV
LABELV $384
ADDRGP4 G_SpawnGEntityFromSpawnVars
CALLV
pop
LABELV $385
ADDRLP4 4
ADDRGP4 G_ParseSpawnVars
CALLI4
ASGNI4
ADDRLP4 4
INDIRI4
CNSTI4 0
NEI4 $384
ADDRGP4 level+4512
CNSTI4 0
ASGNI4
LABELV $378
endproc G_SpawnEntitiesFromString 8 4
import SP_team_CTF_bluespawn
import SP_team_CTF_redspawn
import SP_team_CTF_blueplayer
import SP_team_CTF_redplayer
import SP_shooter_grenade
import SP_shooter_plasma
import SP_shooter_rocket
import SP_misc_portal_surface
import SP_misc_portal_camera
import SP_misc_model
import SP_misc_teleporter_dest
import SP_path_corner
import SP_info_camp
import SP_info_notnull
import SP_info_null
import SP_light
import SP_target_push
import SP_target_location
import SP_target_position
import SP_target_kill
import SP_target_relay
import SP_target_teleporter
import SP_target_score
import SP_target_character
import SP_target_laser
import SP_target_print
import SP_target_speaker
import SP_target_delay
import SP_target_give
import SP_target_remove_powerups
import SP_trigger_hurt
import SP_trigger_teleport
import SP_trigger_push
import SP_trigger_multiple
import SP_trigger_always
import SP_func_timer
import SP_func_train
import SP_func_door
import SP_func_button
import SP_func_pendulum
import SP_func_bobbing
import SP_func_rotating
import SP_func_static
import SP_func_plat
import SP_info_podium
import SP_info_thirdplace
import SP_info_secondplace
import SP_info_firstplace
import SP_info_player_intermission
import SP_info_player_deathmatch
import SP_info_player_start
import trap_SnapVector
import trap_GeneticParentsAndChildSelection
import trap_BotResetWeaponState
import trap_BotFreeWeaponState
import trap_BotAllocWeaponState
import trap_BotLoadWeaponWeights
import trap_BotGetWeaponInfo
import trap_BotChooseBestFightWeapon
import trap_BotAddAvoidSpot
import trap_BotInitMoveState
import trap_BotFreeMoveState
import trap_BotAllocMoveState
import trap_BotPredictVisiblePosition
import trap_BotMovementViewTarget
import trap_BotReachabilityArea
import trap_BotResetLastAvoidReach
import trap_BotResetAvoidReach
import trap_BotMoveInDirection
import trap_BotMoveToGoal
import trap_BotResetMoveState
import trap_BotFreeGoalState
import trap_BotAllocGoalState
import trap_BotMutateGoalFuzzyLogic
import trap_BotSaveGoalFuzzyLogic
import trap_BotInterbreedGoalFuzzyLogic
import trap_BotFreeItemWeights
import trap_BotLoadItemWeights
import trap_BotUpdateEntityItems
import trap_BotInitLevelItems
import trap_BotSetAvoidGoalTime
import trap_BotAvoidGoalTime
import trap_BotGetLevelItemGoal
import trap_BotGetMapLocationGoal
import trap_BotGetNextCampSpotGoal
import trap_BotItemGoalInVisButNotVisible
import trap_BotTouchingGoal
import trap_BotChooseNBGItem
import trap_BotChooseLTGItem
import trap_BotGetSecondGoal
import trap_BotGetTopGoal
import trap_BotGoalName
import trap_BotDumpGoalStack
import trap_BotDumpAvoidGoals
import trap_BotEmptyGoalStack
import trap_BotPopGoal
import trap_BotPushGoal
import trap_BotResetAvoidGoals
import trap_BotRemoveFromAvoidGoals
import trap_BotResetGoalState
import trap_BotSetChatName
import trap_BotSetChatGender
import trap_BotLoadChatFile
import trap_BotReplaceSynonyms
import trap_UnifyWhiteSpaces
import trap_BotMatchVariable
import trap_BotFindMatch
import trap_StringContains
import trap_BotGetChatMessage
import trap_BotEnterChat
import trap_BotChatLength
import trap_BotReplyChat
import trap_BotNumInitialChats
import trap_BotInitialChat
import trap_BotNumConsoleMessages
import trap_BotNextConsoleMessage
import trap_BotRemoveConsoleMessage
import trap_BotQueueConsoleMessage
import trap_BotFreeChatState
import trap_BotAllocChatState
import trap_Characteristic_String
import trap_Characteristic_BInteger
import trap_Characteristic_Integer
import trap_Characteristic_BFloat
import trap_Characteristic_Float
import trap_BotFreeCharacter
import trap_BotLoadCharacter
import trap_EA_ResetInput
import trap_EA_GetInput
import trap_EA_EndRegular
import trap_EA_View
import trap_EA_Move
import trap_EA_DelayedJump
import trap_EA_Jump
import trap_EA_SelectWeapon
import trap_EA_MoveRight
import trap_EA_MoveLeft
import trap_EA_MoveBack
import trap_EA_MoveForward
import trap_EA_MoveDown
import trap_EA_MoveUp
import trap_EA_Crouch
import trap_EA_Respawn
import trap_EA_Use
import trap_EA_Attack
import trap_EA_Talk
import trap_EA_Gesture
import trap_EA_Action
import trap_EA_Command
import trap_EA_SayTeam
import trap_EA_Say
import trap_AAS_PredictClientMovement
import trap_AAS_Swimming
import trap_AAS_AlternativeRouteGoals
import trap_AAS_PredictRoute
import trap_AAS_EnableRoutingArea
import trap_AAS_AreaTravelTimeToGoalArea
import trap_AAS_AreaReachability
import trap_AAS_IntForBSPEpairKey
import trap_AAS_FloatForBSPEpairKey
import trap_AAS_VectorForBSPEpairKey
import trap_AAS_ValueForBSPEpairKey
import trap_AAS_NextBSPEntity
import trap_AAS_PointContents
import trap_AAS_TraceAreas
import trap_AAS_PointReachabilityAreaIndex
import trap_AAS_PointAreaNum
import trap_AAS_Time
import trap_AAS_PresenceTypeBoundingBox
import trap_AAS_Initialized
import trap_AAS_EntityInfo
import trap_AAS_AreaInfo
import trap_AAS_BBoxAreas
import trap_BotUserCommand
import trap_BotGetServerCommand
import trap_BotGetSnapshotEntity
import trap_BotLibTest
import trap_BotLibUpdateEntity
import trap_BotLibLoadMap
import trap_BotLibStartFrame
import trap_BotLibDefine
import trap_BotLibVarGet
import trap_BotLibVarSet
import trap_BotLibShutdown
import trap_BotLibSetup
import trap_DebugPolygonDelete
import trap_DebugPolygonCreate
import trap_GetEntityToken
import trap_GetUsercmd
import trap_BotFreeClient
import trap_BotAllocateClient
import trap_EntityContact
import trap_EntitiesInBox
import trap_UnlinkEntity
import trap_LinkEntity
import trap_AreasConnected
import trap_AdjustAreaPortalState
import trap_InPVSIgnorePortals
import trap_InPVS
import trap_PointContents
import trap_Trace
import trap_SetBrushModel
import trap_GetServerinfo
import trap_SetUserinfo
import trap_GetUserinfo
import trap_GetConfigstring
import trap_SetConfigstring
import trap_SendServerCommand
import trap_DropClient
import trap_LocateGameData
import trap_Cvar_VariableStringBuffer
import trap_Cvar_VariableValue
import trap_Cvar_VariableIntegerValue
import trap_Cvar_Set
import trap_Cvar_Update
import trap_Cvar_Register
import trap_SendConsoleCommand
import trap_FS_Seek
import trap_FS_GetFileList
import trap_FS_FCloseFile
import trap_FS_Write
import trap_FS_Read
import trap_FS_FOpenFile
import trap_Args
import trap_Argv
import trap_Argc
import trap_RealTime
import trap_Milliseconds
import trap_Error
import trap_Printf
import g_proxMineTimeout
import g_singlePlayer
import g_enableBreath
import g_enableDust
import g_rankings
import pmove_msec
import pmove_fixed
import g_smoothClients
import g_blueteam
import g_redteam
import g_cubeTimeout
import g_obeliskRespawnDelay
import g_obeliskRegenAmount
import g_obeliskRegenPeriod
import g_obeliskHealth
import g_filterBan
import g_banIPs
import g_teamForceBalance
import g_teamAutoJoin
import g_allowVote
import g_blood
import g_doWarmup
import g_warmup
import g_motd
import g_synchronousClients
import g_weaponTeamRespawn
import g_weaponRespawn
import g_debugDamage
import g_debugAlloc
import g_debugMove
import g_inactivity
import g_forcerespawn
import g_quadfactor
import g_knockback
import g_speed
import g_gravity
import g_needpass
import g_password
import g_friendlyFire
import g_capturelimit
import g_timelimit
import g_fraglimit
import g_dmflags
import g_restarted
import g_maxGameClients
import g_maxclients
import g_cheats
import g_dedicated
import g_gametype
import g_entities
import level
import Pickup_Team
import CheckTeamStatus
import TeamplayInfoMessage
import Team_GetLocationMsg
import Team_GetLocation
import SelectCTFSpawnPoint
import Team_FreeEntity
import Team_ReturnFlag
import Team_InitGame
import Team_CheckHurtCarrier
import Team_FragBonuses
import Team_DroppedFlagThink
import AddTeamScore
import TeamColorString
import OtherTeamName
import TeamName
import OtherTeam
import BotTestAAS
import BotAIStartFrame
import BotAIShutdownClient
import BotAISetupClient
import BotAILoadMap
import BotAIShutdown
import BotAISetup
import BotInterbreedEndMatch
import Svcmd_BotList_f
import Svcmd_AddBot_f
import G_BotConnect
import G_RemoveQueuedBotBegin
import G_CheckBotSpawn
import G_GetBotInfoByName
import G_GetBotInfoByNumber
import G_InitBots
import Svcmd_AbortPodium_f
import SpawnModelsOnVictoryPads
import UpdateTournamentInfo
import G_WriteSessionData
import G_InitWorldSession
import G_InitSessionData
import G_ReadSessionData
import Svcmd_GameMem_f
import G_InitMemory
import G_Alloc
import CheckObeliskAttack
import Team_CheckDroppedItem
import OnSameTeam
import G_RunClient
import ClientEndFrame
import ClientThink
import ClientCommand
import ClientBegin
import ClientDisconnect
import ClientUserinfoChanged
import ClientConnect
import G_Error
import G_Printf
import SendScoreboardMessageToAllClients
import G_LogPrintf
import G_RunThink
import CheckTeamLeader
import SetLeader
import FindIntermissionPoint
import DeathmatchScoreboardMessage
import G_SetStats
import MoveClientToIntermission
import G_StartKamikaze
import FireWeapon
import G_FilterPacket
import G_ProcessIPBans
import ConsoleCommand
import SpotWouldTelefrag
import CalculateRanks
import AddScore
import player_die
import ClientSpawn
import InitBodyQue
import InitClientResp
import InitClientPersistant
import BeginIntermission
import respawn
import CopyToBodyQue
import SelectSpawnPoint
import SetClientViewAngle
import PickTeam
import TeamLeader
import TeamCount
import Weapon_HookThink
import Weapon_HookFree
import CheckGauntletAttack
import SnapVectorTowards
import CalcMuzzlePoint
import LogAccuracyHit
import DropPortalDestination
import DropPortalSource
import TeleportPlayer
import trigger_teleporter_touch
import Touch_DoorTrigger
import G_RunMover
import fire_prox
import fire_nail
import fire_grapple
import fire_bfg
import fire_rocket
import fire_grenade
import fire_plasma
import fire_blaster
import G_RunMissile
import TossClientCubes
import TossClientPersistantPowerups
import TossClientItems
import body_die
import G_InvulnerabilityEffect
import G_RadiusDamage
import G_Damage
import CanDamage
import BuildShaderStateConfig
import AddRemap
import G_SetOrigin
import G_AddEvent
import G_AddPredictableEvent
import vectoyaw
import vtos
import tv
import G_TouchSolids
import G_TouchTriggers
import G_EntitiesFree
import G_FreeEntity
import G_Sound
import G_TempEntity
import G_Spawn
import G_InitGentity
import G_SetMovedir
import G_UseTargets
import G_PickTarget
import G_Find
import G_KillBox
import G_TeamCommand
import G_SoundIndex
import G_ModelIndex
import SaveRegisteredItems
import RegisterItem
import ClearRegisteredItems
import Touch_Item
import Add_Ammo
import ArmorIndex
import Think_Weapon
import FinishSpawningItem
import G_SpawnItem
import SetRespawn
import LaunchItem
import Drop_Item
import PrecacheItem
import UseHoldableItem
import RespawnItem
import G_RunItem
import G_CheckTeamItems
import Cmd_FollowCycle_f
import SetTeam
import BroadcastTeamChange
import StopFollowing
import Cmd_Score_f
import dropWeapon
import ThrowWeapon
import ClipAmountForWeapon
import Cmd_Reload
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
LABELV $383
byte 1 83
byte 1 112
byte 1 97
byte 1 119
byte 1 110
byte 1 69
byte 1 110
byte 1 116
byte 1 105
byte 1 116
byte 1 105
byte 1 101
byte 1 115
byte 1 58
byte 1 32
byte 1 110
byte 1 111
byte 1 32
byte 1 101
byte 1 110
byte 1 116
byte 1 105
byte 1 116
byte 1 105
byte 1 101
byte 1 115
byte 1 0
align 1
LABELV $377
byte 1 87
byte 1 97
byte 1 114
byte 1 109
byte 1 117
byte 1 112
byte 1 58
byte 1 10
byte 1 0
align 1
LABELV $370
byte 1 103
byte 1 95
byte 1 114
byte 1 101
byte 1 115
byte 1 116
byte 1 97
byte 1 114
byte 1 116
byte 1 101
byte 1 100
byte 1 0
align 1
LABELV $363
byte 1 103
byte 1 95
byte 1 101
byte 1 110
byte 1 97
byte 1 98
byte 1 108
byte 1 101
byte 1 66
byte 1 114
byte 1 101
byte 1 97
byte 1 116
byte 1 104
byte 1 0
align 1
LABELV $362
byte 1 101
byte 1 110
byte 1 97
byte 1 98
byte 1 108
byte 1 101
byte 1 66
byte 1 114
byte 1 101
byte 1 97
byte 1 116
byte 1 104
byte 1 0
align 1
LABELV $361
byte 1 103
byte 1 95
byte 1 101
byte 1 110
byte 1 97
byte 1 98
byte 1 108
byte 1 101
byte 1 68
byte 1 117
byte 1 115
byte 1 116
byte 1 0
align 1
LABELV $360
byte 1 101
byte 1 110
byte 1 97
byte 1 98
byte 1 108
byte 1 101
byte 1 68
byte 1 117
byte 1 115
byte 1 116
byte 1 0
align 1
LABELV $359
byte 1 103
byte 1 95
byte 1 103
byte 1 114
byte 1 97
byte 1 118
byte 1 105
byte 1 116
byte 1 121
byte 1 0
align 1
LABELV $358
byte 1 56
byte 1 48
byte 1 48
byte 1 0
align 1
LABELV $357
byte 1 103
byte 1 114
byte 1 97
byte 1 118
byte 1 105
byte 1 116
byte 1 121
byte 1 0
align 1
LABELV $355
byte 1 109
byte 1 117
byte 1 115
byte 1 105
byte 1 99
byte 1 0
align 1
LABELV $353
byte 1 37
byte 1 105
byte 1 0
align 1
LABELV $352
byte 1 98
byte 1 97
byte 1 115
byte 1 101
byte 1 113
byte 1 51
byte 1 45
byte 1 49
byte 1 0
align 1
LABELV $351
byte 1 83
byte 1 80
byte 1 95
byte 1 119
byte 1 111
byte 1 114
byte 1 108
byte 1 100
byte 1 115
byte 1 112
byte 1 97
byte 1 119
byte 1 110
byte 1 58
byte 1 32
byte 1 84
byte 1 104
byte 1 101
byte 1 32
byte 1 102
byte 1 105
byte 1 114
byte 1 115
byte 1 116
byte 1 32
byte 1 101
byte 1 110
byte 1 116
byte 1 105
byte 1 116
byte 1 121
byte 1 32
byte 1 105
byte 1 115
byte 1 110
byte 1 39
byte 1 116
byte 1 32
byte 1 39
byte 1 119
byte 1 111
byte 1 114
byte 1 108
byte 1 100
byte 1 115
byte 1 112
byte 1 97
byte 1 119
byte 1 110
byte 1 39
byte 1 0
align 1
LABELV $350
byte 1 119
byte 1 111
byte 1 114
byte 1 108
byte 1 100
byte 1 115
byte 1 112
byte 1 97
byte 1 119
byte 1 110
byte 1 0
align 1
LABELV $347
byte 1 0
align 1
LABELV $339
byte 1 71
byte 1 95
byte 1 80
byte 1 97
byte 1 114
byte 1 115
byte 1 101
byte 1 83
byte 1 112
byte 1 97
byte 1 119
byte 1 110
byte 1 86
byte 1 97
byte 1 114
byte 1 115
byte 1 58
byte 1 32
byte 1 77
byte 1 65
byte 1 88
byte 1 95
byte 1 83
byte 1 80
byte 1 65
byte 1 87
byte 1 78
byte 1 95
byte 1 86
byte 1 65
byte 1 82
byte 1 83
byte 1 0
align 1
LABELV $335
byte 1 71
byte 1 95
byte 1 80
byte 1 97
byte 1 114
byte 1 115
byte 1 101
byte 1 83
byte 1 112
byte 1 97
byte 1 119
byte 1 110
byte 1 86
byte 1 97
byte 1 114
byte 1 115
byte 1 58
byte 1 32
byte 1 99
byte 1 108
byte 1 111
byte 1 115
byte 1 105
byte 1 110
byte 1 103
byte 1 32
byte 1 98
byte 1 114
byte 1 97
byte 1 99
byte 1 101
byte 1 32
byte 1 119
byte 1 105
byte 1 116
byte 1 104
byte 1 111
byte 1 117
byte 1 116
byte 1 32
byte 1 100
byte 1 97
byte 1 116
byte 1 97
byte 1 0
align 1
LABELV $328
byte 1 71
byte 1 95
byte 1 80
byte 1 97
byte 1 114
byte 1 115
byte 1 101
byte 1 83
byte 1 112
byte 1 97
byte 1 119
byte 1 110
byte 1 86
byte 1 97
byte 1 114
byte 1 115
byte 1 58
byte 1 32
byte 1 69
byte 1 79
byte 1 70
byte 1 32
byte 1 119
byte 1 105
byte 1 116
byte 1 104
byte 1 111
byte 1 117
byte 1 116
byte 1 32
byte 1 99
byte 1 108
byte 1 111
byte 1 115
byte 1 105
byte 1 110
byte 1 103
byte 1 32
byte 1 98
byte 1 114
byte 1 97
byte 1 99
byte 1 101
byte 1 0
align 1
LABELV $322
byte 1 71
byte 1 95
byte 1 80
byte 1 97
byte 1 114
byte 1 115
byte 1 101
byte 1 83
byte 1 112
byte 1 97
byte 1 119
byte 1 110
byte 1 86
byte 1 97
byte 1 114
byte 1 115
byte 1 58
byte 1 32
byte 1 102
byte 1 111
byte 1 117
byte 1 110
byte 1 100
byte 1 32
byte 1 37
byte 1 115
byte 1 32
byte 1 119
byte 1 104
byte 1 101
byte 1 110
byte 1 32
byte 1 101
byte 1 120
byte 1 112
byte 1 101
byte 1 99
byte 1 116
byte 1 105
byte 1 110
byte 1 103
byte 1 32
byte 1 123
byte 1 0
align 1
LABELV $311
byte 1 71
byte 1 95
byte 1 65
byte 1 100
byte 1 100
byte 1 83
byte 1 112
byte 1 97
byte 1 119
byte 1 110
byte 1 86
byte 1 97
byte 1 114
byte 1 84
byte 1 111
byte 1 107
byte 1 101
byte 1 110
byte 1 58
byte 1 32
byte 1 77
byte 1 65
byte 1 88
byte 1 95
byte 1 83
byte 1 80
byte 1 65
byte 1 87
byte 1 78
byte 1 95
byte 1 67
byte 1 72
byte 1 65
byte 1 82
byte 1 83
byte 1 0
align 1
LABELV $297
byte 1 103
byte 1 97
byte 1 109
byte 1 101
byte 1 116
byte 1 121
byte 1 112
byte 1 101
byte 1 0
align 1
LABELV $292
byte 1 110
byte 1 111
byte 1 116
byte 1 113
byte 1 51
byte 1 97
byte 1 0
align 1
LABELV $289
byte 1 110
byte 1 111
byte 1 116
byte 1 102
byte 1 114
byte 1 101
byte 1 101
byte 1 0
align 1
LABELV $286
byte 1 110
byte 1 111
byte 1 116
byte 1 116
byte 1 101
byte 1 97
byte 1 109
byte 1 0
align 1
LABELV $280
byte 1 48
byte 1 0
align 1
LABELV $279
byte 1 110
byte 1 111
byte 1 116
byte 1 115
byte 1 105
byte 1 110
byte 1 103
byte 1 108
byte 1 101
byte 1 0
align 1
LABELV $267
byte 1 97
byte 1 115
byte 1 115
byte 1 97
byte 1 115
byte 1 115
byte 1 105
byte 1 110
byte 1 115
byte 1 0
align 1
LABELV $266
byte 1 115
byte 1 105
byte 1 110
byte 1 103
byte 1 108
byte 1 101
byte 1 0
align 1
LABELV $265
byte 1 116
byte 1 101
byte 1 97
byte 1 109
byte 1 115
byte 1 117
byte 1 114
byte 1 118
byte 1 105
byte 1 118
byte 1 111
byte 1 114
byte 1 0
align 1
LABELV $264
byte 1 102
byte 1 102
byte 1 97
byte 1 0
align 1
LABELV $231
byte 1 37
byte 1 115
byte 1 32
byte 1 100
byte 1 111
byte 1 101
byte 1 115
byte 1 110
byte 1 39
byte 1 116
byte 1 32
byte 1 104
byte 1 97
byte 1 118
byte 1 101
byte 1 32
byte 1 97
byte 1 32
byte 1 115
byte 1 112
byte 1 97
byte 1 119
byte 1 110
byte 1 32
byte 1 102
byte 1 117
byte 1 110
byte 1 99
byte 1 116
byte 1 105
byte 1 111
byte 1 110
byte 1 10
byte 1 0
align 1
LABELV $217
byte 1 97
byte 1 109
byte 1 109
byte 1 111
byte 1 95
byte 1 0
align 1
LABELV $214
byte 1 97
byte 1 109
byte 1 109
byte 1 111
byte 1 95
byte 1 98
byte 1 102
byte 1 103
byte 1 0
align 1
LABELV $211
byte 1 97
byte 1 109
byte 1 109
byte 1 111
byte 1 95
byte 1 114
byte 1 111
byte 1 99
byte 1 107
byte 1 101
byte 1 116
byte 1 115
byte 1 0
align 1
LABELV $208
byte 1 97
byte 1 109
byte 1 109
byte 1 111
byte 1 95
byte 1 108
byte 1 105
byte 1 103
byte 1 104
byte 1 116
byte 1 110
byte 1 105
byte 1 110
byte 1 103
byte 1 0
align 1
LABELV $205
byte 1 97
byte 1 109
byte 1 109
byte 1 111
byte 1 95
byte 1 99
byte 1 101
byte 1 108
byte 1 108
byte 1 115
byte 1 0
align 1
LABELV $202
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 95
byte 1 114
byte 1 101
byte 1 103
byte 1 101
byte 1 110
byte 1 0
align 1
LABELV $199
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 95
byte 1 105
byte 1 110
byte 1 118
byte 1 105
byte 1 115
byte 1 0
align 1
LABELV $196
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 95
byte 1 102
byte 1 108
byte 1 105
byte 1 103
byte 1 104
byte 1 116
byte 1 0
align 1
LABELV $193
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 95
byte 1 104
byte 1 97
byte 1 115
byte 1 116
byte 1 101
byte 1 0
align 1
LABELV $190
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 95
byte 1 101
byte 1 110
byte 1 118
byte 1 105
byte 1 114
byte 1 111
byte 1 0
align 1
LABELV $187
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 95
byte 1 113
byte 1 117
byte 1 97
byte 1 100
byte 1 0
align 1
LABELV $184
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 95
byte 1 104
byte 1 111
byte 1 108
byte 1 100
byte 1 97
byte 1 98
byte 1 108
byte 1 101
byte 1 95
byte 1 116
byte 1 101
byte 1 108
byte 1 101
byte 1 112
byte 1 111
byte 1 114
byte 1 116
byte 1 0
align 1
LABELV $181
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 95
byte 1 104
byte 1 111
byte 1 108
byte 1 100
byte 1 97
byte 1 98
byte 1 108
byte 1 101
byte 1 95
byte 1 109
byte 1 101
byte 1 100
byte 1 107
byte 1 105
byte 1 116
byte 1 0
align 1
LABELV $178
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 95
byte 1 104
byte 1 101
byte 1 97
byte 1 108
byte 1 116
byte 1 104
byte 1 95
byte 1 109
byte 1 101
byte 1 103
byte 1 97
byte 1 0
align 1
LABELV $175
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 95
byte 1 104
byte 1 101
byte 1 97
byte 1 108
byte 1 116
byte 1 104
byte 1 95
byte 1 108
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 0
align 1
LABELV $172
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 95
byte 1 104
byte 1 101
byte 1 97
byte 1 108
byte 1 116
byte 1 104
byte 1 0
align 1
LABELV $169
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 95
byte 1 104
byte 1 101
byte 1 97
byte 1 108
byte 1 116
byte 1 104
byte 1 95
byte 1 115
byte 1 109
byte 1 97
byte 1 108
byte 1 108
byte 1 0
align 1
LABELV $166
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 95
byte 1 97
byte 1 114
byte 1 109
byte 1 111
byte 1 114
byte 1 95
byte 1 98
byte 1 111
byte 1 100
byte 1 121
byte 1 0
align 1
LABELV $163
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 95
byte 1 97
byte 1 114
byte 1 109
byte 1 111
byte 1 114
byte 1 95
byte 1 99
byte 1 111
byte 1 109
byte 1 98
byte 1 97
byte 1 116
byte 1 0
align 1
LABELV $160
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 95
byte 1 97
byte 1 114
byte 1 109
byte 1 111
byte 1 114
byte 1 95
byte 1 115
byte 1 104
byte 1 97
byte 1 114
byte 1 100
byte 1 0
align 1
LABELV $157
byte 1 119
byte 1 101
byte 1 97
byte 1 112
byte 1 111
byte 1 110
byte 1 95
byte 1 98
byte 1 102
byte 1 103
byte 1 0
align 1
LABELV $154
byte 1 119
byte 1 101
byte 1 97
byte 1 112
byte 1 111
byte 1 110
byte 1 95
byte 1 112
byte 1 108
byte 1 97
byte 1 115
byte 1 109
byte 1 97
byte 1 103
byte 1 117
byte 1 110
byte 1 0
align 1
LABELV $151
byte 1 119
byte 1 101
byte 1 97
byte 1 112
byte 1 111
byte 1 110
byte 1 95
byte 1 108
byte 1 105
byte 1 103
byte 1 104
byte 1 116
byte 1 110
byte 1 105
byte 1 110
byte 1 103
byte 1 0
align 1
LABELV $148
byte 1 119
byte 1 101
byte 1 97
byte 1 112
byte 1 111
byte 1 110
byte 1 95
byte 1 114
byte 1 111
byte 1 99
byte 1 107
byte 1 101
byte 1 116
byte 1 108
byte 1 97
byte 1 117
byte 1 110
byte 1 99
byte 1 104
byte 1 101
byte 1 114
byte 1 0
align 1
LABELV $145
byte 1 71
byte 1 95
byte 1 67
byte 1 97
byte 1 108
byte 1 108
byte 1 83
byte 1 112
byte 1 97
byte 1 119
byte 1 110
byte 1 58
byte 1 32
byte 1 78
byte 1 85
byte 1 76
byte 1 76
byte 1 32
byte 1 99
byte 1 108
byte 1 97
byte 1 115
byte 1 115
byte 1 110
byte 1 97
byte 1 109
byte 1 101
byte 1 10
byte 1 0
align 1
LABELV $141
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 95
byte 1 98
byte 1 111
byte 1 116
byte 1 114
byte 1 111
byte 1 97
byte 1 109
byte 1 0
align 1
LABELV $140
byte 1 116
byte 1 101
byte 1 97
byte 1 109
byte 1 95
byte 1 67
byte 1 84
byte 1 70
byte 1 95
byte 1 98
byte 1 108
byte 1 117
byte 1 101
byte 1 115
byte 1 112
byte 1 97
byte 1 119
byte 1 110
byte 1 0
align 1
LABELV $139
byte 1 116
byte 1 101
byte 1 97
byte 1 109
byte 1 95
byte 1 67
byte 1 84
byte 1 70
byte 1 95
byte 1 114
byte 1 101
byte 1 100
byte 1 115
byte 1 112
byte 1 97
byte 1 119
byte 1 110
byte 1 0
align 1
LABELV $138
byte 1 116
byte 1 101
byte 1 97
byte 1 109
byte 1 95
byte 1 67
byte 1 84
byte 1 70
byte 1 95
byte 1 98
byte 1 108
byte 1 117
byte 1 101
byte 1 112
byte 1 108
byte 1 97
byte 1 121
byte 1 101
byte 1 114
byte 1 0
align 1
LABELV $137
byte 1 116
byte 1 101
byte 1 97
byte 1 109
byte 1 95
byte 1 67
byte 1 84
byte 1 70
byte 1 95
byte 1 114
byte 1 101
byte 1 100
byte 1 112
byte 1 108
byte 1 97
byte 1 121
byte 1 101
byte 1 114
byte 1 0
align 1
LABELV $136
byte 1 115
byte 1 104
byte 1 111
byte 1 111
byte 1 116
byte 1 101
byte 1 114
byte 1 95
byte 1 112
byte 1 108
byte 1 97
byte 1 115
byte 1 109
byte 1 97
byte 1 0
align 1
LABELV $135
byte 1 115
byte 1 104
byte 1 111
byte 1 111
byte 1 116
byte 1 101
byte 1 114
byte 1 95
byte 1 103
byte 1 114
byte 1 101
byte 1 110
byte 1 97
byte 1 100
byte 1 101
byte 1 0
align 1
LABELV $134
byte 1 115
byte 1 104
byte 1 111
byte 1 111
byte 1 116
byte 1 101
byte 1 114
byte 1 95
byte 1 114
byte 1 111
byte 1 99
byte 1 107
byte 1 101
byte 1 116
byte 1 0
align 1
LABELV $133
byte 1 109
byte 1 105
byte 1 115
byte 1 99
byte 1 95
byte 1 112
byte 1 111
byte 1 114
byte 1 116
byte 1 97
byte 1 108
byte 1 95
byte 1 99
byte 1 97
byte 1 109
byte 1 101
byte 1 114
byte 1 97
byte 1 0
align 1
LABELV $132
byte 1 109
byte 1 105
byte 1 115
byte 1 99
byte 1 95
byte 1 112
byte 1 111
byte 1 114
byte 1 116
byte 1 97
byte 1 108
byte 1 95
byte 1 115
byte 1 117
byte 1 114
byte 1 102
byte 1 97
byte 1 99
byte 1 101
byte 1 0
align 1
LABELV $131
byte 1 109
byte 1 105
byte 1 115
byte 1 99
byte 1 95
byte 1 109
byte 1 111
byte 1 100
byte 1 101
byte 1 108
byte 1 0
align 1
LABELV $130
byte 1 109
byte 1 105
byte 1 115
byte 1 99
byte 1 95
byte 1 116
byte 1 101
byte 1 108
byte 1 101
byte 1 112
byte 1 111
byte 1 114
byte 1 116
byte 1 101
byte 1 114
byte 1 95
byte 1 100
byte 1 101
byte 1 115
byte 1 116
byte 1 0
align 1
LABELV $129
byte 1 112
byte 1 97
byte 1 116
byte 1 104
byte 1 95
byte 1 99
byte 1 111
byte 1 114
byte 1 110
byte 1 101
byte 1 114
byte 1 0
align 1
LABELV $128
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 95
byte 1 112
byte 1 117
byte 1 115
byte 1 104
byte 1 0
align 1
LABELV $127
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 95
byte 1 108
byte 1 111
byte 1 99
byte 1 97
byte 1 116
byte 1 105
byte 1 111
byte 1 110
byte 1 0
align 1
LABELV $126
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 95
byte 1 112
byte 1 111
byte 1 115
byte 1 105
byte 1 116
byte 1 105
byte 1 111
byte 1 110
byte 1 0
align 1
LABELV $125
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 95
byte 1 107
byte 1 105
byte 1 108
byte 1 108
byte 1 0
align 1
LABELV $124
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 95
byte 1 114
byte 1 101
byte 1 108
byte 1 97
byte 1 121
byte 1 0
align 1
LABELV $123
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 95
byte 1 116
byte 1 101
byte 1 108
byte 1 101
byte 1 112
byte 1 111
byte 1 114
byte 1 116
byte 1 101
byte 1 114
byte 1 0
align 1
LABELV $122
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 95
byte 1 115
byte 1 99
byte 1 111
byte 1 114
byte 1 101
byte 1 0
align 1
LABELV $121
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 95
byte 1 108
byte 1 97
byte 1 115
byte 1 101
byte 1 114
byte 1 0
align 1
LABELV $120
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 95
byte 1 112
byte 1 114
byte 1 105
byte 1 110
byte 1 116
byte 1 0
align 1
LABELV $119
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 95
byte 1 115
byte 1 112
byte 1 101
byte 1 97
byte 1 107
byte 1 101
byte 1 114
byte 1 0
align 1
LABELV $118
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 95
byte 1 100
byte 1 101
byte 1 108
byte 1 97
byte 1 121
byte 1 0
align 1
LABELV $117
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 95
byte 1 114
byte 1 101
byte 1 109
byte 1 111
byte 1 118
byte 1 101
byte 1 95
byte 1 112
byte 1 111
byte 1 119
byte 1 101
byte 1 114
byte 1 117
byte 1 112
byte 1 115
byte 1 0
align 1
LABELV $116
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 95
byte 1 103
byte 1 105
byte 1 118
byte 1 101
byte 1 0
align 1
LABELV $115
byte 1 116
byte 1 114
byte 1 105
byte 1 103
byte 1 103
byte 1 101
byte 1 114
byte 1 95
byte 1 104
byte 1 117
byte 1 114
byte 1 116
byte 1 0
align 1
LABELV $114
byte 1 116
byte 1 114
byte 1 105
byte 1 103
byte 1 103
byte 1 101
byte 1 114
byte 1 95
byte 1 116
byte 1 101
byte 1 108
byte 1 101
byte 1 112
byte 1 111
byte 1 114
byte 1 116
byte 1 0
align 1
LABELV $113
byte 1 116
byte 1 114
byte 1 105
byte 1 103
byte 1 103
byte 1 101
byte 1 114
byte 1 95
byte 1 112
byte 1 117
byte 1 115
byte 1 104
byte 1 0
align 1
LABELV $112
byte 1 116
byte 1 114
byte 1 105
byte 1 103
byte 1 103
byte 1 101
byte 1 114
byte 1 95
byte 1 109
byte 1 117
byte 1 108
byte 1 116
byte 1 105
byte 1 112
byte 1 108
byte 1 101
byte 1 0
align 1
LABELV $111
byte 1 116
byte 1 114
byte 1 105
byte 1 103
byte 1 103
byte 1 101
byte 1 114
byte 1 95
byte 1 97
byte 1 108
byte 1 119
byte 1 97
byte 1 121
byte 1 115
byte 1 0
align 1
LABELV $110
byte 1 102
byte 1 117
byte 1 110
byte 1 99
byte 1 95
byte 1 116
byte 1 105
byte 1 109
byte 1 101
byte 1 114
byte 1 0
align 1
LABELV $109
byte 1 102
byte 1 117
byte 1 110
byte 1 99
byte 1 95
byte 1 103
byte 1 114
byte 1 111
byte 1 117
byte 1 112
byte 1 0
align 1
LABELV $108
byte 1 102
byte 1 117
byte 1 110
byte 1 99
byte 1 95
byte 1 116
byte 1 114
byte 1 97
byte 1 105
byte 1 110
byte 1 0
align 1
LABELV $107
byte 1 102
byte 1 117
byte 1 110
byte 1 99
byte 1 95
byte 1 112
byte 1 101
byte 1 110
byte 1 100
byte 1 117
byte 1 108
byte 1 117
byte 1 109
byte 1 0
align 1
LABELV $106
byte 1 102
byte 1 117
byte 1 110
byte 1 99
byte 1 95
byte 1 98
byte 1 111
byte 1 98
byte 1 98
byte 1 105
byte 1 110
byte 1 103
byte 1 0
align 1
LABELV $105
byte 1 102
byte 1 117
byte 1 110
byte 1 99
byte 1 95
byte 1 114
byte 1 111
byte 1 116
byte 1 97
byte 1 116
byte 1 105
byte 1 110
byte 1 103
byte 1 0
align 1
LABELV $104
byte 1 102
byte 1 117
byte 1 110
byte 1 99
byte 1 95
byte 1 115
byte 1 116
byte 1 97
byte 1 116
byte 1 105
byte 1 99
byte 1 0
align 1
LABELV $103
byte 1 102
byte 1 117
byte 1 110
byte 1 99
byte 1 95
byte 1 100
byte 1 111
byte 1 111
byte 1 114
byte 1 0
align 1
LABELV $102
byte 1 102
byte 1 117
byte 1 110
byte 1 99
byte 1 95
byte 1 98
byte 1 117
byte 1 116
byte 1 116
byte 1 111
byte 1 110
byte 1 0
align 1
LABELV $101
byte 1 102
byte 1 117
byte 1 110
byte 1 99
byte 1 95
byte 1 112
byte 1 108
byte 1 97
byte 1 116
byte 1 0
align 1
LABELV $100
byte 1 105
byte 1 110
byte 1 102
byte 1 111
byte 1 95
byte 1 99
byte 1 97
byte 1 109
byte 1 112
byte 1 0
align 1
LABELV $99
byte 1 105
byte 1 110
byte 1 102
byte 1 111
byte 1 95
byte 1 110
byte 1 111
byte 1 116
byte 1 110
byte 1 117
byte 1 108
byte 1 108
byte 1 0
align 1
LABELV $98
byte 1 105
byte 1 110
byte 1 102
byte 1 111
byte 1 95
byte 1 110
byte 1 117
byte 1 108
byte 1 108
byte 1 0
align 1
LABELV $97
byte 1 105
byte 1 110
byte 1 102
byte 1 111
byte 1 95
byte 1 112
byte 1 108
byte 1 97
byte 1 121
byte 1 101
byte 1 114
byte 1 95
byte 1 105
byte 1 110
byte 1 116
byte 1 101
byte 1 114
byte 1 109
byte 1 105
byte 1 115
byte 1 115
byte 1 105
byte 1 111
byte 1 110
byte 1 0
align 1
LABELV $96
byte 1 105
byte 1 110
byte 1 102
byte 1 111
byte 1 95
byte 1 112
byte 1 108
byte 1 97
byte 1 121
byte 1 101
byte 1 114
byte 1 95
byte 1 100
byte 1 101
byte 1 97
byte 1 116
byte 1 104
byte 1 109
byte 1 97
byte 1 116
byte 1 99
byte 1 104
byte 1 0
align 1
LABELV $95
byte 1 105
byte 1 110
byte 1 102
byte 1 111
byte 1 95
byte 1 112
byte 1 108
byte 1 97
byte 1 121
byte 1 101
byte 1 114
byte 1 95
byte 1 115
byte 1 116
byte 1 97
byte 1 114
byte 1 116
byte 1 0
align 1
LABELV $92
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 83
byte 1 104
byte 1 97
byte 1 100
byte 1 101
byte 1 114
byte 1 78
byte 1 101
byte 1 119
byte 1 78
byte 1 97
byte 1 109
byte 1 101
byte 1 0
align 1
LABELV $91
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 83
byte 1 104
byte 1 97
byte 1 100
byte 1 101
byte 1 114
byte 1 78
byte 1 97
byte 1 109
byte 1 101
byte 1 0
align 1
LABELV $90
byte 1 97
byte 1 110
byte 1 103
byte 1 108
byte 1 101
byte 1 0
align 1
LABELV $89
byte 1 97
byte 1 110
byte 1 103
byte 1 108
byte 1 101
byte 1 115
byte 1 0
align 1
LABELV $88
byte 1 100
byte 1 109
byte 1 103
byte 1 0
align 1
LABELV $87
byte 1 108
byte 1 105
byte 1 103
byte 1 104
byte 1 116
byte 1 0
align 1
LABELV $86
byte 1 104
byte 1 101
byte 1 97
byte 1 108
byte 1 116
byte 1 104
byte 1 0
align 1
LABELV $85
byte 1 99
byte 1 111
byte 1 117
byte 1 110
byte 1 116
byte 1 0
align 1
LABELV $84
byte 1 114
byte 1 97
byte 1 110
byte 1 100
byte 1 111
byte 1 109
byte 1 0
align 1
LABELV $83
byte 1 119
byte 1 97
byte 1 105
byte 1 116
byte 1 0
align 1
LABELV $82
byte 1 116
byte 1 101
byte 1 97
byte 1 109
byte 1 0
align 1
LABELV $81
byte 1 109
byte 1 101
byte 1 115
byte 1 115
byte 1 97
byte 1 103
byte 1 101
byte 1 0
align 1
LABELV $80
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 110
byte 1 97
byte 1 109
byte 1 101
byte 1 0
align 1
LABELV $79
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 0
align 1
LABELV $78
byte 1 115
byte 1 112
byte 1 101
byte 1 101
byte 1 100
byte 1 0
align 1
LABELV $77
byte 1 115
byte 1 112
byte 1 97
byte 1 119
byte 1 110
byte 1 102
byte 1 108
byte 1 97
byte 1 103
byte 1 115
byte 1 0
align 1
LABELV $76
byte 1 109
byte 1 111
byte 1 100
byte 1 101
byte 1 108
byte 1 50
byte 1 0
align 1
LABELV $75
byte 1 109
byte 1 111
byte 1 100
byte 1 101
byte 1 108
byte 1 0
align 1
LABELV $74
byte 1 111
byte 1 114
byte 1 105
byte 1 103
byte 1 105
byte 1 110
byte 1 0
align 1
LABELV $73
byte 1 99
byte 1 108
byte 1 97
byte 1 115
byte 1 115
byte 1 110
byte 1 97
byte 1 109
byte 1 101
byte 1 0
align 1
LABELV $70
byte 1 37
byte 1 102
byte 1 32
byte 1 37
byte 1 102
byte 1 32
byte 1 37
byte 1 102
byte 1 0
