
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 0200; }

// 函数：构造处理
void create()
{
        set_name("恶人武藏");

        set_level(44);
	set_max_hp(900);
	set_ap(300);
	set_dp(350);
	set_cp(100);
	set_pp(190);
	set_sp(140);
	set_walk_speed(3);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_11, 19) && !who->get_legend(TASK_11, 20) )
        {
		who->set_legend(TASK_11, 20);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,2,"无奈的求助（3）(完成)" );
		send_user(who, "%c%s",'!', "恶人武藏 1/1");
	}
}
