/* Công chiến Vô Song Thành - fix and new code by Ben */
#include <ansi.h>
#include <task.h>
#include <time.h>
#include <city.h>
#include <chia_kenh.h>
inherit DBASE_F;
inherit SAVE_F;

#define _TEST_WS

#define ENTER_WUSHUANG(x) x->add_to_scene(701, 121, 141);
#define GET_TIME get_party_time()
#define START_ATT_HOUR 20
#define START_ATT_MIN 30
#define FINISH_ATT_HOUR 22
#define FINISH_ATT_MIN 0

int iFlag; //0 为关闭
int iWarStatus;
void org_title(string cName, int flag);
int check_war_time();
string get_occupy_org();

// 函数:生成二进制码
void SAVE_BINARY() {}

string get_save_file() { return "data/vosongthanh" SAVE_EXTENSION; }

void create()
{
	object npc;
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		// send_user(me, "%c%s", '!', "Vui lòng sử dụng tính năng bang phái ở Kênh Bang Phái");
		return;
	}
	restore();
	call_out("check_time", 3);
}

int check_join_attack(object me, object who)
{
	int date, wday;
	mixed *mxTime;

	if (iFlag == 1)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Hoạt động còn chưa mở!\n" ESC "Thoát", me->get_name()));
		return 0;
	}
	if (who->get_org_position() != ORG_MASTER)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Chỉ có bang chủ mới có tư cách đăng kí chiếm Vô Song Thành!\n" ESC "Thoát", me->get_name()));
		return 0;
	}
	wday = localtime(time())[TIME_WDAY];
	if (wday == 6 || wday == 0)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Không thể đăng ký Vô Song Thành vào Thứ 7, Chủ Nhật!\n" ESC "Thoát", me->get_name()));
		return 0;
	}
	mxTime = localtime(GET_TIME);
	date = mxTime[TIME_YEAR] * 10000 + (mxTime[TIME_MON] + 1) * 100 + mxTime[TIME_MDAY];
	if (get_save_2("join_org." + who->get_org_name() + ".date") >= date)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Bang phái của ngươi đã đăng ký rồi!\n" ESC "Thoát", me->get_name()));
		return 0;
	}
	if (who->get_cash() < 3000000)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Ngươi mang theo không đủ 3.000.000 ngân lượng!\n" ESC "Thoát", me->get_name()));
		return 0;
	}

	return 1;
}
void query_join_attack(object me, object who)
{
	if ("sys/main/main"->get_kenh() != KENH_BANG)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Vui lòng đăng ký ở Kênh Bang Phái!\n" ESC "Thoát", me->get_name()));
		return;
	}
	if (check_join_attack(me, who) != 1)
		return;
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Vô Song Thành chính là tượng trưng cho địa vị, bạn muốn công chiến Vô Song Thành, trước hết hãy giao nộp 3.000.000 lượng đã!\n" ESC "Đăng kí vô song thành\ntalk %x# welcome.75\n" ESC "Thoát", me->get_name(), getoid(me)));
}

void join_attack(object me, object who)
{
	int date, wday;
	string *nTmp;
	mixed *mxTime;
	if ("sys/main/main"->get_kenh() != KENH_BANG)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Vui lòng đăng ký ở kênh Bang Phái!\n" ESC "Thoát", me->get_name()));
		return;
	}
	if (check_join_attack(me, who) != 1)
		return;

	wday = localtime(time())[TIME_WDAY];
	who->add_cash(-3000000);
	//mxTime = localtime(GET_TIME + 3600 * 24 * 2);
	mxTime = localtime(GET_TIME + 3600 * 24 * (7 - wday));
	date = mxTime[TIME_YEAR] * 10000 + (mxTime[TIME_MON] + 1) * 100 + mxTime[TIME_MDAY];
	nTmp = get_save_2(sprintf("attack_list.%d.orgs", date));
	if (!arrayp(nTmp))
		nTmp = ({who->get_org_name()});
	else
		nTmp += ({who->get_org_name()});
	set_save_2(sprintf("attack_list.%d.orgs", date), nTmp);
	set_save_2("join_org." + who->get_org_name() + ".date", date);
	save();
	//发邮件给帮众
	"sys/sys/manager"->org_mail(0, who->get_org_name(), sprintf("Bổn bang vào Ngày %d tháng %d %02d:%02d - %02d:%02d sẽ tấn công vô song thành, thành viên trong bang hãy chuẩn bị công thành.", mxTime[TIME_MDAY], mxTime[TIME_MON] + 1, START_ATT_HOUR, START_ATT_MIN, FINISH_ATT_HOUR, FINISH_ATT_MIN));
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n Bạn đã đăng ký chiếm Vô Song Thành, thời gian là Chủ Nhật ngày sau 20:30 - 22:00, bạn cũng có thể thông qua Vô Song Thành Thủ Vệ(270, 187) để kiểm tra thời gian công thành.\n" ESC "Thoát", me->get_name()));
}
//进入无双城
void trans_into_wushuang(object me, object who, int arg)
{
	int p, x, y, date, date1;
	mixed *mxTime;
	if (iFlag == 1)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Hoạt động chưa mở!\n" ESC "Thoát", me->get_name()));
		return 0;
	}
	if (who->get_org_name() == "")
		return;
	mxTime = localtime(GET_TIME);
	date = mxTime[TIME_YEAR] * 10000 + (mxTime[TIME_MON] + 1) * 100 + mxTime[TIME_MDAY];
	if (!get_save_2("old_occupy_org") || get_save_2("old_occupy_org") != who->get_org_name())
	{
		if ((date1 = get_save_2("join_org." + who->get_org_name() + ".date")) < date)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Bang phái của bạn không đăng kí chiếm Vô Song Thành, không thể tiến vào Vô Song Thành!\n" ESC "Thoát", me->get_name()));
			return;
		}
		if (date1 > date)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Bang phái của bạn xin chiếm Vô Song Thành không phải hôm nay, không thể tiến vào Vô Song Thành!\n" ESC "Thoát", me->get_name()));
			return;
		}
	}
	if (!(p = get_jumpin(888, 1)))
		return;
	if (arg == 1)
	{
		who->add_to_scene(888, 119, 99, get_d(who), 40971, 0, 40971, 0);
		return;
	}
	if (arg == 2)
	{
		who->add_to_scene(888, 64, 57, get_d(who), 40971, 0, 40971, 0);
		return;
	}
	if (arg == 3)
	{
		who->add_to_scene(888, 100, 72, get_d(who), 40971, 0, 40971, 0);
		return;
	}
	if (arg == 4)
	{
		who->add_to_scene(888, 144, 84, get_d(who), 40971, 0, 40971, 0);
		return;
	}
	if (arg == 5)
	{
		who->add_to_scene(888, 93, 43, get_d(who), 40971, 0, 40971, 0);
		return;
	}
}
//攻城列表
void attack_list(object me, object who)
{
	int i, j, size, date;
	mixed *mxTime;
	string cTmp;
	string *nTmp;

	cTmp = "";
	if (iFlag == 1)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Hoạt động chưa mở!\n" ESC "Thoát", me->get_name()));
		return 0;
	}
	for (j = 0; j < 3; j++)
	{
		mxTime = localtime(GET_TIME + 3600 * 24 * j);
		date = mxTime[TIME_YEAR] * 10000 + (mxTime[TIME_MON] + 1) * 100 + mxTime[TIME_MDAY];
		nTmp = get_save_2(sprintf("attack_list.%d.orgs", date));
		if (!arrayp(nTmp) || !(size = sizeof(nTmp)))
			continue;
		cTmp += sprintf(" Ngày %2d tháng %2d :  ", mxTime[TIME_MDAY], mxTime[TIME_MON] + 1);
		for (i = 0; i < size; i++)
		{
			cTmp += nTmp[i] + " Bang hội, ";
		}
		cTmp += "\n";
	}
	if (sizeof(cTmp) == 0)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n Trước mắt ko có bang phái nào đăng kí.\n" ESC "Thoát", me->get_name()));
		return;
	}
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n Các bang sắp công thành :\n%s\n" ESC "Thoát", me->get_name(), cTmp));
}
//占领城市
void occupy_city(object me, object who)
{
	int date, date1, flag, i, size;
	string org_name, old_org;
	mixed *mxTime;
	object map, *nPlayer, oPlayer;

	if (iFlag == 1)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Hoạt động còn chưa mở!\n" ESC "Thoát", me->get_name()));
		return;
	}
	if (gone_time(me->get("occupy_time")) < 5) //限制申请的间隔
		return;
	me->set("occupy_time", GET_TIME);
	map = get_map_object(get_z(me));
	if (!map || !map->is_wushuang_palace())
		return;
	if (who->get_org_position() != ORG_MASTER)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Chỉ có bang chủ mới có thể chiếm Vô Song Thành!\n" ESC "Thoát", me->get_name()));
		return;
	}
	if (get_save_2("occupy_org") == (org_name = who->get_org_name()))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Bang phái đã chiếm Vô Song Thành rồi!\n" ESC "Thoát", me->get_name()));
		return;
	}
	mxTime = localtime(GET_TIME);
	date = mxTime[TIME_YEAR] * 10000 + (mxTime[TIME_MON] + 1) * 100 + mxTime[TIME_MDAY];
	if (!get_save_2("old_occupy_org") || get_save_2("old_occupy_org") != org_name)
	{
		if ((date1 = get_save_2("join_org." + org_name + ".date")) < date)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Bang phái không đăng kí chiếm Vô Song Thành!\n" ESC "Thoát", me->get_name()));
			return;
		}
		if (date1 > date)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Bang phái không có dăng ký chiếm Vô Song Thành vào hôm nay!\n" ESC "Thoát", me->get_name()));
			return;
		}
	}
	if (check_war_time() != 1)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Bây giờ không phải là thời gian chiếm Vô Song Thành!\n" ESC "Thoát", me->get_name()));
		return;
	}
	nPlayer = map->get_all_user();
	size = sizeof(nPlayer);
	if (!size)
		return;
	for (i = 0; i < size; i++)
	{
		oPlayer = nPlayer[i];
		if (oPlayer && oPlayer->get_org_name() == org_name)
			continue;
		if (oPlayer->is_die())
			continue;
		flag = -1;
		break;
	}
	if (flag == -1)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Vô Song Cung vẫn còn bang phái khác, không thể chiếm lĩnh!\n" ESC "Thoát", me->get_name()));
		return;
	}
	old_org = get_save_2("occupy_org");
	set_save_2("occupy_org", org_name);
	set_save_2("occupy_time", GET_TIME);
	log_file("wushuang.txt", sprintf("%s %s(%d) %s Chiếm lĩnh Vô Song Thành\n",
									 short_time(GET_TIME), who->get_name(), who->get_number(), org_name));
	save();
	org_title(org_name, 1);
	org_title(old_org, 0);
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n Bạn đã tạm thời chiếm lĩnh Vô Song Thành! \nBạn nhận được danh hiệu \"Vô Song Thành Chủ\" !\n" ESC "Thoát", me->get_name()));
	CHAT_D->sys_channel(0, sprintf("Bang hội " HIY "%s" NOR " với sự lãnh đạo của " HIY "%s" NOR " đã tạm thời chiếm lĩnh Vô Song Thành !", org_name, who->get_name()));
	CHAT_D->sys_channel(0, sprintf("Bang hội " HIY "%s" NOR " với sự lãnh đạo của " HIY "%s" NOR " đã tạm thời chiếm lĩnh Vô Song Thành !", org_name, who->get_name()));
	CHAT_D->sys_channel(0, sprintf("Bang hội " HIY "%s" NOR " với sự lãnh đạo của " HIY "%s" NOR " đã tạm thời chiếm lĩnh Vô Song Thành !", org_name, who->get_name()));
}

//检查称谓
void check_org_title(object who)
{
	object file;
	if (who->get_org_name() == get_save_2("occupy_org"))
	{
		if (who->get_org_position() == ORG_MASTER)
		{
			if (!who->have_title("Z888"))
				who->add_title("Z888");
			if (who->have_title("Z889"))
				who->delete_title("Z889");
			if (file = load_object(SKILL->get_skill_file(0099)))
				file->can_perform(who);
		}
		else
		{
			if (who->have_title("Z888"))
				who->delete_title("Z888");
			if (!who->have_title("Z889"))
				who->add_title("Z889");
		}
	}
	else
	{
		if (who->have_title("Z888"))
		{
			who->delete_title("Z888");
			if (file = load_object(SKILL->get_skill_file(0099)))
				file->remove_perform(who);
		}
		if (who->have_title("Z889"))
			who->delete_title("Z889");
	}
}
//处理无双称谓
void org_title(string cName, int flag)
{
	int i, size;
	object orgnpc, who, file;
	string cTmp, *nName;

	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", cName));
	if (!objectp(orgnpc))
		return;
	size = orgnpc->sizeof_member_dbase();
	nName = orgnpc->get_all_member();
	for (i = 0; i < size; i++)
	{
		who = find_char(nName[i]);
		if (!who)
			continue;
		check_org_title(who);
		if (flag)
		{
			if (who->get_org_position() == ORG_MASTER)
			{
				who->show_title("Z888");
				if (file = load_object(SKILL->get_skill_file(0099)))
					file->can_perform(who);
			}
			else
				who->show_title("Z889");
		}
	}
}

void check_time()
{
	int iStart, iStart1, iFinish, date, date1, i, size, size2, p, x, y, j, ben;
	mixed *mxTime;
	string *nTmp, *nTmp2, org_name, master_name, cTmp;
	object orgnpc, npc;

	remove_call_out("check_time");
	if (MAIN_D->get_kenh() == KENH_BANG)
	{
		return;
	}
	if (iFlag == 1)
	{
		call_out("check_time", 3600);
		return;
	}
	mxTime = localtime(GET_TIME);
	date = mxTime[TIME_YEAR] * 10000 + (mxTime[TIME_MON] + 1) * 100 + mxTime[TIME_MDAY];
	iStart = mktime(mxTime[TIME_YEAR], mxTime[TIME_MON] + 1, mxTime[TIME_MDAY], START_ATT_HOUR, START_ATT_MIN, 0);
	iFinish = mktime(mxTime[TIME_YEAR], mxTime[TIME_MON] + 1, mxTime[TIME_MDAY], FINISH_ATT_HOUR, FINISH_ATT_MIN, 0);
	nTmp2 = get_save_2(sprintf("attack_list.%d.orgs", date));
	if (!arrayp(nTmp2) || !(size2 = sizeof(nTmp2)))
	{
		call_out("check_time", 30);
		return;
	}
	if (GET_TIME < iStart) //攻城前
	{
		call_out("check_time", iStart - GET_TIME);
		if (iWarStatus)
		{
			iWarStatus = 0;
			set_save_2("old_occupy_org", get_save_2("occupy_org"));
			save();
		}
		return;
	}
	if (GET_TIME < iFinish) //攻城期间
	{
		call_out("check_time", iFinish - GET_TIME);
		if (!iWarStatus)
			iWarStatus = 1;
	}
	else //攻城后
	{
		mxTime = localtime(iStart + 3600 * 24); //下次攻城时间
		iStart1 = mktime(mxTime[TIME_YEAR], mxTime[TIME_MON] + 1, mxTime[TIME_MDAY], START_ATT_HOUR, START_ATT_MIN, 0);
		call_out("check_time", iStart1 - GET_TIME);
		if (iWarStatus && iWarStatus < 5)
			iWarStatus = 5;
	}
	if (iWarStatus == 1)
	{
		iWarStatus = 2;
		nTmp = get_save_2(sprintf("attack_list.%d.orgs", date));
		if (check_war_time() == 1)
		{
			size = sizeof(nTmp);
			for (i = 0; i < size; i++)
			{
				"sys/sys/manager"->org_mail(0, nTmp[i], HIY "Bổn bang sắp tấn công Vô Song Thành, nhanh nhanh đến trợ giúp!");
			}
			CHAT_D->sys_channel(0, "Trận chiến tranh đoạt Vô Song Thành đã bắt đầu!");
			CHAT_D->sys_channel(0, "Trận chiến tranh đoạt Vô Song Thành đã bắt đầu!");
			CHAT_D->sys_channel(0, "Trận chiến tranh đoạt Vô Song Thành đã bắt đầu!");
			"/sys/party/vstfix"->add_mokhoa(-"/sys/party/vstfix"->get_mokhoa());
			"/sys/party/vstfix"->set_mokhoa1(0);
			"/sys/party/vstfix"->set_mokhoa2(0);
			"/sys/party/vstfix"->set_mokhoa3(0);
		}
	}
	else if (iWarStatus == 5) //清除旧的数据
	{
		iWarStatus = 0;
		set_save_2("old_occupy_org", get_save_2("occupy_org"));
		nTmp = get_save_2(sprintf("attack_list.%d.orgs", date));
		size = sizeof(nTmp);
		for (i = 0; i < size; i++)
		{
			delete_save_2("join_org." + nTmp[i]);
		}
		delete_save_2(sprintf("attack_list.%d", date));
		if (org_name = get_occupy_org())
		{
			orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", org_name));
			if (objectp(orgnpc))
			{
				master_name = orgnpc->get_master_name();
				cTmp = sprintf(HIR "Trận chiến tranh đoạt Vô Song Thành kết thúc, Bang hội " HIG "%s" HIR " với sự anh minh lãnh đạo của " HIG "%s" HIR " đã thành công chiếm lĩnh Vô Song Thành !", org_name, master_name);
				for (i = 0; i < 4; i++)
				{
					CHAT_D->sys_channel(0, cTmp);
					send_user(CHAT_D->get_chat(), "%c%s", 0xA3, cTmp);
				}
			}
		}
		"/sys/party/vstfix"->add_mokhoa(-"/sys/party/vstfix"->get_mokhoa());
		"/sys/party/vstfix"->set_mokhoa1(0);
		"/sys/party/vstfix"->set_mokhoa2(0);
		"/sys/party/vstfix"->set_mokhoa3(0);
	}
	save();
}
//是否可以进入无双宫
int can_enter_palace(object who, object map)
{
	string org_name;

	org_name = get_save_2("occupy_org");
	if (sizeof(org_name) && org_name == who->get_org_name()) //占领的帮派
		return 1;
	//攻打时间内才能进去
	if (check_war_time() != 1)
		return 0;
	return 1;
}
//判断是否攻城时间
int check_war_time()
{
	mixed *mxTime;

	if (iFlag == 1)
		return 0;
	mxTime = localtime(GET_TIME);
	if (mxTime[TIME_HOUR] < START_ATT_HOUR || (mxTime[TIME_HOUR] == START_ATT_HOUR && mxTime[TIME_MIN] < START_ATT_MIN) || (mxTime[TIME_HOUR] > FINISH_ATT_HOUR) || (mxTime[TIME_HOUR] == FINISH_ATT_HOUR && mxTime[TIME_MIN] >= FINISH_ATT_MIN))
		return 0;
	return 1;
}
//check tên bang đã chiếm thành
string get_occupy_org()
{
	string org_name;

	org_name = get_save_2("occupy_org");
	return org_name ? org_name : "";
}

//设置活动状态	0 关闭 1 开启
/*int set_flag(int i)
{
	iFlag = i;
	save();
	check_time();
	return iFlag;	
}*/
//获取状态
void get_status(object who)
{
	if (iFlag == 1)
		tell_user(who, "Vô song công thành trạng thái : Tắt");
	if (iFlag == 0)
	{
		tell_user(who, "Vô song công thành trạng thái : Mở");
		tell_user(who, sprintf("Thời gian hoạt động : %02d:%02d - %02d:%02d", START_ATT_HOUR, START_ATT_MIN, FINISH_ATT_HOUR, FINISH_ATT_MIN));
	}
}
//设置游戏时间
void set_wushuang_time(object who, string tmp)
{
	int year, mon, day, hour, min, sec;

	if (sscanf(tmp, "%d-%d-%d %d:%d:%d", year, mon, day, hour, min, sec) != 6)
	{
		send_user(who, "%c%s", '!', "Cách thức sai !");
		return;
	}
	tell_user(who, "Thiết lập thời gian là : %s", short_time(set_party_time(year, mon, day, hour, min, sec)));
	check_time();
	if (iFlag == 1)
		tell_user(who, "Vô song thành chiến trạng thái: Tắt");
	else
		tell_user(who, "Vô song thành chiến trạng thái: Mở");
}
//add mở khoá
int add_mokhoa(int i)
{
	add_save_2("mokhoa", i);
	//	set_save_2("occupy_org",get_save_2("occupy_org"));
	save();
	return i;
}
//check mở khoá
int get_mokhoa()
{
	int abc;
	abc = get_save_2("mokhoa");
	return abc ? abc : 0;
}
void do_hoatdongkhoa(int sec)
{
	int i, size, tId, p, x, y;
	object *member, npc, map;
	string id;
	sec = sec - 1;
	map = get_map_object(889);
	if (!map)
		return;
	member = map->get_all_user();

	if (sec > 0)
	{
		for (i = 0, size = sizeof(member); i < size; i++)
		{
			write_user(member[i], sprintf(HIR "Sau %d giây, bạn sẽ bị chuyển ra Vô Song Thành.", sec));
		}

		call_out("do_hoatdongkhoa", 1, sec);
	}
	else
	{
		for (i = 0, size = sizeof(member); i < size; i++)
		{
			if (p = get_jumpin(888, -1))
			{
				x = p / 1000, y = p % 1000;
				member[i]->add_to_scene(888, x, y, get_d(member[i]));
			}
		}
		"/sys/party/vstfix"->add_mokhoa(-"/sys/party/vstfix"->get_mokhoa());
		"/sys/party/vstfix"->do_hoatdongkhoa2(300);
	}
}
void do_hoatdongkhoa2(int sec)
{
	sec--;
	if (sec > 0)
	{
		call_out("do_hoatdongkhoa2", 1, sec);
	}
	else
	{
		"/sys/party/vstfix"->set_mokhoa1(0);
		"/sys/party/vstfix"->set_mokhoa2(0);
		"/sys/party/vstfix"->set_mokhoa3(0);
		USER_D->user_channel("Chìa khoá Ất đã " HIR "Tắt " NOR "!");
		USER_D->user_channel("Chìa khoá Bính đã " HIR "Tắt " NOR "!");
		USER_D->user_channel("Chìa khoá Giáp đã " HIR "Tắt " NOR "!");
	}
}
//set mở khoá 1
int set_mokhoa1(int i)
{
	set_save_2("khoa1", i);
	//	set_save_2("occupy_org",get_save_2("occupy_org"));
	save();
	return i;
}
//set mở khoá 2
int set_mokhoa2(int i)
{
	set_save_2("khoa2", i);
	//	set_save_2("occupy_org",get_save_2("occupy_org"));
	save();
	return i;
}
//set mở khoá 3
int set_mokhoa3(int i)
{
	set_save_2("khoa3", i);
	//	set_save_2("occupy_org",get_save_2("occupy_org"));
	save();
	return i;
}
//check khoá 1
int get_mokhoa1()
{
	int abc;
	abc = get_save_2("khoa1");
	return abc ? abc : 0;
}
//check khoá 2
int get_mokhoa2()
{
	int abc;
	abc = get_save_2("khoa2");
	return abc ? abc : 0;
}
//check khoá 3
int get_mokhoa3()
{
	int abc;
	abc = get_save_2("khoa3");
	return abc ? abc : 0;
}
int check_dk(object who)
{
	int date, date1;
	mixed *mxTime;
	mxTime = localtime(GET_TIME);
	date = mxTime[TIME_YEAR] * 10000 + (mxTime[TIME_MON] + 1) * 100 + mxTime[TIME_MDAY];
	if (!get_save_2("old_occupy_org") || get_save_2("old_occupy_org") != who->get_org_name())
	{
		if ((date1 = get_save_2("join_org." + who->get_org_name() + ".date")) < date)
		{
			who->add_to_scene(80, 285 + random(10), 115 + random(15));
			write_user(who, ECHO "Bang phái của bạn không có xin công thành.");
			return;
		}
		if (date1 > date)
		{
			who->add_to_scene(80, 285 + random(10), 115 + random(15));
			write_user(who, ECHO "Bang phái của bạn không có xin công thành vào ngày hôm nay.");
			return;
		}
	}
}
int checkctmk()
{
	int size2, date;
	mixed *mxTime;
	string *nTmp2;

	mxTime = localtime(GET_TIME);
	date = mxTime[TIME_YEAR] * 10000 + (mxTime[TIME_MON] + 1) * 100 + mxTime[TIME_MDAY];
	nTmp2 = get_save_2(sprintf("attack_list.%d.orgs", date));
	if (!arrayp(nTmp2) || !(size2 = sizeof(nTmp2)))
	{
		return 0;
	}
	return 1;
}