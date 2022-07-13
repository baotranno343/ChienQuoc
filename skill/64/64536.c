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
	set_number(536);
	set_name("Dương Giác Đầu Khôi Chế Tác");
	set_skill_level(55);
	set_tool(511);
	set_tili(1);
	set_final("/item/final/65/1055");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"48"	: 	4, 
	"279"	: 	3, 
	"50"	: 	4, 
	"312"	: 	1, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
