/*****************************
	**挖宝**
*****************************/
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
int iStart1,iFinish1;
int check_time();
void generate_chutou(object who);
void set_open(object who,string arg);
void set_close(object who);
int is_open();
void next_session();
//生成二进制代码
void SAVE_BINARY(){}
string get_save_file()	{ return "data/wabaozongdongyuan"SAVE_EXTENSION;}
//创建
void create()
{
	restore();
	check_time();//这里开启检查时间函数。
}

//检查时间
int check_time()
{
	int iHour;
	int interval;
	remove_call_out("check_time");
	iHour = time();
	if( iHour < iStart1)
	{
		if((interval = iStart1 - iHour)<=300)
		{
			USER_D->user_channel(sprintf("挖宝总动员活动在%d分钟后正式开始，请各位玩家"
			"做好准备，在"HIR"周国的王捕头"NOR"处领取挖宝小锄头。",interval/60));
			call_out("check_time",interval);
		}
		else
		{
			call_out("check_time",interval- 300);
		}
	}
	else if(iHour >= iStart1&& iHour < iFinish1)
	{
		USER_D->user_channel("挖宝总动员活动现在正式开始，请各位玩家去"
		HIR"周国的王捕头"NOR"处领取挖宝小锄头。");
		call_out("check_time",iFinish1-iHour);
	}
	else if(iHour >= iFinish1)
	{
		if((interval = iHour - iFinish1)< 30)
		{
			USER_D->user_channel("今天的挖宝总动员活动现在已经结束了，已经领取了挖宝小锄头的"
			"玩家可以继续挖宝。让我们期待下次的活动时间吧~");
			next_session();
		}
	}		
}
//下次活动时间调整。
void next_session()
{
	mixed time_info ;
	time_info= localtime(iStart1);
	if(time_info[TIME_WDAY] == 6)
	{
		iStart1 = iFinish1 + 3600*24;
		iFinish1 = iStart1 + 3600;
		call_out("check_time",3);
		save();
		
	}
	if(time_info[TIME_WDAY] == 0)
	{
		iStart1 = iFinish1+ 3600*24*6;
		iFinish1 = iStart1 + 3600;
		call_out("check_time",3);
		save();
	}
}
//生成锄头
void generate_chutou(object who)
{
	int move_result;
	object goods;
	goods = new("item/std/hoe");
	if(!goods)
	{
		return ;
	}
	if(move_result = goods->move(who,-1))
	{
		goods->add_to_user(move_result);
	}
	else
	{
		destruct(goods);
	}
}

//开启任务
void set_open(object who,string arg)
{
	int year,mon,day,hour,min;
	string cTmp1,cTmp2;
	if ( sscanf(arg ,"%s-%s",cTmp1,cTmp2) != 2 )
	{
		send_user(who,"%c%s",'!',"错误的格式！");	
		return 0;
	}
	//20070518 2000
	year = to_int(cTmp1[0..3]);
	mon = to_int(cTmp1[4..5]);
	day = to_int(cTmp1[6..7]);
	hour = to_int(cTmp1[8..9]);
	min = to_int(cTmp1[10..11]);
	iStart1 = mktime(year,mon,day,hour,min,0);	//活动开始时间

	year = to_int(cTmp2[0..3]);
	mon = to_int(cTmp2[4..5]);
	day = to_int(cTmp2[6..7]);
	hour = to_int(cTmp2[8..9]);
	min = to_int(cTmp2[10..11]);
	iFinish1 = mktime(year,mon,day,hour,min,0);	//结束时间

	if ( !iStart1 || !iFinish1 )
	{
		send_user(who,"%c%s",'!',"错误的时间！");	
		return 0;
	}
	if ( iStart1 > iFinish1 || iFinish1 < time() )
	{
		send_user(who,"%c%s",'!',"错误的时间！！");	
		return 0;
	}
	tell_user(who,"挖宝活动开启：%s！",arg);	
	send_user(who,"%c%s",'!',"挖宝活动开启！");
	call_out("check_time",3);	
	check_time();
	save();
}

//关闭任务
void set_close(object who)
{
	remove_call_out("check_time");
	iStart1 = 0;
	iFinish1 = 0;
	send_user(who,"%c%s",'!',"挖宝活动关闭！");
	save();
}
//是否开启活动。
int is_open()
{
	int iHour = time();
	if(!iStart1 || !iFinish1)
	{
		return 0;
	}
	if(iHour >= iStart1 && iHour < iFinish1)
	{
		return 1;
	}
	else if(iHour >= iFinish1)
	{
		return 0;
	}	
}
