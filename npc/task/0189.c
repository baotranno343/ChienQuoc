
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
        set_name("刺客徐四");

        set_level(112);
	set_max_hp(2500);
	set_ap(680);
	set_dp(600);
	set_cp(100);
	set_pp(360);
	set_sp(260);
	set_walk_speed(3);
	set_attack_speed(13);
        set_max_seek(4);
        
        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_42, 15) && !who->get_legend(TASK_42, 16) )
        {
		who->set_legend(TASK_42, 16);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,80,"除掉刺客(完成)" );
		send_user(who, "%c%s",'!', "刺客徐四 1/1");
	}
}
