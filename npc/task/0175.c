
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
        set_name("劫匪马小七");

        set_level(93);
	set_max_hp(2900);
	set_ap(590);
	set_dp(560);
	set_cp(100);
	set_pp(330);
	set_sp(120);
	set_walk_speed(4);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_30, 27) && !who->get_legend(TASK_30, 28) )
        {
		who->set_legend(TASK_30, 28);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,43,"除掉恶匪(完成)" );
		send_user(who, "%c%s",'!', "劫匪马小七 1/1");
	}
}
   