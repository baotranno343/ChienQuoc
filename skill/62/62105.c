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
	set_number(105);
	set_name("Minh Quang Thị Hồn Rèn");
	set_skill_level(115);
	set_tool(502);
	set_tili(1);
	set_final("/item/final/76/1110");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"269"	: 	2, 
	"262"	: 	2, 
	"248"	: 	1, 
	"274"	: 	1, 
	"241"	: 	1, 
	"320"	: 	1,       	     
        ])); 	
        set_count(1);
}
