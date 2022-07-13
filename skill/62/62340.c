#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(6);
	set_number(340);
	set_name("Đoạn Hồn Sa Rèn");
	set_skill_level(95);
	set_tool(502);
	set_tili(1);
	set_final("/item/final/71/1095");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"41"	: 	2, 
	"263"	: 	2, 
	"1832"	: 	2, 
	"310"	: 	1, 
//	无	: 	0,    	
//	无	: 	0,            
        ])); 	
}
