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
	set_number(743);
	set_name("Thần Uy Thánh Bào Chế Tác");
	set_skill_level(87);
	set_tool(511);
	set_tili(4);
	set_final("/item/final/60/8086");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(2);
	set_base_rate(65);
        set_product( ([
	"52"	: 	5, 
	"191"	: 	4, 
	"32"	: 	4, 
//	无	: 	0, 
	"323"	: 	3, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
