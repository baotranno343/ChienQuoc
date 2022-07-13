/*****Quả Bóng Bốn Màu****/

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <public.h>
#include <time.h>
#include <action.h>

// 函数：生成二进制码
void SAVE_BINARY() { }
// 函数：构造处理
void create()
{
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

	if ( mixTime[TIME_WDAY] < 5 && mixTime[TIME_WDAY] != 0 )
	{
		call_out("check_time",3600*12);
		return ;
	}
	if ( mixTime[TIME_HOUR] < 17  )
	{
		call_out("check_time",60*(60-mixTime[TIME_MIN]));
		return ;
	}
	if ( mixTime[TIME_MIN] < 55  )
	{
		call_out("check_time",60*(55-mixTime[TIME_MIN]));
		return ;
	}
	CHAT_D->sys_channel(0,sprintf(HIY"Nghe nói "HIR "%d phút sau"HIY" quái vật sẽ chiếm ruộng đất để đá bóng.Các anh hùng hãy đi đoạt lấy các Quả Cầu và đến "HIR "Thiên Sứ Trao Đổi "HIY" để đổi lấy phần thưởng！",60-mixTime[TIME_MIN]));
	call_out("check_time2",60*(60-mixTime[TIME_MIN]));
	call_out("check_time",3600*54);	
}

void check_time2()
{
	CHAT_D->sys_channel(0,HIY"Quái vật đã bắt đầu đá bóng.Các vị anh hùng hãy nhanh chân tiêu giệt để đoạt lấy các Quả Cầu "HIR "và đến đổi thưởng ở Thiên Sứ Trao Đổi！");
}