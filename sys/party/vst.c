/********************************************************************************************************************************
		    -----------------------Bắt Đầu đánh Vô Song Thành --------------------
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
object *Scum,*Scum1;
mapping mpNianshou;
// 函数：生成二进制码
void SAVE_BINARY() { }

void create()
{
//	restore();		
	Scum = ({});
	Scum1 = ({});
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
			|| mixTime[TIME_HOUR] == 21 
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
	for(i=0;i<1;i++)
	{
		if( !( p = get_jumpin(888, -1) ) )
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new("npc/event/vosongthanh");
		npc->add_to_scene(888,82,89);	
		Scum += ({ npc });
	}
	call_out("check_time2",7200);
	call_out("check_time3",3600);
	CHAT_D->sys_channel(0,"Trận tử chiến Vô Song Thành đã bắt đầu !");
	CHAT_D->sys_channel(0,"Trận tử chiến Vô Song Thành đã bắt đầu !");
	CHAT_D->sys_channel(0,"Trận tử chiến Vô Song Thành đã bắt đầu !");
	CHAT_D->sys_channel(0,"Trận tử chiến Vô Song Thành đã bắt đầu !");
	CHAT_D->sys_channel(0,"Trận tử chiến Vô Song Thành đã bắt đầu !");
}
void check_time2()
{
	int i,size;
	
	for(i=0,size=sizeof(Scum);i<size;i++)
	{
		if ( !objectp(Scum[i])	)
			continue;

			Scum[i]->remove_from_scene();
			destruct(Scum[i]);
	}
	Scum -= ({ 0 });		
}
void check_time3()
{
	int i,size,z,p,x,y,j;
	object npc;
	for(i=0;i<1;i++)
	{
		if( !( p = get_jumpin(888, -1) ) )
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new("npc/test/khoavsc1");
		npc->add_to_scene(888,68,68);	
		Scum1 += ({ npc });
	}
	for(i=0;i<1;i++)
	{
		if( !( p = get_jumpin(888, -1) ) )
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new("npc/test/khoavsc2");
		npc->add_to_scene(888,110,63);	
		Scum1 += ({ npc });
	}
	for(i=0;i<1;i++)
	{
		if( !( p = get_jumpin(888, -1) ) )
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new("npc/test/khoavsc3");
		npc->add_to_scene(888,114,95);	
		Scum1 += ({ npc });
	}
			"/sys/party/vst3"->set_mokhoa1(0);
			"/sys/party/vst3"->set_mokhoa2(0);
			"/sys/party/vst3"->set_mokhoa3(0);
	call_out("check_time4",3600);
	CHAT_D->sys_channel(0,"Cửa Vô Song Cung đã mở, 3 công tắc Khoá đồng thời xuất hiện !");				
	CHAT_D->sys_channel(0,"Cửa Vô Song Cung đã mở, 3 công tắc Khoá đồng thời xuất hiện !");				
	CHAT_D->sys_channel(0,"Cửa Vô Song Cung đã mở, 3 công tắc Khoá đồng thời xuất hiện !");				
}
void check_time4()
{
	int i,size;
	
	for(i=0,size=sizeof(Scum1);i<size;i++)
	{
		if ( !objectp(Scum1[i])	)
			continue;

			Scum1[i]->remove_from_scene();
			destruct(Scum1[i]);
	}
	Scum1 -= ({ 0 });
			"/sys/party/vst3"->set_mokhoa1(0);
			"/sys/party/vst3"->set_mokhoa2(0);
			"/sys/party/vst3"->set_mokhoa3(0);
}