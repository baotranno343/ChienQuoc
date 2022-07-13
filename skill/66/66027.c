#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(660);
	set_skill_type(1);
	set_number(27);
	set_name("Chìa Khoá Ngân");
	set_skill_level(50);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/16/1615");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"280"	: 	1, 
//	ÎÞ	: 	0, 
//	ÎÞ	: 	0, 
//	ÎÞ	: 	0, 
//	ÎÞ	: 	0, 
//	ÎÞ	: 	0,       	     
        ])); 	
        set_count(1);
}
