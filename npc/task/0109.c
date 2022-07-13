
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
        set_name("马三刀");

        set_level(24);
	set_max_hp(460);
	set_ap(160);
	set_dp(145);
	set_cp(140);
	set_pp(140);
	set_sp(100);
	set_walk_speed(3);
	set_attack_speed(15);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_04, 26)&&!who->get_legend(TASK_04, 27) )
        {
		who->set_legend(TASK_04, 27);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,12,"追捕重犯(完成)" );
		send_user(who, "%c%s",'!', "马三刀 1/1");
	}	
}