
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;


// 函数：获取人物造型
int get_char_picid() { return 0252; }

// 函数：构造处理
void create()
{
        set_name("Mã Đại Long");

        set_level(24);
	set_max_hp(250);
	set_ap(150);
	set_dp(160);
	set_cp(140);
	set_pp(130);
	set_sp(90);
	set_walk_speed(4);
	set_attack_speed(15);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_05, 7)&&!who->get_legend(TASK_05, 8) )
        {
		who->set_legend(TASK_05, 8);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,13,"招摇撞骗(完成)" );
		send_user(who, "%c%s",'!', "Mã Đại Long 1/1");
	}	
}