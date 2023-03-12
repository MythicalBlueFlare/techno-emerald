.set LOCALID_WALLY_ENTRANCE, 4
.set LOCALID_BRANDON, 8

VictoryRoad_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VictoryRoad_1F_OnTransition
	.byte 0

VictoryRoad_1F_OnTransition:
	call_if_eq VAR_VICTORY_ROAD_1F_STATE, 1, VictoryRoad_1F_EventScript_SetEntranceWallyPos1
	call_if_eq VAR_VICTORY_ROAD_1F_STATE, 2, VictoryRoad_1F_EventScript_SetEntranceWallyPos2
	end

VictoryRoad_1F_EventScript_SetEntranceWallyPos1::
	setobjectxyperm LOCALID_WALLY_ENTRANCE, 2, 24
	setobjectmovementtype LOCALID_WALLY_ENTRANCE, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_SetEntranceWallyPos2::
	setobjectxyperm LOCALID_WALLY_ENTRANCE, 3, 24
	setobjectmovementtype LOCALID_WALLY_ENTRANCE, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_WallyBattleTrigger1::
	lockall
	setvar VAR_0x8008, 1
	addobject LOCALID_WALLY_ENTRANCE
	applymovement LOCALID_WALLY_ENTRANCE, VictoryRoad_1F_Movement_WallyApproachPlayer1
	waitmovement 0
	goto VictoryRoad_1F_EventScript_WallyEntranceBattle
	end

VictoryRoad_1F_EventScript_WallyBattleTrigger2::
	lockall
	setvar VAR_0x8008, 2
	addobject LOCALID_WALLY_ENTRANCE
	applymovement LOCALID_WALLY_ENTRANCE, VictoryRoad_1F_Movement_WallyApproachPlayer2
	waitmovement 0
	goto VictoryRoad_1F_EventScript_WallyEntranceBattle
	end

VictoryRoad_1F_EventScript_WallyEntranceBattle::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox VictoryRoad_1F_Text_PromiseWeMade, MSGBOX_DEFAULT
	closemessage
	delay 32 
	playbgm MUS_VS_FINAL_WALLY, FALSE
	delay 8
	msgbox VictoryRoad_1F_Text_WallyIWontLose, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_VR_1, VictoryRoad_1F_Text_WallyEntranceDefeat
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_VICTORY_ROAD_ENTRANCE_WALLY
	copyobjectxytoperm LOCALID_WALLY_ENTRANCE
	setflag FLAG_DEFEATED_WALLY_VICTORY_ROAD
	copyvar VAR_VICTORY_ROAD_1F_STATE, VAR_0x8008
	releaseall
	end

VictoryRoad_1F_Movement_WallyApproachPlayer1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

VictoryRoad_1F_Movement_WallyApproachPlayer2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

@ This Wally appears near the entrance once his battle is triggered and remains there until the Hall of Fame is entered
VictoryRoad_1F_EventScript_EntranceWally::
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_NPC
	end

@ This Wally appears and remains at the exit after the Hall of Fame is entered
VictoryRoad_1F_EventScript_ExitWally::
	trainerbattle_single TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, VictoryRoad_1F_EventScript_RematchWally
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_RematchWally::
	trainerbattle_rematch TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Edgar::
	trainerbattle_single TRAINER_EDGAR, VictoryRoad_1F_Text_EdgarIntro, VictoryRoad_1F_Text_EdgarDefeat
	msgbox VictoryRoad_1F_Text_EdgarPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Albert::
	trainerbattle_single TRAINER_ALBERT, VictoryRoad_1F_Text_AlbertIntro, VictoryRoad_1F_Text_AlbertDefeat
	msgbox VictoryRoad_1F_Text_AlbertPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Hope::
	trainerbattle_single TRAINER_HOPE, VictoryRoad_1F_Text_HopeIntro, VictoryRoad_1F_Text_HopeDefeat
	msgbox VictoryRoad_1F_Text_HopePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_BrandonEncounter1::
	lockall
	setobjectxy LOCALID_BRANDON, 39, 5
	playse SE_EXIT
	applymovement LOCALID_BRANDON, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_BRANDON, Common_Movement_Delay32
	waitmovement 0
	applymovement LOCALID_BRANDON, VictoryRoad_1F_Movement_BrandonApproachPlayer1
	waitmovement 0
	goto VictoryRoad_1F_EventScript_Brandon
	end
	
VictoryRoad_1F_EventScript_BrandonEncounter2::
	lockall
	setobjectxy LOCALID_BRANDON, 39, 5
	playse SE_EXIT
	applymovement LOCALID_BRANDON, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_BRANDON, Common_Movement_Delay32
	waitmovement 0
	applymovement LOCALID_BRANDON, VictoryRoad_1F_Movement_BrandonApproachPlayer2
	waitmovement 0
	goto VictoryRoad_1F_EventScript_Brandon
	end

VictoryRoad_1F_EventScript_BrandonEncounter3::
	lockall
	setobjectxy LOCALID_BRANDON, 39, 5
	playse SE_EXIT
	applymovement LOCALID_BRANDON, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_BRANDON, Common_Movement_Delay32
	waitmovement 0
	applymovement LOCALID_BRANDON, VictoryRoad_1F_Movement_BrandonApproachPlayer3
	waitmovement 0
	goto VictoryRoad_1F_EventScript_Brandon
	end

VictoryRoad_1F_EventScript_Brandon::
	setvar VAR_BATTLE_STATUS, 6
	playse SE_PIN
	playbgm MUS_B_PYRAMID_TOP, TRUE
	applymovement LOCALID_BRANDON, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_BRANDON, Common_Movement_Delay48
	waitmovement 0
	trainerbattle_single TRAINER_PH_BRANDON, VictoryRoad_1F_Text_PHBrandonIntro, VictoryRoad_1F_Text_PHBrandonDefeat, VictoryRoad_1F_EventScript_BrandonDefeated, NO_MUSIC
	end

VictoryRoad_1F_EventScript_BrandonDefeated::
	msgbox VictoryRoad_1F_Text_PHBrandonPostBattle, MSGBOX_DEFAULT
	setflag FLAG_BRANDON_DEFEATED
	setvar VAR_BRANDON_ENCOUNTER, 1
	release
	end 

VictoryRoad_1F_EventScript_BrandonPostBattle::
	lock
	faceplayer
	msgbox VictoryRoad_1F_Text_PHBrandonPostBattle, MSGBOX_DEFAULT
	release
	end
	
VictoryRoad_1F_Movement_BrandonApproachPlayer1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_down
	step_end

VictoryRoad_1F_Movement_BrandonApproachPlayer2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_down
	step_end

VictoryRoad_1F_Movement_BrandonApproachPlayer3:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_down
	step_end

VictoryRoad_1F_Text_PromiseWeMade:
	.string "WALLY: Hi! {PLAYER}!\p"
	.string "I bet you're surprised to see me here!\p"
	.string "That promise we made back then…\n"
	.string "Thank you for keeping your end of it.\p"
	.string "It was really all thanks to you that\n"
	.string "I could make it this far, {PLAYER}.\p"
	.string "It was only because I lost to you back\n"
	.string "then that I could become even stronger.\p"
	.string "I'm sure that you and your POKéMON must\n"
	.string "have had to overcome a lot, too…\p"
	.string "To make it all the way here.\n"
	.string "Right, {PLAYER}?\p"
	.string "Everyone's grown so much…\p"
	.string "And now we'll finally get to see just\n"
	.string "what we can all do.\p"
	.string "Standing here facing you again gives\n"
	.string "me chills…$"
	
VictoryRoad_1F_Text_WallyIWontLose:
	.string "…But I won't give up!\p"
	.string "I won't lose anymore.\p"
	.string "My POKéMON have given me me the\n"
	.string "courage and strength to fight.\p"
	.string "I have to win for their sake!\p"
	.string "So get ready…\n"
	.string "Here I come!$"

VictoryRoad_1F_Text_WallyEntranceDefeat:
	.string "…\p"
	.string "I've lost…$"

VictoryRoad_1F_Text_WallyPostEntranceBattle:
	.string "WALLY: …\p"
	.string "…\p"
	.string "Arghhh!!!\p"
	.string "…\p"
	.string "…\p"
	.string "…Hah.\p"
	.string "{PLAYER}, you…\n"
	.string "and your POKéMON too…\p"
	.string "Thank you for not holding back when you\n"
	.string "battled against us…\l"
	.string "For not holding back when you beat us…\p"
	.string "And…\p"
	.string "VOLCARONA… Everyone…\p"
	.string "Thank you so much…\p"
	.string "I feel like I've been able to take\n"
	.string "another step forward thanks to you!\p"
	.string "I couldn't beat you this time, {PLAYER}.\n"
	.string "But I'll stay here and continue training.\p"
	.string "And one day… Look out!\n"
	.string "I swear I'll catch up to you one day!\p"
	.string "When I do, promise we'll battle again!\n"
	.string "That's a promise I intend to live up to!$"

VictoryRoad_1F_Text_WallyIntro:
	.string "WALLY: Hi! {PLAYER}!\p"
	.string "I've gotten stronger since that last\n"
	.string "time! I wanted to show you, {PLAYER}!\p"
	.string "Okay… Here I come!$"

VictoryRoad_1F_Text_WallyDefeat:
	.string "Wow!\n"
	.string "{PLAYER}, you are strong, after all!$"

VictoryRoad_1F_Text_WallyPostBattle:
	.string "WALLY: I couldn't beat you this time,\n"
	.string "too… But one of these days, {PLAYER},\l"
	.string "I'm going to catch up to you…\p"
	.string "And challenge the POKéMON LEAGUE!$"

VictoryRoad_1F_Text_EdgarIntro:
	.string "I've made it this far a couple times,\n"
	.string "but the last stretch is so long…$"

VictoryRoad_1F_Text_EdgarDefeat:
	.string "My dream ends here again…$"

VictoryRoad_1F_Text_EdgarPostBattle:
	.string "You've made it this far. Keep the\n"
	.string "momentum going and become the\l"
	.string "CHAMPION! If anyone can, it's you!$"

VictoryRoad_1F_Text_AlbertIntro:
	.string "I didn't come all this way to lose now.\n"
	.string "That possibility doesn't exist!$"

VictoryRoad_1F_Text_AlbertDefeat:
	.string "Impossible…\n"
	.string "I lost?$"

VictoryRoad_1F_Text_AlbertPostBattle:
	.string "I lost here…\p"
	.string "That means I lack the qualifications\n"
	.string "to become the CHAMPION…$"

VictoryRoad_1F_Text_HopeIntro:
	.string "This seemingly infinite and harsh road\n"
	.string "lives up to its name of VICTORY.$"

VictoryRoad_1F_Text_HopeDefeat:
	.string "Your battle style is fantastic…$"

VictoryRoad_1F_Text_HopePostBattle:
	.string "You seem to have the potential for\n"
	.string "becoming the CHAMPION.$"

VictoryRoad_1F_Text_PHBrandonIntro:
	.string "Young adventurer…\p"
	.string "Wouldn't you agree that explorations\n"
	.string "are the grandest of adventures?\p"
	.string "Your own wits!\p"
	.string "Your own strength!\p"
	.string "Your own POKéMON!\p"
	.string "And, above all, only your courage\n"
	.string "to lead you through unknown worlds…\p"
	.string "Aah, yes, indeed this life is grand!\n"
	.string "Grand, it is! Eh?\p"
	.string "I'm BRANDON.\p"
	.string "I'm the Pyramid King, at the\n"
	.string "BATTLE FRONTIER.\p"
	.string "Most people call me the chief!\p"
	.string "You coming here means you have\n"
	.string "that much confidence in yourself,\l"
	.string "am I right?\p"
	.string "Hahahah!\n"
	.string "This should be exciting!\p"
	.string "This is the final hurdle before the\n"
	.string "POKéMON LEAGUE!\p"
	.string "Now, then!\n"
	.string "Bring your courage to our battle!$"
	
VictoryRoad_1F_Text_PHBrandonDefeat:
	.string "That's it! You’ve done great!\n"
	.string "You've worked hard for this!$"

VictoryRoad_1F_Text_PHBrandonPostBattle:
	.string "Hahahah! Grand it was!\n"
	.string "Grand, yes, indeed!\p"
	.string "Well done! You've earned the right\n"
	.string "of passage to the POKéMON LEAGUE!\p"
	.string "Good luck!$"

VictoryRoad_1F_Text_KatelynnIntro:
	.string "I have nothing to say to anyone\n"
	.string "that's come this far. Come on!$"

VictoryRoad_1F_Text_KatelynnDefeat:
	.string "This is a disgrace…$"

VictoryRoad_1F_Text_KatelynnPostBattle:
	.string "Humph, go right on ahead.\n"
	.string "See if I care.$"
