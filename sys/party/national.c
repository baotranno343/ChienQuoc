/*******************************
	**国庆活动**
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
void get_xigua_uncle();
void destruct_xigua_uncle();
void get_xigua();
void destruct_xigua();
void get_bad_npc();
void destruct_bad_npc();
int get_close();
object *Bad_npc,*Xigua,Xigua_uncle;
int iStart_b,iFinish1,close_national;
// 函数：生成二进制码
void SAVE_BINARY() { }
string get_save_file()	{ return "data/party_switch"SAVE_EXTENSION;}
void create()
{
	restore();
	Bad_npc = ({});
	Xigua = ({});
	iStart_b = mktime(2007,10,1,7,50,0);	
	iFinish1 = mktime(2007,10,7,20,0,0);	
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
	if ( iTime > iFinish1 )
	{
		destruct_xigua_uncle();
		destruct_xigua();
		destruct_bad_npc();
		return ;
	}

	if ( iTime < iStart_b )	//没到时间
	{
		call_out("check_time",iStart_b-iTime);
		return ;
	}
	if ( mixTime[TIME_HOUR] >= 20 )
	{
		call_out("check_time",3600*24-mixTime[TIME_HOUR]*3600-mixTime[TIME_MIN]*60);
		return ;
	}
	if ( mixTime[TIME_MDAY]!=1 && mixTime[TIME_HOUR] < 8 )
	{
		call_out("check_time",3600*8-mixTime[TIME_HOUR]*3600-mixTime[TIME_MIN]*60);
		return ;
	}
	if ( mixTime[TIME_MDAY]==1 && mixTime[TIME_HOUR] < 8 )
	{
		CHAT_D->sys_channel(0,HIY"各位玩家国庆节快乐，在这个举国同庆的喜庆日子里，大话战国也举办了为期7天的活动，让你的战国之旅永不沉闷，精彩活动即将开始，请各位玩家注意！");
		call_out("check_time2",60*(60-mixTime[TIME_MIN]));
		log_file( "national.dat", sprintf( "%d月%d日 %d ：%d 国庆活动开始。\n",mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN]) );
	}
	else
		call_out("check_time2",1);

}

void check_time2()
{
	int iTime;
	mixed *mixTime;
//	iTime = time();
	iTime = get_party_time();
	mixTime = localtime(iTime);
	get_xigua_uncle();
	CHAT_D->sys_channel(0,HIY"最近大话战国里风调雨顺，农作物都有了很好的收成，尤其是水果，更是大丰收。各个国家农民伯伯都非常开心，但是最近西瓜伯伯却遇到了一些问题。他发现自己没有时间去把自己的西瓜采集回来，于是想委托大话战国的好心玩家帮忙，大家愿意帮助西瓜伯伯吗？");
	call_out("check_time3",1);
	log_file( "national.dat", sprintf( "%d月%d日 %d ：%d 当天的国庆活动开始。\n",mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN]) );
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
	if ( iTime > iFinish1 )
	{
		destruct_xigua_uncle();
		destruct_xigua();
		destruct_bad_npc();
		CHAT_D->sys_channel(0,HIY"国庆的七天活动到此完全结束了，谢谢大家的参与，"HIR"西瓜伯伯"HIY"也对大家的衷心帮忙表示感谢，最后祝大家国庆快乐，游戏更快乐。");
		log_file( "national.dat", sprintf( "%d月%d日 %d ：%d 国庆活动全部结束。\n",mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN]) );
		return ;
	}
	if ( mixTime[TIME_HOUR] >= 20 )
	{
		CHAT_D->sys_channel(0,HIY"今天的的国庆活动就到此了，"HIR"西瓜伯伯"NOR"很感谢大家的帮忙，请大家明天再继续帮助他采集西瓜吧。");
		call_out("check_time3",3600*24-mixTime[TIME_HOUR]*3600-mixTime[TIME_MIN]*60);
		log_file( "national.dat", sprintf( "%d月%d日 %d ：%d 当天的国庆活动结束。\n",mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN]) );
		return ;
	}
	if ( mixTime[TIME_HOUR] < 8 )
	{
		call_out("check_time3",3600*8-mixTime[TIME_HOUR]*3600-mixTime[TIME_MIN]*60);
		return ;
	}
	if ( mixTime[TIME_HOUR]%2 == 1 )
	{
		get_bad_npc();
		CHAT_D->sys_channel(0,HIY"大事不好了，一些坏小猴、坏小猪和坏大熊出现在了"HIR"西瓜伯伯"HIY"的西瓜田里，它们一定是想抢走西瓜，大家赶紧把它们捉起来，然后交给"HIR"西瓜伯伯"HIY"对它们略惩小戒吧！");
		call_out("check_time3",60*(60-mixTime[TIME_MIN]));
		log_file( "national.dat", sprintf( "%d月%d日 %d ：%d 放入坏动物。\n",mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN]) );
		return ;
	}
	if ( mixTime[TIME_HOUR]%2 == 0 )
	{
		get_xigua();
		CHAT_D->sys_channel(0,HIY"大话战国的国庆活动已经开始了，请大家前往"HIR"周国的126，120"HIY"找"HIR"西瓜伯伯"HIY"，帮助他采集西瓜吧。");
		call_out("check_time3",60*(60-mixTime[TIME_MIN]));
		log_file( "national.dat", sprintf( "%d月%d日 %d ：%d 放入西瓜。\n",mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN]) );
		return ;
	}
}
// 放入西瓜伯伯
void get_xigua_uncle()
{
	if ( !objectp(Xigua_uncle) )
	{
		Xigua_uncle = new("/npc/party/watermelon_uncle");
		Xigua_uncle->add_to_scene(80,126,120,3);
	}
}

// 移除西瓜伯伯
void destruct_xigua_uncle()
{
	if ( objectp(Xigua_uncle) )
	{
		Xigua_uncle->remove_from_scene();
		destruct(Xigua_uncle);
	}
}

//  放入西瓜
void get_xigua()
{
	int i,size,z,p,x,y,j,count;
	object item;
	
	destruct_xigua();

	for(j=1;j<9;j++)
	{
		z = j*10;
		for(i=0;i<50;i++)
		{
			if( !( p = efun::get_xy_point( z, IS_CHAR_BLOCK ) ) )
				continue;
			x = ( p % 1000000 ) / 1000;  y = p % 1000;
			item = new("/item/04/0458");
			if ( !objectp(item) )
				continue;
			item->add_to_scene(z,x,y);	
			Xigua += ({ item });
		}
	}

}

//  移除西瓜
void destruct_xigua()
{
	int i,size;

	for(i=0,size=sizeof(Xigua);i<size;i++)
	{
		if ( !objectp(Xigua[i]) )
			continue;
		if ( get_d(Xigua[i]) )
			continue;
		Xigua[i]->remove_from_scene();
		destruct(Xigua[i]);
	}
	Xigua = ({});
}

//  放入坏动物
void get_bad_npc()
{
	int i,size,z,p,x,y,j,count;
	object item;
	
	destruct_bad_npc();

	for(j=1;j<9;j++)
	{
		z = j*10;
		for(i=0;i<100;i++)
		{
			if( !( p = efun::get_xy_point( z, IS_CHAR_BLOCK ) ) )
				continue;
			x = ( p % 1000000 ) / 1000;  y = p % 1000;
			item = new("/npc/party/national_npc01");
			if ( !objectp(item) )
				continue;
			item->add_to_scene(z,x,y);	
			Bad_npc += ({ item });
		}
		for(i=0;i<50;i++)
		{
			if( !( p = efun::get_xy_point( z, IS_CHAR_BLOCK ) ) )
				continue;
			x = ( p % 1000000 ) / 1000;  y = p % 1000;
			item = new("/npc/party/national_npc02");
			if ( !objectp(item) )
				continue;
			item->add_to_scene(z,x,y);	
			Bad_npc += ({ item });
		}
		for(i=0;i<10;i++)
		{
			if( !( p = efun::get_xy_point( z, IS_CHAR_BLOCK ) ) )
				continue;
			x = ( p % 1000000 ) / 1000;  y = p % 1000;
			item = new("/npc/party/national_npc03");
			if ( !objectp(item) )
				continue;
			item->add_to_scene(z,x,y);	
			Bad_npc += ({ item });
		}
	}

}

//  移除坏动物
void destruct_bad_npc()
{
	int i,size;

	for(i=0,size=sizeof(Bad_npc);i<size;i++)
	{
		if ( !objectp(Bad_npc[i]) )
			continue;
		Bad_npc[i]->remove_from_scene();
		destruct(Bad_npc[i]);
	}
	Bad_npc = ({});
}

void before_destruct()
{
	if ( objectp(Xigua_uncle) )
	{
		Xigua_uncle->remove_from_scene();
		destruct(Xigua_uncle);
	}
}

void set_close()
{
	close_national=0;
	save();
	destruct_xigua_uncle();
	destruct_xigua();
	destruct_bad_npc();
	check_time();
}

void set_open()
{
	close_national=1;
	save();
	check_time();
}


int get_status(){return close_national;}