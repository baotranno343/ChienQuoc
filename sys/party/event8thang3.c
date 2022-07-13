/********************************************************************************************************************************
-----------------------Mother Day 8/3 
Pret Kuzl --------------------
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

#define Mother "npc/event/83/mother"

void generate_scum();
void destroy_scum();
object *Scum;
mapping mpNianshou;
// 函数：生成二进制码
void SAVE_BINARY() {}

void create()
{
	//	restore();
	Scum = ({});
	call_out("check_time", 1);
}

void check_time()
{
	int iHour, rate, level, z, p, x, y;
	int i, *nScene, size;
	mixed *mixTime;
	object robber;

	remove_call_out("check_time");
	iHour = time();
	mixTime = localtime(iHour);
	//iHour = mixTime[TIME_HOUR];
	i = 60 * (60 - mixTime[TIME_MIN]);
	if (mixTime[TIME_HOUR] % 2 == 1) // == 0 là giờ lẽ, == 1 là giờ chẵn
	{
		call_out("check_time", i);
		return;
	}
	else
	{
		if (mixTime[TIME_HOUR] == 2 || mixTime[TIME_HOUR] == 4 || mixTime[TIME_HOUR] == 6 || mixTime[TIME_HOUR] == 8 || (mixTime[TIME_HOUR] == 10 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 12 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 14 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 16 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 18 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 20 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 22 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 0 && mixTime[TIME_MIN] > 30))
			call_out("check_time", i + 3600);
		else
		{
			generate_scum();
			call_out("check_time", i + 3600);
		}
	}
}
//  放入武林败类NPC
void generate_scum()
{
	int i, size, z, p, x, y, j;
	object npc;
	for (i = 0; i < 30; i++)
	{
		if (!(p = efun::get_xy_point(001, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (Mother);
		npc->add_to_scene(001, x, y);
		Scum += ({npc});
	}

	for (i = 0; i < 30; i++)
	{
		if (!(p = efun::get_xy_point(80, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (Mother);
		npc->add_to_scene(80, x, y);
		Scum += ({npc});
	}
	call_out("check_time2", 1800); // 30 phút biến mất
								   //	call_out("check_time2",14400);

	CHAT_D->sys_channel(0, HIY "Nghe nói ngoài thành Chu Quốc Và Tân Thủ Thôn xuất hiện rất nhiều bà mẹ đang chờ con, hãy tới xem các mẹ đang cần gì nào, nhanh nhé vì mấy bả chỉ chờ được 30 phút thôi!");
	CHAT_D->sys_channel(0, HIR "Nghe nói ngoài thành Chu Quốc Và Tân Thủ Thôn xuất hiện rất nhiều bà mẹ đang chờ con, hãy tới xem các mẹ đang cần gì nào, nhanh nhé vì mấy bả chỉ chờ được 30 phút thôi!");
}
void check_time2()
{
	int i, size;

	for (i = 0, size = sizeof(Scum); i < size; i++)
	{
		if (!objectp(Scum[i]))
			continue;

		Scum[i]->remove_from_scene();
		destruct(Scum[i]);
	}
	Scum -= ({0});
}