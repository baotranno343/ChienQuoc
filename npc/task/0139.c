
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 0752; }

// 函数：构造处理
void create()
{
        set_name("迷失鬼");

        set_level(53);
	set_max_hp(1100);
	set_ap(380);
	set_dp(390);
	set_cp(100);
	set_pp(200);
	set_sp(160);
	set_walk_speed(4);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_12, 28) && !who->get_legend(TASK_12, 29) )
        {
		who->set_legend(TASK_12, 29);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,10,"众说纷纭(完成)" );
		send_user(who, "%c%s",'!', "迷失鬼 1/1");
	}
}
