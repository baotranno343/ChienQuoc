
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <skill.h>
#include <city.h>

inherit CHAR;

inherit "/inh/char/cmd";
inherit "/inh/char/group";
inherit "/inh/npc/skill";
inherit "/inh/npc/equip";

private
string Name; // 中文名字
private
string RealName; // 实名

// 函数:NPC 人物
int is_npc() { return 1; }

// 函数:功能人物
int is_officer() { return 1; }

// -------------------------------------------------------------

// 函数:NPC 类型
int get_char_type() { return OFFICER_TYPE; }

// 函数:获取人物造型
int get_char_picid() { return 0; } // 需要重载

// 函数:获取人物名称
string get_name() { return Name; }

// 函数:设置人物名称
string set_name(string name)
{
	if (Name != name)
		send_user(get_scene_object_2(this_object(), USER_TYPE), "%c%c%d%s", 0x3d, 5, getoid(this_object()), name);
	return Name = name;
}
// 函数:获取人物名称
string get_real_name() { return RealName; }

// 函数:设置人物名称
string set_real_name(string name)
{
	return RealName = name;
}
// 函数:设置人物名称
// string set_name( string name ) { return Name = name; }    // 庄稼要改名称

// 函数:获取人物名称
string get_short()
{
	if (stringp(get_real_name()))
		return get_real_name() + "||||" + get_name();
	else
		return get_name();
}
// 函数:物体识别处理
int id(string arg)
{
	if (!arg || arg == "")
		return 0;
	if (arg[ < 1] == '#')
		return arg != sprintf("%x#", getoid(this_object())) ? 0 : 1;
	return arg != get_name() ? 0 : 1;
}

// 函数:人物设置函数
void setup() { this_object()->enable_player(); }

// 函数:获取最高人物等级
int get_max_char_level() { return 150; }

// 函数:获取最高技能等级
int get_max_skill_level()
{
	if (MAIN_D->get_host_type() == 4)
		return 120;
	return 150;
}

// 函数:判断可以战斗
int can_fight(object who) { return 0; }

// 函数:可以接受战斗
int can_be_fighted(object who) { return 0; }

// 函数:获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数:获取皮肤颜色
int get_body_color() { return 0; }

// -------------------------------------------------------------

// 函数:设置面向方向
int to_front(int d)
{
	d = range_value(d, 1, 8);
	send_user(this_player(), "%c%d%c", 0x5e, getoid(this_object()), d); // set_d(me, d);
	return d;
}

// -------------------------------------------------------------
//显示任务提示
void show_task_flag(object *user)
{
	int *legend, *nLevel, size, *nKey;
	object me = this_object();
	int id = getoid(me);
	int i, j, count;
	mapping mpLegend;
	string cFlag;
	mixed *mxTmp;

	mpLegend = me->get("mpLegend");
	if (!mapp(mpLegend))
		return;
	nLevel = keys(mpLegend);
	nLevel = sort_array(nLevel, -1);
	for (i = 0, size = sizeof(nLevel); i < size; i++)
	{
		nKey = mpLegend[nLevel[i]];
		count = sizeof(nKey);
		cFlag = "%c%d%c";
		mxTmp = ({
			0x71,
			id,
			nLevel[i],
		});
		for (j = 0; j < count; j++)
		{
			cFlag += "%w";
			mxTmp += ({nKey[j]});
		}
		send_user(user, cFlag, mxTmp);
	}
}

//显示完成任务提示
void show_task_finish_flag(object *user)
{
	int *legend, *nLevel, size, *nKey;
	object me = this_object();
	int id = getoid(me);
	int i, j, count;
	mapping mpLegend;
	string cFlag;
	mixed *mxTmp;

	mpLegend = me->get("mpLegend2");
	if (!mapp(mpLegend))
		return;
	nLevel = keys(mpLegend);
	nLevel = sort_array(nLevel, -1);
	for (i = 0, size = sizeof(nLevel); i < size; i++)
	{
		nKey = mpLegend[nLevel[i]];
		count = sizeof(nKey);
		cFlag = "%c%d%c";
		mxTmp = ({
			0x72,
			id,
			nLevel[i],
		});
		for (j = 0; j < count; j++)
		{
			cFlag += "%w";
			mxTmp += ({nKey[j]});
		}
		send_user(user, cFlag, mxTmp);
	}
}

// 函数:列示给新玩家(对方进场景)(功能NPC 专用)
void show_to_user(object who)
{
	int *legend, level, size;
	object me = this_object();
	int id = getoid(me);

	if (get_char_picid())
		send_user(who, "%c%c%d%w%w%c%c%c%w%c%c%d%s", 0x69, 128, id,
				  get_x(me), get_y(me), get_d(me), get_char_type(), me->get_char_action(), get_char_picid(),
				  0, 0, 0, get_short());
	else
		send_user(who, "%c%c%d%w%w%c%c%c%d%w%w%c%c%c%c%d%s", 0x69, 0, id,
				  get_x(me), get_y(me), get_d(me), get_char_type(), me->get_char_action(),
				  get_armor_code(), get_armor_color_1(), get_weapon_code_2(), 0, 0,
				  0, 0, 0, get_short());
	legend = me->get("legend");
	size = sizeof(legend);
	if (size > 0)
	{
		level = me->get("level");
		switch (size)
		{
		case 1:
			send_user(who, "%c%d%c%w", 0x71, id, level, legend[0]);
			break;
		case 2:
			send_user(who, "%c%d%c%w%w", 0x71, id, level, legend[0], legend[1]);
			break;
		case 3:
			send_user(who, "%c%d%c%w%w%w", 0x71, id, level, legend[0], legend[1], legend[2]);
			break;
		case 4:
			send_user(who, "%c%d%c%w%w%w%w", 0x71, id, level, legend[0], legend[1], legend[2], legend[3]);
			break;
		case 5:
			send_user(who, "%c%d%c%w%w%w%w%w", 0x71, id, level, legend[0], legend[1], legend[2], legend[3], legend[4]);
			break;
		case 6:
			send_user(who, "%c%d%c%w%w%w%w%w%w", 0x71, id, level, legend[0], legend[1], legend[2], legend[3], legend[4], legend[5]);
			break;
		case 7:
			send_user(who, "%c%d%c%w%w%w%w%w%w%w", 0x71, id, level, legend[0], legend[1], legend[2], legend[3], legend[4], legend[5], legend[6]);
			break;
		case 8:
			send_user(who, "%c%d%c%w%w%w%w%w%w%w%w", 0x71, id, level, legend[0], legend[1], legend[2], legend[3], legend[4], legend[5], legend[6], legend[7]);
			break;
		default:
			send_user(who, "%c%d%c%w%w%w%w%w%w%w%w%w", 0x71, id, level, legend[0], legend[1], legend[2], legend[3], legend[4], legend[5], legend[6], legend[7], legend[8]);
			break;
		}
	}
	if (me->get_ride())
		send_user(who, "%c%d%d", 0x62, id, me->get_ride());
	show_task_flag(({who}));
	show_task_finish_flag(({who}));
	if (me->get_id_color())
		send_user(who, "%c%d%d", 0x66, id, me->get_id_color());
}

// 函数:列示给玩家看(新进入场景)(功能NPC 专用)
void show_to_scene(object *user, int x, int y, int d, int add_pf)
{
	int *legend, level, size;
	object me = this_object();
	int id = getoid(me);

	if (get_char_picid())
	{
		if (!add_pf)
			send_user(user, "%c%c%d%w%w%c%c%c%w%c%c%d%s", 0x69, 128, id,
					  x, y, d, get_char_type(), me->get_char_action(), get_char_picid(),
					  0, 0, 0, get_short());
		else
			send_user(user, "%c%c%d%w%w%c%c%c%w%c%w%c%c%c%d%s", 0x69, 129, id,
					  x, y, d, get_char_type(), me->get_char_action(), get_char_picid(),
					  0, add_pf, 1, OVER_BODY, 0, 0, get_short());
	}
	else
	{
		if (!add_pf)
			send_user(user, "%c%c%d%w%w%c%c%c%d%w%w%c%c%c%c%d%s", 0x69, 0, id,
					  x, y, d, get_char_type(), me->get_char_action(),
					  get_armor_code(), get_armor_color_1(), get_weapon_code_2(), 0, 0,
					  0, 0, 0, get_short());
		else
			send_user(user, "%c%c%d%w%w%c%c%c%d%w%w%c%c%c%w%c%c%c%d%s", 0x69, 1, id,
					  x, y, d, get_char_type(), me->get_char_action(),
					  get_armor_code(), get_armor_color_1(), get_weapon_code_2(), 0, 0,
					  0, add_pf, 1, OVER_BODY, 0, 0, get_short());
	}
	legend = me->get("legend");
	size = sizeof(legend);
	if (size > 0)
	{
		level = me->get("level");
		switch (size)
		{
		case 1:
			send_user(user, "%c%d%c%w", 0x71, id, level, legend[0]);
			break;
		case 2:
			send_user(user, "%c%d%c%w%w", 0x71, id, level, legend[0], legend[1]);
			break;
		case 3:
			send_user(user, "%c%d%c%w%w%w", 0x71, id, level, legend[0], legend[1], legend[2]);
			break;
		case 4:
			send_user(user, "%c%d%c%w%w%w%w", 0x71, id, level, legend[0], legend[1], legend[2], legend[3]);
			break;
		case 5:
			send_user(user, "%c%d%c%w%w%w%w%w", 0x71, id, level, legend[0], legend[1], legend[2], legend[3], legend[4]);
			break;
		case 6:
			send_user(user, "%c%d%c%w%w%w%w%w%w", 0x71, id, level, legend[0], legend[1], legend[2], legend[3], legend[4], legend[5]);
			break;
		case 7:
			send_user(user, "%c%d%c%w%w%w%w%w%w%w", 0x71, id, level, legend[0], legend[1], legend[2], legend[3], legend[4], legend[5], legend[6]);
			break;
		case 8:
			send_user(user, "%c%d%c%w%w%w%w%w%w%w%w", 0x71, id, level, legend[0], legend[1], legend[2], legend[3], legend[4], legend[5], legend[6], legend[7]);
			break;
		default:
			send_user(user, "%c%d%c%w%w%w%w%w%w%w%w%w", 0x71, id, level, legend[0], legend[1], legend[2], legend[3], legend[4], legend[5], legend[6], legend[7], legend[8]);
			break;
		}
	}
	if (me->get_ride())
		send_user(user, "%c%d%d", 0x62, id, me->get_ride());
	show_task_flag(user);
	show_task_finish_flag(user);
	if (me->get_id_color())
		send_user(user, "%c%d%d", 0x66, id, me->get_id_color());
}

// -------------------------------------------------------------

void do_patrol(string arg) { "/inh/job/soldier"->do_patrol(this_player(), this_object(), arg); }
void do_stir_up(string arg) { "/inh/job/soldier"->do_stir_up(this_player(), this_object(), arg); }
void do_soldier(string arg) { "/inh/job/soldier"->do_soldier(this_player(), this_object(), arg); }

void do_stir_up_2(string arg) { "/inh/job/trader"->do_stir_up(this_player(), this_object(), arg); }

// 函数:增添对话菜单
void more_look_menu(object who, string text)
{
	object city, me;
	string name1, name2, result = "";
	int id, p;

	if (who->get_strength())
	{
		me = this_object();
		id = getoid(me);

		if (who->is_soldier() && stringp(name1 = who->get_city_name()) && stringp(name2 = me->get_city_name()))
		{
			if (name1 == name2)
			{
				if (who->get_2("train.patrol")) // && me->is_seller()
				{
					if (!get_2("talk.patrol"))
						add_2("talk", (["patrol":(
													 : do_patrol:),
						]));
					result = sprintf(ESC "Có bọn đạo chính trong thành quấy rầy bạn không?\ntalk %x# patrol\n", id);
				}
				if (who->get_2("train.soldier") && (city = CITY_D->get_city_object(who)) && !city->is_soldier_enough())
				{
					if (!get_2("talk.soldier"))
						add_2("talk", (["soldier":(
													  : do_soldier:),
						]));
					result = sprintf(ESC "Bạn có hứng thú tham gia quân ngũ không?\ntalk %x# soldier\n", id);
				}
			}
			else if (name2 != "")
			{
				if (city = CITY_D->get_city_object(who)) // 以后要加敌对判断
				{
					if (!get_2("talk.stir_up"))
						add_2("talk", (["stir_up":(
													  : do_stir_up:),
						]));
					result = sprintf(ESC "Bịa đặt.\ntalk %x# stir_up.?\n", id);
				}
			}
		}
		else if (who->is_businessman() && stringp(name1 = who->get_city_name()) && stringp(name2 = me->get_city_name()) && name1 != name2 && name2 != "")
		{
			if (city = CITY_D->get_city_object(who)) // 以后要加敌对判断
			{
				if (!get_2("talk.stir_up"))
					add_2("talk", (["stir_up":(
												  : do_stir_up_2:),
					]));
				result = sprintf(ESC "Bịa đặt.\ntalk %x# stir_up.?\n", id);
			}
		}
	}

	if (result == "")
	{
		send_user(who, "%c%s", ':', text);
		return;
	}

	if (strlen(text) > 10 && text[ < 6.. < 1] == "CLOSE\n") // 有关闭选择
	{
		if (p = strchr(text, 27, -1)) // ESC
			send_user(who, "%c%s", ':', sprintf("%s%s%s", text[0..p-1], result, text[p..< 1]));
		else
			send_user(who, "%c%s", ':', text + result);
	}
	else
		send_user(who, "%c%s", ':', sprintf("%s%s%s", text, result, ESC "Rời khỏi.\nCLOSE\n"));
}

// -------------------------------------------------------------

// 变量:随机闲话
static string *GossipTable = ({
	"Hôm nay thời tiết, cáp, còn đi.",
	"Ngươi ăn cơm xong  sao không?",
	"Hôm nay mệt mỏi quá, xem ra phải nghỉ ngơi nghỉ ngơi .",
	"Nghe nói vừa rồi lại mới tới  một cái không biết làm sao tới.",
	"Buổi tối đi đường cẩn thận, tốt nhất mang cái đèn lồng.",
	"Ta nhận thức ngươi sao không? Ngươi nhận thức ta sao?",
	"Ta dường như ở nơi nào gặp qua ngươi da. . . . . .",
	"Ta nhận được ngươi, ngươi không phải là cái kia ai thôi!",
	"Chúng ta lại thấy mặt lạp, có rảnh nhiều đến tâm sự nha. . . . . .",
});

static int sizeof_gossip = sizeof(GossipTable);

// 函数:对话处理
void do_look(object who)
{
	more_look_menu(who, sprintf("%s:\n%s\n", get_name(), GossipTable[random(sizeof_gossip)]));
}
