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
	set_number(333);
	set_name("Cửu Hoàn Kim Liên Côn Rèn");
	set_skill_level(85);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/75/1085");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"317"	: 	3, 
	"282"	: 	3, 
	"277"	: 	1, 
	"63"	: 	2, 
	"310"	: 	1, 
//	无	: 	0,            
        ])); 	
}
