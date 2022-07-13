#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <effect.h>
#define IDMAP 891
inherit OFFICER;
int host_type;
int open = 1;
void reset();
// 函数：获取人物造型
int get_char_picid() { return 6009; }
void do_welcome(string arg);
void do_accept(string arg);
void do_query(string arg);
int set_open(int i) { return open = i; }
int get_open() { return open; }
// 函数：构造处理
void create()
{
	object me = this_object();
	set_name(HIG "Loạn Sơn Kê");
	set_real_name("Trị Liệu Tiên Tử");
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
	send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Trị Liệu Tiên Tử :\nLoạn Sơn Kê có rất nhiều động vật, ngươi có muốn biết về nó không?!\n"
																				//
																				ESC HIG "Tham Gia Loạn Sơn Kê\ntalk %x# welcome.1\n"
																				//
																				ESC "Hưỡng Dẫn Chơi\ntalk %x# welcome.2\n"
																				//
																				ESC "Rời khỏi",
																				id, id, id));
}

void do_welcome(string arg)
{
	object me = this_object();
	__FILE__->do_welcome2(me, arg);
}

void do_welcome2(object me, string arg)
{
	int z, x, y, p, move;
	int flag, i, id, tId, *nXy, level, iTime, iDay, size, tid;
	string legend, result;

	object who, item, map, *team, npc, present;
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
		if (get_open() == 1)
		{

			send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Trị Liệu Tiên Tử:\nNhân vật sẽ được tham gia phó bản Loạn Sơn Kê khi đến khung giờ!\n"
																						//
																						ESC "Tiến vào\ntalk %x# welcome.11\n"
																						//
																						ESC "Rời khỏi",
																						id));
		}
		else
		{
			send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Trị Liệu Tiên Tử:\nChưa tới thời gian tham gia Phó Bản\n"
																						//

																						//
																						ESC "Rời khỏi",
																						id));
		}
		break;
	case 2:
		send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Trị Liệu Tiên Tử:\nThời gian của phó bản sẽ kéo dài 1 phút 30 giây, khi vào phó bản ngươi chơi sẽ được tặng Dây Bắt Gà, hãy dùng nó để bắt Sơn Kê. Nếu người chơi bắt thỏ hoang sẽ không được điểm, hãy cẩn thận Ong Độc nó sẽ làm bật bị trừ điểm! \nKhi kết thúc Phó Bản Dây Bắt Gà sẽ biến mất người chơi sẽ được đưa ra ngoài và phần thưởng sẽ tự động cộng vào nhân vật.\n"
																					//

																					//
																					ESC "Rời khỏi",
																					id));
		break;
	case 11:
	{
		if (get_open() == 0)
		{
			return;
		}
		team = who->get_team();
		size = sizeof(team);

		if (size > 1)
		{
			result = sprintf(me->get_name() + ":\nNgươi không được đi cùng với đội nhóm của mình !\n");
			result += sprintf(ESC "Rời khỏi");
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
			return;
		}
		if (who->get_level() < 10)
		{
			result = me->get_name() + "：\n  Đẳng cấp 10 trở lên mới có thể tham gia Loạn Sơn Kê\n";
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
			return;
		}
		if (who->get_save("lsk") == iDay)
		{
			result = me->get_name() + "：\n  Bạn đã tham gia Loạn Sơn Kê hôm nay rồi!\n";
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 2)
		{
			result = sprintf(me->get_name() + ":\nKhông đủ 2 chỗ trống!\n");
			result += sprintf(ESC "Rời khỏi");
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
			return;
		}
		if ((z = find_map_flag(1000, 2999, 0)) > 0)
		{
			p = IDMAP;
			init_virtual_map(z, p); // 生成虚拟地图
			map = new ("/tran/loansonke/map");
			map->set_name("Loạn Sơn Kê");
			map->set_client_id(p);
			set_map_object(map, map->set_id(z));
		}
		if (!map) //创建副本
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Đã hết map trống, quay lại sau\n" ESC "OK");
			return;
		}

		if (!(p = efun::get_xy_point(IDMAP, IS_CHAR_BLOCK)))
			return;
		x = (p % 1000000) / 1000;
		y = p % 1000;
		who->set_save("lsk", iDay);
		who->add_to_scene(z, x, y);
		me->check_outmap(125, who, z);
		if (objectp(item = present("Dây Bắt Gà", who, 1, MAX_CARRY)) && item->get_amount() < 5000)
		{
			item->set_amount(100);
		}
		else
		{
			present = new ("tran/loansonke/daybatga");
			if (!present)
			{
				return;
			}
			if (move = present->move2(who, -1))
			{
				present->set_amount(100);
				present->add_to_user(move);
			}
			else
			{
				destruct(present);
				return;
			}
		}

		break;
	}
	}
	return;
}
void check_outmap(int sec, object who, int z)
{
	object npc, item;
	int i, x, y, p, exp, cashkhoa;
	sec -= 5;

	//send_user(get_range_object_2(who, 10, USER_TYPE), "%c%c%d%s", 0x43, 10, who->get_number(), CHAT + HIR "Phó bản Loạn Sơn Kê" HIG " có thời gian là 1 phút 30 giây, trong thời gian	quy định càng bắt được nhiều " HIR "Sơn Kê" HIG " càng tích được nhiều điểm.");
	//CHAT_D->sys_channel(0, HIR "Phó bản Loạn Sơn Kê" HIG " có thời gian là 1 phút 30 giây, trong thời gian	quy định càng bắt được nhiều " HIR "Sơn Kê" HIG " càng tích được nhiều điểm.");
	if (who)
	{
		if (get_z(who) != z)
		{
			remove_call_out("check_outmap");
			return;
		}

		if (sec > 0)
		{
			if (sec == 120)
				send_user(get_range_object_2(who, 10, USER_TYPE), "%c%c%d%s", 0x43, 10, who->get_number(), CHAT + HIR "Phó bản Loạn Sơn Kê" HIG " có thời gian là 1 phút 30 giây, trong thời gian	quy định càng bắt được nhiều " HIR "Sơn Kê" HIG " càng tích được nhiều điểm.");
			if (sec == 110)
				send_user(get_range_object_2(who, 10, USER_TYPE), "%c%c%d%s", 0x43, 10, who->get_number(), CHAT + HIG "Bắt được " HIR "Cự Hình Kê " HIG "sẽ nhận được nhiều điểm tích hơn, tuy nhiên tỷ lệ bắt thành công không cao, bắt càng nhiều lần tỷ lệ thành công sẽ càng cao.");
			if (sec == 100)
				send_user(get_range_object_2(who, 10, USER_TYPE), "%c%c%d%s", 0x43, 10, who->get_number(), CHAT + HIG "Cẩn thận nếu bắt nhầm " HIR "Ong Độc" HIG ", bị " HIR "Ong Độc" HIG " tấn công sẽ bị trừ tích điểm.");
			if (sec > 90)
			{
				tell_user(who, "Phó bản sẽ bắt đầu sau %d giây", sec - 90);
			}
			if (sec == 90)
			{
				notify("Bắt Đầu");
				tell_user(who, HIR "Bắt Đầu");
				for (i = 0; i < 5; i++)
				{
					npc = new ("tran/loansonke/cuhinhke");
					if (!npc)
					{

						continue;
					}

					if (!(p = efun::get_xy_point(IDMAP, IS_CHAR_BLOCK)))
					{
						continue;
					}

					x = (p % 1000000) / 1000;
					y = p % 1000;
					npc->add_to_scene(z, x, y);
				}
				for (i = 0; i < 10; i++)
				{
					npc = new ("tran/loansonke/sonke");
					if (!npc)
					{

						continue;
					}
					if (!(p = efun::get_xy_point(IDMAP, IS_CHAR_BLOCK)))
					{
						continue;
					}
					x = (p % 1000000) / 1000;
					y = p % 1000;
					npc->add_to_scene(z, x, y);
				}
				for (i = 0; i < 10; i++)
				{
					npc = new ("tran/loansonke/thohoang");
					if (!npc)
					{

						continue;
					}
					if (!(p = efun::get_xy_point(IDMAP, IS_CHAR_BLOCK)))
					{
						continue;
					}
					x = (p % 1000000) / 1000;
					y = p % 1000;
					npc->add_to_scene(z, x, y);
				}
				for (i = 0; i < 5; i++)
				{
					npc = new ("tran/loansonke/ongdoc");
					if (!npc)
					{

						continue;
					}
					if (!(p = efun::get_xy_point(IDMAP, IS_CHAR_BLOCK)))
					{
						continue;
					}
					x = (p % 1000000) / 1000;
					y = p % 1000;
					npc->add_to_scene(z, x, y);
				}
			}
			if (sec == 70)
			{
				for (i = 0; i < 2; i++)
				{
					npc = new ("tran/loansonke/cuhinhke");
					if (!npc)
					{

						continue;
					}
					if (!(p = efun::get_xy_point(IDMAP, IS_CHAR_BLOCK)))
					{
						continue;
					}
					x = (p % 1000000) / 1000;
					y = p % 1000;
					npc->add_to_scene(z, x, y);
				}
				for (i = 0; i < 5; i++)
				{
					npc = new ("tran/loansonke/sonke");
					if (!npc)
					{

						continue;
					}
					if (!(p = efun::get_xy_point(IDMAP, IS_CHAR_BLOCK)))
					{
						continue;
					}
					x = (p % 1000000) / 1000;
					y = p % 1000;
					npc->add_to_scene(z, x, y);
				}
				for (i = 0; i < 5; i++)
				{
					npc = new ("tran/loansonke/thohoang");
					if (!npc)
					{

						continue;
					}
					if (!(p = efun::get_xy_point(IDMAP, IS_CHAR_BLOCK)))
					{
						continue;
					}
					x = (p % 1000000) / 1000;
					y = p % 1000;
					npc->add_to_scene(z, x, y);
				}
				for (i = 0; i < 2; i++)
				{
					npc = new ("tran/loansonke/ongdoc");
					if (!npc)
					{

						continue;
					}
					if (!(p = efun::get_xy_point(IDMAP, IS_CHAR_BLOCK)))
					{
						continue;
					}
					x = (p % 1000000) / 1000;
					y = p % 1000;
					npc->add_to_scene(z, x, y);
				}
			}
			if (sec == 50)
			{
				for (i = 0; i < 2; i++)
				{
					npc = new ("tran/loansonke/cuhinhke");
					if (!npc)
					{

						continue;
					}
					if (!(p = efun::get_xy_point(IDMAP, IS_CHAR_BLOCK)))
					{
						continue;
					}
					x = (p % 1000000) / 1000;
					y = p % 1000;
					npc->add_to_scene(z, x, y);
				}
				for (i = 0; i < 5; i++)
				{
					npc = new ("tran/loansonke/sonke");
					if (!npc)
					{

						continue;
					}
					if (!(p = efun::get_xy_point(IDMAP, IS_CHAR_BLOCK)))
					{
						continue;
					}
					x = (p % 1000000) / 1000;
					y = p % 1000;
					npc->add_to_scene(z, x, y);
				}
				for (i = 0; i < 5; i++)
				{
					npc = new ("tran/loansonke/thohoang");
					if (!npc)
					{

						continue;
					}
					if (!(p = efun::get_xy_point(IDMAP, IS_CHAR_BLOCK)))
					{
						continue;
					}
					x = (p % 1000000) / 1000;
					y = p % 1000;
					npc->add_to_scene(z, x, y);
				}
				for (i = 0; i < 2; i++)
				{
					npc = new ("tran/loansonke/ongdoc");
					if (!npc)
					{

						continue;
					}
					if (!(p = efun::get_xy_point(IDMAP, IS_CHAR_BLOCK)))
					{
						continue;
					}
					x = (p % 1000000) / 1000;
					y = p % 1000;
					npc->add_to_scene(z, x, y);
				}
			}
			if (sec == 30)
			{
				for (i = 0; i < 2; i++)
				{
					npc = new ("tran/loansonke/cuhinhke");
					if (!npc)
					{

						continue;
					}
					if (!(p = efun::get_xy_point(IDMAP, IS_CHAR_BLOCK)))
					{
						continue;
					}
					x = (p % 1000000) / 1000;
					y = p % 1000;
					npc->add_to_scene(z, x, y);
				}
				for (i = 0; i < 5; i++)
				{
					npc = new ("tran/loansonke/sonke");
					if (!npc)
					{

						continue;
					}
					if (!(p = efun::get_xy_point(IDMAP, IS_CHAR_BLOCK)))
					{
						continue;
					}
					x = (p % 1000000) / 1000;
					y = p % 1000;
					npc->add_to_scene(z, x, y);
				}
				for (i = 0; i < 5; i++)
				{
					npc = new ("tran/loansonke/thohoang");
					if (!npc)
					{

						continue;
					}
					if (!(p = efun::get_xy_point(IDMAP, IS_CHAR_BLOCK)))
					{
						continue;
					}
					x = (p % 1000000) / 1000;
					y = p % 1000;
					npc->add_to_scene(z, x, y);
				}
				for (i = 0; i < 2; i++)
				{
					npc = new ("tran/loansonke/ongdoc");
					if (!npc)
					{

						continue;
					}
					if (!(p = efun::get_xy_point(IDMAP, IS_CHAR_BLOCK)))
					{
						continue;
					}
					x = (p % 1000000) / 1000;
					y = p % 1000;
					npc->add_to_scene(z, x, y);
				}
			}
			if (sec <= 20)
			{
				tell_user(who, "Phó bản sẽ kết thúc sau %d giây", sec);
			}

			call_out("check_outmap", 5, sec, who, z);
			return;
		}
		else
		{
			remove_call_out("check_outmap");
			if (objectp(item = present("Dây Bắt Gà", who, 1, MAX_CARRY * 4)))
			{
				item->remove_from_user();
				destruct(item);
			}
			if (who->get("diemlsk"))
			{
				if (who->get("diemlsk") >= 40)
				{
					exp = USER_EXP_D->get_level_exp(who->get_reincarnation(), who->get_level()) / 2;
				}
				else
				{
					exp = USER_EXP_D->get_level_exp(who->get_reincarnation(), who->get_level()) / 3;
				}

				cashkhoa = who->get("diemlsk") * 1700;
				who->add_exp(10000 + exp);
				who->add_cashkhoa(cashkhoa);
				send_user(who, "%c%s", ';', sprintf("Bạn đã hoàn thành Loạn Sơn Kê, bạn nhận được %d Kinh Nghiệm và %d Ngân Lượng Khóa", exp, cashkhoa));
				who->delete ("diemlsk");
			}
			who->add_to_scene(001, 151 + random(20), 129 + random(20));
			return;
		}
	}
	else
	{
		remove_call_out("check_outmap");
		return;
	}
	return;
}