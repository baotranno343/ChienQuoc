#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(4);
	set_number(61);
	set_name("Xích Tinh Kiếm Rèn");
	set_skill_level(71);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/76/1070");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"284"	: 	2, 
	"257"	: 	2, 
	"243"	: 	1, 
	"218"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
