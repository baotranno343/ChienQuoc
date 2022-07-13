#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(2);
	set_number(100);
	set_name("Trảm Yêu Khấp Huyết Rèn");
	set_skill_level(105);
	set_tool(502);
	set_tili(1);
	set_final("/item/final/72/1100");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"269"	: 	2, 
	"263"	: 	2, 
	"241"	: 	1, 
	"320"	: 	1, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
