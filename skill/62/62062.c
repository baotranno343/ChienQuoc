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
	set_number(62);
	set_name("Bách Thắng Đao Rèn");
	set_skill_level(72);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/72/1070");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"259"	: 	2, 
	"283"	: 	2, 
	"247"	: 	1, 
	"218"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
