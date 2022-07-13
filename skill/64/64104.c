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
	set_number(104);
	set_name("Thuý Ngọc Bào Chế Tác");
	set_skill_level(63);
	set_tool(511);
	set_tili(1);
	set_final("/item/final/60/5060");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"50"	: 	2, 
	"259"	: 	2, 
	"52"	: 	1, 
	"36"	: 	1, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
