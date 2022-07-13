
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 1051; }

// 函数：构造处理
void create()
{
        set_name("孤竹族使节");

        set_level(35);
	set_max_hp(740);
	set_ap(300);
	set_dp(290);
	set_cp(100);
	set_pp(200);
	set_sp(120);
	set_walk_speed(3);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_13, 19) && !who->get_legend(TASK_13, 20) )
        {
		who->set_legend(TASK_13, 20);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,7,"孤竹族使节（2）(完成)" );
		send_user(who, "%c%s",'!', "孤竹族使节 1/1");
	}
}
