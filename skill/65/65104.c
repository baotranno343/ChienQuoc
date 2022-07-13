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
	set_number(104);
	set_name("Cực Hiệu Ngoại Công Chế Tác");
	set_skill_level(100);
	set_tool(517);
	set_tili(2);
	set_final("/item/final/15/1525");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"64"	: 	1, 
	"65"	: 	1, 
	"75"	: 	1, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
