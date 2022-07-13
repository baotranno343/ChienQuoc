#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(610);
	set_skill_type(1);
	set_number(8);
	set_name("Trứng Chim Nóng Đầu Bếp");
	set_skill_level(45);
	set_tool(0);
	set_tili(1);
	set_final("/item/final/33/1774");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(95);
        set_product( ([
	"171"	: 	2, 
	"221"	: 	1, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
