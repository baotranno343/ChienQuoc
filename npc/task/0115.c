
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
        set_name("李大山");

        set_level(27);
	set_max_hp(580);
	set_ap(180);
	set_dp(200);
	set_cp(140);
	set_pp(150);
	set_sp(110);
	set_walk_speed(3);
	set_attack_speed(15);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_05, 25)&&!who->get_legend(TASK_05, 26) )
        {
		who->set_legend(TASK_05, 26);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,17,"遗忘的誓言(完成)" );
		send_user(who, "%c%s",'!', "李大山 1/1");
	}	
}