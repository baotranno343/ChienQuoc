#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>
inherit "/inh/std/vitaskill";

void create()
{	
	set_skill(%d);
	set_skill_type(%d);
	set_number(%d);
	set_name("%s");
	set_skill_level(%d);
	set_tool(%s);
	set_tili(%d);
	set_final(%s);
	set_skill_temp(%d);
	set_master("%s");
	set_skill_color(%d);
	set_base_rate(%d);
        set_product( ([
%s	%s	: 	%d, 
%s	%s	: 	%d, 
%s	%s	: 	%d, 
%s	%s	: 	%d, 
%s	%s	: 	%d, 
%s	%s	: 	%d,       	     
        ])); 	
        set_count(%d);
}
