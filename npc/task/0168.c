
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 0251; }

// 函数：构造处理
void create()
{
        set_name("奸贼武之真");

        set_level(81);
	set_max_hp(2300);
	set_ap(530);
	set_dp(520);
	set_cp(100);
	set_pp(290);
	set_sp(210);
	set_walk_speed(3);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_25, 22) && !who->get_legend(TASK_25, 23) )
        {
		who->set_legend(TASK_25, 23);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,23,"清除奸贼(完成)" );
		send_user(who, "%c%s",'!', "奸贼武之真 1/1");
		USER_TASK_D->send_task_intro(who,2,TID_HANGUO,23);
		
	}
}
   