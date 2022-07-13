/*******************************
	**重阳活动**
*******************************/

#include <time.h>
#include <ansi.h>
#include <cmd.h>
#include <npc.h>
#include <city.h>
#include <action.h>
#include <effect.h>
#include <skill.h>
#include <public.h>
inherit SAVE_F;
void get_party_npc();
void destruct_party_npc();


void get_party_item();
void destruct_party_item();
int get_close();
object *Party_item,Party_npc;
int iStart_b,iFinish1,iFinish_a,close_national;
// 函数：生成二进制码
void SAVE_BINARY() { }
string get_save_file()	{ return "data/party_switch"SAVE_EXTENSION;}
void create()
{
	restore();
	Party_item = ({});

	iStart_b = mktime(2007,10,19,9,50,0);	
	iFinish1 = mktime(2007,10,20,22,0,0);	
	iFinish_a = mktime(2007,10,23,22,0,0);
	call_out("check_time",1);
}

void check_time()
{
	int iTime,rate,level,z,p,x,y;
	int i,*nScene,size;
	mixed *mixTime;
	object robber;
	
	remove_call_out("check_time");
//	iTime = time();
	iTime = get_party_time();
	mixTime = localtime(iTime);
	if (!close_national) return;

	if ( iTime < iStart_b )	//没到时间
	{
		call_out("check_time",iStart_b-iTime);
		return ;
	}
	if ( iTime > iFinish_a )
	{
		destruct_party_npc();
		destruct_party_item();
		return;
	}
	if(iTime > iFinish1)
	{
		destruct_party_item();
		get_party_npc();
		call_out("destruct_party_npc",iFinish_a - iTime);
		return;
	}
	CHAT_D->sys_channel(0,HIY"各位大话战国的玩家朋友们，重阳节活动将在十分钟后开启，各位玩家赶快做好准备哦！");
	log_file( "chongyang.dat", sprintf( "%d月%d日 %d ：%d 当天的重阳活动准备。\n",mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN]) );
	call_out("check_time2",600);

}

void check_time2()
{
	int iTime;
	mixed *mixTime;
//	iTime = time();
	iTime = get_party_time();
	mixTime = localtime(iTime);
	get_party_npc();
	get_party_item();
	log_file( "chongyang.dat", sprintf( "%d月%d日 %d ：%d 放入重阳四宝。\n",mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN]) );
	CHAT_D->sys_channel(0,HIY"可爱的重阳老人来已经来到了我们的战国世界，目前他正在新手村找人帮忙收集重阳四宝，大家赶快过去帮帮他啊！");
	call_out("check_time3",60*(60-mixTime[TIME_MIN]));
	log_file( "chongyang.dat", sprintf( "%d月%d日 %d ：%d 当天的重阳活动开始。\n",mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN]) );
}

void check_time3()
{
	int iTime,rate,level,z,p,x,y;
	int i,*nScene,size;
	mixed *mixTime;
	object robber;
	
	remove_call_out("check_time3");
//	iTime = time();
	iTime = get_party_time();	
	mixTime = localtime(iTime);
	if (!close_national) return;

	if ( iTime > iFinish_a )
	{
		destruct_party_npc();
		destruct_party_item();
		return;
	}
	if(iTime > iFinish1)
	{
		destruct_party_item();
		call_out("destruct_party_npc",iFinish_a - iTime);
		CHAT_D->sys_channel(0,HIY"重阳节活动到现在结束了，感谢各位热心的玩家帮助了重阳老人，重阳老人有感于大家的热情，而且还发现战国世界十分有趣，所以决定继续在战国里呆三天，希望还没有来得及兑换物品的玩家赶快带着重阳四宝去找重阳老人兑换啊！");
		log_file( "chongyang.dat", sprintf( "%d月%d日 %d ：%d 重阳活动结束。\n",mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN]) );
		return;
	}
	get_party_item();
	CHAT_D->sys_channel(0,HIY"重阳四宝散落在了新手村和七国郊外，大家赶快去帮重阳老人收集啊！");
	log_file( "chongyang.dat", sprintf( "%d月%d日 %d ：%d 放入重阳四宝。\n",mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN]) );
	call_out("check_time3",3600);
}
// 放入活动NPC
void get_party_npc()
{
	if ( !objectp(Party_npc) )
	{
		Party_npc = new("/npc/party/chongyang");
		Party_npc->add_to_scene(1,156,130,6);
	}
}

// 移除活动NPC
void destruct_party_npc()
{
	if ( objectp(Party_npc) )
	{
		Party_npc->remove_from_scene();
		destruct(Party_npc);
		CHAT_D->sys_channel(0,HIY"重阳老人在战国期间得到了很多热心玩家的帮助，感动得眼泪哗啦啦直流，都不想走了，一个黑洞突然出现，把恋恋不舍的重阳老人拖走了，最后从里面隐约传来一个不甘声音：“我不想走啊！……”");
	}
}

//  放入活动物品
void get_party_item()
{
	int i,size,z,p,x,y,j,count;
	object item;
	
	destruct_party_item();

	for(j=1;j<9;j++)
	{
		z = j*10;
		if (z==80) z=1;
		for(i=0;i<100;i++)
		{
			if( !( p = efun::get_xy_point( z, IS_CHAR_BLOCK ) ) )
				continue;
			x = ( p % 1000000 ) / 1000;  y = p % 1000;
			item = new("/item/04/0459");
			if ( !objectp(item) )
				continue;
			item->add_to_scene(z,x,y);	
			Party_item += ({ item });
		}
		for(i=0;i<50;i++)
		{
			if( !( p = efun::get_xy_point( z, IS_CHAR_BLOCK ) ) )
				continue;
			x = ( p % 1000000 ) / 1000;  y = p % 1000;
			item = new("/item/04/0460");
			if ( !objectp(item) )
				continue;
			item->add_to_scene(z,x,y);	
			Party_item += ({ item });
		}
		for(i=0;i<30;i++)
		{
			if( !( p = efun::get_xy_point( z, IS_CHAR_BLOCK ) ) )
				continue;
			x = ( p % 1000000 ) / 1000;  y = p % 1000;
			item = new("/item/04/0461");
			if ( !objectp(item) )
				continue;
			item->add_to_scene(z,x,y);	
			Party_item += ({ item });
		}
		for(i=0;i<20;i++)
		{
			if( !( p = efun::get_xy_point( z, IS_CHAR_BLOCK ) ) )
				continue;
			x = ( p % 1000000 ) / 1000;  y = p % 1000;
			item = new("/item/04/0462");
			if ( !objectp(item) )
				continue;
			item->add_to_scene(z,x,y);	
			Party_item += ({ item });
		}

	}

}

//  移除活动物品
void destruct_party_item()
{
	int i,size;

	for(i=0,size=sizeof(Party_item);i<size;i++)
	{
		if ( !objectp(Party_item[i]) )
			continue;
		if ( get_d(Party_item[i]) )
			continue;
		Party_item[i]->remove_from_scene();
		destruct(Party_item[i]);
	}
	Party_item = ({});
}

void set_close()
{
	close_national=0;
	save();
	destruct_party_npc();
	destruct_party_item();

	check_time();
}

void set_open()
{
	close_national=1;
	save();
	check_time();
}


int get_status(){return close_national;}