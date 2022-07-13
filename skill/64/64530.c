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
	set_number(530);
	set_name("Cương Thiết Hộ Tâm Giáp Chế Tác");
	set_skill_level(55);
	set_tool(511);
	set_tili(1);
	set_final("/item/final/60/3055");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"48"	: 	4, 
	"279"	: 	2, 
	"50"	: 	4, 
	"312"	: 	1, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
