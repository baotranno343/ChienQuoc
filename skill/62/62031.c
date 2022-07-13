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
	set_number(31);
	set_name("Tướng Quân Côn Rèn");
	set_skill_level(44);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/75/1040");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"316"	: 	2, 
	"252"	: 	2, 
	"240"	: 	1, 
	"32"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
