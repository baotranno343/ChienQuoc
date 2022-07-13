#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(3);
	set_number(326);
	set_name("Long Tiêm Thương Rèn");
	set_skill_level(75);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/74/1075");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"286"	: 	3, 
	"259"	: 	3, 
	"283"	: 	1, 
	"103"	: 	1, 
	"310"	: 	1, 
//	无	: 	0,            
        ])); 	
}
