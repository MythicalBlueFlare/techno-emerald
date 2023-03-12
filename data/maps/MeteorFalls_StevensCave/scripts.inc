.set LOCALID_COURTNEY, 1

MeteorFalls_StevensCave_MapScripts::
	.byte 0

MeteorFalls_StevensCave_EventScript_Courtney::
	lock
	waitse
	playse SE_PIN
	applymovement LOCALID_COURTNEY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_COURTNEY, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_COURTNEY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_TimeToSettleThis, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_COURTNEY_METEOR_FALLS_FINAL, MeteorFalls_StevensCave_Text_CourtneyDefeat
	msgbox MeteorFalls_StevensCave_Text_DontLookForMe, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_METEOR_FALLS_STEVEN
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_COURTNEY
	fadescreen FADE_FROM_BLACK
	release
	end 

MeteorFalls_StevensCave_Text_TimeToSettleThis:
	.string "So, you've found me…\p"
	.string "Haha… ha…\p"
	.string "I'm so pathetic…\n"
	.string "Letting myself get caught by you.\p"
	.string "Guess I have no choice…\p"
	.string "Time to settle this!$"

MeteorFalls_StevensCave_Text_CourtneyDefeat:
	.string "So…\n"
	.string "This is it, then…$"

MeteorFalls_StevensCave_Text_DontLookForMe:
	.string "I've lost…\n"
	.string "Again and again.\p"
	.string "Maybe LEADER MAXIE was right.\p"
	.string "…\p"
	.string "I need to think…\n"
	.string "Don't come looking for me.$"

