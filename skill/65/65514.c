#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(650);
	set_skill_type(2);
	set_number(514);
	set_name("Hoàng Hôn Hạng Liên");
	set_skill_level(35);
	set_tool(515);
	set_tili(1);
	set_final("/item/final/86/6035");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"81"	: 	1, 
	"78"	: 	1, 
	"45"	: 	2, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
