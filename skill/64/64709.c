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
	set_number(709);
	set_name("Long Cốt Cân Chế  Tác");
	set_skill_level(119);
	set_tool(512);
	set_tili(2);
	set_final("/item/final/65/2119");
	set_skill_temp(1);
	set_master("0");
	set_skill_color(1);
	set_base_rate(75);
        set_product( ([
	"54"	: 	4, 
	"272"	: 	3, 
	"28"	: 	3, 
	"309"	: 	5, 
	"130"	: 	5, 
	"94"	: 	1,       	     
        ])); 	
        set_count(1);
}
