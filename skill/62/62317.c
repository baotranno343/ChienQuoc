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
	set_number(317);
	set_name("Hổ Trảo Quyền Sáo Rèn");
	set_skill_level(55);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/70/1055");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"277"	: 	4, 
	"40"	: 	4, 
	"48"	: 	3, 
	"312"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
