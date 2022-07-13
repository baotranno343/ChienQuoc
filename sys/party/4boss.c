/********************************************************************************************************************************
		    ----------------------- Uy Võ, Âm Gian, Hổ Vương, K.Thái Lang --------------------
********************************************************************************************************************************/

#include <time.h>
#include <ansi.h>
#include <cmd.h>
#include <chia_kenh.h>
#include <npc.h>
#include <city.h>
#include <action.h>
#include <effect.h>
#include <skill.h>
#include <public.h>

#define hv "npc/boss/0001"
#define ktl "npc/boss/0002"
#define uv "npc/boss/0003"
#define ag "npc/boss/0016"

void generate_scum();
void destroy_scum();
object *Scum;
mapping mpNianshou;
// 函数：生成二进制码
void SAVE_BINARY() {}

void create()
{
	if (MAIN_D->get_kenh() != KENH_EVENT)
	{
		return;
	}
	//	restore();
	Scum = ({});
	call_out("check_time", 1);
}

void check_time()
{
	int iTime, rate, level, z, p, x, y;
	int i, *nScene, size, g;
	mixed *mixTime;
	object robber;

	remove_call_out("check_time");
	iTime = time();

	mixTime = localtime(iTime);
	i = 60 * (60 - mixTime[TIME_MIN]);
	if (mixTime[TIME_HOUR] % 2 == 1) // Gọi ra vào giờ lẻ
	{
		call_out("check_time", i);
	}
	if (mixTime[TIME_HOUR] == 22)
	{
		"cmd/base/time"->set_4boss(1);
		generate_scum();
		call_out("destroy_scum", i);
		call_out("check_time", i);
		"cmd/func/allfunc"->thongbao_event(HIR "Kênh Event:" HIG " Bốn Boss Thần Binh đã xuất hiện, Hổ Vương đang ở Trường Bạch Thiên Tri, Uy Võ Đại Tướng Quân đang ở Mục Trường, Âm Gian Bạn Đồ đang ở Hầm Vạn Nhân, Khuyển Thái Lang đang ở Hải Tân");
		log_file("party_event.dat", sprintf("%d ：%d: Bốn Boss Thần Binh mở ra\n", mixTime[TIME_HOUR], mixTime[TIME_MIN]));
	}
	else
		call_out("check_time", i);
}
//  放入武林败类NPC
void generate_scum()
{
	int i, size, z, p, x, y, j;
	object *objs, npc;
	for (i = 0; i < 1; i++) // Hổ Vương
	{
		if (!(p = efun::get_xy_point(174, IS_CHAR_BLOCK)))
			continue;
		x = (p % 1000000) / 1000;
		y = p % 1000;
		npc = new (hv);
		npc->add_to_scene(174, x, y);
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++) // Uy Võ Đại Tướng Quân
	{
		if (!(p = get_valid_xy(139, x = 116 + random(20), y = 59 + random(20), IS_CHAR_BLOCK)))
			continue;
		x = (p % 1000000) / 1000;
		y = p % 1000;
		npc = new (uv);
		npc->add_to_scene(139, x, y);
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++) // Âm Gian Bạn Đồ
	{
		if (!(p = efun::get_xy_point(335, IS_CHAR_BLOCK)))
			continue;
		x = (p % 1000000) / 1000;
		y = p % 1000;
		npc = new (ag);
		npc->add_to_scene(335, x, y);
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++) // Khuyển Thái Lang
	{
		if (!(p = efun::get_xy_point(014, IS_CHAR_BLOCK)))
			continue;
		x = (p % 1000000) / 1000;
		y = p % 1000;
		npc = new (ktl);
		npc->add_to_scene(014, x, y);
		Scum += ({npc});
	}

	//	call_out("check_time2",20*3600);
} /*
//Sau 20 giờ từ khi Boss xuất hiện, Boss sẽ tự động biến mất 
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
}*/
void destroy_scum()
{
	int i, size;

	for (i = 0, size = sizeof(Scum); i < size; i++)
	{
		if (!objectp(Scum[i]))
			continue;

		Scum[i]->remove_from_scene();
		destruct(Scum[i]);
	}
	CHAT_D->sys_channel(0, HIC "Bốn Boss Thần Binh đã rời đi cảm ơn các bàn hữu đã giúp người dân đánh đuổi chúng");
	"cmd/base/time"->set_4boss(0);
	Scum -= ({0});
}