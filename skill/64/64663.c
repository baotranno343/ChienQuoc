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
	set_number(663);
	set_name("Thiên Cương Chiến Khôi Chế Tác");
	set_skill_level(115);
	set_tool(512);
	set_tili(2);
	set_final("/item/final/65/3115");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"54"	: 	3, 
	"274"	: 	2, 
	"26"	: 	2, 
	"320"	: 	1, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
