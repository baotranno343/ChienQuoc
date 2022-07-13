#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(640);
	set_skill_type(1);
	set_number(531);
	set_name("Toả Liên Hành Trang Chế Tác");
	set_skill_level(55);
	set_tool(511);
	set_tili(1);
	set_final("/item/final/60/2055");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"50"	: 	4, 
	"190"	: 	4, 
	"73"	: 	1, 
	"312"	: 	1, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
