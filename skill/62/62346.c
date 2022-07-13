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
	set_number(346);
	set_name("Huyền Thiết Tụ Lý Tiễn Rèn");
	set_skill_level(105);
	set_tool(502);
	set_tili(2);
	set_final("/item/final/71/1105");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"43"	: 	2, 
	"268"	: 	2, 
	"1837"	: 	1, 
	"42"	: 	1, 
	"310"	: 	1, 
//	无	: 	0,            
        ])); 	
}
