
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 0801; }

// 函数：构造处理
void create()
{
        set_name("骷髅妖王");

        set_level(95);
	set_max_hp(2892);
	set_ap(595);
	set_dp(570);
	set_cp(690);
	set_pp(320);
	set_sp(235);
	set_walk_speed(3);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_31, 21) && !who->get_legend(TASK_31, 22) )
        {
		who->set_legend(TASK_31, 22);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,40,"秘密（3）(完成)" );
		send_user(who, "%c%s",'!', "骷髅妖王 1/1");
		USER_TASK_D->send_task_intro(who,2,TID_YANGUO,40);
	}
}
   