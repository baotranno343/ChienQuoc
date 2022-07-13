#include <ansi.h>
#include <npc.h>
#include <cmd.h>
#include <city.h>

inherit OFFICER;

int is_self_look() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 9306; }

void do_welcome(string arg);
void do_look2(object me, object who);

// 函数：构造处理
void create()
{
	object me = this_object();
	set_name("Võ Giáo Đầu");
	set_city_name("Bang Phái");
	set_2("talk", (["welcome":(
								  : do_welcome:),
	]));
	setup();
}

void do_look(object who)
{
	string result;
	object me = this_object();
	__FILE__->do_look2(me, who);
}

void do_look2(object who, object me)
{

	string result, name;
	object orgnpc;
	int position;
	// if (me->get_org_name() != who->get_org_name())
	// 	return;
	// position = me->get_org_position();
	// name = me->get_org_name();
	// if (name == "")
	// 	return;
	// if (position < 1)
	// 	return;
	// orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	// if (!objectp(orgnpc))
	// 	return;
	result = sprintf("：\n    Tôi được giao nhiệm vụ nâng cao sức mạnh của NPCS và tuyển dụng lính đánh thuê để hỗ trợ chiến tranh. Hiện tại lưu trữ gỗ của Bang Phái , tổng số tiền của Bang Phái vàng. Bạn có cần bất kỳ dịch vụ?\n");
	result += sprintf(ESC "Tìm hiểu nguồn gốc của gỗ\ntalk %x# welcome.10\n", getoid(who));

	result += sprintf(ESC "Huấn luyện quân đội\ntalk %x# welcome.20\n", getoid(who));

	result += sprintf(ESC "Nâng cấp tháp tên\ntalk %x# welcome.30\n", getoid(who));

	result += sprintf(ESC "Nâng cấp ống chính\ntalk %x# welcome.40\n", getoid(who));
	result += sprintf(ESC "Tuyển dụng lính đánh thuê\ntalk %x# welcome.50\n", getoid(who));
	result += ESC "Rời khỏi\nCLOSE\n";
	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
}

void do_welcome(string arg)
{
	object me = this_object();
	__FILE__->do_welcome2(me, arg);
}

void do_welcome2(object who, string arg)
{
	int flag, position, time, level;
	object me, orgnpc, map, npc;
	string name, result, name1, name2;
	int z, size, p, x, y;
	me = this_player();
	// position = me->get_org_position();
	// name = me->get_city_name();
	if (name == "")
		return;
	// orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	// if (!objectp(orgnpc))
	// 	return;
	// time = orgnpc->get_level1_time();
	// z = orgnpc->get_battle();
	map = get_map_object(get_z(me));
	if (map)
	{
		name1 = map->get_war_attack();
		name2 = map->get_war_defense();
	}
	// if (time > 0 && time() > time)
	// {
	// 	__FILE__->level1_callout(who);
	// 	return;
	// }
	// time = orgnpc->get_level2_time();
	// if (time > 0 && time() > time)
	// {
	// 	__FILE__->level2_callout(who);
	// 	return;
	// }
	// time = orgnpc->get_level3_time();
	// if (time > 0 && time() > time)
	// {
	// 	__FILE__->level3_callout(who);
	// 	return;
	// }
	flag = to_int(arg);
	switch (flag)
	{
	case 10:
		result = sprintf("Cau Hoi: \n");
		result += ESC "Rời khỏi\nCLOSE\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	case 20:
		// if (position < 8)
		// 	return;
		// level = orgnpc->get_level2();
		result = sprintf("Cau Hoi: \n");
		result += sprintf(ESC "Chắc chắn\ntalk %x# welcome.21\n", getoid(who));
		result += ESC "Rời khỏi\nCLOSE\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	case 21:
		// if (position < 8)
		// 	return;
		// level = orgnpc->get_level2();
		// time = orgnpc->get_level2_time();
		// if (time > 0)
		// {
		// 	result = sprintf("%s：\n    Tôi đang cố gắng tập luyện, người lớn phải đợi %d giây để xem kết quả.\n", who->get_name(), time - time());
		// 	result += ESC "Rời khỏi\nCLOSE\n";
		// 	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		// 	break;
		// }
		// if (level >= orgnpc->get_level1())
		// {
		// 	result = sprintf("%s：\n    Cấp độ huấn luyện của đơn vị không thể vượt quá cấp bậc của Bang Chủ.\n", who->get_name());
		// 	result += ESC "Rời khỏi\nCLOSE\n";
		// 	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		// 	break;
		// }
		// if (orgnpc->get_wood() < level * 60)
		// {
		// 	result = sprintf("%s：\n    Gang không đủ gỗ%d。\n", who->get_name(), level * 60);
		// 	result += ESC "Rời khỏi\nCLOSE\n";
		// 	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		// 	break;
		// }
		// if (orgnpc->get_gold() < level * 10000)
		// {
		// 	result = sprintf("%s：\n    Bang Phái không đủ tiền%d。\n", who->get_name(), level * 10000);
		// 	result += ESC "Rời khỏi\nCLOSE\n";
		// 	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		// 	break;
		// }
		// orgnpc->add_gold(-level * 10000);
		// orgnpc->add_wood(-level * 60);
		// orgnpc->set_level2_time(time() + 100);
		call_out("level2_callout", 1, who);
		result = "Bang Phái bắt đầu huấn luyện lực lượng.";
		CHAT_D->sys_channel(0, result);
		break;
	case 30:
		// if (position < 8)
		// 	return;
		// level = orgnpc->get_level3();
		result = sprintf("Cau Hoi: \n");
		result += sprintf(ESC "Chắc chắn\ntalk %x# welcome.31\n", getoid(who));
		result += ESC "Rời khỏi\nCLOSE\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	case 31:
		// if (position < 8)
		// 	return;
		// level = orgnpc->get_level3();
		// time = orgnpc->get_level3_time();
		// if (time > 0)
		// {
		// 	result = sprintf("%s：\n   Tôi đang cố gắng hết sức để củng cố hệ thống phòng thủ của Bang Phái, và người lớn sẽ phải đợi %d giây để xem kết quả.\n", who->get_name(), time - time());
		// 	result += ESC "Rời khỏi\nCLOSE\n";
		// 	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		// 	break;
		// }
		// if (level >= orgnpc->get_level1())
		// {
		// 	result = sprintf("%s：\n    Tháp mũi tên không thể vượt quá cấp bậc của người quản lý.\n", who->get_name());
		// 	result += ESC "Rời khỏi\nCLOSE\n";
		// 	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		// 	break;
		// }
		// if (orgnpc->get_wood() < 40 + (level - 1) * 30)
		// {
		// 	result = sprintf("%s：\n    Nhóm gỗ ít hơn %d.\n", who->get_name(), 40 + (level - 1) * 30);
		// 	result += ESC "Rời khỏi\nCLOSE\n";
		// 	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		// 	break;
		// }
		// if (orgnpc->get_gold() < 80000 + (level - 1) * 20000)
		// {
		// 	result = sprintf("%s：\n    Bang Phái không được tài trợ bởi %d.\n", who->get_name(), 400000 + (level - 1) * 200000);
		// 	result += ESC "Rời khỏi\nCLOSE\n";
		// 	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		// 	break;
		// }
		// orgnpc->add_gold(-400000 - (level - 1) * 200000);
		// orgnpc->add_wood(-40 - (level - 1) * 30);
		// orgnpc->set_level3_time(time() + 120);
		call_out("level3_callout", 1, who);
		result = "Bang Phái bắt đầu nâng cấp tháp tên.";
		CHAT_D->sys_channel(0, result);
		break;
	case 40:
		// if (position < 8)
		// 	return;
		// level = orgnpc->get_level1();
		result = sprintf("Cau Hoi: \n");
		result += sprintf(ESC "Chắc chắn\ntalk %x# welcome.41\n", getoid(who));
		result += ESC "Rời khỏi\nCLOSE\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	case 41:
		CHAT_D->sys_channel(0, "41");
		// if (position < 8)
		// 	return;
		// time = orgnpc->get_level1_time();
		// if (time > 0)
		// {
		// 	result = sprintf("%s：\n   Nâng cấp cấp chính của Bang Phái này sẽ phải chờ %d giây.\n", who->get_name(), time - time());
		// 	result += ESC "Rời khỏi\nCLOSE\n";
		// 	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		// 	break;
		// }
		// level = orgnpc->get_level1();
		// if (level >= 6)
		// {
		// 	result = sprintf("%s：\n    Cấp bậc của tổng đài không thể vượt quá mức 6。\n", who->get_name());
		// 	result += ESC "Rời khỏi\nCLOSE\n";
		// 	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		// 	break;
		// }
		// if (orgnpc->get_wood() < level * 200)
		// {
		// 	result = sprintf("%s：\n    Nhóm gỗ ít hơn %d.\n", who->get_name(), level * 200);
		// 	result += ESC "Rời khỏi\nCLOSE\n";
		// 	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		// 	break;
		// }
		// if (orgnpc->get_gold() < 50000 * level)
		// {
		// 	result = sprintf("%s：\n    Bang Phái không được tài trợ bởi %d.\n", who->get_name(), 50000 * level);
		// 	result += ESC "Rời khỏi\nCLOSE\n";
		// 	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		// 	break;
		// }
		// orgnpc->add_gold(-50000 * level);
		// orgnpc->add_wood(-level * 200);
		// orgnpc->set_level1_time(time() + 120);
		call_out("level1_callout", 1, who);
		result = "Các Bang Phái bắt đầu nâng cấp cấp trên.";
		CHAT_D->sys_channel(0, result);
		break;
	case 50:
		result = sprintf("%s：\n    Anh muốn tuyển mộ loại quân đội nào?\n", who->get_name());
		result += sprintf(ESC "Lính đánh thuê bình thường(30000)\ntalk %x# welcome.51\n", getoid(who));

		result += sprintf(ESC "Con rối chiến đấu(50000)\ntalk %x# welcome.52\n", getoid(who));
		result += ESC "Rời đi\nCLOSE\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	case 51:
		if (!map)
			return;
		if (me->get_cash() < 30000)
		{
			result = sprintf("%s：\n    Tiền mặt của bạn là ít hơn 30.000.\n", who->get_name());
			result += ESC "Rời đi\nCLOSE\n";
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			break;
		}
		if (name == name1)
			size = map->sizeof_hire_dbase();
		else
			size = map->sizeof_hire_2_dbase();
		if (size >= 20)
		{
			result = sprintf("%s：\n    Số lượng lính đánh thuê đã lên đến 20 và không thể được thuê thêm nữa.\n", who->get_name());
			result += ESC "Rời đi\nCLOSE\n";
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			break;
		}
		me->add_cash(-30000);
		"/sys/sys/count"->add_use("war", 30000);
		me->log_money("Chiến tranh mua", -30000);
		npc = new ("/npc/war/0081");
		if (!npc)
			return;
		npc->set_org_name(name);
		npc->set_name(me->get_name() + "lính đánh thuê");
		if (name == name1)
		{
			npc->set_char_picid(8012);
			p = get_jumpin(z, 10 + random(3));
			map->add_hire(npc);
			npc->set_manager(map->get_manager());
			npc->set_front(1);
		}
		else
		{
			npc->set_char_picid(8013);
			p = get_jumpin(z, 15 + random(3));
			map->add_hire_2(npc);
			npc->set_manager(map->get_manager_2());
			npc->set_front(2);
		}
		x = p / 1000;
		y = p % 1000;
		npc->add_to_scene(z, x, y, 3);
		result = sprintf("%s：\n    Anh đã chi 30.000 lượng vàng để thuê một lính đánh thuê。\n", who->get_name());
		result += ESC "Rời đi\nCLOSE\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	case 52:
		if (!map)
			return;
		// if (orgnpc->get_weapon() != 1)
		// 	return;
		// if (me->get_cash() < 50000)
		// {
		// 	result = sprintf("%s：\n    Tiền mặt của bạn là ít hơn 50.000.\n", who->get_name());
		// 	result += ESC "Rời đi\nCLOSE\n";
		// 	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		// 	break;
		// }
		if (name == name1)
			size = map->sizeof_power_dbase();
		else
			size = map->sizeof_power_2_dbase();
		if (size >= 5)
		{
			result = sprintf("%s：\n    Số lượng con rối chiến đấu đã lên đến năm và không thể được thuê thêm nữa。\n", who->get_name());
			result += ESC "Rời đi\nCLOSE\n";
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			break;
		}
		me->add_cash(-50000);
		"/sys/sys/count"->add_use("war", 50000);
		me->log_money("Chiến tranh mua", -50000);
		npc = new ("/npc/war/0082");
		if (!npc)
			return;
		npc->set_org_name(name);
		npc->set_name(name + "的战斗傀儡");
		if (name == name1)
		{
			npc->set_char_picid(8012);
			p = get_jumpin(z, 10 + random(3));
			map->add_power(npc);
			npc->set_manager(map->get_manager());
			npc->set_front(1);
		}
		else
		{
			npc->set_char_picid(8013);
			p = get_jumpin(z, 15 + random(3));
			map->add_power_2(npc);
			npc->set_manager(map->get_manager_2());
			npc->set_front(2);
		}
		x = p / 1000;
		y = p % 1000;
		npc->add_to_scene(z, x, y, 3);
		result = sprintf("%s：\n    Bạn đã chi 50.000 vàng để thuê một con rối chiến đấu.\n", who->get_name());
		result += ESC "离开\nCLOSE\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	}
}

// 函数：心跳处理(循环)
void level1_callout(object me) // 每１分处理
{
	string name, result, name1, name2;
	int level, z;
	object orgnpc, map, target;
	// name = me->get_org_name();
	remove_call_out("level1_callout");
	// orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	// if (!objectp(orgnpc))
	// 	return;
	// level = orgnpc->get_level1();
	// level++;
	// orgnpc->set_level1(level);
	// orgnpc->set_level1_time(0);
	// z = orgnpc->get_battle();
	map = get_map_object(get_z(me));
	if (!map)
		return;
	name1 = map->get_war_attack();
	name2 = map->get_war_defense();
	if (name == name1)
		target = map->get_manager();
	else
		target = map->get_manager_2();
	target->upgrade(target->get_level() + 1);
	result = sprintf(HIR "Tổng quản của %s thuận lợi tăng lên một cấp, trước mắt cấp bậc là %d cấp。", name, level);
	CHAT_D->sys_channel(0, result);
	CHAT_D->sys_channel(0, result);
}

// 函数：心跳处理(循环)
void level2_callout(object me) // 每１分处理
{
	string name, result, name1, name2;
	int level, z, i, size;
	object orgnpc, map, *target;
	// name = me->get_org_name();
	remove_call_out("level2_callout");
	// orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	// if (!objectp(orgnpc))
	// 	return;
	// level = orgnpc->get_level2();
	// level++;
	// orgnpc->set_level2(level);
	// orgnpc->set_level2_time(0);
	// z = orgnpc->get_battle();
	map = get_map_object(get_z(me));
	if (!map)
		return;
	name1 = map->get_war_attack();
	name2 = map->get_war_defense();
	if (name == name1)
		target = map->get_comrade_dbase();
	else
		target = map->get_comrade_2_dbase();
	size = sizeof(target);
	for (i = 0; i < size; i++)
		target[i]->upgrade(target[i]->get_level() + 1);
	result = sprintf(HIR "Bộ đội của %s thuận lợi tăng lên một cấp, trước mắt cấp bậc là cấp %d.", name, level);
	CHAT_D->sys_channel(0, result);
	CHAT_D->sys_channel(0, result);
}

// 函数：心跳处理(循环)
void level3_callout(object me) // 每１分处理
{
	string name, result, name1, name2;
	int level, z, i, size;
	object orgnpc, map, *target;
	// name = me->get_org_name();
	remove_call_out("level3_callout");
	// orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	// if (!objectp(orgnpc))
	// 	return;
	// level = orgnpc->get_level3();
	// level++;
	// orgnpc->set_level3(level);
	// orgnpc->set_level3_time(0);
	// z = orgnpc->get_battle();
	map = get_map_object(get_z(me));
	if (!map)
		return;
	name1 = map->get_war_attack();
	name2 = map->get_war_defense();
	if (name == name1)
		target = map->get_tower_dbase();
	else
		target = map->get_tower_2_dbase();
	size = sizeof(target);
	for (i = 0; i < size; i++)
		target[i]->upgrade(target[i]->get_level() + 1);
	result = sprintf(HIR "Tháp mũi tên của %s thuận lợi tăng lên một cấp, trước mắt cấp bậc là cấp %d.", name, level);
	CHAT_D->sys_channel(0, result);
	CHAT_D->sys_channel(0, result);
}
