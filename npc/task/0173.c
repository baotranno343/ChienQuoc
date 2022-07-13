
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 1001; }

// 函数：构造处理
void create()
{
        set_name("刺客李武");

        set_level(89);
	set_max_hp(2456);
	set_ap(565);
	set_dp(552);
	set_cp(647);
	set_pp(300);
	set_sp(225);
	set_walk_speed(3);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_29, 1) && !who->get_legend(TASK_29, 2) )
        {
		who->set_legend(TASK_29, 2);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,53,"秘密行动(完成)" );
		send_user(who, "%c%s",'!', "刺客李武 1/1");
	}
}
   