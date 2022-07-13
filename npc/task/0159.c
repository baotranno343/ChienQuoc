
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 0052; }

// 函数：构造处理
void create()
{
        set_name("恶霸张九");

        set_level(71);
	set_max_hp(1700);
	set_ap(460);
	set_dp(480);
	set_cp(100);
	set_pp(260);
	set_sp(180);
	set_walk_speed(4);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_21, 10) && !who->get_legend(TASK_21, 11) )
        {
		who->set_legend(TASK_21, 11);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,31,"铲除恶霸(完成)" );
		send_user(who, "%c%s",'!', "恶霸张九 1/1");
	}
}
   