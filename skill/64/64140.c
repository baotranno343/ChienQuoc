#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(640);
	set_skill_type(7);
	set_number(140);
	set_name("Túi Bách Bảo Chế Tác");
	set_skill_level(80);
	set_tool(511);
	set_tili(1);
	set_final("/item/std/6006");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"52"	: 	5, 
	"36"	: 	5, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
