#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(6);
	set_number(360);
	set_name("Ngọc Hành Châm Rèn");
	set_skill_level(120);
	set_tool(502);
	set_tili(2);
	set_final("/item/final/71/1120");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(2);
	set_base_rate(75);
        set_product( ([
	"42"	: 	2, 
	"309"	: 	1, 
	"42"	: 	1, 
	"1837"	: 	3, 
	"94"	: 	2, 
//	无	: 	0,            
        ])); 	
}
