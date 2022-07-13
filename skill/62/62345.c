#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(5);
	set_number(345);
	set_name("Kình Thiên Trụ Rèn");
	set_skill_level(105);
	set_tool(502);
	set_tili(2);
	set_final("/item/final/75/1105");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"309"	: 	1, 
	"267"	: 	3, 
	"65"	: 	1, 
	"24"	: 	1, 
	"310"	: 	1, 
//	无	: 	0,            
        ])); 	
}
