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
	set_number(39);
	set_name("Ngân Xà Kiếm Rèn");
	set_skill_level(51);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/76/1050");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"252"	: 	2, 
	"279"	: 	1, 
	"254"	: 	2, 
	"240"	: 	2, 
	"32"	: 	1, 
//	无	: 	0,            
        ])); 	
}
