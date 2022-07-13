#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(5);
	set_number(64);
	set_name("Vô Cực Côn Rèn");
	set_skill_level(74);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/75/1070");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"22"	: 	3, 
	"257"	: 	3, 
	"36"	: 	2, 
	"218"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
