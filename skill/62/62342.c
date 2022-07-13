#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(4);
	set_number(342);
	set_name("Xích Tiêu Rèn");
	set_skill_level(105);
	set_tool(502);
	set_tili(2);
	set_final("/item/final/76/1105");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"269"	: 	2, 
	"262"	: 	2, 
	"88"	: 	1, 
	"274"	: 	1, 
	"310"	: 	1, 
//	无	: 	0,            
        ])); 	
}
