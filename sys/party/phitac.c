/********************************************************************************************************************************
-----------------------Trộm Bảo Phi Tặc --------------------
10 : ({061,001,}),==Tân Thủ Thôn
20 : ({081,089,}),==Thủ Dương Sơn
30 : ({163,164,}),==Ranh giới Đầm Lầy, địa giới Đầm Lầy
40 : ({151,011,}),==Kênh Trịnh Quốc 1
50 : ({173,072,}),==Bạch Vân Phòng
60 : ({032,541}),==Triệu Trường Thành 2
70 : ({534,542,}),==Linh Cốc Động 1
80 : ({535,543}),==Loạn Đạo 1
90 : ({536,544}),==Khốn Ma Trận 1,
100: ({537,545}),==Cầu Cửu Khúc 1
110: ({538,546 }),==Thiên Môn Trận 1
120: ({539,547 }),==Tru Tiên Trận 1
130: ({540,548 }),==Địa ngục tầng 8
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

#define PhiTac "npc/event/phitac"

void generate_scum();
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
	int i, *nScene, size;
	mixed *mixTime; // khai báo mixTime ( quan trọng, nhớ  có dấu * ở trước )
	object robber;

	remove_call_out("check_time");
	iTime = time(); // khai báo Time
	mixTime = localtime(iTime);
	if (mixTime[TIME_WDAY] == 2 || mixTime[TIME_WDAY] == 4 || mixTime[TIME_WDAY] == 6) // Thứ 3, thứ 5, thứ 7 không có phi tặc
	{
		call_out("check_time", 3600 * 24 - mixTime[TIME_HOUR] * 3600 - mixTime[TIME_MIN] * 60);
		return;
	}
	else
	{
		i = 60 * (60 - mixTime[TIME_MIN]);
		if (mixTime[TIME_HOUR] % 2 == 0) // == 0 là giờ lẽ, == 1 là giờ chẵn
		{
			call_out("check_time", i);
			return;
		}
		else
		{
			if ((mixTime[TIME_HOUR] == 1) || (mixTime[TIME_HOUR] == 3) || (mixTime[TIME_HOUR] == 5) || (mixTime[TIME_HOUR] == 7) || (mixTime[TIME_HOUR] == 9 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 11 && mixTime[TIME_MIN] > 30) //Nếu giờ hiện tại là: 1 , 3, 5, 7h thì Kết thúc hàm -> ko có Phi Tặc
				|| (mixTime[TIME_HOUR] == 13 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 15) || (mixTime[TIME_HOUR] == 17 && mixTime[TIME_MIN] > 30)																					// Nếu ko có dòng > 30 thì 9h59 vẫn sẽ có phỉ còn nếu có thì khi bật GSE lên 9h30 sẽ ko có phỉ
				|| (mixTime[TIME_HOUR] == 19 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 21 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 0 && mixTime[TIME_MIN] > 30))
			{
				call_out("check_time", i + 3600);
				return;
			}
			else
			{
				"cmd/base/time"->set_phitac(1);
				generate_scum();				  // Nếu giờ hiện tại là: 9,11,13,15,17,19,21,23h thì gọi Phi Tặc ra
				call_out("check_time", i + 3600); //( nhưng nếu cùng giờ đó mà số phút lớn hơn 30 - Chỉ tính cái này khi vừa bật GSE -> thì Phi Tặc sẽ đợi sang giờ kế tiếp mới xuất hiện )
				call_out("check_time2", 1800 - (60 * mixTime[TIME_MIN]));
				log_file("party_event.dat", sprintf("%d ：%d: Phỉ Tặc mở ra\n", mixTime[TIME_HOUR], mixTime[TIME_MIN]));
				return;
			}
		}
	}
}

//  放入武林败类NPC
void generate_scum()
{
	int i, size, z, p, x, y, j;
	object npc;
	// cấp 10 Tân Thủ Thôn
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(001, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (PhiTac);
		npc->set_level(10);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 10);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(001, x, y);
		Scum += ({npc});
	}
	// cấp 10  Sở Phương Thành 1
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(061, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (PhiTac);
		npc->set_level(10);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 10);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(061, x, y);
		Scum += ({npc});
	}
	// cấp 20 Thủ Dương Sơn
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(081, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (PhiTac);
		npc->set_level(20);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 20);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(081, x, y);
		Scum += ({npc});
	}
	// cấp 20 Hồ Lao Quan
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(089, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (PhiTac);
		npc->set_level(20);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 20);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(089, x, y);
		Scum += ({npc});
	}
	// cấp 30 Ranh Giới
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(163, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (PhiTac);
		npc->set_level(30);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 30);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(163, x, y);
		Scum += ({npc});
	}
	// cấp 30 Địa Giới
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(164, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (PhiTac);
		npc->set_level(30);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 30);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(164, x, y);
		Scum += ({npc});
	}
	// cấp 40 Kênh Trịnh Quốc 1
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(151, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (PhiTac);
		npc->set_level(40);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 40);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(151, x, y);
		Scum += ({npc});
	}
	// cấp 40  Đông Hải Thôn
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(011, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (PhiTac);
		npc->set_level(40);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 40);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(011, x, y);
		Scum += ({npc});
	}
	// cấp 50  Bạch Vân Phong
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(173, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (PhiTac);
		npc->set_level(50);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 50);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(173, x, y);
		Scum += ({npc});
	}
	// cấp 60  Triệu Trường Thành 2
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(032, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (PhiTac);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(032, x, y);
		Scum += ({npc});
	}
	// cấp 70  Linh Cốc Động 1
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(311, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (PhiTac);
		npc->set_level(70);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 70);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(311, x, y);
		Scum += ({npc});
	}
	// cấp 80 Loan Đạo 1
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(321, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (PhiTac);
		npc->set_level(80);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 80);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(321, x, y);
		Scum += ({npc});
	}
	// // cấp 90  Khốn Ma Trận 1
	// for (i = 0; i < 10; i++)
	// {
	// 	if (!(p = efun::get_xy_point(291, IS_CHAR_BLOCK)))
	// 		continue;
	// 	x = p / 1000;
	// 	y = p % 1000;
	// 	npc = new (PhiTac);
	// 	npc->set_level(90);
	// 	npc->set_char_type(FIGHTER_TYPE_2);
	// 	NPC_ENERGY_D->init_level(npc, 90);
	// 	npc->add_max_hp(npc->get_max_hp() * 40);
	// 	npc->add_dp(npc->get_dp() / 2);
	// 	npc->add_ap(npc->get_ap() * 2 / 5);
	// 	npc->add_pp(npc->get_pp() / 2);
	// 	npc->add_to_scene(291, x, y);
	// 	Scum += ({npc});
	// }
	// // cấp 100  Cầu Cửu Khúc 1
	// for (i = 0; i < 10; i++)
	// {
	// 	if (!(p = efun::get_xy_point(372, IS_CHAR_BLOCK)))
	// 		continue;
	// 	x = p / 1000;
	// 	y = p % 1000;
	// 	npc = new (PhiTac);
	// 	npc->set_level(100);
	// 	npc->set_char_type(FIGHTER_TYPE_2);
	// 	NPC_ENERGY_D->init_level(npc, 100);
	// 	npc->add_max_hp(npc->get_max_hp() * 40);
	// 	npc->add_dp(npc->get_dp() / 2);
	// 	npc->add_ap(npc->get_ap() * 2 / 5);
	// 	npc->add_pp(npc->get_pp() / 2);
	// 	npc->add_to_scene(372, x, y);
	// 	Scum += ({npc});
	// }
	// for (i = 0; i < 10; i++) // cap 110
	// {
	// 	if (!(p = efun::get_xy_point(091, IS_CHAR_BLOCK)))
	// 		continue;
	// 	x = p / 1000;
	// 	y = p % 1000;
	// 	npc = new (PhiTac);
	// 	npc->set_level(110);
	// 	npc->set_char_type(FIGHTER_TYPE_2);
	// 	NPC_ENERGY_D->init_level(npc, 110);
	// 	npc->add_max_hp(npc->get_max_hp() * 40);
	// 	npc->add_dp(npc->get_dp() / 2);
	// 	npc->add_ap(npc->get_ap() * 2 / 5);
	// 	npc->add_pp(npc->get_pp() / 2);
	// 	npc->add_to_scene(091, x, y);
	// 	Scum += ({npc});
	// }
	// for (i = 0; i < 10; i++) // cap 110
	// {
	// 	if (!(p = efun::get_xy_point(092, IS_CHAR_BLOCK)))
	// 		continue;
	// 	x = p / 1000;
	// 	y = p % 1000;
	// 	npc = new (PhiTac);
	// 	npc->set_level(110);
	// 	npc->set_char_type(FIGHTER_TYPE_2);
	// 	NPC_ENERGY_D->init_level(npc, 110);
	// 	npc->add_max_hp(npc->get_max_hp() * 40);
	// 	npc->add_dp(npc->get_dp() / 2);
	// 	npc->add_ap(npc->get_ap() * 2 / 5);
	// 	npc->add_pp(npc->get_pp() / 2);
	// 	npc->add_to_scene(092, x, y);
	// 	Scum += ({npc});
	// }
	// // Cấp 120
	// for (i = 0; i < 10; i++)
	// {
	// 	if (!(p = efun::get_xy_point(391, IS_CHAR_BLOCK)))
	// 		continue;
	// 	x = p / 1000;
	// 	y = p % 1000;
	// 	npc = new (PhiTac);
	// 	npc->set_level(120);
	// 	npc->set_char_type(FIGHTER_TYPE_2);
	// 	NPC_ENERGY_D->init_level(npc, 120);
	// 	npc->add_max_hp(npc->get_max_hp() * 40);
	// 	npc->add_dp(npc->get_dp() / 2);
	// 	npc->add_ap(npc->get_ap() * 2 / 5);
	// 	npc->add_pp(npc->get_pp() / 2);
	// 	npc->add_to_scene(391, x, y);
	// 	Scum += ({npc});
	// }
	// // Cấp 120
	// for (i = 0; i < 10; i++)
	// {
	// 	if (!(p = efun::get_xy_point(392, IS_CHAR_BLOCK)))
	// 		continue;
	// 	x = p / 1000;
	// 	y = p % 1000;
	// 	npc = new (PhiTac);
	// 	npc->set_level(120);
	// 	npc->set_char_type(FIGHTER_TYPE_2);
	// 	NPC_ENERGY_D->init_level(npc, 120);
	// 	npc->add_max_hp(npc->get_max_hp() * 40);
	// 	npc->add_dp(npc->get_dp() / 2);
	// 	npc->add_ap(npc->get_ap() * 2 / 5);
	// 	npc->add_pp(npc->get_pp() / 2);
	// 	npc->add_to_scene(392, x, y);
	// 	Scum += ({npc});
	// }
	// for (i = 0; i < 10; i++) //cap 130
	// {
	// 	if (!(p = efun::get_xy_point(540, IS_CHAR_BLOCK)))
	// 		continue;
	// 	x = p / 1000;
	// 	y = p % 1000;
	// 	npc = new (PhiTac);
	// 	npc->set_level(130);
	// 	npc->set_char_type(FIGHTER_TYPE_2);
	// 	NPC_ENERGY_D->init_level(npc, 130);
	// 	npc->add_max_hp(npc->get_max_hp() * 40);
	// 	npc->add_dp(npc->get_dp() / 2);
	// 	npc->add_ap(npc->get_ap() * 2 / 5);
	// 	npc->add_pp(npc->get_pp() / 2);
	// 	npc->add_to_scene(540, x, y);
	// 	Scum += ({npc});
	// }
	// for (i = 0; i < 10; i++) //cap 130
	// {
	// 	if (!(p = efun::get_xy_point(548, IS_CHAR_BLOCK)))
	// 		continue;
	// 	x = p / 1000;
	// 	y = p % 1000;
	// 	npc = new (PhiTac);
	// 	npc->set_level(130);
	// 	npc->set_char_type(FIGHTER_TYPE_2);
	// 	NPC_ENERGY_D->init_level(npc, 130);
	// 	npc->add_max_hp(npc->get_max_hp() * 40);
	// 	npc->add_dp(npc->get_dp() / 2);
	// 	npc->add_ap(npc->get_ap() * 2 / 5);
	// 	npc->add_pp(npc->get_pp() / 2);
	// 	npc->add_to_scene(548, x, y);
	// 	Scum += ({npc});
	// }
	//Hư
	/*for(i=0;i<6;i++)
	{
		if( !( p = efun::get_xy_point( 532, IS_CHAR_BLOCK ) ) )
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new(PhiTac);
			npc->set_level(105);
			npc->set_char_type(FIGHTER_TYPE_2);
			NPC_ENERGY_D->init_level(npc, 105);
			npc->add_max_hp(npc->get_max_hp()*40);
			npc->add_dp(npc->get_dp()/2);
			npc->add_ap(npc->get_ap()*2/5);
			npc->add_pp(npc->get_pp()/2);
		npc->add_to_scene(532,x,y);	
		Scum += ({ npc });
	}
	for(i=0;i<6;i++)
	{
		if( !( p = efun::get_xy_point( 532, IS_CHAR_BLOCK ) ) )
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new(PhiTac);
			npc->set_level(105);
			npc->set_char_type(FIGHTER_TYPE_2);
			NPC_ENERGY_D->init_level(npc, 105);
			npc->add_max_hp(npc->get_max_hp()*40);
			npc->add_dp(npc->get_dp()/2);
			npc->add_ap(npc->get_ap()*2/5);
			npc->add_pp(npc->get_pp()/2);
		npc->add_to_scene(532,x,y);	
		Scum += ({ npc });
	}
	for(i=0;i<6;i++)
	{
		if( !( p = efun::get_xy_point( 519, IS_CHAR_BLOCK ) ) )
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new(PhiTac);
			npc->set_level(105);
			npc->set_char_type(FIGHTER_TYPE_2);
			NPC_ENERGY_D->init_level(npc, 105);
			npc->add_max_hp(npc->get_max_hp()*40);
			npc->add_dp(npc->get_dp()/2);
			npc->add_ap(npc->get_ap()*2/5);
			npc->add_pp(npc->get_pp()/2);
		npc->add_to_scene(519,x,y);	
		Scum += ({ npc });
	}*/

	CHAT_D->sys_channel(0, HIY "Thổ Phỉ đã trộm một số báu vật từ hoàng cung. Bọn chúng đang mang báu vật trốn ở Tân Thủ Thôn, Sở Phương Thành 1, Thủ Dương Sơn, Hổ Lao Quan, Ranh giới Đầm Lầy, Địa Giới Đầm Lầy, Đông Hải Ngư Thôn, Kênh Trịnh Quốc 1");
	//	CHAT_D->sys_channel(0, HIY "Thổ Phỉ đã trộm một số báu vật từ hoàng cung. Bọn chúng đang mang báu vật trốn ở Bạch Vân Phong, Triệu Trường Thành 2, Linh Cốc Động 1, Loan Đạo 1, Khốn Ma Trận 1, Cầu Cửu Khúc 1, Thiên Môn Trận 1,2, Tru Tiên Trận 1,2 và Địa Ngục 8, Thiên Ngoại Ảo Cảnh 8");
	CHAT_D->sys_channel(0, HIY "Thổ Phỉ đã trộm một số báu vật từ hoàng cung. Bọn chúng đang mang báu vật trốn ở Bạch Vân Phong, Triệu Trường Thành 2, Linh Cốc Động 1, Loan Đạo 1");

	"cmd/func/allfunc"->thongbao_event(HIR "Kênh Event:" HIY "Thổ Phỉ đã trộm một số báu vật từ hoàng cung. Bọn chúng đang mang báu vật trốn ở Tân Thủ Thôn, Sở Phương Thành 1, Thủ Dương Sơn, Hổ Lao Quan, Ranh giới Đầm Lầy, Địa Giới Đầm Lầy, Đông Hải Ngư Thôn, Kênh Trịnh Quốc 1");
	//"cmd/func/allfunc"->thongbao_event(HIR "Kênh Event:" HIY "Thổ Phỉ đã trộm một số báu vật từ hoàng cung. Bọn chúng đang mang báu vật trốn ở Bạch Vân Phong, Triệu Trường Thành 2, Linh Cốc Động 1, Loan Đạo 1, Khốn Ma Trận 1, Cầu Cửu Khúc 1, Thiên Môn Trận 1,2, Tru Tiên Trận 1,2 và Địa Ngục 8, Thiên Ngoại Ảo Cảnh 8");// mở cấp 120
	"cmd/func/allfunc"->thongbao_event(HIR "Kênh Event:" HIY "Thổ Phỉ đã trộm một số báu vật từ hoàng cung. Bọn chúng đang mang báu vật trốn ở Bạch Vân Phong, Triệu Trường Thành 2, Linh Cốc Động 1, Loan Đạo 1");
}
//Sau 30 phút từ khi Phi Tặc xuất hiện, Phi Tặc sẽ tự động biến mất
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
	"cmd/base/time"->set_phitac(0);
	Scum -= ({0});
	CHAT_D->sys_channel(0, HIY "Trộm Bảo Phi Tặc tạm thời đã sợ hãi rút lui !");
	CHAT_D->sys_channel(0, HIY "Trộm Bảo Phi Tặc tạm thời đã sợ hãi rút lui !");
}
object drop_food_wine(int level)
{
	int *nTmp;
	object item;
	mapping mpFood = ([130:({3301, 3302}),
					   110:({3310, 3311}),
						90:({3303, 3304}),
						70:({3320, 3280}),
						50:({3281, 3285}),
						30:({3283, 3284}),
						10:({3282, 3325}),
	]);

	if (random(2)) //酒
	{
		if (level >= 130)
			item = new ("item/31/3156");
		else if (level >= 110)
			item = new ("item/31/3155");
		else if (level >= 90)
			item = new ("item/31/3154");
		else if (level >= 70)
			item = new ("item/31/3153");
		else if (level >= 50)
			item = new ("item/31/3152");
		else if (level >= 30)
			item = new ("item/31/3151");
		else
			item = new ("item/31/3150");
	}
	else //食物
	{
		if (level >= 130)
			level = 130;
		else if (level >= 110)
			level = 110;
		else if (level >= 90)
			level = 90;
		else if (level >= 70)
			level = 70;
		else if (level >= 50)
			level = 50;
		else if (level >= 30)
			level = 30;
		else
			level = 10;
		nTmp = mpFood[level];
		level = nTmp[random(sizeof(nTmp))];
		item = new (sprintf("item/%d/%d", level / 100, level));
	}
	if (!objectp(item))
		return;
	item->set_amount(10);
	return item;
}

// 函数：掉宝奖励
void drop_items(object me, object who)
{
	int x, y, z, p, i, rate, rate1, level, level2;
	string *nTmp, id, owner, file;
	object item, leader;

	level = me->get_level();
	z = get_z(me);
	x = get_x(me);
	y = get_y(me);
	id = who->get_leader();
	if (!id)
	{
		owner = who->get_id();
	}
	else
	{
		if (leader = find_player(id))
		{
			owner = leader->get_id();
		}
		else
		{
			owner = who->get_id();
		}
	}
	for (i = 0; i < random(5); i++)
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/item/std/0001");
			item->set_value(level * 20);
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	for (i = 0; i < 10; i++)
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = drop_food_wine(level);
			if (!item)
			{
				continue;
			}
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}

	p = get_valid_xy(z, x, y, IS_ITEM_BLOCK);
	if (!p)
	{
		return;
	}
	rate1 = me->correct_drop_rate(me->get_level() - who->get_level()) * who->get_online_rate() / 100;
	if (rate1 < 40)
	{
		return;
	}
	rate = random(10000);
	item = 0;
	if (rate < 1000)
	{ //	i.	1000的几率掉落一件同等级段的随机门派蓝色装备。
		file = file = WEAPON_FILE->get_weapon_file_2((level / 10) * 10);
		item = new (file);
		if (!item)
		{
			return 0;
		}
		ITEM_EQUIP_D->init_equip_prop_1(item);
	}
	else if (rate < 2000)
	{ //	ii.	1000的几率掉落一件同等级段的随机门派蓝色武器。
		file = ARMOR_FILE->get_armor_file_2((level / 10) * 10);
		item = new (file);
		if (!item)
		{
			return 0;
		}
		ITEM_EQUIP_D->init_equip_prop_1(item);
	}
	else if (rate < 3000)
	{ //	iii.	1000的几率掉落一个随机的低级宠物食物。
		item = new ("/item/44/4403");
	}
	else if (rate < 3500)
	{ //	v.	500的几率掉落一个宝箱（紫金、青铜、红木随机一个）
		item = new (sprintf("/item/01/020%d", random(3)));
	}
	else if (rate < 4000)
	{ //	vi.	500的几率掉落道具“紫参丹”一颗。
		item = new ("/item/91/9167");
	}
	else if (rate < 8300)
	{ //	vii.	4300的几率掉落同等级段随机生活技能配方一个。
		level2 = me->get_level() / 10 * 10;
		if (level2 > 120)
		{
			level2 = 120;
		}
		if (load_object(file = "/quest/product2"->get_random_level_product(level2, level2)))
		{
			item = new (file);
		}
		else
		{
			return 0;
		}
	}
	else if (rate < 9871)
	{ //	viii.	1500的几率掉落随机技能进阶一本。//8-23	viii.	1571的几率掉落随机技能进阶一本。
		item = new (BOOK_FILE->get_book_file());
	} /*else if(rate < 9941 ) {	//	i.	100的几率随机变身卡一张。。	//8-23	ix.	70的几率随机变身卡一张。
		item = new (sprintf("/item/54/%04d",change54[random(sizeof(change54))]));
	}*/
	else if (rate < 9946)
	{ //	ii.	40的几率掉落随机一级晶石一颗	//8-23	x.	5的几率掉落随机一级晶石一颗
		file = STONE_FILE->get_diamond_file();
		item = new (file);
		if (!item)
		{
			return 0;
		}
		item->set_level(1);
	}
	else if (rate < 9951)
	{ //	iii.	10的几率掉落小血石		//8-23	xi.	5的几率掉落小血石
		item = new ("/item/08/0003");
	}
	else if (rate < 9956)
	{ //	iv.	10的几率掉落小法力石		//8-23	xii.	5的几率掉落小法力石
		item = new ("/item/08/0004");
	}
	else if (rate < 9962)
	{ //	v.	10的几率掉落战国号角		//8-23	xiii.	6的几率掉落战国号
		item = new ("/item/08/0002");
	}
	else if (rate < 9969)
	{ //	vi.	5的几率掉落低级宠物食物		//8-23	xiv.	7的几率掉落玉灵液一瓶。
		item = new ("/item/44/4403");
	}
	else if (rate < 9970)
	{ //	vii.	5的几率掉落战国令		//8-23	xv.	1的几率掉落战国令
		item = new ("/item/08/0001");
	}
	else if (rate < 9985)
	{ //	viii.	10的几率掉落速效小治愈药水。	//8-23	xvi.	15的几率掉落速效小治愈药水。
		item = new ("/item/sell/0007");
	}
	else if (rate < 10000)
	{ //	ix.	10的几率掉落速效小恢复药水。	//8-23	xvii.	15的几率掉落速效小恢复药水。
		item = new ("/item/sell/0009");
	}
	if (!item)
	{
		return 0;
	}
	TEAM_D->drop_item(item, who);
	item->set_user_id(owner);
	item->add_to_scene(z, p / 1000, p % 1000);
	item->set("winner", who);
	item->set("time", time());
}
void win_bonus_callout(object me, object who)
{
	object owner, *team;
	int level, level2, exp, exp2, pot, alllevel, knbkhoa, knbkhoa2, knb;
	int i, size, status, time, flag, vip;

	if (!objectp(who = me->get_enemy_4()))
		return;

	if (owner = who->get_owner())
		who = owner;
	if (who->is_npc())
		return;
	if (who->get_group_id())
		return;

	CHAT_D->sys_channel(0, HIY "Nghe nói tên Trộm Bảo Phi Tặc đã bị bằng hữu " + who->get_name() + " tiêu diệt");
	if (who->get_online_rate())
	{
		drop_items(me, who);
	}

	level = me->get_level();
	if (who->get_leader() && arrayp(team = who->get_team()) && sizeof(team) > 1)
	{
		team = me->correct_bonus_team(team);
		size = sizeof(team);
	}
	else
	{
		team = ({who});
		size = 1;
	}

	alllevel = 0;
	for (i = 0; i < size; i++)
		if (team[i])
		{
			alllevel += team[i]->get_level();
		}
	if (alllevel == 0)
		alllevel = 1;
	exp = level * 100;
	pot = level * 5;
	knb = (level / 2) / size > 1 ? (level / 2) / size : 1;
	knbkhoa2 = random(level * 20 / 100 / size) + 1;
	knbkhoa = knbkhoa2 > 1 ? knbkhoa2 : 1;
	for (i = 0; i < size; i++)
		if (team[i])
		{
			// if (team[i]->get_vip())
			// 	vip = team[i]->get_save("kenvip") * 5;
			level2 = level - team[i]->get_level();
			exp2 = exp * team[i]->get_level() / alllevel;
			exp2 = me->correct_exp_bonus(level, level2, exp2) * who->get_online_rate() / 100;

			if (exp2 < 5)
				exp2 = 5;
			exp2 = exp2 * team[i]->get_online_rate() / 100;
			pot = pot * team[i]->get_online_rate() / 100;
			team[i]->add_exp(exp2);
			team[i]->add_potential(pot);
			"sys/sys/test_db"->add_yuanbao(team[i], knb);
			team[i]->add_knbkhoa(knbkhoa);
			write_user(team[i], sprintf(ECHO "Bạn tiêu diệt Phi Tặc cấp %d và nhận được %d Ngân Bảo và %d Ngân Bảo Khóa !", level, knb, knbkhoa));

			/*		write_user(team[i], sprintf(ECHO "Bạn tiêu diệt Phi Tặc cấp %d và nhận được %d Kim Bảo, VIP(+%d KNB) !",level, (level*10/size)/10, ((level*10/size)*vip/100)/10 ));
				"sys/sys/test_db"->add_yuanbao(team[i],10/size);
			write_user(team[i], sprintf(ECHO "Bạn tiêu diệt Phi Tặc cấp %d và nhận được %d Kim Nguyên Bảo !",level, 10/size ));*/
		}
}