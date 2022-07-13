/********************************************************************************************************************************
		    ----------------------- Bắt giữ Ác Quỷ Vương --------------------
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

#define AcQuyVuong "npc/event/acquyvuong"

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
	int iTime, rate, level, z, p, x, y;
	int i, *nScene, size;
	mixed *mixTime;
	object robber;

	remove_call_out("check_time");
	iTime = time();

	mixTime = localtime(iTime);
	if (mixTime[TIME_WDAY] == 1 || mixTime[TIME_WDAY] == 3 || mixTime[TIME_WDAY] == 5) // 3 5 7 chu nhat co ac quy

	// Thứ 5 thứ 6 thứ 7 CN có Ác Quỷ
	{
		//	destroy_scum();
		call_out("check_time", 3600 * 24);
		return;
	}
	/*	else if ( mixTime[TIME_HOUR] < 5 || mixTime[TIME_HOUR] > 23 )
	{
		destroy_scum();
		call_out("check_time",3600*24);
		return ;
	}*/
	// else
	// {

	i = 60 * (60 - mixTime[TIME_MIN]);
	if (mixTime[TIME_HOUR] % 2 == 1) // GIờ lẻ
	{
		call_out("check_time", i);
	}
	else
	{
		if (mixTime[TIME_HOUR] == 0 || mixTime[TIME_HOUR] == 2 || mixTime[TIME_HOUR] == 4 || mixTime[TIME_HOUR] == 6 || mixTime[TIME_HOUR] == 8) // 1 3 5 7 9 11 13h không có ác quỷ
																																				 // 15h 17h 19h 21h 23h có ác quỷ
			call_out("check_time", i + 3600);
		else
		{
			generate_scum();
			call_out("check_time", i + 3600);
		}
	}
	//	}
}
//  放入武林败类NPC
void generate_scum()
{
	int i, size, z, p, x, y, j;
	object npc;

	//	destroy_scum();

	for (i = 0; i <= 75 + random(10); i++)
	{
		if (!(p = efun::get_xy_point(80, IS_CHAR_BLOCK)))
			continue;
		x = (p % 1000000) / 1000;
		y = p % 1000;
		npc = new (AcQuyVuong);
		npc->add_to_scene(80, x, y);
		Scum += ({npc});
	}
	for (i = 0; i <= 75 + random(10); i++)
	{
		if (!(p = efun::get_xy_point(01, IS_CHAR_BLOCK)))
			continue;
		x = (p % 1000000) / 1000;
		y = p % 1000;
		npc = new (AcQuyVuong);
		npc->add_to_scene(01, x, y);
		Scum += ({npc});
	}
	call_out("check_time2", 1800);

	CHAT_D->sys_channel(0, HIC "Nghe nói Ác Quỷ Vương đã xuất hiện ở ngoài thành Chu Quốc và Tân Thủ Thôn, nếu như bắt được đám Ác Quỷ này thì có thể đến NPC Phàm Trân  để đổi các phần thưởng quý giá !");
}
//Sau 55 phút từ khi Ác Quỷ xuất hiện, Ác Quỷ sẽ tự động biến mất
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