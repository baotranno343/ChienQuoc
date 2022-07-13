#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(2);
	set_number(89);
	set_name("Phá Không Đao Rèn");
	set_skill_level(94);
	set_tool(502);
	set_tili(1);
	set_final("/item/final/72/1090");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"264"	: 	2, 
	"258"	: 	2, 
	"252"	: 	1, 
	"241"	: 	1, 
	"320"	: 	1, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
