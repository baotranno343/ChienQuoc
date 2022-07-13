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
	set_number(723);
	set_name("Truy Phong Pháp Quán Chế Tác");
	set_skill_level(47);
	set_tool(511);
	set_tili(4);
	set_final("/item/final/65/8046");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(2);
	set_base_rate(65);
        set_product( ([
	"50"	: 	5, 
	"190"	: 	3, 
	"239"	: 	5, 
	"215"	: 	2, 
	"323"	: 	3, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
