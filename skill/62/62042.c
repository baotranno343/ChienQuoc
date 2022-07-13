#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(3);
	set_number(42);
	set_name("Độc Nha Thương Rèn");
	set_skill_level(54);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/74/1050");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"254"	: 	3, 
	"281"	: 	3, 
	"240"	: 	2, 
	"32"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
