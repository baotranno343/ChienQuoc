#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(650);
	set_skill_type(1);
	set_number(82);
	set_name("Cường Hiệu Ngoại Kháng Chế Tác");
	set_skill_level(79);
	set_tool(516);
	set_tili(1);
	set_final("/item/final/15/1521");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"86"	: 	1, 
	"86"	: 	1, 
	"98"	: 	1, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
