
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;


// 函数：获取人物造型
int get_char_picid() { return 1051; }

// 函数：构造处理
void create()
{
        set_name("恶官马三");

        set_level(26);
	set_max_hp(420);
	set_ap(180);
	set_dp(205);
	set_cp(165);
	set_pp(120);
	set_sp(110);
	set_walk_speed(3);
	set_attack_speed(15);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_05, 1)&&!who->get_legend(TASK_05, 2) )
        {
		who->set_legend(TASK_05, 2);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,13,"解救工匠(完成)" );
		send_user(who, "%c%s",'!', "恶官马三 1/1");
	}	
}