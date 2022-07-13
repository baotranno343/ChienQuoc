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
	set_number(613);
	set_name("Đế Vương Chi Khải Chế Tác");
	set_skill_level(95);
	set_tool(512);
	set_tili(1);
	set_final("/item/final/60/1095");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"54"	: 	4, 
	"264"	: 	2, 
	"218"	: 	1, 
	"310"	: 	1, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
