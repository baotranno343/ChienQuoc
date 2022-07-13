
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
        set_name("土匪马大");

        set_level(83);
	set_max_hp(2500);
	set_ap(540);
	set_dp(530);
	set_cp(100);
	set_pp(300);
	set_sp(220);
	set_walk_speed(3);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_26, 17) && !who->get_legend(TASK_26, 18) )
        {
		who->set_legend(TASK_26, 18);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,34,"为民除害(完成)" );
		send_user(who, "%c%s",'!', "土匪马大 1/1");
		USER_TASK_D->send_task_intro(who,2,TID_HANGUO,34);
		
	}
}
   