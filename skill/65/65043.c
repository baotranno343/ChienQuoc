#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(650);
	set_skill_type(1);
	set_number(43);
	set_name("Trung Cấp Nội Kháng Chế Tác");
	set_skill_level(47);
	set_tool(516);
	set_tili(1);
	set_final("/item/final/15/1511");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"82"	: 	1, 
	"58"	: 	1, 
	"95"	: 	1, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
