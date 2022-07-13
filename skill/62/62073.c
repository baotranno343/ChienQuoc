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
	set_number(73);
	set_name("Đại Hạ Long Tước Rèn");
	set_skill_level(84);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/72/1080");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"259"	: 	2, 
	"263"	: 	2, 
	"252"	: 	1, 
	"36"	: 	3, 
	"218"	: 	1, 
//	无	: 	0,            
        ])); 	
}
