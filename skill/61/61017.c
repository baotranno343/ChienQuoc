#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(610);
	set_skill_type(1);
	set_number(17);
	set_name("Thần Bí Qủa Đầu Bếp");
	set_skill_level(80);
	set_tool(0);
	set_tili(2);
	set_final("/item/final/33/1770");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(95);
        set_product( ([
	"218"	: 	1, 
	"310"	: 	1, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
