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
	set_number(708);
	set_name("Truy Phong Hạng Liên Chế Tác");
	set_skill_level(46);
	set_tool(516);
	set_tili(4);
	set_final("/item/final/86/8046");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(2);
	set_base_rate(65);
        set_product( ([
	"59"	: 	2, 
	"40"	: 	2, 
	"93"	: 	2, 
	"101"	: 	3, 
	"323"	: 	3, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
