#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(4);
	set_number(318);
	set_name("Vũ Lộ Kiếm Rèn");
	set_skill_level(65);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/76/1065");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"259"	: 	2, 
	"257"	: 	2, 
	"243"	: 	1, 
	"84"	: 	1, 
	"312"	: 	1, 
//	无	: 	0,            
        ])); 	
}
