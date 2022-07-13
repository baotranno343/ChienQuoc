/*****************************
	**端午节**
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
object *ZhongZi;
object Dongtingzhouzi;
void generate_zhongzi();
void destroy_zhongzi();
void get_dongtingzhouzi();
void destruct_dongtingzhouzi();

// 函数：生成二进制码
void SAVE_BINARY() { }
string get_save_file()	{ return "data/duanwujie"SAVE_EXTENSION;}
void create()
{
	restore();
	ZhongZi = ({});
	call_out("check_time",3);
}

void check_time()
{
	int iHour;
	remove_call_out("check_time");
	iHour = time();
	if ( iHour > iFinish1+3600 || iFinish1 == 0 )
	{
		destroy_zhongzi();
		destruct_dongtingzhouzi();
		return ;
	}
	if ( iHour < iStart1 )	//没到时间
	{
		call_out("check_time",iStart1-iHour);
		return ;
	}
	get_dongtingzhouzi();
	call_out("check_time2",3);
}
void check_time2()
{
	int iHour;
	remove_call_out("check_time2");
	iHour = time();
	if ( iHour > iFinish1+3600 || iFinish1 == 0 )
	{
		destroy_zhongzi();
		destruct_dongtingzhouzi();
		return ;
	}
	destroy_zhongzi();
	if (iHour < iFinish1)
	{
		CHAT_D->sys_channel(0,HIY"大诗人屈原投汨罗江而死，大家快去找到遗落在楚国的包粽子材料，交给在洞庭湖（161,177）的洞庭湖舟子来制作粽子抛进江中，以防止鱼儿去咬屈子的遗体啊。");
		generate_zhongzi();
	}
	call_out("check_time2",1800);
}


// 放入洞庭舟子
void get_dongtingzhouzi()
{
	if ( !objectp(Dongtingzhouzi) )
	{
		Dongtingzhouzi = new("/npc/party/dongtingzhouzi");
		Dongtingzhouzi->add_to_scene(161,161,177,3);
	}
}

// 移除洞庭舟子
void destruct_dongtingzhouzi()
{
	if ( objectp(Dongtingzhouzi) )
	{
		Dongtingzhouzi->remove_from_scene();
		destruct(Dongtingzhouzi);
	}
}

//  放入糯米、猪肉、蓼叶
void generate_zhongzi()
{
	int i,size,z,p,x,y,j,count;
	object item;
	
	destroy_zhongzi();

	z = 60;
	for(j=7;j<10;j++)
	{
		for(i=0;i<200;i++)
		{
			if( !( p = efun::get_xy_point( z, IS_CHAR_BLOCK ) ) )
				continue;
			x = ( p % 1000000 ) / 1000;  y = p % 1000;
			item = new(sprintf("/item/04/044%d",j));
			if ( !objectp(item) )
				continue;
			item->add_to_scene(z,x,y);	
			ZhongZi += ({ item });
		}
	}
}

//  移除糯米、猪肉、蓼叶
void destroy_zhongzi()
{
	int i,size;

	for(i=0,size=sizeof(ZhongZi);i<size;i++)
	{
		if ( !objectp(ZhongZi[i]) )
			continue;
		if ( get_d(ZhongZi[i]) )
			continue;
		ZhongZi[i]->remove_from_scene();
		destruct(ZhongZi[i]);
	}
	ZhongZi = ({});
}

//设置端午节活动的开启和关闭
int set_open(object who,string arg)
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
	tell_user(who,"端午节活动开启：%s！",arg);	
	send_user(who,"%c%s",'!',"端午节活动开启！");	
	save();
	call_out("check_time",3);
	return 1;
}

int set_close(object who)
{
	remove_call_out("check_time");
	iStart1 = 0;	
	iFinish1 = 0;		
	send_user(who,"%c%s",'!',"端午节活动关闭！");	
	save();
	return 1;	
}

