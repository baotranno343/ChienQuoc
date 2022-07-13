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
	set_number(720);
	set_name("Truy Phong Lý Chế Tác");
	set_skill_level(47);
	set_tool(511);
	set_tili(4);
	set_final("/item/final/88/8046");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(2);
	set_base_rate(65);
        set_product( ([
	"50"	: 	3, 
	"253"	: 	3, 
	"215"	: 	2, 
	"312"	: 	2, 
	"323"	: 	3, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
