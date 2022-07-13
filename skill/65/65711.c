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
	set_number(711);
	set_name("Lôi Thần Hạng Liên Chế Tác");
	set_skill_level(86);
	set_tool(517);
	set_tili(4);
	set_final("/item/final/86/8086");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(2);
	set_base_rate(65);
        set_product( ([
	"61"	: 	2, 
	"41"	: 	3, 
	"103"	: 	3, 
	"41"	: 	3, 
	"323"	: 	4, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
