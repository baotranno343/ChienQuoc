
#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>
#include <effect.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 2100; }

// 有自己的do_look函数
int is_self_look() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Chú Kiếm Thạch");

        setup();
}

// 函数：对话处理
void do_look( object who )
{

	if( who->get_legend(TASK_NEWBIE_03,7) && !who->get_legend(TASK_NEWBIE_03,8) && who->get_save_2("xuantieshi") < 3  )
	{
		if (get_effect(who, EFFECT_MINE)) return;
		send_user(who, "%c%c%w%s", 0x5a, 0, 10, "开采中……");
		set_effect(who, EFFECT_MINE, 10);
		who->set_save_2("mine",sprintf("%x#",getoid(this_object())));
	}

}

// 函数：对话处理
void into_effect( object who )
{
	int p;
	object npc,item;
	
	send_user(who, "%c%c%c", 0x5a, 1, 1);
	npc = find_char(who->get_save_2("mine"));
	who->delete_save_2("mine");
	if ( !objectp(npc) )
		return;
	if( npc->get_name() == "Chú Kiếm Thạch" && who->get_legend(TASK_NEWBIE_03,7) && !who->get_legend(TASK_NEWBIE_03,8) && who->get_save_2("xuantieshi") < 3  )
	{

		if ( objectp( item = present("Chú Kiếm Thạch", who, 1, MAX_CARRY) ) && item->is_xuantieshi() == 1 ) 
		{
			if ( item->get_amount() < 3 )
				item->add_amount(1);
		}		
		else
		{
			item = new("item/98/0003");
			p = item->move(who,-1);
			if ( !p )
			{
				destruct(item);
				send_user(who,"%c%s",'!', "你携带的东西太多了!");
				return;	
			}
			item->add_to_user(p);
		}
		npc->remove_from_scene();
		destruct(npc);
		send_user(who,"%c%s",'!', "你得到"HIY"Chú Kiếm Thạch");
		p = who->add_save_2("xuantieshi",1);
		if ( p >= 3 )
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,4,"打造惊世之剑(完成)" );
		}
		USER_TASK_D->send_task_intro(who,2,TID_CHUGUO,4);
	}
	else if( npc->get_name() == "精铁矿石" && who->get_legend(TASK_05,10) && !who->get_legend(TASK_05,11) )
	{
		item = new("item/98/0017");
		p = item->move(who,-1);
		if ( !p )
		{
			destruct(item);
			send_user(who,"%c%s",'!', "你携带的东西太多了!");
			return;	
		}
		item->add_to_user(p);
		who->set_legend(TASK_05,11);
		send_user(who,"%c%s",'!', "你得到"HIY"百炼精铁");
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,11,"锻造之路(完成)" );
		USER_TASK_D->send_task_intro(who,2,TID_WEIGUO,11);
	}
}

void effect_break(object who)
{
	set_effect(who, EFFECT_MINE, 0);
	send_user(who, "%c%c%c", 0x5a, 1, 0);
}