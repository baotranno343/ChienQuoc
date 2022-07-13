
#include <npc.h>
#include <ansi.h>
#include <city.h>
#include <effect.h>

inherit OFFICER;
inherit SAVE_F;
int iStart, iFinish, iStart2;
string org_name;
int max_org_qgl;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5205; }
string get_save_file() { return "data/qiguoling" SAVE_EXTENSION; }
// 函数：构造处理
void create()
{
	restore();
	set_name("七国令收集员");
	set_2("talk", (["welcome":(
								  : do_welcome:),
	]));
	setup();
	set("mpLegend", ([0:({32}), ]));
	if (!clonep(this_object()))
		return;
	if (MAIN_D->get_host_type() == 2) //台湾除外
		call_out("go_there", 2);
}

void do_look(object who) { __FILE__->do_look_call(this_object(), who); }

void do_look_call(object me, object who)
{
	object orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", me->get_org_name()));
	int id = getoid(me);
	if (!objectp(orgnpc))
		return;
	if (MAIN_D->get_host_type() == 2)
		return;
	if (who->get_org_name() != me->get_org_name())
		return;
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    传闻七国令与本帮有着某种神秘的关系，为了揭开这个秘密，你还是将七国令交给我吧～！作为回报，你将会得到一定的奖励哦～！    现在帮派中已经交纳的七国令累计有" HIR "%d" NOR "个\n" ESC "交纳七国令\ntalk %x# welcome.1\n" ESC "领取帮派齐心合力奖\ntalk %x# welcome.3\n" ESC "领取超级无敌帮会奖\ntalk %x# welcome.9\n" ESC "了解帮派齐心合力奖\ntalk %x# welcome.7\n" ESC "了解超级无敌帮会奖\ntalk %x# welcome.8\n" ESC "离开", me->get_name(), orgnpc->get_save("qgl_org_n"), id, id, id, id, id));
}

void do_welcome(string arg) { __FILE__->do_welcome_call(this_object(), arg); }

void do_welcome_call(object me, string arg)
{
	int flag, p, iTime, i, size, id, x, y, z, level, number;
	object who, item, *nTeam, member, npc, map, orgnpc;
	string name, *nTmp, tmp, result;
	mixed *mxTime;

	if (MAIN_D->get_host_type() == 2)
		return;

	who = this_player();
	flag = to_int(arg);
	who->set_time("talk", 0);
	id = getoid(me);

	switch (flag)
	{
	case 1:
		if (iStart == 0 || time() < iStart)
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    活动还没开始呢，详情请查看官方网站(zg.mop.com)公告。\n" ESC "离开", me->get_name(), ));
		else if (iStart == 1 || (time() > iStart && time() < iFinish))
		{
			if (who->get_org_name() != me->get_org_name())
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    你来本帮有何贵干？千万不要来捣乱哦～！不然本帮兄弟一定会对你不客气的～！\n" ESC "离开", me->get_name(), ));
			else if (!objectp(item = present("七国令", who, 1, MAX_CARRY)))
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    你身上并没有七国令啊～！你还是好好想想吧～！想想，是不是忘记放在什么地方？\n" ESC "离开", me->get_name(), ));
			else
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    感谢你为本帮所做的贡献，这是给你的奖励，奖励虽不多，但意义重大！你可一定要收下哦～！\n" ESC "领取奖励\ntalk %x# welcome.2\n" ESC "离开", me->get_name(), id));
		}
		else if (iStart == 2 || time() > iFinish)
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    本项活动已经结束，谢谢你的参与！\n" ESC "离开", me->get_name(), ));
		break;

		break;
	case 2:
		if (iStart == 2 || time() > iFinish)
			return;
		if (objectp(item = present("七国令", who, 1, MAX_CARRY)))
		{
			orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", who->get_org_name()));
			number = who->get_number();
			orgnpc->set_member_contribute(number, orgnpc->get_member_contribute(number) + 5);
			result = sprintf("交纳 %s,%d,%s,%s @%s %s %s %s %d %s %d_%d_%d", who->get_name(), who->get_number(), get_ip_name(who), who->get_id(), "", me->get_name(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), 1, item->get_user_id(), get_z(who), get_x(who), get_y(who));
			item->add_amount(-1);
			who->add_exp(2000);
			who->add_potential(50);
			send_user(who, "%c%s", ';', "您得到了5点帮贡、2000经验、50潜能的奖励");
			who->add_save("qgl_n", 1);
			orgnpc->add_save("qgl_org_n", 1);
			orgnpc->save();
			log_file("qgl_org_n.txt", sprintf("%d 服务器 %d %s 帮 %s 有七国令 %d\n", MAIN_D->get_host(), MAIN_D->get_host_type(), who->get_org_name(), short_time(), orgnpc->get_save("qgl_org_n")));
			//"/sys/user/cmd"->log_item(result);
			if (orgnpc->get_save("qgl_org_n") > max_org_qgl)
			{
				org_name = who->get_org_name();
				max_org_qgl = orgnpc->get_save("qgl_org_n");
				save();
			}
		}
		break;
	case 3:
		if (iStart2 == 0)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    帮派齐心合力奖还没有评选出来，你还是等评选出帮派齐心合力奖再来找我吧～！\n" ESC "离开", me->get_name(), ));
			return;
		}
		if (who->get_org_name() != org_name)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    你们帮并没有获得帮派齐心合力奖啊～！\n" ESC "离开", me->get_name(), ));
			return;
		}
		if (who->get_org_time() > iFinish)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    你是在此次活动结束后加入本帮的，不能领奖！\n" ESC "离开", me->get_name(), ));
			return;
		}
		if (who->get_save("qgl_org_receive"))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    你已经领取过奖励了～！可不要贪心哦～！\n" ESC "离开", me->get_name(), ));
			return;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 3)
		{
			send_user(who, "%c%s", '!', "请清理一下你的包包再来领取奖励吧！");
			return;
		}
		if (who->get_org_position() == 9)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    恭喜贵帮荣获帮派齐心合力奖，作为帮主，你领导有方，本员特给予你丰厚的嘉奖，希望你日后再接再厉～！\n" ESC "离开", me->get_name(), ));
			if (who->get_cash() + 5000000 > who->get_max_cash())
				who->add_cash(who->get_max_cash() - who->get_cash());
			else
				who->add_cash(5000000);
		}
		else
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    恭喜贵帮荣获帮派齐心合力奖，作为成员，你们齐心合力，本员特给予你丰厚的嘉奖，希望你日后再接再厉～！\n" ESC "离开", me->get_name(), ));

		//武功进阶书
		item = new (BOOK_FILE->get_book_file());
		p = item->move(who, -1);
		item->add_to_user(p);

		//变身卡
		item = new ("quest/gift"->get_random_card());
		p = item->move(who, -1);
		item->add_to_user(p);

		//麻布包裹
		item = new ("item/std/6003");
		p = item->move(who, -1);
		item->add_to_user(p);

		who->set_save("qgl_org_receive", time());

		break;
	case 7:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    想获取帮派齐心合力奖吗？那就赶快来参与吧！活动结束一周内评出每组服务器一个交令牌最多帮派，帮派内每位成员得到随机武功进阶书一本、麻布包裹一个、随机变身卡一张，会长可得到500W游戏币。如此诱人的奖励可不要错过哦～！\n" ESC "离开", me->get_name(), ));
		break;
	case 8:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    想获取超级无敌帮会奖吗？那就赶快来参与吧！山外有山天外有天，超级无敌帮派不仅仅是帮会所在服务器的缴纳令牌数第一名，在全服的缴纳排名也要位列第一才行！活动结束一周内，超级无敌帮会内每位成员得到武功进阶书一本、麻布包裹一个、变身卡一张，会长可得到1000W游戏币。如此诱人的奖励可不要错过哦～！\n" ESC "离开", me->get_name(), ));
		break;
	case 9:
		orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", who->get_org_name()));
		if (iStart2 == 0)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    超级无敌帮会奖还没有评选出来，你还是等评选出超级无敌帮会奖再来找我吧～！\n" ESC "离开", me->get_name(), ));
			return;
		}
		if (who->get_org_name() != "再續前緣")
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    你们帮并没有获得超级无敌帮会奖啊～！\n" ESC "离开", me->get_name(), ));
			return;
		}
		if (orgnpc->get_save("qgl_org_n") < 3000)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    你们帮并没有获得超级无敌帮会奖啊～！\n" ESC "离开", me->get_name(), ));
			return;
		}
		if (who->get_org_time() > iFinish)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    你是在此次活动结束后加入本帮的，不能领奖！\n" ESC "离开", me->get_name(), ));
			return;
		}
		if (who->get_save("qgl_org_receive2"))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    你已经领取过奖励了～！可不要贪心哦～！\n" ESC "离开", me->get_name(), ));
			return;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 3)
		{
			send_user(who, "%c%s", '!', "请清理一下你的包包再来领取奖励吧！");
			return;
		}
		if (who->get_org_position() == 9)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    恭喜贵帮荣获超级无敌帮会奖，作为帮主，你领导有方，本员特给予你丰厚的嘉奖，希望你日后再接再厉～！\n" ESC "离开", me->get_name(), ));
			if (who->get_cash() + 10000000 > who->get_max_cash())
				who->add_cash(who->get_max_cash() - who->get_cash());
			else
				who->add_cash(10000000);
		}
		else
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    恭喜贵帮荣获超级无敌帮会奖，作为成员，你们齐心合力，本员特给予你丰厚的嘉奖，希望你日后再接再厉～！\n" ESC "离开", me->get_name(), ));

		//武功进阶书
		item = new (BOOK_FILE->get_book_file());
		p = item->move(who, -1);
		item->add_to_user(p);

		//变身卡
		item = new ("quest/gift"->get_random_card());
		p = item->move(who, -1);
		item->add_to_user(p);

		//麻布包裹
		item = new ("item/std/6003");
		p = item->move(who, -1);
		item->add_to_user(p);

		who->set_save("qgl_org_receive2", time());

		break;
	}
}

void go_there()
{
	object me = this_object();

	me->add_to_scene(802, 78, 43, 2);
}

void set_prepare()
{
	iStart = 0;
	save();
}

void set_open()
{
	iStart = 1;
	save();
}

int set_open_time(object who, string arg)
{
	int date1, date2, year1, year2, mon1, mon2, day1, day2;
	if (sscanf(arg, "%d-%d", date1, date2) != 2)
	{
		send_user(who, "%c%s", '!', "错误的格式！");
		return 0;
	}
	year1 = date1 / 10000;
	mon1 = date1 % 10000 / 100;
	day1 = date1 % 10000 % 100;
	year2 = date2 / 10000;
	mon2 = date2 % 10000 / 100;
	day2 = date2 % 10000 % 100;
	if (!year1 || !mon1 || !day1 || !year2 || !mon2 || !day2)
	{
		send_user(who, "%c%s", '!', "错误的时间！");
		return 0;
	}
	iStart = mktime(year1, mon1, day1, 0, 0, 0);
	iFinish = mktime(year2, mon2, day2, 0, 0, 0);
	if (iStart > iFinish)
	{
		send_user(who, "%c%s", '!', "错误的时间！！");
		return 0;
	}
	save();
	return 1;
}

void set_close()
{
	iStart = 2;
	iFinish = time();
	save();
}

void set_open2()
{
	iStart2 = 1;
	save();
}

void set_close2()
{
	iStart2 = 0;
	save();
}
