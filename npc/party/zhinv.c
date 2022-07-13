#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <equip.h>
#include <task.h>
#include <effect.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 7302; }
void do_visit(string arg);

// 函数：构造处理
void create()
{
        set_name("织女");
        set_2( "talk", ([
                 "visit"         : (: do_visit :),
        ]) );
        setup();
	set("mpLegend",([0:({32}),]));
        if ( !clonep(this_object()) )
        	return ;
        if (MAIN_D->get_host_type()==2)		//台湾除外
        	call_out("go_there",2);
}

void do_look(object who) { __FILE__->do_look_call(this_object(),who); }

void do_look_call(object me,object who)
{
	int tId,i,size;
	int id = getoid(me);
	int iTime=time();
	object *team;
	if (MAIN_D->get_host_type()==2)
		return ;
	if ( who->get_gender() != 1 )
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    银河万里碧水滔，夜夜青天望今朝。\n"
		ESC"七夕天赐奇缘\ntalk %x# visit.1\n"
		ESC"离开",me->get_name(),id));
/*	if ( who->get_gender() != 1 && who->get_save_2("qixi.flag")==12)
	{
		tId = who->get_team_id();
		team = who->get_team();
	
	        if( ( size = sizeof(team) ) > 2 )
	        {
	                send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + "：\n    不要带些不相干的人来！\n"ESC"离开" );
	                return;
	        }
	        if( !tId || ( size = sizeof(team) ) != 2 )
	        {
	                send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + "：\n    你的有缘人呢？还是赶快找到有缘人再来我这里吧！\n"ESC"离开" );
	                return;
	        }
		for (i=0;i<size;i++)		
		{
			if (!inside_screen_2(me, team[i]))
			{
	                	send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + "：\n    和你在一起的人呢？我怎么没有看到？等你们到齐了再一起来找我吧！\n"ESC"离开" );	
				return;
			}
		}
		if (team[0]->get_save_2("qixi.together") != team[1]->get_save_2("qixi.together"))
			return;
		for (i=0;i<size;i++)
		{
			if ( team[i]->get_gender() != 1 )
				send_user(team[i],"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    就是这颗仙丹吗？太感谢你们了！我们会有后报的。\n"
				ESC"完成任务\ntalk %x# visit.3\n"
				ESC"离开",me->get_name(),id));
			if ( team[i]->get_gender() == 1 )
				send_user(team[i],"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    就是这颗仙丹吗？太感谢你们了！我们会有后报的。\n"
				ESC"完成任务\ntalk %x# visit.4\n"
				ESC"离开",me->get_name(),id));
		}
	}*/
}

void do_visit(string arg) { __FILE__->do_visit_call(this_object(),arg); }

void do_visit_call( object me,string arg )
{
	int flag, p,iTime,i,size,id,x,y,z,level,tId;
       	object who, item,*nTeam,member,npc,map,item_qx1,item_qx2,*team;
       	string name,*nTmp,tmp;
	mixed *mxTime;  

	
	if (MAIN_D->get_host_type()==2)
		return ;
		
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
	if ( who->get_save_2("qixi.finish") == 1 )
	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你已经做过七夕任务了，不能再领了\n"
		ESC"离开",me->get_name()));
		return ;	
	}
        switch(flag)
        {
        case 1:
		if ( who->get_gender() == 1 ) return ;

		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你愿意帮助我们吗？如果愿意，那么就拿着这个信物吧，找到与你持有相同信物的异性，然后一起去找月老，他会告诉你一切的。\n"
		ESC"领取信物\ntalk %x# visit.2\n"
		ESC"离开",me->get_name(),id));
        	break;
        case 2:
		if ( who->get_gender() == 1 ) return ;
//        	if ( who->get_save_2("qixi.receive") == 1 )
		if ( objectp( item = present("七夕蓝玫瑰", who, 1, MAX_CARRY) ) || objectp( item = present("七夕白玫瑰", who, 1, MAX_CARRY) ) || objectp( item = present("七夕红玫瑰", who, 1, MAX_CARRY) ) || objectp( item = present("七夕紫玫瑰", who, 1, MAX_CARRY) ) || who->get_save_2( "qixi.flag" ) > 1 )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你不是已经领了信物吗？赶快去找你的有缘人吧！\n"
			ESC"离开",me->get_name()));
			return ;	
		}
       		if ( USER_INVENTORY_D->count_empty_carry(who) < 1 )
		{
			send_user(who,"%c%s",'!',"请清理一下你的包包再来领取吧！");
			return ;	
		}
		item = new(sprintf("item/04/045%d",random(4)));
		p = item->move(who,-1);
		item->add_to_user(p);
		who->set_save_2( "qixi.flag", 1 );
//		who->set_save_2("qixi.receive",1);	//已经领取了
		send_user( who,"%c%s",';',sprintf("你得到了"HIR"%s",item->get_name()));
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    找到你的有缘人后，将其加入你的队伍，然后去找月老，\n"
		ESC"离开",me->get_name()));
        	break;
        case 3:
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    请等待队友的回应……\n"
			ESC"离开",me->get_name()));
        	break;
        case 4:
//	        if ( team[0]->get_save_2("qixi.flag") == 12 && team[1]->get_save_2("qixi.flag") == 12 && team[0]->get_gender() != team[1]->get_gender() && team[0]->get_save_2("qixi.together") == team[1]->get_save_2("qixi.together") )
	        if ( who->get_save_2("qixi.flag") == 12 )
		{
/*			if(USER_INVENTORY_D->count_empty_carry(team[0]) < 1 )
			{
			        send_user(team[0],"%c%s",';',"你的东西太多了，请清理一下你的包包，再来找我们吧！");
		    		return;
			}
			if(USER_INVENTORY_D->count_empty_carry(team[1]) < 1 )
			{
			        send_user(team[1],"%c%s",';',"你的东西太多了，请清理一下你的包包，再来找我们吧！");
		    		return;
			}

			if( !objectp( item_qx1 = present("给牛郎织女的仙丹", team[0], 1, MAX_CARRY) ) )
			{
				send_user(team[0],"%c%s",'!',"你的仙丹呢?");
				return;	
			}
			if( !objectp( item_qx2 = present("给牛郎织女的仙丹", team[1], 1, MAX_CARRY) ) )
			{
				send_user(team[1],"%c%s",'!',"你的仙丹呢?");
				return;	
			}

			item_qx1->remove_from_user();
                	destruct(item_qx1);
			item_qx2->remove_from_user();
                	destruct(item_qx2);*/
//			for (i=0;i<size;i++)
			{
				who->add_exp(50000*(who->get_online_rate()/100));
				who->add_cash(50000*(who->get_online_rate()/100));
//				if ( who->get_gender() == 1 )
//				     	item=new("item/04/ring1");
//				else
					item=new("item/04/ring2");
				p = item->move(who,-1);
				item->add_to_user(p);
				send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    这是我们的一点心意，你们就收下吧。\n"
				ESC"离开",me->get_name()));
				send_user(who,"%c%s",';',sprintf(HIR"你完成了七夕天赐奇缘任务，获得金钱50000，经验50000，情比金坚戒 "));
				who->delete_save_2("qixi.flag");
				who->set_save_2("qixi.finish",1);
				send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,12,"" ); 
				send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"" ); 
			}
			send_user( CHAT_D->get_chat(), "%c%s", 0xA3, sprintf(HIY"恭喜%s完成七夕天赐奇缘任务，使牛郎织女能够幸福地生活在一起。",who->get_name()) );
		}
        	break;
        }
}

int accept_object(object me, object item,int amount)
{

	return __FILE__->accept_object2(me, this_object(), item,amount);
}

int accept_object2(object me, object who, object item2,int amount)
{
	if ( USER_INVENTORY_D->count_empty_carry(me) < 1 )
	{
		send_user(who,"%c%s",';',"请清理一下你的包包再来领取吧！");
		return 0;	
	}
	if (item2->get_name()=="给织女的仙丹" && me->get_save_2("qixi.flag") == 12 )
	{
		who->do_visit(4);
tell_user(me,"jjjjjj");
		return 1;
	}
	return 0;
}

void go_there()
{
	object me=this_object();
	
	me->add_to_scene(802,78,43,2);
}
