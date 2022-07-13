#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(2);
	set_number(307);
	set_name("Hải Hồn Đao Rèn");
	set_skill_level(45);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/72/1045");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"249"	: 	3, 
	"248"	: 	3, 
	"59"	: 	1, 
	"312"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
