
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
        set_name("劫盗李三");

        set_level(80);
	set_max_hp(2200);
	set_ap(520);
	set_dp(510);
	set_cp(100);
	set_pp(280);
	set_sp(200);
	set_walk_speed(3);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_25, 6) && !who->get_legend(TASK_25, 7) )
        {
		who->set_legend(TASK_25, 7);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,17,"清除威胁(完成)" );
		send_user(who, "%c%s",'!', "劫盗李三 1/1");
		USER_TASK_D->send_task_intro(who,2,TID_HANGUO,17);
		
	}
}
   