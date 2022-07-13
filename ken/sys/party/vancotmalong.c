/********************************************************************************************************************************
		    ----------------------- Ma Long --------------------
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

#define MaLong "npc/boss/vancotmalong"

int BatDau, KetThuc;
void generate_scum();
void generate_scum2();
void destroy_scum();
string *schoolname = ({
	"Đào Hoa Nguyên",
	"Thục Sơn",
	"Cấm Vệ Quân",
	"Đường Môn",
	"Mao Sơn",
	"Côn Luân",
	"Vân Mộng Cốc",
});
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
	if (mixTime[TIME_WDAY] == 0) // Chủ nhật Không có boss
	{
		call_out("check_time", 3600 * 24);
		return;
	}
	i = 60 * (60 - mixTime[TIME_MIN]);
	if (mixTime[TIME_HOUR] % 2 == 0)
	{
		call_out("check_time", i);
	}
	else
	{ // 21h boss ra
		if (mixTime[TIME_HOUR] == 1 || mixTime[TIME_HOUR] == 3 || mixTime[TIME_HOUR] == 5 || mixTime[TIME_HOUR] == 7 || mixTime[TIME_HOUR] == 9 || mixTime[TIME_HOUR] == 11 || mixTime[TIME_HOUR] == 13 || mixTime[TIME_HOUR] == 15 || mixTime[TIME_HOUR] == 17 || mixTime[TIME_HOUR] == 19 || mixTime[TIME_HOUR] == 23)
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

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(549, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (MaLong);
		npc->add_to_scene(549, x, y);
		Scum += ({npc});
	}
	call_out("check_time2", 7200);
	CHAT_D->sys_channel(0, ECHO "Vạn Cốt Ma Long đã xuất hiện tại bản đồ Cự Thú Đảo và đang đợi sự khiêu chiến của các anh hùng. Mọi người hãy nhanh chân đi thu phục nó trừ hại cho bá tánh !");
	CHAT_D->sys_channel(0, ECHO "Vạn Cốt Ma Long đã xuất hiện tại bản đồ Cự Thú Đảo và đang đợi sự khiêu chiến của các anh hùng. Mọi người hãy nhanh chân đi thu phục nó trừ hại cho bá tánh !");
}
void generate_scum2()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(001, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (MaLong);
		npc->add_to_scene(001, x, y);
		Scum += ({npc});
	}
	call_out("check_time2", 7200);
	CHAT_D->sys_channel(0, ECHO "Vạn Cốt Ma Long đã xuất hiện tại bản đồ Tân Thủ Thôn và đang đợi sự khiêu chiến của các anh hùng. Mọi người hãy nhanh chân đi thu phục nó trừ hại cho bá tánh !");
	CHAT_D->sys_channel(0, ECHO "Vạn Cốt Ma Long đã xuất hiện tại bản đồ Tân Thủ Thôn và đang đợi sự khiêu chiến của các anh hùng. Mọi người hãy nhanh chân đi thu phục nó trừ hại cho bá tánh !");
}

void check_time2()
{
	int i, size;
	object betboss;
	for (i = 0, size = sizeof(Scum); i < size; i++)
	{
		if (!objectp(Scum[i]))
			continue;

		Scum[i]->remove_from_scene();
		destruct(Scum[i]);
		if(objectp(betboss = "/map/city/08"->get("betboss"))) betboss->huy();//hủy cược
	}
	Scum -= ({0});
}