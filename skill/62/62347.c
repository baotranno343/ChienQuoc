#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(1);
	set_number(347);
	set_name("Toản Thạch Tinh Trần Rèn");
	set_skill_level(105);
	set_tool(502);
	set_tili(2);
	set_final("/item/final/70/1105");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"267"	: 	4, 
	"52"	: 	4, 
	"272"	: 	1, 
	"310"	: 	1, 
//	无	: 	0,    	
//	无	: 	0,            
        ])); 	
}
