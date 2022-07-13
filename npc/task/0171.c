
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 4134; }

// 函数：构造处理
void create()
{
        set_name("僵尸李刃");

        set_level(87);
	set_max_hp(2400);
	set_ap(555);
	set_dp(546);
	set_cp(632);
	set_pp(296);
	set_sp(221);
	set_walk_speed(3);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_28, 4) && !who->get_legend(TASK_28, 5) )
        {
		who->set_legend(TASK_28, 5);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,46,"深入牧场(完成)" );
		USER_TASK_D->send_task_intro(who,2,TID_ZHAOGUO,46);
		send_user(who, "%c%s",'!', "僵尸李刃 1/1");
	}
}
