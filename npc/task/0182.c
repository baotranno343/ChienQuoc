
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
        set_name("朱老五");

        set_level(102);
	set_max_hp(3900);
	set_ap(650);
	set_dp(595);
	set_cp(340);
	set_pp(260);
	set_sp(120);
	set_walk_speed(4);
	set_attack_speed(13);
        set_max_seek(4);
        
        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_34, 28) && !who->get_legend(TASK_34, 29) )
        {
		who->set_legend(TASK_34, 29);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,50,"姻缘之路4(完成)" );
		send_user(who, "%c%s",'!', "朱老五 1/1");
	}
}
