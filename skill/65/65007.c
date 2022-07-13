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
	set_number(7);
	set_name("Sơ Cấp Khí Huyết Chế Tác");
	set_skill_level(18);
	set_tool(515);
	set_tili(1);
	set_final("/item/final/15/1500");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"55"	: 	1, 
	"56"	: 	2, 
	"101"	: 	2, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
