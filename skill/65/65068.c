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
	set_number(68);
	set_name("Cường Hiệu Ngoại Công Chế Tác");
	set_skill_level(66);
	set_tool(516);
	set_tili(1);
	set_final("/item/final/15/1518");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"84"	: 	1, 
	"102"	: 	1, 
	"73"	: 	1, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
