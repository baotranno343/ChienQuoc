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
	set_number(701);
	set_name("Hư Minh Hạng Liên Chế Tác");
	set_skill_level(120);
	set_tool(517);
	set_tili(2);
	set_final("/item/final/86/1120");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(2);
	set_base_rate(75);
        set_product( ([
	"67"	: 	1, 
	"94"	: 	1, 
	"1761"	: 	2, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
