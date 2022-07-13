#include <time.h>
#include <ansi.h>
#include <cmd.h>

#include <npc.h>
#include <city.h>
#include <action.h>
#include <effect.h>
#include <skill.h>
#include <public.h>
private
int aptieu = 0;

// private
// int sugia = 0;

//int set_aptieu_x2(int i) { return i; }
int get_aptieu_x2() { return aptieu; }
// //int set_sugia_x2(int i) { return i; }
// int get_sugia_x2() { return sugia; }

void create()
{
	call_out("check_time", 1);
}

void check_time()
{
	int iTime, i;
	mixed *mixTime;
	remove_call_out("check_time");
	iTime = time();
	mixTime = localtime(iTime);
	i = 60 * (60 - mixTime[TIME_MIN]);
	if (mixTime[TIME_HOUR] != 12 && mixTime[TIME_HOUR] != 20)
	{
		call_out("check_time", i);
		return;
	}
	if ((mixTime[TIME_HOUR] == 12 && mixTime[TIME_MIN] < 30) || (mixTime[TIME_HOUR] == 20 && mixTime[TIME_MIN] < 30))
	{
		CHAT_D->sys_channel(0, HIG "Khung giờ tăng phần thưởng nhiệm vụ" HIR " Áp Tiêu" HIG " đã Bắt Đầu!!!!!!");
		CHAT_D->sys_channel(0, HIG "Khung giờ tăng phần thưởng nhiệm vụ" HIR " Áp Tiêu" HIG " đã Bắt Đầu!!!!!!");
		CHAT_D->sys_channel(0, HIG "Khung giờ tăng phần thưởng nhiệm vụ" HIR " Áp Tiêu" HIG " đã Bắt Đầu!!!!!!");
		aptieu = 1;
		"cmd/base/time"->set_aptieu(1);
		call_out("check_time_aptieu", 1800 - (60 * mixTime[TIME_MIN]));
		call_out("check_time", 1800 - (60 * mixTime[TIME_MIN]));
		log_file("party_event.dat", sprintf("%d ：%d: x2 Áp Tiêu mở ra\n", mixTime[TIME_HOUR], mixTime[TIME_MIN]));
		return;
	}
	// if ((mixTime[TIME_HOUR] == 12 && mixTime[TIME_MIN] >= 30) || (mixTime[TIME_HOUR] == 20 && mixTime[TIME_MIN] >= 30))
	// {
	// 	CHAT_D->sys_channel(0, HIG "Khung giờ tăng phần thưởng nhiệm vụ" HIR " Sư Gia" HIG " đã Bắt Đầu!!!!!!");
	// 	CHAT_D->sys_channel(0, HIG "Khung giờ tăng phần thưởng nhiệm vụ" HIR " Sư Gia" HIG " đã Bắt Đầu!!!!!!");
	// 	CHAT_D->sys_channel(0, HIG "Khung giờ tăng phần thưởng nhiệm vụ" HIR " Sư Gia" HIG " đã Bắt Đầu!!!!!!");
	// 	sugia = 1;
	// 	call_out("check_time_sugia", 3600 - (60 * mixTime[TIME_MIN]));
	// 	call_out("check_time", 3600 - (60 * mixTime[TIME_MIN]));
	// 	return;
	// }

	if (mixTime[TIME_MIN] > 30)
	{
		call_out("check_time", 60 * (60 - mixTime[TIME_MIN]));
	}
	else
	{
		call_out("check_time", 60 * (30 - mixTime[TIME_MIN]));
	}
	return;
}
//  移除武林败类NPC
void check_time_aptieu()
{
	object *member, map;
	int i, size;
	aptieu = 0;
	"cmd/base/time"->set_aptieu(0);
	CHAT_D->sys_channel(0, HIR "Khung giờ x2 nhiệm vụ" HIG " Áp Tiêu" HIG " đã kết thúc!!!!!!");
}

// void check_time_sugia()
// {
// 	object *member, map;
// 	int i, size;
// 	sugia = 0;
// 	CHAT_D->sys_channel(0, HIR "Khung giờ x2 nhiệm vụ" HIG " Sư Gia" HIG " đã kết thúc!!!!!!");
// }
