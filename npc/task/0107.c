
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
        set_name("Ngô Tư");

        set_level(22);
	set_max_hp(350);
	set_ap(160);
	set_dp(155);
	set_cp(100);
	set_pp(145);
	set_sp(85);
	set_walk_speed(3);
	set_attack_speed(15);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_04, 4)&&!who->get_legend(TASK_04, 5) )
        {
		who->set_legend(TASK_04, 5);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,2,"内政官的烦恼(完成)" );
		send_user(who, "%c%s",'!', "Ngô Tư 1/1");
	}	
}