EventScript_PokeRider:: 
	goto_if_set FLAG_CHALLENGING_ELITE_4, EventScript_PokeRider_CantUse
	special SetupPokeRider
	release 
	end 
	
EventScript_PokeRider_CantUse::
	msgbox PokeRider_Text_CantUse, MSGBOX_DEFAULT
	release
	end
	
PokeRider_Text_CantUse:
	.string "DAD's advice…\n"
	.string "{PLAYER}, there's a time and place for\l"
	.string "everything!$"