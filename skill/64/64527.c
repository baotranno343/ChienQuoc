#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(640);
	set_skill_type(3);
	set_number(527);
	set_name("Ngân Ty Trường Ngoa Chế Tác");
	set_skill_level(45);
	set_tool(511);
	set_tili(1);
	set_final("/item/final/88/3045");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"48"	: 	5, 
	"254"	: 	2, 
	"50"	: 	4, 
	"215"	: 	1, 
	"312"	: 	1, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
