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
	set_number(28);
	set_name("Phá Giáp Châm Rèn");
	set_skill_level(40);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/71/1040");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"40"	: 	2, 
	"253"	: 	1, 
	"252"	: 	1, 
	"240"	: 	1, 
	"32"	: 	1, 
//	无	: 	0,            
        ])); 	
}
