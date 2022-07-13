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
	set_number(171);
	set_name("Phi Thiên Chiến Khôi Chế Tác");
	set_skill_level(93);
	set_tool(512);
	set_tili(1);
	set_final("/item/final/65/3090");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"54"	: 	2, 
	"264"	: 	1, 
	"191"	: 	1, 
	"241"	: 	1, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
