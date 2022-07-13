
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
        set_name("心之魔");

        set_level(61);
	set_max_hp(1600);
	set_ap(390);
	set_dp(400);
	set_cp(100);
	set_pp(240);
	set_sp(170);
	set_walk_speed(3);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_16, 17) && !who->get_legend(TASK_16, 18) )
        {
		who->set_legend(TASK_16, 18);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,16,"恶魔来临(完成)" );
		send_user(who, "%c%s",'!', "心之魔 1/1");
	}
}
   