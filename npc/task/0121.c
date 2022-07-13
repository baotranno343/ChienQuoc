
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 0702; }

// 函数：构造处理
void create()
{
        set_name("巫山精灵");

        set_level(35);
	set_max_hp(640);
	set_ap(270);
	set_dp(260);
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
        if ( objectp(who) && who->get_legend(TASK_08, 4)&&!who->get_legend(TASK_08, 5) )
        {
		who->set_legend(TASK_08, 5);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,14,"山谷解迷(完成)" );
		send_user(who, "%c%s",'!', "巫山精灵 1/1");
	}
        
}
