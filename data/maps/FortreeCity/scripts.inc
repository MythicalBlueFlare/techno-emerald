.set LOCALID_FALKNER, 7

FortreeCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, FortreeCity_OnResume
	.byte 0

FortreeCity_OnTransition:
	setflag FLAG_VISITED_FORTREE_CITY
	end

FortreeCity_OnResume:
	setstepcallback STEP_CB_FORTREE_BRIDGE
	end

FortreeCity_EventScript_Man::
	msgbox FortreeCity_Text_SawGiganticPokemonInSky, MSGBOX_NPC
	end

FortreeCity_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_KECLEON_FLED_FORTREE, FortreeCity_EventScript_WomanGymAccessible
	msgbox FortreeCity_Text_SomethingBlockingGym, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_WomanGymAccessible::
	msgbox FortreeCity_Text_ThisTimeIllBeatWinona, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_Girl::
	msgbox FortreeCity_Text_TreesGrowByDrinkingRainwater, MSGBOX_NPC
	end

FortreeCity_EventScript_OldMan::
	msgbox FortreeCity_Text_EveryoneHealthyAndLively, MSGBOX_NPC
	end

FortreeCity_EventScript_Boy::
	msgbox FortreeCity_Text_BugPokemonComeThroughWindow, MSGBOX_NPC
	end

FortreeCity_EventScript_GameboyKid::
	msgbox FortreeCity_Text_PokemonThatEvolveWhenTraded, MSGBOX_NPC
	end

FortreeCity_EventScript_CitySign::
	msgbox FortreeCity_Text_CitySign, MSGBOX_SIGN
	end

FortreeCity_EventScript_GymSign::
	msgbox FortreeCity_Text_GymSign, MSGBOX_SIGN
	end

FortreeCity_EventScript_Kecleon::
	lock
	faceplayer
	checkitem ITEM_DEVON_SCOPE
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_EventScript_AskUseDevonScope
	msgbox FortreeCity_Text_SomethingUnseeable, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_AskUseDevonScope::
	msgbox FortreeCity_Text_UnseeableUseDevonScope, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FortreeCity_EventScript_UseDevonScope
	release
	end

FortreeCity_EventScript_UseDevonScope::
	msgbox FortreeCity_Text_UsedDevonScopePokemonFled, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Movement_KecleonAppears
	waitmovement 0
	waitse
	playmoncry SPECIES_KECLEON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	applymovement VAR_LAST_TALKED, FortreeCity_Movement_KecleonFlee
	waitmovement 0
	removeobject VAR_LAST_TALKED
	setflag FLAG_KECLEON_FLED_FORTREE
	release
	end

FortreeCity_Movement_KecleonFlee:
	walk_right
	step_end

FortreeCity_EventScript_Falkner::
	lockall
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	waitfieldeffect FLDEFF_NPCFLY_OUT
	addobject LOCALID_FALKNER
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_FALKNER, FortreeCity_Movement_FalknerApproachPlayer
	waitmovement 0
	msgbox FortreeCity_Text_ImFalkner, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FALKNER, FortreeCity_Movement_MoveInFrontGymFalkner
	applymovement OBJ_EVENT_ID_PLAYER, FortreeCity_Movement_MoveInFrontGymPlayer
	waitmovement 0
	msgbox FortreeCity_Text_IllShowYouPowerBirdPokemon, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_FALKNER, FortreeCity_Text_FalknerDefeat
	msgbox FortreeCity_Text_MyDadsBirdPokemon, MSGBOX_DEFAULT
	givemon SPECIES_PIDGEY, 30, ITEM_PIDGEOTITE
	closemessage
	msgbox FortreeCity_Text_FalknerLeave, MSGBOX_DEFAULT
	closemessage
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_FALKNER
	waitfieldeffect FLDEFF_NPCFLY_OUT
	setvar VAR_FALKNER_DEFEATED, 1
	release 
	end 
	
FortreeCity_Movement_FalknerApproachPlayer:
	walk_down
	walk_down
	walk_down
	step_end

FortreeCity_Movement_MoveInFrontGymPlayer:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	face_right
	step_end

FortreeCity_Movement_MoveInFrontGymFalkner:
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

FortreeCity_Text_SawGiganticPokemonInSky:
	.string "No one believes me, but I saw this\n"
	.string "gigantic POKéMON in the sky.\p"
	.string "It seemed to squirm as it flew toward\n"
	.string "ROUTE 131.\p"
	.string "By the way… Sniff…\n"
	.string "Um… You, uh…smell singed.\p"
	.string "Were you at a volcano or something?$"

FortreeCity_Text_SomethingBlockingGym:
	.string "I want to go to the POKéMON GYM,\n"
	.string "but something's blocking the way.\p"
	.string "After all the bother I went through\n"
	.string "training on ROUTE 120…$"

FortreeCity_Text_ThisTimeIllBeatWinona:
	.string "I've got my pride-and-joy POKéMON\n"
	.string "with me. This time, I'll beat WINONA.$"

FortreeCity_Text_TreesGrowByDrinkingRainwater:
	.string "The ground absorbs rainwater, and\n"
	.string "trees grow by drinking that water…\p"
	.string "Our FORTREE CITY exists because\n"
	.string "there's both water and soil.$"

FortreeCity_Text_EveryoneHealthyAndLively:
	.string "The CITY consists of homes built on\n"
	.string "trees.\p"
	.string "Perhaps because of that lifestyle,\n"
	.string "everyone is healthy and lively.\p"
	.string "Why, even myself--I feel as if I've\n"
	.string "grown thirty years younger.$"

FortreeCity_Text_BugPokemonComeThroughWindow:
	.string "Living on top of trees is okay.\p"
	.string "But sometimes BUG POKéMON come in\n"
	.string "through windows.\l"
	.string "It can be really startling.$"

FortreeCity_Text_PokemonThatEvolveWhenTraded:
	.string "There are POKéMON that evolve when\n"
	.string "you trade them! That's what I heard.$"

FortreeCity_Text_SomethingUnseeable:
	.string "Something unseeable is in the way.$"

FortreeCity_Text_UnseeableUseDevonScope:
	.string "Something unseeable is in the way.\p"
	.string "Want to use the DEVON SCOPE?$"

FortreeCity_Text_UsedDevonScopePokemonFled:
	.string "{PLAYER} used the DEVON SCOPE.\p"
	.string "An invisible POKéMON became completely\n"
	.string "visible!\p"
	.string "The startled POKéMON fled!$"

FortreeCity_Text_CitySign:
	.string "FORTREE CITY\n"
	.string "“The treetop city that frolics with\l"
	.string "nature.”$"

FortreeCity_Text_GymSign:
	.string "FORTREE CITY POKéMON GYM\n"
	.string "LEADER: WINONA\p"
	.string "“The bird user taking flight into\n"
	.string "the world.”$"

FortreeCity_Text_ImFalkner:
	.string "Oh?\n"
	.string "Are you looking to challenge the\l"
	.string "FORTREE GYM?\p"
	.string "I see.\n"
	.string "I'm FALKNER, a GYM LEADER from JOHTO.\p"
	.string "My FATHER was a friend of the\n"
	.string "GYM LEADER here,\l"
	.string "So I've come to visit.\p"
	.string "You seem like a strong trainer to make\n"
	.string "it this far.\l"
	.string "I'd like to test you before you take\l"
	.string "on this GYM.\p"
	.string "Let's move to a more spacious area.$"

FortreeCity_Text_IllShowYouPowerBirdPokemon:
	.string "People say you can clip Flying-type\n"
	.string "POKéMON's wings with a jolt of\l"
	.string "electricity…\p"
	.string "I won't allow such insults to bird\n"
	.string "POKéMON!\p"
	.string "I'll show you the real power of the\n"
	.string "magnificent bird POKéMON!$"

FortreeCity_Text_FalknerDefeat:
	.string "I understand…\n"
	.string "I'll bow out gracefully.$"

FortreeCity_Text_MyDadsBirdPokemon:
	.string "…For pity's sake!\n"
	.string "My dad's cherished bird POKéMON…\l"
	.string "But a defeat is a defeat.\p"
	.string "All right.\n"
	.string "Take this POKéMON,\l"
	.string "it comes all the way from JOHTO.$"

FortreeCity_Text_FalknerLeave:
	.string "You will be able to MEGA EVOLVE\n"
	.string "that POKéMON once it has fully evolved.\p"
	.string "Assuming you have a MEGA RING,\n"
	.string "of course.\p"
	.string "Truthfully…\n"
	.string "I'm unsure if you'll be able to obtain\l"
	.string "one…\p"
	.string "I've heard others from JOHTO are\n"
	.string "visiting.\p"
	.string "Maybe one of them will give you a\n"
	.string "MEGA RING.\p"
	.string "Good luck with your GYM CHALLENGE,\n"
	.string "trainer!$"
