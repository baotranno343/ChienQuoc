#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(1);
	set_number(303);
	set_name("Tàm Ti Hộ Thủ Rèn");
	set_skill_level(35);
	set_tool(500);
	set_tili(1);
	set_final("/item/final/70/1035");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"247"	: 	2, 
	"319"	: 	2, 
	"47"	: 	5, 
	"311"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
