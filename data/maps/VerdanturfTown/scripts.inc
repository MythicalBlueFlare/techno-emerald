.set LOCALID_TWIN, 2
.set LOCALID_TUCKER, 5

VerdanturfTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_OnTransition
	.byte 0

VerdanturfTown_OnTransition:
	setflag FLAG_VISITED_VERDANTURF_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	end

VerdanturfTown_EventScript_Twin::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_TwinTunnelOpen
	msgbox VerdanturfTown_Text_ManTryingToDigTunnel, MSGBOX_DEFAULT
	applymovement LOCALID_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_TwinTunnelOpen::
	msgbox VerdanturfTown_Text_ManDugTunnelForLove, MSGBOX_DEFAULT
	applymovement LOCALID_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_Man::
	msgbox VerdanturfTown_Text_AirCleanHere, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Camper::
	msgbox VerdanturfTown_Text_MakeBattleTentDebut, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_BoyTunnelOpen
	msgbox VerdanturfTown_Text_GuyTryingToBustThroughCave, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_BoyTunnelOpen::
	msgbox VerdanturfTown_Text_EasyToGetToRustboroNow, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_TownSign::
	msgbox VerdanturfTown_Text_TownSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_WandasHouseSign::
	msgbox VerdanturfTown_Text_WandasHouse, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_BattleTentSign::
	msgbox VerdanturfTown_Text_BattleTentSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_RusturfTunnelSign::
	msgbox VerdanturfTown_Text_RusturfTunnelSign, MSGBOX_SIGN
	end
	
VerdanturfTown_EventScript_Tucker::
	lockall 
	faceplayer
	playse SE_PIN
	applymovement LOCALID_TUCKER, Common_Movement_ExclamationMark
	waitmovement 0
	call_if_set FLAG_BRANDON_DEFEATED, VerdanturfTown_EventScript_TuckerHardMode
	trainerbattle_double TRAINER_TUCKER_1, VerdanturfTown_Text_TuckerIntro, VerdanturfTown_Text_TuckerDefeat, VerdanturfTown_Text_TuckerNeedTwoMons, VerdanturfTown_EventScript_TuckerDefeated, NO_MUSIC
	end 
	
VerdanturfTown_EventScript_TuckerHardMode::
	trainerbattle_double TRAINER_TUCKER_2, VerdanturfTown_Text_TuckerIntro, VerdanturfTown_Text_TuckerDefeat, VerdanturfTown_EventScript_TuckerDefeated, NO_MUSIC
	end 
	
VerdanturfTown_EventScript_TuckerDefeated:: 
	lockall 
	faceplayer
	msgbox VerdanturfTown_Text_TuckerLeave, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_CHOICE_SCARF
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_TUCKER
	setflag FLAG_TUCKER_DEFEATED
	fadescreen FADE_FROM_BLACK
	release 
	end 

VerdanturfTown_Text_ManTryingToDigTunnel:
	.string "My papa told me.\p"
	.string "He says this tunnel is full of\n"
	.string "timid POKéMON.\p"
	.string "They get all scared of loud noise and\n"
	.string "make a big uproar.\p"
	.string "So they had to stop the big tunnel\n"
	.string "project.\p"
	.string "But there's one man. He's trying to dig\n"
	.string "the tunnel by himself!$"

VerdanturfTown_Text_ManDugTunnelForLove:
	.string "There was a man who dug a tunnel for\n"
	.string "a lady he loved.\p"
	.string "I don't really get it, but hey!$"

VerdanturfTown_Text_AirCleanHere:
	.string "The way the winds blow, volcanic ash\n"
	.string "is never blown in this direction.\p"
	.string "The air is clean and delicious here.\n"
	.string "Living here should do wonders for even\l"
	.string "frail and sickly people.$"

VerdanturfTown_Text_MakeBattleTentDebut:
	.string "My POKéMON and I, we've been riding\n"
	.string "a hot winning streak.\p"
	.string "So I decided to make my BATTLE TENT\n"
	.string "debut in this town.$"

VerdanturfTown_Text_GuyTryingToBustThroughCave:
	.string "Did you see the cave next to the\n"
	.string "POKéMON MART?\p"
	.string "There's a guy in there who's trying to\n"
	.string "bust up boulders so he can bust out\l"
	.string "through to the other side.\p"
	.string "It'd be great if we could go through…\n"
	.string "It'll make it easy to visit RUSTBORO.$"

VerdanturfTown_Text_EasyToGetToRustboroNow:
	.string "That cave next to the POKéMON MART\n"
	.string "is now a tunnel to the other side.\p"
	.string "It's great--it's easy to go shop for\n"
	.string "new DEVON products in RUSTBORO now.$"

VerdanturfTown_Text_TownSign:
	.string "VERDANTURF TOWN\p"
	.string "“The windswept highlands with the\n"
	.string "sweet fragrance of grass.”$"

VerdanturfTown_Text_WandasHouse:
	.string "WANDA'S HOUSE$"

VerdanturfTown_Text_BattleTentSign:
	.string "BATTLE TENT VERDANTURF SITE\n"
	.string "“Feast Your Eyes on Battles!”$"

VerdanturfTown_Text_RusturfTunnelSign:
	.string "RUSTURF TUNNEL\n"
	.string "“Linking RUSTBORO and VERDANTURF\p"
	.string "“The tunnel project has been\n"
	.string "canceled.”$"

VerdanturfTown_Text_TuckerIntro:
	.string "Ahahah!\p"
	.string "Greetings!\n"
	.string "I am TUCKER, head of the BATTLE DOME.\p"
	.string "I bet you are twitching with tension of\n"
	.string "my presence!\p"
	.string "But don't worry about a thing!\p"
	.string "I want something from you.\p"
	.string "Your strategy!\n"
	.string "Let's see it!\l"
	.string "Let the battle begin!$"
	
VerdanturfTown_Text_TuckerNeedTwoMons:
	.string "You intend to challenge me with one\n"
	.string "POKéMON?\l"
	.string "Don't make me laugh!$"

VerdanturfTown_Text_TuckerDefeat:
	.string "Grr… What the…$"
	
VerdanturfTown_Text_TuckerLeave:
	.string "I see you've defeated me…\p"
	.string "Well then. Take this.\n"
	.string "It is an item said to increase the\l"
	.string "SPEED of a POKéMON, but at the cost\l"
	.string "of only being able to select one move.\p"
	.string "I have a show to put on. Can't keep the\n"
	.string "audience waiting!$"
