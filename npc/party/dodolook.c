#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <equip.h>
#include <task.h>
#include <effect.h>

inherit OFFICER;
inherit SAVE_F;

int iStart1;

// 函数：获取人物造型
int get_char_picid() { return 8113; }
void do_welcome(string arg);
int check_dodolook(object me,object who);
void init_npc(object npc, int level);
int check_yuanfen(object who,object me);	

string get_save_file()	{ return "data/dodolook_task"SAVE_EXTENSION;}

// 函数：构造处理
void create()
{
        restore();
        set_name("dodolook");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );
        setup();
	set("mpLegend",([0:({32}),]));
        if ( !clonep(this_object()) )
        	return ;
        if (MAIN_D->get_host_type()==2)		//台湾除外
        	call_out("go_there",2);
}
string get_short() 
{ 
	if ( stringp(get_real_name()) )
		return get_name() + "|" + get_real_name();
	else
		return get_name();
}
void do_look(object who) { __FILE__->do_look_call(this_object(),who); }

void do_look_call(object me,object who)
{
	int id = getoid(me);
	int iTime=time();
	
	if (MAIN_D->get_host_type()==2)
		return ;
	if ( who->get_save_2("dodolook_task.finish") )
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    缘分天注定，把握在个人哦！这里有一个考验你们缘分的机会，你们愿意接受吗？想必你们都已做好准备了吧！既然如此，缘分的测试就要开始了哦！\n"ESC"领取缘分宠物\ntalk %x# welcome.101\n"ESC"注意事项\ntalk %x# welcome.102\n"ESC"完成缘分任务\ntalk %x# welcome.107\n"ESC"传送去缘分驿站\ntalk %x# welcome.108\n"ESC"离开",me->get_name(),id,id,id,id));
	else
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    缘分天注定，把握在个人哦！这里有一个考验你们缘分的机会，你们愿意接受吗？想必你们都已做好准备了吧！既然如此，缘分的测试就要开始了哦！\n"ESC"领取缘分宠物\ntalk %x# welcome.101\n"ESC"注意事项\ntalk %x# welcome.102\n"ESC"接受缘分任务\ntalk %x# welcome.103\n"ESC"传送去缘分驿站\ntalk %x# welcome.108\n"ESC"离开",me->get_name(),id,id,id,id));
}

void do_welcome(string arg) { __FILE__->do_welcome_call(this_object(),arg); }

void do_welcome_call( object me,string arg )
{
	int flag, p,iTime,i,size,id,x,y,z,level;
       	object who, item,*nTeam,member,npc,map;
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
        case 101:
        case 10091:
        case 10101:
        	if ( !iStart1 || time() < iStart1 )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    活动还没开始呢，详情请查看官方网站(zg.mop.com)公告。\n"ESC"离开",me->get_name(),));
        		return ;	
        	}        	
        	if ( who->get_save("dodolook_yuanfen") == 2 )
        	{
			send_user(who,"%c%s",'!',"你已经领过了！");
			return ;	
		}
        	if ( !check_yuanfen(who,me) )
        		return ;
       		if ( USER_INVENTORY_D->count_empty_carry(who) < 1 )
		{
			send_user(who,"%c%s",'!',"请清理一下你的包包再来领取吧！");
			return ;	
		}
		who->set_save("dodolook_yuanfen",2);	//已经领取了
		if ( who->get_gender() == 1 )
			item = new("item/04/0436");
		else
			item = new("item/04/0437");
		p = item->move(who,-1);
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    恭喜你获得了%s。\n"ESC"离开",me->get_name(),item->get_name()));
		item->add_to_user(p);
		
        	break;
        case 102:
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    拥有缘分卡的用户一定要先领取缘分宠物再进行缘分任务～！不然你将会失去缘分对对碰的抽奖机会哦～！缘分任务只为有缘人设置，领取缘分任务玩家要求必须是男女双方各一人，双方要处于组队状态。并且，拥有缘分宠物的用户必须和同样拥有缘分宠物的用户一起组队任务才可以噢。当你们完成任务后来我这里交还任务，我会送给你们双方一人一套缘分套装哦！就算任务失败也不用担心，可以取消任务任务重新再来，不过中间要间隔一个小时哦！\n"ESC"离开",me->get_name(),));
        	break;
        case 103:
        	if ( !iStart1 || time() < iStart1 )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    活动还没开始呢，详情请查看官方网站(zg.mop.com)公告。\n"ESC"离开",me->get_name(),));
        		return ;	
        	}
        	if ( check_dodolook(me,who) != 1 )
        		return ;
        	if( !( p = XY_D->get_city_point( -1, IS_CHAR_BLOCK ) ) ) return;
	        z = p / 1000000;  x = ( p % 1000000 ) / 1000;  y = p % 1000;
	        if( !objectp( map = get_map_object(z) ) || !map->is_scene() ) return;
        	name = "噬情魔" + NPC_NAME_D->get_banditi_name();
		who->set_2("dodolook_task.name",name);
		who->set_2("dodolook_task.x",x);
		who->set_2("dodolook_task.y",y);
		who->set_2("dodolook_task.z",z);
		who->set_2("dodolook_task.time",time());
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    在%s国（%d,%d）有个怪物“%s”，顾名思义，就是它作祟将不知多少缠绵情侣之间的真爱一点点吞噬掉。你们的任务就是合力消灭他，为人世间的有缘人扫除天敌。任务达成后记得回到我这里呦！\n"ESC"接受\ntalk %x# welcome.104\n"ESC"离开",me->get_name(),map->get_name(),x,y,name,id,));
        	break;
       case 104:
        	if ( check_dodolook(me,who) != 1 )
        		return ;
       		name = who->get_2("dodolook_task.name");
		if ( !name )
			return ;
		nTeam = who->get_team();
		nTeam -= ({ who });
		member = nTeam[0];
		send_user(nTeam[0],"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    拥有缘分卡的用户一定要先领取缘分宠物再进行缘分任务～！不然你将会失去缘分对对碰的抽奖机会哦～！%s已经接受了缘分任务，你是否一同协助？\n"ESC"接受\ntalk %x# welcome.105\n"ESC"拒绝\ntalk %x# welcome.106\n",me->get_name(),who->get_name(),id,id));
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    请等待%s回应。\n",me->get_name(),member->get_name()));
       		break;
       case 105:
       		nTeam = who->get_team();
       		nTeam -= ({ who,0 });
       		if ( sizeof(nTeam) != 1 )
       			return ;
       		member = who;
       		who = nTeam[0];
       		if ( check_dodolook(me,who) != 1 )
        		return ;
        	iTime = time();
       		name = who->get_2("dodolook_task.name");
       		x = who->get_2("dodolook_task.x");
       		y = who->get_2("dodolook_task.y");
       		z = who->get_2("dodolook_task.z");
       		if ( !name || !x || !y || !z )
       			return ;
       		if( !objectp( map = get_map_object(z) ) || !map->is_scene() ) return;
       		level = who->get_level();
       		if ( level < member->get_level() )
       			level = member->get_level();
       		level += 5;
       		who->delete_2("dodolook_task");
       		npc = new("npc/party/dodolook1");
       		npc->set_name(name);
       		npc->set( "birthday", iTime );
       		NPC_ENERGY_D->init_level(npc, level);
		init_npc(npc,level);
	        npc->add_to_scene(z, x, y, 3);
		map->add_reset(npc);    // 加入复位列表
		
		who->set_save_2("dodolook_task.x",x);
		who->set_save_2("dodolook_task.y",y);
		who->set_save_2("dodolook_task.z",z);
		who->set_save_2("dodolook_task.npcid",getoid(npc));
		who->set_save_2("dodolook_task.time",iTime);
		who->set_save_2("dodolook_task.name",name);
		who->set_save_2("dodolook_task.country",map->get_name());
		who->set_save_2("dodolook_task.member",member->get_number());
                send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_YUANFEN,"缘分对对碰" );     
                send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_YUANFEN,1,"消灭噬情魔" );                  		
                send_user( who, "%c%s", '!',"得到任务 消灭噬情魔" );                  		
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    %s已经同意接受任务。\n",me->get_name(),member->get_name()));

		member->set_save_2("dodolook_task.x",x);
		member->set_save_2("dodolook_task.y",y);
		member->set_save_2("dodolook_task.z",z);
		member->set_save_2("dodolook_task.npcid",getoid(npc));
		member->set_save_2("dodolook_task.time",iTime);
		member->set_save_2("dodolook_task.name",name);
		member->set_save_2("dodolook_task.country",map->get_name());
		member->set_save_2("dodolook_task.member",who->get_number());
                send_user( member, "%c%c%c%w%s", 0x51, 1, 1,TID_YUANFEN,"缘分对对碰" );     
                send_user( member, "%c%c%c%w%w%s", 0x51, 1, 2,TID_YUANFEN,1,"消灭噬情魔" );                  		
                send_user( member, "%c%s", '!',"得到任务 消灭噬情魔" );                  		

       		break; 	
       case 106:
       		nTeam = who->get_team();
       		nTeam -= ({ who,0 });
       		if ( sizeof(nTeam) != 1 )
       			return ;
       		member = who;
       		who = nTeam[0];
       		name = who->get_2("dodolook_task.name");
       		x = who->get_2("dodolook_task.x");
       		y = who->get_2("dodolook_task.y");
       		z = who->get_2("dodolook_task.z");
       		if ( !name || !x || !y || !z )
       			return ;       	
       		who->delete_2("dodolook_task");
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    %s拒绝协助，你将不能获得缘分任务！\n",me->get_name(),member->get_name()));
       		break;
       	case 107:
       		if ( !who->get_save_2("dodolook_task.finish") )
       			return ;
       		if ( !who->is_leader() )
       		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你不是队长，不能完成任务！\n"ESC"离开",me->get_name(),));
			return ;
		}
       		nTeam = who->get_team();
       		nTeam -= ({ who,0 });
       		if ( sizeof(nTeam) == 0 )
       		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    怎么就你一人来呢？你的有缘人呢？还是把你的有缘人带来，再找我领取奖励吧！\n"ESC"离开",me->get_name(),));
			return ;
		}
       		if ( sizeof(nTeam) > 1 )
       		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    人太多了，奖励不好分啊！\n"ESC"离开",me->get_name(),));
			return ;
		}
       		member = nTeam[0];
       		if ( !inside_screen_2(who,member) 
       			|| member->get_number() != who->get_save_2("dodolook_task.member") 
       			|| who->get_number() != member->get_save_2("dodolook_task.member")  )
       		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    怎么就你一人来呢？你的有缘人呢？还是把你的有缘人带来，再找我领取奖励吧！\n"ESC"离开",me->get_name(),));
			return ;
		}	
       		if ( USER_INVENTORY_D->count_empty_carry(who) < 2 )
		{
			send_user(who,"%c%s",'!',"你携带的物品太多了");
			return ;	
		}
		if ( USER_INVENTORY_D->count_empty_carry(member) < 2 )
		{
			send_user(who,"%c%s",'!',"对方携带的物品太多了");
			send_user(member,"%c%s",'!',"你携带的物品太多了");
			return ;	
		}
		iTime = time();
		who->delete_save_2("dodolook_task");
		member->delete_save_2("dodolook_task");
		who->set_save("dodolook_task",iTime);
		member->set_save("dodolook_task",iTime);
		if ( who->get_gender() == 1 )
		{
			item = new("item/std/9602");				
			p = item->move(who,-1);
			item->add_to_user(p);
			item = new("item/std/9603");				
			p = item->move(member,-1);
			item->add_to_user(p);
			send_user(who,"%c%s",';',"缘分对对碰 龙镯 1 七国令 1");
			send_user(member,"%c%s",';',"缘分对对碰 凤镯 1 七国令 1");
		}
		else
		{
			item = new("item/std/9603");				
			p = item->move(who,-1);
			item->add_to_user(p);
			item = new("item/std/9602");				
			p = item->move(member,-1);
			item->add_to_user(p);
			send_user(who,"%c%s",';',"缘分对对碰 凤镯 1 七国令 1");
			send_user(member,"%c%s",';',"缘分对对碰 龙镯 1 七国令 1");
		}
		item = new("item/04/7777");				
		p = item->move(who,-1);
		item->add_to_user(p);
		item = new("item/04/7777");				
		p = item->move(member,-1);
		item->add_to_user(p);
		send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_YUANFEN,1,"" );                  		
		send_user( member, "%c%c%c%w%w%s", 0x51, 1, 2,TID_YUANFEN,1,"" ); 
		send_user( CHAT_D->get_chat(), "%c%s", 0xA3, sprintf(HIY"%s和%s成功完成了缘分测试，让我们祝福他们成为真心相待的有缘人！",who->get_name(),member->get_name()) );
//		if ( who->get_save("dodolook_yuanfen") && member->get_save("dodolook_yuanfen") ) //有缘分卡的记录下来
			log_file("dodolook_task.txt",sprintf("%s %d %s(%d) %s(%d) 完成任务\n",short_time(),"sys/main/main"->get_host(),who->get_name(),who->get_number(),member->get_name(),member->get_number())); 	
       		break;
       	case 108:
       		if ( !who->get_save("dodolook_task") )
       		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    很不幸，你没有通过缘分测试，你没有获得进入缘分驿站的资格！想进入缘分驿站就赶快去参加缘分测试活动吧！\n"ESC"离开",me->get_name(),));
			return ;
		}
        	send_user(who, "%c%c%w%s", 0x5a, 0, 3, "传送中……");
        	p = get_jumpin(805,1);
	        who->set_2("travel.z", 805);
	        who->set_2("travel.p", p);
	        set_effect(who, EFFECT_TRAVEL, 3);		
       		break;
        }
}

void go_there()
{
	object me=this_object();
	
	me->add_to_scene(802,78,43,2);
}

void init_npc(object npc, int level)
{
	int p;
	
	if ( !(p=get("test_rate")) )
		p = random(100);
	if ( p < 20)	//低物防高敏型
	{
		npc->set_skill(348,level);
		npc->set_skill(251,level);
		npc->set_skill(241,level);
		npc->set_char_picid(811);
                npc->set_walk_speed(4);
                npc->set_attack_speed(10);	
                npc->add_dp(-1*npc->get_dp()/4);
                npc->add_max_hp(npc->get_max_hp()*8);	
                npc->add_sp(npc->get_sp()*2);
                npc->add_ap(npc->get_ap()*4/5);
                npc->add_mp(npc->get_mp()/2);  
                npc->set("dodolook.type",1);              		
	}
	else if ( p < 40 )	//高物防低法防型
	{
		npc->set_skill(221,level);
		npc->set_skill(231,level);
		npc->set_char_picid(0252);
                npc->set_walk_speed(4);
                npc->set_attack_speed(10);	
                npc->add_dp(npc->get_dp()*3);
                npc->add_max_hp(npc->get_max_hp()*4); 	
                npc->add_pp(-1*npc->get_pp()*3/10);                
                npc->add_ap(npc->get_ap()*4/5);                
                npc->add_mp(npc->get_mp()/2);  
                npc->set("dodolook.type",2);              		
	}
	else if ( p < 60 )	//高法防低物防型
	{
		npc->set_skill(424,level);
		npc->set_skill(423,level);
		npc->set_skill(425,level);
		npc->set_char_picid(8010);
                npc->set_walk_speed(4);
                npc->set_attack_speed(10);	
                npc->add_dp(-1*npc->get_dp()/4);
                npc->add_max_hp(npc->get_max_hp()*4); 	
                npc->add_sp(npc->get_sp());  
                npc->add_pp(npc->get_pp()*3/2);                
                npc->add_cp(npc->get_cp());
		npc->add_mp(npc->get_mp()*6);
                npc->set("dodolook.type",3);              		
	}	
	else if ( p < 70 )	//长血型：拳脚类
	{
		npc->set_skill(317,level);
		npc->set_skill(211,level);
		npc->set_char_picid(8000);
                npc->set_walk_speed(3);
                npc->set_attack_speed(10);	
                npc->add_dp(-1*npc->get_dp()/5);        
                npc->add_max_hp(npc->get_max_hp()*20); 
                npc->add_pp(-1*npc->get_pp()/5);                
                npc->add_cp(npc->get_cp()/2);                 
                npc->add_ap(npc->get_ap()*9/10);  
                npc->set("dodolook.type",4);              		
	}
	else if ( p < 90 )	//长血高物防高法防型：远程暗器类
	{
		npc->set_skill(261,level);
		npc->set_char_picid(8012);
                npc->set_walk_speed(4);
                npc->set_attack_speed(10);	
		npc->add_dp(npc->get_dp()*9/20);
		npc->add_max_hp(npc->get_max_hp()*5); 
 		npc->add_sp(npc->get_sp()*3);
 		npc->add_pp(npc->get_pp()*9/5);
 		npc->add_mp(npc->get_mp());
 		npc->add_ap(npc->get_ap()/2);
                npc->set("dodolook.type",5);              		
	}
	else 	//强攻型加召唤
	{
		npc->set_skill(414,level);
		npc->set_char_picid(8013);
                npc->set_walk_speed(4);
                npc->set_attack_speed(8);	
                npc->add_dp(npc->get_dp()*9/20);
                npc->add_ap(npc->get_ap()); 
                npc->add_max_hp(npc->get_max_hp()*5);                 
                npc->add_sp(npc->get_sp()*3);  
                npc->add_pp(npc->get_pp()*9/20);      
                npc->add_mp(npc->get_mp()*3/2);  
                npc->set("dodolook.type",6);              		
	}		

}


void task_giveup(object who)
{
	int id,iTime;
	object npc;
	
	id = who->get_save_2("dodolook_task.npcid");
	if ( !id )
		return ;
	if ( who->get_save_2("dodolook_task.finish") )
       			return ;
	iTime = who->get_save_2("dodolook_task.time");
	who->delete_save_2("dodolook_task.x");
	who->delete_save_2("dodolook_task.y");
	who->delete_save_2("dodolook_task.z");
	who->delete_save_2("dodolook_task.npcid");
	who->delete_save_2("dodolook_task.name");
	who->delete_save_2("dodolook_task.member");
	who->delete_save_2("dodolook_task.country");
	send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_YUANFEN,1,"" );                  		

	npc = find_any_object(sprintf("%x#",id));
	if ( npc && npc->get("birthday") == iTime )
	{
		npc->remove_from_scene();
		destruct(npc);
	}
}

int check_dodolook(object me, object who)
{
	int size;
	object *nTeam,member;
	
	if ( !who->is_leader() )
	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你不是队长，不能接任务！\n"ESC"离开",me->get_name(),));
		return 0;
	}
	nTeam = who->get_team();
	if ( (size=sizeof(nTeam)) == 0 )
	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你还是和你的有缘人一起来吧！\n"ESC"离开",me->get_name(),));
		return 0;
	}
	nTeam -= ({0});
	if ( (size=sizeof(nTeam)) == 1 )
	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你还是和你的有缘人一起来吧！\n"ESC"离开",me->get_name(),));
		return 0;
	}
	if ( (size=sizeof(nTeam)) > 2 )
	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    本姑娘只为有缘的男女双方（男女双方各一人）提供任务哦！\n"ESC"离开",me->get_name(),));
		return 0;
	}
	nTeam -= ({who});
	member = nTeam[0];
	if ( who->get_gender() == member->get_gender() )
	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    本姑娘只为有缘的男女双方（男女双方各一人）提供任务哦！\n"ESC"离开",me->get_name(),));
		return 0;
	}
	if ( who->get_level() < 30 )
	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    等你有点实力再来找我接取此任务吧～！（玩家等级≥30级）\n"ESC"离开",me->get_name(),));
		return 0;
	}
	if ( member->get_level() < 30 )
	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你的队中好像有人的实力不足以接取此任务～！（玩家等级≥30级）\n"ESC"离开",me->get_name(),));
		return 0;
	}
	//是否都为缘分卡片用户
	if ( (who->get_save("dodolook_yuanfen") && !member->get_save("dodolook_yuanfen")) || (!who->get_save("dodolook_yuanfen") && member->get_save("dodolook_yuanfen")) )
	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你们是有缘人吗？（必需是都拥有缘分宠物或都没有缘分宠物的用户组队才可以）我想还是去阅读一下我定的任务须知再来吧！\n"ESC"离开",me->get_name(),));
		return 0;
	}
	if ( who->get_save("dodolook_task") || member->get_save("dodolook_task") )
	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你已经帮助过我了，不好意思再次麻烦你！\n"ESC"离开",me->get_name(),));
		return 0;
	}
	if ( who->get_save_2("dodolook_task.npcid")  )
 	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    由于你们队伍中%s没有完成上次缘分任务，所以该任务不能领取。\n"ESC"离开",me->get_name(),who->get_name()));
		return 0;
	}
	if ( member->get_save_2("dodolook_task.npcid") )
 	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    由于你们队伍中%s没有完成上次缘分任务，所以该任务不能领取。\n"ESC"离开",me->get_name(),member->get_name()));
		return 0;
	}
	if ( gone_time(member->get_save_2("dodolook_task.time")) < 3600 || gone_time(who->get_save_2("dodolook_task.time")) < 3600 )
 	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    可惜，刚刚有人先你一步，帮助我去消灭那噬情魔了，现在很太平，暂时还没有发现噬情魔，你过段时间再来吧！\n"ESC"离开",me->get_name()));
		return 0;
	}
	if ( !inside_screen_2(me,who) || !inside_screen_2(who,member) )
	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你的队友不在现场啊！\n"ESC"离开",me->get_name()));
		return 0;
	}
	return 1;	
}
//查询是否有对应的缘分卡，有则赋值。
int check_yuanfen(object me,object who)
{
	int status;
	string flag;
	if( me->get_save("dodolook_yuanfen") )	//已经查询
		return 1;
	status = me->get_pay_money_buy_item();
	if ( status == 0 )
	{
		if ( me->get_gender() == 1 )
			flag = "1009";
		else
			flag = "1010";
                me->set("phpnum", to_int(flag));
		me->set_pay_money_buy_item(1);
		me->set_pay_type(4);
		me->set_buy_item_cmd_string( sprintf("%x# welcome.", getoid(who) ) );
		db_user_pay( me, sprintf( "%s:80\n"
               		"GET http:/""/%s/getgoods.php?t=%s&u=%d&o=%d&n=%s&ip=%s&r=%d&h=%d\r\n", MAIN_D->get_php_ip(),
               		MAIN_D->get_php_ip(), short_time_2(), me->get_acountid(), me->get_number(), flag, get_ip_name(me), MAIN_D->get_region(), MAIN_D->get_host() ) );
log_file("php.dat", sprintf( "%s:80\n"
               		"GET http:/""/%s/getgoods.php?t=%s&u=%d&o=%d&n=%s&ip=%s&r=%d&h=%d\r\n", MAIN_D->get_php_ip(),
               		MAIN_D->get_php_ip(), short_time_2(), me->get_acountid(), me->get_number(), flag, get_ip_name(me), MAIN_D->get_region(), MAIN_D->get_host() ) );
		return 0;
	}
	if (status!=8)
	{
		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
			who->get_name()+":\n    您的申请正在处理中，请稍候。\n"
			ESC"离开" );
	        return 0;
	}
	me->set_save("dodolook_yuanfen",1);	//有缘分卡
	me->set_pay_money_buy_item(0);
	return 1;
}


int set_open(object who,string arg)
{
	int date1,year1,mon1,day1;
	if ( sscanf(arg ,"%d",date1) != 1 )
	{
		send_user(who,"%c%s",'!',"错误的格式！");	
		return 0;
	}
	year1 = date1 /10000;
	mon1 = date1 % 10000 / 100;
	day1 = date1 % 10000 % 100;
	if ( !year1 || !mon1 || !day1 )
	{
		send_user(who,"%c%s",'!',"错误的时间！");	
		return 0;
	}
	iStart1 = mktime(year1,mon1,day1,0,0,0);	

	tell_user(who,"活动开启：%s！",arg);	
	send_user(who,"%c%s",'!',"活动开启！");	
	save();
	return 1;
}

int set_close(object who)
{
	iStart1 = 0;	
	send_user(who,"%c%s",'!',"活动关闭！");	
	save();
	return 1;	
}