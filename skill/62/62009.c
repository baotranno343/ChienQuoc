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
	set_number(9);
	set_name("Đồng Châm Rèn");
	set_skill_level(23);
	set_tool(500);
	set_tili(1);
	set_final("/item/final/71/1020");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"313"	: 	2, 
	"243"	: 	2, 
	"239"	: 	1, 
	"215"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
