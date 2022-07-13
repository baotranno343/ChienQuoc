#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(6);
	set_number(65);
	set_name("Hàm Sa Xạ Ảnh Rèn");
	set_skill_level(75);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/71/1070");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"37"	: 	2, 
	"258"	: 	2, 
	"36"	: 	2, 
	"218"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
