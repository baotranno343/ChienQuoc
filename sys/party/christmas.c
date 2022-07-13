/*****************************
	**giáng sinh**
*****************************/

#include <time.h>
#include <ansi.h>
#include <cmd.h>
#define SANTACLAUS "npc/party/santaclaus"
#define TURKEY "item/04/0413"
#define SANTANBADMAN "npc/party/0012"

int *nScene = ({1, 10, 20, 30, 40, 50, 60, 70});
int iStart, iFinish;
object SantaClaus, SantaBear, SantaGuan, SantaFeizei;
mapping mpTree1 = ([1:({
						  ({53, 144}),
					  }),
				   80:({
						  ({292, 183}),
					  }),
]);
mapping mpTree2 = ([1:({
						  ({193, 148}),
						  ({146, 153}),
						  ({182, 153}),
					  }),
				   10:({({130, 113}), ({135, 117}), ({139, 198}), ({143, 195})}),
				   20:({
						  ({228, 84}),
						  ({167, 87}),
						  ({172, 93}),
						  ({230, 93}),
					  }),
				   30:({
						  ({191, 80}),
						  ({173, 94}),
						  ({229, 96}),
						  ({202, 78}),
					  }),
				   40:({
						  ({270, 113}),
						  ({265, 117}),
						  ({258, 191}),
						  ({264, 196}),
					  }),
				   50:({
						  ({128, 114}),
						  ({134, 118}),
						  ({118, 172}),
					  }),
				   60:({
						  ({242, 169}),
						  ({247, 173}),
						  ({138, 184}),
						  ({133, 188}),
					  }),
				   70:({
						  ({181, 219}),
						  ({251, 187}),
						  ({217, 245}),
						  ({232, 217}),
					  }),
				   80:({
						  ({220, 49}),
						  ({189, 70}),
						  ({161, 75}),
						  ({214, 117}),
						  ({209, 121}),
						  ({323, 134}),
					  }),
				  289:({({49, 59}), ({66, 62})}),
				  165:({({90, 30}), ({110, 30})}),
				  269:({({253, 166}), ({265, 188})}),
				  273:({
						  ({185, 140}),
						  ({197, 155}),
						  ({216, 170}),
					  }),
				   54:({
						  ({140, 115}),
						  ({127, 126}),
						  ({114, 138}),
					  }),
				  324:({({99, 115}), ({119, 156})}),
				  886:({({112, 92}), ({136, 110})}),
]);

int SantaClausGift(object me, object who);
int check_turkey(object who, int count);
int give_turkey(object who, int count);
void generate_turkey();
void generate_badman();
void destroy_badman();
void generate_tree();

// 函数:生成二进制码
void SAVE_BINARY() {}

void create()
{
	iStart = mktime(2020, 11, 22, 0, 0, 0);
	iFinish = mktime(2020, 12, 30, 0, 0, 0);
}

void check_time()
{
	int iHour, p;
	mixed *mixTime;

	remove_call_out("check_time");
	iHour = time();
	if (iHour > iFinish)
		return;
	if (iHour < iStart)
	{
		call_out("check_time", iStart - iHour);
		return;
	}
	if (!objectp(SantaClaus))
	{
		SantaClaus = new (SANTACLAUS);
		SantaClaus->add_to_scene(80, 285, 176, 4);
	}
	if (!objectp(SantaBear))
	{
		SantaBear = new ("npc/party/santabear");
		SantaBear->add_to_scene(80, 287, 178, 4);
	}
	if (!objectp(SantaGuan))
	{
		SantaGuan = new ("npc/party/santaguan");
		SantaGuan->add_to_scene(80, 286, 179, 4);
	}
	if (!objectp(SantaFeizei))
	{
		SantaFeizei = new ("npc/party/santafeizei");
		SantaFeizei->add_to_scene(80, 288, 177, 4);
	}
	mixTime = localtime(time());
	iHour = mixTime[TIME_HOUR];
	if (mixTime[TIME_MIN] >= 30)
		call_out("check_time", 60 * (60 - mixTime[TIME_MIN]));
	else
		call_out("check_time", 60 * (30 - mixTime[TIME_MIN]));

	if (iHour >= 19) //放火鸡
	{
		if (SANTACLAUS->get("turkey") != time() / 1800)
		{
			SANTACLAUS->set("turkey", time() / 1800);
			generate_turkey();
		}
	}
	// Time xuất hiện
	if (iHour == 9 || iHour == 12 || iHour == 15 || iHour == 19 || iHour == 22) //刷新恶人
	{
		if (SANTACLAUS->get("banman") != iHour)
		{
			generate_badman();
			SANTACLAUS->set("banman", iHour);
		}
	}
	else if (iHour == 11 || iHour == 14 || iHour == 17 || iHour == 21 || iHour == 0)
	{
		destroy_badman();
	}
}

void before_destruct()
{
	int i, size;
	object *nObj;
	if (objectp(SantaClaus))
	{
		SantaClaus->remove_from_scene();
		destruct(SantaClaus);
	}
	if (objectp(SantaBear))
	{
		SantaBear->remove_from_scene();
		destruct(SantaBear);
	}
	if (objectp(SantaGuan))
	{
		SantaGuan->remove_from_scene();
		destruct(SantaGuan);
	}
	if (objectp(SantaFeizei))
	{
		SantaFeizei->remove_from_scene();
		destruct(SantaFeizei);
	}
	nObj = SANTACLAUS->get("tree");
	for (i = 0, size = sizeof(nObj); i < size; i++)
	{
		if (!objectp(nObj[i]))
			continue;
		nObj[i]->remove_from_scene();
		destruct(nObj[i]);
	}
}

void do_look(object me, object who)
{
	int id = getoid(me), i;
	i = time();
	//	if ( i >iStart && i < iFinish )
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n  Sự kiện Giáng Sinh hàng năm lại đến, tôi - ông già Noel đã chuẩn bị rất nhiều quà tặng cho các bạn.\nNếu bạn có Vớ hoặc Gà Tây có thể giao cho tôi để nhận phần quà Noel trong đêm Giáng Sinh ấm áp!\n" ESC "Giao nộp vớ\ntalk %x# welcome.1\n" ESC "Giao nộp gà tây\ntalk %x# welcome.2\n" ESC "Rời khỏi", me->get_name(), id, id));
}

void do_welcome(object me, string arg)
{
	int flag, i, rate, exp, money, pot;
	int id = getoid(me);
	object who, item, player, gift;
	string name, cTmp, id1;
	mixed *mixTime;
	who = this_player();
	if (sscanf(arg, "%d.%s", flag, id1) != 2)
		flag = to_int(arg);
	who->set_time("talk", 0);
	switch (flag)
	{
	case 1:
		if (!objectp(item = present("Vớ dài", who, 1, MAX_CARRY)) || item->is_christmas() != 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n Vớ noel của bạn đâu, ta chưa thấy !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		item->add_amount(-1);
		if (SantaClausGift(me, who) != 1)
			item->add_amount(1);
		break;
	case 2:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n Bạn có Gà tây Noel, có thể giao cho tôi để đổi phần quà giáng sinh !\n" ESC "Giao nộp 5 Gà tây Noel đổi quà\ntalk %x# welcome.3\n" ESC "Rời khỏi", me->get_name(), getoid(me)));
		break;
	case 3:
		if (check_turkey(who, 5) != 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n Bạn không có đủ 5 Gà tây Noel !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		if (TASK_LEGEND_D->can_carry_amount(who, 1) != 1)
			return;
		give_turkey(who, 5);
		SantaClausGift(me, who);
		break;
	case 4:
		if (time() > iFinish)
			return;
		if (time() < iStart)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n Cám ơn mọi người đã ủng hộ Chiến Quốc, ta sẽ rất nhớ mọi người.\n", me->get_name()));
			return;
		}
		if (who->get_save("20070104gift"))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n Bạn không thể quá tham lam, hãy chờ đợi cơ hội tiếp theo để nhận quà.\n", me->get_name()));
			return;
		}
		if (who->get_level() < 50)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n Cấp bậc của bạn chưa đạt 50 cấp.\n", me->get_name()));
			return;
		}
		if (TASK_LEGEND_D->can_carry_amount(who, 8) != 1)
			return;
		break;
		break;
	}
}
//检查火鸡数量
int check_turkey(object who, int count)
{
	int i, size, amount;
	object *inv, item;
	string name = "Thiệp Giáng Sinh Hỏa Kê";
	inv = all_inventory(who, 1, MAX_CARRY);

	if (!objectp(item = present(name, who, 1, MAX_CARRY)) || item->is_christmas() != 1)
	{
		return 0;
	}
	for (i = 0, size = sizeof(inv); i < size; i++)
	{
		if (!objectp(inv[i]))
			continue;
		if (inv[i]->get_name() != name || inv[i]->is_christmas() != 1)
			continue;
		if (inv[i]->is_combined())
			amount += inv[i]->get_amount();
		else
			amount++;
	}
	if (amount < count)
	{
		return 0;
	}
	return 1;
}
//给予火鸡
int give_turkey(object who, int count)
{
	int i, size, amount;
	object *inv, item;
	string name = "Thiệp Giáng Sinh Hỏa Kê";
	if (check_turkey(who, count) != 1)
		return 0;
	inv = all_inventory(who, 1, MAX_CARRY);
	for (i = 0, size = sizeof(inv); i < size; i++)
	{
		if (!objectp(inv[i]))
			continue;
		if (inv[i]->get_name() != name || inv[i]->is_christmas() != 1)
			continue;
		amount = inv[i]->get_amount();
		if (count >= amount)
		{
			inv[i]->remove_from_user();
			destruct(inv[i]);
			count -= amount;
		}
		else
		{
			inv[i]->add_amount(-count);
			count = 0;
		}
		if (count <= 0)
			break;
	}
	return 1;
}
//圣诞礼物
int SantaClausGift(object me, object who)
{
	int rate, p, exp, pot, money;
	object gift;
	string name;

	rate = random(10000);
	if (rate < 2000)
	{
		exp = 24000;
	}
	else if (rate < 4000)
	{
		pot = 3000;
	}
	else if (rate < 4010)
	{
		gift = new ("item/08/0001");
		name = "Chiến Quốc Lệnh";
	}
	else if (rate < 4060)
	{
		gift = new ("item/08/0003");
		name = "Huyết Thạch";
	}
	else if (rate < 4090)
	{
		gift = new ("item/08/0004");
		name = "Pháp Thạch";
	}
	else if (rate < 4120) //技能进阶书
	{
		gift = new (BOOK_FILE->get_book_file());
		name = gift->get_name();
	}
	// else if (rate < 4620)
	// {
	// 	gift = new ("item/huyenthu/exp");
	// 	name = "Thiên Hỏa Thạch Bàn Đơn";
	// }
	else if (rate < 5120) //Hạt Giống Cây Noel
	{
		switch (random(3))
		{
		default:
			gift = new ("item/04/0414");
			break;
		case 1:
			gift = new ("item/sell/0032");
			name = "Sơ Cấp Đoạn Thạch";
			break;
		case 2:
			gift = new ("item/sell/1032");
			name = "Trung Cấp Đoạn Thạch";
			break;
		}
	}
	else if (rate < 5420)
	{
		gift = new (STONE_FILE->get_diamond_file());
		gift->set_level(3);
	}
	else if (rate < 6000)
	{
		gift = new (STONE_FILE->get_diamond_file());
		gift->set_level(1);
	}
	else if (rate < 6340)
	{
		gift = new ("item/91/9178");
		name = "Phục Sinh Đơn";
	}
	else if (rate < 7500) //Tinh Thạch cấp 1
	{
		gift = new (STONE_FILE->get_diamond_file());
		gift->set_level(2);
	}

	else if (rate < 8500) //Thẻ Biến Thân
	{
		switch (random(3))
		{
		default:
			gift = new ("item/04/0415");
			break;
		case 1:
			gift = new ("item/04/0416");
			break;
		case 2:
			gift = new ("item/04/0417");
			break;
		}
	}
	else if (rate < 9250) //炼丹成品
	{
		p = random(6);
		switch (p)
		{
		default:
			gift = new ("item/final/91/1808"); //Ngân Hạnh Tử (Hồi 10% máu)
			break;
		case 1:
			gift = new ("item/final/91/1809"); //Tiên Sơn Linh Chi (Hồi 10% pháp lực)
			break;
		case 2:
			gift = new ("item/final/91/1810"); //Tử Thiến Đơn (Tăng 10% Thân Thủ)
			break;
		case 3:
			gift = new ("item/final/91/1811"); //Xá Lợi Tử (Tăng 10% Ngoại Kháng)
			break;
		case 4:
			gift = new ("item/std/5211"); //Hạc Đỉnh Hồng x3
			gift->set_amount(3);
			break;
		case 5:
			gift = new ("item/91/9145"); //Thanh Tâm Đan x2
			gift->set_amount(2);
			break;
		}
	}
	else //机关中成品
	{
		p = random(4);
		switch (p)
		{
		default:
			gift = new ("item/final/16/1607"); //铁制机关构件
			break;
		case 1:
			gift = new ("item/test2/TuiQuaVoSong"); //精铁机关构件
			break;
		case 2:
			gift = new ("item/test2/TuiPhapBao"); //永动核心
			break;
		case 3:
			gift = new ("item/test/chenbac"); //传动机构
			break;
		}
	}
	if (gift)
	{
		p = gift->move(who, -1);
		if (!p)
		{
			destruct(gift);
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n Hành trang của bạn không đủ ô trống !\n" ESC "Rời khỏi", me->get_name()));
			return 0;
		}
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n Bạn đã nhận được phần quà " HIR "%s" NOR ", chúc bạn giáng sinh ấm áp\n" ESC "Rời khỏi", me->get_name(), gift->get_name()));
		gift->add_to_user(p);
		if (name)
			CHAT_D->sys_channel(0, sprintf(HIY "Xin chúc mừng " HIR "%s" HIY " trong sự kiện Giáng Sinh đạt được " HIG "%s" NOR "!", who->get_name(), name));
	}
	else if (money)
	{
		who->add_cash(money);
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n Bạn đã nhận được " HIR "%d lượng" NOR ", xin chúc mừng !\n" ESC "Rời khỏi", me->get_name(), money));
	}
	else if (pot)
	{
		who->add_potential(pot);
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n Bạn đã nhận được " HIR "%d tiềm năng" NOR ", xin chúc mừng !\n" ESC "Rời khỏi", me->get_name(), pot));
	}
	else if (exp)
	{
		who->add_exp(exp);
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n Bạn đã nhận được " HIR "%d kinh nghiệm" NOR ", xin chúc mừng !\n" ESC "Rời khỏi", me->get_name(), exp));
	}
	return 1;
}

void destroy_turkey()
{
	int i, size;
	object *nObj;
	nObj = SANTACLAUS->get("item");
	for (i = 0, size = sizeof(nObj); i < size; i++)
	{
		if (!objectp(nObj[i]))
			continue;
		if (get_d(nObj[i]))
			continue;
		nObj[i]->remove_from_scene();
		destruct(nObj[i]);
	}
	SANTACLAUS->delete ("item");
}

void generate_turkey()
{
	int i, size, z, p, x, y, j, count;
	object *nObj, item;

	destroy_turkey();
	nObj = ({});
	for (j = 0, count = sizeof(nScene); j < count; j++)
	{
		z = nScene[j];
		for (i = 0; i < 50; i++)
		{
			if (!(p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
				continue;
			x = (p % 1000000) / 1000;
			y = p % 1000;
			item = new (TURKEY);
			if (!objectp(item))
				continue;
			item->add_to_scene(z, x, y);
			nObj += ({item});
			//log_file("christmas.txt",sprintf("%s %d %d %d %d\n",short_time(),i,z,x,y));
		}
	}
	log_file("christmas.txt", short_time() + " hoạt động Noel bắt đầu\n");
	SANTACLAUS->set("item", nObj);
	CHAT_D->sys_channel(0, HIG "Gà tây Noel đã xuất hiện ở ngoài thành Thất quốc và Tân Thủ Thôn, hãy nhanh chóng đi nhặt chúng về để đổi quà từ Ông già Noel !");
	CHAT_D->sys_channel(0, HIG "Gà tây Noel đã xuất hiện ở ngoài thành Thất quốc và Tân Thủ Thôn, hãy nhanh chóng đi nhặt chúng về để đổi quà từ Ông già Noel !");
}

void generate_badman()
{
	int i, size, z, p, x, y;
	object *nObj, npc;

	nObj = ({});
	for (z = 10; z <= 70; z += 10)
	{
		for (i = 0; i < 30; i++)
		{
			if (!(p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
				continue;
			x = (p % 1000000) / 1000;
			y = p % 1000;
			npc = new (SANTANBADMAN);
			if (!objectp(npc))
				continue;
			switch (random(3))
			{
			default:
				npc->set_name("Gấu Ngốc Noel");
				npc->set_char_picid(1289);
				npc->set_max_hp(1);
				npc->set_ap(1);
				npc->set_dp(1);
				npc->set_cp(1);
				npc->set_pp(1);
				npc->set_sp(1);
				npc->set_walk_speed(4);
				npc->set_attack_speed(3);
				break;
			case 1:
				npc->set_name("Quán Yêu Noel");
				npc->set_char_picid(1291);
				npc->set_max_hp(10);
				npc->set_ap(1);
				npc->set_dp(1);
				npc->set_cp(1);
				npc->set_pp(1);
				npc->set_sp(1);
				npc->set_walk_speed(2);
				npc->set_attack_speed(3);
				break;
			case 2:
				npc->set_name("Phi Tặc Noel");
				npc->set_char_picid(1290);
				npc->set_max_hp(1);
				npc->set_ap(1);
				npc->set_dp(1);
				npc->set_cp(1);
				npc->set_pp(1);
				npc->set_sp(1);
				npc->set_walk_speed(2);
				npc->set_attack_speed(1);
				break;
			}
			npc->add_to_scene(z, x, y);
			nObj += ({npc});
			//log_file("christmas.txt",sprintf("%s %d %d %d %d\n",short_time(),i,z,x,y));
		}
	}
	log_file("christmas.txt", short_time() + " quái vật noel xuất hiện\n");
	SANTACLAUS->set("npc", nObj);
	CHAT_D->sys_channel(0, HIG "Một đám quái vật đã cướp túi quà giáng sinh của ông già Noel, nghe nói chúng đang xuất hiện ở ngoài thành 7 nước. Tiêu diệt chúng để thu về Vớ dài đùng để đổi quà tại Ông già Noel !");
}

void destroy_badman()
{
	int i, size, z, p, x, y;
	object *nObj, npc;

	nObj = SANTACLAUS->get("npc");
	for (i = 0, size = sizeof(nObj); i < size; i++)
	{
		if (!objectp(nObj[i]))
			continue;
		nObj[i]->remove_from_scene();
		destruct(nObj[i]);
	}
	SANTACLAUS->delete ("npc");
}
//逃离
void away_user(object me, object who)
{
	int x, y, z, x0, y0, z0, p, d;
	string cmd;

	z = get_z(who);
	x = get_x(who);
	y = get_y(who);
	z0 = get_z(me);
	x0 = get_x(me);
	y0 = get_y(me);
	d = distance_between(me, who);

	if (x0 > x)
	{
		if (y0 > y)
		{
			if (p = get_valid_path(z, x0, y0, (x + (d + 1 + random(3))), y + (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, x, y + (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, (x + (d + 1 + random(3))), y))
				;
			else if (p = get_valid_path(z, x0, y0, (x - (d + 1 + random(3))), y + (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, (x + (d + 1 + random(3))), y - (d + 1 + random(3))))
				;
		}
		else if (y0 == y)
		{
			if (p = get_valid_path(z, x0, y0, (x + (d + 1 + random(3))), y))
				;
			else if (p = get_valid_path(z, x0, y0, (x + (d + 1 + random(3))), y + (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, (x + (d + 1 + random(3))), y - (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, x, y + (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, x, y - (d + 1 + random(3))))
				;
		}
		else
		{
			if (p = get_valid_path(z, x0, y0, (x + (d + 1 + random(3))), y - (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, (x + (d + 1 + random(3))), y))
				;
			else if (p = get_valid_path(z, x0, y0, x, y - (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, (x + (d + 1 + random(3))), y + (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, (x - (d + 1 + random(3))), y - (d + 1 + random(3))))
				;
		}
	}
	else if (x0 == x)
	{
		if (y0 > y)
		{
			if (p = get_valid_path(z, x0, y0, x, y + (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, (x - (d + 1 + random(3))), y + (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, (x + (d + 1 + random(3))), y + (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, (x - (d + 1 + random(3))), y))
				;
			else if (p = get_valid_path(z, x0, y0, (x + (d + 1 + random(3))), y))
				;
		}
		else if (y0 == y)
			;
		else
		{
			if (p = get_valid_path(z, x0, y0, x, y - (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, (x + (d + 1 + random(3))), y - (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, (x - (d + 1 + random(3))), y - (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, (x + (d + 1 + random(3))), y))
				;
			else if (p = get_valid_path(z, x0, y0, (x - (d + 1 + random(3))), y))
				;
		}
	}
	else
	{
		if (y0 > y)
		{
			if (p = get_valid_path(z, x0, y0, (x - (d + 1 + random(3))), y + (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, (x - (d + 1 + random(3))), y))
				;
			else if (p = get_valid_path(z, x0, y0, x, y + (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, (x - (d + 1 + random(3))), y - (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, (x + (d + 1 + random(3))), y + (d + 1 + random(3))))
				;
		}
		else if (y0 == y)
		{
			if (p = get_valid_path(z, x0, y0, (x - (d + 1 + random(3))), y))
				;
			else if (p = get_valid_path(z, x0, y0, (x - (d + 1 + random(3))), y - (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, (x - (d + 1 + random(3))), y + (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, x, y - (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, x, y + (d + 1 + random(3))))
				;
		}
		else
		{
			if (p = get_valid_path(z, x0, y0, (x - (d + 1 + random(3))), y - (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, x, y - (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, (x - (d + 1 + random(3))), y))
				;
			else if (p = get_valid_path(z, x0, y0, (x + (d + 1 + random(3))), y - (d + 1 + random(3))))
				;
			else if (p = get_valid_path(z, x0, y0, (x - (d + 1 + random(3))), y + (d + 1 + random(3))))
				;
		}
	}

	if (p) // 找到可走路径
	{
		cmd = sprintf("%d", p);

		switch (me->get_walk_step())
		{
		case 0:
		case 1:
			if (strlen(cmd) > 1)
				cmd = cmd[0..0];
			break;
		case 2:
			if (strlen(cmd) > 2)
				cmd = cmd[0..1];
			break;
		default:
			break;
		}
		GO_CMD->main_npc(me, cmd);
	}
}
//放圣诞树
void generate_tree()
{
	int i, size, z, p, x, y, j, count, *nZ, *nXy;
	object *nObj, tree;
	mixed *nPoint;
	nObj = ({});

	nZ = keys(mpTree1);
	for (j = 0, count = sizeof(nZ); j < count; j++)
	{
		z = nZ[j];
		nPoint = mpTree1[z];
		for (i = 0, size = sizeof(nPoint); i < size; i++)
		{
			tree = new ("npc/party/santatree1");
			if (!objectp(tree))
				continue;
			nXy = nPoint[i];
			tree->add_to_scene(z, nXy[0], nXy[1]);
			nObj += ({tree});
		}
	}

	nZ = keys(mpTree2);
	for (j = 0, count = sizeof(nZ); j < count; j++)
	{
		z = nZ[j];
		nPoint = mpTree2[z];
		for (i = 0, size = sizeof(nPoint); i < size; i++)
		{
			tree = new ("npc/party/santatree2");
			if (!objectp(tree))
				continue;
			nXy = nPoint[i];
			tree->add_to_scene(z, nXy[0], nXy[1]);
			nObj += ({tree});
		}
	}

	SANTACLAUS->set("tree", nObj);
}

void test()
{
	//	int i,size;
	//	object *nObj;
	//
	//	nObj = SANTACLAUS->get("plant");
	//	for(i=0,size=sizeof(nObj);i<size;i++)
	//	{
	//		if ( !objectp(nObj[i]) ) continue;
	//		nObj[i]->remove_from_scene();
	//		destruct(nObj[i]);
	//	}
}