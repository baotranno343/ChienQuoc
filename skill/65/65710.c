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
	set_number(710);
	set_name("Phong Thần Hạng Liên Chế Tác");
	set_skill_level(76);
	set_tool(516);
	set_tili(4);
	set_final("/item/final/86/8076");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(2);
	set_base_rate(65);
        set_product( ([
	"61"	: 	2, 
	"38"	: 	2, 
	"93"	: 	2, 
	"102"	: 	3, 
	"323"	: 	3, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
