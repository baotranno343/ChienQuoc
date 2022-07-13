#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(640);
	set_skill_type(2);
	set_number(86);
	set_name("Cản Nhật Đầu Cân Chế Tác");
	set_skill_level(54);
	set_tool(511);
	set_tili(1);
	set_final("/item/final/65/4050");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"48"	: 	2, 
	"190"	: 	4, 
	"240"	: 	1, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
