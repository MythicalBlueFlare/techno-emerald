.set LOCALID_NURSE, 1
.set LOCALID_GUARD_1, 3
.set LOCALID_GUARD_2, 4
.set LOCALID_WALLACE, 5

EverGrandeCity_PokemonLeague_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_PokemonLeague_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

EverGrandeCity_PokemonLeague_1F_OnTransition:
	setrespawn HEAL_LOCATION_EVER_GRANDE_CITY_POKEMON_LEAGUE
	setflag FLAG_LANDMARK_POKEMON_LEAGUE
	call_if_unset FLAG_ENTERED_ELITE_FOUR, EverGrandeCity_PokemonLeague_1F_EventScript_GuardsBlockDoor
	end

EverGrandeCity_PokemonLeague_1F_EventScript_GuardsBlockDoor::
	setobjectxyperm LOCALID_GUARD_1, 9, 2
	setobjectxyperm LOCALID_GUARD_2, 10, 2
	return

EverGrandeCity_PokemonLeague_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

EverGrandeCity_PokemonLeague_1F_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart EverGrandeCity_PokemonLeague_1F_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
EverGrandeCity_PokemonLeague_1F_Pokemart:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end

@ The door guards only check for FLAG_BADGE06_GET because Winonas badge is the only one that can be skipped
@ Its assumed the player has the remaining badges
EverGrandeCity_PokemonLeague_1F_EventScript_DoorGuard::
	lockall
	goto_if_set FLAG_ENTERED_ELITE_FOUR, EverGrandeCity_PokemonLeague_1F_EventScript_GoForth
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_ge VAR_TEMP_0, 11, EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromRight
	call_if_le VAR_TEMP_0, 8, EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromLeft
	message EverGrandeCity_PokemonLeague_1F_Text_MustHaveAllGymBadges
	waitmessage
	delay 120
	goto_if_unset FLAG_BADGE06_GET, EverGrandeCity_PokemonLeague_1F_EventScript_NotAllBadges
	closemessage
	applymovement LOCALID_GUARD_1, EverGrandeCity_PokemonLeague_1F_Movement_LeftGuardOutOfWay
	applymovement LOCALID_GUARD_2, EverGrandeCity_PokemonLeague_1F_Movement_RightGuardOutOfWay
	waitmovement 0
	delay 10
	playfanfare MUS_OBTAIN_BADGE
	message EverGrandeCity_PokemonLeague_1F_Text_GoForth
	waitmessage
	waitfanfare
	closemessage
	copyobjectxytoperm LOCALID_GUARD_1
	copyobjectxytoperm LOCALID_GUARD_2
	setflag FLAG_ENTERED_ELITE_FOUR
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromRight::
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromRight
	waitmovement 0
	return

EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromLeft::
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromLeft
	waitmovement 0
	return

EverGrandeCity_PokemonLeague_1F_EventScript_NotAllBadges::
	playse SE_FAILURE
	msgbox EverGrandeCity_PokemonLeague_1F_Text_HaventObtainedAllBadges, MSGBOX_DEFAULT
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_EventScript_GoForth::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox EverGrandeCity_PokemonLeague_1F_Text_GoForth, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromRight:
	walk_down
	walk_left
	walk_in_place_faster_up
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromLeft:
	walk_down
	walk_right
	walk_in_place_faster_up
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_LeftGuardOutOfWay:
	walk_left
	walk_in_place_faster_down
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_RightGuardOutOfWay:
	walk_right
	walk_in_place_faster_down
	step_end
	
EverGrandeCity_PokemonLeague_1F_Movement_WallaceStartWalkUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
	
EverGrandeCity_PokemonLeague_1F_Movement_WallaceLeave:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

EverGrandeCity_PokemonLeague_1F_EventScript_Wallace0::
	lockall
	setobjectxy LOCALID_WALLACE, 9, 8
	goto EverGrandeCity_PokemonLeague_1F_EventScript_Wallace
	end

EverGrandeCity_PokemonLeague_1F_EventScript_Wallace1::
	lockall
	setobjectxy LOCALID_WALLACE, 10, 8
	goto EverGrandeCity_PokemonLeague_1F_EventScript_Wallace
	end
	
EverGrandeCity_PokemonLeague_1F_EventScript_Wallace:: 
	setvar VAR_BATTLE_STATUS, 8
	applymovement LOCALID_WALLACE, EverGrandeCity_PokemonLeague_1F_Movement_WallaceStartWalkUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	setweather WEATHER_RAIN
	doweather
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	trainerbattle_single TRAINER_WALLACE, EverGrandeCity_PokemonLeague_1F_Text_WallaceSoYouveMadeIt, EverGrandeCity_PokemonLeague_1F_Text_WallaceDefeat, EverGrandeCity_PokemonLeague_1F_EventScript_WallaceDefeated, MUSIC
	release 
	end
	
EverGrandeCity_PokemonLeague_1F_EventScript_WallaceDefeated::
	lockall 
	setweather WEATHER_NONE
	doweather
	msgbox EverGrandeCity_PokemonLeague_1F_Text_WallaceGreatBattle, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLACE, EverGrandeCity_PokemonLeague_1F_Movement_WallaceLeave
	waitmovement 0 
	removeobject LOCALID_WALLACE
	setvar VAR_WALLACE_ENCOUNTER, 1
	setflag FLAG_WALLACE_DEFEATED
	release 
	end 

EverGrandeCity_PokemonLeague_1F_Text_MustHaveAllGymBadges:
	.string "Beyond this point, only those TRAINERS\n"
	.string "who have collected all the GYM BADGES\l"
	.string "are permitted to enter.\p"
	.string "TRAINER, let us confirm that you have\n"
	.string "all the GYM BADGES.$"

EverGrandeCity_PokemonLeague_1F_Text_HaventObtainedAllBadges:
	.string "You haven't obtained all the BADGES.\p"
	.string "If you're bound for the POKéMON\n"
	.string "LEAGUE, you must return with them.$"

EverGrandeCity_PokemonLeague_1F_Text_GoForth:
	.string "TRAINER! Believe in yourself and your\n"
	.string "POKéMON, and go forth!$"

EverGrandeCity_PokemonLeague_1F_Text_WallaceSoYouveMadeIt:
	.string "I see you've made it, {PLAYER}.\p"
	.string "From the moment I met you in\n"
	.string "MOSSDEEP CITY, I could tell you\l"
	.string "would achieve greatness.\p"
	.string "Here you are, standing elegantly at\n"
	.string "the gates of the POKéMON LEAGUE.\p"
	.string "There's something about you…\p"
	.string "A difference in your demeanor…\p"
	.string "Before you challenge the ELITE FOUR,\n"
	.string "I would like you evaluate you myself.\p"
	.string "Now, show me.\n"
	.string "Show me the power you wield with\l"
	.string "your POKéMON.\p"
	.string "And I, in turn, shall present you…\n"
	.string "With a performance of illusions in\l"
	.string "water… By me and my POKéMON!$"
	
EverGrandeCity_PokemonLeague_1F_Text_WallaceDefeat:
	.string "Bravo!$"
	
EverGrandeCity_PokemonLeague_1F_Text_WallaceGreatBattle:
	.string "I realize now your authenticity\n"
	.string "and magnificence as a POKéMON TRAINER.\p"
	.string "I find much joy in having met you\n"
	.string "and your POKéMON.\p"
	.string "{PLAYER}, please keep reaching for the\n"
	.string "stars! Become the ultimate work of art,\l"
	.string "and show me what you can do!$"