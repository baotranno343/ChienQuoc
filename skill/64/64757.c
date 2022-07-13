#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(640);
	set_skill_type(3);
	set_number(757);
	set_name("Kỳ Lân Chiến Ngoa Chế Tác");
	set_skill_level(107);
	set_tool(512);
	set_tili(4);
	set_final("/item/final/88/8107");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(2);
	set_base_rate(65);
        set_product( ([
	"54"	: 	4, 
	"269"	: 	3, 
	"104"	: 	2, 
	"309"	: 	2, 
	"323"	: 	3, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
