#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(650);
	set_skill_type(2);
	set_number(713);
	set_name("Tinh Tú Hạng Liên Chế Tác");
	set_skill_level(106);
	set_tool(517);
	set_tili(4);
	set_final("/item/final/86/8106");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(2);
	set_base_rate(65);
        set_product( ([
	"64"	: 	2, 
	"269"	: 	3, 
	"86"	: 	2, 
	"83"	: 	2, 
	"323"	: 	4, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
