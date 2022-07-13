
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 0201; }

// 函数：构造处理
void create()
{
        set_name("梁少");

        set_level(99);
	set_max_hp(3004);
	set_ap(615);
	set_dp(582);
	set_cp(719);
	set_pp(329);
	set_sp(241);
	set_walk_speed(4);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_33, 16) && !who->get_legend(TASK_33, 17) )
        {
		who->set_legend(TASK_33, 17);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,38,"惩戒梁少(完成)" );
		send_user(who, "%c%s",'!', "梁少 1/1");
	}
}
