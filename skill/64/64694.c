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
	set_number(694);
	set_name("Tinh Thần Chiến Ngoa Chế Tác");
	set_skill_level(120);
	set_tool(512);
	set_tili(2);
	set_final("/item/final/88/1120");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"54"	: 	4, 
	"274"	: 	3, 
	"30"	: 	3, 
	"66"	: 	2, 
	"310"	: 	5, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
