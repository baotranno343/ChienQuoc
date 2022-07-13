#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(660);
	set_skill_type(1);
	set_number(46);
	set_name("Hỗn Thiên Nghi Chế Tác");
	set_skill_level(74);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/16/1629");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"1609"	: 	1, 
	"1626"	: 	2, 
	"1614"	: 	1, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
