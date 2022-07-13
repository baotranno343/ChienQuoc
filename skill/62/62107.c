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
	set_number(107);
	set_name("Minh Quang Hàn Kích Rèn");
	set_skill_level(117);
	set_tool(502);
	set_tili(1);
	set_final("/item/final/74/1110");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"271"	: 	3, 
	"264"	: 	3, 
	"283"	: 	1, 
	"24"	: 	1, 
	"241"	: 	1, 
	"320"	: 	1,       	     
        ])); 	
        set_count(1);
}
