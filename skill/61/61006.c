#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(610);
	set_skill_type(1);
	set_number(6);
	set_name("Cây Ngô Canh Đầu Bếp");
	set_skill_level(35);
	set_tool(0);
	set_tili(1);
	set_final("/item/final/33/1773");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(95);
        set_product( ([
	"144"	: 	1, 
	"171"	: 	1, 
	"221"	: 	1, 
//	无	: 	0, 
//	无	: 	0, 
//	无	: 	0,       	     
        ])); 	
        set_count(1);
}
