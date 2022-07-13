
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 0800; }

// 函数：构造处理
void create()
{
        set_name("三刀鬼");

        set_level(61);
	set_max_hp(1500);
	set_ap(410);
	set_dp(400);
	set_cp(100);
	set_pp(240);
	set_sp(180);
	set_walk_speed(4);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_16, 20) && !who->get_legend(TASK_16, 21) )
        {
		who->set_legend(TASK_16, 21);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,17,"临终寄托(完成)" );
		send_user(who, "%c%s",'!', "三刀鬼 1/1");
	}
}
   