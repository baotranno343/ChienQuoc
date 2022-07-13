
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;


// 函数：获取人物造型
int get_char_picid() { return 8000; }

// 函数：构造处理
void create()
{
        set_name("Trọng Phạm Hứa Hoành Đao");

        set_level(26);
	set_max_hp(500);
	set_ap(188);
	set_dp(100);
	set_cp(0);
	set_pp(120);
	set_sp(130);
	set_walk_speed(3);
	set_attack_speed(10);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}


void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_05, 4)&&!who->get_legend(TASK_05, 5) )
        {
		who->set_legend(TASK_05, 5);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,14,"明正刑典(完成)" );
		send_user(who, "%c%s",'!', "Trọng Phạm Hứa Hoành Đao 1/1");
	}	
}