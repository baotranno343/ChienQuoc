#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(1);
	set_number(329);
	set_name("Thiên Mã Lưu Tinh Rèn");
	set_skill_level(75);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/70/1075");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"257"	: 	1, 
	"282"	: 	3, 
	"37"	: 	3, 
	"52"	: 	2, 
	"310"	: 	1, 
//	无	: 	0,            
        ])); 	
}
