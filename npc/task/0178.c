
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 0252; }

// 函数：构造处理
void create()
{
        set_name("烈焰");

        set_level(97);
	set_max_hp(2920);
	set_ap(600);
	set_dp(573);
	set_cp(698);
	set_pp(372);
	set_sp(236);
	set_walk_speed(3);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_32, 20) && !who->get_legend(TASK_32, 21) )
        {
		who->set_legend(TASK_32, 21);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,47,"罪恶的源泉(完成)" );
		USER_TASK_D->send_task_intro(who,2,TID_YANGUO,47);
		send_user(who, "%c%s",'!', "烈焰 1/1");
	}
}
   