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
	set_number(749);
	set_name("Tinh Tú Pháp Y Chế Tác");
	set_skill_level(97);
	set_tool(512);
	set_tili(4);
	set_final("/item/final/60/8097");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(2);
	set_base_rate(65);
        set_product( ([
	"54"	: 	5, 
	"63"	: 	3, 
	"218"	: 	2, 
	"310"	: 	2, 
	"323"	: 	3, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
