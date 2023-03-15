.set LOCALID_MORTY, 4

MtPyre_1F_MapScripts::
	.byte 0

MtPyre_1F_EventScript_CleanseTagWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CLEANSE_TAG, MtPyre_1F_EventScript_ReceivedCleanseTag
	msgbox MtPyre_1F_Text_TakeThisForYourOwnGood, MSGBOX_DEFAULT
	giveitem ITEM_CLEANSE_TAG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CLEANSE_TAG
	release
	end

MtPyre_1F_EventScript_ReceivedCleanseTag::
	msgbox MtPyre_1F_Text_ExplainCleanseTag, MSGBOX_DEFAULT
	release
	end

MtPyre_1F_EventScript_PokefanF::
	msgbox MtPyre_1F_Text_ComeToPayRespects, MSGBOX_NPC
	end

MtPyre_1F_EventScript_Man::
	msgbox MtPyre_1F_Text_RestingPlaceOfZigzagoon, MSGBOX_NPC
	end

MtPyre_1F_EventScript_Morty::
	lockall 
	faceplayer
	playse SE_PIN
	applymovement LOCALID_MORTY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MORTY, Common_Movement_Delay48
	waitmovement 0
	trainerbattle_single TRAINER_MORTY, MtPyre_1F_Text_MortyIntro, MtPyre_1F_Text_MortyDefeat, MtPyre_1F_EventScript_MortyDefeated, NO_MUSIC
	end 
	
MtPyre_1F_EventScript_MortyDefeated:: 
	msgbox MtPyre_1F_Text_MortyGiveShuppet, MSGBOX_DEFAULT
	givemon SPECIES_SHUPPET, 30, ITEM_BANETTITE
	closemessage
	msgbox MtPyre_1F_Text_MortyGiveMegaRing, MSGBOX_DEFAULT
	giveitem ITEM_MEGA_RING
	closemessage
	msgbox MtPyre_1F_Text_MortyLeave, MSGBOX_DEFAULT
	closemessage
	playse SE_EXIT
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MORTY
	setflag FLAG_MORTY_DEFEATED
	fadescreen FADE_FROM_BLACK
	release 
	end 

MtPyre_1F_Text_TakeThisForYourOwnGood:
	.string "All sorts of beings wander the slopes\n"
	.string "of MT. PYRE…\p"
	.string "There is no telling what may happen.\n"
	.string "Take this. It's for your own good.$"

MtPyre_1F_Text_ExplainCleanseTag:
	.string "Have a POKéMON hold that\n"
	.string "CLEANSE TAG.\p"
	.string "It will help ward off wild POKéMON.$"

MtPyre_1F_Text_ComeToPayRespects:
	.string "Did you come to pay your respect\n"
	.string "to the spirits of departed POKéMON?\p"
	.string "You must care for your POKéMON a lot.$"

MtPyre_1F_Text_RestingPlaceOfZigzagoon:
	.string "This is the final resting place of my\n"
	.string "ZIGZAGOON. I cherished it…$"

MtPyre_1F_Text_MortyIntro:	
	.string "Greetings.\n"
	.string "My name is MORTY.\p"
	.string "I am a GYM LEADER from JOHTO.\p"
	.string "The land of HOENN is mysterious,\n"
	.string "and facinating.\p"
	.string "There are many POKéMON here that\n"
	.string "can be found nowhere else.\p"
	.string "Back in my home town,\n"
	.string "it is believed that a raibow-hued\l"
	.string "POKéMON will come down to appear\l"
	.string "before a truly powerful TRAINER.\p"
	.string "I believed that tale,\n"
	.string "so I have been traveling and training\l"
	.string "all my life.\p"
	.string "As a result,\n"
	.string "I can see what others cannot.\p"
	.string "I see a shadow of the person who will\n"
	.string "who will make the POKéMON appear.\p"
	.string "I believe that person is me!\p"
	.string "And I've decided…\n"
	.string "You're going to help me reach that level!$"

MtPyre_1F_Text_MortyDefeat:
	.string "How is this possible…$"

MtPyre_1F_Text_MortyGiveShuppet:
	.string "I don't think our potentials are\n"
	.string "so different.\l"
	.string "But you seem to have something more\l"
	.string "than that…\p"
	.string "So be it.\p"
	.string "I'd like you to have this POKéMON.\n"
	.string "It is not native to HOENN.$"

MtPyre_1F_Text_MortyGiveMegaRing:
	.string "That SHUPPET is holding a special item.\p"
	.string "It is a MEGA STONE. It will allow you to\n"
	.string "MEGA EVOLVE it in battle, much like my\l"
	.string "GENGAR.\p"
	.string "Well… As long as you have a MEGA RING.\p"
	.string "Speaking of which,\n"
	.string "take one.\l"
	.string "I have a few spare on me.$"

MtPyre_1F_Text_MortyLeave:
	.string "I should be going now.\p"
	.string "I believe others from JOHTO\n"
	.string "are visiting as well.\l"
	.string "Maybe you will bump into them.\p"
	.string "Farewell…$"