.set LOCALID_LANCE, 1

EverGrandeCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_OnTransition
	.byte 0

EverGrandeCity_OnTransition:
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	end

EverGrandeCity_EventScript_VictoryRoadSign::
	msgbox EverGrandeCity_Text_EnteringVictoryRoad, MSGBOX_SIGN
	end

EverGrandeCity_EventScript_CitySign::
	msgbox EverGrandeCity_Text_CitySign, MSGBOX_SIGN
	end

EverGrandeCity_EventScript_PokemonLeagueSign::
	msgbox EverGrandeCity_Text_EnteringPokemonLeague, MSGBOX_SIGN
	end

EverGrandeCity_EventScript_SetVisitedEverGrande::
	setflag FLAG_VISITED_EVER_GRANDE_CITY
	setvar VAR_TEMP_1, 1
	end

EverGrandeCity_EventScript_Lance::
	lockall 
	msgbox EverGrandeCity_Text_HoldIt, MSGBOX_DEFAULT
	closemessage
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	waitfieldeffect FLDEFF_NPCFLY_OUT
	addobject LOCALID_LANCE
	applymovement LOCALID_LANCE, Common_Movement_FaceUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	playse SE_PIN
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_LANCE, Common_Movement_WalkUp
	waitmovement 0
	msgbox EverGrandeCity_Text_LanceFaceMeWithCourage, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_LANCE, EverGrandeCity_Text_LanceDefeat
	msgbox EverGrandeCity_Text_LanceTrulyPowerful
	givemon SPECIES_AERODACTYL, 75, ITEM_AERODACTYLITE
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_LANCE
	waitfieldeffect FLDEFF_NPCFLY_OUT
	setvar VAR_LANCE_ENCOUNTER, 1
	releaseall
	end

EverGrandeCity_Text_EnteringVictoryRoad:
	.string "ENTERING VICTORY ROAD$"

EverGrandeCity_Text_EnteringPokemonLeague:
	.string "ENTERING POKéMON LEAGUE\n"
	.string "CENTER GATE$"

EverGrandeCity_Text_CitySign:
	.string "EVER GRANDE CITY\p"
	.string "“The paradise of flowers, the sea,\n"
	.string "and POKéMON.”$"

EverGrandeCity_Text_HoldIt:
	.string "Hold it!$"

EverGrandeCity_Text_LanceFaceMeWithCourage:
	.string "You must be {PLAYER},\n"
	.string "yes?\p"
	.string "I'm LANCE, the CHAMPION of JOHTO.\p"
	.string "When I heard of the crisis that\n"
	.string "befell HOENN,\l"
	.string "I came as soon as possible.\p"
	.string "It seems that it has already been dealt\n"
	.string "with.\p"
	.string "STEVEN STONE told me that you were the\n"
	.string "one to quell the LEGENDARIES' rage.\p"
	.string "I have only stayed for one reason.\p"
	.string "I would like to face you myself.\n"
	.string "I won't take no for an answer!\p"
	.string "Face me with the courage you faced\n"
	.string "the LEGENDARIES with!$"

EverGrandeCity_Text_LanceDefeat:
	.string "…It's over.\p"
	.string "But it's an odd feeling.\p"
	.string "I'm not angry that I lost.\p"
	.string "In fact,\n"
	.string "I feel happy.\p"
	.string "Happy I get to witness the rise\n"
	.string "of a great TRAINER like yourself.$"

EverGrandeCity_Text_LanceTrulyPowerful:
	.string "You are a truly powerful POKéMON\n"
	.string "TRAINER.\p"
	.string "I am glad to have gotten to meet you.\p"
	.string "I leave you with this parting gift,\n"
	.string "a strong and powerful POKéMON capable\l"
	.string "of MEGA EVOLUTION.\p"
	.string "Farewell, {PLAYER}!$"