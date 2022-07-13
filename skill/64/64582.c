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
	set_number(582);
	set_name("Tử Hà Quán Chế Tác");
	set_skill_level(75);
	set_tool(511);
	set_tili(1);
	set_final("/item/final/65/6075");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"52"	: 	3, 
	"37"	: 	4, 
	"62"	: 	1, 
	"310"	: 	1, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
