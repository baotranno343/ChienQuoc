#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <effect.h>

inherit OFFICER;
int host_type;
void reset();
// 函数：获取人物造型
int get_char_picid() { return 5201; }
void do_welcome(string arg);
void do_accept(string arg);
void do_query(string arg);

// 函数：构造处理
void create()
{
	object me = this_object();
	set_name("Phá Thiên Tháp Truyền Tống");
	set_2("talk", (["welcome":(
								  : do_welcome:),
					  "accept":(
								   : do_accept:),
	]));
	setup();
}

void do_look(object who)
{
	int id;
	object me = this_object();

	id = getoid(me);
	send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Phá Thiên Tháp Truyền Tống :\nPhá Thiên Tháp là nơi trung gian, giao giữa tam giới với nhau. Nơi đây rất nhiều yêu ma chướng khí, đỉnh tháp cao trùng trùng. Bên trong là vô vàn quái vật với sức mạnh kinh người, nhiều người đã tiến vào thăm dò nhưng không thấy quay trở về. Các ngươi có muốn mạo hiểm một phen không?\n" ESC "Tiến vào Phá Thiên Tháp\ntalk %x# welcome.1\n" ESC "Rời khỏi", id, id, id));
}

void do_welcome(string arg)
{
	object me = this_object();
	__FILE__->do_welcome2(me, arg);
}

void do_welcome2(object me, string arg)
{
	int z, x, y, p;
	int flag, i, id, tId, *nXy, level, iTime, iDay, size, tid;
	string legend, result;

	object who, item, map, *team, npc;
	mixed *mxTime;
	iTime = time();
	mxTime = localtime(iTime);
	iDay = mxTime[TIME_YDAY];
	who = this_player();
	flag = to_int(arg);

	//	level = who->get_level();
	who->set_time("talk", 0);
	id = getoid(me);
	switch (flag)
	{
	case 1:
		send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Phá Thiên Tháp Truyền Tống :\nMỗi nhân vật sẽ được tham gia phó bản miễn phí 1 lần trong ngày. Nếu sở hữu Phá Thiên Lệnh, ta có thể phá lệ cho ngươi thám hiểm thêm một lần nữa !\n" ESC "Tiến vào\ntalk %x# welcome.11\n" ESC "Rời khỏi", id));
		break;

	case 11:
	{
		team = who->get_team();
		size = sizeof(team);

		if (!who->is_leader())

		{
			result = sprintf(me->get_name() + ":\nHãy gọi đội trưởng tới gặp ta !\n");
			result += sprintf(ESC "Rời khỏi");
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
			return;
		}
		if (size < 2)
		{
			result = sprintf(me->get_name() + ":\nĐội nhóm của ngươi phải từ 2 người trở lên !\n");
			result += sprintf(ESC "Rời khỏi");
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
			return;
		}
		for (i = 0; i < size; i++)
		{
			if (!objectp(team[i]))
				continue;
			if (!inside_screen_2(me, team[i]))
			{
				result = sprintf(me->get_name() + ":\nHãy gọi tất cả thành viên trong nhóm đến gặp ta !\n");
				result += sprintf(ESC "Rời khỏi");
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
				return;
			}
			if (team[i]->get_level() < 60)
			{
				result = sprintf(me->get_name() + ":\nThành viên trong nhóm của ngươi %s cấp bậc chưa đủ 60 cấp trở lên !\n", team[i]->get_name());
				result += sprintf(ESC "Rời khỏi");
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
				return;
			}
			if (team[i]->get_save_2("ptt.check_thap") == iDay)
			{
				if (team[i]->get_save_2("ptt.phathienlenh") == iDay)
				{
					result = sprintf(me->get_name() + ":\nĐội nhóm của ngươi có người đã đi thám hiểm 2 lần Phá Thiên Tháp rồi !\n");
					result += sprintf(ESC "Rời khỏi");
					send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
					return;
				}
				else
				{

					if (TASK_LEGEND_D->check_task_item_amount(team[i], "Phá Thiên Lệnh") < 1)
					{
						result = sprintf(me->get_name() + ":\nTrong tổ đội của ngươi có người đã tham gia phó bản rồi. Nếu muốn tham gia thêm một lần nữa hãy nói hắn giao cho ta Phá Thiên Lệnh !\n");
						result += sprintf(ESC "Rời khỏi");
						send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
						return;
					}
				}
			}
		}

		for (i = 0; i < size; i++)
		{
			level = level + team[i]->get_level();
			if (team[i]->get_save_2("ptt.check_thap") == iDay && team[i]->get_save_2("ptt.phathienlenh") != iDay)
			{

				TASK_LEGEND_D->check_task_item1(team[i], "Phá Thiên Lệnh", 1);
				team[i]->set_save_2("ptt.phathienlenh", iDay);
			}
		}
		level = level / size;
		tid = who->get("team_id");
		if ((z = find_map_flag(1000, 2999, 0)) > 0)
		{
			p = 894;
			init_virtual_map(z, p); // 生成虚拟地图
			map = new ("/ken/pb/map");
			map->set_name("Chiến Quốc Trận");
			map->set_client_id(p);
			set_map_object(map, map->set_id(z));
			map->set("S", 1);
		}
		if (!map) //创建副本
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Đã hết map trống, quay lại sau\n" ESC "OK");
			return;
		}
		for (i = 0; i < 20; i++)
		{
			npc = new ("ken/pb/pbquai");
			if (!npc)
			{
				continue;
			}
			else
			{
				npc->set_level(level);
				npc->init(1);
			}
			if (!(p = efun::get_xy_point(894, IS_CHAR_BLOCK)))
				continue;
			x = (p % 1000000) / 1000;
			y = p % 1000;
			npc->add_to_scene(z, x, y);
			map->add("amount", 1);
		}
		for (i = 0; i < sizeof(team); i++)
		{
			if (!(p = efun::get_xy_point(894, IS_CHAR_BLOCK)))
				continue;
			x = (p % 1000000) / 1000;
			y = p % 1000;
			team[i]->add_to_scene(z, x, y);

			team[i]->set_save_2("ptt.check_thap", iDay);
		}
		break;
	}
	}
}
