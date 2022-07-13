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
	set_number(41);
	set_name("Ngọc Phong Châm Rèn");
	set_skill_level(53);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/71/1050");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"253"	: 	2, 
	"39"	: 	2, 
	"240"	: 	2, 
	"32"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
