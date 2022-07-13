#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(640);
	set_skill_type(2);
	set_number(668);
	set_name("Thiên Toàn Đấu Lạp Chế Tác");
	set_skill_level(115);
	set_tool(512);
	set_tili(2);
	set_final("/item/final/65/4115");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"54"	: 	3, 
	"272"	: 	2, 
	"28"	: 	2, 
	"89"	: 	1, 
	"309"	: 	1, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
