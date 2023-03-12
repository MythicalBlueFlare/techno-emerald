.set LOCALID_RAYQUAZA_SLEEPING, 1
.set LOCALID_COURTNEY, 3

SkyPillar_Top_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, SkyPillar_Top_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, SkyPillar_Top_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SkyPillar_Top_OnWarp
	.byte 0

SkyPillar_Top_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, SkyPillar_Top_EventScript_TryRemoveRayquaza
	end

SkyPillar_Top_EventScript_TryRemoveRayquaza::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

SkyPillar_Top_OnTransition:
	call_if_lt VAR_SKY_PILLAR_STATE, 2, SkyPillar_Top_EventScript_SetCleanLayout
	call_if_ge VAR_SKY_PILLAR_STATE, 2, SkyPillar_Top_EventScript_TryShowRayquaza
	end

SkyPillar_Top_EventScript_SetCleanLayout::
	setmaplayoutindex LAYOUT_SKY_PILLAR_TOP_CLEAN
	setobjectmovementtype LOCALID_RAYQUAZA_SLEEPING, MOVEMENT_TYPE_FACE_DOWN
	return

SkyPillar_Top_EventScript_TryShowRayquaza::
	call_if_unset FLAG_DEFEATED_RAYQUAZA, SkyPillar_Top_EventScript_ShowRayquaza
	return

SkyPillar_Top_EventScript_ShowRayquaza::
	clearflag FLAG_HIDE_SKY_PILLAR_TOP_RAYQUAZA_STILL
	return

SkyPillar_Top_OnWarp:
	map_script_2 VAR_SKY_PILLAR_STATE, 0, SkyPillar_Top_EventScript_RayquazaFaceDown
	.2byte 0

SkyPillar_Top_EventScript_RayquazaFaceDown::
	turnobject LOCALID_RAYQUAZA_SLEEPING, DIR_SOUTH
	end

SkyPillar_Top_EventScript_Rayquaza::
	lockall
	waitse
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_NECROZMA, 82
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SkyPillar_Top_EventScript_DefeatedRayquaza
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SkyPillar_Top_EventScript_RanFromRayquaza
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SkyPillar_Top_EventScript_RanFromRayquaza
	setflag FLAG_DEFEATED_RAYQUAZA
	releaseall
	end

SkyPillar_Top_EventScript_DefeatedRayquaza::
	setflag FLAG_DEFEATED_RAYQUAZA
	goto SkyPillar_Top_EventScript_DefeatedRayquaza2
	end

SkyPillar_Top_EventScript_RanFromRayquaza::
	setvar VAR_0x8004, SPECIES_RAYQUAZA
	goto SkyPillar_Top_EventScript_RanFromRayquaza2
	end

SkyPillar_Top_EventScript_DefeatedRayquaza2::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	releaseall
	end

SkyPillar_Top_EventScript_RanFromRayquaza2::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	bufferspeciesname STR_VAR_1, VAR_0x8004
	msgbox gText_LegendaryFlewAway, MSGBOX_DEFAULT
	releaseall
	end

SkyPillar_Top_EventScript_AwakenRayquaza::
	lockall
	fadeoutbgm 1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, SkyPillar_Top_Movement_CameraPanUp
	waitmovement 0
	special RemoveCameraObject
	applymovement LOCALID_RAYQUAZA_SLEEPING, SkyPillar_Top_Movement_RayquazaStir
	waitmovement 0
	waitse
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
	waitstate
	waitse
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	waitmoncry
	applymovement LOCALID_RAYQUAZA_SLEEPING, SkyPillar_Top_Movement_RayquazaFlyOff
	waitmovement 0
	removeobject LOCALID_RAYQUAZA_SLEEPING
	msgbox SkyPillar_Top_Text_RayquazaFlewOff, MSGBOX_DEFAULT
	closemessage
	delay 20
	fadeinbgm 1
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, SkyPillar_Top_Movement_CameraPanDown
	waitmovement 0
	special RemoveCameraObject
	setvar VAR_SOOTOPOLIS_CITY_STATE, 5
	setvar VAR_SKY_PILLAR_STATE, 1
	setvar VAR_SKY_PILLAR_RAQUAZA_CRY_DONE, 1
	releaseall
	end

@ Rayquaza has unusual movement frames
@ See comments, or sAnimTable_Rayquaza
SkyPillar_Top_Movement_RayquazaStir:
	delay_16
	walk_in_place_fast_left  @ Coiled, awake
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_left  @ Coiled, mouth open
	delay_16
	walk_in_place_right  @ Normal, awake
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	step_end

SkyPillar_Top_Movement_RayquazaFlyOff:
	delay_16
	walk_in_place_down  @ Coiled, asleep
	delay_8
	walk_in_place_right  @ Normal, awake
	delay_8
	walk_faster_up  @ Fly up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	step_end

SkyPillar_Top_Movement_CameraPanUp:
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end

SkyPillar_Top_Movement_CameraPanDown:
	walk_slow_down
	walk_slow_down
	walk_slow_down
	step_end
	
SkyPillar_Top_Movement_CourtneyPaceUp:
	walk_up
	delay_16
	face_down
	step_end
	
SkyPillar_Top_EventScript_Courtney::
	lock
	faceplayer 
	playse SE_PIN
	applymovement LOCALID_COURTNEY, Common_Movement_ExclamationMark
	waitmovement 0
	delay 30
	playbgm MUS_RG_POKE_MANSION, FALSE
	msgbox SkyPillar_Top_Text_YouFinallyArrived, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COURTNEY, Common_Movement_WalkUp
	waitmovement 0 
	delay 8
	applymovement LOCALID_COURTNEY, Common_Movement_FaceDown
	waitmovement 0
	msgbox SkyPillar_Top_Text_TheStrangeCreatures, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COURTNEY, Common_Movement_WalkDown
	waitmovement 0 
	trainerbattle_double TRAINER_COURTNEY_SKYPILLAR, SkyPillar_Top_Text_FaceMeInBattle, SkyPillar_Top_Text_CourtneyDefeat, SkyPillar_Top_Text_CourtneyNeedTwoMons, SkyPillar_Top_EventScript_CourtneyDefeated, NO_MUSIC
	release
	end 
	
SkyPillar_Top_EventScript_CourtneyDefeated::
	msgbox SkyPillar_Top_Text_WhyMustYouGetInMyWay, MSGBOX_DEFAULT
	closemessage
	delay 32
	msgbox SkyPillar_Top_Text_WhenIReturn, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_COURTNEY
	setflag FLAG_FINAL_COURTNEY_DEFEATED
	fadescreen FADE_FROM_BLACK
	release
	end 

SkyPillar_Top_Text_RayquazaFlewOff:
	.string "The awakened RAYQUAZA flew off…$"
	
SkyPillar_Top_Text_YouFinallyArrived:
	.string "What do you plan on doing, {PLAYER}?\p"
	.string "To calm RESHIRAM and ZEKROM's rage?\n"
	.string "This world will eventually reach the\l"
	.string "point of no return.\p"
	.string "My team… The team I put all my hope\n"
	.string "into… LEADER MAXIE… He was broken…\p"
	.string "Broken because of you.$"
	
SkyPillar_Top_Text_TheStrangeCreatures:
	.string "Those… Things… That TEAM MAGMA and\n"
	.string "TEAM AQUA obtained.\p"
	.string "They did not show up on a whim.\p"
	.string "They were brought here by a certain\n"
	.string "POKéMON…\p"
	.string "A POKéMON capable of opening tears in\n"
	.string "space and time.$"
	
SkyPillar_Top_Text_FaceMeInBattle:
	.string "This POKéMON is now under my control!\n"
	.string "With it, I will plunge this world into\l"
	.string "darkness.\p"
	.string "And for you…\p"
	.string "It's the end of the line!$"
	
SkyPillar_Top_Text_CourtneyDefeat:
	.string "…Just barely!$"
	
SkyPillar_Top_Text_CourtneyNeedTwoMons:
	.string "Only one POKéMON? Don't humor me.$"
	
SkyPillar_Top_Text_WhyMustYouGetInMyWay:
	.string "Why? Why must… you always…\n"
	.string "Always, always, always, always…\l"
	.string "Get in my way!\p"
	.string "Darn! Dang it…$"
	
SkyPillar_Top_Text_WhenIReturn:
	.string "…Ha ha. Ahahahaha haha!\p"
	.string "Don't think this is the end!\n"
	.string "I'll be back someday…\l"
	.string "And when I return…\p"
	.string "You'll be sorry.$"