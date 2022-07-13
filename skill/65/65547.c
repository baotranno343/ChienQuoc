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
	set_number(547);
	set_name("Huyền Nguyệt Hạng Liên Chế Tác");
	set_skill_level(85);
	set_tool(517);
	set_tili(1);
	set_final("/item/final/86/7085");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"1835"	: 	1, 
	"63"	: 	1, 
	"62"	: 	1, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
