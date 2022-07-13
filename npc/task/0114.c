
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;


// 函数：获取人物造型
int get_char_picid() { return 1051; }

// 函数：构造处理
void create()
{
        set_name("赵术士");

        set_level(27);
	set_max_hp(600);
	set_ap(200);
	set_dp(195);
	set_cp(110);
	set_pp(180);
	set_sp(80);
	set_walk_speed(3);
	set_attack_speed(15);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_05, 22)&&!who->get_legend(TASK_05, 23) )
        {
		who->set_legend(TASK_05, 23);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,16,"沉默的剑魂(完成)" );
		send_user(who, "%c%s",'!', "赵术士 1/1");
	}	
}