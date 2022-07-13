
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <npc.h>

mapping mpFamilyObj = (["Đào Hoa Nguyên":"/item/09/0901",
							  "Thục Sơn":"/item/09/0902",
						   "Cấm Vệ Quân":"/item/09/0903",
							 "Đường Môn":"/item/09/0904",
							   "Mao Sơn":"/item/09/0905",
							  "Côn Luân":"/item/09/0906",
						  "Vân Mộng Cốc":"/item/09/0907",
]);
mapping mpEquip = (["Đào Hoa Nguyên":({
										 "/item/70/0010",
									 }),
						  "Thục Sơn":({"/item/73/0010", "/item/72/0010"}),
					   "Cấm Vệ Quân":({"/item/75/0010", "/item/74/0010"}),
						 "Đường Môn":({
										 "/item/71/1010",
									 }),
						   "Mao Sơn":({
										 "/item/77/1010",
									 }),
						  "Côn Luân":({
										 "/item/78/1010",
									 }),
					  "Vân Mộng Cốc":({
										 "/item/79/1010",
									 }),
]);
void do_give_familyobj(object player, object master);
int challenge(object player, object master);

int *spec_skill = ({
	0211,
	0212,
	0316,
	0317,
	0319,
	0221,
	0231,
	0222,
	0325,
	0329,
	0241,
	0251,
	0242,
	0348,
	0349,
	0261,
	0363,
	0364,
	0365,
	0368,
	0271,
	0413,
	0414,
	0417,
	0418,
	0421,
	0422,
	0423,
	0424,
	0425,
	0281,
	0501,
	0511,
	0531,
	0591,
});

// 函数:生成二进制码
void SAVE_BINARY() {}

void do_look(object player, object master)
{
	string name1, name2, result = "", word;
	int order1, order2;
	name1 = player->get_fam_name();
	name2 = master->get_fam_name();
	order1 = player->get_fam_order();
	order2 = master->get_fam_order();
	if (master->get_fam_order() > 4 && name1 == name2)
		result = sprintf(" %s :\n Ngươi có thể học được tuyệt kỹ của bổn môn ở chỗ sư phụ. Còn nữa, sư phụ có thể giao cho ngươi nhiều nhiệm vụ yêu cầu ngươi hoàn thành .\n", master->get_name());
	else
	{
		word = "/quest/master"->get_answer(name2, master->get_fam_order());
		result = sprintf(" %s :\n %s \n", master->get_name(), word);
	}
	if (name1 == name2 && order2 == 4)
		result += sprintf(ESC "Mua trang bị của bổn môn phái\nlist %x#\n", getoid(master));
	if (name1 == "" && order2 == 4 || name1 == name2 && (order1 == order2 || order1 == 0))
		result += sprintf(ESC "Ở đâu có thể mua được vũ khí của bổn môn phái?\ntalk %x# apprentice.11\n" ESC "Bái sư\ntalk %x# apprentice.12\n" ESC "Chỉ là đến bái sư 1 chút thôi\nCLOSE\n", getoid(master), getoid(master));
	else if (name1 == name2 && order2 == 7 && !player->get_save_2("init_gift7"))
		result += sprintf("Để đệ tử của bổn môn phái có thể phát huy tinh túy võ học của bổn môn, bổn trưởng lão đặc biệt cho xóa điểm miễn phí 1 lần.\n" ESC "Xóa điểm miễn phí\ntalk %x# init.1\n", getoid(master));
	result += ESC "Rời khỏi\nCLOSE";
	send_user(player, "%c%s", ':', result);
}

string get_chat(object player, object master)
{
	string name1, name2, result = "", word;
	int order1, order2;
	name1 = player->get_fam_name();
	name2 = master->get_fam_name();
	order1 = player->get_fam_order();
	order2 = master->get_fam_order();
	if (master->get_fam_order() > 4 && name1 == name2)
		result = sprintf("%s:\Ngươi có thể học được kĩ năng ở chỗ Sư phụ, và còn có các nhiệm vụ Sư phụ giao cho ngươi.\n", master->get_name());
	else
	{
		result = "/quest/master"->get_answer(name2, master->get_fam_order());
	}
	return result;
}
void do_apprentice(object player, object master, string arg)
{
	string name1, name2, result = "";
	int order1, order2, flag, i, size;
	object *nEquip, item;
	string *nTmp, tmp;

	name1 = player->get_fam_name();
	name2 = master->get_fam_name();
	order1 = player->get_fam_order();
	order2 = master->get_fam_order();
	flag = to_int(arg);
	switch (flag)
	{
	case 11:
		if (name2 == "Cấm Vệ Quân")
			result = " " + master->get_name() + " :\n Ở Chủ Tiệm Vũ Khí của Chu Quốc(215, 202) và Cửa hàng Giáp trụ(177, 181) có thể mua được trang bị vũ khí của bổn môn.";
		else if (name2 == "Đào Hoa Nguyên")
			result = master->get_name() + ":\n    Ở Chủ Tiệm Vũ Khí của Triệu Quốc（172，060）và Cửa hàng Giáp trụ（184，088）có thể mua được trang bị vũ khí của bổn môn..";
		else if (name2 == "Thục Sơn")
			result = master->get_name() + ":\n    Ở Chủ Tiệm Vũ Khí của Yên Quốc（237，242）và Cửa hàng Giáp trụ（220，230）có thể mua được trang bị vũ khí của bổn môn..";
		else if (name2 == "Đường Môn")
			result = master->get_name() + ":\n    Ở Chủ Tiệm Vũ Khí của Hàn Quốc（213，106）và Cửa hàng Giáp trụ（197，97）có thể mua được trang bị vũ khí của bổn môn..另外你必须注意，使用暗器攻击敌人，必须先学会本门的武功“漫天花雨”.";
		else if (name2 == "Côn Luân")
			result = master->get_name() + ":\n    Ở Chủ Tiệm Vũ Khí của Tần Quốc（137，158）và Cửa hàng Giáp trụ（125，149）có thể mua được trang bị vũ khí của bổn môn..";
		else if (name2 == "Mao Sơn")
			result = master->get_name() + ":\n    Ở Chủ Tiệm Vũ Khí của Tề Quốc（139，162）và Cửa hàng Giáp trụ（135，154）có thể mua được trang bị vũ khí của bổn môn..";
		else if (name2 == "Vân Mộng Cốc")
			result = master->get_name() + ":\n    Ở Chủ Tiệm Vũ Khí của Ngụy Quốc（291，154）và Cửa hàng Giáp trụ（279，165）có thể mua được trang bị vũ khí của bổn môn..";
		else
			return;
		send_user(player, "%c%c%w%s", ':', 3, master->get_char_picid(), result);
		return;
	case 12:
		send_user(player, "%c%c%w%s", ':', 3, master->get_char_picid(), sprintf(" %s :\n Gia nhập bổn môn, ngươi phải tu hành và luyện tập rất gian khổ, ngươi có chắc muốn bái ta làm sư phụ không?\n" ESC "Chấp nhận\ntalk %x# apprentice\n" ESC "Hay là để ta suy nghĩ lại……", master->get_name(), getoid(master)));
		return;
	case 13:
		send_user(player, "%c%c%w%s", ':', 3, master->get_char_picid(), sprintf("%s:\n    Đồ nhi, ngươi thật sự không muốn làm nhiệm vụ này à, vậy ta sẽ suy nghĩ đến việc giao nhiệm vụ cho ngươi.\n" ESC "Nhận nhiệm vụ\ntalk %x# accept_quest\n" ESC "Cự tuyệt\ntalk %x# apprentice.14\n", master->get_name(), getoid(master), getoid(master)));
		return;
	case 14:
		item = player->get_equip(HAND_TYPE);
		if (item && item->get_item_number() == 10001078)
		{
			send_user(player, "%c%c%s", 0x59, 1, sprintf("你是否使用'瞒天过海符'来消除你的任务间隔时间？\n" ESC "%c\n" ESC "use %x# master2\n", 1, getoid(item)));
		}
		return;
	case 15:
		//检查能否学习强化技能.
		TASK_MASTER_D->check_enhance_sk(player, master);
		return;
	}
	// 拜师
	if ((name1 == "" && order2 == 4 || name1 == name2 && (order1 == order2 || order1 == 0)) && player->get_fam_master() != master->get_name())
	{
		if (player->get_level() < 10)
		{
			result = sprintf("%s:\n    Ngươi chưa đạt tới cấp 10, ta không thể nhận ngươi.\n", master->get_name());
			send_user(player, "%c%s", ':', result);
			return;
		}
		nEquip = player->get_all_equip();
		if (nEquip[WEAPON_POSITION] != 0)
		{
			result = sprintf("%s:\n    Bỏ vũ khí ra rồi lại đến tìm ta/\n", master->get_name());
			send_user(player, "%c%s", ':', result);
			return;
		}
		if (USER_INVENTORY_D->get_free_count(player) < 1)
		{
			result = sprintf("%s:\n    Hành trang của ngươi đã đầy, hãy chừa 1 ô trống rồi đến tìm ta.\n", master->get_name());
			send_user(player, "%c%s", ':', result);
			return;
		}
		nTmp = mpEquip[name2];
		if (sizeof(nTmp) == 0)
			return;
		tmp = nTmp[random(sizeof(nTmp))];
		item = new (tmp);
		if (!item)
			return;
		i = item->move2(player);
		item->add_to_user(i);
		send_user(player, "%c%s", ';', sprintf("Ngươi đã nhận được vũ khí môn phái mà sư phụ tặng" HIR " %s", item->get_name()));
		if (name1 == "")
		{
			player->set_fam_name(name2);
			"/sys/sys/count"->add_family(name2, 1);
			for (i = (player->get_fam_type() - 1) * 5; i < player->get_fam_type() * 5; i++)
			{
				if (player->get_skill(spec_skill[i]) <= 0)
					player->set_skill(spec_skill[i], 1);
				//	player->set_skill(spec_skill[i], 1);
			}
		}
		player->use_equip(item);
		player->set_save("famrec", 1);
		if (order1 != order2)
			player->set_fam_order(order2);
		player->set_fam_master(master->get_name());
		player->set_fam_time(time());
		FAMILY_D->family_channel(name2, 0, sprintf(HIY " %s ( %d ) quyết định vào môn hạ %s của %s .", player->get_name(), player->get_number(), name2, master->get_name()));
		if (player->get_legend(TASK_49, 11) && !player->get_legend(TASK_49, 12))
			USER_TASK_D->send_task_intro(player, 2, TID_NEWBIE_01, 118);
		result = sprintf("Ngươi gia nhập môn hạ %s của %s !", name2, master->get_name());
		send_user(player, "%c%s", '!', result);
		result = sprintf(" %s :\n Vậy thì ta thu nhận ngươi vậy.\n", master->get_name());
		send_user(player, "%c%s", ':', result);
		USER_ENERGY_D->count_max_yuan(player);
		if (!nEquip[FAMILY_POSITION])
		{
			do_give_familyobj(player, master);
		}
		else if (nEquip[FAMILY_POSITION]->is_newplayer() == 1) //新手信物
		{
			nEquip[FAMILY_POSITION]->remove_from_user();
			destruct(nEquip[FAMILY_POSITION]);
			player->set_equip(FAMILY_TYPE, 0);
			do_give_familyobj(player, master);
		}
		/*   send_user( get_scene_object_2(player, USER_TYPE), "%c%d%d%w", 0x23, getoid(player), 
                                	player->get_armor_code(), player->get_armor_color_1() );*/
		send_user(get_scene_object_2(player, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(player),
				  player->get_armor_code(), player->get_armor_color_1(), player->get_back(), player->get_back_color(), player->get_back2(), player->get_back2_color());
	}
	switch (flag)
	{
	case 1:
		if (player->get_fam_master() == master->get_name() && order1 != order2)
		{
			result = sprintf("%s:\n Ngươi đã đánh thắng ta, bây giờ có thể bái Sư bá của ngươi làm Sư phụ rồi.\n", master->get_name());
			send_user(player, "%c%s", ':', result);
			return;
		}
		if (order2 == 1)
			return;
		if (time() - player->get_save_2("masterfight.time") < 3600)
		{
			result = sprintf("%s:\n Nhanh như vậy ngươi đã có ý nghĩ khiêu chiến ư, hãy chờ thêm 1 thời gian đi !\n", master->get_name());
			send_user(player, "%c%s", ':', result);
			return;
		}
		if (player->get_level() < master->get_level() - 15)
		{
			result = sprintf(" %s :\n Đồ Nhi, ngươi đã vội vàng thái quá rồi, dựa vào năng lực hiện giờ của ngươi thì chưa đủ để tiếp nhận thử thách của sư môn. Sau khi ngươi đạt cấp %d thì hãy quay lại nhé .\n", master->get_name(), master->get_level() - 15);
			send_user(player, "%c%s", ':', result);
			return;
		}
		else if (player->get_level() < master->get_level() - 5)
		{
			result = sprintf(" %s :\n Dựa vào năng lực hiện giờ của ngươi thì vẫn còn khó khăn chất định để tiếp nhận thử thách này, nếu như không chuẩn bị thật tốt thì chịu thiệt thòi chính là ngươi đó. Ngươi chắc chắn muốn đi vào thử thách của trường luyện võ không?\n" ESC "Ta muốn thử thách\ntalk %x# apprentice.2\n" ESC "Ngươi cần phải suy nghĩ 1 chút", master->get_name(), getoid(master));
			send_user(player, "%c%s", ':', result);
			return;
		}
		else
		{
			result = sprintf("%s:\n Tốt ! hôm nay hãy cho Sư phụ thấy năng lực của ngươi....\n" ESC "Ta phải Khiêu Chiến\ntalk %x# apprentice.2\n" ESC "Ta vẫn còn lo lắng", master->get_name(), getoid(master));
			send_user(player, "%c%s", ':', result);
			return;
		}
		break;
	case 2:
		if (player->get_fam_master() == master->get_name() && order1 != order2)
		{
			result = sprintf("%s:\n Ngươi đã đánh thắng ta, bây giờ có thể bái Sư bá của ngươi làm Sư phụ rồi.\n", master->get_name());
			send_user(player, "%c%s", ':', result);
			return;
		}
		if (order2 == 1)
			return;
		if (time() - player->get_save_2("masterfight.time") < 3600)
		{
			result = sprintf("%s:\n Nhanh như vậy ngươi đã có ý nghĩ khiêu chiến ư, hãy chờ thêm 1 thời gian đi !\n", master->get_name());
			send_user(player, "%c%s", ':', result);
			return;
		}
		if (player->get_level() < master->get_level() - 15)
		{
			result = sprintf("%s:\n Ngươi phải nâng cao năng lực một chút, trước mắt ta thấy ngươi vẫn không được.\n", master->get_name());
			send_user(player, "%c%s", ':', result);
			return;
		}
		challenge(player, master);
		break;
	}
}

void do_give_familyobj(object player, object master)
{
	string name2, cFile;
	object item;

	name2 = master->get_fam_name();
	cFile = mpFamilyObj[name2];
	if (!stringp(cFile))
		return;
	item = new (cFile);
	if (!item)
		return;
	item->set_item_level(1);
	item->init_familyobj();
	if (!player->restore_equip(item))
	{
		destruct(item);
		return;
	}
	USER_ENERGY_D->count_all_prop(player);
	player->init_beast();
	tell_user(player, "Ngươi được tín vật của sư môn: " HIY + cFile->get_name());
	"skill/00/00051"->can_perform(player);
}
//师门挑战
int challenge(object player, object master)
{
	int x, y, z, level, p, d, family, ord;
	string cityname;
	object map, npc;

	ord = master->get_fam_order();
	if (ord == 4)
		level = 60;
	else if (ord == 3)
		level = 90;
	else if (ord == 2)
		level = 120;
	else if (ord == 1)
		level = 150;
	else
		return 0;
	if ((z = find_map_flag(1000, 2999, 0)) <= 0)
		return 1;
	x = (p % 1000000) / 1000;
	y = p % 1000;
	npc = new ("npc/90/app_fight");
	if (!npc)
		return 0;
	npc->set("level", level);
	switch (master->get_fam_name())
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
	init_virtual_map(z, d);
	map = new (NEWBIE);
	map->set_client_id(d);
	map->set_owner(player);
	set_map_object(map, map->set_id(z));
	map->set_name(cityname);
	p = get_jumpin(z, 1);
	NPC_ENERGY_2_D->init_family(npc, family, level, -1);
	npc->set_fam_name(master->get_fam_name());
	npc->set_char_type(FIGHTER_TYPE_2);
	npc->set_name(" " + cityname + " Thủ Vệ");
	npc->set_level(level);
	NPC_ENERGY_D->init_family1(npc);
	x = p / 1000, y = p % 1000;
	npc->set("f_z", z);
	npc->set("f_x", x);
	npc->set("f_y", y);
	npc->set("user", player->get_number());
	npc->set("fight", player);
	player->set_2("masterfight.x", get_x(player));
	player->set_2("masterfight.y", get_y(player));
	player->set_2("masterfight.z", get_z(player));
	if (p = get_valid_xy(z, x, y, IS_CHAR_BLOCK))
	{
		x = p / 1000, y = p % 1000;
		player->add_to_scene(z, x, y, 3);
	}
	player->set_save_2("masterfight.time", time());
	player->set_save_2("masterfight.status", 1);
	npc->do_fight(16);
	return 1;
}