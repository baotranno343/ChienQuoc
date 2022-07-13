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
	set_number(350);
	set_name("Phương Thiên Kích Rèn");
	set_skill_level(115);
	set_tool(502);
	set_tili(2);
	set_final("/item/final/74/1115");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"309"	: 	1, 
	"264"	: 	3, 
	"283"	: 	1, 
	"104"	: 	2, 
	"24"	: 	1, 
//	无	: 	0,            
        ])); 	
}
