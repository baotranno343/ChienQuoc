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
	set_number(8);
	set_name("Ổ Trục Gỗ Chế Tác");
	set_skill_level(25);
	set_tool(500);
	set_tili(0);
	set_final("/item/final/16/1604");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"1603"	: 	1, 
	"245"	: 	2, 
	"246"	: 	1, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
