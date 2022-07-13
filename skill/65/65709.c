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
	set_number(709);
	set_name("Thần Hành Hạng Liên Chế Tác");
	set_skill_level(56);
	set_tool(516);
	set_tili(4);
	set_final("/item/final/86/8056");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(2);
	set_base_rate(65);
        set_product( ([
	"60"	: 	2, 
	"39"	: 	3, 
	"93"	: 	2, 
	"102"	: 	3, 
	"323"	: 	3, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
