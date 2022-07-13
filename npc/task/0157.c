
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 0053; }

// 函数：构造处理
void create()
{
        set_name("酒鬼");

        set_level(69);
	set_max_hp(1600);
	set_ap(450);
	set_dp(500);
	set_cp(509);
	set_pp(260);
	set_sp(180);
	set_walk_speed(3);
	set_attack_speed(14);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
	int p;
	object item;
        if ( objectp(who) && who->get_legend(TASK_20, 16) && !who->get_legend(TASK_20, 17) )
        {
        	item = new("item/98/0093");
        	p = item->move(who,-1);
        	if ( !p )
        	{
        		destruct(item);
        		send_user(who,"%c%s",'!',"你携带的物品太多了");	
        		return ;
        	}
        	item->add_to_user(p);
		who->set_legend(TASK_20, 17);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,53,"重阳节（4）(完成)" );
		USER_TASK_D->send_task_intro(who,2,TID_QINGUO,53);
		send_user(who, "%c%s",'!', "酒鬼 1/1");
	}
}
   