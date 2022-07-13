#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(7);
	set_number(26);
	set_name("Thanh Đồng Ti Rèn");
	set_skill_level(39);
	set_tool(500);
	set_tili(0);
	set_final("/item/stuff/0040");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(95);
        set_product( ([
	"216"	: 	1, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
