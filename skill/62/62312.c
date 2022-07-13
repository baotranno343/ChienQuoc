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
	set_number(312);
	set_name("Ngự Tràng Rèn");
	set_skill_level(55);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/76/1055");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"279"	: 	2, 
	"254"	: 	3, 
	"252"	: 	2, 
	"311"	: 	1, 
	"312"	: 	1, 
//	无	: 	0,            
        ])); 	
}
