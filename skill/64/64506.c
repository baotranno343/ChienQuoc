#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(640);
	set_skill_type(1);
	set_number(506);
	set_name("Ma Bố Bào Chế Tác");
	set_skill_level(35);
	set_tool(510);
	set_tili(1);
	set_final("/item/final/60/5035");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"45"	: 	8, 
	"239"	: 	4, 
	"215"	: 	1, 
	"312"	: 	1, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
