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
	set_number(40);
	set_name("Thanh Độc Đao Rèn");
	set_skill_level(52);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/72/1050");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"252"	: 	2, 
	"278"	: 	2, 
	"240"	: 	2, 
	"32"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
