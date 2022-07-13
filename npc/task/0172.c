
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 1052; }

// 函数：构造处理
void create()
{
        set_name("熊平");

        set_level(88);
	set_max_hp(2426);
	set_ap(560);
	set_dp(549);
	set_cp(640);
	set_pp(298);
	set_sp(243);
	set_walk_speed(3);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
	int p;
	object item;
        if ( objectp(who) && who->get_legend(TASK_28, 14) && !who->get_legend(TASK_28, 15) )
        {
        	item = new("item/98/0136");
        	p = item->move(who,-1);
        	if ( !p )
        	{
        		destruct(item);
        		return ;	
        	}
        	item->add_to_user(p);
		who->set_legend(TASK_28, 15);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,7,"木箱的秘密（4）(完成)" );
		USER_TASK_D->send_task_intro(who,2,TID_ZHOUGUO,7);
		send_user(who, "%c%s",'!', "特殊的木块 1/1");
	}
}
