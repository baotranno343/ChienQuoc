#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(620);
	set_skill_type(3);
	set_number(63);
	set_name("Trượng Bát Xà Mâu Rèn");
	set_skill_level(73);
	set_tool(501);
	set_tili(1);
	set_final("/item/final/74/1070");
	set_skill_temp(0);
	set_master("0");
	set_skill_color(0);
	set_base_rate(75);
        set_product( ([
	"286"	: 	3, 
	"259"	: 	3, 
	"283"	: 	1, 
	"218"	: 	1, 
//	无	: 	0, 
//	无	: 	0,            
        ])); 	
}
