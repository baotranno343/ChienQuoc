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
	set_number(108);
	set_name("Chấn Thiên Rèn");
	set_skill_level(118);
	set_tool(502);
	set_tili(1);
	set_final("/item/final/75/1110");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"321"	: 	3, 
	"282"	: 	3, 
	"262"	: 	1, 
	"24"	: 	1, 
	"241"	: 	1, 
	"320"	: 	1,       	     
        ])); 	
        set_count(1);
}
