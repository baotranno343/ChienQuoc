/*******************************
	**CQ Pro - Pretkuzl Truy lùng tử tù event**
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

void generate_scum();
void destroy_scum();

string *nCountry = ({
	"Chu Quốc",
	"Tề Quốc",
	"Hàn Quốc",
	"Triệu Quốc",
	"Ngụy Quốc",
	"Tần Quốc",
	"Sở Quốc",
	"Yên Quốc",
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

	i = 60 * (60 - mixTime[TIME_MIN]);
	if (mixTime[TIME_HOUR] % 2 == 1) // Giờ lẻ
	{
		call_out("check_time", i);
	}
	else
	{
		// Giờ xuất hiện event 7, 11, 15, 19, 21
		if (mixTime[TIME_HOUR] == 0 || mixTime[TIME_HOUR] == 2 || mixTime[TIME_HOUR] == 4 || mixTime[TIME_HOUR] == 6 || mixTime[TIME_HOUR] == 8)
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

	j = random(8);
	z = 80;
	for (i = 0; i <= 50 + random(5); i++)
	{
		if (!(p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new ("/npc/event/tunhanvuotnguc");
		npc->add_to_scene(z, x, y);
		Scum += ({npc});
	}
	call_out("check_time2", 900); // Sau 15 phút

	CHAT_D->sys_channel(0, HIC "Kẻ bắt nạt con nít đã xuất hiện ở " HIY "Chu Quốc" HIC " các vị anh hùng hãy nhanh tay đi tìm và giết chúng để lấy Túi Hàng chúng mang trên người nào.");
	CHAT_D->sys_channel(0, HIC "Kẻ bắt nạt con nít đã xuất hiện ở " HIY "Chu Quốc" HIC " các vị anh hùng hãy nhanh tay đi tìm và giết chúng để lấy Túi Hàng chúng mang trên người nào.");
}

//  移除武林败类NPC
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
	CHAT_D->sys_channel(0, HIY "Bọn Tử Tù đã ra nhận tội, bên ngoài thành lại yên bình trở lại!!!");
}
