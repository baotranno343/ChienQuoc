
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 0201; }

// 函数：构造处理
void create()
{
        set_name("奸细石七");

        set_level(72);
	set_max_hp(1800);
	set_ap(470);
	set_dp(490);
	set_cp(100);
	set_pp(270);
	set_sp(190);
	set_walk_speed(4);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_21, 17) && !who->get_legend(TASK_21, 18) )
        {
		who->set_legend(TASK_21, 18);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,34,"出使之难(完成)" );
		send_user(who, "%c%s",'!', "奸细石七 1/1");
	}
}
   