#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(680);
	set_skill_type(1);
	set_number(21);
	set_name("Phiên Hồng Hoa Gia Công");
	set_skill_level(80);
	set_tool(0);
	set_tili(1);
	set_final("/item/stuff/0307");
	set_skill_temp(0);
	set_master("Chủ Tiệm Y Dược");
	set_skill_color(0);
	set_base_rate(100);
        set_product( ([
	"129"	: 	1, 
//		: 	0, 
//		: 	0, 
//		: 	0, 
//		: 	0, 
//		: 	0,            
        ])); 	
}
