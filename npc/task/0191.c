
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 8013; }

// 函数：构造处理
void create()
{
        set_name("蔡九");

        set_level(113);
	set_max_hp(2600);
	set_ap(700);
	set_dp(610);
	set_cp(100);
	set_pp(370);
	set_sp(270);
	set_walk_speed(3);
	set_attack_speed(13);
        set_max_seek(4);
        
        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_42, 28) && !who->get_legend(TASK_42, 29) )
        {
		who->set_legend(TASK_42, 29);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,86,"枉法之徒(完成)" );
		send_user(who, "%c%s",'!', "蔡九 1/1");
	}
}
