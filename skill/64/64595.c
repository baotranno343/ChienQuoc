#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(640);
	set_skill_type(1);
	set_number(595);
	set_name("Hoàn Vũ Hành Trang Chế Tác");
	set_skill_level(85);
	set_tool(511);
	set_tili(1);
	set_final("/item/final/60/4085");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"52"	: 	4, 
	"191"	: 	3, 
	"32"	: 	3, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
