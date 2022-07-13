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
	set_number(507);
	set_name("Hộ Mệnh Hạng Liên Chế Tác");
	set_skill_level(25);
	set_tool(515);
	set_tili(1);
	set_final("/item/final/86/6025");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"56"	: 	1, 
	"79"	: 	1, 
	"243"	: 	1, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
