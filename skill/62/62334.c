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
	set_number(334);
	set_name("Bạo Vũ Lê Hoa Châm Rèn");
	set_skill_level(85);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/71/1085");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"41"	: 	3, 
	"263"	: 	2, 
	"39"	: 	1, 
	"1832"	: 	1, 
	"310"	: 	1, 
//	无	: 	0,            
        ])); 	
}
