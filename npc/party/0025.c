#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <equip.h>
#include <task.h>

inherit OFFICER;
// 函数：获取人物造型
int get_char_picid() { return 6009; }
void do_welcome(string arg);


// 函数：构造处理
void create()
{
        set_name("寻踪使者");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );
        setup();
        if ( !clonep(this_object()) )
        	return ;
        if (MAIN_D->get_host_type()==2)		//台湾除外
        	call_out("go_there",2);
}

void do_look(object who) { __FILE__->do_look_call(this_object(),who); }
void do_look_call(object me,object who)
{
	int id = getoid(me);
	
	if (MAIN_D->get_host_type()==2)
		return ;
	if ( who->get_save("dodolook") == 5 )
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你已经领过额外奖励了吧。做人不能太贪心噢！\n"ESC"离开",me->get_name(),));
	else if ( who->get_save("dodolook") != 4 )
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你确认你完成过七国令任务吗？你还是回去好好想想再来找我吧！\n"ESC"离开",me->get_name(),));
	else if( !present("七国令", who, 1, MAX_CARRY) )
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你确认你完成过七国令的任务？好好看看你的包裹，你必须带着七国令来找我，才能给你相应的奖励哦\n"ESC"离开",me->get_name(),));
	else
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    每一个完成任务拿到七国令的人都可以获得一个小小的惊喜哦。拿着吧，这是对你的奖励！\n"ESC"领取dodolook带你游七国之新手有礼活动奖励\ntalk %x# welcome.1\n"ESC"离开",me->get_name(),id,));
	
}

void do_welcome(string arg) { __FILE__->do_welcome_call(this_object(),arg); }

void do_welcome_call( object me,string arg )
{
	int flag, p,iTime,i,size,id,level,iLev;
       	object who, item;
       	string name,*nTmp,tmp;
	mixed *mxTime;  
	
	
	if (MAIN_D->get_host_type()==2)
		return ;
		
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
	case 1:
		if ( who->get_save("dodolook") == 4 && objectp( item = present("七国令", who, 1, MAX_CARRY) ) )
		{
			if ( USER_INVENTORY_D->count_empty_carry(who) < 2 )
			{
				send_user(who,"%c%s",'!',"清理一下你的包包！");
				return ;	
			}
			item = new("item/std/8000");
			p = item->move(who,-1);
			item->add_to_user(p);
			item = new("item/std/6003");
			p = item->move(who,-1);
			item->add_to_user(p);
			who->set_save("dodolook",5);
			send_user(who,"%c%s",'!',"你得到藏宝图一张和麻布包裹一个");
		}
		break;        	
        	
        }
}

void go_there()
{
	object me=this_object();
	
	me->add_to_scene(802,79,45,2);
}