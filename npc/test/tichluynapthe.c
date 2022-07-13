#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>
#include <equip.h>
#include <time.h>
#include <effect.h>
#include <skill.h>

inherit OFFICER;

int iStart2, iFinish2, close_val, open_val, BatDau, KetThuc;

// 函数:获取人物造型
int get_char_picid() { return 9003; }
void do_gift(string arg);
// 函数：小贩识别
int is_seller() { return 7010; }
int is_self_look() { return 1; }

void create()
{

	set_name("Thiên Nhân");
	set_real_name("Sứ Giả Tích Lũy");
	set_2("good", (["01":"/item/100/10060",
					  "02":"/item/100/11060",
					  "03":"/item/100/10061",
					  "04":"/item/100/11061",
					  "05":"/item/100/10062",
					  "06":"/item/100/11062",
					  "07":"/item/100/10063",
					  "08":"/item/100/11063",
					  "09":"/item/100/10064",
					  "10":"/item/100/11064",
					  //	  "11":"/item/100/10065",
					  //	  "12":"/item/100/11065",
					  "11":"/item/ride/thucuoivip/cao",
					  "12":"/item/ride/thucuoivip/cavoi",
					  "13":"/item/ride/thucuoivip/chim",
					  "14":"/item/ride/thucuoivip/dadieu",
					  "15":"/item/ride/thucuoivip/gau",
					  "16":"/item/ride/thucuoivip/kien",
					  "17":"/item/ride/thucuoivip/ngua",
					  "18":"/item/ride/thucuoivip/rua",
					  "19":"/item/ride/thucuoivip/tham",
					  "20":"/item/ride/thucuoivip/tuanloc",
					  "21":"/item/ride/thucuoivip/voi",
					  //  "24":"/item/01/0007",

					  //	"05" : "/item/sell/0031",
					  //	"06" : "/item/sell/0031_2",
	]));
	set_2("talk", (["gift":(
							   : do_gift:),
	]));

	setup();
}

void do_look(object who)
{
	int id = getoid(this_object());
	int dtlnt = who->get_save("diemtlnt");
	object me = this_object();
	string result;
	send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n Ngươi hiện có:" HIR " %d " NOR " Điểm Tích Lũy Nạp Thẻ \n Quỹ Nhận Quà hiện có:\n- Quỹ 50: %d ngày\n- Quỹ 100: %d ngày\n- Quỹ 200: %d ngày\n- Quỹ 500: %d ngày\n- Quỹ 1000: %d ngày\n Hãy dùng nó để đổi lấy phần thưởng \n"

																 ESC HIG "Mua vật phẩm (Bằng Điểm Tích Lũy Nạp Thẻ)\nlist10 %x#\n"
																 //
																 ESC HIG "Mua vật phẩm (Bằng Điểm Tích Lũy Nạp Thẻ)\ntalk %x# gift.1\n"
																 //
																 ESC "Nhận quà hằng ngày quỹ - 50\ntalk %x# gift.50\n"
																 //
																 ESC "Nhận quà hằng ngày quỹ - 100\ntalk %x# gift.100\n"
																 //
																 ESC "Nhận quà hằng ngày quỹ - 200\ntalk %x# gift.200\n"
																 //
																 ESC "Nhận quà hằng ngày quỹ - 500\ntalk %x# gift.500\n"
																 //
																 ESC "Nhận quà hằng ngày quỹ - 1000\ntalk %x# gift.1000\n"
																 //
																 ESC "Rời khỏi",
																 get_name(), dtlnt, who->get_save_2("goiquahangngay.50.luot"), who->get_save_2("goiquahangngay.100.luot"), who->get_save_2("goiquahangngay.200.luot"), who->get_save_2("goiquahangngay.500.luot"), who->get_save_2("goiquahangngay.1000.luot"), id, id, id, id, id, id, id));
}

void do_gift(string arg)
{
	object me = this_object();
	__FILE__->do_gift2(me, arg);
}

void do_gift2(object me, string arg)
{
	int flag, id, i, size, p, iTime, iDay, iGio, exp, cashkhoa, knbkhoa;
	object who, *objs, target;
	string *nTmp, result, ngay, luot;
	mixed *mxTime;
	iTime = time();
	mxTime = localtime(iTime);
	iDay = mxTime[TIME_YDAY];
	iGio = mxTime[TIME_HOUR];

	who = this_player();
	id = getoid(me);
	flag = to_int(arg);
	who->set_time("talk", 0);

	switch (flag)
	{
	case 1:

		objs = children("/npc/test/tichluynapthe_2");
		//	printf(objs);
		size = sizeof(objs);
		if (size == 0)
		{
			return;
		}
		for (i = 0; i < size; i++)
		{
			if (objectp(objs[i]))
			{
				target = objs[i];
				break;
			}
		}

		if (!target)
		{

			return;
		}
		//	me->set("pawn_time", time());
		"/cmd/std/list10"->main(who, sprintf("%x#", getoid(target)));

		return;
		break;
	case 50:
	case 100:
	case 200:
	case 500:
	case 1000:
		ngay = sprintf("goiquahangngay.%d.ngay", flag);
		luot = sprintf("goiquahangngay.%d.luot", flag);
		if (!who->get_save_2("goiquahangngay"))
		{
			result = me->get_name() + "：\n Ngươi không có quỹ quà hằng ngày !\n";
			send_user(who, "%c%c%w%s", ':', 3, 6010, result);
			return;
		}
		if (!who->get_save_2(sprintf("goiquahangngay.%d", flag)))
		{
			result = me->get_name() + "：\n Ngươi không có gói quà hằng ngày của quỹ này !\n";
			send_user(who, "%c%c%w%s", ':', 3, 6010, result);
			return;
		}
		if (who->get_save_2(ngay) == iDay)
		{
			result = me->get_name() + "：\n Ngươi đã nhận quà hôm nay rồi mai hãy đến nhé !\n";
			send_user(who, "%c%c%w%s", ':', 3, 6010, result);
			return;
		}
		if (who->get_save_2(luot) < 1)
		{
			result = me->get_name() + "：\n Ngươi đã nhận xong toàn bộ mốc quà hằng ngày của quỹ này !\n";
			send_user(who, "%c%c%w%s", ':', 3, 6010, result);
			return;
		}
		if (flag == 100)
			exp = 5000 + USER_EXP_D->get_level_exp(who->get_reincarnation(), who->get_level()) * 20 / 100;
		else if (flag == 200)
			exp = 5000 + USER_EXP_D->get_level_exp(who->get_reincarnation(), who->get_level()) * 30 / 100;
		else if (flag == 500)
			exp = 5000 + USER_EXP_D->get_level_exp(who->get_reincarnation(), who->get_level()) * 40 / 100;
		else if (flag == 1000)
			exp = 5000 + USER_EXP_D->get_level_exp(who->get_reincarnation(), who->get_level()) * 50 / 100;
		else
			exp = 0;
		knbkhoa = flag / 10;
		cashkhoa = flag * 200;
		who->set_save_2(ngay, iDay);
		who->add_save_2(luot, -1);
		who->add_knbkhoa(knbkhoa);
		who->add_cashkhoa(cashkhoa);
		who->add_exp(exp);
		send_user(who, "%c%s", ':', me->get_name() + sprintf(":\nNhận điểm danh quỹ %d thành công. Bạn nhận được %d Kinh Nghiệm và %d Ngân Lượng Khóa, %d Ngân Bảo Khóa.\n" ESC "Rời khỏi.", flag, exp, cashkhoa, knbkhoa));

		if (who->get_save_2(luot) < 1)
		{
			who->delete_save_2(sprintf("goiquahangngay.%d", flag));
			result = me->get_name() + "：\n Ngươi đã nhận xong toàn bộ quà hàng ngày của quỹ này!\n";
			send_user(who, "%c%c%w%s", ':', 3, 6010, result);
			// return;
		}
		return;
		//	send_user(who, "%c%s", ';', sprintf("Nhận được %d Ngân lượng, %d KNB, %sx%d, %sx%d, %sx%d", tien, knb, item1->get_name(), vip, item2->get_name(), vip, item3->get_name(), vip));
		break;
	default:

		break;
	}
	return;
}
