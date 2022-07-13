/********************************************************************************************************************************
-----------------------Đoạt Bảo Mã Tặc --------------------
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

#define DoatBaoMaTac "npc/event/doatbaomatac"

void generate_scum();
void generate_scum1();
void generate_scum2();
void generate_scum3();
void generate_scum4();
void generate_scum5();
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
	mixed *mixTime;
	object robber;

	remove_call_out("check_time");
	iTime = time();

	mixTime = localtime(iTime);

	if (mixTime[TIME_WDAY] == 1 || mixTime[TIME_WDAY] == 3 || mixTime[TIME_WDAY] == 5 || mixTime[TIME_WDAY] == 0) // Thứ 3, t5, t7 có Boss
	{
		call_out("check_time", 3600 * (24 - mixTime[TIME_HOUR]));
		return;
	}
	else
	{
		i = 60 * (60 - mixTime[TIME_MIN]);
		if (mixTime[TIME_HOUR] % 2 == 0)
		{
			call_out("check_time", i);
		}
		else
		{
			if ((mixTime[TIME_HOUR] == 1) || (mixTime[TIME_HOUR] == 3) || (mixTime[TIME_HOUR] == 5) || (mixTime[TIME_HOUR] == 7) || (mixTime[TIME_HOUR] == 9 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 11 && mixTime[TIME_MIN] > 30) //Nếu giờ hiện tại là: 1 , 3, 5, 7h thì Kết thúc hàm -> ko có Phi Tặc
				|| (mixTime[TIME_HOUR] == 13 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 15) || (mixTime[TIME_HOUR] == 17 && mixTime[TIME_MIN] > 30)																					// Nếu ko có dòng > 30 thì 9h59 vẫn sẽ có phỉ còn nếu có thì khi bật GSE lên 9h30 sẽ ko có phỉ
				|| (mixTime[TIME_HOUR] == 19 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 21 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 0 && mixTime[TIME_MIN] > 30))
				call_out("check_time", i + 3600);
			else
			{
				if (random(10) < 3)
					generate_scum();
				else if (random(10) < 4)
					generate_scum1();
				else if (random(10) < 5)
					generate_scum2();
				else if (random(10) < 6)
					generate_scum3();
				else if (random(10) < 8)
					generate_scum4();
				else
					generate_scum5();
				"cmd/base/time"->set_doatbaomatac(1);

				call_out("check_time", i + 3600);
			}
		}
	}
}
//  Random 1
void generate_scum()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(041, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (DoatBaoMaTac);
		npc->add_to_scene(041, x, y);
		Scum += ({npc});
	}
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(042, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (DoatBaoMaTac);
		npc->add_to_scene(042, x, y);
		Scum += ({npc});
	}
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(043, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (DoatBaoMaTac);
		npc->add_to_scene(043, x, y);
		Scum += ({npc});
	}

	call_out("check_time2", 1800);
	"cmd/func/allfunc"->thongbao_event(HIR "Kênh Event:" HIG "Nghe nói có một đám Đoạt Bảo Mã Tặc đã trộm rất nhiều Kim Bảo từ triều đình và đang lẩn trốn, nghe nói chúng đang xuất hiện tại Bờ Vô Định Hà, Vô Định Hà 1, Vô Định Hà 2 !");
	CHAT_D->sys_channel(0, "Nghe nói có một đám Đoạt Bảo Mã Tặc đã trộm rất nhiều Kim Bảo từ triều đình và đang lẩn trốn, nghe nói chúng đang xuất hiện tại Bờ Vô Định Hà, Vô Định Hà 1, Vô Định Hà 2 !");
	CHAT_D->sys_channel(0, "Nghe nói có một đám Đoạt Bảo Mã Tặc đã trộm rất nhiều Kim Bảo từ triều đình và đang lẩn trốn, nghe nói chúng đang xuất hiện tại Bờ Vô Định Hà, Vô Định Hà 1, Vô Định Hà 2 !");
	//	CHAT_D->sys_channel(0,"Nghe nói có một đám Đoạt Bảo Mã Tặc đã xuất hiện tại Bờ Vô Định Hà, Vô Định Hà 1, Vô Định Hà 2 !");
}
//  Random 2
void generate_scum1()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(151, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (DoatBaoMaTac);
		npc->add_to_scene(151, x, y);
		Scum += ({npc});
	}
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(152, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (DoatBaoMaTac);
		npc->add_to_scene(152, x, y);
		Scum += ({npc});
	}
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(153, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (DoatBaoMaTac);
		npc->add_to_scene(153, x, y);
		Scum += ({npc});
	}

	call_out("check_time2", 1800);
	"cmd/func/allfunc"->thongbao_event(HIR "Kênh Event:" HIG "Nghe nói có một đám Đoạt Bảo Mã Tặc đã trộm rất nhiều Kim Bảo từ triều đình và đang lẩn trốn, nghe nói chúng đang xuất hiện tại Kênh Trịnh Quốc 1, Kênh Trịnh Quốc 2, Kênh Trịnh Quốc 3 !");

	CHAT_D->sys_channel(0, "Nghe nói có một đám Đoạt Bảo Mã Tặc đã trộm rất nhiều Kim Bảo từ triều đình và đang lẩn trốn, nghe nói chúng đang xuất hiện tại Kênh Trịnh Quốc 1, Kênh Trịnh Quốc 2, Kênh Trịnh Quốc 3 !");
	CHAT_D->sys_channel(0, "Nghe nói có một đám Đoạt Bảo Mã Tặc đã trộm rất nhiều Kim Bảo từ triều đình và đang lẩn trốn, nghe nói chúng đang xuất hiện tại Kênh Trịnh Quốc 1, Kênh Trịnh Quốc 2, Kênh Trịnh Quốc 3 !");
	//	CHAT_D->sys_channel(0,"Nghe nói có một đám Đoạt Bảo Mã Tặc đã xuất hiện tại Kênh Trịnh Quốc 1, Kênh Trịnh Quốc 2, Kênh Trịnh Quốc 3 !");
}
//  Random 3
void generate_scum2()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(012, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (DoatBaoMaTac);
		npc->add_to_scene(012, x, y);
		Scum += ({npc});
	}
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(013, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (DoatBaoMaTac);
		npc->add_to_scene(013, x, y);
		Scum += ({npc});
	}
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(014, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (DoatBaoMaTac);
		npc->add_to_scene(014, x, y);
		Scum += ({npc});
	}

	call_out("check_time2", 1800);
	"cmd/func/allfunc"->thongbao_event(HIR "Kênh Event:" HIG "Nghe nói có một đám Đoạt Bảo Mã Tặc đã trộm rất nhiều Kim Bảo từ triều đình và đang lẩn trốn, nghe nói chúng đang xuất hiện tại Bờ Đông Hải, Hải Tân 1, Hải Tân 2 !");

	CHAT_D->sys_channel(0, "Nghe nói có một đám Đoạt Bảo Mã Tặc đã trộm rất nhiều Kim Bảo từ triều đình và đang lẩn trốn, nghe nói chúng đang xuất hiện tại Bờ Đông Hải, Hải Tân 1, Hải Tân 2 !");
	CHAT_D->sys_channel(0, "Nghe nói có một đám Đoạt Bảo Mã Tặc đã trộm rất nhiều Kim Bảo từ triều đình và đang lẩn trốn, nghe nói chúng đang xuất hiện tại Bờ Đông Hải, Hải Tân 1, Hải Tân 2 !");
	//	CHAT_D->sys_channel(0,"Nghe nói có một đám Đoạt Bảo Mã Tặc đã xuất hiện tại Bờ Đông Hải, Hải Tân 1, Hải Tân 2 !");
}
//  Random 4
void generate_scum3()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(163, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (DoatBaoMaTac);
		npc->add_to_scene(163, x, y);
		Scum += ({npc});
	}
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(164, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (DoatBaoMaTac);
		npc->add_to_scene(164, x, y);
		Scum += ({npc});
	}
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(261, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (DoatBaoMaTac);
		npc->add_to_scene(261, x, y);
		Scum += ({npc});
	}

	call_out("check_time2", 1800);
	"cmd/func/allfunc"->thongbao_event(HIR "Kênh Event:" HIG "Nghe nói có một đám Đoạt Bảo Mã Tặc đã trộm rất nhiều Kim Bảo từ triều đình và đang lẩn trốn, nghe nói chúng đang xuất hiện tại Ranh Giới Đầm Lầy, Địa Giới Đầm Lầy, Chân Núi Đại Biệt !");

	CHAT_D->sys_channel(0, "Nghe nói có một đám Đoạt Bảo Mã Tặc đã trộm rất nhiều Kim Bảo từ triều đình và đang lẩn trốn, nghe nói chúng đang xuất hiện tại Ranh Giới Đầm Lầy, Địa Giới Đầm Lầy, Chân Núi Đại Biệt !");
	CHAT_D->sys_channel(0, "Nghe nói có một đám Đoạt Bảo Mã Tặc đã trộm rất nhiều Kim Bảo từ triều đình và đang lẩn trốn, nghe nói chúng đang xuất hiện tại Ranh Giới Đầm Lầy, Địa Giới Đầm Lầy, Chân Núi Đại Biệt !");
	//	CHAT_D->sys_channel(0,"Nghe nói có một đám Đoạt Bảo Mã Tặc đã xuất hiện tại Ranh Giới Đầm Lầy, Địa Giới Đầm Lầy, Chân Núi Đại Biệt !");
}
//  Random 5
void generate_scum4()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(141, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (DoatBaoMaTac);
		npc->add_to_scene(141, x, y);
		Scum += ({npc});
	}
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(142, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (DoatBaoMaTac);
		npc->add_to_scene(142, x, y);
		Scum += ({npc});
	}
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(211, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (DoatBaoMaTac);
		npc->add_to_scene(211, x, y);
		Scum += ({npc});
	}

	call_out("check_time2", 1800);
	"cmd/func/allfunc"->thongbao_event(HIR "Kênh Event:" HIG "Nghe nói có một đám Đoạt Bảo Mã Tặc đã trộm rất nhiều Kim Bảo từ triều đình và đang lẩn trốn, nghe nói chúng đang xuất hiện tại Mã Lăng Đạo, Bạch Mã Trang, Mã Đạp Hồ !");

	CHAT_D->sys_channel(0, "Nghe nói có một đám Đoạt Bảo Mã Tặc đã trộm rất nhiều Kim Bảo từ triều đình và đang lẩn trốn, nghe nói chúng đang xuất hiện tại Mã Lăng Đạo, Bạch Mã Trang, Mã Đạp Hồ !");
	CHAT_D->sys_channel(0, "Nghe nói có một đám Đoạt Bảo Mã Tặc đã trộm rất nhiều Kim Bảo từ triều đình và đang lẩn trốn, nghe nói chúng đang xuất hiện tại Mã Lăng Đạo, Bạch Mã Trang, Mã Đạp Hồ !");
	//	CHAT_D->sys_channel(0,"Nghe nói có một đám Đoạt Bảo Mã Tặc đã xuất hiện tại Mã Lăng Đạo, Bạch Mã Trang, Mã Đạp Hồ !");
}
//  Random 6
void generate_scum5()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(061, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (DoatBaoMaTac);
		npc->add_to_scene(061, x, y);
		Scum += ({npc});
	}
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(062, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (DoatBaoMaTac);
		npc->add_to_scene(062, x, y);
		Scum += ({npc});
	}
	for (i = 0; i < 10; i++)
	{
		if (!(p = efun::get_xy_point(063, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (DoatBaoMaTac);
		npc->add_to_scene(063, x, y);
		Scum += ({npc});
	}

	call_out("check_time2", 1800);
	"cmd/func/allfunc"->thongbao_event(HIR "Kênh Event:" HIG "Nghe nói có một đám Đoạt Bảo Mã Tặc đã trộm rất nhiều Kim Bảo từ triều đình và đang lẩn trốn, nghe nói chúng đang xuất hiện tại Sở Phương Thành 1, Sở Phương Thành 2, Sở Phương Thành 3 !");

	CHAT_D->sys_channel(0, "Nghe nói có một đám Đoạt Bảo Mã Tặc đã trộm rất nhiều Kim Bảo từ triều đình và đang lẩn trốn, nghe nói chúng đang xuất hiện tại Sở Phương Thành 1, Sở Phương Thành 2, Sở Phương Thành 3 !");
	CHAT_D->sys_channel(0, "Nghe nói có một đám Đoạt Bảo Mã Tặc đã trộm rất nhiều Kim Bảo từ triều đình và đang lẩn trốn, nghe nói chúng đang xuất hiện tại Sở Phương Thành 1, Sở Phương Thành 2, Sở Phương Thành 3 !");
	//	CHAT_D->sys_channel(0,"Nghe nói có một đám Đoạt Bảo Mã Tặc đã xuất hiện tại Sở Phương Thành 1, Sở Phương Thành 2, Sở Phương Thành 3 !");
}
//Sau 30 phút từ khi Đoạt Bảo xuất hiện sẽ biến mất
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
	"cmd/base/time"->set_doatbaomatac(0);
}

void win_bonus_callout(object me, object who)
{
	object owner, *team;
	int level, level2, exp, exp2, pot, alllevel;
	int i, size, status, time, flag, z, x, y, p, knbkhoa, knbkhoa2, knb, cash;

	if (!objectp(who = me->get_enemy_4()))
		return;

	if (owner = who->get_owner())
		who = owner;
	if (who->is_npc())
		return;
	if (who->get_group_id())
		return;

	CHAT_D->sys_channel(0, HIY "Bằng hữu " + who->get_name() + " thành công đoạt lại Kim Bảo từ Đoạt Bảo Mã Tặc.");
	who->delete_save_2("doatbaomatac");
	z = who->get_2("doatbaomatac.z");
	x = who->get_2("doatbaomatac.x");
	y = who->get_2("doatbaomatac.y");
	if (!(p = get_valid_xy(z, x, y, IS_CHAR_BLOCK)))
		return;
	x = p / 1000;
	y = p % 1000;
	who->add_to_scene(z, x, y, 3);

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
	knb = (level / 2) / size > 0 ? (level / 2) / size : 1;
	knbkhoa2 = random(level * 20 / 100 / size) + 1;
	knbkhoa = knbkhoa2 > 1 ? knbkhoa2 : 1;
	cash = level / size * random(100);
	for (i = 0; i < size; i++)
		if (team[i])
		{
			level2 = level - team[i]->get_level();
			exp2 = exp * team[i]->get_level() / alllevel;
			exp2 = me->correct_exp_bonus(level, level2, exp2) * who->get_online_rate() / 100;

			if (exp2 < 5)
				exp2 = 5;
			exp2 = exp2 * team[i]->get_online_rate() / 100;
			pot = pot * team[i]->get_online_rate() / 100;
			team[i]->add_exp(exp2);
			team[i]->add_potential(pot);
			team[i]->add_cash(cash);
			"sys/sys/test_db"->add_yuanbao(team[i], knb);
			team[i]->add_knbkhoa(knbkhoa);
			write_user(team[i], sprintf(ECHO "Bạn tiêu diệt Đoạt Bảo Mã Tặc cấp %d và nhận được %d Ngân Bảo và %d Ngân Bảo Khóa, %d ngân lượng !", level, knb, knbkhoa, cash));
			//	write_user(team[i], sprintf(ECHO "Bạn tiêu diệt Đoạt Bảo Mã Tặc và nhận được %d Ngân Bảo Khóa !", knbkhoa));
		}
}