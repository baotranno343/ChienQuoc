/*****************************
	**七夕**
*****************************/

#include <ansi.h>
#include <music.h>
#include <task.h>

#include <time.h>
#include <cmd.h>

int iStart_qixi,iFinish_qixi;
object Niulang,Zhinv,Wangmu;
string *qixi_rose=({"七夕蓝玫瑰","七夕白玫瑰","七夕红玫瑰","七夕紫玫瑰",});
void get_qixi_npc();
void destruct_qixi_npc();
// 函数：生成二进制码
void SAVE_BINARY() { }

void create()
{
	iStart_qixi = mktime(2007,8,19,7,50,0);	
	iFinish_qixi = mktime(2007,8,19,22,0,0);

	call_out("check_time",3);
}

void check_time()
{
	int i;
	remove_call_out("check_time");
	i = time();

	if ( i > iFinish_qixi )
		return ;
	if ( i < iStart_qixi )	//没到时间
	{
		call_out("check_time",iStart_qixi - i);
		return ;
	}
	call_out("check_time2",600);
	CHAT_D->sys_channel(0,HIY"牛郎织女将在10分钟后降临人间繁华地——周国，寻求有缘人的帮助，大家赶快去周国啊！");
}

void check_time2()
{
	int i;
	remove_call_out("check_time2");
	i = time();

	if ( i > iFinish_qixi )
	{
		call_out("check_time3",3);
		return ;
	}
	get_qixi_npc();
	CHAT_D->sys_channel(0,HIY"牛郎织女七夕降临人间，为了能够长相守，他们正在周国天坛寻求有缘人的帮助。为了有情人能够终成眷属，大家赶快找自己的有缘人去帮助他们啊！");
	call_out("check_time2",1800);
}
void check_time3()
{
	destruct_qixi_npc();
	CHAT_D->sys_channel(0,HIY"经过大家的热情帮助，牛郎和织女终于摆脱了天河，找到一个风景秀丽的地方，幸福地生活在了一起。真诚祝愿帮助过他们的有缘人‘有情人能终成眷属’。");
	CHAT_D->sys_channel(0,HIY"经过大家的热情帮助，牛郎和织女终于摆脱了天河，找到一个风景秀丽的地方，幸福地生活在了一起。真诚祝愿帮助过他们的有缘人‘有情人能终成眷属’。");
	CHAT_D->sys_channel(0,HIY"经过大家的热情帮助，牛郎和织女终于摆脱了天河，找到一个风景秀丽的地方，幸福地生活在了一起。真诚祝愿帮助过他们的有缘人‘有情人能终成眷属’。");
}
// 函数：放入活动NPC
void get_qixi_npc()
{
	if ( !objectp(Niulang) )
	{
		Niulang = new("/npc/party/niulang");
		Niulang->add_to_scene(80,286,179,4);
	}
	if ( !objectp(Zhinv) )
	{
		Zhinv = new("/npc/party/zhinv");
		Zhinv->add_to_scene(80,288,178,4);
	}
}

// 函数：取消七夕任务
void task_giveup(object who , int iKind)
{
        object map, *reset, npc, item,*team;
        string thief,*member;
        int time, id, i, size,tId,together;
        if( !who->get_save_2("qixi.flag") )    
        {
                return;
        }
	if ( iKind != who->get_save_2("qixi.flag") )
		return ;
        for (i=0;i<sizeof(qixi_rose);i++)
        {
		if (objectp( item=present(qixi_rose[i], who, 1, MAX_CARRY) )) break;
        }

       	if( objectp( item ) )
       	{
        	item->remove_from_user();
        	destruct(item); 
       	} 
        switch( iKind )
        {
	      default : return;
	       case 3 : 
	                break;
	       case 9 :
		        if( stringp( thief = who->get_save_2("qixi.thief") ) && ( npc = find_char(thief) ) )
	                {
			        npc->remove_from_scene();
			        destruct(npc);
		        }
	                break;
	       case 10 : 
	                break;
	       case 12 : 
	               	if( objectp( item = present("给牛郎的仙丹", who, 1, MAX_CARRY) ) )
	               	{
	                	item->remove_from_user();
	                	destruct(item); 
	               	} 
	               	if( objectp( item = present("给织女的仙丹", who, 1, MAX_CARRY) ) )
	               	{
	                	item->remove_from_user();
	                	destruct(item); 
	               	} 
	                break;
        }
       	who->delete_save_2("qixi.flag");
//	who->delete_save_2("qixi.receive");
        send_user( who, "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_QIXI,iKind,0,"" );
	send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,iKind,"" ); 
	send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"" ); 

	if (!who->get_team_id()) return;
	team = who->get_team();
	together = who->get_save_2("qixi.together");
	team -=({who});
	size = sizeof(team);
	if (size<1) return;
        for (i=0;i<size;i++ )
	{
		if ( team[i]->get_save_2("qixi.together") == together )
			MAILBOX->sys_mail(team[i]->get_id(),team[i]->get_number(),HIY"你的有缘人已经放弃了七夕天赐奇缘任务了，你如果想完成此任务，需要放弃任务后，和你的"HIR"有缘人"HIY"在牛郎织女那儿重新开始。");
//			send_user( team[i],"%c%s",';',sprintf(HIY"你的有缘人已经放弃了七夕天赐奇缘任务了，你如果想完成此任务，需要放弃任务后，和你的有缘人在牛郎织女那儿重新开始。"));
	}
}

// 函数：七夕任务信息
void send_task_list(object who)
{
	int iFlag;
	string name,id;
	object npc;
	if( iFlag = who->get_save_2("qixi.flag") ) 
	{
		    
		switch( iFlag )
		{
		       	case 3 : // 2. 七夕天赐奇缘（1）
					send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"七夕任务" ); 
					send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,3,"七夕天赐奇缘（1）" ); 
		                break;
		       	case 9 : // 3. 七夕天赐奇缘（2）
					send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"七夕任务" ); 
					send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,9,"七夕天赐奇缘（2）" ); 
		                break;
		       	case 10 : // 3. 七夕天赐奇缘（2）
					send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"七夕任务" ); 
					send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,10,"七夕天赐奇缘（2）" ); 
		                break;
		       	case 12: // 4. 七夕天赐奇缘（3）
					send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"七夕任务" ); 
					send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,12,"七夕天赐奇缘（3）" ); 
		                break;
	        }			
	}	
}

// 移除活动NPC
void destruct_qixi_npc()
{
	if ( objectp(Niulang) )
	{
		Niulang->remove_from_scene();
		destruct(Niulang);
	}
	if ( objectp(Zhinv) )
	{
		Zhinv->remove_from_scene();
		destruct(Zhinv);
	}
}

//月老的
void do_qixi( object me, object who,string arg )
{
        int flag,i,j,size,p;
        string *name,tmp,name214_1;
        object user,item,item214_1;

	int id,tId,very_good=0;
	object *team,item1,item2,*inv1,*inv2,*brand1,*brand2,pai1,pai2;
	string leader;
	id = getoid(me);
	tId = who->get_team_id();
	team = who->get_team();

        flag = to_int(arg);
        who->set_time( "talk",  0);

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
        for (i=0;i<sizeof(qixi_rose);i++)
        {
		if (objectp( pai1=present(qixi_rose[i], team[0], 1, MAX_CARRY) )) break;
        }
        for (i=0;i<sizeof(qixi_rose);i++)
        {
		if (objectp( pai2=present(qixi_rose[i], team[1], 1, MAX_CARRY) )) break;
        }
	if (!objectp(pai1)||!objectp(pai2)) very_good=-1;

	if (pai1->get_name()==pai2->get_name())
	{
		team[0]->set_save_2("qixi.together",team[0]->get_number());
		team[1]->set_save_2("qixi.together",team[0]->get_number());
		very_good=1;
	}
        switch(flag)
        {

	case 16:
		if(  !who->is_leader() )
		{
		        send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + "：\n    你们的队长呢？让队长过来。\n"ESC"离开" );
		        return;
		}
		if ( team[0]->get_gender() == team[1]->get_gender() )
	        {
	                send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + "：\n    你们是来戏弄老夫吗？虽然我已经几千岁了，但最基本的还是能分清的，现在的年轻人啊！唉！……找到你的另一半再来找我吧！\n"ESC"离开" );
	                return;
	        }
	        if( very_good != 1 )
	        {
	                send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + "：\n    你的有缘人呢？还是赶快找到有缘人再来我这里吧！\n"ESC"离开" );
	                return;
	        }
		if ( team[0]->get_gender() != team[1]->get_gender() && team[0]->get_save_2("qixi.flag") == 1 && team[1]->get_save_2("qixi.flag") == 1 && team[0]->get_save_2("qixi.together") == team[1]->get_save_2("qixi.together") && very_good==1 )
		{

			if (team[0]->get_gender()==1)
			        send_user( team[0], "%c%c%w%s", ':', 3, me->get_char_picid(),
			        	sprintf("%s：\n    牛郎和织女的生活原本十分恩爱幸福，可惜触犯了王母娘娘的禁忌……\n    当时娘娘只是取下头钗轻轻一挥，便将他们隔在了天河的两端。\n    所以，解铃还须系铃人啊！现在王母娘娘正在人间巡查，只要你能找到娘娘就有希望。\n    前两天我遇到一个十分喜欢"HIR"云游"NOR"的人无意间说起曾经见到过王母娘娘。不过那个人喜欢四处跑，所以，我也不知道他现在在什么地方，不过在一些地方应该能打听到\n"
			                ESC "接受任务\ntalk %x# qixi.19\n"
			                ESC "离开", me->get_name(), getoid(me) ) );
			else
			        send_user( team[0], "%c%c%w%s", ':', 3, me->get_char_picid(),
			        	sprintf("%s：\n    牛郎和织女的生活原本十分恩爱幸福，可惜触犯了王母娘娘的禁忌……\n    当时娘娘只是取下头钗轻轻一挥，便将他们隔在了天河的两端。\n    所以，解铃还须系铃人啊！现在王母娘娘正在人间巡查，只要你能找到娘娘就有希望。\n    前两天我遇到一个卖珍稀品的"HIR"商人"NOR"无意间说起过曾经见到过王母娘娘。不过那个商人已经离开了，不过那个商人很特别，在一些消息流通的地方应该能很容易打听到。\n"
			                ESC "接受任务\ntalk %x# qixi.19\n"
			                ESC "离开", me->get_name(), getoid(me) ) );
			if (team[1]->get_gender()==1)
			        send_user( team[1], "%c%c%w%s", ':', 3, me->get_char_picid(),
			        	sprintf("%s：\n    牛郎和织女的生活原本十分恩爱幸福，可惜触犯了王母娘娘的禁忌……\n    当时娘娘只是取下头钗轻轻一挥，便将他们隔在了天河的两端。\n    所以，解铃还须系铃人啊！现在王母娘娘正在人间巡查，只要你能找到娘娘就有希望。\n    前两天我遇到一个十分喜欢"HIR"云游"NOR"的人无意间说起曾经见到过王母娘娘。不过那个人喜欢四处跑，所以，我也不知道他现在在什么地方，不过在一些地方应该能打听到\n"
			                ESC "接受任务\ntalk %x# qixi.19\n"
			                ESC "离开", me->get_name(), getoid(me) ) );
			else
			        send_user( team[1], "%c%c%w%s", ':', 3, me->get_char_picid(),
			        	sprintf("%s：\n    牛郎和织女的生活原本十分恩爱幸福，可惜触犯了王母娘娘的禁忌……\n    当时娘娘只是取下头钗轻轻一挥，便将他们隔在了天河的两端。\n    所以，解铃还须系铃人啊！现在王母娘娘正在人间巡查，只要你能找到娘娘就有希望。\n    前两天我遇到一个卖珍稀品的"HIR"商人"NOR"无意间说起过曾经见到过王母娘娘。不过那个商人已经离开了，不过那个商人很特别，在一些消息流通的地方应该能很容易打听到。\n"
			                ESC "接受任务\ntalk %x# qixi.19\n"
			                ESC "离开", me->get_name(), getoid(me) ) );
		}
		break;
	case 19:
		if(  !who->is_leader() )
		        return;
		if ( team[0]->get_gender() == team[1]->get_gender() )
	                return;
		if ( team[0]->get_gender() != team[1]->get_gender() && team[0]->get_save_2("qixi.flag") == 1 && team[1]->get_save_2("qixi.flag") == 1 && team[0]->get_save_2("qixi.together") == team[1]->get_save_2("qixi.together") && very_good==1 )
		{
			pai1->remove_from_user();
		     	destruct(pai1);
			pai2->remove_from_user();
		     	destruct(pai2);
			team[0]->set_save_2( "qixi.flag", 3 );
			team[1]->set_save_2( "qixi.flag", 3 );
			send_user( team[0], "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"七夕任务" ); 
			send_user( team[0], "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,3,"七夕天赐奇缘（1）" ); 
			send_user( team[1], "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"七夕任务" ); 
			send_user( team[1], "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,3,"七夕天赐奇缘（1）" ); 
			send_user( team[0], "%c%s", '!', "得到任务 "HIY"七夕天赐奇缘（1）");
			send_user( team[1], "%c%s", '!', "得到任务 "HIY"七夕天赐奇缘（1）");
		}
		break;

	}
}

//云游商人的
void do_qixi3( object me, object who,string arg )
{
        int flag,i,j,size,p,z,x,y;
        string *name,tmp,name_qixi_1;
        object user,item,item_qixi_1;

	int id,tId,very_good;
	object *team,item1,item2,*inv1,*inv2,*brand1,*brand2,pai1,pai2,map,npc;
	string leader;
	id = getoid(me);
	tId = who->get_team_id();
	team = who->get_team();


        flag = to_int(arg);
        who->set_time( "talk",  0);

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
                	send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + "：\n    你的队员呢？人都没齐，人到齐了就叫你们"HIR"队长"NOR"来找我。\n"ESC"离开" );	
			return;
		}
	}

	if (team[0]->get_save_2("qixi.together") != team[1]->get_save_2("qixi.together"))
		return;

        switch(flag)
        {
	case 1:
	        if(  !who->is_leader() )
	        {
	                send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + "：\n    你们的队长呢？让队长过来。\n"ESC"离开" );
	                return;
	        }
	        if ( team[0]->get_save_2("qixi.flag") == 3 && team[1]->get_save_2("qixi.flag") == 3 && team[0]->get_gender() != team[1]->get_gender() && team[0]->get_save_2("qixi.together") == team[1]->get_save_2("qixi.together") )
		{
		        send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
		        	sprintf("%s：\n    我知道你们在找王母娘娘，等下"HIR"队长"NOR"再来找我！\n"
		                ESC "完成任务\ntalk %x# qixi.2\n"
		                ESC "离开", me->get_name(), getoid(me) ) );
		}
	        if ( team[0]->get_save_2("qixi.flag") == 8 && team[1]->get_save_2("qixi.flag") == 8 && team[0]->get_gender() != team[1]->get_gender() && team[0]->get_save_2("qixi.together") == team[1]->get_save_2("qixi.together") )
		{
			z = (random(8)+1)*10;
			p = efun::get_xy_point( z, IS_CHAR_BLOCK );
			x = ( p % 1000000 ) / 1000;  y = p % 1000;
			map = get_map_object(z);
			team[0]->set_save_2("qixi.z",z);
			team[0]->set_save_2("qixi.x",x);
			team[0]->set_save_2("qixi.y",y);
			team[1]->set_save_2("qixi.z",z);
			team[1]->set_save_2("qixi.x",x);
			team[1]->set_save_2("qixi.y",y);
		        send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
		        	sprintf("%s：\n    我知道你们要找王母娘娘，不过，王母娘娘要我为她收集一味灵药，只要你把灵药采来，我就告诉你王母娘娘的行踪。听说"HIR"%s（%d,%d）"NOR"有此灵药，如果你们能帮我采回来，我可以立刻给他们解除天河的限制。不过灵药都有强大的灵兽守护着，你可要考虑清楚。\n"
		                ESC "我考虑清楚了\ntalk %x# qixi.3\n"
		                ESC "离开", me->get_name(),map->get_name(),x,y, getoid(me) ) );
		}
	        if ( team[0]->get_save_2("qixi.flag") == 9 && team[1]->get_save_2("qixi.flag") == 9 && team[0]->get_gender() != team[1]->get_gender() && team[0]->get_save_2("qixi.together") == team[1]->get_save_2("qixi.together") )
		{
		        send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
		        	sprintf("%s：\n    我要的灵药呢？\n"
		                ESC "离开", me->get_name(), ) );
		}
	        if ( team[0]->get_save_2("qixi.flag") == 10 && team[1]->get_save_2("qixi.flag") == 10 && team[0]->get_gender() != team[1]->get_gender() && team[0]->get_save_2("qixi.together") == team[1]->get_save_2("qixi.together") )
		{
		        send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
		        	sprintf("%s：\n    不错，就是这种灵药，你们等会再来找我吧！\n"
		                ESC "完成任务\ntalk %x# qixi.5\n"
		                ESC "离开", me->get_name(), getoid(me) ) );
		}
	        if ( team[0]->get_save_2("qixi.flag") == 11 && team[1]->get_save_2("qixi.flag") == 11 && team[0]->get_gender() != team[1]->get_gender() && team[0]->get_save_2("qixi.together") == team[1]->get_save_2("qixi.together") )
		{
		        send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
		        	sprintf("%s：\n    其实，王母娘娘早就知道了你们会来找她，因此娘娘留下仙丹，只要你们通过了考验，就可以得到仙丹。牛郎织女服下仙丹，以后就自由了。赶快给他们送"HIR"(ALT+G)"NOR"去吧！\n"
		                ESC "接受任务\ntalk %x# qixi.6\n"
		                ESC "离开", me->get_name(),getoid(me) ) );
		}
		break;
	case 2:
	        if ( team[0]->get_save_2("qixi.flag") == 3 && team[1]->get_save_2("qixi.flag") == 3 && team[0]->get_gender() != team[1]->get_gender() && team[0]->get_save_2("qixi.together") == team[1]->get_save_2("qixi.together") )
		{
		     	team[0]->add_exp(50*(team[0]->get_online_rate()/100));
		     	team[1]->add_exp(50*(team[1]->get_online_rate()/100));
		     	
		     	team[0]->add_cash(500*(team[0]->get_online_rate()/100));
		     	team[1]->add_cash(500*(team[1]->get_online_rate()/100));

		     	team[0]->set_save_2("qixi.flag",8);
		     	team[1]->set_save_2("qixi.flag",8);
		     	
		        send_user( team[0], "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_QIXI,1,0,"" );
			send_user( team[0], "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,3,"" ); 
			send_user( team[0], "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"" ); 
		        send_user( team[1], "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_QIXI,1,0,"" );
			send_user( team[1], "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,3,"" ); 
			send_user( team[1], "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"" ); 
			me->do_qixi(1);
		}				
		break;
	case 3:
		if (!team[0]->get_save_2("qixi.z")) return;
	        if ( team[0]->get_save_2("qixi.flag") == 8 && team[1]->get_save_2("qixi.flag") == 8 && team[0]->get_gender() != team[1]->get_gender() && team[0]->get_save_2("qixi.together") == team[1]->get_save_2("qixi.together") )
		{
		        send_user( team[0], "%c%c%w%s", ':', 3, me->get_char_picid(),
		        	sprintf("%s：\n    请等待其他队员回应。\n", me->get_name()) );
		        send_user( team[1], "%c%c%w%s", ':', 3, me->get_char_picid(),
		        	sprintf("%s：\n    玩家%s决定为王母娘娘采集灵药，你是否接受？\n"
		                ESC "接受\ntalk %x# qixi.4\n"
		                ESC "离开", me->get_name(), team[0]->get_name(),getoid(me) ) );
		}
		break;
	case 4:
		if (!team[0]->get_save_2("qixi.z")) return;
	        if ( team[0]->get_save_2("qixi.flag") == 8 && team[1]->get_save_2("qixi.flag") == 8 && team[0]->get_gender() != team[1]->get_gender() && team[0]->get_save_2("qixi.together") == team[1]->get_save_2("qixi.together") )
		{
		        npc = new( "npc/party/spirit" );
			map = get_map_object(who->get_save_2("qixi.z"));
		        npc->add_to_scene(who->get_save_2("qixi.z"), who->get_save_2("qixi.x"), who->get_save_2("qixi.y"), 3);
			map->add_reset(npc); 
			npc->set("bb",who->get_save_2("qixi.together"));
			npc->set("user0", team[0]->get_number());
			npc->set("user1", team[1]->get_number());

			team[0]->set_save_2( "qixi.flag", 9 );
			team[1]->set_save_2( "qixi.flag", 9 );
			send_user( team[0], "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"七夕任务" ); 
			send_user( team[0], "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,9,"七夕天赐奇缘（2）" ); 
			send_user( team[1], "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"七夕任务" ); 
			send_user( team[1], "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,9,"七夕天赐奇缘（2）" ); 
		        team[0]->set_save_2( "qixi.thief", sprintf( "%x#", getoid(npc) ) );
		        team[1]->set_save_2( "qixi.thief", sprintf( "%x#", getoid(npc) ) );
			team[0]->set_save_2( "qixi.time", time() );
			team[1]->set_save_2( "qixi.time", time() );
		        send_user( team[0], "%c%c%w%s", ':', 3, me->get_char_picid(),
		        	sprintf("%s：\n    你们小队已领取了采药的任务，赶快去吧！\n"ESC "离开", me->get_name()) );
		        send_user( team[1], "%c%c%w%s", ':', 3, me->get_char_picid(),
		        	sprintf("%s：\n    你们小队已领取了采药的任务，赶快去吧！\n"ESC "离开", me->get_name()) );
		}
		break;
	case 5:
	        if ( team[0]->get_save_2("qixi.flag") == 10 && team[1]->get_save_2("qixi.flag") == 10 && team[0]->get_gender() != team[1]->get_gender() && team[0]->get_save_2("qixi.together") == team[1]->get_save_2("qixi.together") )
		{
		     	team[0]->add_exp(50*(team[0]->get_online_rate()/100));
		     	team[1]->add_exp(50*(team[1]->get_online_rate()/100));
		     	
		     	team[0]->add_cash(500*(team[0]->get_online_rate()/100));
		     	team[1]->add_cash(500*(team[1]->get_online_rate()/100));

		     	team[0]->set_save_2("qixi.flag",11);
		     	team[0]->delete_save_2("qixi.thief");
		     	team[0]->delete_save_2("qixi.z");
		     	team[0]->delete_save_2("qixi.x");
		     	team[0]->delete_save_2("qixi.y");
		     	team[1]->set_save_2("qixi.flag",11);
		     	team[1]->delete_save_2("qixi.thief");
		     	team[1]->delete_save_2("qixi.z");
		     	team[1]->delete_save_2("qixi.x");
		     	team[1]->delete_save_2("qixi.y");		     	
		     	
		        send_user( team[0], "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_QIXI,1,0,"" );
			send_user( team[0], "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,10,"" ); 
			send_user( team[0], "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"" ); 
		        send_user( team[1], "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_QIXI,1,0,"" );
			send_user( team[1], "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,10,"" ); 
			send_user( team[1], "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"" ); 
			
			me->do_qixi(1);
		}				
		break;
	case 6:
	        if ( team[0]->get_save_2("qixi.flag") == 11 && team[1]->get_save_2("qixi.flag") == 11 && team[0]->get_gender() != team[1]->get_gender() && team[0]->get_save_2("qixi.together") == team[1]->get_save_2("qixi.together") )
		{
			if(USER_INVENTORY_D->count_empty_carry(team[0]) < 1 )
			{
			        send_user(team[0],"%c%s",';',"你的东西太多了，请清理一下你的包包，再来找我吧！");
		    		return;
			}
			if(USER_INVENTORY_D->count_empty_carry(team[1]) < 1 )
			{
			        send_user(team[1],"%c%s",';',"你的东西太多了，请清理一下你的包包，再来找我吧！");
		    		return;
			}
			if (team[0]->get_gender()==1)
			{
			     	item=new("item/98/0247");
				p = item->move(team[0],-1);
				item->add_to_user(p);
			}
			else
			{
			     	item=new("item/98/0248");
				p = item->move(team[0],-1);
				item->add_to_user(p);
			}
			if (team[1]->get_gender()==1)
			{
			     	item=new("item/98/0247");
				p = item->move(team[1],-1);
				item->add_to_user(p);
			}				
			else
			{

			     	item=new("item/98/0248");
				p = item->move(team[1],-1);
				item->add_to_user(p);
			}
		     	team[0]->set_save_2("qixi.flag",12);
		     	team[1]->set_save_2("qixi.flag",12);
		     	
			send_user( team[0], "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"七夕任务" ); 
			send_user( team[0], "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,12,"七夕天赐奇缘（3）" ); 
			send_user( team[0],"%c%s",';',"你得到了"HIR"仙丹");
			send_user( team[1], "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"七夕任务" ); 
			send_user( team[1], "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,12,"七夕天赐奇缘（3）" ); 
			send_user( team[1],"%c%s",';',"你得到了"HIR"仙丹");

		}				
		break;
	}
}

int get_qixi_time(){return iFinish_qixi;}