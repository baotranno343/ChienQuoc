inherit ITEM;

void remove_effect(object who)
{
	int hp,pp,dp;
	pp = who->get_2("magic_card.pp");
	if ( pp )
	{
		who->delete_2("magic_card.pp");	
		USER_ENERGY_D->count_pp(who);
	}
	dp = who->get_2("magic_card.dp");
	if ( dp )
	{	who->delete_2("magic_card.dp");	
		USER_ENERGY_D->count_dp(who);
	}
	hp = who->get_2("magic_card.hp");
	if ( hp )
	{
		who->delete_2("magic_card.hp");	
		USER_ENERGY_D->count_max_hp(who);
	}
}

