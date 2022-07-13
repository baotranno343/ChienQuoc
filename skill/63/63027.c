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
	set_number(27);
	set_name("Thanh Tâm Đan Luyện Chế");
	set_skill_level(68);
	set_tool(507);
	set_tili(1);
	set_final("/item/91/9145");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"120"	: 	2, 
	"300"	: 	1, 
	"299"	: 	2, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
