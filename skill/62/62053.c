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
	set_number(53);
	set_name("Truy Tâm Tiễn Rèn");
	set_skill_level(64);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/71/1060");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"38"	: 	2, 
	"258"	: 	2, 
	"36"	: 	1, 
	"218"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
