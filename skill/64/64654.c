#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(640);
	set_skill_type(3);
	set_number(654);
	set_name("Thất Bảo Ngoa Chế Tác");
	set_skill_level(105);
	set_tool(512);
	set_tili(2);
	set_final("/item/final/88/4105");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"54"	: 	3, 
	"269"	: 	2, 
	"104"	: 	1, 
	"309"	: 	1, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
