#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(640);
	set_skill_type(3);
	set_number(763);
	set_name("Long Thần Chiến Ngoa Chế Tác");
	set_skill_level(117);
	set_tool(512);
	set_tili(4);
	set_final("/item/final/88/8116");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(2);
	set_base_rate(65);
        set_product( ([
	"54"	: 	4, 
	"274"	: 	3, 
	"30"	: 	3, 
	"66"	: 	2, 
	"323"	: 	3, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
