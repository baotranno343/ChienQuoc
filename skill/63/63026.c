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
	set_number(26);
	set_name("Tiêu Dao Tán Luyện Chế");
	set_skill_level(67);
	set_tool(507);
	set_tili(1);
	set_final("/item/91/9162");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"120"	: 	1, 
	"300"	: 	1, 
	"299"	: 	1, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
