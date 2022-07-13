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
	set_number(714);
	set_name("Long Thần Hạng Liên Chế Tác");
	set_skill_level(116);
	set_tool(517);
	set_tili(4);
	set_final("/item/final/86/8116");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(2);
	set_base_rate(65);
        set_product( ([
	"66"	: 	2, 
	"65"	: 	2, 
	"42"	: 	3, 
	"65"	: 	2, 
	"323"	: 	4, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
