
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
        set_name("许子高");

        set_level(74);
	set_max_hp(2000);
	set_ap(490);
	set_dp(510);
	set_cp(100);
	set_pp(290);
	set_sp(210);
	set_walk_speed(4);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_22, 5) && !who->get_legend(TASK_22, 6) )
        {
		who->set_legend(TASK_22, 6);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,42,"真相大白(完成)" );
		send_user(who, "%c%s",'!', "许子高 1/1");
	}
}
   