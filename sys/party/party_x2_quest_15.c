#include <time.h>
#include <ansi.h>
#include <cmd.h>
#include <city.h>
#include <public.h>
#include <chia_kenh.h>
private
int truybatdaopham = 0;
private
int sugia = 0;
// private
// int nguyenlieu = 0;
// Nguyen lIeu
object *npcnguyenlieu;
void generate_npcnguyenlieu();
//
//int set_aptieu_x2(int i) { return i; }
int get_truybatdaopham_x2() { return truybatdaopham; }
int get_sugia_x2() { return sugia; }
// int get_nguyenlieu() { return nguyenlieu; }
void create()
{
	npcnguyenlieu = ({});
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
	//19 -21
	if (mixTime[TIME_HOUR] != 11 && mixTime[TIME_HOUR] != 12 && mixTime[TIME_HOUR] != 13 && mixTime[TIME_HOUR] != 19 && mixTime[TIME_HOUR] != 20 && mixTime[TIME_HOUR] != 21)
	{
		call_out("check_time", i);
		return;
	}

	if ((mixTime[TIME_HOUR] == 11 && mixTime[TIME_MIN] >= 45) || (mixTime[TIME_HOUR] == 19 && mixTime[TIME_MIN] >= 45))
	{
		CHAT_D->sys_channel(0, HIG "Khung giờ tăng phần thưởng nhiệm vụ" HIR " Truy Bắt Đạo Phạm" HIG " đã Bắt Đầu!!!!!!");
		CHAT_D->sys_channel(0, HIG "Khung giờ tăng phần thưởng nhiệm vụ" HIR " Truy Bắt Đạo Phạm " HIG "đã Bắt Đầu!!!!!!");
		CHAT_D->sys_channel(0, HIG "Khung giờ tăng phần thưởng nhiệm vụ" HIR " Truy Bắt Đạo Phạm " HIG "đã Bắt Đầu!!!!!!");
		truybatdaopham = 1;
		"cmd/base/time"->set_truybatdaopham(1);
		call_out("check_time_truybatdaopham", 3600 - (60 * mixTime[TIME_MIN]));
		call_out("check_time", 3600 - (60 * mixTime[TIME_MIN]));
		log_file("party_event.dat", sprintf("%d ：%d: x2 Truy Bắt Đạo Phạm mở ra\n", mixTime[TIME_HOUR], mixTime[TIME_MIN]));
		return;
	}
	if ((mixTime[TIME_HOUR] == 12 && mixTime[TIME_MIN] >= 45) || (mixTime[TIME_HOUR] == 20 && mixTime[TIME_MIN] >= 45))
	{
		CHAT_D->sys_channel(0, HIG "Khung giờ tăng phần thưởng nhiệm vụ" HIR " Sư Gia" HIG " đã Bắt Đầu!!!!!!");
		CHAT_D->sys_channel(0, HIG "Khung giờ tăng phần thưởng nhiệm vụ" HIR " Sư Gia" HIG " đã Bắt Đầu!!!!!!");
		CHAT_D->sys_channel(0, HIG "Khung giờ tăng phần thưởng nhiệm vụ" HIR " Sư Gia" HIG " đã Bắt Đầu!!!!!!");
		sugia = 1;
		"cmd/base/time"->set_sugia(1);
		call_out("check_time_sugia", 3600 - (60 * mixTime[TIME_MIN]));
		call_out("check_time", 3600 - (60 * mixTime[TIME_MIN]));
		log_file("party_event.dat", sprintf("%d ：%d: x2 Sư Gia mở ra\n", mixTime[TIME_HOUR], mixTime[TIME_MIN]));
		return;
	}
	//Nguyen Lieu
	if ((mixTime[TIME_HOUR] == 21 && mixTime[TIME_MIN] >= 45))
	{
		if (MAIN_D->get_kenh() != KENH_EVENT)
		{
			call_out("check_time", 3600 - (60 * mixTime[TIME_MIN]));
			return;
		}
		// nguyenlieu = 1;
		"cmd/base/time"->set_nguyenlieu(1);
		generate_npcnguyenlieu();
		call_out("check_time", 3600 - (60 * mixTime[TIME_MIN]));
		call_out("destroy_npcnguyenlieu", 3600 - (60 * mixTime[TIME_MIN]));
		log_file("party_event.dat", sprintf("%d ：%d: x2 NPC Nguyên Liệu mở ra\n", mixTime[TIME_HOUR], mixTime[TIME_MIN]));
		return;
	}
	//
	if (mixTime[TIME_MIN] < 15)
	{
		call_out("check_time", 60 * (15 - mixTime[TIME_MIN]));
	}
	else
	{
		call_out("check_time", 60 * (15 - (mixTime[TIME_MIN] % 15)));
	}
	return;
}
//  移除武林败类NPC

void check_time_truybatdaopham()
{
	object *member, map;
	int i, size;
	truybatdaopham = 0;
	"cmd/base/time"->set_truybatdaopham(0);
	CHAT_D->sys_channel(0, HIR "Khung giờ x2 nhiệm vụ" HIG " Truy Bắt Đạo Phạm" HIR " đã kết thúc!!!!!!");
	return;
}
void check_time_sugia()
{
	object *member, map;
	int i, size;
	sugia = 0;
	"cmd/base/time"->set_sugia(0);
	CHAT_D->sys_channel(0, HIR "Khung giờ x2 nhiệm vụ" HIG " Sư Gia" HIR " đã kết thúc!!!!!!");
	return;
}
//Nguyen Lieu
void generate_npcnguyenlieu()
{
	int i, iTime, size, z, p, x, y, j;
	object npc;
	mixed *mixTime;
	int *thatquoc = ({01, 80});
	int npcfinal = 0;
	iTime = time(); // khai báo Time
	mixTime = localtime(iTime);
	j = random(2);
	z = thatquoc[j];
	if (mixTime[TIME_MDAY] % 2 == 0)
		npcfinal = 0;
	else
		npcfinal = 7;

	if (z == 80)
	{
		x = 283;
		y = 120;
		CHAT_D->sys_channel(0, HIG "Người buôn nguyên liệu đã xuất hiện ở Chu Quốc Tọa Độ: " + x + "," + y + " các người chơi có 15 phút để mua nguyên liệu");
		CHAT_D->sys_channel(0, HIG "Người buôn nguyên liệu đã xuất hiện ở Chu Quốc Tọa Độ: " + x + "," + y + " các người chơi có 15 phút để mua nguyên liệu");
		"cmd/func/allfunc"->thongbao_event(HIR "Kênh Event:" HIG " Người buôn nguyên liệu đã xuất hiện ở Chu Quốc Tọa Độ: " + x + "," + y + " các người chơi có 15 phút để mua nguyên liệu");
	}
	else
	{
		x = 147;
		y = 139;
		CHAT_D->sys_channel(0, HIG "Người buôn nguyên liệu đã xuất hiện ở Tân Thủ Thôn Tọa Độ: " + x + "," + y + " các người chơi có 15 phút để mua nguyên liệu");
		CHAT_D->sys_channel(0, HIG "Người buôn nguyên liệu đã xuất hiện ở Tân Thủ Thôn Tọa Độ: " + x + "," + y + " các người chơi có 15 phút để mua nguyên liệu");
		"cmd/func/allfunc"->thongbao_event(HIR "Kênh Event:" HIG " Người buôn nguyên liệu đã xuất hiện ở Tân Thủ Thôn Tọa Độ: " + x + "," + y + " các người chơi có 15 phút để mua nguyên liệu");
	}

	for (i = npcfinal; i < (npcfinal + 7); i++)
	{
		if (!p = get_valid_xy(z, x, y, IS_CHAR_BLOCK))
			continue;
		// x = p / 10000;
		// y = p % 10000;
		npc = new (sprintf("/npc/npcnguyenlieu/npcnguyenlieu%d", i + 1));
		npc->add_to_scene(z, p / 1000 + random(10), p % 1000 - random(10));
		npcnguyenlieu += ({npc});
	}
	return;
	//	CHAT_D->sys_channel(0, HIG "Người buôn nguyên liệu đã xuất hiện ở Chu Quốc Tọa Độ: " + x + "," + y + " các người chơi có 15 phút để mua nguyên liệu");
}
void destroy_npcnguyenlieu()
{
	int i, size;
	for (i = 0, size = sizeof(npcnguyenlieu); i < size; i++)
	{
		if (!objectp(npcnguyenlieu[i]))
			continue;

		npcnguyenlieu[i]->remove_from_scene();
		destruct(npcnguyenlieu[i]);
	}
	CHAT_D->sys_channel(0, HIR "Thương Nhân buôn nguyên liệu đã đi mất rồi các ngươi đừng lo các thương nhân sẽ lại xuất hiện sớm thôi");
	// nguyenlieu = 0;
	"cmd/base/time"->set_nguyenlieu(0);
	npcnguyenlieu -= ({0});
	return;
}
