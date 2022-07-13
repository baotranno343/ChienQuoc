
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 0053; }

// 函数：构造处理
void create()
{
        set_name("赵讯");

        set_level(77);
	set_max_hp(1812);
	set_ap(495);
	set_dp(516);
	set_cp(560);
	set_pp(275);
	set_sp(204);
	set_walk_speed(4);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_23, 27) && !who->get_legend(TASK_23, 28) )
        {
		who->set_legend(TASK_23, 28);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,40,"武士的爱情（3）(完成)" );
		send_user(who, "%c%s",'!', "赵讯 1/1");
		USER_TASK_D->send_task_intro(who,2,TID_ZHAOGUO,40);
		
	}
}
   