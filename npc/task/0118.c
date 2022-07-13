
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
        set_name("胡子山");

        set_level(28);
	set_max_hp(800);
	set_ap(188);
	set_dp(130);
	set_cp(140);
	set_pp(130);
	set_sp(90);
	set_walk_speed(3);
	set_attack_speed(15);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_06, 10)&&!who->get_legend(TASK_06, 11) )
        {
		who->set_legend(TASK_06, 11);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,22,"遥远的梦想(完成)" );
		send_user(who, "%c%s",'!', "胡子山 1/1");
	}	
}