#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <equip.h>
#include <task.h>

inherit OFFICER;
// 函数：获取人物造型
int get_char_picid() { return 5502; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("极限穿越审查官");
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
	int iTime=time();
	
	if (MAIN_D->get_host_type()==2)
		return ;
	if ( who->get_save_2("51cuanye.time") )
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("%s：\n    五一七天乐，战国乐翻天！\n    我站在这里，无视投过来的眼神，惊奇也好，诧异也罢，我只等待那个寻找我的人。\n"ESC"极限穿越\ntalk %x# welcome.1\n"ESC"离开",me->get_name(),id,));
	else
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("%s：\n    五一七天乐，战国乐翻天！\n    我站在这里，无视投过来的眼神，惊奇也好，诧异也罢，我只等待那个寻找我的人。\n"ESC"离开",me->get_name(),));
}


void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag, p,i,size,id,iTime,amount;
       	object who, item,*nTeam;
	  
	if (MAIN_D->get_host_type()==2)
		return ;
		
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	iTime = who->get_save_2("51cuanye.time");
        	if ( !iTime )
        		return ;
		if ( !who->is_leader() )
       		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你不是队长，不能完成任务！\n"ESC"离开",me->get_name(),));
			return ;
		}
		if ( !objectp(item = present("极限穿越证明书", who, 1, MAX_CARRY)) )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你的极限穿越证明书呢？\n"ESC"离开",me->get_name(),));
			return ;
		}
        	id = getoid(me);
        	i = gone_time(iTime)/60;
        	if ( i <= 10 )
        		p = 5;
        	else if ( i <= 20 )
        		p = 4;
        	else if ( i <= 30 )
        		p = 3;
        	else
        		p = 2;
        	who->set_save_2("51cuanye.min",i);
        	who->set_save_2("51cuanye.amount",p);
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    五一七天乐，战国乐翻天！\n    没想到你这么快就找到我了，我还以为，我要再等上一万年！\n    你花费了%d分钟找到我，将得到%d个战国劳动奖章。\n"ESC"极限穿越\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),i,p,id,));
		break;
	case 2:
		iTime = who->get_save_2("51cuanye.time");
		i = who->get_save_2("51cuanye.min");
		amount = who->get_save_2("51cuanye.amount");
		if ( !amount )
			return ;
		if ( !who->is_leader() )
       		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你不是队长，不能完成任务！\n"ESC"离开",me->get_name(),));
			return ;
		}
		if ( !objectp(item = present("极限穿越证明书", who, 1, MAX_CARRY)) )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你的极限穿越证明书呢？\n"ESC"离开",me->get_name(),));
			return ;
		}
		who->delete_save_2("51cuanye.min");
		who->delete_save_2("51cuanye.amount");
		nTeam = who->get_team();
		size = sizeof(nTeam);
		if ( !size )
			return ;
		for(i=0;i<size;i++)
		{
			if ( !objectp(nTeam[i]) )
				continue;
			if ( !inside_screen_2(nTeam[i],me) )
				continue;
			if ( iTime != nTeam[i]->get_save_2("51cuanye.time") )
				continue;
			if ( USER_INVENTORY_D->count_empty_carry(nTeam[i]) < 1 )
			{
				send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    队伍中"HIR+nTeam[i]->get_name()+NOR"玩家的道具栏空间不够，建议空出一格来放任务奖励物品。\n"ESC"离开",me->get_name(),));
				return ;
			}
		}				
		item->remove_from_user();
		destruct(item);
		for(i=0;i<size;i++)
		{
			if ( !objectp(nTeam[i]) )
				continue;
			if ( !inside_screen_2(nTeam[i],me) )
				continue;
			if ( iTime != nTeam[i]->get_save_2("51cuanye.time") )
				continue;
			nTeam[i]->delete_save_2("51cuanye.time");
			item = new("item/04/0438");
			item->set_amount(amount);
			p = item->move(nTeam[i],-1);
			item->add_to_user(p);
			send_user(nTeam[i],"%c%s",';',sprintf("你完成任务，得到%d个战国劳动奖章",amount));
	                send_user( nTeam[i], "%c%c%c%w%w%s", 0x51, 1, 2,TID_WUYIHUODONG,1,"" );                  		
		}

		break;
	}

}

void go_there()
{
	object me=this_object();
	
	me->add_to_scene(802,78,43,2);
}