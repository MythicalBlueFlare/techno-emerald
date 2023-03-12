GraniteCave_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveHole_CheckFallDownHole
	map_script MAP_SCRIPT_ON_TRANSITION, CaveHole_FixCrackedGround
	map_script MAP_SCRIPT_ON_RESUME, GraniteCave_B1F_SetHoleWarp
	.byte 0

GraniteCave_B1F_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_GRANITE_CAVE_B2F
	end

GraniteCave_B1F_EventScript_Artist::
	lock
	faceplayer
	playse SE_PIN
	applymovement 2, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox GraniteCave_B1F_ArtistComplain, MSGBOX_DEFAULT
	closemessage
	applymovement 2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end
	
GraniteCave_B1F_ArtistComplain:
	.string "Hmm? What do you want?\n" 
	.string "You dare disturb a painting prodigy?\p" 
	.string "Scram!$" 
