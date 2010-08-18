export CG_BuildSolidList
code
proc CG_BuildSolidList 32 0
ADDRLP4 16
CNSTI4 0
ASGNI4
ADDRGP4 cg_numSolidEntities
ADDRLP4 16
INDIRI4
ASGNI4
ADDRGP4 cg_numTriggerEntities
ADDRLP4 16
INDIRI4
ASGNI4
ADDRGP4 cg+40
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $72
ADDRLP4 20
CNSTI4 0
ASGNI4
ADDRGP4 cg+107596
INDIRI4
ADDRLP4 20
INDIRI4
NEI4 $72
ADDRGP4 cg+107592
INDIRI4
ADDRLP4 20
INDIRI4
NEI4 $72
ADDRLP4 12
ADDRGP4 cg+40
INDIRP4
ASGNP4
ADDRGP4 $73
JUMPV
LABELV $72
ADDRLP4 12
ADDRGP4 cg+36
INDIRP4
ASGNP4
LABELV $73
ADDRLP4 8
CNSTI4 0
ASGNI4
ADDRGP4 $82
JUMPV
LABELV $79
ADDRLP4 0
CNSTI4 728
CNSTI4 208
ADDRLP4 8
INDIRI4
MULI4
ADDRLP4 12
INDIRP4
CNSTI4 516
ADDP4
ADDP4
INDIRI4
MULI4
ADDRGP4 cg_entities
ADDP4
ASGNP4
ADDRLP4 4
ADDRLP4 0
INDIRP4
ASGNP4
ADDRLP4 24
ADDRLP4 4
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
ASGNI4
ADDRLP4 24
INDIRI4
CNSTI4 2
EQI4 $86
ADDRLP4 24
INDIRI4
CNSTI4 8
EQI4 $86
ADDRLP4 24
INDIRI4
CNSTI4 9
NEI4 $83
LABELV $86
ADDRGP4 cg_numTriggerEntities
INDIRI4
CNSTI4 2
LSHI4
ADDRGP4 cg_triggerEntities
ADDP4
ADDRLP4 0
INDIRP4
ASGNP4
ADDRLP4 28
ADDRGP4 cg_numTriggerEntities
ASGNP4
ADDRLP4 28
INDIRP4
ADDRLP4 28
INDIRP4
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
ADDRGP4 $80
JUMPV
LABELV $83
ADDRLP4 0
INDIRP4
CNSTI4 384
ADDP4
INDIRI4
CNSTI4 0
EQI4 $87
ADDRGP4 cg_numSolidEntities
INDIRI4
CNSTI4 2
LSHI4
ADDRGP4 cg_solidEntities
ADDP4
ADDRLP4 0
INDIRP4
ASGNP4
ADDRLP4 28
ADDRGP4 cg_numSolidEntities
ASGNP4
ADDRLP4 28
INDIRP4
ADDRLP4 28
INDIRP4
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $87
LABELV $80
ADDRLP4 8
ADDRLP4 8
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $82
ADDRLP4 8
INDIRI4
ADDRLP4 12
INDIRP4
CNSTI4 512
ADDP4
INDIRI4
LTI4 $79
LABELV $71
endproc CG_BuildSolidList 32 0
proc CG_ClipMoveToEntities 152 36
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 4
ADDRFP4 4
INDIRP4
ASGNP4
ADDRFP4 8
ADDRFP4 8
INDIRP4
ASGNP4
ADDRFP4 12
ADDRFP4 12
INDIRP4
ASGNP4
ADDRFP4 16
ADDRFP4 16
INDIRI4
ASGNI4
ADDRFP4 20
ADDRFP4 20
INDIRI4
ASGNI4
ADDRFP4 24
ADDRFP4 24
INDIRP4
ASGNP4
ADDRLP4 64
CNSTI4 0
ASGNI4
ADDRGP4 $93
JUMPV
LABELV $90
ADDRLP4 60
ADDRLP4 64
INDIRI4
CNSTI4 2
LSHI4
ADDRGP4 cg_solidEntities
ADDP4
INDIRP4
ASGNP4
ADDRLP4 0
ADDRLP4 60
INDIRP4
ASGNP4
ADDRLP4 0
INDIRP4
INDIRI4
ADDRFP4 16
INDIRI4
NEI4 $94
ADDRGP4 $91
JUMPV
LABELV $94
ADDRLP4 0
INDIRP4
CNSTI4 176
ADDP4
INDIRI4
CNSTI4 16777215
NEI4 $96
ADDRLP4 0
INDIRP4
CNSTI4 160
ADDP4
INDIRI4
ARGI4
ADDRLP4 132
ADDRGP4 trap_CM_InlineModel
CALLI4
ASGNI4
ADDRLP4 68
ADDRLP4 132
INDIRI4
ASGNI4
ADDRLP4 108
ADDRLP4 60
INDIRP4
CNSTI4 716
ADDP4
INDIRB
ASGNB 12
ADDRLP4 60
INDIRP4
CNSTI4 12
ADDP4
ARGP4
ADDRGP4 cg+107612
INDIRI4
ARGI4
ADDRLP4 96
ARGP4
ADDRGP4 BG_EvaluateTrajectory
CALLV
pop
ADDRGP4 $97
JUMPV
LABELV $96
ADDRLP4 132
ADDRLP4 0
INDIRP4
CNSTI4 176
ADDP4
ASGNP4
ADDRLP4 136
CNSTI4 255
ASGNI4
ADDRLP4 120
ADDRLP4 132
INDIRP4
INDIRI4
ADDRLP4 136
INDIRI4
BANDI4
ASGNI4
ADDRLP4 124
ADDRLP4 132
INDIRP4
INDIRI4
CNSTI4 8
RSHI4
ADDRLP4 136
INDIRI4
BANDI4
ASGNI4
ADDRLP4 128
ADDRLP4 132
INDIRP4
INDIRI4
CNSTI4 16
RSHI4
ADDRLP4 136
INDIRI4
BANDI4
CNSTI4 32
SUBI4
ASGNI4
ADDRLP4 140
ADDRLP4 120
INDIRI4
NEGI4
CVIF4 4
ASGNF4
ADDRLP4 72+4
ADDRLP4 140
INDIRF4
ASGNF4
ADDRLP4 72
ADDRLP4 140
INDIRF4
ASGNF4
ADDRLP4 144
ADDRLP4 120
INDIRI4
CVIF4 4
ASGNF4
ADDRLP4 84+4
ADDRLP4 144
INDIRF4
ASGNF4
ADDRLP4 84
ADDRLP4 144
INDIRF4
ASGNF4
ADDRLP4 72+8
ADDRLP4 124
INDIRI4
NEGI4
CVIF4 4
ASGNF4
ADDRLP4 84+8
ADDRLP4 128
INDIRI4
CVIF4 4
ASGNF4
ADDRLP4 72
ARGP4
ADDRLP4 84
ARGP4
ADDRLP4 148
ADDRGP4 trap_CM_TempBoxModel
CALLI4
ASGNI4
ADDRLP4 68
ADDRLP4 148
INDIRI4
ASGNI4
ADDRLP4 108
ADDRGP4 vec3_origin
INDIRB
ASGNB 12
ADDRLP4 96
ADDRLP4 60
INDIRP4
CNSTI4 704
ADDP4
INDIRB
ASGNB 12
LABELV $97
ADDRLP4 4
ARGP4
ADDRFP4 0
INDIRP4
ARGP4
ADDRFP4 12
INDIRP4
ARGP4
ADDRFP4 4
INDIRP4
ARGP4
ADDRFP4 8
INDIRP4
ARGP4
ADDRLP4 68
INDIRI4
ARGI4
ADDRFP4 20
INDIRI4
ARGI4
ADDRLP4 96
ARGP4
ADDRLP4 108
ARGP4
ADDRGP4 trap_CM_TransformedBoxTrace
CALLV
pop
ADDRLP4 4
INDIRI4
CNSTI4 0
NEI4 $106
ADDRLP4 4+8
INDIRF4
ADDRFP4 24
INDIRP4
CNSTI4 8
ADDP4
INDIRF4
GEF4 $103
LABELV $106
ADDRLP4 4+52
ADDRLP4 0
INDIRP4
INDIRI4
ASGNI4
ADDRFP4 24
INDIRP4
ADDRLP4 4
INDIRB
ASGNB 56
ADDRGP4 $104
JUMPV
LABELV $103
ADDRLP4 4+4
INDIRI4
CNSTI4 0
EQI4 $108
ADDRFP4 24
INDIRP4
CNSTI4 4
ADDP4
CNSTI4 1
ASGNI4
LABELV $108
LABELV $104
ADDRFP4 24
INDIRP4
INDIRI4
CNSTI4 0
EQI4 $111
ADDRGP4 $89
JUMPV
LABELV $111
LABELV $91
ADDRLP4 64
ADDRLP4 64
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $93
ADDRLP4 64
INDIRI4
ADDRGP4 cg_numSolidEntities
INDIRI4
LTI4 $90
LABELV $89
endproc CG_ClipMoveToEntities 152 36
export CG_Trace
proc CG_Trace 60 28
ADDRLP4 0
ARGP4
ADDRFP4 4
INDIRP4
ARGP4
ADDRFP4 16
INDIRP4
ARGP4
ADDRFP4 8
INDIRP4
ARGP4
ADDRFP4 12
INDIRP4
ARGP4
CNSTI4 0
ARGI4
ADDRFP4 24
INDIRI4
ARGI4
ADDRGP4 trap_CM_BoxTrace
CALLV
pop
ADDRLP4 0+8
INDIRF4
CNSTF4 1065353216
EQF4 $117
ADDRLP4 56
CNSTI4 1022
ASGNI4
ADDRGP4 $118
JUMPV
LABELV $117
ADDRLP4 56
CNSTI4 1023
ASGNI4
LABELV $118
ADDRLP4 0+52
ADDRLP4 56
INDIRI4
ASGNI4
ADDRFP4 4
INDIRP4
ARGP4
ADDRFP4 8
INDIRP4
ARGP4
ADDRFP4 12
INDIRP4
ARGP4
ADDRFP4 16
INDIRP4
ARGP4
ADDRFP4 20
INDIRI4
ARGI4
ADDRFP4 24
INDIRI4
ARGI4
ADDRLP4 0
ARGP4
ADDRGP4 CG_ClipMoveToEntities
CALLV
pop
ADDRFP4 0
INDIRP4
ADDRLP4 0
INDIRB
ASGNB 56
LABELV $113
endproc CG_Trace 60 28
export CG_PointContents
proc CG_PointContents 36 16
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 4
ADDRFP4 4
INDIRI4
ASGNI4
ADDRFP4 0
INDIRP4
ARGP4
CNSTI4 0
ARGI4
ADDRLP4 20
ADDRGP4 trap_CM_PointContents
CALLI4
ASGNI4
ADDRLP4 16
ADDRLP4 20
INDIRI4
ASGNI4
ADDRLP4 4
CNSTI4 0
ASGNI4
ADDRGP4 $123
JUMPV
LABELV $120
ADDRLP4 12
ADDRLP4 4
INDIRI4
CNSTI4 2
LSHI4
ADDRGP4 cg_solidEntities
ADDP4
INDIRP4
ASGNP4
ADDRLP4 0
ADDRLP4 12
INDIRP4
ASGNP4
ADDRLP4 0
INDIRP4
INDIRI4
ADDRFP4 4
INDIRI4
NEI4 $124
ADDRGP4 $121
JUMPV
LABELV $124
ADDRLP4 0
INDIRP4
CNSTI4 176
ADDP4
INDIRI4
CNSTI4 16777215
EQI4 $126
ADDRGP4 $121
JUMPV
LABELV $126
ADDRLP4 0
INDIRP4
CNSTI4 160
ADDP4
INDIRI4
ARGI4
ADDRLP4 24
ADDRGP4 trap_CM_InlineModel
CALLI4
ASGNI4
ADDRLP4 8
ADDRLP4 24
INDIRI4
ASGNI4
ADDRLP4 8
INDIRI4
CNSTI4 0
NEI4 $128
ADDRGP4 $121
JUMPV
LABELV $128
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 8
INDIRI4
ARGI4
ADDRLP4 0
INDIRP4
CNSTI4 92
ADDP4
ARGP4
ADDRLP4 0
INDIRP4
CNSTI4 116
ADDP4
ARGP4
ADDRLP4 32
ADDRGP4 trap_CM_TransformedPointContents
CALLI4
ASGNI4
ADDRLP4 16
ADDRLP4 16
INDIRI4
ADDRLP4 32
INDIRI4
BORI4
ASGNI4
LABELV $121
ADDRLP4 4
ADDRLP4 4
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $123
ADDRLP4 4
INDIRI4
ADDRGP4 cg_numSolidEntities
INDIRI4
LTI4 $120
ADDRLP4 16
INDIRI4
RETI4
LABELV $119
endproc CG_PointContents 36 16
proc CG_InterpolatePlayerState 76 12
ADDRFP4 0
ADDRFP4 0
INDIRI4
ASGNI4
ADDRLP4 12
ADDRGP4 cg+107636
ASGNP4
ADDRLP4 4
ADDRGP4 cg+36
INDIRP4
ASGNP4
ADDRLP4 8
ADDRGP4 cg+40
INDIRP4
ASGNP4
ADDRLP4 12
INDIRP4
ADDRGP4 cg+36
INDIRP4
CNSTI4 44
ADDP4
INDIRB
ASGNB 468
ADDRFP4 0
INDIRI4
CNSTI4 0
EQI4 $135
ADDRLP4 48
ADDRGP4 trap_GetCurrentCmdNumber
CALLI4
ASGNI4
ADDRLP4 44
ADDRLP4 48
INDIRI4
ASGNI4
ADDRLP4 44
INDIRI4
ARGI4
ADDRLP4 20
ARGP4
ADDRGP4 trap_GetUserCmd
CALLI4
pop
ADDRLP4 12
INDIRP4
ARGP4
ADDRLP4 20
ARGP4
ADDRGP4 PM_UpdateViewAngles
CALLV
pop
LABELV $135
ADDRGP4 cg+107596
INDIRI4
CNSTI4 0
EQI4 $137
ADDRGP4 $130
JUMPV
LABELV $137
ADDRLP4 8
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $142
ADDRLP4 24
CNSTI4 8
ASGNI4
ADDRLP4 8
INDIRP4
ADDRLP4 24
INDIRI4
ADDP4
INDIRI4
ADDRLP4 4
INDIRP4
ADDRLP4 24
INDIRI4
ADDP4
INDIRI4
GTI4 $140
LABELV $142
ADDRGP4 $130
JUMPV
LABELV $140
ADDRLP4 32
CNSTI4 8
ASGNI4
ADDRLP4 36
ADDRLP4 4
INDIRP4
ADDRLP4 32
INDIRI4
ADDP4
INDIRI4
ASGNI4
ADDRLP4 16
ADDRGP4 cg+107604
INDIRI4
ADDRLP4 36
INDIRI4
SUBI4
CVIF4 4
ADDRLP4 8
INDIRP4
ADDRLP4 32
INDIRI4
ADDP4
INDIRI4
ADDRLP4 36
INDIRI4
SUBI4
CVIF4 4
DIVF4
ASGNF4
ADDRLP4 44
CNSTI4 52
ASGNI4
ADDRLP4 0
ADDRLP4 8
INDIRP4
ADDRLP4 44
INDIRI4
ADDP4
INDIRI4
ASGNI4
ADDRLP4 0
INDIRI4
ADDRLP4 4
INDIRP4
ADDRLP4 44
INDIRI4
ADDP4
INDIRI4
GEI4 $144
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 256
ADDI4
ASGNI4
LABELV $144
ADDRLP4 48
ADDRLP4 4
INDIRP4
CNSTI4 52
ADDP4
INDIRI4
ASGNI4
ADDRLP4 12
INDIRP4
CNSTI4 8
ADDP4
ADDRLP4 48
INDIRI4
CVIF4 4
ADDRLP4 16
INDIRF4
ADDRLP4 0
INDIRI4
ADDRLP4 48
INDIRI4
SUBI4
CVIF4 4
MULF4
ADDF4
CVFI4 4
ASGNI4
ADDRLP4 0
CNSTI4 0
ASGNI4
LABELV $146
ADDRLP4 52
ADDRLP4 0
INDIRI4
CNSTI4 2
LSHI4
ASGNI4
ADDRLP4 56
CNSTI4 64
ASGNI4
ADDRLP4 60
ADDRLP4 52
INDIRI4
ADDRLP4 4
INDIRP4
ADDRLP4 56
INDIRI4
ADDP4
ADDP4
INDIRF4
ASGNF4
ADDRLP4 52
INDIRI4
ADDRLP4 12
INDIRP4
CNSTI4 20
ADDP4
ADDP4
ADDRLP4 60
INDIRF4
ADDRLP4 16
INDIRF4
ADDRLP4 52
INDIRI4
ADDRLP4 8
INDIRP4
ADDRLP4 56
INDIRI4
ADDP4
ADDP4
INDIRF4
ADDRLP4 60
INDIRF4
SUBF4
MULF4
ADDF4
ASGNF4
ADDRFP4 0
INDIRI4
CNSTI4 0
NEI4 $150
ADDRLP4 64
ADDRLP4 0
INDIRI4
CNSTI4 2
LSHI4
ASGNI4
ADDRLP4 68
CNSTI4 196
ASGNI4
ADDRLP4 64
INDIRI4
ADDRLP4 4
INDIRP4
ADDRLP4 68
INDIRI4
ADDP4
ADDP4
INDIRF4
ARGF4
ADDRLP4 64
INDIRI4
ADDRLP4 8
INDIRP4
ADDRLP4 68
INDIRI4
ADDP4
ADDP4
INDIRF4
ARGF4
ADDRLP4 16
INDIRF4
ARGF4
ADDRLP4 72
ADDRGP4 LerpAngle
CALLF4
ASGNF4
ADDRLP4 64
INDIRI4
ADDRLP4 12
INDIRP4
CNSTI4 152
ADDP4
ADDP4
ADDRLP4 72
INDIRF4
ASGNF4
LABELV $150
ADDRLP4 64
ADDRLP4 0
INDIRI4
CNSTI4 2
LSHI4
ASGNI4
ADDRLP4 68
CNSTI4 76
ASGNI4
ADDRLP4 72
ADDRLP4 64
INDIRI4
ADDRLP4 4
INDIRP4
ADDRLP4 68
INDIRI4
ADDP4
ADDP4
INDIRF4
ASGNF4
ADDRLP4 64
INDIRI4
ADDRLP4 12
INDIRP4
CNSTI4 32
ADDP4
ADDP4
ADDRLP4 72
INDIRF4
ADDRLP4 16
INDIRF4
ADDRLP4 64
INDIRI4
ADDRLP4 8
INDIRP4
ADDRLP4 68
INDIRI4
ADDP4
ADDP4
INDIRF4
ADDRLP4 72
INDIRF4
SUBF4
MULF4
ADDF4
ASGNF4
LABELV $147
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
ADDRLP4 0
INDIRI4
CNSTI4 3
LTI4 $146
LABELV $130
endproc CG_InterpolatePlayerState 76 12
proc CG_TouchItem 24 12
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRGP4 cg_predictItems+12
INDIRI4
CNSTI4 0
NEI4 $153
ADDRGP4 $152
JUMPV
LABELV $153
ADDRGP4 cg+107636
ARGP4
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 cg+107604
INDIRI4
ARGI4
ADDRLP4 4
ADDRGP4 BG_PlayerTouchesItem
CALLI4
ASGNI4
ADDRLP4 4
INDIRI4
CNSTI4 0
NEI4 $156
ADDRGP4 $152
JUMPV
LABELV $156
ADDRFP4 0
INDIRP4
CNSTI4 444
ADDP4
INDIRI4
ADDRGP4 cg+107604
INDIRI4
NEI4 $160
ADDRGP4 $152
JUMPV
LABELV $160
ADDRGP4 cgs+31456
INDIRI4
ARGI4
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 cg+107636
ARGP4
ADDRLP4 8
ADDRGP4 BG_CanItemBeGrabbed
CALLI4
ASGNI4
ADDRLP4 8
INDIRI4
CNSTI4 0
NEI4 $163
ADDRGP4 $152
JUMPV
LABELV $163
ADDRLP4 12
ADDRFP4 0
INDIRP4
CNSTI4 160
ADDP4
ASGNP4
ADDRLP4 0
CNSTI4 52
ADDRLP4 12
INDIRP4
INDIRI4
MULI4
ADDRGP4 bg_itemlist
ADDP4
ASGNP4
CNSTI4 19
ARGI4
ADDRLP4 12
INDIRP4
INDIRI4
ARGI4
ADDRGP4 cg+107636
ARGP4
ADDRGP4 BG_AddPredictableEventToPlayerstate
CALLV
pop
ADDRLP4 16
ADDRFP4 0
INDIRP4
CNSTI4 8
ADDP4
ASGNP4
ADDRLP4 16
INDIRP4
ADDRLP4 16
INDIRP4
INDIRI4
CNSTI4 128
BORI4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 444
ADDP4
ADDRGP4 cg+107604
INDIRI4
ASGNI4
ADDRLP4 0
INDIRP4
CNSTI4 36
ADDP4
INDIRI4
CNSTI4 1
NEI4 $169
ADDRLP4 20
ADDRGP4 cg+107636+184+8
ASGNP4
ADDRLP4 20
INDIRP4
ADDRLP4 20
INDIRP4
INDIRI4
CNSTI4 1
ADDRLP4 0
INDIRP4
CNSTI4 40
ADDP4
INDIRI4
LSHI4
BORI4
ASGNI4
ADDRLP4 0
INDIRP4
CNSTI4 40
ADDP4
INDIRI4
CNSTI4 2
LSHI4
ADDRGP4 cg+107636+376
ADDP4
INDIRI4
CNSTI4 0
NEI4 $174
ADDRLP4 0
INDIRP4
CNSTI4 40
ADDP4
INDIRI4
CNSTI4 2
LSHI4
ADDRGP4 cg+107636+376
ADDP4
CNSTI4 1
ASGNI4
LABELV $174
LABELV $169
LABELV $152
endproc CG_TouchItem 24 12
proc CG_TouchTriggerPrediction 88 28
ADDRGP4 cg+107636+184
INDIRI4
CNSTI4 0
GTI4 $181
ADDRGP4 $180
JUMPV
LABELV $181
ADDRGP4 cg+107636+4
INDIRI4
CNSTI4 2
NEI4 $188
ADDRLP4 76
CNSTI4 1
ASGNI4
ADDRGP4 $189
JUMPV
LABELV $188
ADDRLP4 76
CNSTI4 0
ASGNI4
LABELV $189
ADDRLP4 72
ADDRLP4 76
INDIRI4
ASGNI4
ADDRLP4 80
CNSTI4 0
ASGNI4
ADDRGP4 cg+107636+4
INDIRI4
ADDRLP4 80
INDIRI4
EQI4 $190
ADDRLP4 72
INDIRI4
ADDRLP4 80
INDIRI4
NEI4 $190
ADDRGP4 $180
JUMPV
LABELV $190
ADDRLP4 4
CNSTI4 0
ASGNI4
ADDRGP4 $197
JUMPV
LABELV $194
ADDRLP4 12
ADDRLP4 4
INDIRI4
CNSTI4 2
LSHI4
ADDRGP4 cg_triggerEntities
ADDP4
INDIRP4
ASGNP4
ADDRLP4 0
ADDRLP4 12
INDIRP4
ASGNP4
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
CNSTI4 2
NEI4 $198
ADDRLP4 72
INDIRI4
CNSTI4 0
NEI4 $198
ADDRLP4 12
INDIRP4
ARGP4
ADDRGP4 CG_TouchItem
CALLV
pop
ADDRGP4 $195
JUMPV
LABELV $198
ADDRLP4 0
INDIRP4
CNSTI4 176
ADDP4
INDIRI4
CNSTI4 16777215
EQI4 $200
ADDRGP4 $195
JUMPV
LABELV $200
ADDRLP4 0
INDIRP4
CNSTI4 160
ADDP4
INDIRI4
ARGI4
ADDRLP4 84
ADDRGP4 trap_CM_InlineModel
CALLI4
ASGNI4
ADDRLP4 8
ADDRLP4 84
INDIRI4
ASGNI4
ADDRLP4 8
INDIRI4
CNSTI4 0
NEI4 $202
ADDRGP4 $195
JUMPV
LABELV $202
ADDRLP4 16
ARGP4
ADDRGP4 cg+107636+20
ARGP4
ADDRGP4 cg+107636+20
ARGP4
ADDRGP4 cg_pmove+180
ARGP4
ADDRGP4 cg_pmove+192
ARGP4
ADDRLP4 8
INDIRI4
ARGI4
CNSTI4 -1
ARGI4
ADDRGP4 trap_CM_BoxTrace
CALLV
pop
ADDRLP4 16+4
INDIRI4
CNSTI4 0
NEI4 $210
ADDRGP4 $195
JUMPV
LABELV $210
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
CNSTI4 9
NEI4 $213
ADDRGP4 cg+107632
CNSTI4 1
ASGNI4
ADDRGP4 $214
JUMPV
LABELV $213
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
CNSTI4 8
NEI4 $216
ADDRGP4 cg+107636
ARGP4
ADDRLP4 0
INDIRP4
ARGP4
ADDRGP4 BG_TouchJumpPad
CALLV
pop
LABELV $216
LABELV $214
LABELV $195
ADDRLP4 4
ADDRLP4 4
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $197
ADDRLP4 4
INDIRI4
ADDRGP4 cg_numTriggerEntities
INDIRI4
LTI4 $194
ADDRGP4 cg+107636+460
INDIRI4
ADDRGP4 cg+107636+456
INDIRI4
EQI4 $219
ADDRGP4 cg+107636+460
CNSTI4 0
ASGNI4
ADDRGP4 cg+107636+448
CNSTI4 0
ASGNI4
LABELV $219
LABELV $180
endproc CG_TouchTriggerPrediction 88 28
export CG_PredictPlayerState
proc CG_PredictPlayerState 592 20
ADDRGP4 cg+107632
CNSTI4 0
ASGNI4
ADDRGP4 cg+108832
INDIRI4
CNSTI4 0
NEI4 $231
ADDRGP4 cg+108832
CNSTI4 1
ASGNI4
ADDRGP4 cg+107636
ADDRGP4 cg+36
INDIRP4
CNSTI4 44
ADDP4
INDIRB
ASGNB 468
LABELV $231
ADDRLP4 528
CNSTI4 0
ASGNI4
ADDRGP4 cg+8
INDIRI4
ADDRLP4 528
INDIRI4
NEI4 $241
ADDRGP4 cg+36
INDIRP4
CNSTI4 56
ADDP4
INDIRI4
CNSTI4 4096
BANDI4
ADDRLP4 528
INDIRI4
EQI4 $237
LABELV $241
CNSTI4 0
ARGI4
ADDRGP4 CG_InterpolatePlayerState
CALLV
pop
ADDRGP4 $229
JUMPV
LABELV $237
ADDRLP4 532
CNSTI4 0
ASGNI4
ADDRGP4 cg_nopredict+12
INDIRI4
ADDRLP4 532
INDIRI4
NEI4 $246
ADDRGP4 cg_synchronousClients+12
INDIRI4
ADDRLP4 532
INDIRI4
EQI4 $242
LABELV $246
CNSTI4 1
ARGI4
ADDRGP4 CG_InterpolatePlayerState
CALLV
pop
ADDRGP4 $229
JUMPV
LABELV $242
ADDRGP4 cg_pmove
ADDRGP4 cg+107636
ASGNP4
ADDRGP4 cg_pmove+224
ADDRGP4 CG_Trace
ASGNP4
ADDRGP4 cg_pmove+228
ADDRGP4 CG_PointContents
ASGNP4
ADDRGP4 cg_pmove
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
CNSTI4 3
NEI4 $250
ADDRGP4 cg_pmove+28
CNSTI4 65537
ASGNI4
ADDRGP4 $251
JUMPV
LABELV $250
ADDRGP4 cg_pmove+28
CNSTI4 33619969
ASGNI4
LABELV $251
ADDRGP4 cg+36
INDIRP4
CNSTI4 304
ADDP4
INDIRI4
CNSTI4 3
NEI4 $254
ADDRLP4 536
ADDRGP4 cg_pmove+28
ASGNP4
ADDRLP4 536
INDIRP4
ADDRLP4 536
INDIRP4
INDIRI4
CNSTI4 -33554433
BANDI4
ASGNI4
LABELV $254
ADDRGP4 cgs+31460
INDIRI4
CNSTI4 32
BANDI4
CNSTI4 0
LEI4 $261
ADDRLP4 536
CNSTI4 1
ASGNI4
ADDRGP4 $262
JUMPV
LABELV $261
ADDRLP4 536
CNSTI4 0
ASGNI4
LABELV $262
ADDRGP4 cg_pmove+36
ADDRLP4 536
INDIRI4
ASGNI4
ADDRLP4 4
ADDRGP4 cg+107636
INDIRB
ASGNB 468
ADDRLP4 540
ADDRGP4 trap_GetCurrentCmdNumber
CALLI4
ASGNI4
ADDRLP4 472
ADDRLP4 540
INDIRI4
ASGNI4
ADDRLP4 0
ADDRLP4 472
INDIRI4
CNSTI4 64
SUBI4
CNSTI4 1
ADDI4
ASGNI4
ADDRLP4 0
INDIRI4
ARGI4
ADDRLP4 504
ARGP4
ADDRGP4 trap_GetUserCmd
CALLI4
pop
ADDRLP4 544
ADDRLP4 504
INDIRI4
ASGNI4
ADDRLP4 544
INDIRI4
ADDRGP4 cg+36
INDIRP4
CNSTI4 44
ADDP4
INDIRI4
LEI4 $264
ADDRLP4 544
INDIRI4
ADDRGP4 cg+107604
INDIRI4
GEI4 $264
ADDRGP4 cg_showmiss+12
INDIRI4
CNSTI4 0
EQI4 $229
ADDRGP4 $271
ARGP4
ADDRGP4 CG_Printf
CALLV
pop
ADDRGP4 $229
JUMPV
LABELV $264
ADDRLP4 472
INDIRI4
ARGI4
ADDRLP4 480
ARGP4
ADDRGP4 trap_GetUserCmd
CALLI4
pop
ADDRGP4 cg+40
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $272
ADDRLP4 548
CNSTI4 0
ASGNI4
ADDRGP4 cg+107596
INDIRI4
ADDRLP4 548
INDIRI4
NEI4 $272
ADDRGP4 cg+107592
INDIRI4
ADDRLP4 548
INDIRI4
NEI4 $272
ADDRGP4 cg+107636
ADDRGP4 cg+40
INDIRP4
CNSTI4 44
ADDP4
INDIRB
ASGNB 468
ADDRGP4 cg+107612
ADDRGP4 cg+40
INDIRP4
CNSTI4 8
ADDP4
INDIRI4
ASGNI4
ADDRGP4 $273
JUMPV
LABELV $272
ADDRGP4 cg+107636
ADDRGP4 cg+36
INDIRP4
CNSTI4 44
ADDP4
INDIRB
ASGNB 468
ADDRGP4 cg+107612
ADDRGP4 cg+36
INDIRP4
CNSTI4 8
ADDP4
INDIRI4
ASGNI4
LABELV $273
ADDRGP4 pmove_msec+12
INDIRI4
CNSTI4 8
GEI4 $285
ADDRGP4 $288
ARGP4
ADDRGP4 $289
ARGP4
ADDRGP4 trap_Cvar_Set
CALLV
pop
ADDRGP4 $286
JUMPV
LABELV $285
ADDRGP4 pmove_msec+12
INDIRI4
CNSTI4 33
LEI4 $290
ADDRGP4 $288
ARGP4
ADDRGP4 $293
ARGP4
ADDRGP4 trap_Cvar_Set
CALLV
pop
LABELV $290
LABELV $286
ADDRGP4 cg_pmove+216
ADDRGP4 pmove_fixed+12
INDIRI4
ASGNI4
ADDRGP4 cg_pmove+220
ADDRGP4 pmove_msec+12
INDIRI4
ASGNI4
ADDRLP4 476
CNSTI4 0
ASGNI4
ADDRLP4 0
ADDRLP4 472
INDIRI4
CNSTI4 64
SUBI4
CNSTI4 1
ADDI4
ASGNI4
ADDRGP4 $301
JUMPV
LABELV $298
ADDRLP4 0
INDIRI4
ARGI4
ADDRGP4 cg_pmove+4
ARGP4
ADDRGP4 trap_GetUserCmd
CALLI4
pop
ADDRGP4 cg_pmove+216
INDIRI4
CNSTI4 0
EQI4 $303
ADDRGP4 cg_pmove
INDIRP4
ARGP4
ADDRGP4 cg_pmove+4
ARGP4
ADDRGP4 PM_UpdateViewAngles
CALLV
pop
LABELV $303
ADDRGP4 cg_pmove+4
INDIRI4
ADDRGP4 cg+107636
INDIRI4
GTI4 $307
ADDRGP4 $299
JUMPV
LABELV $307
ADDRGP4 cg_pmove+4
INDIRI4
ADDRLP4 480
INDIRI4
LEI4 $311
ADDRGP4 $299
JUMPV
LABELV $311
ADDRGP4 cg+107636
INDIRI4
ADDRLP4 4
INDIRI4
NEI4 $314
ADDRGP4 cg+107592
INDIRI4
CNSTI4 0
EQI4 $317
ADDRLP4 568
CNSTF4 0
ASGNF4
ADDRGP4 cg+108840+8
ADDRLP4 568
INDIRF4
ASGNF4
ADDRGP4 cg+108840+4
ADDRLP4 568
INDIRF4
ASGNF4
ADDRGP4 cg+108840
ADDRLP4 568
INDIRF4
ASGNF4
ADDRGP4 cg_showmiss+12
INDIRI4
CNSTI4 0
EQI4 $325
ADDRGP4 $328
ARGP4
ADDRGP4 CG_Printf
CALLV
pop
LABELV $325
ADDRGP4 cg+107592
CNSTI4 0
ASGNI4
ADDRGP4 $318
JUMPV
LABELV $317
ADDRGP4 cg+107636+20
ARGP4
ADDRGP4 cg+107636+68
INDIRI4
ARGI4
ADDRGP4 cg+107612
INDIRI4
ARGI4
ADDRGP4 cg+107608
INDIRI4
ARGI4
ADDRLP4 568
ARGP4
ADDRGP4 CG_AdjustPositionForMover
CALLV
pop
ADDRGP4 cg_showmiss+12
INDIRI4
CNSTI4 0
EQI4 $336
ADDRLP4 4+20
ARGP4
ADDRLP4 568
ARGP4
ADDRLP4 580
ADDRGP4 VectorCompare
CALLI4
ASGNI4
ADDRLP4 580
INDIRI4
CNSTI4 0
NEI4 $339
ADDRGP4 $342
ARGP4
ADDRGP4 CG_Printf
CALLV
pop
LABELV $339
LABELV $336
ADDRLP4 552
ADDRLP4 4+20
INDIRF4
ADDRLP4 568
INDIRF4
SUBF4
ASGNF4
ADDRLP4 552+4
ADDRLP4 4+20+4
INDIRF4
ADDRLP4 568+4
INDIRF4
SUBF4
ASGNF4
ADDRLP4 552+8
ADDRLP4 4+20+8
INDIRF4
ADDRLP4 568+8
INDIRF4
SUBF4
ASGNF4
ADDRLP4 552
ARGP4
ADDRLP4 580
ADDRGP4 VectorLength
CALLF4
ASGNF4
ADDRLP4 564
ADDRLP4 580
INDIRF4
ASGNF4
ADDRLP4 564
INDIRF4
CNSTF4 1036831949
LEF4 $352
ADDRGP4 cg_showmiss+12
INDIRI4
CNSTI4 0
EQI4 $354
ADDRGP4 $357
ARGP4
ADDRLP4 564
INDIRF4
ARGF4
ADDRGP4 CG_Printf
CALLV
pop
LABELV $354
ADDRGP4 cg_errorDecay+12
INDIRI4
CNSTI4 0
EQI4 $358
ADDRLP4 588
ADDRGP4 cg+107604
INDIRI4
ADDRGP4 cg+108836
INDIRI4
SUBI4
ASGNI4
ADDRLP4 584
ADDRGP4 cg_errorDecay+8
INDIRF4
ADDRLP4 588
INDIRI4
CVIF4 4
SUBF4
ADDRGP4 cg_errorDecay+8
INDIRF4
DIVF4
ASGNF4
ADDRLP4 584
INDIRF4
CNSTF4 0
GEF4 $365
ADDRLP4 584
CNSTF4 0
ASGNF4
LABELV $365
ADDRLP4 584
INDIRF4
CNSTF4 0
LEF4 $367
ADDRGP4 cg_showmiss+12
INDIRI4
CNSTI4 0
EQI4 $367
ADDRGP4 $370
ARGP4
ADDRLP4 584
INDIRF4
ARGF4
ADDRGP4 CG_Printf
CALLV
pop
LABELV $367
ADDRGP4 cg+108840
ADDRGP4 cg+108840
INDIRF4
ADDRLP4 584
INDIRF4
MULF4
ASGNF4
ADDRGP4 cg+108840+4
ADDRGP4 cg+108840+4
INDIRF4
ADDRLP4 584
INDIRF4
MULF4
ASGNF4
ADDRGP4 cg+108840+8
ADDRGP4 cg+108840+8
INDIRF4
ADDRLP4 584
INDIRF4
MULF4
ASGNF4
ADDRGP4 $359
JUMPV
LABELV $358
ADDRLP4 584
CNSTF4 0
ASGNF4
ADDRGP4 cg+108840+8
ADDRLP4 584
INDIRF4
ASGNF4
ADDRGP4 cg+108840+4
ADDRLP4 584
INDIRF4
ASGNF4
ADDRGP4 cg+108840
ADDRLP4 584
INDIRF4
ASGNF4
LABELV $359
ADDRGP4 cg+108840
ADDRLP4 552
INDIRF4
ADDRGP4 cg+108840
INDIRF4
ADDF4
ASGNF4
ADDRGP4 cg+108840+4
ADDRLP4 552+4
INDIRF4
ADDRGP4 cg+108840+4
INDIRF4
ADDF4
ASGNF4
ADDRGP4 cg+108840+8
ADDRLP4 552+8
INDIRF4
ADDRGP4 cg+108840+8
INDIRF4
ADDF4
ASGNF4
ADDRGP4 cg+108836
ADDRGP4 cg+107608
INDIRI4
ASGNI4
LABELV $352
LABELV $318
LABELV $314
ADDRGP4 cg_pmove+40
CNSTI4 0
ASGNI4
ADDRGP4 cg_pmove+216
INDIRI4
CNSTI4 0
EQI4 $401
ADDRGP4 cg_pmove+4
ADDRGP4 cg_pmove+4
INDIRI4
ADDRGP4 pmove_msec+12
INDIRI4
ADDI4
CNSTI4 1
SUBI4
ADDRGP4 pmove_msec+12
INDIRI4
DIVI4
ADDRGP4 pmove_msec+12
INDIRI4
MULI4
ASGNI4
LABELV $401
ADDRGP4 cg_pmove
ARGP4
ADDRGP4 Pmove
CALLV
pop
ADDRLP4 476
CNSTI4 1
ASGNI4
ADDRGP4 CG_TouchTriggerPrediction
CALLV
pop
LABELV $299
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $301
ADDRLP4 0
INDIRI4
ADDRLP4 472
INDIRI4
LEI4 $298
ADDRGP4 cg_showmiss+12
INDIRI4
CNSTI4 1
LEI4 $409
ADDRGP4 $412
ARGP4
ADDRGP4 cg_pmove+4
INDIRI4
ARGI4
ADDRGP4 cg+107604
INDIRI4
ARGI4
ADDRGP4 CG_Printf
CALLV
pop
LABELV $409
ADDRLP4 476
INDIRI4
CNSTI4 0
NEI4 $415
ADDRGP4 cg_showmiss+12
INDIRI4
CNSTI4 0
EQI4 $229
ADDRGP4 $420
ARGP4
ADDRGP4 CG_Printf
CALLV
pop
ADDRGP4 $229
JUMPV
LABELV $415
ADDRGP4 cg+107636+20
ARGP4
ADDRGP4 cg+107636+68
INDIRI4
ARGI4
ADDRGP4 cg+107612
INDIRI4
ARGI4
ADDRGP4 cg+107604
INDIRI4
ARGI4
ADDRGP4 cg+107636+20
ARGP4
ADDRGP4 CG_AdjustPositionForMover
CALLV
pop
ADDRGP4 cg_showmiss+12
INDIRI4
CNSTI4 0
EQI4 $429
ADDRGP4 cg+107636+108
INDIRI4
ADDRLP4 4+108
INDIRI4
CNSTI4 2
ADDI4
LEI4 $432
ADDRGP4 $437
ARGP4
ADDRGP4 CG_Printf
CALLV
pop
LABELV $432
LABELV $429
ADDRGP4 cg+107636
ARGP4
ADDRLP4 4
ARGP4
ADDRGP4 CG_TransitionPlayerState
CALLV
pop
ADDRGP4 cg_showmiss+12
INDIRI4
CNSTI4 0
EQI4 $439
ADDRGP4 cg+108852
INDIRI4
ADDRGP4 cg+107636+108
INDIRI4
LEI4 $442
ADDRGP4 $447
ARGP4
ADDRGP4 CG_Printf
CALLV
pop
ADDRGP4 cg+108852
ADDRGP4 cg+107636+108
INDIRI4
ASGNI4
LABELV $442
LABELV $439
LABELV $229
endproc CG_PredictPlayerState 592 20
bss
align 4
LABELV cg_triggerEntities
skip 1024
align 4
LABELV cg_numTriggerEntities
skip 4
align 4
LABELV cg_solidEntities
skip 1024
align 4
LABELV cg_numSolidEntities
skip 4
align 4
LABELV cg_pmove
skip 232
import CG_NewParticleArea
import initparticles
import CG_ParticleExplosion
import CG_ParticleMisc
import CG_ParticleDust
import CG_ParticleSparks
import CG_ParticleBulletDebris
import CG_ParticleSnowFlurry
import CG_AddParticleShrapnel
import CG_ParticleSmoke
import CG_ParticleSnow
import CG_AddParticles
import CG_ClearParticles
import trap_GetEntityToken
import trap_getCameraInfo
import trap_startCamera
import trap_loadCamera
import trap_SnapVector
import trap_CIN_SetExtents
import trap_CIN_DrawCinematic
import trap_CIN_RunCinematic
import trap_CIN_StopCinematic
import trap_CIN_PlayCinematic
import trap_Key_GetKey
import trap_Key_SetCatcher
import trap_Key_GetCatcher
import trap_Key_IsDown
import trap_R_RegisterFont
import trap_MemoryRemaining
import testPrintFloat
import testPrintInt
import trap_SetUserCmdValue
import trap_GetUserCmd
import trap_GetCurrentCmdNumber
import trap_GetServerCommand
import trap_GetSnapshot
import trap_GetCurrentSnapshotNumber
import trap_GetGameState
import trap_GetGlconfig
import trap_R_RemapShader
import trap_R_LerpTag
import trap_R_ModelBounds
import trap_R_DrawStretchPic
import trap_R_SetColor
import trap_R_RenderScene
import trap_R_LightForPoint
import trap_R_AddLightToScene
import trap_R_AddPolysToScene
import trap_R_AddPolyToScene
import trap_R_AddRefEntityToScene
import trap_R_ClearScene
import trap_R_RegisterShaderNoMip
import trap_R_RegisterShader
import trap_R_RegisterSkin
import trap_R_RegisterModel
import trap_R_LoadWorldMap
import trap_S_StopBackgroundTrack
import trap_S_StartBackgroundTrack
import trap_S_RegisterSound
import trap_S_Respatialize
import trap_S_UpdateEntityPosition
import trap_S_AddRealLoopingSound
import trap_S_AddLoopingSound
import trap_S_ClearLoopingSounds
import trap_S_StartLocalSound
import trap_S_StopLoopingSound
import trap_S_StartSound
import trap_CM_MarkFragments
import trap_CM_TransformedBoxTrace
import trap_CM_BoxTrace
import trap_CM_TransformedPointContents
import trap_CM_PointContents
import trap_CM_TempBoxModel
import trap_CM_InlineModel
import trap_CM_NumInlineModels
import trap_CM_LoadMap
import trap_UpdateScreen
import trap_SendClientCommand
import trap_AddCommand
import trap_SendConsoleCommand
import trap_FS_Seek
import trap_FS_FCloseFile
import trap_FS_Write
import trap_FS_Read
import trap_FS_FOpenFile
import trap_Args
import trap_Argv
import trap_Argc
import trap_Cvar_VariableStringBuffer
import trap_Cvar_Set
import trap_Cvar_Update
import trap_Cvar_Register
import trap_Milliseconds
import trap_Error
import trap_Print
import CG_CheckChangedPredictableEvents
import CG_TransitionPlayerState
import CG_Respawn
import CG_PlayBufferedVoiceChats
import CG_VoiceChatLocal
import CG_ShaderStateChanged
import CG_LoadVoiceChats
import CG_SetConfigValues
import CG_ParseServerinfo
import CG_ExecuteNewServerCommands
import CG_InitConsoleCommands
import CG_ConsoleCommand
import CG_DrawOldTourneyScoreboard
import CG_DrawOldScoreboard
import CG_DrawInformation
import CG_LoadingClient
import CG_LoadingItem
import CG_LoadingString
import CG_ProcessSnapshots
import CG_MakeExplosion
import CG_Bleed
import CG_BigExplode
import CG_GibPlayer
import CG_ScorePlum
import CG_LightningBoltBeam
import CG_InvulnerabilityJuiced
import CG_InvulnerabilityImpact
import CG_ObeliskPain
import CG_ObeliskExplode
import CG_KamikazeEffect
import CG_SpawnEffect
import CG_BubbleTrail
import CG_SmokePuff
import CG_AddLocalEntities
import CG_AllocLocalEntity
import CG_InitLocalEntities
import CG_ImpactMark
import CG_AddMarks
import CG_InitMarkPolys
import CG_OutOfAmmoChange
import CG_DrawWeaponSelect
import CG_AddPlayerWeapon
import CG_AddViewWeapon
import CG_GrappleTrail
import CG_RailTrail
import CG_Bullet
import CG_ShotgunFire
import CG_MissileHitPlayer
import CG_MissileHitWall
import CG_FireWeapon
import CG_RegisterItemVisuals
import CG_RegisterWeapon
import CG_Weapon_f
import CG_PrevWeapon_f
import CG_NextWeapon_f
import CG_PositionRotatedEntityOnTag
import CG_PositionEntityOnTag
import CG_AdjustPositionForMover
import CG_Beam
import CG_AddPacketEntities
import CG_SetEntitySoundPosition
import CG_PainEvent
import CG_EntityEvent
import CG_PlaceString
import CG_CheckEvents
import CG_LoadDeferredPlayers
import CG_CustomSound
import CG_NewClientInfo
import CG_AddRefEntityWithPowerups
import CG_ResetPlayerEntity
import CG_Player
import CG_StatusHandle
import CG_OtherTeamHasFlag
import CG_YourTeamHasFlag
import CG_GameTypeString
import CG_CheckOrderPending
import CG_Text_PaintChar
import CG_Draw3DModel
import CG_GetKillerText
import CG_GetGameStatusText
import CG_GetTeamColor
import CG_InitTeamChat
import CG_SetPrintString
import CG_ShowResponseHead
import CG_RunMenuScript
import CG_OwnerDrawVisible
import CG_GetValue
import CG_SelectNextPlayer
import CG_SelectPrevPlayer
import CG_Text_Height
import CG_Text_Width
import CG_Text_Paint
import CG_OwnerDraw
import CG_DrawTeamBackground
import CG_DrawFlagModel
import CG_DrawActive
import CG_DrawHead
import CG_CenterPrint
import CG_AddLagometerSnapshotInfo
import CG_AddLagometerFrameInfo
import teamChat2
import teamChat1
import systemChat
import drawTeamOverlayModificationCount
import numSortedTeamPlayers
import sortedTeamPlayers
import CG_DrawTopBottom
import CG_DrawSides
import CG_DrawRect
import UI_DrawProportionalString
import CG_GetColorForHealth
import CG_ColorForHealth
import CG_TileClear
import CG_TeamColor
import CG_FadeColor
import CG_DrawStrlen
import CG_DrawSmallStringColor
import CG_DrawSmallString
import CG_DrawBigStringColor
import CG_DrawBigString
import CG_DrawStringExt
import CG_DrawString
import CG_DrawPic
import CG_FillRect
import CG_AdjustFrom640
import CG_DrawActiveFrame
import CG_AddBufferedSound
import CG_ZoomUp_f
import CG_ZoomDown_f
import CG_TestModelPrevSkin_f
import CG_TestModelNextSkin_f
import CG_TestModelPrevFrame_f
import CG_TestModelNextFrame_f
import CG_TestGun_f
import CG_TestModel_f
import CG_BuildSpectatorString
import CG_GetSelectedScore
import CG_SetScoreSelection
import CG_RankRunFrame
import CG_EventHandling
import CG_MouseEvent
import CG_KeyEvent
import CG_LoadMenus
import CG_LastAttacker
import CG_CrosshairPlayer
import CG_UpdateCvars
import CG_StartMusic
import CG_Error
import CG_Printf
import CG_Argv
import CG_ConfigString
import cg_obeliskRespawnDelay
import cg_recordSPDemoName
import cg_recordSPDemo
import cg_singlePlayerActive
import cg_enableBreath
import cg_enableDust
import cg_singlePlayer
import cg_currentSelectedPlayerName
import cg_currentSelectedPlayer
import cg_blueTeamName
import cg_redTeamName
import cg_trueLightning
import cg_oldPlasma
import cg_oldRocket
import cg_oldRail
import cg_noProjectileTrail
import cg_noTaunt
import cg_bigFont
import cg_smallFont
import cg_cameraMode
import cg_timescale
import cg_timescaleFadeSpeed
import cg_timescaleFadeEnd
import cg_cameraOrbitDelay
import cg_cameraOrbit
import pmove_msec
import pmove_fixed
import cg_smoothClients
import cg_scorePlum
import cg_noVoiceText
import cg_noVoiceChats
import cg_teamChatsOnly
import cg_drawFriend
import cg_deferPlayers
import cg_predictItems
import cg_blood
import cg_paused
import cg_buildScript
import cg_forceModel
import cg_stats
import cg_teamChatHeight
import cg_teamChatTime
import cg_synchronousClients
import cg_drawAttacker
import cg_lagometer
import cg_thirdPerson
import cg_thirdPersonAngle
import cg_thirdPersonRange
import cg_zoomFov
import cg_fov
import cg_simpleItems
import cg_ignore
import cg_autoswitch
import cg_tracerLength
import cg_tracerWidth
import cg_tracerChance
import cg_viewsize
import cg_drawGun
import cg_gun_z
import cg_gun_y
import cg_gun_x
import cg_gun_frame
import cg_brassTime
import cg_addMarks
import cg_footsteps
import cg_showmiss
import cg_noPlayerAnims
import cg_nopredict
import cg_errorDecay
import cg_railTrailTime
import cg_debugEvents
import cg_debugPosition
import cg_debugAnim
import cg_animSpeed
import cg_draw2D
import cg_drawStatus
import cg_crosshairHealth
import cg_crosshairSize
import cg_crosshairY
import cg_crosshairX
import cg_teamOverlayUserinfo
import cg_drawTeamOverlay
import cg_drawRewards
import cg_drawCrosshairNames
import cg_drawCrosshair
import cg_drawAmmoWarning
import cg_drawIcons
import cg_draw3dIcons
import cg_drawSnapshot
import cg_drawFPS
import cg_drawTimer
import cg_gibs
import cg_shadows
import cg_swingSpeed
import cg_bobroll
import cg_bobpitch
import cg_bobup
import cg_runroll
import cg_runpitch
import cg_centertime
import cg_markPolys
import cg_items
import cg_weapons
import cg_entities
import cg
import cgs
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
LABELV $447
byte 1 87
byte 1 65
byte 1 82
byte 1 78
byte 1 73
byte 1 78
byte 1 71
byte 1 58
byte 1 32
byte 1 100
byte 1 111
byte 1 117
byte 1 98
byte 1 108
byte 1 101
byte 1 32
byte 1 101
byte 1 118
byte 1 101
byte 1 110
byte 1 116
byte 1 10
byte 1 0
align 1
LABELV $437
byte 1 87
byte 1 65
byte 1 82
byte 1 78
byte 1 73
byte 1 78
byte 1 71
byte 1 58
byte 1 32
byte 1 100
byte 1 114
byte 1 111
byte 1 112
byte 1 112
byte 1 101
byte 1 100
byte 1 32
byte 1 101
byte 1 118
byte 1 101
byte 1 110
byte 1 116
byte 1 10
byte 1 0
align 1
LABELV $420
byte 1 110
byte 1 111
byte 1 116
byte 1 32
byte 1 109
byte 1 111
byte 1 118
byte 1 101
byte 1 100
byte 1 10
byte 1 0
align 1
LABELV $412
byte 1 91
byte 1 37
byte 1 105
byte 1 32
byte 1 58
byte 1 32
byte 1 37
byte 1 105
byte 1 93
byte 1 32
byte 1 0
align 1
LABELV $370
byte 1 68
byte 1 111
byte 1 117
byte 1 98
byte 1 108
byte 1 101
byte 1 32
byte 1 112
byte 1 114
byte 1 101
byte 1 100
byte 1 105
byte 1 99
byte 1 116
byte 1 105
byte 1 111
byte 1 110
byte 1 32
byte 1 100
byte 1 101
byte 1 99
byte 1 97
byte 1 121
byte 1 58
byte 1 32
byte 1 37
byte 1 102
byte 1 10
byte 1 0
align 1
LABELV $357
byte 1 80
byte 1 114
byte 1 101
byte 1 100
byte 1 105
byte 1 99
byte 1 116
byte 1 105
byte 1 111
byte 1 110
byte 1 32
byte 1 109
byte 1 105
byte 1 115
byte 1 115
byte 1 58
byte 1 32
byte 1 37
byte 1 102
byte 1 10
byte 1 0
align 1
LABELV $342
byte 1 112
byte 1 114
byte 1 101
byte 1 100
byte 1 105
byte 1 99
byte 1 116
byte 1 105
byte 1 111
byte 1 110
byte 1 32
byte 1 101
byte 1 114
byte 1 114
byte 1 111
byte 1 114
byte 1 10
byte 1 0
align 1
LABELV $328
byte 1 80
byte 1 114
byte 1 101
byte 1 100
byte 1 105
byte 1 99
byte 1 116
byte 1 105
byte 1 111
byte 1 110
byte 1 84
byte 1 101
byte 1 108
byte 1 101
byte 1 112
byte 1 111
byte 1 114
byte 1 116
byte 1 10
byte 1 0
align 1
LABELV $293
byte 1 51
byte 1 51
byte 1 0
align 1
LABELV $289
byte 1 56
byte 1 0
align 1
LABELV $288
byte 1 112
byte 1 109
byte 1 111
byte 1 118
byte 1 101
byte 1 95
byte 1 109
byte 1 115
byte 1 101
byte 1 99
byte 1 0
align 1
LABELV $271
byte 1 101
byte 1 120
byte 1 99
byte 1 101
byte 1 101
byte 1 100
byte 1 101
byte 1 100
byte 1 32
byte 1 80
byte 1 65
byte 1 67
byte 1 75
byte 1 69
byte 1 84
byte 1 95
byte 1 66
byte 1 65
byte 1 67
byte 1 75
byte 1 85
byte 1 80
byte 1 32
byte 1 111
byte 1 110
byte 1 32
byte 1 99
byte 1 111
byte 1 109
byte 1 109
byte 1 97
byte 1 110
byte 1 100
byte 1 115
byte 1 10
byte 1 0
