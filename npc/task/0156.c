
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 0201; }

// 函数：构造处理
void create()
{
        set_name("无赖李小六");

        set_level(64);
	set_max_hp(1600);
	set_ap(410);
	set_dp(420);
	set_cp(100);
	set_pp(230);
	set_sp(180);
	set_walk_speed(4);
	set_attack_speed(12);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_18, 13) && !who->get_legend(TASK_18, 14) )
        {
		who->set_legend(TASK_18, 14);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,34,"长城上的烟火(完成)" );
		send_user(who, "%c%s",'!', "无赖李小六 1/1");
	}
}
   