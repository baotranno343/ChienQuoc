
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 0802; }

// 函数：构造处理
void create()
{
        set_name("骨魔精");

        set_level(39);
	set_max_hp(800);
	set_ap(320);
	set_dp(300);
	set_cp(100);
	set_pp(180);
	set_sp(120);
	set_walk_speed(4);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_09, 13) && !who->get_legend(TASK_09, 14) )
        {
		who->set_legend(TASK_09, 14);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,27,"龙骨坡的遗骸(完成)" );
		send_user(who, "%c%s",'!', "骨魔精 1/1");
	}
        
}
