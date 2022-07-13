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
	set_number(364);
	set_name("Thiên Xu Thương Rèn");
	set_skill_level(120);
	set_tool(502);
	set_tili(2);
	set_final("/item/final/74/1120");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(2);
	set_base_rate(75);
        set_product( ([
	"276"	: 	3, 
	"309"	: 	1, 
	"278"	: 	1, 
	"105"	: 	2, 
	"94"	: 	1, 
//	无	: 	0,            
        ])); 	
}
