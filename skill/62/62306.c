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
	set_number(306);
	set_name("Liệt Viêm Kiếm Rèn");
	set_skill_level(45);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/76/1045");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"254"	: 	2, 
	"252"	: 	2, 
	"82"	: 	2, 
	"312"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
