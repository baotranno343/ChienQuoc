
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
        set_name("张大升");

        set_level(38);
	set_max_hp(720);
	set_ap(300);
	set_dp(290);
	set_cp(100);
	set_pp(160);
	set_sp(120);
	set_walk_speed(4);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_09, 1) && !who->get_legend(TASK_09, 2) )
        {
		who->set_legend(TASK_09, 2);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,23,"大孤山脚里的哭声(完成)" );
		send_user(who, "%c%s",'!', "张大升 1/1");
	}
        
}
