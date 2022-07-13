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
	set_number(766);
	set_name("Thiên Tôn Thần Khải Chế Tác");
	set_skill_level(127);
	set_tool(512);
	set_tili(4);
	set_final("/item/final/60/8127");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(2);
	set_base_rate(65);
        set_product( ([
	"54"	: 	8, 
	"195"	: 	7, 
	"218"	: 	4, 
	"310"	: 	4, 
	"323"	: 	3, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
