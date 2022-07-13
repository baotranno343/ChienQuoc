
#include <npc.h>
#include <ansi.h>
#include <music.h>
#include <equip.h>
#include <task.h>

#define CRIMINAL "/npc/task/8000"
#define TREASURE "/item/std/8000"

//#define _CRIMINAL_TEST
#define TASK_TIME_LIMIT 1800

inherit OFFICER;

void do_quest();
void accept_task(); //nhan nv
void task_info();
void task_bonus(); //quà nhiem vu
void do_visit(string arg);
void do_thief(string arg);
void accept_thief();
void give_thief_bonus();
void do_treasure();
void get_hoe();

// 函数:获取人物造型
int get_char_picid() { return 5205; }

// 函数:构造处理
void create()
{
	set_name("Vương Bộ Đầu");

	set_2("talk", (["quest":(
								: do_quest()
								:),
							"accept":(
										 : accept_task()
										 :),
							  "info":(
										 : task_info()
										 :),
							 "bonus":(
										 : task_bonus()
										 :),
							 "visit":(
										 : do_visit:),
							 "thief":(
										 : do_thief:),
					  "accept_thief":(
										 : accept_thief:),
					   "bonus_thief":(
										 : give_thief_bonus:),
							   "hoe":(
										 : get_hoe:),
						  "treasure":(
										 : do_treasure:),

	]));
	setup();
	set("mpLegend", ([0:({
							32,
						}),
	]));
}

// 函数:对话处理
void do_look(object who)
{
	object npc, me = this_object();
	int id = getoid(me), i;
	string criminal, result;
	string cmd1 = sprintf("talk %x# quest\n", id);
	string cmd2 = sprintf("talk %x# info\n", id);
	string cmd3 = sprintf("talk %x# thief\n", id);
	string cmd4 = sprintf("talk %x# treasure\n", id);
	string tmp = "";

	if ((i = who->get_quest("thief.flag")) && (TASK_TIME_LIMIT - gone_time(who->get_quest("thief.time")) > 0))
	{
		if (i == 1)
			tmp = ESC "Giáo Huấn Tiểu Thâu\n" + cmd3;
		else if (i == 2)
			tmp = ESC "Tìm lại Vật Phẩm\n" + cmd3;
		else if (i == 3)
			tmp = ESC "Mua Vật Phẩm\n" + cmd3;
		else if (i == 4)
			tmp = ESC "Truy Nã Thiết Tặc\n" + cmd3;
	}
	else
		tmp = ESC "Nhiệm vụ của Vương Bộ Đầu.\n" + cmd3;
	/*
	如果活动时间还没有到或者活动时间已经结束，这里样的就不出现这个获取挖宝小锄头选项
	*/
	if (who->get_task("criminal.bonus") && (criminal = who->get_task("criminal.name")) && stringp(criminal))
		tmp += ESC + sprintf("Truy Nã %s.\n", criminal) + cmd2;
	else if (stringp(criminal = who->get_task("criminal")) && (npc = find_char(criminal)) && npc->is_criminal())
		tmp += ESC + sprintf("Truy Nã %s.\n", npc->get_name()) + cmd2;
	else
		tmp += ESC HIG "Truy Bắt Đào Phạm.\n" + cmd1;
	if (who->get_level() >= 10 && who->get_legend(TASK_2_00, 10) && !who->get_legend(TASK_2_00, 11))
		tmp += sprintf(ESC HIY "Nhiệm vụ Vương Bộ Đầu\ntalk %x# visit.1\n", getoid(this_object()));
	if (who->get_legend(TASK_2_00, 11) && !who->get_legend(TASK_2_00, 12))
		tmp += sprintf(ESC HIY "Gặp mặt Sư Gia\ntalk %x# visit.3\n", getoid(this_object()));
	if ("sys/party/treasure"->is_open())
	{
		tmp += ESC "Tối đa lấy trong Bảo Khố\n" + cmd4;
	}
	send_user(who, "%c%s", ':', sprintf(" %s :\n Thời gian trước bức tường ngục bị phá, vài tên tội phạm lợi dụng đào tẩu, Quan huyện ra sức truy bắt, ra lệnh cho ta phụ trách việc này, nếu ngươi muốn truy bắt tội phạm này, phải đưa cho ta 500 lượng trước, ta sẽ trao cơ hội tốt này cho, phần thưởng sẽ không ít đâu!\n" + tmp + ESC "Rời khỏi.\nCLOSE\n", get_name()));
}
//极限挖宝
void do_treasure()
{
	object me = this_object();
	object player = this_player();
	string tmp = "";
	string cmd4 = sprintf("talk %x# hoe\n", getoid(me));
	if ("sys/party/treasure"->is_open())
	{
		tmp += ESC "Lĩnh cái cuốc trong Bảo Khố\n" + cmd4;
		send_user(player, "%c%s", ':', get_name() + ":\n " HIR "每个星期六与星期日的16:00—17:00" NOR "，你都可以来我这里领取挖宝小锄头，" HIR "每次只可领取一把，但是次数无上限" NOR "，一个小时内挖宝小锄头任你领！\n" + tmp + ESC "Rời khỏi\nCLOSE\n");
	}
}
// 函数:任务处理
void do_quest()
{
	object me, who, npc, map, item;
	string criminal;
	int level, z, x, y, p;

	me = this_object();
	who = this_player();

	if (who->get_cash() < 500)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Trên người ngươi không có ngân lượng làm răng nhận truy bắt Đào Phạm được đây!!");
		return;
	}

	if (stringp(criminal = who->get_task("criminal")) && (npc = find_char(criminal)) && npc->is_criminal())
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Nhanh lùng bắt Đào Phạm đi !!");
		return;
	}
	if (gone_time(who->get_task("criminal.time")) < 180)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Khoảng cách nhận nhiệm vụ cách nhau 3 Phút. !!\n" ESC "Rời khỏi\nCLOSE\n");
		return;
	}
	level = who->get_level() - random(6);
	if (level < 0)
		level = 0;

	if (!(p = XY_D->get_city_point(-1, IS_CHAR_BLOCK)))
		return;

	z = p / 1000000;
	x = (p % 1000000) / 1000;
	y = p % 1000;

	if (!objectp(map = get_map_object(z)) || !map->is_scene())
		return;

	criminal = NPC_NAME_D->get_criminal_name();

	who->set("criminal.name", criminal);
	who->set("criminal.x", x);
	who->set("criminal.y", y);
	who->set("criminal.z", z);
	x = x + random(30) - 15;
	y = y + random(30) - 15;
	if (x < 1)
		x = 1;
	if (y < 1)
		y = 1;
	item = who->get_equip(HAND_TYPE);
	if (item && item->get_item_number() == 10001078)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + sprintf(": \n    Đạo Tặc " HIR "%s" NOR ".Nếu ngươi có Công Văn Truy Nã sẽ phát hiện" HIR "%s" NOR "đang ở đâu rất dễ dàng.Nếu ngươi có thể đem được Đào Phạm trở về ta sẽ thưởng cho ngươi! \n", criminal, criminal) + ESC "Nhận\n" + sprintf("talk %x# accept\n", getoid(me)) + ESC "Rời khỏi\n" + sprintf("talk %x# visit.cancel\n", getoid(me)));
	}
	else
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + sprintf(": \n    Đạo Tặc " HIR "%s" NOR ".Nếu ngươi có Công Văn Truy Nã sẽ phát hiện" HIR "%s" NOR "đang ở đâu rất dễ dàng.Nếu ngươi có thể đem được Đào Phạm trở về ta sẽ thưởng cho ngươi! \n", criminal, criminal) + ESC "Nhận\n" + sprintf("talk %x# accept\n", getoid(me)) + ESC "Rời khỏi\nCLOSE\n");
	}
	who->set("criminal.x1", x);
	who->set("criminal.y1", y);
}

void accept_task()
{
	object me, who, npc, map;
	string criminal;
	int level, z, x, y, p;

	me = this_object();
	who = this_player();

	if (who->get_cash() < 500)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Trên người ngươi không có ngân lượng làm răng nhận truy bắt Đào Phạm được đây!!");
		return;
	}

	if (stringp(criminal = who->get_task("criminal")) && (npc = find_char(criminal)) && npc->is_criminal())
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Nhanh lùng bắt Đào Phạm đi!!");
		return;
	}
	if (gone_time(who->get_task("criminal.time")) < 180)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Khoảng cách nhận nhiệm vụ cách nhau 3 Phút. !!\n" ESC "Rời khỏi\nCLOSE\n");
		return;
	}

	level = who->get_level() - random(6);

	if (level < 0)
		level = 0;
	x = who->get("criminal.x");
	y = who->get("criminal.y");
	z = who->get("criminal.z");
	criminal = who->get("criminal.name");
	if (!stringp(criminal) || !objectp(map = get_map_object(z)) || !map->is_scene())
		return;
	who->set_task("criminal.time", time());
	who->delete ("criminal.x");
	who->delete ("criminal.y");
	who->delete ("criminal.z");
	who->delete ("criminal.name");
	npc = new (CRIMINAL);
	npc->set_name("Trọng Phạm" + criminal);
	NPC_ENERGY_D->init_level(npc, level);
	npc->add_max_hp(5000);
	npc->add_dp(level * 150 / 10);
	npc->add_pp(level * 150 / 10);
	npc->add_ap(level * 150 / 10);
	npc->add_to_scene(z, x, y, 3);

	npc->set("user", ({sprintf("%d", who->get_number())}));
	map->add_reset(npc); // 加入复位列表

	who->add_cash(-500);

	who->add_gold_log("pay", 500);
	who->log_money("Trọng Phạm", -500);
	"/sys/sys/count"->add_use("criminal", 500);
	who->set_task("criminal", sprintf("%x#", getoid(npc)));
	who->set_task("criminal.x", who->get("criminal.x1"));
	who->set_task("criminal.y", who->get("criminal.y1"));
	//cấm bay
	//who->set_save("cambayquest", 1);
	//
	npc->set("task", who->get_number());
	npc->set("xy.z", z);
	npc->set("xy.x", x);
	npc->set("xy.y", y);
	npc->set("level", who->get_level());
	send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_CRIMINAL, "Đoạt Bảo Nhiệm Vụ");
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_CRIMINAL, 1, "Tiêu diệt Đào Phạm");
}

void task_info()
{
	object me, who, npc, map;
	string criminal;
	int level, z, x, y, p;

	me = this_object();
	who = this_player();
	if (who->get_task("criminal.bonus"))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Rất tốt,nhanh như vậy đã tiêu diệt được Đào Phạm.Ngươi hãy nhận thưởng nè!!\n" ESC "Hoàn thành nhiệm vụ\n" + sprintf("talk %x# bonus\n", getoid(me)) + ESC "Rời khỏi\nCLOSE\n");
		return;
	}
	criminal = who->get_task("criminal");

	npc = find_char(criminal);
	if (!objectp(npc))
	{
		return;
	}
	if (npc->is_criminal() == 0)
	{
		return;
	}
	z = get_z(npc);
	if (!objectp(map = get_map_object(z)) || !map->is_scene())
		return;
	x = who->get_task("criminal.x");
	y = who->get_task("criminal.y");
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + sprintf(": \n    Tiến hành thế nào rồi? " HIR "%s" NOR "ngay tại" HIR "%s(%d,%d)" NOR "vùng thường lui tới.Nếu ngươi có Công Văn Truy Nã sẽ dễ dàng tìm ra hắn.\n", npc->get_name(), map->get_name(), x, y, npc->get_name()) + ESC "Rời khỏi\nCLOSE\n");
}

void task_bonus() { __FILE__->task_bonus_callout(this_object(), this_player()); }

void task_bonus_callout(object me, object who)
{
	int level, exp, pot, money, knb, moneykhoa;
	string name;
	//	object who = this_player();

	if (who->get_task("criminal.bonus") == 0)
		return;

	level = who->get_task("criminal.level");
	name = who->get_task("criminal.name");

	who->delete_task("criminal.bonus");
	who->delete_task("criminal.level");
	who->delete_task("criminal.name");
	who->delete_task("criminal.map");
	who->delete_task("criminal.x");
	who->delete_task("criminal.y");
	who->delete_task("criminal");

	//who->delete_save("cambayquest");
	exp = level * level / 5 + 200;
	exp = exp * who->get_online_rate() / 100;
	who->add_exp(exp); // add_exp(exp, 1);
	pot = level * 2;
	pot = pot * who->get_online_rate() / 100;
	who->add_potential(pot);
	money = 10000 * who->get_online_rate() / 100;
	// moneykhoa = who->get_level() / 3 * 1000 * who->get_online_rate() / 100;
	// if (moneykhoa > 20000)
	// 	moneykhoa = 20000;
	if ("sys/party/party_x2_quest_15"->get_truybatdaopham_x2() == 1)
	{
		if (localtime(time())[2] == localtime(who->get_task("criminal.time"))[2])
		{
			money = who->get_level() * 750;
			//moneykhoa = 0;
			if (money > 45000)
			{
				money = 45000;
			}
		}
	}
	// if (moneykhoa > 0)
	// 	who->add_cashkhoa(moneykhoa);

	who->add_cash(money);
	//who->delete_task("criminal.time");
	who->log_money("Trọng Phạm", money);
	"/sys/sys/count"->add_income("criminal", money);

	who->add_log("&criminal", exp);
	who->add_log("*criminal", pot);
	who->add_log("$criminal", money);

	send_user(who, "%c%w", 0x0d, MUSIC_TASK);
	log_file("truybatdaopham.txt", sprintf("%s : %s (%d) đã hoàn thành nhiệm vụ áp tiêu, Ngân Lượng: %+d \n", short_time(time()), who->get_name(), who->get_number(), money));
	send_user(who, "%c%s", ';', sprintf("Ngươi hoàn thành truy nã %s nhiệm vụ，Kinh Nghiệm %+d, Tiềm Năng %+d, Ngân Lượng +%d.", name, exp, pot, money));
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 3, TID_CRIMINAL, 1, "");
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_CRIMINAL, 1, "");
	send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_CRIMINAL, "");
}

void task_giveup(object who, int iKind)
{
	object npc, item;
	string id, *member;

	if (who->get_task("criminal.bonus"))
	{
		send_user(who, "%c%s", '!', "Nhiệm vụ đã hoàn thành.Hãy về Vương Bổ Đầu trả nhiệm vụ.");
		return;
	}
	if (gone_time(who->get_task("criminal.time")) < 180)
	{
		item = who->get_equip(HAND_TYPE);
		if (item && item->get_item_number() == 10001078)
		{
			send_user(who, "%c%c%s", 0x59, 1, sprintf("Ngươi sử dụng Phù để trừ khoảng cách thời gian nhiệm vụ của ngươi???\n" ESC "%c\n" ESC "use %x# criminal2\n", 1, getoid(item)));
			return;
		}
		send_user(who, "%c%s", '!', "Hãy đợi 3 phút,Sau đó huỷ bỏ nhiệm vụ 1 lần nữa");
		return;
	}
	id = who->get_task("criminal");
	who->delete_task("criminal");
	//	who->delete_save("cambayquest");
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 3, TID_CRIMINAL, 1, "");
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_CRIMINAL, 1, "");
	send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_CRIMINAL, "");

	if (!stringp(id) || !objectp(npc = find_char(id)) || !npc->is_criminal())
	{
		return;
	}
	member = npc->get("user");
	id = sprintf("%d", who->get_number());
	member -= ({id});
	if (sizeof(member) == 0)
	{
		npc->remove_from_scene();
		destruct(npc);
	}
	else
		npc->set("user", member);
}

void do_visit(string arg)
{
	int i, exp, pot, money;
	object who, npc, item;
	who = this_player();
	npc = this_object();

	if (arg == "cancel") // 拒绝任务转到这里进行
	{
		item = who->get_equip(HAND_TYPE);
		if (item && item->get_item_number() == 10001078)
		{
			send_user(who, "%c%c%s", 0x59, 1, sprintf("Ngươi sử dụng Phù để tiêu trừ khoảng cách thời gian nhiệm vụ của ngươi???\n" ESC "%c\n" ESC "use %x# criminal\n", 1, getoid(item)));
			return;
		}
	}
	if (who->get_level() >= 10 && who->get_legend(TASK_2_00, 10) && !who->get_legend(TASK_2_00, 11))
	{
		i = to_int(arg);
		if (i == 1)
		{
			if (who->get_fam_name() == "")
				send_user(who, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf("%s\n    Nhìn ngươi chưa gia nhập Môn Phái nào làm sao nhận nhiệm vụ được,hãy gia nhập Phái học võ nghệ rồi đến tìm ta.\n", npc->get_name(), ));
			else
				send_user(who, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf("%s\n    Qủa nhiên người của Môn Phái giới thiệu rất khác người,rất thông minh và võ nghệ siêu phàm!!!.\n" ESC "Hoàn thành nhiệm vụ\ntalk %x# visit.2\n", npc->get_name(), getoid(npc)));
		}
		else if (i == 2 && who->get_fam_name() != "")
		{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_2_00, 11);
			exp = 300;
			pot = 35;
			money = 500;
			who->add_exp(exp);
			who->add_potential(pot);
			who->add_cash(money);
			send_user(who, "%c%s", ';', sprintf("Nhiệm vụ Vương Bộ Đầu :Kinh Nghiệm %d Tiềm Năng %d Ngân Lượng %d", exp, pot, money));
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 119, "");
			npc->do_visit(3);
		}
	}
	if (who->get_legend(TASK_2_00, 11) && !who->get_legend(TASK_2_00, 12))
	{
		i = to_int(arg);
		if (i == 3)
			send_user(who, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf("%s\n    Trong nha môn Sư Gia chính là nhân vật truyền kỳ,nghe nói hắn tham ô hối lộ,cũng có người nói hắn là 1 vị quan tốt.Gần đây hay xuất hiện đạo tặc,Sư Gia đang tìm người hỗ trợ bắt đạo tặc,ngươi cũng đến tham gia cho biết đi!!\n" ESC "Nhận nhiệm vụ\ntalk %x# visit.4\n", npc->get_name(), getoid(npc)));
		else if (i == 4)
		{
			if (TASK_LEGEND_D->can_task_add(who) != 1)
				return;
			who->set_legend(TASK_2_00, 12);
			send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_ZHOUGUO, "Chu");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_ZHOUGUO, 16, "Gặp mặt Sư Gia");
			send_user(who, "%c%s", '!', "Nhận nhiệm vụ " HIY "Gặp mặt Sư Gia");
		}
	}
}

void do_thief(string arg) { TASK_THIEF_D->do_task_start(this_player(), this_object()); }

void accept_thief() { TASK_THIEF_D->accept_task(this_player(), this_object()); }
void give_thief_bonus() { TASK_THIEF_D->give_bonus(this_player()); }

//获得锄头
void get_hoe()
{
	object player = this_player();
	object npc = this_object();
	int index, size, flag = 0; //flag标志判断是否可以获得锄头,0为可以获得,1为不可以获得.
	object *all_inv;
	if ("sys/party/treasure"->is_open() == 0) //现在活动还没有开始,不能领取锄头.
	{
		return;
	}
	if (player->get_online_rate() != 100)
	{
		send_user(player, "%c%s", '!', "Ngươi hiện tại không được khoẻ,không thể tham gia hoạt động");
		return;
	}
	if (sizeof_inventory(player, 1, MAX_CARRY) >= MAX_CARRY)
	{
		send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), npc->get_name() + ":\n	Trên người ngươi không đủ chỗ trống,chừa bớt hành trang rồi hãy đến Lĩnh cái cuốc trong Bảo Khố");
		flag = 1;
	}
	all_inv = all_inventory(player, 1, MAX_CARRY * 4);
	size = sizeof(all_inv);
	if (size > 0)
	{
		for (index = 0; index < size; index++)
		{
			if (all_inv[index]->get_name() == "Lấy cái cuốc trong Bảo Khố")
			{
				send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), npc->get_name() + ":\n	Ngươi muốn lĩnh cái cuốc,hãy sử dụng rồi lần sau lại đến tìm ta lĩnh!!");
				flag = 1;
			}
		}
	}
	if (flag == 0)
	{
		"sys/party/treasure"->generate_chutou(player);
		send_user(player, "%c%s", '!', "Ngươi nhận được cái cuốc lĩnh trong Bảo Khố");
	}
}
