
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 0752; }

// 函数：构造处理
void create()
{
        set_name("夜浮鬼");

        set_level(37);
	set_max_hp(700);
	set_ap(300);
	set_dp(310);
	set_cp(100);
	set_pp(160);
	set_sp(120);
	set_walk_speed(4);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_08, 25) && !who->get_legend(TASK_08, 26) )
        {
		who->set_legend(TASK_08, 26);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,21,"湘妃林的鬼火(完成)" );
		send_user(who, "%c%s",'!', "夜浮鬼 1/1");
	}
}
