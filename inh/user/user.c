
#include <npc.h>
#include <ansi.h>
#include <cmd.h>
#include <skill.h>
#include <equip.h>
#include <city.h>
#include <action.h>
#include <effect.h>
#include <map.h>
#include <time.h>
#include <chia_kenh.h>
inherit CHAR;

inherit "/inh/user/gift";
inherit "/inh/user/energy";
inherit "/inh/char/energy2";
inherit "/inh/user/prop";
inherit "/inh/user/setting";
inherit "/inh/user/dbase2";
inherit "/inh/user/dbase3";
inherit "/inh/user/dbase4";
inherit "/inh/char/dbase5";
inherit "/inh/user/city";
inherit "/inh/char/attack";
inherit "/inh/user/attack2";
inherit "/inh/char/cmd";
inherit "/inh/char/group";
inherit "/inh/user/skill";
inherit "/inh/user/equip";
inherit "/inh/user/inventory";
inherit "/inh/user/seller";
inherit "/inh/user/friend";
inherit "/inh/user/login";
inherit "/inh/user/login0";
inherit "/inh/user/save";
inherit "/inh/user/beast";

private
int IdNumber; // 数字标识
private
string Id; // 对象标识
private
static string RealId; // 帐号
private
string Name; // 中文名字

private
static int Action; // 人物动作

private
int iVip; // vip的标志 1 表示vip包获得的vip身份；

private
static int *rc_status = ({
	EFFECT_USE_ITEM_1,
	EFFECT_USE_ITEM_2,
	EFFECT_CHAR_KING_2,
});

private
string *Titles = ({}); //拥有的称谓(代码）
private
string cTitle = ""; //显示的称谓
private
string cTitleCode; //设置的称谓代码
private
string *Apprentices = ({}); //徒弟的集合
private
static int AcountId; // 帐号对应的id
private
int AcountNo; // 帐号对应的Number

int get_login_flag();

// 函数：玩家识别函数
int is_user() { return 1; }

// 函数：获取人物标识(用于 find_char 函数)
string get_char_id() { return sprintf("%d", IdNumber); } // 涉及太广，禁止改动

// -------------------------------------------------------------

// 函数：获取唯一号码
int get_acountid() { return AcountId; }

// 函数：设置唯一号码
int set_acountid(int id) { return AcountId = id; }

// 函数：获取帐号的no
int get_acountno() { return AcountNo; }

// 函数：设置唯一号码
int set_acountno(int id) { return AcountNo = id; }

// 函数：获取唯一号码
int get_number() { return IdNumber; }

// 函数：设置唯一号码
int set_number(int id) { return IdNumber = id; }

// 函数：获取vip标志
int get_vip() { return iVip; }

// 函数：设置vip标志
int set_vip(int id) { return iVip = id; }

// 函数：获取对象标识
string get_id() { return Id; }

// 函数：设置对象标识
string set_id(string id) { return Id = strlwr(id); }

// 函数：获取对象标识
string get_real_id() { return RealId; }

// 函数：设置对象标识
string set_real_id(string id) { return RealId = strlwr(id); }

// 函数：获取中文名字
string get_name() { return Name; }

// 函数：设置中文名字
string set_name(string name)
{
	object me;
	//	me = this_object();
	if (!is_chinese(name))
	{
		if (!Name || Name == "")
			Name = "无名氏";
		return Name;
	}

	if (Name != name)
	{
		me = this_object();
		if (get_login_flag() > 1)
			send_user(me, "%c%c%s", 0x3d, 4, name);
		send_user(get_scene_object_2(me, USER_TYPE), "%c%c%d%s", 0x3d, 5, getoid(me), name);
	}

	return Name = name;
}

// 函数：获取人物名称
string get_short()
{
	string cName;
	int z;
	object map, me;

	me = this_object();
	cName = get_name();
	z = get_z(me);
	map = get_map_object(z);
	if (map)
	{
		if (!map->is_changping())
			return cName;
		if (me->get_2("changping.country") == "Tần Quốc")
			cName = HIR + cName;
		else if (me->get_2("changping.country") == "Triệu Quốc")
			cName = HIB + cName;
	}
	return cName;
}
// 函数：获取人物称谓
string get_title()
{
	if (stringp(cTitle))
		return cTitle;
	else
		return "";
}
// 函数：获取人物称谓
string get_title_code()
{
	if (stringp(cTitleCode))
		return cTitleCode;
	else
		return "";
}
//设置显示的称谓
string set_title(string tltlecode, string titlename)
{
	cTitleCode = tltlecode;
	return cTitle = titlename;
}

//显示玩家称谓
void show_title(string titlecode)
{
	if (!arrayp(Titles) || member_array(titlecode, Titles) == -1)
		return;
	TITLE_D->show_title(this_object(), titlecode);
}
//隐藏玩家称谓
void hide_title()
{
	TITLE_D->hide_title(this_object());
}

//查找称谓
int have_title(string titlecode)
{
	if (!arrayp(Titles) || member_array(titlecode, Titles) == -1)
		return 0;
	return 1;
}

// 函数：增加人物称谓
string add_title(string titlecode)
{
	if (TITLE_D->check_title_code(titlecode) != 1)
		return;
	if (!arrayp(Titles))
		Titles = ({});
	if (member_array(titlecode, Titles) != -1)
		return;
	Titles += ({titlecode});
	TITLE_D->send_title(this_object(), titlecode);
	return titlecode;
}
// 函数：删除人物称谓
string delete_title(string titlecode)
{
	if (!arrayp(Titles))
		Titles = ({});
	if (member_array(titlecode, Titles) == -1)
		return;
	Titles -= ({titlecode});
	if (cTitleCode == titlecode)
		hide_title();
	TITLE_D->delete_title(this_object(), titlecode);
}
//发送称谓列表 登陆时
void send_title_list()
{
	int i, size;
	string *nTmp = ({});
	object me = this_object();

	size = sizeof(Titles);
	if (!size)
		return;
	for (i = 0; i < size; i++)
	{
		if (Titles[i][0..0] == "M" && !me->get_save_2("marry"))
		{
			if (cTitleCode[0..0] == "M")
			{
				cTitleCode = "";
				cTitle = "";
			}
			nTmp += ({Titles[i]});
		}
	}
	if (sizeof(nTmp))
		Titles -= nTmp;
	for (i = 0, size = sizeof(Titles); i < size; i++)
	{
		TITLE_D->send_title(me, Titles[i]);
	}
	if (me->get_save("sxTimes"))
		"sys/school/shouxi"->check_shouxi_title(me);
}
//增加徒弟
string add_apprentice(string cName)
{
	if (!arrayp(Apprentices))
		Apprentices = ({});
	if (member_array(cName, Apprentices) != -1)
		return;
	Apprentices += ({cName});
	return cName;
}
//取得徒弟列表
string *get_apprentice()
{
	return copy(Apprentices);
}

// 函数：物体识别处理
int id(string arg)
{
	if (!arg || arg == "")
		return 0;
	if (arg[ < 1] == '#')
		return arg != sprintf("%x#", getoid(this_object())) ? 0 : 1;
	return arg != get_name() ? 0 : 1;
}

// -------------------------------------------------------------

// 函数：获取动作状态
int get_char_action() { return is_die() ? DIE_ACT : Action; }

// 函数：设置动作状态
int set_char_action(int action)
{
	object me = this_object();
	if (Action != action && get_login_flag() > 1)
		send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), action);
	return Action = action;
}

// -------------------------------------------------------------

// 函数：设置面向方向
int to_front(int d)
{
	object me = this_object();

	d = range_value(d, 1, 8);

	if (get_d(me) != d)
	{
		set_d(me, d);
		send_user(get_scene_object_2(me, USER_TYPE), "%c%d%c", 0x5e, getoid(me), get_d(me));
	}
	else
		send_user(me, "%c%d%c", 0x5e, getoid(me), get_d(me)); // 客户端要求回馈

	return d;
}

// -------------------------------------------------------------

// 函数：人物设置函数
void setup()
{
	object me = this_object();

	set_char_type(PLAYER_TYPE_1);
	enable_player();

	if (!clonep(me))
		return;

	set_heart_timer(me, set_heart_timer_2(me, 0));
	set_heart_loop(me, 10); // 循环心跳：１秒钟
	me->heart_beat();
	set_heart_beat(1);
}

private
static int Speed; // 攻击速度

// 函数：累加攻击速度
int inc_attack_speed() { return ++Speed; }

void set_heart_beat_status(int flag)
{
	set_heart_beat(flag);
}

// 函数：心跳处理
void heart_beat() { __FILE__->heart_beat_callout(this_object()); }

// 函数：心跳处理(在线更新)
void heart_beat_callout(object me) // 每 0.1 秒 heart_timer + 1, 当 heart_count 为 0 时进入
{
	object who;
	string file, arg;
	int heart, count;

	heart = get_heart_timer(me);											   // 获取心跳时钟(主)
	count = get_heart_count_2(me);											   // 获取心跳标记
	count = set_heart_count_2(me, count - abs(heart - get_heart_timer_2(me))); // 主辅心跳之差

	if (count < 1)
	{
		switch (get_heart_state(me))
		{
		case FIGHT_STAT: // 普通攻击, 特殊技(动作)
			set_heart_state(me, FIGHT_STAT_DONE);
			me->add_2("go_count.count2", 2);
			set_heart_count_2(me, 2);
			if (who = me->get_enemy_3())
			{
				if (stringp(file = me->get_perform_file()) && load_object(file) && file->perform_done(me, who) == 2) // 特技攻击(完成)
					;

				else if (stringp(file = me->get_perform_2_file()) && load_object(file) && file->perform_done(me, who) == 2) // 特技攻击(循环)(完成)
					;

				else
					switch (me->get_weapon_code()) // 普通攻击(完成)
					{
						//                       case UNARMED : case THROWING :
					default:
						CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED);
						break;
					case BLADE:
						CHAR_FIGHT_D->attack_done(me, who, HIT_BLADE);
						break;
					case SWORD:
						CHAR_FIGHT_D->attack_done(me, who, HIT_SWORD);
						break;
					case SPEAR:
						CHAR_FIGHT_D->attack_done(me, who, HIT_SPEAR);
						break;
					case STICK:
						CHAR_FIGHT_D->attack_done(me, who, HIT_STICK);
						break;
					}

				if (who = me->get_enemy_5()) // 顺势推舟
				{
					switch (me->get_weapon_code()) // 自动反击(完成)
					{
						//                               case UNARMED : case THROWING :
					default:
						CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED);
						break;
					case BLADE:
						CHAR_FIGHT_D->attack_done(me, who, HIT_BLADE);
						break;
					case SWORD:
						CHAR_FIGHT_D->attack_done(me, who, HIT_SWORD);
						break;
					case SPEAR:
						CHAR_FIGHT_D->attack_done(me, who, HIT_SPEAR);
						break;
					case STICK:
						CHAR_FIGHT_D->attack_done(me, who, HIT_STICK);
						break;
					}
					me->add_mp(-PF_FILE_02321->get_sub_mp_2(me)); // 扣减法力
					me->set_enemy_5(0);
				}
			}
			me->set_perform_file(0); // 重要：清除非法特技
			if (!me)
				return; // 死亡退出
			break;

		case MAGIC_STAT: // 发放法术(动作)
			set_heart_state(me, WALK_STAT);
			USER_HEART_D->heart_beat_cast(me);
			if (!me)
				return; // 死亡退出
			break;

		default:
			set_heart_state(me, WALK_STAT); // 允许 go 指令
			break;
		}

		if (get_heart_count_2(me) < 1)
		{
			if (stringp(arg = me->get_force_command()))
			{
				me->force_me(arg);
				me->set_force_command(0);
			}
			if (get_heart_count_2(me) < 1)
			{
				if (!me->get("new_heart"))
					USER_HEART_D->heart_beat_attack(me);
			}
		}
	}
	else
		set_heart_count(me, count); // 重设心跳标志(主), 0.? 秒进入心跳

	set_heart_timer_2(me, heart); // 更新心跳时钟(辅), 表示其已处理
}

private
static int PayMoneyBuyItem = 0; // 通过点数购买道具中
private
static string BuyItemCmdString = ""; // 通过点数购买道具命令串
private
static int PayType; // 类型 1 通过点数购买道具 2 验证序列号

// 函数：获取购买道具标志
int get_pay_money_buy_item() { return PayMoneyBuyItem; }

// 函数：设置购买道具标志
int set_pay_money_buy_item(int flag) { return PayMoneyBuyItem = flag; }

// 函数：获取购买道具命令串
string get_buy_item_cmd_string() { return BuyItemCmdString; }

// 函数：设置购买道具命令串
string set_buy_item_cmd_string(string arg) { return BuyItemCmdString = arg; }

int get_pay_type() { return PayType; }

// 函数：设置类型
int set_pay_type(int flag) { return PayType = flag; }

//增加防沉迷引导性提示.
void get_more_tips(object me)
{
	send_user(me, "%c%c%d%s", 0x43, 10, 0, HIY "防沉迷系统会让您在游戏里的经验、收益都将随着时间变化而减少，最后将无法获取游戏收益.\n" NOR + HIY "如果您之前不慎身份证填写错误或使用非身份证以外证件注册，请及时至官方网站的会员中心帐号管理处进行“实名验证”修改身份证信息.");
	send_user(me, "%c%s", ';', "防沉迷系统会让您在游戏里的经验、收益都将随着时间变化而减少，最后将无法获取游戏收益.\n如果您之前不慎身份证填写错误或使用非身份证以外证件注册，请及时至官方网站的会员中心帐号管理处进行“实名验证”修改身份证信息.");
}

private
static int HeartSec = 0; // 心跳计时

// 函数：获取心跳计时
int get_heart_sec() { return HeartSec; }

// 函数：设置心跳计时
int set_heart_sec(int point) { return HeartSec = point; }

// 函数：增添心跳计时
int add_heart_sec(int point) { return set_heart_sec(HeartSec + point); }

// 函数：心跳处理(循环)
void heart_beat_loop(int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) { __FILE__->heart_beat_loop_callout(this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout(object me, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) // 每１秒处理
{
	int sec, yuan, time, type, add_hp, add_mp, hoi_nguyen_khi;
	string result, *key;
	int i, size, index, p, z, x, y, x2, y2;
	string name, fileobject;
	object *user, item1, item2, *equip, *obj, zombie, item, map, who, item5;
	object *getuser2 = get_scene_object_2(me, USER_TYPE);
	USER_EFFECT_D->into_effect(me, effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8); // 征状处理

	//      USER_HEART_D->heart_beat_other(me);

	if (me->get_perform_file() && gone_time(me->get_perform_enable_time()) > 8) // 删除聚气效果
	{
		USER_SKILL_D->cancel_enabled_perform(me, "");										 // 扣减法力
		me->set_perform_file(0);															 // 前句没清空
		send_user(getuser2, "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_STOP); // 删除聚气
	}
	/*// if (me->get_pay_money_buy_item()			// 通过点数购买道具中？
	// 	&& me->get_buy_item_cmd_string() != "") // 存在购买道具命令串？
	// {
	// 	result = get_exchange_pay_string(me);
	// 	if (MAIN_D->get_host_type() == 0)
	// 		result = "10000";
	// }

	// if (me->get_pay_money_buy_item()		   // 通过点数购买道具中？
	// 	&& me->get_buy_item_cmd_string() != "" // 存在购买道具命令串？
	// 	&& result != "")					   // 收到扣点返回结果？
	// {
	// 	type = me->get_pay_type();
	// 	switch (type)
	// 	{
	// 	case 1:
	// 		if (MAIN_D->get_host_type() == 4 || MAIN_D->get_host_type() == 0)
	// 		{
	// 			if (MAIN_D->get_host_type() == 0)
	// 			{
	// 				result = "ok:1:1";
	// 			}
	// 			key = explode(result, ":");
	// 			if (key[0] == "ok")
	// 			{
	// 				if (sizeof(key) == 3)
	// 				{
	// 					write_user(me, ECHO "Tài khoản giảm đi %d Kim Nguyên Bảo.", to_int(key[2]));
	// 					result = me->get_buy_item_cmd_string();
	// 					me->set_buy_item_cmd_string("");
	// 					me->set_pay_money_buy_item(8); // 通过点数购买道具成功！
	// 					BUY_CMD->main(me, result);	   // 获得相关道具！
	// 				}
	// 				else
	// 					send_user(me, "%c%s", '!', "Giá trị phản hồi không đúng" + result);
	// 			}
	// 			else
	// 			{
	// 				if (key[0] == "fail")
	// 				{
	// 					if (sizeof(key) == 2)
	// 					{
	// 						switch (to_int(key[1]))
	// 						{
	// 						case 1:
	// 							send_user(me, "%c%s", '!', "Thời gian quá thời hạn");
	// 							break;
	// 						case 2:
	// 							send_user(me, "%c%s", '!', "Tài khoản không đủ");
	// 							break;
	// 						}
	// 					}
	// 					else
	// 						send_user(me, "%c%s", '!', "Giá trị phản hồi không đúng" + result);
	// 					me->set_pay_money_buy_item(0);
	// 					me->set_buy_item_cmd_string("");
	// 				}
	// 			}
	// 			break;
	// 		}
	// 		if (result[0] >= '0' && result[0] <= '9') // 0, 或者正数, 表示扣点成功
	// 		{
	// 			send_user(me, "%c%s", '!', sprintf("Ngươi còn dư %d Kim Nguyên Bảo.", to_int(result)));
	// 			write_user(me, ECHO "Ngươi còn dư %d Kim Nguyên Bảo.", to_int(result));
	// 			result = me->get_buy_item_cmd_string();
	// 			me->set_buy_item_cmd_string("");
	// 			me->set_pay_money_buy_item(8); // 通过点数购买道具成功！
	// 			BUY_CMD->main(me, result);	   // 获得相关道具！
	// 		}
	// 		else if (result[0] == '-')
	// 		{
	// 			me->set_pay_money_buy_item(0);
	// 			me->set_buy_item_cmd_string("");
	// 			me->set("paycount", to_int(result));
	// 			send_user(me, "%c%s", '!', "Tài khoản không đủ");
	// 		}
	// 		else
	// 		{
	// 			me->set_pay_money_buy_item(0);
	// 			me->set_buy_item_cmd_string("");
	// 			send_user(me, "%c%s", '!', "Mua vật phẩm thất bại" + result);
	// 		}
	// 		break;
	// 	case 2:
	// 		if (result[0] && result[0] != 'Y')
	// 		{
	// 			me->set_buy_item_cmd_string("");
	// 			me->set_pay_money_buy_item(0);
	// 			me->set_pay_type(0);
	// 		}
	// 		switch (result[0])
	// 		{
	// 		case 'P':
	// 			send_user(me, "%c%s", '!', "Số lần sai lầm quá nhiều");
	// 			break;
	// 		case 'H':
	// 			send_user(me, "%c%s", '!', "Cung cấp mã kích hoạt đã sử dụng");
	// 			break;
	// 		case 'N':
	// 			send_user(me, "%c%s", '!', "Cung cấp dẫy số không chính xác");
	// 			break;
	// 		case 'Y':
	// 			result = me->get_buy_item_cmd_string();
	// 			me->set_buy_item_cmd_string("");
	// 			me->set_pay_money_buy_item(8);		// 通过点数购买道具成功！
	// 			"/cmd/user/talk"->main(me, result); // 获得相关道具！
	// 			break;
	// 		default:
	// 			send_user(me, "%c%s", '!', "Kiểm tra mã sai !" + result);
	// 			break;
	// 		}
	// 		break;
	// 	case 3: // 充值
	// 		if (result[0])
	// 		{
	// 			me->set_buy_item_cmd_string("");
	// 			me->set_pay_money_buy_item(0);
	// 			me->set_pay_type(0);
	// 		}
	// 		if (result[0] >= '0' && result[0] <= '9')
	// 		{
	// 			send_user(me, "%c%s", '!', sprintf("Ngươi nạp thành công %d Kim Nguyên Bảo.", to_int(result)));
	// 			write_user(me, ECHO "Ngươi thêm %d Kim Nguyên Bảo.", to_int(result));
	// 			log_file("deposit.dat", sprintf("%s %s(%d) nạp thành công %d Kim Nguyên Bảo\n", short_time(), me->get_id(), me->get_number(), to_int(result)));
	// 			break;
	// 		}
	// 		switch (result[0])
	// 		{
	// 		case '#':
	// 			send_user(me, "%c%s", '!', "Thao tác sai !");
	// 			break;
	// 		case 'S':
	// 			send_user(me, "%c%s", '!', "Phục vụ chưa đăng ký");
	// 			break;
	// 		case 'N':
	// 			send_user(me, "%c%s", '!', "Cung cấp dẫy số không chính xác");
	// 			break;
	// 		case 'X':
	// 			send_user(me, "%c%s", '!', "Truyền vào số liệu không hoàn chỉnh");
	// 			break;
	// 		case 'I':
	// 		case 'X':
	// 			send_user(me, "%c%s", '!', "Ngươi sử dụng trướng hào không tồn tại");
	// 			break;
	// 			break;
	// 		default:
	// 			send_user(me, "%c%s", '!', "Nạp thất bại " + result);
	// 			break;
	// 		}
	// 		break;
	// 	case 4:
	// 		if (MAIN_D->get_host_type() == 0)
	// 		{
	// 			if (is_god(me))
	// 				result = sprintf("ok:%d", me->get("lb"));
	// 		}
	// 		key = explode(result, ":");
	// 		if (key[0] == "ok")
	// 		{
	// 			if (sizeof(key) == 2)
	// 			{
	// 				result = me->get_buy_item_cmd_string();
	// 				me->set_buy_item_cmd_string("");
	// 				me->set_pay_money_buy_item(8);				 // 通过点数购买道具成功！
	// 				"/cmd/user/talk"->main(me, result + key[1]); // 获得相关道具！
	// 				me->set_pay_money_buy_item(0);				 // 初始状态
	// 			}
	// 			else
	// 				send_user(me, "%c%s", '!', "Lĩnh đạo cụ kết quả không đúng " + result);
	// 		}
	// 		else
	// 		{
	// 			if (key[0] == "fail")
	// 			{
	// 				if (sizeof(key) == 2)
	// 				{
	// 					switch (to_int(key[1]))
	// 					{
	// 					case 1:
	// 						send_user(me, "%c%s", '!', "Thời gian quá thời hạn");
	// 						break;
	// 					case 2:
	// 						"/quest/php"->send_error_tips(me);
	// 						break;
	// 					}
	// 				}
	// 				else
	// 					send_user(me, "%c%s", '!', "Lĩnh đạo cụ kết quả không đúng " + result);
	// 				me->set_pay_money_buy_item(0);
	// 				me->set_buy_item_cmd_string("");
	// 			}
	// 		}
	// 		break;
	// 	case 5:
	// 		if (MAIN_D->get_host_type() == 0)
	// 		{
	// 			result = "ok:1000";
	// 		}
	// 		if (MAIN_D->get_host_type() == 1000)
	// 		{
	// 			result = sprintf("ok:%d", "sys/sys/test_db"->get_yuanbao(me));
	// 		}

	// 		if (MAIN_D->get_host_type() == 6012)
	// 		{
	// 			//log_file("php.date", "5"+result+"\n");
	// 			result = replace_string(result, "\n", "");
	// 			result = replace_string(result, "\r", "");
	// 			key = explode(result, ",");
	// 			if (key[0] == "FF")
	// 			{
	// 				send_user(me, "%c%s", '!', "Lỗi kiểm tra kết quá " + result + ".");
	// 				me->set_buy_item_cmd_string("");
	// 				me->set_pay_money_buy_item(0); // 通过点数购买道具成功！
	// 				break;
	// 			}
	// 			if (key[0] == "21")
	// 			{
	// 				if (sizeof(key) == 6 && key[5][0] == '1')
	// 				{
	// 					write_user(me, ECHO "Ngươi dư %d Kim Nguyên Bảo. Tổng hiện có là %d", to_int(key[3]), to_int(key[4]));
	// 					me->set_buy_item_cmd_string("");
	// 					me->set_pay_money_buy_item(0); // 通过点数购买道具成功！
	// 												   //        				send_user( me, "%c%s", '!', sprintf( "Số dư tài khoản của bạn là %d .", to_int(key[1]) ) );
	// 					send_user(me, "%c%c%d%d", 0x45, 2, to_int(key[3]), to_int(key[3]));
	// 				}
	// 				else
	// 				{
	// 					if (sizeof(key) != 6)
	// 						send_user(me, "%c%s", '!', "Tuần tra hạng không đủ 6 vị" + result + ".");
	// 					if (key[5] != "1")
	// 						send_user(me, "%c%s", '!', "Tuần tra cuối cùng không phải 1" + result + ".");
	// 				}
	// 			}
	// 			me->set_buy_item_cmd_string("");
	// 			me->set_pay_money_buy_item(0); // 通过点数购买道具成功！
	// 			break;
	// 		}
	// 		key = explode(result, ":");
	// 		me->set("phpbalance", 1);
	// 		if (key[0] == "ok")
	// 		{
	// 			if (sizeof(key) == 2)
	// 			{
	// 				write_user(me, ECHO "Số dư tài khoản của bạn là %d .", to_int(key[1]));
	// 				me->set_buy_item_cmd_string("");
	// 				me->set_pay_money_buy_item(0); // 通过点数购买道具成功！
	// 											   //        				send_user( me, "%c%s", '!', sprintf( "Số dư tài khoản của bạn là %d .", to_int(key[1]) ) );
	// 				send_user(me, "%c%c%d", 0x45, 2, to_int(key[1]));
	// 			}
	// 			else
	// 				send_user(me, "%c%s", '!', "Kiểm tra số dư thất bại " + result);
	// 		}
	// 		else
	// 		{
	// 			if (key[0] == "fail")
	// 			{
	// 				if (sizeof(key) == 2)
	// 				{
	// 					switch (to_int(key[1]))
	// 					{
	// 					case 1:
	// 						send_user(me, "%c%s", '!', "Thời gian quá thời hạn");
	// 						break;
	// 					case 2:
	// 						send_user(me, "%c%c%d", 0x45, 2, 0);
	// 						break;
	// 					}
	// 				}
	// 				else
	// 					send_user(me, "%c%s", '!', "Kiểm tra kết quả không đúng " + result);
	// 				me->set_pay_money_buy_item(0);
	// 				me->set_buy_item_cmd_string("");
	// 			}
	// 		}
	// 		break;
	// 	case 6:
	// 		if (MAIN_D->get_host_type() == 4 || MAIN_D->get_host_type() == 0)
	// 		{
	// 			if (MAIN_D->get_host_type() == 0)
	// 			{
	// 				result = "ok:1:1";
	// 			}
	// 			key = explode(result, ":");
	// 			if (key[0] == "ok")
	// 			{
	// 				if (sizeof(key) == 3)
	// 				{
	// 					write_user(me, ECHO "Ngươi dư %d Kim Nguyên Bảo.", to_int(key[2]));
	// 					result = me->get_buy_item_cmd_string();
	// 					me->set_buy_item_cmd_string("");
	// 					me->set_pay_money_buy_item(8);		   // 通过点数购买道具成功！
	// 					"/cmd/base/buyitem"->main(me, result); // 获得相关道具！
	// 					send_user(me, "%c%c%d", 0x45, 2, to_int(key[2]));
	// 				}
	// 				else
	// 					send_user(me, "%c%s", '!', "Mua đạo cụ kết quả không đúng " + result);
	// 			}
	// 			else
	// 			{
	// 				if (key[0] == "fail")
	// 				{
	// 					if (sizeof(key) == 2)
	// 					{
	// 						switch (to_int(key[1]))
	// 						{
	// 						case 1:
	// 							send_user(me, "%c%s", '!', "Thời gian quá thời hạn");
	// 							break;
	// 						case 2:
	// 							if (me->get_buy_item_cmd_string() == "99 1 1")
	// 								send_user(me, "%c%s", ';', "Ngươi không đủ Kim Nguyên Bảo để mua vật phẩm ");
	// 							else
	// 								send_user(me, "%c%s", '!', "Tài khoản không đủ");
	// 							break;
	// 						}
	// 					}
	// 					else
	// 						send_user(me, "%c%s", '!', "Giá trị phản hồi không đúng" + result);
	// 					me->set_pay_money_buy_item(0);
	// 					me->set_buy_item_cmd_string("");
	// 				}
	// 			}
	// 			break;
	// 		}
	// 		else if (MAIN_D->get_host_type() == 6012)
	// 		{
	// 			//log_file("php.date", "6: "+result+"\n");
	// 			result = replace_string(result, "\n", "");
	// 			result = replace_string(result, "\r", "");
	// 			key = explode(result, ",");
	// 			if (key[0] == "FF")
	// 			{
	// 				send_user(me, "%c%s", '!', "Mua đạo cụ lỗi " + result + ".");
	// 				me->set_pay_money_buy_item(0);
	// 				me->set_buy_item_cmd_string("");
	// 			}
	// 			else
	// 			{
	// 				if (sizeof(key) == 8)
	// 				{
	// 					switch (key[7])
	// 					{
	// 					case "1":
	// 						send_user(me, "%c%s", '!', sprintf("Ngươi tiêu phí %d Kim Nguyên Bảo.", to_int(key[6])));
	// 						write_user(me, ECHO "Ngươi tiêu phí %d Kim Nguyên Bảo.", to_int(key[6]));
	// 						result = me->get_buy_item_cmd_string();
	// 						me->set_buy_item_cmd_string("");
	// 						me->set_pay_money_buy_item(8);		   // 通过点数购买道具成功！
	// 						"/cmd/base/buyitem"->main(me, result); // 获得相关道具！
	// 															   // 重查余额
	// 						db_user_pay(me, sprintf("210.48.144.183:2500\n"
	// 												"21,\"%s\",%d\r\n",
	// 												me->get_real_id(), me->get_acountno()));
	// 						me->set_pay_money_buy_item(1);
	// 						me->set_pay_type(5);
	// 						me->set_buy_item_cmd_string("  ");
	// 						break;
	// 					case "-1":
	// 						send_user(me, "%c%s", '!', "Người sử dụng không tồn tại !");
	// 						break;
	// 					case "-2":
	// 						send_user(me, "%c%s", '!', "Số liệu không tương xứng !");
	// 						break;
	// 					case "-3":
	// 					case "-4":
	// 						send_user(me, "%c%s", '!', "Không đủ ngạch trống !");
	// 						break;
	// 					case "-5":
	// 						send_user(me, "%c%s", '!', "Trò chơi số hiệu không đúng");
	// 						break;
	// 					case "-6":
	// 						send_user(me, "%c%s", '!', "Sản phẩm số hiệu không đúng");
	// 						break;
	// 					case "-98":
	// 					case "-99":
	// 						send_user(me, "%c%s", '!', "Số liệu lỗi !");
	// 						break;
	// 					case "-255":
	// 						send_user(me, "%c%s", '!', "Khấu khí phục vụ khí bận rộn");
	// 						break;
	// 					case "-256":
	// 						send_user(me, "%c%s", '!', "Khấu khí phục vụ khí không tồn tại !");
	// 						break;
	// 					case "-257":
	// 						send_user(me, "%c%s", '!', "Khấu khí phục vụ khí mất hiệu lực !");
	// 						break;
	// 					}
	// 				}
	// 				else
	// 					send_user(me, "%c%s", '!', "Mua đạo cụ lỗi " + result + ".");
	// 			}
	// 			if (me->get_pay_money_buy_item() != 1)
	// 			{
	// 				me->set_pay_money_buy_item(0);
	// 				me->set_buy_item_cmd_string("");
	// 			}
	// 			break;
	// 		}
	// 		if (result[0] >= '0' && result[0] <= '9') // 0, 或者正数, 表示扣点成功
	// 		{
	// 			send_user(me, "%c%s", '!', sprintf("Ngươi còn dư %d Kim Nguyên Bảo.", to_int(result)));
	// 			write_user(me, ECHO "Ngươi còn dư %d Kim Nguyên Bảo.", to_int(result));
	// 			result = me->get_buy_item_cmd_string();
	// 			me->set_buy_item_cmd_string("");
	// 			me->set_pay_money_buy_item(8);		   // 通过点数购买道具成功！
	// 			"/cmd/base/buyitem"->main(me, result); // 获得相关道具！
	// 		}
	// 		else if (result[0] == '-')
	// 		{
	// 			me->set_pay_money_buy_item(0);
	// 			me->set_buy_item_cmd_string("");
	// 			me->set("paycount", to_int(result));
	// 			send_user(me, "%c%s", '!', "Tài khoản không đủ");
	// 		}
	// 		else
	// 		{
	// 			me->set_pay_money_buy_item(0);
	// 			me->set_buy_item_cmd_string("");
	// 			send_user(me, "%c%s", '!', "Mua vật phẩm thất bại" + result);
	// 		}
	// 		break;
	// 	case 7:
	// 		me->set_pay_money_buy_item(8);
	// 		"/cmd/user/consign"->php_result(me, me->get_buy_item_cmd_string(), result);
	// 		me->set_pay_money_buy_item(0);
	// 		me->set_buy_item_cmd_string("");
	// 		break;
	// 	case 8:
	// 		me->set_pay_type(0);
	// 		if (MAIN_D->get_host_type() == 0)
	// 		{
	// 			result = "fail:2";
	// 		}
	// 		key = explode(result, ":");
	// 		me->set("phpbalance", 1);
	// 		if (key[0] == "ok")
	// 		{
	// 			if (sizeof(key) == 2)
	// 			{
	// 				write_user(me, ECHO "Số dư tài khoản của bạn là %d .", to_int(key[1]));
	// 				me->set_buy_item_cmd_string("");
	// 				me->set_pay_money_buy_item(0); // 通过点数购买道具成功！
	// 				if (to_int(key[1]) >= 390)
	// 					"cmd/base/buyitem"->main(me, "99 0 1");
	// 				else
	// 				{
	// 					send_user(me, "%c%s", ':', "    Trên người ngươi không đủ Kim Nguyên Bảo, hãy nạp vào rồi lại đến mua\n" ESC "Rời khỏi");
	// 					return;
	// 				}
	// 			}
	// 			else
	// 				send_user(me, "%c%s", '!', "Kiểm tra số dư thất bại " + result);
	// 		}
	// 		else
	// 		{
	// 			if (key[0] == "fail")
	// 			{
	// 				if (sizeof(key) == 2)
	// 				{
	// 					switch (to_int(key[1]))
	// 					{
	// 					case 1:
	// 						send_user(me, "%c%s", '!', "Thời gian quá thời hạn");
	// 						break;
	// 					case 2:
	// 						send_user(me, "%c%s", ':', "    Trên người ngươi không đủ Kim Nguyên Bảo, hãy nạp vào rồi lại đến mua\n" ESC "Rời khỏi");
	// 						//        						send_user(me, "%c%c%d", 0x45, 2, 0 );
	// 						break;
	// 					}
	// 				}
	// 				else
	// 					send_user(me, "%c%s", '!', "Kiểm tra kết quả không đúng " + result);
	// 				me->set_pay_money_buy_item(0);
	// 				me->set_buy_item_cmd_string("");
	// 			}
	// 		}
	// 		break;
	// 	}
	// }*/

	sec = me->add_heart_sec(1);

	if (me->get_fam_name() == FAMILY_1)
	{
		if (sec % 3 == 0)
			me->add_yuan(1);													// 每三秒恢复元气
		if ((sec % 3 == 0) && (time() - me->get_perform(PF_FLAG_03172) < 1800)) // 护体金罡－元气复生
		{
			yuan = me->get_yuan();
			if (me->add_yuan(1) != yuan)
			{
				send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), 31721, 1, OVER_BODY, PF_ONCE);
			}
		}
		if (me->get_perform(PF_FLAG_03172) && time() - me->get_perform(PF_FLAG_03172) > 1800)
		{
			me->set_perform(PF_FLAG_03172, 0);
			send_user(me, "%c%s", '!', "Nguyên khí hiệu quả sống lại đã xong");
		}
	}
	else
	{
		if (me->get_perform(PF_FLAG_03172))
			me->set_perform(PF_FLAG_03172, 0);
		if (sec % 3 == 0)
			me->add_yuan(1); // 每三秒恢复元气
	}
	x = get_x(me);
	y = get_y(me);
	if (!me->get_2("speed") || me->get("phihanh") || me->get_2("speed.z") != get_z(me))
	{
		me->delete ("phihanh");
		me->set_2("speed.z", get_z(me));
		me->set_2("speed.x", x);
		me->set_2("speed.y", y);
	}
	else
	{
		x2 = me->get_2("speed.x");
		y2 = me->get_2("speed.y");
		if (x2 != x || y2 != y)
		{
			x2 = abs(x - x2);
			y2 = abs(y - y2);
			if ((x2 == 6 || y2 == 6))
			{
				me->add_2("speed.t", 1);
			}
			else if (me->get_2("speed.t") > 0)
			{
				me->add_2("speed.t", -1);
			}
			if (((x2 > 6 || y2 > 6) && (x2 < 9 && y2 < 9)) || me->get_2("speed.t") >= 2)
			{
				me->delete_2("speed.t");
				log_file("speed.txt", sprintf("%s: %s(%d) Chạy quá tốc độ (%dx%d)\n", short_time(), me->get_name(), me->get_number(), x2, y2));
				tell_user(me, sprintf("Chạy quá tốc độ. Phạt Choáng 3 giây!"));
				set_effect(me, EFFECT_CHAR_NO_MOVE, 3);
				me->add_to_scene(get_z(me), me->get_2("speed.x"), me->get_2("speed.y"));
			}
			else
			{
				me->set_2("speed.x", x);
				me->set_2("speed.y", y);
			}
		}
	}
	if (objectp(item5 = present("Thẻ VIP", me, 1, MAX_CARRY * 4)) &&
		item5->get_lock_time() &&
		item5->get_lock_time() > time() &&
		get_z(me) != 887 &&
		me->get_save("thevip") >= 1)
	{
		if (sec % 3 == 0)
			me->add_save("theviptime", 1);
	}
	if (me->get_save("thevip") >= 1 && get_z(me) == 887 && me->get_save("theviptime") > 0)
	{
		if (sec % 1 == 0)
			me->add_save("theviptime", -1);
	}
	if (me->get_save("thevip") >= 1 && get_z(me) == 887 && me->get_save("theviptime") < 0)
	{
		me->set_login_flag(2);
		set_invisible(me, 1);
		set_effect(me, EFFECT_USER_LOGIN, 4);
		me->add_to_scene(80, 256, 147);
		write_user(me, ECHO "Thời gian Tu luyện Võ công của bạn đã hết.");
		write_user(me, ECHO "Thời gian Tu luyện Võ công của bạn đã hết.");
		write_user(me, ECHO "Thời gian Tu luyện Võ công của bạn đã hết.");
	}
	if (objectp(item5 = present("Thẻ VIP", me, 1, MAX_CARRY * 4)) &&
		item5->get_lock_time() &&
		item5->get_lock_time() < time() &&
		me->get_save("thevip") >= 1)
	{
		if (get_z(me) == 887)
		{
			me->set_login_flag(2);
			set_invisible(me, 1);
			set_effect(me, EFFECT_USER_LOGIN, 4);
			me->add_to_scene(80, 256, 147);
			write_user(me, ECHO "Thẻ VIP đã hết hạn sử dụng.");
			write_user(me, ECHO "Thẻ VIP đã hết hạn sử dụng.");
			write_user(me, ECHO "Thẻ VIP đã hết hạn sử dụng.");
			item5->remove_from_user();
			destruct(item5);
			me->set_save("thevip", 0);
			if (!me->get_vip())
			{
				send_user(me, "%c%c%c", 0xA2, 4, 0);
			}
		}
		else
		{
			write_user(me, ECHO "Thẻ VIP đã hết hạn sử dụng.");
			write_user(me, ECHO "Thẻ VIP đã hết hạn sử dụng.");
			write_user(me, ECHO "Thẻ VIP đã hết hạn sử dụng.");
			item5->remove_from_user();
			destruct(item5);
			me->set_save("thevip", 0);
			if (!me->get_vip())
			{
				send_user(me, "%c%c%c", 0xA2, 4, 0);
			}
		}
	}
	// if (me->get_save("hoiphucnguyenkhi") > 0)
	// {
	// 	if (sec % 1 == 0)
	// 	{
	// 		me->add_yuan(4);
	// 		me->add_save("hoiphucnguyenkhi", -1);
	// 	}
	// }
	// if (me->get_save("hoiphuckhihuyet") > 0)
	// {
	// 	if (sec % 2 == 0)
	// 	{
	// 		me->add_hp(100);
	// 		me->add_save("hoiphuckhihuyet", -2);
	// 		send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE);
	// 	}
	// }
	// if (me->get_save("hoiphucphapluc") > 0)
	// {
	// 	if (sec % 2 == 0)
	// 	{
	// 		me->add_mp(100);
	// 		me->add_save("hoiphucphapluc", -2);
	// 		send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE);
	// 	}
	// }
	if (get_z(me) == 704 && me->get_save("vaotu") > 0)
	{
		if (sec % 1 == 0)
			me->add_save("vaotu", -1);
	}
	// if (me->get_save("nhanquaonline") > 0)
	// {
	// 	if (sec % 1 == 0)
	// 		me->add_save("nhanquaonline", -1);
	// }
	if (get_z(me) == 704 && me->get_save("vaotu") < 1)
	{
		me->delete_save("vaotu");
		me->set_save("gietnguoi", 0);
		me->set_login_flag(2);
		set_invisible(me, 1);
		set_effect(me, EFFECT_USER_LOGIN, 4);
		me->add_to_scene(391, 86, 70);
		CHAT_D->rumor_channel(0, CHAT + sprintf(HIM "Người chơi %s (%d) lúc ở Nhà Ngục đã biết sám hối tội lỗi của mình, nên được Chu Vương ân xá trả lại tự do !!", me->get_name(), me->get_number()));
	}
	if (get_z(me) >= 533 && get_z(me) <= 549 && MAIN_D->get_kenh() != KENH_CUTHUDAO && KENH_CUTHUDAO != 0)
	{
		me->add_to_scene(80, 285 + random(10), 115 + random(15));
	}
	if (me->have_title("Z888"))
	{
		"sys/party/vst4"->check_revive(me);
		"sys/party/vst4"->check_revive2(me);
		"sys/party/vst4"->check_revive3(me);
		"sys/party/vst4"->check_revive4(me);
	}
	if ((get_z(me) == 888 || get_z(me) == 889) && me->get_org_name() == "" && !is_god(me))
	{
		me->set_login_flag(2);
		set_invisible(me, 1);
		set_effect(me, EFFECT_USER_LOGIN, 4);
		me->add_to_scene(80, 285 + random(10), 115 + random(15));
		write_user(me, ECHO "Bạn chưa gia nhập Bang, không thể vào Vô Song Thành.");
	}
	if ((get_z(me) == 888 || get_z(me) == 889) && !is_god(me))
	{
		"/sys/party/vstfix"->check_dk(me);
	}
	/*	if( me->get_pk() > 0 )
		{
			if( sec % 900 == 0)
			{
			me->add_pk(-1);
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			}
		}*/
	if (get_z(me) != 704 && me->get_pk() >= 300)
	{
		map = get_map_object(get_z(me));
		if (sec % 1800 == 0)
		{
			if (me->add_hp(-(me->get_max_hp() / 2)) > 0)
			{
				me->add_hp(-(me->get_max_hp() / 2));
			}
			else
			{
				if (map->get_no_fight())
				{
					me->set_hp(0);
					me->set_die(6);
				}
				else if (map->is_changping())
				{
					me->set_hp(0);
					me->set_die(9);
				}
				else if (get_z(me) < 885 || map->is_org_map() || map->is_copy_scene() || map->is_pvp())
				{
					me->set_hp(0);
					me->set_die(1);
				}
				else if (map->get_client_id() == 885 || map->get_client_id() == 887 || map->get_client_id() == 891 || map->is_wushuang())
				{
					me->set_hp(0);
					me->set_die(5);
				}
			}
			send_user(getuser2, "%c%d%w%c%c%c", 0x6f, getoid(me), 25163, 1, OVER_BODY, PF_ONCE);
			send_user(getuser2, "%c%d%w%c%c%c", 0x6f, getoid(me), 25164, 1, OVER_BODY, PF_ONCE);
			//	USER_D->user_channel(sprintf(HIM"Vì tội nghiệt quá nặng nề nên "HIC"%s (%d)"HIM" đã bị Lôi Thần dùng Ngũ Lôi Áp Đỉnh trừng phạt !!", me->get_name(), me->get_number() ));
			CHAT_D->rumor_channel(0, CHAT + sprintf(HIM "Vì tội nghiệp quá nặng nề nên %s (%d) đã bị Lôi Thần dùng Ngũ Lôi Áp Đỉnh trừng phạt !!", me->get_name(), me->get_number()));
		}
	}
	// if (me->get_save_2("timeAuto") && me->get("autoRun"))
	// {
	// 	"cmd/func/allfunc"->getItemAround(me);
	// }
	if (sec % 360 == 0) // 每六分钟处理
	{
		me->add_strength(1);
		//                                time = gone_time( me->get_login_time() );
		//                                me->set_game_time( me->get_game_time() + time );
		//                                me->set_login_time(time());
		USER_RANK_D->online_rank(me, 1);
		me->save();
		send_user(me, "%c%c%d", 0x49, 0x03, time()); // time() 防加速器
	}
	if (sec % 60 == 0)
	{
		"cmd/func/allfunc"->nap_the(me);
		if (get_z(me) >= 533 && get_z(me) <= 549)
			me->add_cuthudaotime(60);

		if (me->get_pk()) //洗红名
		{
			me->add_clean_pk_time(60);
			if (me->get_clean_pk_time() >= 1800)
			{
				me->set_clean_pk_time(0);
				me->add_pk(-0);
			}
		}
		if (me->get_vip()) // vip
			"item/sell/0061"->check_vip(me);
	}

	if (sec % 15 == 0) // 每１５秒处理
	{
		if (!me->is_die())
		{
			add_hp = 10;
			add_mp = 5;
			// Long Trạc Phượng Trạc
			item1 = me->get_equip(HAND_TYPE);
			if (objectp(item1))
			{
				if (item1->get_name() == "Long Trạc")
					name = "Phượng Trạc";
				else if (item1->get_name() == "Phượng Trạc")
					name = "Long Trạc";
				if (name)
				{
					if (arrayp(user = me->get_team()))
					{
						user -= ({0, me});
						size = sizeof(user);
						for (i = 0; i < size; i++)
						{
							if (!objectp(item2 = user[i]->get_equip(HAND_TYPE)) || item2->get_name() != name)
								continue;
							add_hp += add_hp / 10;
							if (sec % 30 == 0) // 2次加1/5
								add_mp += add_mp / 5;
							break;
						}
					}
				}
			}

			me->add_hp(add_hp);
			me->add_mp(add_mp);
		}

		// if (me->get_idle_time() >= 180)
		// {
		// 	me->set_idle_time(300);
		// 	QUIT_CMD->main(me, ""); // 断线僵尸超过３分钟退出
		// 	return;
		// }
		//----------------------------------------------------------------------------------------------------------
		if (item = me->get("12pet_item"))
		{
			if (item->get_lock_time() && time() > item->get_lock_time())
			{
				obj = me->get("zombie");
				size = sizeof(obj);
				if (size)
				{
					for (index = 0; index < size; index++)
					{
						zombie = obj[index];
						if (!objectp(zombie))
							continue;
						send_user(get_scene_object_2(zombie, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, get_x(zombie), get_y(zombie), 9414, 1, OVER_BODY, PF_ONCE);
						send_user(me, "%c%c%d", 0x2c, 0, getoid(zombie));
						zombie->remove_from_scene();
						destruct(zombie);
					}
					item->set_no_drop(0);
					item->set_no_get(0);
					me->delete ("12pet_item");
					me->delete ("zombie");
					me->delete_2("jiguan");
					USER_ENERGY_D->count_all_prop(me);
				}
				send_user(me, "%c%s", '!', "Vật phẩm " + item->get_name() + " đã sử dụng qua một tháng");
			}
		}

		if (item = me->get_equip(HAND_TYPE))
		/*{
			if(item->get_lock_time() && time() > item->get_lock_time())
			{
				if(sizeof_inventory(me, 1, MAX_CARRY) >= MAX_CARRY)
					{
						if(!item->get("del_power"))
						{
							USER_ENERGY_D->count_ap(me);  USER_ENERGY_D->count_cp(me);  USER_ENERGY_D->count_dp(me);
						item ->set("del_power",1);
						send_user(me,"%c%s",'!',"您的"+item->get_name()+"已经过了使用期.");
					}
					}
					else
					{
					me->remove_equip(HAND_TYPE);
					}
			}
		}*/
		{
			if (item->get_lock_time() && time() > item->get_lock_time())
			{
				//	MAILBOX->sys_mail(me->get_id(),me->get_number(),sprintf("Pháp bảo %s đã hết hạn sử dụng.",item->get_name()));
				item->remove_from_user();
				destruct(item);
				USER_ENERGY_D->count_all_prop(me);
			}
		}
		if (item = me->get_equip(BACK_TYPE))
		{
			if (item->get_lock_time() && time() > item->get_lock_time())
			{
				//	MAILBOX->sys_mail(me->get_id(),me->get_number(),sprintf("Trang bị %s đã hết hạn sử dụng.",item->get_name()));
				if (!item->is_nangcap())
				{
					item->remove_from_user();
					destruct(item);
					USER_ENERGY_D->count_all_prop(me);
				}
				else
				{

					if (item->get("aohoa"))
					{
						"cmd/std/mixaohoa"->xoa_aohoa(item, me);
					}
				}
			}
		}
		/*	if(item = me->get_equip(ARMOR_TYPE))
		{
			if(item->get_lock_time() && time() > item->get_lock_time())
			{
				item->remove_from_user();
				destruct(item);
				USER_ENERGY_D->count_all_prop(me);
			}
		}
		if(item = me->get_equip(HEAD_TYPE))
		{
			if(item->get_lock_time() && time() > item->get_lock_time())
			{
				item->remove_from_user();
				destruct(item);
				USER_ENERGY_D->count_all_prop(me);
			}
		}
		if(item = me->get_equip(NECK_TYPE))
		{
			if(item->get_lock_time() && time() > item->get_lock_time())
			{
				item->remove_from_user();
				destruct(item);
				USER_ENERGY_D->count_all_prop(me);
			}
		}
		if(item = me->get_equip(WAIST_TYPE))
		{
			if(item->get_lock_time() && time() > item->get_lock_time())
			{
				item->remove_from_user();
				destruct(item);
				USER_ENERGY_D->count_all_prop(me);
			}
		}
		if(item = me->get_equip(BOOTS_TYPE))
		{
			if(item->get_lock_time() && time() > item->get_lock_time())
			{
				item->remove_from_user();
				destruct(item);
				USER_ENERGY_D->count_all_prop(me);
			}
		}*/
		if (item = me->get_equip(FASHION_TYPE))
		{
			if (item->get_lock_time() && time() > item->get_lock_time())
			{
				//	MAILBOX->sys_mail(me->get_id(),me->get_number(),sprintf("Ngoại trang %s đã hết hạn sử dụng.",item->get_name()));
				item->remove_from_user();
				destruct(item);
				USER_ENERGY_D->count_all_prop(me);
				send_user(getuser2, "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
						  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
			}
		}
		if (me->get("wg_bl_15"))
		{
			map = get_map_object(get_z(me));
			if (!map->is_scum_map())
				me->delete ("wg_bl_15");
		}

		//----------------------------------------------------------------------------------------------------------
	}
	if (sec % 5 == 0)
	{
		if (me->get("autoRun"))
		{
			if (me->get("noKill") < 20)
			{
				me->add("noKill", 5);
			}
			else
			{
				if (!me->is_die())
				{
					z = get_z(me);
					if ((p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
					{
						x = p / 1000;
						y = p % 1000;
						me->add_to_scene(z, x, y);
					}
				}
				me->delete ("noKill");
			}
		}
	}
	if (sec % 1 == 0) //每5秒
	{
		equip = me->get_all_equip();
		for (i = 0; i < MAX_EQUIP; i++)
			if (equip[i] && equip[i]->get_lasting() >= 100)
			{
				if (i == 2 && get_effect(me, EFFECT_NO_WEAPON))
					continue;
				if (add_hp = equip[i]->get("hp+@"))
					me->add_hp(add_hp);
				if (add_mp = equip[i]->get("mp+@"))
					me->add_mp(add_mp);
				if (hoi_nguyen_khi = equip[i]->get("yuan+@"))
					me->add_yuan(hoi_nguyen_khi);
			}
	}
}

// 函数：特技攻击对手
int perform_action(object who) { return USER_ATTACK_D->perform_action(this_object(), who); }

// 函数：判断可以战斗
int can_fight(object who)
{
	object target = this_object();
	if (is_gm3(who) || is_gm3(target))
	{
		if (who->is_die() || target->is_die())
			return 0;
		return 1;
	}
	return USER_ATTACK_D->can_fight(this_object(), who);
}

// 函数：可以接受战斗
int can_be_fighted(object who)
{
	object target = this_object();
	if (is_gm3(who) || is_gm3(target))
	{
		if (who->is_die() || target->is_die())
			return 0;
		return 1;
	}
	return USER_ATTACK_D->can_be_fighted(this_object(), who);
}

// -------------------------------------------------------------

// 函数：列示给新玩家(对方进场景)
void show_to_user(object who)
{
	object me = this_object(), map;
	int id = getoid(me);
	int type = 0, armor, speed = 0;
	int gender;
	if (get_invisible(me) == 2 && who != me)
		return;
	armor = get_armor_code();
	if (get_effect(me, EFFECT_MAGIC_4243))
	{
		type = get_save("pf#4243");
		armor = type;
		speed = 2;
	}
	else if (get_effect(me, EFFECT_MAGIC_CARD))
	{
		type = get_save("magic_card");
		armor = type;
		speed = 2;
	}
	else if (me->get_save("temp_act"))
	{
		type = me->get_save("temp_act");
		armor = type;
		speed = 2;
	}
	else if (me->get("temp_act"))
	{
		type = me->get("temp_act");
		armor = type;
		speed = 2;
	}
	else
		type = get_head_code();
	if ("/sys/sys/count"->get_new_person())
		type = me->get_hair();
	//        if (MAIN_D->get_host_type()!=1000)
	if ("/sys/sys/count"->get_new_person())
		send_user(who, "%c%c%d%w%w%c%c%c%w%d%w%w%w%w%w%w%w%w%w%w%c%c%c%c%d%s", 0x69, 10, id,
				  get_x(me), get_y(me), get_d(me), get_char_type(), get_char_action(),
				  me->get_photo(), armor, me->get_armor_color_1(),
				  type, me->get_hair_color(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color(),
				  get_weapon_code_2(), me->get_weapon_color(), me->get_weapon_color_2(),
				  get_reincarnation(), get_reincarnation(),
				  get_hp_cent(), speed, get_number(), sprintf("%-16s%s", get_short(), get_title()));
	else
		send_user(who, "%c%c%d%w%w%c%c%c%d%w%w%c%c%c%c%d%s", 0x69, 0, id,
				  get_x(me), get_y(me), get_d(me), get_char_type(), get_char_action(),
				  armor, get_armor_color_1(), get_weapon_code_2(), get_reincarnation(), get_reincarnation(),
				  get_hp_cent(), speed, get_number(), sprintf("%-16s%s", get_short(), get_title()));

	if (!is_player(me))
		send_user(who, "%c%d%d", 0x66, id, 0xff6500);
	if (me->get_ride())
		send_user(who, "%c%d%d", 0x62, id, me->get_ride());
	CHAR_CHAR_D->send_loop_perform(me, who);   // 显示持续效果
	CHAR_CHAR_D->send_loop_perform_2(me, who); // 显示持续图标

	if (is_store_open())
		send_user(who, "%c%c%d%s", 0x3d, 81, id, get_store_name()); // 显示摆摊名号

	map = get_map_object(get_z(me));
	if (map && map->is_wushuang())
		send_user(who, "%c%c%d%s", 0xA2, 13, me->get_number(), me->get_org_name());
}

// 函数：列示给玩家看(新进入场景)
varargs void show_to_scene(object *user, int x, int y, int d, int add_pf, int add_pf_2)
{
	object me = this_object(), map;
	int id = getoid(me);
	int type = 0, armor, speed = 0;
	if (get_invisible(me) == 2)
		return;
	armor = get_armor_code();
	if (get_effect(me, EFFECT_MAGIC_4243))
	{
		type = get_save("pf#4243");
		armor = type;
		speed = 2;
	}
	else if (get_effect(me, EFFECT_MAGIC_CARD))
	{
		type = get_save("magic_card");
		armor = type;
		speed = 2;
	}
	else if (me->get_save("temp_act"))
	{
		type = me->get_save("temp_act");
		armor = type;
		speed = 2;
	}
	else if (me->get("temp_act"))
	{
		type = me->get("temp_act");
		armor = type;
		speed = 2;
	}
	else
		type = get_head_code();
	if ("/sys/sys/count"->get_new_person())
		type = me->get_hair();
	if ("/sys/sys/count"->get_new_person())
	{
		if (!add_pf)
			send_user(user, "%c%c%d%w%w%c%c%c%w%d%w%w%w%w%w%w%w%w%w%w%c%c%c%c%d%s", 0x69, 10, id,
					  get_x(me), get_y(me), get_d(me), get_char_type(), get_char_action(),
					  me->get_photo(), armor, me->get_armor_color_1(),
					  type, me->get_hair_color(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color(),
					  get_weapon_code_2(), me->get_weapon_color(), me->get_weapon_color_2(),
					  get_reincarnation(), get_reincarnation(),
					  get_hp_cent(), speed, get_number(), sprintf("%-16s%s", get_short(), get_title()));
		else if (!add_pf_2)
			send_user(user, "%c%c%d%w%w%c%c%c%w%d%w%w%w%w%w%w%w%w%w%w%c%c%c%w%c%c%c%d%s", 0x69, 11, id,
					  get_x(me), get_y(me), get_d(me), get_char_type(), get_char_action(),
					  me->get_photo(), armor, me->get_armor_color_1(),
					  type, me->get_hair_color(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color(),
					  get_weapon_code_2(), me->get_weapon_color(), me->get_weapon_color_2(),
					  get_reincarnation(), get_reincarnation(),
					  get_hp_cent(), add_pf, 1, OVER_BODY, speed, get_number(), sprintf("%-16s%s", get_short(), get_title()));
		else
			send_user(user, "%c%c%d%w%w%c%c%c%w%d%w%w%w%w%w%w%w%w%w%w%c%c%c%w%c%c%w%c%c%c%d%s", 0x69, 12, id,
					  get_x(me), get_y(me), get_d(me), get_char_type(), get_char_action(),
					  me->get_photo(), armor, me->get_armor_color_1(),
					  type, me->get_hair_color(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color(),
					  get_weapon_code_2(), me->get_weapon_color(), me->get_weapon_color_2(),
					  get_reincarnation(), get_reincarnation(),
					  get_hp_cent(), add_pf, 1, OVER_BODY, add_pf_2, 1, OVER_BODY, speed, get_number(), sprintf("%-16s%s", get_short(), get_title()));
	}
	else
	{
		if (!add_pf)
			send_user(user, "%c%c%d%w%w%c%c%c%d%w%w%c%c%c%c%d%s", 0x69, 0, id,
					  x, y, d, get_char_type(), get_char_action(),
					  armor, get_armor_color_1(), get_weapon_code_2(), get_reincarnation(), get_reincarnation(),
					  get_hp_cent(), speed, get_number(), sprintf("%-16s%s", get_short(), get_title()));
		else if (!add_pf_2)
			send_user(user, "%c%c%d%w%w%c%c%c%d%w%w%c%c%c%w%c%c%c%d%s", 0x69, 1, id,
					  x, y, d, get_char_type(), get_char_action(),
					  armor, get_armor_color_1(), get_weapon_code_2(), get_reincarnation(), get_reincarnation(),
					  get_hp_cent(), add_pf, 1, OVER_BODY, speed, get_number(), sprintf("%-16s%s", get_short(), get_title()));
		else
			send_user(user, "%c%c%d%w%w%c%c%c%d%w%w%c%c%c%w%c%c%w%c%c%c%d%s", 0x69, 2, id,
					  x, y, d, get_char_type(), get_char_action(),
					  armor, get_armor_color_1(), get_weapon_code_2(), get_reincarnation(), get_reincarnation(),
					  get_hp_cent(), add_pf, 1, OVER_BODY, add_pf_2, 1, OVER_BODY, speed, get_number(), sprintf("%-16s%s", get_short(), get_title()));
	}
	if (!is_player(me))
		send_user(user, "%c%d%d", 0x66, id, 0xff6500);
	if (me->get_ride())
		send_user(user, "%c%d%d", 0x62, id, me->get_ride());
	CHAR_CHAR_D->send_loop_perform(me, user);	// 显示持续效果
	CHAR_CHAR_D->send_loop_perform_2(me, user); // 显示持续图标

	if (is_store_open())
		send_user(user, "%c%c%d%s", 0x3d, 81, id, get_store_name()); // 显示摆摊名号

	map = get_map_object(get_z(me));
	if (map && map->is_wushuang())
		send_user(user, "%c%c%d%s", 0xA2, 13, me->get_number(), me->get_org_name());
}

// 函数：进入场景处理
varargs void add_to_scene(int z, int x, int y, int d, int add_pf, int add_pf_2, int rm_pf, int rm_pf_2)
{
	object map, *user, *npc, *item, me, *team;
	int z0, x0, y0, i, size;

	me = this_object();
	if (me->is_store_open())
	{
		me->init_store_dbase();
		me->open_store(0);
		//召唤兽
		team = me->get_all_beast();
		for (i = 0, size = sizeof(team); i < size; i++)
			team[i]->delete ("store");
		send_user(me, "%c%c%c%c", 0x7b, 0, 0, 1);
		send_user(me, "%s", ECHO + "Bạn đóng cửa tiệm");
	}
	z0 = get_z(me);
	x0 = get_x(me);
	y0 = get_y(me);
	remove_block(z0, x0, y0, CHAR_BLOCK);
	user = get_scene_object(z0, x0, y0, USER_TYPE) - ({me});
	if (!rm_pf)
		send_user(user, "%c%d", 0x78, getoid(me));
	else if (!rm_pf_2)
		send_user(user, "%c%d%w%c%c", 0x78, getoid(me), rm_pf, 1, OVER_BODY);
	else
		send_user(user, "%c%d%w%c%c%w%c%c", 0x78, getoid(me), rm_pf, 1, OVER_BODY, rm_pf_2, 1, OVER_BODY);
	// 加上租宠的处理
	//	if (z!=80 && get_effect(me, EFFECT_RIDE))
	//	set_effect(me, EFFECT_RIDE, 1);
	if (z != z0)
	{
		if (get_effect(me, EFFECT_CHAR_CHAN))
			set_effect(me, EFFECT_CHAR_CHAN, 1);
		if (map = get_map_object(z0))
			map->before_jumpout(me); // 跳离之前处理

		if (map = get_map_object(z))
		{
			if (map->get_map_type() <= FIELD_MAP)
			{
				if (me->get_ride())
					; // me->set_ride(0);
			}
			send_user(me, "%c%w%w%w%s", 0x3c, map->get_client_id(), x, y, map->get_name());
		}
		else
			send_user(me, "%c%w%w%w%s", 0x3c, z, x, y, "Bản đồ vô danh");

		// if( z == 1 ) set_latest_city(00110);    // 回城符：新手村(001 #10)
	}
	set_z(me, z);
	set_x(me, x);
	set_y(me, y);
	set_d(me, d);
	set_block(z, x, y, CHAR_BLOCK);
	move_object(me, z, x, y, USER_TYPE);
	if (get_login_flag() != 3)
		set_invisible(me, 1); // 准备未就绪，NPC 不攻击

	user = get_scene_object(z, x, y, USER_TYPE);
	show_to_scene(user, x, y, d, add_pf, add_pf_2);
	user -= ({me});
	npc = get_scene_object(z, x, y, CHAR_TYPE);
	item = get_scene_object(z, x, y, ITEM_TYPE);
	user->show_to_user(me);
	npc->show_to_user(me);
	item->show_to_user(me);

	item = get_scene_object(z, x, y, SEAL_TYPE);
	item->show_to_user_2(me);

	if (z != z0) // 显示地图名
	{
		if (map = get_map_object(z))
			map->enter_scene(me);
		if (arrayp(user = me->get_team())) // 更新队员坐标(删除)
		{
			user -= ({me, 0});
			user = filter_array(user, (
										  : $1 && get_z($1) == $2:),
								z0);
			send_user(user, "%c%c%d%w%w", 0x54, 10, me->get_number(), -1, -1);
			for (i = 0, size = sizeof(user); i < size; i++)
				if (user[i])
					send_user(me, "%c%c%d%w%w", 0x54, 10, user[i]->get_number(), -1, -1);
		}
	}

	if (arrayp(user = me->get_team())) // 更新队员坐标(新增)
	{
		user -= ({me, 0});
		user = filter_array(user, (
									  : $1 && get_z($1) == $2:),
							z);
		send_user(user, "%c%c%d%w%w", 0x54, 10, me->get_number(), x, y);
		for (i = 0, size = sizeof(user); i < size; i++)
			if (user[i])
				send_user(me, "%c%c%d%w%w", 0x54, 10, user[i]->get_number(), get_x(user[i]), get_y(user[i]));
	}
	if ((z0 = me->get_task_xy()) && z0 / 1000000 == z) // 更新任务坐标
	{
		x0 = (z0 % 1000000) / 1000;
		y0 = z0 % 1000;

		send_user(me, "%c%c%d%w%w", 0x54, 12, getoid(me), x0, y0); // 借用 getoid(me)
	}
	me->send_mtask_xy(z);					 //更新任务坐标
	if (MAP_D->is_inside_safe_zone(z, x, y)) // 安全区判断
	{
		me->set_no_fight(1);
	}
	else
	{
		me->set_no_fight(0);

		npc = get_range_object_2(me, 6, CHAR_TYPE);
		if (sizeof(npc))
			npc->init_heart_beat_idle();
	}

	// if (get_effect(me, EFFECT_CHAR_CHAN))
	// 	set_effect(me, EFFECT_CHAR_CHAN, 1); // 移除粘手效果
	CHAR_CHAR_D->send_loop_perform_2(me, me);
	if (get_effect_3(me, EFFECT_CHAR_INVISIBLE))
	{
		if (get_effect_3(me, EFFECT_03643) || me->get_save("no_visible"))
			send_user(me, "%c%c%c", 0x3d, 241, 2);
	}
	if (z != 1 && z != 4 && z != 7)
		"/quest/help"->send_help_tips(me, 21);
	if (z == 10 || z == 20 || z == 30 || z == 40 || z == 50 || z == 60 || z == 70)
		"/quest/help"->send_help_tips(me, 25);
	if (z == 12 || z == 139 || z == 174 || z == 804)
		"/quest/help"->send_help_tips(me, 33);
}

// -------------------------------------------------------------

private
static int SecurityClass; // 安全等级

// 函数：获取安全等级
int get_security_class() { return SecurityClass; }

// 函数：安全等级设置
void set_security_class()
{
	if (CLASS_D->is_god(this_object()))
		SecurityClass = 5;
	else if (CLASS_D->is_gm2(this_object()))
		SecurityClass = 4;
	else if (CLASS_D->is_gm3(this_object()))
		SecurityClass = 3;
	else if (CLASS_D->is_gm(this_object()))
		SecurityClass = 2;
	else
		SecurityClass = 1;
}

// 记录死亡时需要记录的使用限制时间
void save_limit_time()
{
	object me = this_object();
	int i, size;
	string name;
	size = sizeof(rc_status);
	for (i = 0; i < size; i++)
	{
		if (get_effect(me, rc_status[i]))
		{
			name = sprintf("rc_record.%d", rc_status[i]);
			me->set_save_2(name, get_effect(me, rc_status[i]));
		}
	}
}

// 恢复死亡时需要记录的使用限制时间
void restore_limit_time()
{
	object me = this_object();
	int i, size;
	string name;
	size = sizeof(rc_status);
	for (i = 0; i < size; i++)
	{
		name = sprintf("rc_record.%d", rc_status[i]);
		if (me->get_save_2(name))
			set_effect(me, rc_status[i], me->get_save_2(name));
	}
	me->delete_save_2("rc_record");
}

void apex_kickout(int action)
{
	object me = this_object();
	if (!is_player(me))
	{
		record_login(me, me->get_id(), 0);
		tell_user(me, "Ngươi bị phản ngoại quá trình tự theo dõi");
	}
	else
	{
		me->set_idle_time(200);
		QUIT_CMD->main(this_object(), "");
	}
}
