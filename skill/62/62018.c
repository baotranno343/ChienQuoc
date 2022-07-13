#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(5);
	set_number(18);
	set_name("Văn Tu Côn Rèn");
	set_skill_level(31);
	set_tool(500);
	set_tili(1);
	set_final("/item/final/75/1030");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"315"	: 	2, 
	"247"	: 	2, 
	"35"	: 	1, 
	"32"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
