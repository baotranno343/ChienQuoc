#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(640);
	set_skill_type(7);
	set_number(50);
	set_name("Lăng Bao Bố Chế Tác");
	set_skill_level(40);
	set_tool(511);
	set_tili(1);
	set_final("/item/std/6004");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"48"	: 	5, 
	"35"	: 	5, 
	"240"	: 	1, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
