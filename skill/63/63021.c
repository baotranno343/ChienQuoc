#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(630);
	set_skill_type(1);
	set_number(21);
	set_name("Tử Thiến Đơn Luyện Chế");
	set_skill_level(57);
	set_tool(506);
	set_tili(1);
	set_final("/item/final/91/1810");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"296"	: 	2, 
	"297"	: 	1, 
	"295"	: 	1, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
