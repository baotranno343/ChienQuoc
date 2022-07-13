#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(640);
	set_skill_type(2);
	set_number(14);
	set_name("Tế Ma Quán Chế Tác");
	set_skill_level(21);
	set_tool(510);
	set_tili(1);
	set_final("/item/final/65/6020");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"45"	: 	3, 
	"313"	: 	1, 
	"239"	: 	1, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
