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
	set_number(341);
	set_name("Băng Tinh Lung Thủ Rèn");
	set_skill_level(95);
	set_tool(502);
	set_tili(1);
	set_final("/item/final/70/1095");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"262"	: 	3, 
	"41"	: 	1, 
	"52"	: 	4, 
	"310"	: 	1, 
//	无	: 	0,     
//	无	: 	0,           
        ])); 	
}
