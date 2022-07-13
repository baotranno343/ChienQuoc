#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <effect.h>

inherit OFFICER;

// 函数:获取人物造型
int get_char_picid() { return 0450; }
void do_welcome(string arg);
void do_accept(string arg);
void do_query(string arg);

// 函数:构造处理
void create()
{
	object me = this_object();
	set_name("Đào Vong Khổ Dịch");
	set_2("talk", (["welcome":(
								  : do_welcome:),
					  "accept":(
								   : do_accept:),
					   "query":(
								   : do_query:),
	]));
	set_head_color(0x39eb);
	setup();
}

void do_look(object who)
{
	int id, level;
	object me = this_object();

	id = getoid(me);
	level = who->get_level();
	if (MAIN_D->get_host_type() == 6012)
	{
		send_user(who, "%c%s", '!', "副本系统尚未开放！");
		return;
	}
	if (level > 90 && !who->get_vip())
		send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Đào Vong Khổ Dịch:\n    Làm việc tại Lăng Ly Sơn này quả thực chẳng bằng heo chó, khó khăn lắm ta mới trốn thoát được, ta đã thề nhất định phải báo thù, nếu ngươi muốn vào báo thú rửa hận giùm ta thì ta có thể dẫn đường, nhưng ngươi nhất định phải bảo vệ ta an toàn !\n" ESC "Sử dụng Hạt Mè Khai Môn tiến vào\ntalk %x# welcome.85\n" ESC "Lăng Ly Sơn là nơi nào ?\ntalk %x# welcome.47\n" ESC "Tìm hiểu quy tắc\ntalk %x# welcome.109\n" ESC "Rời khỏi", id, id, id));
	else
		send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Đào Vong Khổ Dịch:\n    Làm việc tại Lăng Ly Sơn này quả thực chẳng bằng heo chó, khó khăn lắm ta mới trốn thoát được, ta đã thề nhất định phải báo thù, nếu ngươi muốn vào báo thú rửa hận giùm ta thì ta có thể dẫn đường, nhưng ngươi nhất định phải bảo vệ ta an toàn !\n" ESC "Tiến vào Lăng Ly Sơn\ntalk %x# welcome.72\n" ESC "Lăng Ly Sơn là nơi nào ?\ntalk %x# welcome.47\n" ESC "Tìm hiểu quy tắc\ntalk %x# welcome.109\n" ESC "Rời khỏi", id, id, id));
}

void do_welcome(string arg)
{
	object me = this_object();
	__FILE__->do_welcome2(me, arg);
}

void do_welcome2(object me, string arg)
{
	int flag, i, id, tId, *nXy, level;
	object who, item, map;
	string legend;
	who = this_player();
	flag = to_int(arg);
	level = who->get_level();
	who->set_time("talk", 0);
	id = getoid(me);
	if (MAIN_D->get_host_type() == 6012)
	{
		send_user(who, "%c%s", '!', "副本系统尚未开放！");
		return;
	}
	switch (flag)
	{
	case 47:
		if (level > 90 && !who->get_vip())
			send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Đào Vong Khổ Dịch:\n    Lăng Ly Sơn là một ngôi mộ chứa rất nhiều điều bí ẩn đang chờ đợi mọi người vào khám phá, bên trong có rất nhiều quái vật cao cấp và nghe nói khi tiêu diệt chúng sẽ nhận được nhiều trang bị quý hiếm !\n" ESC "Tìm hiểu quy tắc\ntalk %x# welcome.109\n" ESC "Sử dụng Hạt Mè Khai Môn tiến vào\ntalk %x# welcome.85\n" ESC "Rời khỏi", id, id, ));
		else
			send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Đào Vong Khổ Dịch:\n    Lăng Ly Sơn là một ngôi mộ chứa rất nhiều điều bí ẩn đang chờ đợi mọi người vào khám phá, bên trong có rất nhiều quái vật cao cấp và nghe nói khi tiêu diệt chúng sẽ nhận được nhiều trang bị quý hiếm !\n" ESC "Tìm hiểu quy tắc\ntalk %x# welcome.109\n" ESC "Tiến vào Lăng Ly Sơn\ntalk %x# welcome.72\n" ESC "Rời khỏi", id, id, ));

		break;
	case 109:
		if ((level >= 70 && level <= 90) || (level > 90 && who->get_vip()))
			send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Đào Vong Khổ Dịch:\n    Để tiến vào Lăng Ly Sơn người chơi phải lập nhóm, mỗi một nhóm cho phép tối đa " HIR "5 người" NOR ". Người chơi phải đạt cấp bật" HIR " 70-90" NOR " mới có thể tiến vào.\n" ESC "Tiến vào Lăng Ly Sơn\ntalk %x# welcome.72\n" ESC "Rời khỏi", id, ));
		else
			send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), "Đào Vong Khổ Dịch:\n    Để tiến vào Lăng Ly Sơn người chơi phải lập nhóm, mỗi một nhóm cho phép tối đa " HIR "5 người" NOR ". Người chơi phải đạt cấp bật" HIR " 70-90" NOR " mới có thể tiến vào.\n" ESC "Rời khỏi");
		break;
	case 72:
		if (level < 70 || (level > 90 && !who->get_vip()))
		{
			send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), "Đào Vong Khổ Dịch:\n    Để tiến vào Lăng Ly Sơn người chơi phải lập nhóm, mỗi một nhóm cho phép tối đa " HIR "5 người" NOR ". Người chơi phải đạt cấp bật" HIR " 70-90" NOR " mới có thể tiến vào.\n" ESC "Rời khỏi");
			return;
		}
		tId = who->get_team_id();
		if (!tId)
		{
			send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Đào Vong Khổ Dịch:\n    Quái vật trong Lăng Ly Sơn rất lợi hại, nếu ngươi muốn vào thì tốt nhất là hãy đi cùng đội nhóm của mình.\n"));
			return;
		}

		if (tId)
		{
			map = TEAM_D->get_copy_scene(tId, COPY_TOMB1);
			if (!map) //创建副本
			{
				map = "sys/copy/tomb"->new_copy_tomb1(me, who);
			}
			if (!map)
				return;
			nXy = map->get("entrance1");
			send_user(who, "%c%c%w%s", 0x5a, 0, 1, "Truyền tống……");
			who->set_2("travel.z", map->get_id());
			who->set_2("travel.p", nXy[0] * 1000 + nXy[1]);
			set_effect(who, EFFECT_TRAVEL, 1);
		}
		break;
	case 85:
		if (level <= 90 || (level > 90 && who->get_vip()))
			return;
		//	if ( level < 70 ) return ;
		item = present("Hạt Mè Khai Môn", who, 1, MAX_CARRY * 4);
		if (!item)
		{
			send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Đào Vong Khổ Dịch:\n    Nhân vật cấp 70-90 có thể tiến vào Lăng Ly Sơn, nếu cấp bậc vượt qua 90 phải sử dụng 1 Hạt Mè Khai Môn mới có thể tiến vào.\n"));
			return;
		}
		tId = who->get_team_id();
		if (!tId)
		{
			send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Đào Vong Khổ Dịch:\n    Quái vật trong Lăng Ly Sơn rất lợi hại, nếu ngươi muốn vào thì tốt nhất là hãy đi cùng đội nhóm của mình.\n"));
			return;
		}
		send_user(who, "%c%c%s", 0x59, 1, sprintf("Bạn sử dụng " HIR "Hạt Mè Khai Môn" NOR " tiến vào Lăng Ly Sơn\n" ESC "%c\n" ESC "talk %x# welcome.95\n", 1, getoid(me)));
		break;
	case 95:
		if (level <= 90 || (level > 90 && who->get_vip()))
			return;
		//	if ( level < 70 ) return ;
		item = present("Hạt Mè Khai Môn", who, 1, MAX_CARRY * 4);
		if (!item)
		{
			send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Đào Vong Khổ Dịch:\n    Nhân vật cấp 70-90 có thể tiến vào Lăng Ly Sơn, nếu cấp bậc vượt qua 90 phải sử dụng 1 Hạt Mè Khai Môn mới có thể tiến vào.\n"));
			return;
		}
		tId = who->get_team_id();
		if (!tId)
		{
			send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Đào Vong Khổ Dịch:\n    Quái vật trong Lăng Ly Sơn rất lợi hại, nếu ngươi muốn vào thì tốt nhất là hãy đi cùng đội nhóm của mình.\n"));
			return;
		}
		legend = sprintf("进入副本使用 %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", who->get_name(), who->get_number(), get_ip_name(who), who->get_id(), me->get_name(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), 1, item->get_user_id(), get_z(who), get_x(who), get_y(who));
		//"/sys/user/cmd"->log_item(legend);
		//	item->remove_from_user();
		//	destruct(item);
		item->add_amount(-1);
		if (tId)
		{
			map = TEAM_D->get_copy_scene(tId, COPY_TOMB1);
			if (!map) //创建副本
			{
				map = "sys/copy/tomb"->new_copy_tomb1(me, who);
			}
			if (!map)
				return;
			nXy = map->get("entrance1");
			send_user(who, "%c%c%w%s", 0x5a, 0, 1, "Truyền tống……");
			who->set_2("travel.z", map->get_id());
			who->set_2("travel.p", nXy[0] * 1000 + nXy[1]);
			set_effect(who, EFFECT_TRAVEL, 1);
		}
		break;
	}
}
