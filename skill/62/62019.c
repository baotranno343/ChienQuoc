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
	set_number(19);
	set_name("Trường Kích Rèn");
	set_skill_level(32);
	set_tool(500);
	set_tili(1);
	set_final("/item/final/74/1030");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"251"	: 	2, 
	"249"	: 	2, 
	"35"	: 	1, 
	"32"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
