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
	set_number(338);
	set_name("Hào Long Đảm Rèn");
	set_skill_level(95);
	set_tool(502);
	set_tili(1);
	set_final("/item/final/74/1095");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"266"	: 	3, 
	"279"	: 	3, 
	"309"	: 	1, 
	"104"	: 	1, 
	"310"	: 	1, 
//	无	: 	0,            
        ])); 	
}
