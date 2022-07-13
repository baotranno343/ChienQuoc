#include <npc.h>
#include <city.h>
#include <ansi.h>
#include <effect.h>
#include <skill.h>
#include <equip.h>
#include <time.h>
inherit SAVE_F;
inherit OFFICER;

int iStart_n, iFinish_n;
#define GUESS_TRUE_TIGER "/sys/party/guess_true_tiger"

void do_bonus(string arg);
void do_tiger_bonus(string arg);

// 函数：获取人物造型
int get_char_picid() { return 0952; }
string get_save_file() { return "data/wg_national_ex" SAVE_EXTENSION; }
// 函数：构造处理
void create()
{
	restore();
	set_name("Thiên Sứ Trao Đổi");

	set_2("talk", (["bonus":(
								: do_bonus:),
					  "tiger":(
								  : do_tiger_bonus:),
	]));
	//	iStart_n = mktime(2007,9,27,11,0,0);
	//	iFinish_n = mktime(2007,10,8,0,0,0);
	setup();
}

void do_look(object who)
{
	__FILE__->do_look_2(who, this_object());
}

void do_look_2(object who, object me)
{
	int id, iTime;
	string tiger_str = "", national = "", ssss, national2 = "";
	id = getoid(me);
	iTime = get_party_time();
	if (GUESS_TRUE_TIGER->is_active_open())
	{
		tiger_str = sprintf(ESC "Thật Giả Hổ Vương \ntalk %x# tiger.1\n", id);
	}
	ssss = " :\n Bạn có ý kiến nào thú vị đều có thể giao cho tôi để đổi lấy phần thưởng! Phần thưởng ở chỗ tôi vô cùng phong phú và đa dạng!\n";

	if (iTime < iFinish_n && iTime > iStart_n)
	{
		national2 = sprintf(ESC HIY "Mua Đại Lễ Bao Quốc Khánh \ntalk %x# bonus.43\n", id);
		national = sprintf(ESC HIY "Nhận Đại Lễ Bao của Tinh Linh Mèo \ntalk %x# bonus.34\n" ESC HIY "Nhận Đại Lễ Bao Trường Lưới \ntalk %x# bonus.34\n" ESC HIY "Nhận túi quà tân thủ \ntalk %x# bonus.34\n", id, id, id);
		//		national += sprintf(ESC"Nhận quà tu vị \ntalk %x# bonus.36\n",id);
	}

	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
			  "" + me->get_name() + ssss + tiger_str + national + national2 + sprintf(ESC "Quả bóng bốn màu\ntalk %x# bonus.1\n" ESC "Đổi danh hiệu Hoàng Kim Thánh Y\ntalk %x# bonus.32\n" ESC "Kiểm tra điểm số tích lũy nhiệm vụ của tôi\ntalk %x# bonus.33\n" ESC "Rời khỏi", id, id, id));
}

//	真假虎王活动奖励领取
void do_tiger_bonus(string arg)
{
	__FILE__->do_tiger_bonus_reflash(this_object(), arg);
}

//	真假虎王活动的领取，在线更新
void do_tiger_bonus_reflash(object me, string arg)
{
	object who;
	string say_word;
	string *active_bonus;
	int level, flag, id;
	who = this_player();
	id = getoid(me);
	flag = to_int(arg);
	level = who->get_save("guess_true_tiger");
	if (who->get_save("guess_true_tiger_fight"))
	{
		GUESS_TRUE_TIGER->delete_tigers_on_player(who);
		who->delete_save("guess_true_tiger");
		level = 0;
	}
	switch (flag)
	{
	case 1:
		if (level > 0)
		{
			if (level >= 6)
			{
				say_word = "Ngươi quá lợi hại, đã qua được 6 ải, nhận được 1.000.000 ngân lượng thêm vô vàn phần thưởng phong phú!";
			}
			else
			{
				active_bonus = GUESS_TRUE_TIGER->get_active_bonus(level);
				if (level > 1)
				{
					say_word = sprintf("Ngươi đã vượt qua %d ải, nhận được %s Ngân Lượng cùng " HIR "%s" NOR " Phần Thưởng Danh Hiệu.", level, active_bonus[2], active_bonus[1]);
				}
				else
				{
					say_word = sprintf("Ngươi hết thảy qua %d Quan, có thể nhận lấy" HIR "%s" NOR " Phần Thưởng Danh Hiệu.", level, active_bonus[1]);
				}
			}
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n%s\n" ESC "Nhận lấy phần thưởng \ntalk %x# tiger.2\n" ESC "Rời khỏi", me->get_name(), say_word, id));
		}
		else
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n Sao ngươi không thử vượt ải?\n" ESC "Rời khỏi", me->get_name()));
		}
		break;
	case 2:
		if (level > 0)
		{
			active_bonus = GUESS_TRUE_TIGER->get_active_bonus(level);
			who->add_cashkhoa(to_int(replace_string(active_bonus[2], ",", "")));
			log_file("guess_true_tiger.txt", sprintf("%s : %s (%d) đã nhận %s Ngân Lượng\n", short_time(time()), who->get_name(), who->get_number(), active_bonus[2]));
			if (level > 1)
			{
				send_user(who, "%c%s", '!', sprintf("Tiền tài của ngươi tăng lên %s ngân lượng.", active_bonus[2]));
			}
			who->delete_save("guess_true_tiger");
			if (who->have_title(active_bonus[0]))
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Ngươi đã có danh hiệu này!\n" ESC "Rời khỏi", me->get_name()));
				return;
			}
			who->add_title(active_bonus[0]);
			who->show_title(active_bonus[0]);
			send_user(who, "%c%s", ';', sprintf(HIY "Ngươi đã đổi danh hiệu  %s.", who->get_title()));
		}
		break;
	}
}

void do_bonus(string arg)
{
	__FILE__->do_bonus_2(this_object(), arg);
}

void do_bonus_2(object me, string arg)
{
	int flag, p, iTime, i, j, size, id, x, y, z, level, rate, amount, count;
	object who, item, *nTeam, member, npc, map, item_q, item_q2, item_q3, item_q4, *inv, *inv2;
	string name, *nTmp, tmp, result = "", result2 = "", cTmp, national2, ssss;
	string result_key = "", *key = ({});
	mixed *mxTime;
	int *armor = ({101, 102, 104, 105, 106});
	iTime = get_party_time();

	if (MAIN_D->get_host_type() == 2)
		return;

	who = this_player();
	flag = to_int(arg);
	who->set_time("talk", 0);
	id = getoid(me);

	switch (flag)
	{
	case 1:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Gần đây quái vật thường xuyên chiếm lấy ruộng đất của dân để làm sânđá bóng, làm sao chúng ta có thể đứng nhìn đây ! rất nhiều quái vật mang theorất nhiều loại cầu, nếu chúng ta có thể chiếm lấy cầu của đám quái này sẽ cóthể gìn giữ sân vườn của dân chúng, nếu bạn có Hắc Cầu, Lam Cầu, Hồng Cầu,Hoa Cầu có thể đến chỗ ta đổi thưởng !!\n" ESC "Hắc Cầu đổi giải thưởng ngẫu nhiên\ntalk%x# bonus.2\n" ESC "Lam Cầu đổi giải thưởng ngẫu nhiên\ntalk%x# bonus.7\n" ESC "Hồng Cầu đổi giải thưởng ngẫu nhiên\ntalk%x# bonus.12\n" ESC "Hoa Cầu đổi giải thưởng ngẫu nhiên\ntalk%x# bonus.17\n" ESC "Hắc Cầu + Lam Cầu đổi Tàng Bảo Đồ\ntalk%x# bonus.22\n" ESC "Hắc Cầu + Lam Cầu + Hồng Cầu đổi Tử SâmĐơn\ntalk %x# bonus.24\n" ESC "Hắc Cầu + Lam Cầu + Hồng Cầu + Hoa Cầuđổi trang bị Hoàng Kim\ntalk %x# bonus.26\n" ESC "Hắc Cầu + Lam Cầu đổi phần thưởng ngẫunhiên\ntalk %x# bonus.28\n" ESC "Hắc Cầu + Lam Cầu + Hồng Cầu đổi phầnthưởng ngẫu nhiên\ntalk %x# bonus.30\n" ESC "Trở Về", me->get_name(), id, id, id, id, id, id, id, id, id));
		break;
	case 2:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Bạn có thể dùng Hắc Cầu đổi thưởng : \n" ESC "Một Hắc Cầu đổi 5 Hồi Bang Phù\ntalk %x#bonus.3\n" ESC "Một Hắc Cầu đổi 10 Phi Hành Phù\ntalk %x#bonus.5\n" ESC "Rời khỏi", me->get_name(), id, id));
		break;
	case 3:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Xác nhận muốn đổi 1 Hắc Cầu lấy 5 Hồi Bang Phù phải không ?\n" ESC "Xác nhận\ntalk %x# bonus.4\n" ESC "Rời khỏi", me->get_name(), id));
		break;
	case 4:
		if (!objectp(item_q = present("Hắc Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Hành trang không đủ chỗ, vui lòng thu dọn lại hành trang !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		item_q->add_amount(-1);
		item = new ("item/std/0410"); //回帮符
		item->set_amount(5);
		p = item->move2(who, -1);
		item->add_to_user(p);
		send_user(who, "%c%s", ';', "Bạn dùng một Hắc Cầu đổi 5 Hồi Bang Phù");
		break;
	case 5:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Bạn muốn đổi một Hắc Cầu lấy 10 Phi Hành Phù phải không ?\n" ESC "Xác nhận\ntalk %x# bonus.6\n" ESC "Rời khỏi", me->get_name(), id));
		break;
	case 6:
		if (!objectp(item_q = present("Hắc Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Hành trang không đủ chỗ, vui lòng thu dọn lại hành trang !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		item_q->add_amount(-1);
		item = new ("item/std/0409"); //Phi Hành Phù
		item->set_amount(10);
		p = item->move2(who, -1);
		item->add_to_user(p);
		send_user(who, "%c%s", ';', "Bạn dùng một Hắc Cầu đổi 10 Phi Hành Phù");
		break;
	case 7:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Bạn có thể dùng Lam Cầu đổi thưởng : \n" ESC "Một Lam Cầu đổi Tàng Bảo Đồ\ntalk %x#bonus.8\n" ESC "Một Lam Cầu đổi 10 Hạt Lạc Hoàn\ntalk %x#bonus.10\n" ESC "Rời khỏi", me->get_name(), id, id));
		break;
	case 8:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Bạn muốn dùng một Lam Cầu đổi Tàng Bảo Đồ phải không ?\n" ESC "Xác nhận\ntalk %x# bonus.9\n" ESC "Rời khỏi", me->get_name(), id));
		break;
	case 9:
		if (!objectp(item_q = present("Lam Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Hành trang không đủ chỗ, vui lòng thu dọn lại hành trang !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		item_q->add_amount(-1);
		item = new ("item/std/8000"); //Tàng Bảo Đồ
		p = item->move2(who, -1);
		item->add_to_user(p);
		send_user(who, "%c%s", ';', "Bạn dùng một Lam Cầu đổi Tàng Bảo Đồ");
		break;
	case 10:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Bạn muốn dùng một Lam Cầu đổi 10 Hạc Lạc Hoàn không ?\n" ESC "Xác nhận\ntalk %x# bonus.11\n" ESC "Rời khỏi", me->get_name(), id));
		break;
	case 11:
		if (!objectp(item_q = present("Lam Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Hành trang không đủ chỗ, vui lòng thu dọn lại hành trang !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		item_q->add_amount(-1);
		item = new ("item/91/9101"); //活络丸
		item->set_amount(10);
		p = item->move2(who, -1);
		item->add_to_user(p);
		send_user(who, "%c%s", ';', "Bạn dùng một Lam Cầu đổi 10 Hạc Lạc Hoàn");
		break;
	case 12:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Bạn có thể dùng một Hồng Cầu để đổi thưởng :\n" ESC "Trong 1 giờ gia tăng tối đa 200 điểm KhíHuyết\ntalk %x# bonus.13\n" ESC "Trong 1 giờ gia tăng tối đa 200 điểm PhápLực\ntalk %x# bonus.15\n" ESC "Rời khỏi", me->get_name(), id, id));
		break;
	case 13:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Bạn muốn trong 1 giờ gia tăng 200 điểm Khí Huyết phải không ?\n" ESC "Xác nhận\ntalk %x# bonus.14\n" ESC "Rời khỏi", me->get_name(), id));
		break;
	case 14:
		if (!objectp(item_q = present("Hồng Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (get_effect(who, EFFECT_USER_EXCHANGE_HP))
		{
			send_user(who, "%c%s", ';', "Tạm thời bạn đã có hiệu lực");
			return;
		}
		item_q->add_amount(-1);
		set_effect(who, EFFECT_USER_EXCHANGE_HP, 3600); //+HP
		USER_ENERGY_D->count_max_hp(who);
		send_user(who, "%c%w%w%c", 0x81, 0443, 3600, EFFECT_GOOD);
		send_user(who, "%c%s", ';', "Bạn dùng một Hồng Cầu đổi Gia tăng 200điểm Khí Huyết trong 1 giờ");
		break;
	case 15:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Bạn muốn trong 1 giò gia tăng 200 điểm Pháp Lực phải không ?\n" ESC "Xác nhận\ntalk %x# bonus.16\n" ESC "Rời khỏi", me->get_name(), id));
		break;
	case 16:
		if (!objectp(item_q = present("Hồng Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (get_effect(who, EFFECT_USER_EXCHANGE_MP))
		{
			send_user(who, "%c%s", ';', "Tạm thời bạn đã có hiệu lực");
			return;
		}
		item_q->add_amount(-1);
		set_effect(who, EFFECT_USER_EXCHANGE_MP, 3600); //+MP
		USER_ENERGY_D->count_max_mp(who);
		send_user(who, "%c%w%w%c", 0x81, 0444, 3600, EFFECT_GOOD);
		send_user(who, "%c%s", ';', "Bạn dùng một Hồng Cầu đổi Gia tăng 200điểm Pháp Lực trong 1 giờ");
		break;
	case 17:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Bạn có thể dùng một Hoa Cầu đổi thưởng :\n" ESC "Trong một giờ gia tăng 100 điểm NgoạiCông\ntalk %x# bonus.18\n" ESC "Trong một giờ gia tăng 100 điểm NộiCông\ntalk %x# bonus.20\n" ESC "Rời khỏi", me->get_name(), id, id));
		break;
	case 18:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Bạn muốn trong một giờ gia tăng 100 điểm Ngoại Công phải không ?\n" ESC "Xác nhận\ntalk %x# bonus.19\n" ESC "Rời khỏi", me->get_name(), id));
		break;
	case 19:
		if (!objectp(item_q = present("Hoa Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (get_effect(who, EFFECT_USER_EXCHANGE_AP))
		{
			send_user(who, "%c%s", ';', "Tạm thời bạn đã có hiệu lực");
			return;
		}
		item_q->add_amount(-1);
		set_effect(who, EFFECT_USER_EXCHANGE_AP, 3600); //+AP
		USER_ENERGY_D->count_ap(who);
		send_user(who, "%c%w%w%c", 0x81, 0445, 3600, EFFECT_GOOD);
		send_user(who, "%c%s", ';', "Bạn dùng Hoa Cầu đổi Gia tăng 100 điểmNgoại Công trong 1 giờ");
		break;
	case 20:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Bạn muốn dùng một Hoa Cầu gia tăng 100 điểm Nội Công phải không ?\n" ESC "Xác nhận\ntalk %x# bonus.21\n" ESC "Rời khỏi", me->get_name(), id));
		break;
	case 21:
		if (!objectp(item_q = present("Hoa Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (get_effect(who, EFFECT_USER_EXCHANGE_CP))
		{
			send_user(who, "%c%s", ';', "Tạm thời bạn đã có hiệu lực");
			return;
		}
		item_q->add_amount(-1);
		set_effect(who, EFFECT_USER_EXCHANGE_CP, 3600); //+CP
		USER_ENERGY_D->count_cp(who);
		send_user(who, "%c%w%w%c", 0x81, 0446, 3600, EFFECT_GOOD);
		send_user(who, "%c%s", ';', "Bạn dùng Hoa Cầu đổi Gia tăng Nội Công100 điểm trong 1 giờ");
		break;
	case 22:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Bạn muốn đổi một Hắc Cầu và một Lam Cầu đổi 2 Tàng Bảo Đồ phải không?\n" ESC "Xác nhận\ntalk %x# bonus.23\n" ESC "Rời khỏi", me->get_name(), id));
		break;
	case 23:
		if (!objectp(item_q = present("Lam Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (!objectp(item_q2 = present("Hắc Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 2)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Hành trang không đủ chỗ, vui lòng thu dọn lại hành trang !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		item_q->add_amount(-1);
		item_q2->add_amount(-1);
		item = new ("item/std/8000"); //Tàng Bảo Đồ
		p = item->move2(who, -1);
		item->add_to_user(p);
		item = new ("item/std/8000"); //Tàng Bảo Đồ
		p = item->move2(who, -1);
		item->add_to_user(p);
		send_user(who, "%c%s", ';', "Bạn đổi Hắc Cầu và Lam Cầu lấy 2 Tàng BảoĐồ");
		break;
	case 24:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Bạn muốn đổi một Hắc Cầu một Lam Cầu môt Hồng Cầu đổi Tử Sâm Đơn phảikhông ?\n" ESC "Xác nhận\ntalk %x# bonus.25\n" ESC "Rời khỏi", me->get_name(), id));
		break;
	case 25:
		if (!objectp(item_q = present("Lam Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (!objectp(item_q2 = present("Hắc Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (!objectp(item_q3 = present("Hồng Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Hành trang không đủ chỗ, vui lòng thu dọn lại hành trang !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		item_q->add_amount(-1);
		item_q2->add_amount(-1);
		item_q3->add_amount(-1);
		item = new ("item/91/9167"); //紫参丹
		p = item->move2(who, -1);
		item->add_to_user(p);
		send_user(who, "%c%s", ';', "Bạn đổi một Hồng Cầu một Lam Cầu một HắcCầu lấy Tử Sâm Đơn");
		CHAT_D->sys_channel(0, CHAT + sprintf("Chúc mừng " HIR "%s" NOR " nhận được phẩn thưởng " HIR "%s", who->get_name(), item->get_name()));
		break;
	case 26:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Bạn muốn dùng một Lam Cầu một Hắc Cầu một Hồng Cầu một Hoa Cầu đổitrang bị Hoàng Kim phải không ?\n" ESC "Xác nhận\ntalk %x# bonus.27\n" ESC "Rời khỏi", me->get_name(), id));
		break;
	case 27:
		if (!objectp(item_q = present("Lam Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (!objectp(item_q2 = present("Hắc Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (!objectp(item_q3 = present("Hồng Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (!objectp(item_q4 = present("Hoa Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Hành trang không đủ chỗ, vui lòng thu dọn lại hành trang !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		item_q->add_amount(-1);
		item_q2->add_amount(-1);
		item_q3->add_amount(-1);
		item_q4->add_amount(-1);
		level = who->get_level();
		if (level > 120)
			level = 120;
		if (level > 50 && who->get_fam_name() == "")
			level = 50;
		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(), who->get_gender(), level, armor[random(5)]);
		tmp = nTmp[random(sizeof(nTmp))];
		if (!stringp(tmp))
			return;
		item = new (tmp);
		item->set_record(1);
		ITEM_EQUIP_D->init_equip_prop_3(item);
		if (item->get_item_color() != 2)
		{
			item->set_item_color(2);
			item->set_bind(1);
		}
		p = item->move2(who, -1);
		item->add_to_user(p);
		send_user(who, "%c%s", ';', sprintf("Bạn dùng Lam Cầu, Hắc Cầu, Hồng Cầu, HoaCầu đổi trang bị Hoàng Kim: %s", item->get_name()));
		CHAT_D->sys_channel(0, CHAT + sprintf("Chúc mừng " HIR "%s" NOR " nhận được phần thưởng " HIR "%s", who->get_name(), item->get_name()));
		break;
	case 28:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Bạn muốn dùng một Hắc Cầu một Lam Cầu đổi phần thưởng ngẫu nhiên phảikhông ?\n" ESC "Xác nhận\ntalk %x# bonus.29\n" ESC "Rời khỏi", me->get_name(), id));
		break;
	case 29:
		if (!objectp(item_q = present("Lam Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (!objectp(item_q2 = present("Hắc Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Hành trang không đủ chỗ, vui lòng thu dọn lại hành trang !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		item_q->add_amount(-1);
		item_q2->add_amount(-1);

		rate = random(10000);
		if (rate < 3000)
		{
			amount = 5000 + random(10001);
			who->add_cash(amount);
			result = result + sprintf(HIR "%d lượng", amount);
		}
		else if (rate >= 3000 && rate < 6000)
		{
			amount = 5000 + random(5001);
			who->add_exp(amount);
			result = result + sprintf(HIR "%d kinh nghiệm", amount);
		}
		else if (rate >= 6000 && rate < 9000)
		{
			amount = 100 + random(200);
			who->add_potential(amount);
			result = result + sprintf(HIR "%d tiềm năng", amount);
		}
		else if (rate >= 9000 && rate < 9300)
		{
			item = new ("item/std/6003"); //麻布包裹
			result = result + sprintf(HIR "%s", item->get_name());
		}
		else if (rate >= 9300 && rate < 9600)
		{
			item = new ("item/44/4488"); //随机宠物技能丹
			result = result + sprintf(HIR "%s", item->get_name());
		}
		else if (rate >= 9600 && rate < 9800)
		{
			item = new ("item/91/9125"); //再造丸
			result = result + sprintf(HIR "%s", item->get_name());
			result2 = result2 + sprintf(HIR "%s", item->get_name());
		}
		else if (rate >= 9800 && rate < 9900)
		{
			item = new ("item/91/9160"); //气脉丹
			result = result + sprintf(HIR "%s", item->get_name());
			result2 = result2 + sprintf(HIR "%s", item->get_name());
		}
		else if (rate >= 9900 && rate < 10000)
		{
			item = new ("item/91/9161"); //周天丹
			result = result + sprintf(HIR "%s", item->get_name());
			result2 = result2 + sprintf(HIR "%s", item->get_name());
		}
		if (item)
		{
			p = item->move2(who, -1);
			item->add_to_user(p);
		}
		send_user(who, "%c%s", ';', sprintf("Bạn dùng một Hắc Cầu một Lam Cầu đổi %s", result));
		if (result2 != "")
			CHAT_D->sys_channel(0, CHAT + sprintf("Chúc mừng " HIR "%s" NOR " nhận được phần thưởng " HIR "%s", who->get_name(), result2));
		break;
	case 30:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Bạn muốn dùng một Lam Cầu, một Hắc Cầu, một Hồng Cầu đổi phần thưởngngẫu nhiên phải không ?\n" ESC "Xác nhận\ntalk %x# bonus.31\n" ESC "Rời khỏi", me->get_name(), id));
		break;
	case 31:
		if (!objectp(item_q = present("Lam Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (!objectp(item_q2 = present("Hắc Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (!objectp(item_q3 = present("Hồng Cầu", who, 1, MAX_CARRY)))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người không có Cầu, hãy thu thập rồi lại đến đổi thưởng !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Hành trang không đủ chỗ, vui lòng thu dọn lại hành trang !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		item_q->add_amount(-1);
		item_q2->add_amount(-1);
		item_q3->add_amount(-1);

		rate = random(10000);
		if (rate < 3600)
		{
			cTmp = BOOK_FILE->get_book_file();
			item = new (cTmp); //随机门派技能进阶书
			result = result + sprintf(HIR "%s", item->get_name());
		}
		else if (rate >= 3600 && rate < 5000)
		{
			item = new ("item/91/9167"); //紫参丹
			result = result + sprintf(HIR "%s", item->get_name());
		}
		else if (rate >= 5000 && rate < 6100)
		{
			item = new ("item/91/9162"); //逍遥散
			result = result + sprintf(HIR "%s", item->get_name());
		}
		else if (rate >= 6100 && rate < 7200)
		{
			item = new ("item/91/9163"); //金桑散
			result = result + sprintf(HIR "%s", item->get_name());
		}
		else if (rate >= 7200 && rate < 8300)
		{
			item = new ("item/91/9164"); //紫心丹
			result = result + sprintf(HIR "%s", item->get_name());
		}
		else if (rate >= 8300 && rate < 9400)
		{
			item = new ("item/91/9165"); //归元丹
			result = result + sprintf(HIR "%s", item->get_name());
		}
		else if (rate >= 9400 && rate < 10000)
		{
			level = who->get_level();
			if (level > 120)
				level = 120;
			if (level > 50 && who->get_fam_name() == "")
				level = 50;
			nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(), who->get_gender(), level, armor[random(5)]);
			tmp = nTmp[random(sizeof(nTmp))];
			if (!stringp(tmp))
				return;
			item = new (tmp);
			item->set_record(1);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			if (item->get_item_color() != 2)
			{
				item->set_item_color(2);
				item->set_bind(1);
			}
		}
		p = item->move2(who, -1);
		item->add_to_user(p);
		send_user(who, "%c%s", ';', sprintf("Bạn dùng một Lam Cầu, một Hắc Cầu, mộtHồng Cầu đổi %s", item->get_name()));
		CHAT_D->sys_channel(0, CHAT + sprintf("Chúc mừng " HIR "%s" NOR " nhận được phần thưởng " HIR "%s", who->get_name(), item->get_name()));
		//		USER_D->user_channel(result);
		break;
	case 32:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s:\n Số lần của nhiệm vụ càng nhiều, bạn càng có thể đổi lấy danh hiệu càng cao.\n" ESC "5 lần nhiệm vụ đổi lấy danh hiệu ThanhĐồng Thánh Đấu Sĩ\ntalk %x# bonus.1005\n" ESC "10 lần nhiệm vụ đổi lấy danh hiệu BạchNgân Thánh Đấu Sĩ\ntalk %x# bonus.1010\n" ESC "50 lần nhiệm vụ đổi lấy danh hiệu HoàngKim Thánh Đấu Sĩ\ntalk %x# bonus.1050\n" ESC "100 lần nhiệm vụ đổi lấy danh hiệu HắcÁm Thánh Đấu Sĩ\ntalk %x# bonus.1100\n" ESC "Rời khỏi", me->get_name(), id, id, id, id, ));
		break;
	case 33:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s:\n Điểm tích lũy nhiệm vụ của bạn là %d điểm.\n" ESC "Rời khỏi", me->get_name(), who->get_save("warrior_title")));
		break;
	case 34:
		if (who->get_level() >= 40 || who->get_level() < 10)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Phần thưởng lần này chỉ đặc biệt tặng cho tân thủ, bởi vậy chỉ có" HIR "Người chơi 10 Cấp ~39 Cấp" NOR "mới có thể nhận lấy những phần thưởng này.\n" ESC "Rời khỏi\n", me->get_name()));
			return;
		}
		if (who->get_save("wg_national_new"))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Làm sao? Hiệu quả của tinh thạch không tồi ~ Vũ khí sau khi tinh luyện thì khi tiêu diệt quái vật hiệu quả nhất định sẽ cao hơn.\n" ESC "Rời khỏi\n", me->get_name()));
			return;
		}
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Đã tới cấp 10, sẽ có những yêu cầu khác biệt về vũ khí, ta quyết định đưa ngươi 4 viên có thể tăng thêm thuộc tính cho vũ khí trang bị" HIR "Tinh thạch" NOR "Nếu như bạn tinh luyện 2 linh thạch có cùng thuộc tính vào vũ khí hoặc áo giáp theo thứ tự từ thấp đến cao, bạn sẽ thấy sức mạnh của chúng được nâng cao hơn rất nhiều ~ Hãy nhớ rằng, những linh thạch này" HIR "Chỉ trang bị" NOR "từ cấp 20 trở xuống.\n    Ngoại trừ những này tinh thạch, Song Ngư tiểu thư sẽ bầu bạn với ngươi.\n" ESC "Nhận lấy \ntalk %x# bonus.35\n", me->get_name(), id));
		break;
	case 35:
		if (iTime < iFinish_n && iTime > iStart_n && !who->get_save("wg_national_new") && who->get_level() < 40 && who->get_level() >= 10)
		{
			if (USER_INVENTORY_D->count_empty_carry(who) < 5)
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Trên người ngươi không có đủ chỗ trống, yêu cầu dọn dẹp hành trang ~\n" ESC "Rời khỏi", me->get_name()));
				return;
			}
			item = new ("item/08/0831"); //双鱼宠物
			p = item->move2(who, -1);
			item->add_to_user(p);
			item = new ("item/93/9343"); //新手土晶石
			p = item->move2(who, -1);
			item->add_to_user(p);
			item = new ("item/93/9345"); //新手火晶石
			p = item->move2(who, -1);
			item->add_to_user(p);
			item = new ("item/93/9343"); //新手土晶石
			item->set_level(2);
			p = item->move2(who, -1);
			item->add_to_user(p);
			item = new ("item/93/9345"); //新手火晶石
			item->set_level(2);
			p = item->move2(who, -1);
			item->add_to_user(p);
			who->set_save("wg_national_new", 1);
			send_user(who, "%c%s", ';', "Ngài nhận lấy bốn viên tinh thạch cùng một Sủng Vật Song Ngư");
		}
		break;
		//        case 36:
		//		if (who->get_save_2("online_rank.level")<27 )
		//		{
		//			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s: \n   Tu vị của ngài đẳng cấp chưa đủ 27 Cấp, đạt tới 27 Cấp hẵng đến nhận.\n"ESC"Rời khỏi\n",me->get_name()));
		//			return;
		//		}
		//		if (who->get_save("wg_national_new"))
		//		{
		//			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s: \n   Ngài đã từng nhận Sủng Vật Song Ngư \n"ESC"Rời khỏi\n",me->get_name()));
		//			return;
		//		}
		//		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s: \n   Để đáp lễ những người chơi đã ủng hộ, chỉ cần tu vị đẳng cấp đạt đến 27 Cấp, có thể tới chỗ ta nhận lấy một con Sủng Vật Song Ngư.\n"ESC"Nhận lấy \ntalk %x# bonus.37\n",me->get_name(),id));
		//        	break;
		//        case 37:
		//		if( iTime<iFinish_n && iTime>iStart_n && !who->get_save("wg_national_new") && who->get_save_2("online_rank.level")>=27 )
		//		{
		//			if(USER_INVENTORY_D->count_empty_carry(who) < 1 )
		//			{
		//				send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s: \n   Trên người ngươi không có đủ chỗ trống, yêu cầu dọn dẹp hành trang ~\n"ESC"Rời khỏi",me->get_name()));
		//		    		return;
		//			}
		//			item = new ("item/08/0831");//双鱼宠物
		//			p = item->move2(who,-1);
		//			item->add_to_user(p);
		//			who->set_save("wg_national_new",1);
		//			send_user(who, "%c%s", ';', "Ngài nhận lấy một cái Sủng Vật Song Ngư");
		//		}
		//        	break;
	case 38:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n    Đại lễ bao bao gồm các vật phẩm: 1 Can Tương Bảo Thạch, 1 Thẻ Niên Thú, 1 Lỗ Ban Bảo Thạch, 1 chìa khoá tử kim, 1 Mãn thiên quá hải phù, 1 Bảo Đề Phù, 1 Chiến Quốc Lệnh, 1 Chi Ma Khai Môn, 1 Tế thế bảo ngọc, 1 Thượng Phương Bảo Kiếm, 1 Nhân Sâm Vương, 1 cuốn cẩm nang và 1 ma lực chùy, còn có 1 bao lì xì 200 nguyên bảo, ta lấy ngươi 390 Nguyên Bảo thôi, xác nhận chứ?\n" ESC "Quả nhiên là vật phâm quý, ta phải mua ngay \ntalk %x# bonus.42\n" ESC "Để ta suy nghĩ thêm", me->get_name(), id));
		break;
	case 39:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Tất cả vật phẩm trong gói quà này đều không khóa, có thể tặng bằng hữu, để ngươi cùng bằng hữu có thể vui vẻ đón Quốc Khánh. Đồng thời cũng có thể giao dịch. Bởi vì là rất trân quý lễ vật, cho nên sẽ chỉ ở trong lúc Quốc Khánh mới được bán.\n" ESC "Ta hiểu rồi", me->get_name()));
		break;
	case 40:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n    Đại lễ bao bao gồm các vật phẩm: 1 Can Tương Bảo Thạch, 1 Thẻ Niên Thú, 1 Lỗ Ban Bảo Thạch, 1 chìa khoá tử kim, 1 Mãn thiên quá hải phù, 1 Bảo Đề Phù, 1 Chiến Quốc Lệnh, 1 Chi Ma Khai Môn, 1 Tế thế bảo ngọc, 1 Thượng Phương Bảo Kiếm, 1 Nhân Sâm Vương, 1 cuốn cẩm nang và 1 ma lực chùy, còn có 1 bao lì xì 200 nguyên bảo.\n" ESC "Xem ra lễ vật rất phong phú", me->get_name()));
		break;
	case 41:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Tốt, nhưng những món quà này chỉ bán vào dịp Quốc Khánh, bỏ qua thì thật là đáng tiếc. Có muốn ta giữ lại cho ngươi 1 món hay không? hehe!\n" ESC "Rời khỏi", me->get_name()));
		break;
	case 42:
		if (who->get_pay_money_buy_item() > 0)
		{
			send_user(who, "%c%s", '!', "Yêu cầu của ngài đang được xử lý, xin hãy chờ đợi.");
			return;
		}
		who->set_pay_money_buy_item(1); // 查询余额
		who->set_pay_type(8);
		who->set_buy_item_cmd_string(sprintf("%x# bonus", getoid(me)));
		db_user_pay(who, sprintf("%s:80\n"
								 "GET http:/"
								 "/%s/querybalance.php?t=%s&u=%d\r\n",
								 MAIN_D->get_php_ip(),
								 MAIN_D->get_php_ip(), short_time_2(), who->get_acountid()));
		break;
	case 43:
		ssss = ":\n    Thu sắc tiệm nồng, hỷ khánh tiệm hiện. Trung thu ngọt ngào vừa trôi qua, Quốc Khánh lại từ từ tiến tới. Khắp chốn mừng vui, thế giới Chiến Quốc quả thực vô cùng nhộn nhịp. Vì cái gì đây? Cũng bởi vì trong tay ta có Đại Lễ Bao Phong Cuồng Quốc Khánh! Đang là thời gian ưu đãi, mỗi bộ Đại Lễ Bao chỉ bán với giá 390 Nguyên bảo. Hây hây hây, không nên chen lấn, xếp hàng từng người từng người thôi.\n";
		national2 = sprintf(ESC HIY "Nhanh tay nào, lập tức mua \ntalk %x# bonus.38\n" ESC "Ta muốn hiểu rõ hơn \ntalk %x# bonus.39\n" ESC "Ta muốn thấy bên trong gói quà có thứ gì \ntalk %x# bonus.40\n" ESC "Đợi ta nạp thẻ \ntalk %x# bonus.41\n", id, id, id, id);
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:" + ssss + national2 + ESC "Rời khỏi", me->get_name()));
		break;

	case 1005:
	case 1010:
	case 1050:
	case 1100:
		count = flag - 1000;
		if (count == 5)
			tmp = "A009";
		else if (count == 10)
			tmp = "A010";
		else if (count == 50)
			tmp = "A011";
		else if (count == 100)
			tmp = "A012";
		if (who->have_title(tmp))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Bạn đã có danh hiệu này !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		amount = who->get_save("warrior_title");
		if (amount < count)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \n   Điểm tích luỹ không đủ để đổi danh hiệu !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		who->add_save("warrior_title", -count);
		who->add_title(tmp);
		who->show_title(tmp);
		send_user(who, "%c%s", ';', sprintf(HIY "Bạn đổi thành công danh hiệu %s ", who->get_title()));
		break;
	}
}

// 函数：获取描述(持续)
string get_loop_desc1(object me)
{
	return "Trong 1 giờ gia tăng 200 điểm Khí Huyết\n";
}

string get_loop_desc2(object me)
{
	return "Trong 1 giờ gia tăng 200 điểm Pháp Lực\n";
}

string get_loop_desc3(object me)
{
	return "Trong 1 giờ gia tăng 100 điểm NgoạiCông\n";
}

string get_loop_desc4(object me)
{
	return "Trong 1 giờ gia tăng 100 điểm Nội Công\n";
}

//开启任务
void set_open(object who, string arg)
{
	int year, mon, day, hour, min;
	string cTmp1, cTmp2;
	if (sscanf(arg, "%s-%s", cTmp1, cTmp2) != 2)
	{
		send_user(who, "%c%s", '!', "Cách thức sai!");
		return 0;
	}
	//20070518 2000
	year = to_int(cTmp1[0..3]);
	mon = to_int(cTmp1[4..5]);
	day = to_int(cTmp1[6..7]);
	hour = to_int(cTmp1[8..9]);
	min = to_int(cTmp1[10..11]);
	iStart_n = mktime(year, mon, day, hour, min, 0); //活动开始时间

	year = to_int(cTmp2[0..3]);
	mon = to_int(cTmp2[4..5]);
	day = to_int(cTmp2[6..7]);
	hour = to_int(cTmp2[8..9]);
	min = to_int(cTmp2[10..11]);
	iFinish_n = mktime(year, mon, day, hour, min, 0); //结束时间

	if (!iStart_n || !iFinish_n)
	{
		send_user(who, "%c%s", '!', "Thời gian sai!");
		return 0;
	}
	if (iStart_n > iFinish_n || iFinish_n < time())
	{
		send_user(who, "%c%s", '!', "Thời gian sai!!");
		return 0;
	}
	tell_user(who, "Hoạt động lễ vật Quốc Khánh mở ra: %s!", arg);
	send_user(who, "%c%s", '!', "Hoạt động lễ vật Quốc Khánh mở ra!");
	save();
}

//关闭任务
void set_close(object who)
{
	iStart_n = 0;
	iFinish_n = 0;
	send_user(who, "%c%s", '!', "Hoạt động lễ vật Quốc Khánh đóng lại!");
	save();
}
//是否开启活动。
int is_open()
{
	int iHour = time();
	if (!iStart_n || !iFinish_n)
	{
		return 0;
	}
	if (iHour >= iStart_n && iHour < iFinish_n)
	{
		return 1;
	}
	else if (iHour >= iFinish_n)
	{
		return 0;
	}
}