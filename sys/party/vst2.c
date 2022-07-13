/********************************************************************************************************************************
		    -----------------------Kết thúc đánh Vô Song Thành --------------------
********************************************************************************************************************************/

#include <time.h>
#include <ansi.h>
#include <cmd.h>

#include <npc.h>
#include <city.h>
#include <action.h>
#include <effect.h>
#include <skill.h>
#include <public.h>


int BatDau,KetThuc;
void generate_scum();
void destroy_scum();
string *schoolname = ({"Đào Hoa Nguyên", "Thục Sơn", "Cấm Vệ Quân", "Đường Môn", "Mao Sơn", "Côn Luân", "Vân Mộng Cốc", });
//object *Scum;
mapping mpNianshou;
// 函数：生成二进制码
void SAVE_BINARY() { }

void create()
{
//	restore();		
//	Scum = ({});
	call_out("check_time",1);
}

void check_time()
{
	int iTime,rate,level,z,p,x,y;
	int i,*nScene,size;
	mixed *mixTime;
	object robber;
	
	remove_call_out("check_time");
	iTime = time();
	
	mixTime = localtime(iTime);

	if ( mixTime[TIME_WDAY] == 1 
	|| mixTime[TIME_WDAY] == 2
	|| mixTime[TIME_WDAY] == 4
	|| mixTime[TIME_WDAY] == 5
	|| mixTime[TIME_WDAY] == 6 )
	{
		call_out("check_time",3600*24);
		return ;
	}
	else
	{
		i = 60*(60-mixTime[TIME_MIN]);
		if ( mixTime[TIME_HOUR]%2 == 0 )
		{
			call_out("check_time",i);
		}
		else
		{
			if ( mixTime[TIME_HOUR] == 1 
			|| mixTime[TIME_HOUR] == 3 
			|| mixTime[TIME_HOUR] == 5 
			|| mixTime[TIME_HOUR] == 7 
			|| mixTime[TIME_HOUR] == 9 
			|| mixTime[TIME_HOUR] == 11 
			|| mixTime[TIME_HOUR] == 13 
			|| mixTime[TIME_HOUR] == 15 
			|| mixTime[TIME_HOUR] == 17 
			|| mixTime[TIME_HOUR] == 19 
			|| mixTime[TIME_HOUR] == 23 )
				call_out("check_time",i+3600);	
			else
			{
				generate_scum();
				call_out("check_time",i+3600);
			}
		}
	}

}
//  放入武林败类NPC
void generate_scum()
{
	int i,size,z,p,x,y,j;
	object npc;
	
	//call_out("check_time2",3600);
	CHAT_D->sys_channel(0,"Trận tử chiến Vô Song Thành đã kết thúc !");
	CHAT_D->sys_channel(0,"Trận tử chiến Vô Song Thành đã kết thúc !");
	CHAT_D->sys_channel(0,"Trận tử chiến Vô Song Thành đã kết thúc !");
	CHAT_D->sys_channel(0,"Trận tử chiến Vô Song Thành đã kết thúc !");
	CHAT_D->sys_channel(0,"Trận tử chiến Vô Song Thành đã kết thúc !");
}
