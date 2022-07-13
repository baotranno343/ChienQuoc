#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(4);
	set_number(305);
	set_name("Huyền Hoàng Kiếm Rèn");
	set_skill_level(35);
	set_tool(500);
	set_tili(1);
	set_final("/item/final/76/1035");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"249"	: 	2, 
	"247"	: 	2, 
	"81"	: 	2, 
	"311"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
