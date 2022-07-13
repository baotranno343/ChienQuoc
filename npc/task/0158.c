
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 0200; }

// 函数：构造处理
void create()
{
        set_name("恶霸秦老四");

        set_level(70);
	set_max_hp(1600);
	set_ap(450);
	set_dp(480);
	set_cp(100);
	set_pp(250);
	set_sp(180);
	set_walk_speed(4);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_20, 27) && !who->get_legend(TASK_20, 28) )
        {
		who->set_legend(TASK_20, 28);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,26,"扫清障碍(完成)" );
		send_user(who, "%c%s",'!', "恶霸秦老四 1/1");
	}
}
   