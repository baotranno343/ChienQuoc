
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 0902; }

// 函数：构造处理
void create()
{
        set_name("瘟神");

        set_level(105);
	set_max_hp(3478);
	set_ap(645);
	set_dp(600);
	set_pp(343);
	set_sp(251);
	set_walk_speed(4);
	set_attack_speed(13);
        set_max_seek(4);
        
        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_36, 14) && !who->get_legend(TASK_36, 15) )
        {
		who->set_legend(TASK_36, 15);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,54,"瘟疫之灾(完成)" );
		send_user(who, "%c%s",'!', "瘟神 1/1");
		USER_TASK_D->send_task_intro(who,2,TID_QIGUO,54);
	}
}
