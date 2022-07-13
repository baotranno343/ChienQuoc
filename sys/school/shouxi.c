//首席大弟子控制模块

#include <ansi.h>
#include <time.h>
#include <npc.h>
#include <chia_kenh.h>

#define DEBUG(arg)       \
	if (find_char("21")) \
		tell_user(find_char("21"), arg);
#define FILE_ENERGY "sys/user/energy"
#define FILE_MINGREN "sys/party/mingren"

inherit DBASE_F;
inherit SAVE_F;

static string *SchoolName = ({
	"Đào Hoa Nguyên",
	"Cấm Vệ Quân",
	"Thục Sơn",
	"Côn Luân",
	"Mao Sơn",
	"Vân Mộng Cốc",
	"Đường Môn",
});
static mapping mpPic = (["Cấm Vệ Quân":40000, "Mao Sơn":80000, "Vân Mộng Cốc":70000, "Đào Hoa Nguyên":20100, "Thục Sơn":30100, "Côn Luân":60100, "Đường Môn":50100]);
static mapping mpPos = (["Cấm Vệ Quân":({80, 172, 77, 8}), "Mao Sơn":({269, 261, 173, 4}), "Vân Mộng Cốc":({165, 110, 23, 3}), "Đào Hoa Nguyên":({289, 84, 73, 4}), "Thục Sơn":({273, 203, 152, 3}), "Côn Luân":({54, 124, 128, 3}), "Đường Môn":({324, 94, 118, 3})]);
static string cTmp;
static int iGen;
static string *nDrugs = ({
	"item/91/9125",
	"item/91/9150",
	"item/91/9160",
	"item/91/9161",
	"item/91/9162",
	"item/91/9163",
	"item/91/9164",
	"item/91/9165",
});
int iTimes; //竞选的次数

void open_vote();
void start_vote();
void generate_shouxi();

// 函数：生成二进制码
void SAVE_BINARY() {}

string get_save_file() { return "data/shouxi" SAVE_EXTENSION; }

void create()
{
	if (MAIN_D->get_kenh() == KENH_BANG)
	{
		return;
	}
	restore();
	call_out("check_time", 3);
}

int check_price(object who)
{
	int i;
	if ((i = who->get_level()) < 30)
		i = 50000;
	else
		i = i * i * 10 + 50000;
	return i;
}
void check_time()
{
	int i;
	mixed *mixTime;

	remove_call_out("check_time");
	mixTime = localtime(get_party_time());
	if (mixTime[TIME_WDAY] == 0)
		call_out("check_time", 60 * (60 - mixTime[TIME_MIN]));
	else
		call_out("check_time", 3600 * 12);

	i = (get_party_time() - 4 * 24 * 3600 + 8 * 3600) / (7 * 24 * 3600);
	if (iTimes != i) //生成新一周的首席弟子
	{
		iTimes = i;
		open_vote();

		start_vote();
		generate_shouxi();
		iGen = 1;
		FILE_MINGREN->check_time();
		save();
	}
	if (iGen != 1) //没生成的就生成
	{
		generate_shouxi();
		iGen = 1;
	}
}

void do_look(object me, object who)
{
	int id = getoid(me), picid;
	string fam_name, name;

	fam_name = me->get("fam_name");
	if ((picid = me->get_armor_code()) == 0)
		picid = mpPic[fam_name];
	name = me->get_real_name() ? me->get_real_name() : me->get_name();
	if (fam_name != who->get_fam_name())
	{
		send_user(who, "%c%c%w%s", ':', 3, picid, name + " :\n Ngươi đến bổn môn có việc gì không ? Nếu đến là sinh ra tranh cãi , làm cho người làm Đại Đệ Tử bổn môn như ta không thể tha thứ cho ngươi!\n" + ESC "Rời khỏi");
		return;
	}
	send_user(who, "%c%c%w%s", ':', 3, picid, name + " :\n Ta là Đại Đệ Tử cao nhất ở bổn môn, đệ tử bổn môn đều có thể vinh dự vì đã chọn Đại Đệ Tử này, ngươi muốn đạt được thân phận cao quí này à? Vậy thì ngươi phải nổ lực nhiều hơn nữa!\n" + sprintf(ESC "Tranh cử Đại Đệ Tử cao quí\ntalk %x# elect\n", id) + sprintf(ESC "Ta cần bỏ phiếu\ntalk %x# list\n", id) + sprintf(ESC "Lĩnh chân truyền Môn phái\ntalk %x# hornor.0\n", id) + sprintf(ESC "Đổi báu vật\ntalk %x# exchange.0\n", id) +
												  //	sprintf(ESC"Đổi Mật tịch cấp 150 Môn Phái\nlist7 %x#\n",id) +
												  ESC "Rời khỏi");
}

void join_elect(object me, object who)
{
	int picid;
	string fam_name, name;
	if ((fam_name = me->get("fam_name")) != who->get_fam_name())
		return;
	if ((picid = me->get_armor_code()) == 0)
		picid = mpPic[fam_name];
	name = me->get_real_name() ? me->get_real_name() : me->get_name();
	send_user(who, "%c%c%w%s", ':', 3, picid, name + sprintf(" :\n Ngươi muốn tranh chức Đại Đệ Tử trừ khi ngươi đánh bại được ta! ngoài ra còn giao nạp phí tranh cử là %d. Thật tình ngươi không có chút thực lực, ta khuyên ngươi sớm Thoát ra!\n", check_price(who)) + sprintf(ESC "Chấp nhận\ntalk %x# fight\n", getoid(me)) + ESC "Rời khỏi");
}

void do_fight(object me, object who)
{
	int iCash, level, z, d, family, x, y, p, pic, picid, price;
	string cityname, fam_name, name;
	object npc, map;

	if ((fam_name = me->get("fam_name")) != who->get_fam_name())
		return;
	if ((picid = me->get_armor_code()) == 0)
		picid = mpPic[fam_name];
	name = me->get_real_name() ? me->get_real_name() : me->get_name();
	if (sizeof(get_save_2(sprintf("elect.%s", who->get_fam_name()))) >= 20)
	{
		send_user(who, "%c%c%w%s", ':', 3, picid, name + ":\n    Vị sư đệ này, tranh cử Đại Đệ Tử cao quý đã chấm dứt, hãy đợi tới tuần sau đi !\n" + ESC "Rời khỏi");
		return;
	}
	if (mapp(get_save_2(sprintf("elect.%s.%d", who->get_fam_name(), who->get_number()))))
	{
		send_user(who, "%c%c%w%s", ':', 3, picid, name + ":\n    Ngươi đã tham gia tranh cử Đại Đệ Tử cao quý rồi !\n" + ESC "Rời khỏi");
		return;
	}
	price = check_price(who);
	if ((z = find_map_flag(1000, 2999, 0)) <= 0)
		return;
	if (who->get_level() < 50)
	{
		send_user(who, "%c%s", '!', "Cấp dưới 50 không thể tranh cử !");
		return;
	}
	if ((iCash = who->get_cash()) < price)
	{
		send_user(who, "%c%s", '!', "Không đủ chi phí tranh cử !");
		return;
	}
	switch (who->get_fam_name())
	{
	case "Đào Hoa Nguyên":
		family = 10;
		d = 891;
		cityname = "Đào Hoa Đảo";
		break;
	case "Thục Sơn":
		family = 20;
		d = 892;
		cityname = "Thục Lĩnh Phong";
		break;
	case "Cấm Vệ Quân":
		family = 30;
		d = 893;
		cityname = "Doanh trại Cấm vệ quân";
		break;
	case "Đường Môn":
		family = 40;
		d = 894;
		cityname = "Đường Môn Mật Thất";
		break;
	case "Mao Sơn":
		family = 50;
		d = 895;
		cityname = "Quỷ Môn Phủ";
		break;
	case "Côn Luân":
		family = 60;
		d = 896;
		cityname = "Côn Luân Tiên Cảnh";
		break;
	default:
		family = 70;
		d = 897;
		cityname = "Tử Vong Đầm Lầy";
		break;
	}
	level = who->get_level() + 5;
	npc = new ("npc/school/00011");
	if (!npc)
		return;

	init_virtual_map(z, d);
	map = new (NEWBIE);
	map->set_client_id(d);
	map->set_owner(who);
	set_map_object(map, map->set_id(z));
	map->set_name(cityname);
	p = get_jumpin(z, 1);
	NPC_ENERGY_2_D->init_family(npc, family, level, -1);
	npc->add_dp(npc->get_dp() / 10);
	npc->add_max_hp(npc->get_max_hp() * 4);
	npc->add_pp(npc->get_pp() / 10);
	npc->add_mp(npc->get_mp() / 2);
	npc->add_ap(-npc->get_ap() / 10);

	npc->set_fam_name(who->get_fam_name());
	npc->set_char_type(FIGHTER_TYPE_2);
	npc->set_name(me->get_name());
	npc->set_real_name(me->get_real_name());
	//	npc->set_char_picid(mpPic[who->get_fam_name()]);
	who->set_2("shouxi.x", get_x(who));
	who->set_2("shouxi.y", get_y(who));
	who->set_2("shouxi.z", get_z(who));
	x = p / 1000, y = p % 1000;
	npc->set("user", who->get_number());
	if (stringp(get_save_2(sprintf("winners.%s.name", who->get_fam_name()))))
	{
		if (pic = get_save_2(sprintf("winners.%s.armorcode", who->get_fam_name())))
			npc->set_armor_code(pic);
		else
			npc->set_armor_code(mpPic[who->get_fam_name()]);
	}
	else
	{
		npc->set_armor_code(mpPic[who->get_fam_name()]);
	}
	npc->add_to_scene(z, x, y, 3);
	if (p = get_valid_xy(z, x, y, IS_CHAR_BLOCK))
	{
		x = p / 1000, y = p % 1000;
		who->add_to_scene(z, x, y, 3);
	}
	who->add_cash(-price);
}
//加入竞选
void add_elect(object who)
{
	string fam_name;

	fam_name = who->get_fam_name();
	set_save_2(sprintf("elect.%s.%d.name", fam_name, who->get_number()), who->get_name());
	set_save_2(sprintf("elect.%s.%d.armorcode", fam_name, who->get_number()), who->get_armor_code());
	set_save_2(sprintf("elect.%s.%d.level", fam_name, who->get_number()), who->get_level());
	save();
	log_file("schoolvote.txt", sprintf("%s %s %d %s 加入竞选\n", short_time(), fam_name, who->get_number(), who->get_name()));
}
//列表竞选名单
void do_list(object me, object who)
{
	int i, size, id;
	string fam_name, *key;
	mapping mpTmp;
	//restore();
	if (me->get("fam_name") != who->get_fam_name())
		return;
	fam_name = me->get("fam_name");
	mpTmp = get_save_2("elect." + fam_name);
	if (!mapp(mpTmp))
	{
		send_user(who, "%c%s", '!', "Hiện tại không có ai tham gia tranh cử");
		return;
	}
	if (who->get_level() < 50)
	{
		send_user(who, "%c%s", '!', "Cấp độ nhỏ thua 50 không thể bỏ phiếu");
		return;
	}
	key = keys(mpTmp);
	id = getoid(me);
	for (i = 0, size = sizeof(key); i < size; i++)
	{
		//tell_user(who,"%d %d %d %s",to_int(key[i]),id,mpTmp[key[i]]["point"],mpTmp[key[i]]["name"]);
		send_user(who, "%c%c%d%d%w%w%s", 0xA0, 1, to_int(key[i]), id, mpTmp[key[i]]["level"], mpTmp[key[i]]["point"], mpTmp[key[i]]["name"]);
	}
}

void do_info(object me, object who, string arg)
{

	int i, size, k;
	string fam_name, id;
	mapping mpTmp;

	if (me->get("fam_name") != who->get_fam_name())
		return;
	fam_name = me->get("fam_name");
	mpTmp = get_save_2("elect." + fam_name);
	if (!mapp(mpTmp))
		return;
	if (sscanf(arg, "%d.%s.%s", k, id, arg) != 3)
	{
		if (sscanf(arg, "%d.%s", k, id) != 2)
			return;
	}
	if (!mapp(mpTmp[id]))
		return;
	if (k == 1)
	{
		if (stringp(mpTmp[id]["info"]))
			send_user(who, "%c%c%d%d%s", 0xA0, 2, to_int(id), getoid(me), mpTmp[id]["info"]);
		else
			send_user(who, "%c%c%d%d%s", 0xA0, 2, to_int(id), getoid(me), "");
	}
	else if (k == 2)
	{
		if (sizeof(arg) > 120)
		{
			send_user(who, "%c%s", '!', "Quá dài, hãy giảm bớt kí tự !");
			return;
		}
		if (strstr(arg, ".") != -1)
		{
			send_user(who, "%c%s", '!', "Từ ngữ sai quy tắc !");
			return;
		}
		if (mpTmp[id]["level"] != who->get_level())
			set_save_2(sprintf("elect.%s.%s.level", fam_name, id), who->get_level());
		set_save_2(sprintf("elect.%s.%s.info", fam_name, id), arg);
		save();
	}
}

void do_vote(object me, object who, string arg)
{
	int level, p;
	string id, name, fam_name;

	if (me->get("fam_name") != who->get_fam_name())
		return;
	if (!stringp(arg))
		return;
	id = arg;
	if (who->get_save("shouxivote") == iTimes)
	{
		send_user(who, "%c%s", '!', "Ngươi đã bỏ phiếu rồi !");
		return;
	}
	fam_name = who->get_fam_name();
	level = who->get_level();
	if (sizeof(fam_name) == 0 || level < 10)
	{
		send_user(who, "%c%s", '!', "Ngươi không đủ tư cách bỏ phiếu !");
		return;
	}
	if (!mapp(get_save_2(sprintf("elect.%s.%s", fam_name, id)))) //不存在
		return;
	if (level < 30)
		p = 1;
	else if (level < 60)
		p = 2;
	else if (level < 90)
		p = 3;
	else if (level < 120)
		p = 4;
	else if (level <= 150)
		p = 5;
	add_save_2(sprintf("elect.%s.%s.point", fam_name, id), p);
	who->set_save("shouxivote", iTimes);
	save();
	name = get_save_2(sprintf("elect.%s.%s.name", fam_name, id));
	FAMILY_D->family_channel(fam_name, 0, CHAT + sprintf(" %s Người chơi bầu cử Đại Đệ Tử bỏ %s một phiếu, %s người chơi xứng đáng tích luỹ tăng thêm %d phần", who->get_name(), name, name, p));
	send_user(who, "%c%c%d%d%w%w%s", 0xA0, 1, to_int(id), getoid(me), get_save_2(sprintf("elect.%s.%s.level", fam_name, id)), get_save_2(sprintf("elect.%s.%s.point", fam_name, id)));
	log_file("schoolvote.txt", sprintf("%s %s %s 投票 %s 得分 %d 总分 %d\n", short_time(), fam_name, who->get_name(), name, p, get_save_2(sprintf("elect.%s.%s.point", fam_name, id))));
}

// 函数：票数比对 降序
int vote_cmp(string key1, string key2)
{
	return get_save_2(sprintf("elect.%s.%s.point", cTmp, key2)) - get_save_2(sprintf("elect.%s.%s.point", cTmp, key1));
}
//选举结果
void open_vote()
{
	int i, size;
	string *key;

	for (i = 0, size = sizeof(SchoolName); i < size; i++)
	{
		if (sizeof(get_save_2(sprintf("elect.%s", SchoolName[i]))) == 0)
			continue;
		cTmp = SchoolName[i];
		key = sort_array(keys(get_save_2(sprintf("elect.%s", SchoolName[i]))), (
																				   : vote_cmp($1, $2)
																				   :));
		set_save_2(sprintf("winners.%s.name", SchoolName[i]), get_save_2(sprintf("elect.%s.%s.name", SchoolName[i], key[0])));
		set_save_2(sprintf("winners.%s.armorcode", SchoolName[i]), get_save_2(sprintf("elect.%s.%s.armorcode", SchoolName[i], key[0])));
		set_save_2(sprintf("winners.%s.level", SchoolName[i]), get_save_2(sprintf("elect.%s.%s.level", SchoolName[i], key[0])));
		set_save_2(sprintf("winners.%s.id", SchoolName[i]), key[0]);
		set_save_2(sprintf("winners.%s.family", SchoolName[i]), SchoolName[i]);
		set_save_2(sprintf("winners.%s.point", SchoolName[i]), get_save_2(sprintf("elect.%s.%s.point", SchoolName[i], key[0])));
		log_file("schoolvote.txt", sprintf("%s %s Đại Đệ Tử cao quí: %s %s \n", short_time(), SchoolName[i], key[0], get_save_2(sprintf("elect.%s.%s.name", SchoolName[i], key[0]))));
	}
	save();
}
//开始新投票
void start_vote()
{
	int i, size, *nTmp;
	string id;
	mapping mpTmp;

	delete_save_2("elect");
	for (i = 0, size = sizeof(SchoolName); i < size; i++)
	{
		log_file("schoolvote.txt", sprintf("%s %s 开始新一轮竞选\n", short_time(), SchoolName[i], ));
		mpTmp = get_save_2(sprintf("winners.%s", SchoolName[i]));
		if (!mapp(mpTmp))
			continue;
		id = mpTmp["id"];
		set_save_2(sprintf("elect.%s.%s.name", SchoolName[i], id), mpTmp["name"]);
		set_save_2(sprintf("elect.%s.%s.armorcode", SchoolName[i], id), mpTmp["armorcode"]);
		set_save_2(sprintf("elect.%s.%s.level", SchoolName[i], id), mpTmp["level"]);
	}
	save();
}
//生成首席弟子
void generate_shouxi()
{
	int i, size, *nTmp, z;
	string name;
	object npc;

	for (i = 0, size = sizeof(SchoolName); i < size; i++)
	{
		if (!objectp(npc = get(SchoolName[i])))
		{
			npc = new ("npc/school/0001");
			if (!npc)
				break;
			set(SchoolName[i], npc);
		}
		npc->set("fam_name", SchoolName[i]);
		nTmp = mpPos[SchoolName[i]];
		if (stringp(name = get_save_2(sprintf("winners.%s.name", SchoolName[i]))))
		{
			npc->set_name(" " + SchoolName[i] + " " + "Đại Đệ Tử cao quí");
			npc->set_real_name(name);
			if (z = get_save_2(sprintf("winners.%s.armorcode", SchoolName[i])))
				npc->set_armor_code(z);
			else
				npc->set_armor_code(mpPic[SchoolName[i]]);
		}
		else
		{
			npc->set_name("Đại Đệ Tử cao quí");
			npc->set_armor_code(mpPic[SchoolName[i]]);
		}
		npc->add_to_scene(nTmp[0], nTmp[1], nTmp[2], nTmp[3]);
		set_block(nTmp[0], nTmp[1], nTmp[2], FLY_BLOCK);
	}
}

void before_destruct()
{
	int i, size;
	object npc;
	for (i = 0, size = sizeof(SchoolName); i < size; i++)
	{
		if (!objectp(npc = get(SchoolName[i])))
			continue;
		npc->remove_from_scene();
		destruct(npc);
	}
}

void do_exchange(object me, object who, string arg)
{
	int i, id, p, p1, p2, picid;
	object item;
	string cTmp, fam_name, name;
	i = to_int(arg);
	id = getoid(me);
	if ((fam_name = me->get("fam_name")) != who->get_fam_name())
		return;
	if ((picid = me->get_armor_code()) == 0)
		picid = mpPic[fam_name];
	name = me->get_real_name() ? me->get_real_name() : me->get_name();
	if (i == 0)
	{
		send_user(who, "%c%c%w%s", ':', 3, picid, " " + name + " :\n Sư đệ! Sư phụ nhìn thấy ngươi gần đâ nổ lực cực khổ tập luyện vì muốn phát dương quang đại bổn môn đã Cống hiến không ít, lần khen thưởng này ngươi nhất thiết dùng sự Cống hiến đổi lấy.\n" + sprintf(ESC "12 điểm đổi Tầm Bảo Đồ\ntalk %x# exchange.1\n", id) +
													  //			sprintf(ESC"64 điểm đổi 技能进阶书\ntalk %x# exchange.2\n",id) +
													  sprintf(ESC "12 điểm đổi 1 viên thuốc cao cấp\ntalk %x# exchange.3\n", id) +
													  //	sprintf(ESC"2000 điểm đổi 1 Bí Kíp Sơ Cấp 150 Môn Phái\ntalk %x# exchange.4\n",id) +
													  //	sprintf(ESC"3000 điểm đổi 1 Bí Kíp Trung Cấp 150 Môn Phái\ntalk %x# exchange.5\n",id) +
													  //	sprintf(ESC"4000 điểm đổi 1 Bí Kíp Cao Cấp 150 Môn Phái\ntalk %x# exchange.6\n",id) +
													  //	sprintf(ESC"5000 điểm đổi 1 Bí Kíp Bá Vương 150 Môn Phái\ntalk %x# exchange.7\n",id) +
													  ESC "Rời khỏi");
		return;
	}
	if (i == 1)
	{
		cTmp = "item/std/8000";
		p1 = 12;
	}
	else if (i == 2)
	{
		cTmp = BOOK_FILE->get_book_file();
		p1 = 64;
	}
	else if (i == 3)
	{
		cTmp = nDrugs[random(sizeof(nDrugs))];
		p1 = 12;
	}

	else
		return;
	if (!stringp(cTmp))
		return;
	if ((p2 = who->get_fam_contribute()) < p1)
	{
		send_user(who, "%c%s", '!', "Điểm cống hiến Môn phái không đủ !");
		return;
	}
	item = new (cTmp);
	if (!item)
		return;
	p = item->move2(who, -1);
	if (!p)
	{
		send_user(who, "%c%s", '!', "Hành trang không đủ chỗ !");
		return;
	}
	send_user(who, "%c%s", '!', "Ngươi đổi thành công " + item->get_name());
	item->add_to_user(p);
	who->set_fam_contribute(p2 - p1);
}

int can_betray(object who)
{
	string fam_name;
	fam_name = who->get_fam_name();
	if (sizeof(fam_name) == 0)
		return 1;
	if (mapp(get_save_2(sprintf("elect.%s.%d", fam_name, who->get_number()))))
	{
		send_user(who, "%c%s", '!', "Ngươi tham gia tranh cử Đại đệ tử, không thể phản bội Sư môn !");
		return 0;
	}
	return 1;
}
//领取师门称谓
void get_hornor(object me, object who, string arg)
{
	string fam_name, cTitle, name;
	mapping mpTmp;
	int level, point, flag, id, picid;

	//restore();
	if ((fam_name = me->get("fam_name")) != who->get_fam_name())
		return;
	if ((picid = me->get_armor_code()) == 0)
		picid = mpPic[fam_name];
	id = getoid(me);
	flag = to_int(arg);
	name = me->get_real_name() ? me->get_real_name() : me->get_name();
	if (flag == 0)
	{
		send_user(who, "%c%c%w%s", ':', 3, picid, " " + name + " :\n Những Cống hiến của sư đệ gần đây, sư phụ rất hài lòng, để khẳng định những nổ lực này của sư đệ, sư phụ quyết định cho ngươi số hiệu tương đương.\n" + sprintf(ESC "Lĩnh cấp 1 xưng hô\ntalk %x# hornor.1\n", id) + sprintf(ESC "Lĩnh cấp 2 xưng hô\ntalk %x# hornor.2\n", id) + sprintf(ESC "Lĩnh cấp 3 xưng hô\ntalk %x# hornor.3\n", id) + sprintf(ESC "Lĩnh cấp 4 xưng hô\ntalk %x# hornor.4\n", id) + sprintf(ESC "Lĩnh được xưng vị cấp cao nhất\ntalk %x# hornor.9\n", id) + ESC "Rời khỏi");
		return;
	}
	else if (flag == 9)
	{
		//领取首席称谓
		mpTmp = get_save_2(sprintf("winners.%s", fam_name));
		if (iTimes != who->get_save("sxTimes") && mapp(mpTmp) && to_int(mpTmp["id"]) == who->get_number())
		{
			who->set_save("sxTimes", iTimes);
			who->set_save("sxFamily", fam_name);
			TITLE_D->add_shouxi_title(who, fam_name);
			send_user(who, "%c%s", '!', "Ngươi nhận Thủ tịch Đại đệ tử Xưng hô");
		}
		return;
	}
	else if (flag == 1)
	{
		level = 30;
		point = 150;
	}
	else if (flag == 2)
	{
		level = 60;
		point = 300;
	}
	else if (flag == 3)
	{
		level = 90;
		point = 600;
	}
	else if (flag == 4)
	{
		level = 120;
		point = 1200;
	}
	else
		return;
	if (who->get_level() < level)
	{
		send_user(who, "%c%s", '!', "Cấp bậc của ngươi không đủ !");
		return;
	}
	if (who->get_fam_contribute() < point)
	{
		send_user(who, "%c%s", '!', sprintf("Điểm Cống hiến của bạn cho Môn phái không đủ %d điểm!", point));
		return;
	}
	cTitle = who->get_fam_title();
	if (sizeof(cTitle) == 4)
	{
		if (to_int(cTitle[2..2]) >= flag)
		{
			send_user(who, "%c%s", '!', "Ngươi không thể lĩnh cấp bậc xưng hô này !");
			return;
		}
		who->delete_title(cTitle);
	}
	cTitle = sprintf("S%d%d%d", who->get_fam_type(), flag, who->get_gender());
	who->add_title(cTitle);
	who->set_fam_title(cTitle);
	send_user(who, "%c%s", '!', sprintf("Ngươi nhận được %d cấp xưng hô !", flag));
}
//检查首席称谓
void check_shouxi_title(object who)
{
	string fam_name;
	fam_name = who->get_fam_name();
	if (iTimes == who->get_save("sxTimes") && fam_name == who->get_save("sxFamily"))
		return;
	who->delete_save("sxTimes");
	who->delete_save("sxFamily");
	who->delete_title(TITLE_D->get_shouxi_titlecode(fam_name));
}
//test
void test_add_elect(object who)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		set_save_2(sprintf("elect.Thục Sơn.%d.name", i), sprintf("test%d", i));
		set_save_2(sprintf("elect.Thục Sơn.%d.level", i), i * 10);
	}
	tell_user(who, "ok!");

	save();
}

void test_times()
{
	iTimes = 0;
}
