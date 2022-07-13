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
	set_number(357);
	set_name("Thiên Quyền Côn Rèn");
	set_skill_level(120);
	set_tool(502);
	set_tili(2);
	set_final("/item/final/75/1120");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"24"	: 	3, 
	"309"	: 	1, 
	"267"	: 	1, 
	"67"	: 	1, 
	"94"	: 	1, 
//	无	: 	0,            
        ])); 	
}
