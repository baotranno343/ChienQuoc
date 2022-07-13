#include <ansi.h>
#include <task.h>

int is_legend_npc() { return 1;}

int can_fight( object who ) 
{
	object me; 
	me = this_object();
	if ( me->get_enemy()==0 && who && who->get_enemy() != me )
	{
		return 0; 
	}
	return 1;
}