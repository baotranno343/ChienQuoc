
#include <ansi.h>
#include <city.h>
#include <chia_kenh.h>
// 函数：命令处理
int main(object me, string arg)
{
	object city, *char, *team, npc, obj, orgnpc, who;
	string name, name2, result, *args, *allmember;
	int flag, z, x, y, p, position, number;
	int kenh = MAIN_D->get_kenh(), i, size, vitri;
	string *list = MAIN_D->getlist();
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(me, "%c%s", '!', "Vui lòng sử dụng tính năng bang phái ở Kênh Bang Phái");
		return;
	}
	if (!arg)
		return 1;
	if (arg == "status")
	{
		name = me->get_org_name();
		if (!name || name == "")
			return 1;
		orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
		if (!objectp(orgnpc))
			return 1;
		position = me->get_org_position();
		if (position == 0)
			return 1;
		number = me->get_number();
		result = sprintf("%-12s%c", name, position);
		//        	result += sprintf("%-12s%c", orgnpc->get_master_name(), 9);
		//        	if (orgnpc->get_master_name_2()!="") result += sprintf("%-12s%c", orgnpc->get_master_name_2(), 8);
		send_user(me, "%c%c%c%c%c%d%d%d%d%d%d%d%s", 0x95, 81, orgnpc->get_grade(), orgnpc->get_science(), orgnpc->get_train(),
				  orgnpc->get_power(), orgnpc->get_favour(), orgnpc->get_stable(), orgnpc->get_store(),
				  orgnpc->get_gold(), orgnpc->get_member_contribute(number), orgnpc->get_member_all_contribute(number), result);
		size = orgnpc->sizeof_member_dbase();
		allmember = orgnpc->get_all_member();
		for (i = 0; i < size; i++)
		{
			number = to_int(allmember[i]);
			if (number == 0)
				continue;
			if (orgnpc->get_member_name(number) == 0)
				continue;
			send_user(me, "%c%c%d%d%c%d%d%c%s", 0x95, 91, number,
					  orgnpc->get_member_time(number), orgnpc->get_member_quit(number) ? 0 : 1,
					  orgnpc->get_member_gold(number), orgnpc->get_member_all_contribute(number), orgnpc->get_member_level(number),
					  sprintf("%-12s%s", orgnpc->get_member_name(number), orgnpc->get_member_rank(number)));
		}
		return 1;
	}
	if (arg == "joinlist")
	{
		name = me->get_org_name();
		if (!name || name == "")
			return 1;
		orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
		if (!objectp(orgnpc))
			return 1;
		position = me->get_org_position();
		if (position == 0)
			return 1;
		size = orgnpc->sizeof_join_dbase();
		allmember = orgnpc->get_all_join();

		for (i = 0; i < size; i++)
		{
			number = to_int(allmember[i]);
			if (number == 0)
				continue;
			send_user(me, "%c%c%d%w%s", 0x95, 93, number,
					  orgnpc->get_join_level(number), orgnpc->get_join_name(number));
			if (orgnpc->get_join_family(number) == 0)
				send_user(me, "%c%c%d%c%d%d%s", 0x95, 94, number,
						  orgnpc->get_join_gender(number), orgnpc->get_photo(number),
						  orgnpc->get_join_time(number), " ");
			else
				send_user(me, "%c%c%d%c%d%d%s", 0x95, 94, number,
						  orgnpc->get_join_gender(number), orgnpc->get_photo(number),
						  orgnpc->get_join_time(number), orgnpc->get_join_family(number));
		}
		return 1;
	}
	if (arg == "note")
	{
		name = me->get_org_name();
		orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
		if (!objectp(orgnpc))
			return 1;
		position = me->get_org_position();
		if (position == 0)
			return 1;
		if (orgnpc->get_bulletin() != 0)
			send_user(me, "%c%c%s", 0x95, 80, orgnpc->get_bulletin());
		return 1;
	}
	if (sscanf(arg, "@ %s", name) == 1) // 同意创建帮派
	{
		if (!CHECK_D->is_legal_org(me, name))
			return 1;

		name2 = sprintf("org.%s", name);

		if (CITY_QI->get_save_2(name2) || CITY_HAN->get_save_2(name2) || CITY_ZHAO->get_save_2(name2) || CITY_WEI->get_save_2(name2) || CITY_QIN->get_save_2(name2) || CITY_CHU->get_save_2(name2) || CITY_YAN->get_save_2(name2))
		{
			notify("“%s” đã tồn tại", name);
			return 1;
		}
		size = strlen(name);
		if (size == 0)
			return 1;
		for (i = 0; i < size; i++)
			if (name[i] == '.')
			{
				notify("“%s” sai quy định", name);
				return 1;
			}
		if (!(city = CITY_D->get_city_object(me)))
			return 1;

		if (!objectp(obj = present("Tù Và Đế Vương", me, 1, MAX_CARRY * 4)))
		{
			return 1;
		}

		obj->remove_from_user(); // Xóa bỏ “Tù Và Đế Vương”
		destruct(obj);
		switch (me->get_city_name())
		{
		case "Tề Quốc":
			vitri = 1;
			break;
		case "Hàn Quốc":
			vitri = 2;
			break;
		case "Triệu Quốc":
			vitri = 3;
			break;
		case "Ngụy Quốc":
			vitri = 4;
			break;
		case "Tần Quốc":
			vitri = 5;
			break;
		case "Sở Quốc":
			vitri = 6;
			break;
		case "Yên Quốc":
			vitri = 7;
			break;

		default:
			break;
			vitri = 0;
		}
		if (vitri > 0)
		{
			for (i = 0; i < sizeof(list); i++)
			{
				if (kenh == to_int(list[i]))
					continue;
				ghi_file(sprintf("bang/check%s.txt", list[i]), sprintf("\nloadbang %d ", vitri));
			}
		}

		me->set_org_position(9);
		me->set_org_name(name);
		me->set_org_title("Bang Chủ");
		me->add_title("C001");
		me->show_title("C001");
		me->set_org_time(time());
		send_user(me, "%c%c%c%s", 0x3d, 49,
				  me->get_org_position(), me->get_org_name());
		if ("/sys/sys/count"->get_firstorg() == 0)
		{
			me->add_title("Z008");
			"/sys/sys/count"->set_firstorg(1);
			"/sys/sys/count"->save();
		}
		z = get_z(me);
		x = get_x(me);
		y = get_y(me);
		city->set_save_2(name2, sprintf("%d,%d", x, y));
		city->save();

		npc = new (MANAGER);
		npc->set_name(sprintf(" %s Tổng Quản", name));
		npc->set_city_name(me->get_city_name());
		npc->set_org_name(name);

		npc->set_master(me->get_number());
		npc->set_master_name(me->get_name());
		npc->set_master_id(me->get_id());
		npc->set_creator(me->get_name());
		npc->set_create_time(time());
		npc->set_master_name_2("－－");
		npc->set_develop(0);
		npc->set_gold(0);
		npc->set_total(size);
		npc->set_tenet("");
		npc->set_bulletin("");
		npc->set_grade(1);
		npc->set_house(1);
		npc->set_stable(1000);
		npc->set_favour(1000);
		npc->set_science(1);
		npc->set_producttime(time() + 12 * 3600);
		npc->check_skill();

		npc->init_member_info(me->get_number(), me->get_id(), me->get_name(),
							  me->get_armor_code(), me->get_gender(), me->get_level(),
							  me->get_fam_name(),
							  me->get_org_title(), time(), 0);

		result = sprintf(" %s bạn sáng lập “ %s ”!", short_time(time()), name);
		me->log_legend(result);
		npc->save();

		CITY_ZHOU->set_2(sprintf("org.%s", name), npc); // 要同 /map/city/* 中同步

		char = city->get("manager");
		if (!arrayp(char))
			char = ({npc});
		else
			char = char + ({npc}) - ({0});
		city->set("manager", char);

		result = sprintf(" %s ( %d ) sáng lập “ %s ”!", me->get_name(), me->get_number(), name);
		USER_D->user_channel(result);
		FAMILY_D->city_channel(me->get_city_name(), 0, sprintf(CHAT "Chúc mừng %s sáng lập %s", me->get_name(), name));
	}
	args = explode(arg, " ");
	if (sizeof(args) != 2)
		return 1;
	if (args[0] == "info")
	{
		name = me->get_org_name();
		if (!name || name == "")
			return 1;
		orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
		if (!objectp(orgnpc))
			return 1;
		number = to_int(args[1]);
		if (orgnpc->get_member_family(number))
			send_user(me, "%c%c%d%c%d%d%s", 0x95, 92, number,
					  orgnpc->get_member_gender(number), orgnpc->get_photo(number),
					  orgnpc->get_member_quit(number), orgnpc->get_member_family(number));
		else
			send_user(me, "%c%c%d%c%d%d%c", 0x95, 92, number,
					  orgnpc->get_member_gender(number), orgnpc->get_photo(number),
					  orgnpc->get_member_quit(number), 0);

		return 1;
	}
	if (args[0] == "invite" || args[0] == "join")
	{
		who = find_player(args[1]);
		if (!who)
		{
			notify("Không tìm thấy người này");
			return 1;
		}
		name = me->get_name();
		name2 = who->get_name();
		name = replace_string(name, "#", "＃");
		name2 = replace_string(name2, "#", "＃");
	}
	switch (args[0])
	{
	case "invite":
		if (me->get_org_position() < ORG_XIANGZHU)
		{
			notify("Địa vị trong Bang của ngươi không đủ");
			return 1;
		}
		if (who->get_org_name() != "" && who->get_org_position() > 0)
		{
			notify("Đối phương đã có Bang phái, không thể mời vào");
			return 1;
		}
		if ((who->get_city_name() != "") && who->get_city_name() != me->get_city_name())
		{
			notify("Đối phương đã gia nhập nước khác, không thể nhận lời mời");
			return 1;
		}
		orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", me->get_org_name()));
		if (!objectp(orgnpc))
		{
			notify("Bang Phái số liệu xảy ra vấn đề");
			return 1;
		}
		if (orgnpc->sizeof_member_dbase() >= orgnpc->get_max_number())
		{
			notify("Thành viên Bang Phái đã đạt số lượng tối đa");
			return 1;
		}
		me->set("orginvite", who);
		send_user(who, "%c%c%s", 0x59, 1, sprintf("%s %s (%d) mời gia nhập Bang, đồng ý không ?\n" ESC "%c\n" ESC "org join %d\n", me->get_org_name(), name, me->get_number(), 1, me->get_number()));
		printf(ECHO "Bạn mời %s (%d) gia nhập Bang, chờ hắn trả lời", name2, who->get_number());
		break;
	case "join":
		if (me != who->get("orginvite"))
		{
			notify("Bạn không được mời gia nhập");
			return 1;
		}
		if (who->get_org_position() < ORG_XIANGZHU)
		{
			notify("Đối phương ở trong Bang địa vị không đủ");
			return 1;
		}
		if (me->get_org_name() != "" && me->get_org_position() > 0)
		{
			notify("Bạn đã có Bang Phái, không thể nhận lời mời");
			return 1;
		}
		if ((me->get_city_name() != "") && who->get_city_name() != me->get_city_name())
		{
			notify("Đối phương đã gia nhập nước khác, bạn không thể gia nhập");
			return 1;
		}
		orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", who->get_org_name()));
		if (!objectp(orgnpc))
		{
			notify("Đối phương Bang Phái số liệu xảy ra vấn đề");
			return 1;
		}
		if (orgnpc->sizeof_member_dbase() >= orgnpc->get_max_number())
		{
			notify("Đối phương cho biết thành viên Bang Phái đã đạt số lượng tối đa");
			return 1;
		}
		if (me->get_city_name() == 0 || me->get_city_name() == "")
		{
			me->set_city_name(who->get_city_name());
			me->set_city_position(1);
			me->set_city_time(time());
			me->log_legend(sprintf("Bạn gia nhập %s", who->get_city_name()));
			printf(ECHO "Bạn gia nhập %s.", who->get_city_name());
		}
		if (me->get_org_name() != "") // 删掉申请信息
		{
			npc = CITY_ZHOU->get_2(sprintf("org.%s", me->get_org_name()));
			if (npc)
			{
				npc->delete_join_info(me->get_number());
			}
		}
		me->set_org_position(ORG_MEMBER);
		me->set_org_name(who->get_org_name());
		me->set_org_title("－－");
		me->set_org_time(time());
		me->add_title("C008");
		me->show_title("C008");
		send_user(me, "%c%c%c%s", 0x3d, 49,
				  me->get_org_position(), me->get_org_name());
		me->log_legend(sprintf("Bạn gia nhập “%s”！", who->get_org_name()));
		orgnpc->init_member_info(me->get_number(), me->get_id(), me->get_name(),
								 me->get_armor_code(), me->get_gender(), me->get_level(),
								 me->get_fam_name(),
								 me->get_org_title(), time(), 0);
		orgnpc->add_total(1);
		orgnpc->save();
		FAMILY_D->org_channel(me->get_org_name(), 0, sprintf(HIR "%s tiếp nhận %s (%d) gia nhập bổn bang !", who->get_name(), me->get_name(), me->get_number()));
		break;
	case "accept":
	case "refuse":
	case "banish":
	case "demise":
	case "appoint":
		name = me->get_org_name();
		orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
		if (!objectp(orgnpc))
			return 1;
		position = me->get_org_position();
		if (position == 0)
			return 1;
		result = sprintf("%x# %s.%s", getoid(orgnpc), args[0], args[1]);
		"/cmd/user/talk"->main(me, result);
		break;
	}
	return 1;
}
