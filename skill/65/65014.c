#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(650);
	set_skill_type(2);
	set_number(14);
	set_name("Kim Hạng Liên Chế Tác");
	set_skill_level(25);
	set_tool(515);
	set_tili(1);
	set_final("/item/final/86/5020");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"57"	: 	1, 
	"78"	: 	1, 
	"79"	: 	1, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
