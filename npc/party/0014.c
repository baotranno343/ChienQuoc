#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <equip.h>

inherit OFFICER;
int iStart1,iFinish1;
// 函数：获取人物造型
int get_char_picid() { return 6009; }
void do_welcome(string arg);
void read_renwang();

// 函数：构造处理
void create()
{
        set_name("战国活动使者");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );
	iStart1 = mktime(2007,5,1,0,0,0);	
	iFinish1 = mktime(2007,5,8,0,0,0);	
        setup();
        if ( !clonep(this_object()) )
        	return ;
        if (MAIN_D->get_host_type()==2)		//台湾除外
        	call_out("go_there",2);
}

void do_look(object who)
{
	int id = getoid(this_object());
	int iTime=time();
	
	if (MAIN_D->get_host_type()==2)
		return ;
	if ( iTime > iStart1 && iTime < iFinish1 )	
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("%s：\n    亲爱的"HIR"%s"NOR"你好，我是天帝派来的战国帮助使者。为了答谢广大玩家对战国的热爱，我们会在内测的一个月内陆续推出玩家帮帮帮、战国王者征集令、经验双倍节假日、宝藏大搜寻四大活动，希望你可以在这个活动月内可以尽情享受叱咤战国的快乐。\n"ESC"领取玩家帮帮帮奖励\ntalk %x# welcome.1\n"ESC"什么是玩家帮帮帮？\ntalk %x# welcome.2\n"ESC"领取战国王者的奖励\ntalk %x# welcome.3",this_object()->get_name(),who->get_name(),id,id,id));
	else
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("%s：\n    亲爱的"HIR"%s"NOR"你好，我是天帝派来的战国帮助使者。为了答谢广大玩家对战国的热爱，我们会在内测的一个月内陆续推出玩家帮帮帮、战国王者征集令、经验双倍节假日、宝藏大搜寻四大活动，希望你可以在这个活动月内可以尽情享受叱咤战国的快乐。\n"ESC"领取战国王者的奖励\ntalk %x# welcome.3\n"ESC"离开",this_object()->get_name(),who->get_name(),id,));
	
}


void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
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
        switch(flag)
        {
        case 1:
        	if ( time() < iStart1 )
        	{
			send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("%s：\n    在1月19日到1月31日期间，战国将会举办玩家帮帮帮活动，玩家帮帮帮是通过玩家之间的组队练级互相协作会获得经验奖励，如果你跟其他玩家一起组队杀怪练级，在互相帮助的过程中，我会给予你经验奖励，与你组队的玩家越多，我奖励你的经验也就越多，赶快加入玩家帮帮帮的行列吧。\n",me->get_name()));
        		return ;	
        	}
        	if ( time() > iFinish1 )
        	{
			send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("%s：\n    玩家帮帮帮的活动已经结束了，祝您游戏愉快。\n",me->get_name()));
        		return ;	
        	}
        	i = who->get_save("exp20070112");
        	if ( i<=0 )
        	{
			send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("%s：\n    你并没有获得任何玩家帮帮帮的活动奖励，希望你尽快去寻找其他玩家一齐打怪练级、互相帮助吧。到时候，你就可以回来跟我要奖励了。\n"ESC"离开",me->get_name()));
        		return ;	
        	}
        	who->add_exp(i);
        	tell_user(who,"你获得%d点的经验奖励。",i);
        	who->delete_save("exp20070112");
        	break;
        case 2:
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("%s：\n    在1月19日到1月31日期间，战国将会举办玩家帮帮帮活动，玩家帮帮帮是通过玩家之间的组队练级互相协作会获得经验奖励，如果你跟其他玩家一起组队杀怪练级，在互相帮助的过程中，我会给予你经验奖励，与你组队的玩家越多，我奖励你的经验也就越多，赶快加入玩家帮帮帮的行列吧。\n"ESC"我这就去找人组队练级",me->get_name()));
        	break;
        case 3:
        	if ( time() < iFinish2 )
        	{
			send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("%s：\n    不要心急，活动的时间从1月19日至2月12日结束，活动结束后，我们将会根据玩家的等级挑选出本服务器七个门派的王者出来。到时你能成为等级最高的战国王者再来找我吧～！\n"ESC"离开",me->get_name()));
        		return ;		
        	}
        	name = who->get_name();
        	id = who->get_number();
		if ( !mpXinrenwang[name] || mpXinrenwang[name]["id"] != id )
		{
			send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("%s：\n    你好象不是万人瞩目的战国王者吧？\n"ESC"离开",me->get_name()));
        		return ;		
        	}
		if ( who->get_save("zgwangzhe")  )
			return ;
		level = mpXinrenwang[name]["level"];
		if ( level == 1 || level == 2 )
		{
			iLev = who->get_level() / 10 * 10 + 10;
			nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),iLev,WEAPON_TYPE);
	        	tmp = nTmp[random(sizeof(nTmp))];
	        	if ( !stringp(tmp) )
	        		return ;
	        	item = new(tmp);
	        	p = item->move(who,-1);
	        	if ( !p )
	        	{
				send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"战国活动使者：\n    您身上的物品好像太多了点，先到商店或者当铺清空一下您的包包，再来本使者这里领取礼物吧～");
	        		destruct(item);
	        		return;	
	        	}
	        	if ( level == 1 )
	        		ITEM_EQUIP_D->init_equip_prop_3(item);
	        	else
	        		ITEM_EQUIP_D->init_equip_prop_1(item);
	        	item->add_to_user(p);
	        }
		who->add_cash(500000);
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"战国活动使者：\n    经过这段时间的考验和您自己的努力，你已经成为万人瞩目的战国王者了，作为对您的鼓励，这是给您的奖品～！");
		CHAT_D->sys_channel(0,sprintf(HIG"恭喜"HIY"%s"HIG"成为%s的战国王者，期待"HIY"%s"HIG"在战国世界中有更加出色的表现！",who->get_name(),who->get_fam_name(),who->get_name()));
		who->set_save("zgwangzhe",time());
		log_file("zgwangzhe.txt",sprintf("%s %s(%d)领取战国王者%s第%d名奖励\n",short_time(),name,id,who->get_fam_name(),level));
        	break;
	}

}

void go_there()
{
	object me=this_object();
	
	me->add_to_scene(802,78,43,2);
}

void read_renwang()
{
	int i,size,num,level;
	string cTmp,*line,tmp;
	
	cTmp = read_file("npc/party/xinrenwang.txt");
	if ( sizeof(cTmp) == 0 )
		return;
	line = explode( cTmp, "\n" );
	size = sizeof(line);
	mpXinrenwang = ([]);
        for( i = 0; i < size; i ++ ) 
	{
		if ( line[i][0..0] == "#" )
			continue;
		if ( sscanf(line[i],"%s %d %d",tmp,num,level) != 3 )
			continue;
		mpXinrenwang[tmp] = (["id":num,"level":level]);
	}
}
