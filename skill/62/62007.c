#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(2);
	set_number(7);
	set_name("Đồng Đao Rèn");
	set_skill_level(21);
	set_tool(500);
	set_tili(1);
	set_final("/item/final/72/1020");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"244"	: 	2, 
	"243"	: 	2, 
	"239"	: 	1, 
	"215"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
