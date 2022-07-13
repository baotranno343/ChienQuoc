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
	set_number(337);
	set_name("Phá Phong Đao Rèn");
	set_skill_level(95);
	set_tool(502);
	set_tili(1);
	set_final("/item/final/72/1095");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"264"	: 	2, 
	"258"	: 	2, 
	"309"	: 	1, 
	"64"	: 	1, 
	"310"	: 	1, 
//	无	: 	0,            
        ])); 	
}
