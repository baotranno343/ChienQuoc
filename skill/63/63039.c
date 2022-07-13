#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(630);
	set_skill_type(1);
	set_number(39);
	set_name("Thiên Hương Tục Mệnh Tán Luyện Chế");
	set_skill_level(80);
	set_tool(507);
	set_tili(1);
	set_final("/item/final/91/1814");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"307"	: 	2, 
	"306"	: 	4, 
	"308"	: 	2, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
