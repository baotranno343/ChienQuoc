
#include <cmd.h>

#define LOGIN_TIMEOUT 60  // 连线超时限制
#define AUTH_TIMEOUT 1800 // 连线超时限制

class UserList
{
	int ord;
	int number;
	int shape;
	int level;
	string name;
}

private static class UserList *list = ({});

private
static int OnlineTime = -1; // 沉迷时间
private
int CuThuDaoTime;
private
int Birthday; // 生日时间
private
int GameTime; // 游戏时间
private
int DoubleTime; // 双倍经验时间
private
int FeeStart; // 扣费开始时间
private
int FeeTime; // 扣费时间

private
static int LoginFlag; // 连线状态

private
int LoginTime; // 连线时间
private
int QuitTime; // 退出时间
private
string QuitIP; // 退出ＩＰ

private
int ExtraDoubleTime; // 战国令双倍经验时间
private
int ExtraExpTime; // 战国号角加经验时间
// =============================================================

// 函数：获取沉迷时间
int get_cuthudaotime() { return CuThuDaoTime; }

// 函数：设置沉迷时间
int set_cuthudaotime(int time) { return CuThuDaoTime = time; }

// 函数：增添沉迷时间
int add_cuthudaotime(int time)
{

	return set_cuthudaotime(CuThuDaoTime + time);
}

// 函数：清除沉迷时间
int clean_cuthudaotime()
{
	return CuThuDaoTime = 0; // 下线五小时，即回复原点
}

// 函数：获取在线奖励率
int get_cuthudaotime_rate()
{

	switch (CuThuDaoTime)
	{
	case 0..14399:
		return 100; // 3 x 60 x 60 = 10800  三小时
	case 14400..21600:
		return 50; // 5 x 60 x 60 = 18000  五小时
	default:
		return 0;
	}
}
/////
// 函数：获取沉迷时间
int get_online_time() { return OnlineTime; }

// 函数：设置沉迷时间
int set_online_time(int time) { return OnlineTime = range_value(time, -1, MAX_NUMBER); }

// 函数：增添沉迷时间
int add_online_time(int time)
{
	if (OnlineTime == -1)
		return 0;
	return set_online_time(OnlineTime + time);
}

// 函数：清除沉迷时间
int clean_online_time()
{
	int sec;

	sec = LoginTime - QuitTime; // 离线时间

	if (sec > 0) // 离线时间为正数
	{
		if (sec < 18000)																  // 5 x 60 x 60 = 18000  五小时
			OnlineTime = range_value(range_value(OnlineTime, -1, 18000) - sec, 0, 18000); // 由最高五小时减起
		else
			OnlineTime = 0; // 下线五小时，即回复原点
	}
}

// 函数：获取在线奖励率
int get_online_rate()
{
	if (OnlineTime == -1)
		return 100;

	switch (OnlineTime)
	{
	case 0..10799:
		return 100; // 3 x 60 x 60 = 10800  三小时
	case 10800..18000:
		return 50; // 5 x 60 x 60 = 18000  五小时
	default:
		return 0;
	}
}

// -------------------------------------------------------------

// 函数：获取生日时间
int get_birthday() { return Birthday; }

// 函数：设置生日时间
int set_birthday(int time) { return Birthday = time; }

// 函数：获取游戏时间
int get_game_time() { return GameTime; }

// 函数：设置游戏时间
int set_game_time(int time) { return GameTime = time; }

// 函数：获取双倍经验时间
int get_double_time() { return DoubleTime; }

// 函数：获取战国令双倍经验时间
int get_extra_double_time() { return ExtraDoubleTime; }

// 函数：获取战国号角经验时间
int get_extra_exp_time() { return ExtraExpTime; }

// 函数：设置双倍经验时间
int set_double_time(int time) { return DoubleTime = time; }

// 函数：设置双倍经验时间
int set_extra_double_time(int time) { return ExtraDoubleTime = time; }

// 函数：设置双倍经验时间
int set_extra_exp_time(int time) { return ExtraExpTime = time; }

// 函数：获取扣费开始时间
int get_fee_start() { return FeeStart; }

// 函数：设置扣费开始时间
int set_fee_start(int time) { return FeeStart = time; }

// 函数：获取扣费时间
int get_feetime() { return FeeTime; }

// 函数：设置扣费时间
int set_feetime(int time) { return FeeTime = time; }

// 函数：获取连线状态
int get_login_flag() { return LoginFlag; }

// 函数：设置连线状态
// 注释：1: 登录中；2: 登录成功；3: 准备就绪
int set_login_flag(int flag) { return LoginFlag = flag; }

// 函数：获取连线时间
int get_login_time() { return LoginTime; }

// 函数：设置连线时间
int set_login_time(int time) { return LoginTime = time; } // 唯一在 login.c 时设置

// 函数：获取退出时间
int get_quit_time() { return QuitTime; }

// 函数：设置退出时间
int set_quit_time(int time) { return QuitTime = time; }

// 函数：获取退出ＩＰ
string get_quit_ip() { return QuitIP; }

// 函数：设置退出ＩＰ
string set_quit_ip(string ip) { return QuitIP = ip; }

// =============================================================

// 函数：连线处理
void logon()
{
	set_login_flag(1);
	call_out("login_timeout", LOGIN_TIMEOUT);
	LOGIN_D->logon(this_object());
}

// 函数：连线超时处理
void login_timeout()
{
	if (get_login_flag() < 2)
		destruct(this_object());
	else
	{
		remove_call_out("login_timeout");
		remove_call_out("login_timeout2");
	}
}

void authentic_callout()
{
	remove_call_out("login_timeout");
	remove_call_out("login_timeout2");
	call_out("login_timeout2", AUTH_TIMEOUT);
}

// 函数：连线超时处理
void login_timeout2()
{
	if (get_login_flag() < 2)
		destruct(this_object());
	else
		remove_call_out("login_timeout2");
}

// -------------------------------------------------------------

// 函数：用户密码校验
void user_authentic_callout(string passwd, int order)
{
	object me = this_object();
	string result = get_exchange_urs_string(me);
	string name, ret, name1, name2, Owner, Id;
	string *line;
	mapping list;
	object obj;
	int i, size, a1, a2, a3, a4, time, armor;
	int *number = ({0, 0, 0, 0, 0, 0});
	int *shape = ({0, 0, 0, 0, 0, 0});
	int *level = ({0, 0, 0, 0, 0, 0});
	string *namelist = ({" ", " ", " ", " ", " ", " "});
	string *fam = ({" ", " ", " ", " ", " ", " "});

	remove_call_out("user_authentic_callout");

	if (result == "")
	{
		call_out("user_authentic_callout", 1, passwd, order); // 继续等待结果
		return;
	}
	if (MAIN_D->get_host_type() == 6012)
	{
		log_file("php.date", sprintf("result=%s\n", result));
		line = explode(result, " ");
		if (sizeof(line) != 3)
		{
			switch (result[0])
			{
			case '#':
				send_user(me, "%c%s", '!', "数据库操作错误！");
				db_user_clear(me, me->get_id());
				destruct(me);
				return;
			case 'S':
				send_user(me, "%c%s", '!', "此服务器未登记！");
				db_user_clear(me, me->get_id());
				destruct(me);
				return;
			case 'X':
				send_user(me, "%c%s", '!', "您输入了空的KEY！");
				db_user_clear(me, me->get_id());
				destruct(me);
				return;
			case 'I':
				send_user(me, "%c%s", '!', "用户帐号不存在！");
				db_user_clear(me, me->get_id());
				destruct(me);
				return;
			case 'P':
				send_user(me, "%c%s", '!', "传入KEY错误！");
				db_user_clear(me, me->get_id());
				destruct(me);
				return;
			}
		}
		Id = strlwr(line[0]);
		if (!CHECK_D->is_legal_id(me, Id))
			return;
		me->set_id(Id);
		me->set_real_id(Id);
		i = to_int(line[1]);
		me->set_acountid(i);
		i = to_int(line[2]);
		me->set_acountno(i);
		Owner = me->get_id();
		name1 = sprintf("data/%c/%c/%c/%s/list.txt", Owner[0], Owner[1], Owner[2], Owner);
		name2 = sprintf("data/%c/%c/%c/%s/list" SAVE_EXTENSION, Owner[0], Owner[1], Owner[2], Owner);
		if (file_size(name1) > 0)
		{
			rename(name1, name2);
		}
		obj = new ("/inh/user/list");
		if (!obj)
			return;
		obj->set_owner(me->get_id());
		obj->restore();
		list = obj->get_save("userlist");
		if (!list)
			list = ([]);
		for (i = 0; i < 6; i++)
		{
			if (obj->get_save_2(sprintf("%d.number", i + 1)) == 0)
				continue;
			number[i] = obj->get_save_2(sprintf("%d.number", i + 1));
			shape[i] = obj->get_save_2(sprintf("%d.shape", i + 1));
			level[i] = obj->get_save_2(sprintf("%d.level", i + 1));
			namelist[i] = obj->get_save_2(sprintf("%d.name", i + 1));
			if ("/sys/sys/count"->get_new_person() == 0)
			{
				switch (shape[i] / 10000)
				{
				case 1:
					ret = "Vô Môn Phái";
					break;
				case 2:
					ret = "Đào Hoa Nguyên";
					break;
				case 3:
					ret = "Thục Sơn";
					break;
				case 4:
					ret = "Cấm Vệ Quân";
					break;
				case 5:
					ret = "Đường Môn";
					break;
				case 6:
					ret = "Côn Luân";
					break;
				case 7:
					ret = "Vân Mộng Cốc";
					break;
				case 8:
					ret = "Mao Sơn";
					break;
				default:
					ret = obj->get_save_2(sprintf("%d.family", i + 1));
					if (ret == "")
						ret = "Vô Môn Phái";
					break;
				}
			}
			else
			{
				shape[i] = obj->get_save_2(sprintf("%d.armor", i + 1));
				switch (shape[i] % 10)
				{
				/*case 1:
	        			ret = "Vô Môn Phái";
	        			break;
	        		case 2:
	        			ret = "Đào Hoa Nguyên";
	        			break;
	        		case 3:
	        			ret = "Thục Sơn";
	        			break;
	        		case 4:
	        			ret = "Cấm Vệ Quân";
	        			break;
	        		case 5:
	        			ret = "Đường Môn";
	        			break;
	        		case 6:
	        			ret = "Côn Luân";
	        			break;
	        		case 7:
	        			ret = "Vân Mộng Cốc";
	        			break;
	        		case 8:
	        			ret = "Mao Sơn";
	        			break;*/
				default:
					ret = obj->get_save_2(sprintf("%d.family", i + 1));
					if (ret == "")
						ret = "Vô Môn Phái";
					break;
				}
			}
			fam[i] = ret;
		}
		if (order == 0)
		{
			for (i = 0; i < 6; i++)
			{
				ret = sprintf("%-12s%-6s", namelist[i], fam[i]);
				if ("/sys/sys/count"->get_new_person() == 0)
					send_user(me, "%c%c%c%d%c%d%s", 0x49, 9, i + 1, number[i], level[i], shape[i], ret);
				else
				{
					armor = obj->get_save_2(sprintf("%d.armor", i + 1));
					if (armor == 0)
					{
						if ((shape[i] / 100) % 2 == 1)
							armor = 10001;
						else
							armor = 11001;
					}
					send_user(me, "%c%c%c%d%c%d%w%w%w%w%w%w%w%w%w%w%s", 0x49, 11, i + 1, number[i], level[i],
							  armor,
							  obj->get_save_2(sprintf("%d.armorc", i + 1)),
							  obj->get_save_2(sprintf("%d.hair", i + 1)),
							  obj->get_save_2(sprintf("%d.hairc", i + 1)),
							  obj->get_save_2(sprintf("%d.back", i + 1)),
							  obj->get_save_2(sprintf("%d.backc", i + 1)),
							  obj->get_save_2(sprintf("%d.back2", i + 1)),
							  obj->get_save_2(sprintf("%d.back2c", i + 1)),
							  obj->get_save_2(sprintf("%d.weapon", i + 1)),
							  obj->get_save_2(sprintf("%d.weaponc", i + 1)),
							  obj->get_save_2(sprintf("%d.weaponc2", i + 1)),
							  ret);
				}
			}
			// 发送玩家列表
			db_user_clear(me, me->get_id());
			destruct(me);
			destruct(obj);
			return;
		}
		if (order > 6)
		{
			send_user(me, "%c%s", '!', "用户数据不存在！");
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		}
		if (number[order - 1] == 0)
		{
			send_user(me, "%c%s", '!', "用户数据不存在！");
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		}
		if (order > 1)
		{
			me->set_id(sprintf("%s#%d", me->get_id(), order));
			me->set_number(number[order - 1]);
			if ((shape[order - 1] / 100) % 2 == 0)
				me->set_gender(1);
			else
				me->set_gender(2);
		}
		else
		{
			me->set_number(number[0]);
			if ((shape[0] / 100) % 2 == 0)
				me->set_gender(1);
			else
				me->set_gender(2);
		}
		if ("/sys/sys/count"->get_new_person())
		{
			i = obj->get_save_2(sprintf("%d.armor", order));
			if (i >= 11000)
				me->set_gender(2);
			else
				me->set_gender(1);
			me->set_hair(obj->get_save_2(sprintf("%d.hair", order)));
		}
		LOGIN_D->do_user_exist(me, passwd, namelist[order - 1]);
		destruct(obj);
		return;
	}
	if (MAIN_D->get_host_type() == 4 || MAIN_D->get_host_type() == 0 || MAIN_D->get_host_type() == 1000)
	{
		if (MAIN_D->get_host_type() == 0)
		{
			result = "ok:1:1:1";
		}
		if (MAIN_D->get_host_type() == 1000)
		{
			result = "ok:1:1:1";
			//	result = sprintf("ok:%d", "sys/sys/test_db"->get_yuanbao(me) );
		}
		//log_file("testphp.dat", me->get_id()+" "+ result+"\n");
		line = explode(result, ":");
		if (sizeof(line) <= 1)
		{
			send_user(me, "%c%s", '!', "连接出错，请重新连接。" + result);
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		}
		switch (line[0])
		{
		case "ok":
			me->set_acountid(to_int(line[1]));
			if (sizeof(line) >= 4)
			{
				if (line[3] != "-1")
				{
					me->set_online_time(to_int(line[3]) * 60);
				}
				else
					me->set_online_time(-1);
			}
			else
				me->set_online_time(-1);
			break;
		case "fail":
			if (sizeof(line) <= 2)
				send_user(me, "%c%s", '!', "连接出错，请重新连接。");
			else
			{
				switch (to_int(line[2]))
				{
				case 1:
					send_user(me, "%c%s", '!', "时间戳过期。");
					break;
				case 2:
					send_user(me, "%c%s", '!', "密钥错误。");
					break;
				case 3:
					send_user(me, "%c%s", '!', "您的帐号不存在或者没有激活该大区。");
					break;
				case 4:
					send_user(me, "%c%s", '!', "密码错误。");
					break;
				case 5:
					send_user(me, "%c%s", '!', "尝试次数过多。");
					break;
				default:
					send_user(me, "%c%s", '!', "连接出错，请重新连接。");
					break;
				}
			}
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		default:
			send_user(me, "%c%s", '!', "连接出错，请重新连接。" + result);
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		}
		Owner = me->get_id();
		name1 = sprintf("data/%c/%c/%c/%s/list.txt", Owner[0], Owner[1], Owner[2], Owner);
		name2 = sprintf("data/%c/%c/%c/%s/list" SAVE_EXTENSION, Owner[0], Owner[1], Owner[2], Owner);
		if (file_size(name1) > 0)
		{
			rename(name1, name2);
		}
		obj = new ("/inh/user/list");
		if (!obj)
			return;
		obj->set_owner(me->get_id());
		obj->restore();
		list = obj->get_save("userlist");
		if (!list)
			list = ([]);
		for (i = 0; i < 6; i++)
		{
			if (obj->get_save_2(sprintf("%d.number", i + 1)) == 0)
				continue;
			number[i] = obj->get_save_2(sprintf("%d.number", i + 1));
			shape[i] = obj->get_save_2(sprintf("%d.shape", i + 1));
			level[i] = obj->get_save_2(sprintf("%d.level", i + 1));
			namelist[i] = obj->get_save_2(sprintf("%d.name", i + 1));
			if ("/sys/sys/count"->get_new_person() == 0)
			{
				switch (shape[i] / 10000)
				{
				case 1:
					ret = "Vô Môn Phái";
					break;
				case 2:
					ret = "Đào Hoa Nguyên";
					break;
				case 3:
					ret = "Thục Sơn";
					break;
				case 4:
					ret = "Cấm Vệ Quân";
					break;
				case 5:
					ret = "Đường Môn";
					break;
				case 6:
					ret = "Côn Luân";
					break;
				case 7:
					ret = "Vân Mộng Cốc";
					break;
				case 8:
					ret = "Mao Sơn";
					break;
				default:
					ret = obj->get_save_2(sprintf("%d.family", i + 1));
					if (ret == "")
						ret = "Vô Môn Phái";
					break;
				}
			}
			else
			{
				shape[i] = obj->get_save_2(sprintf("%d.armor", i + 1));
				switch (shape[i] % 10)
				{
				/*case 1:
	        			ret = "Vô Môn Phái";
	        			break;
	        		case 2:
	        			ret = "Đào Hoa Nguyên";
	        			break;
	        		case 3:
	        			ret = "Thục Sơn";
	        			break;
	        		case 4:
	        			ret = "Cấm Vệ Quân";
	        			break;
	        		case 5:
	        			ret = "Đường Môn";
	        			break;
	        		case 6:
	        			ret = "Côn Luân";
	        			break;
	        		case 7:
	        			ret = "Vân Mộng Cốc";
	        			break;
	        		case 8:
	        			ret = "Mao Sơn";
	        			break;*/
				default:
					ret = obj->get_save_2(sprintf("%d.family", i + 1));
					if (ret == "")
						ret = "Vô Môn Phái";
					break;
				}
			}
			fam[i] = ret;
		}
		if (order == 0)
		{
			for (i = 0; i < 6; i++)
			{
				ret = sprintf("%-12s%-6s", namelist[i], fam[i]);
				if ("/sys/sys/count"->get_new_person() == 0)
					send_user(me, "%c%c%c%d%c%d%s", 0x49, 9, i + 1, number[i], level[i], shape[i], ret);
				else
				{
					armor = obj->get_save_2(sprintf("%d.armor", i + 1));
					if (armor == 0)
					{
						if ((shape[i] / 100) % 2 == 1)
							armor = 10001;
						else
							armor = 11001;
					}
					send_user(me, "%c%c%c%d%c%d%w%w%w%w%w%w%w%w%w%w%s", 0x49, 11, i + 1, number[i], level[i],
							  armor,
							  obj->get_save_2(sprintf("%d.armorc", i + 1)),
							  obj->get_save_2(sprintf("%d.hair", i + 1)),
							  obj->get_save_2(sprintf("%d.hairc", i + 1)),
							  obj->get_save_2(sprintf("%d.back", i + 1)),
							  obj->get_save_2(sprintf("%d.backc", i + 1)),
							  obj->get_save_2(sprintf("%d.back2", i + 1)),
							  obj->get_save_2(sprintf("%d.back2c", i + 1)),
							  obj->get_save_2(sprintf("%d.weapon", i + 1)),
							  obj->get_save_2(sprintf("%d.weaponc", i + 1)),
							  obj->get_save_2(sprintf("%d.weaponc2", i + 1)),
							  ret);
				}
			}
			// 发送玩家列表
			db_user_clear(me, me->get_id());
			destruct(me);
			destruct(obj);
			return;
		}
		if (order > 6)
		{
			send_user(me, "%c%s", '!', "用户数据不存在！");
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		}
		if (number[order - 1] == 0)
		{
			send_user(me, "%c%s", '!', "用户数据不存在！");
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		}
		if (order > 1)
		{
			me->set_id(sprintf("%s#%d", me->get_id(), order));
			me->set_number(number[order - 1]);
			if ((shape[order - 1] / 100) % 2 == 0)
				me->set_gender(1);
			else
				me->set_gender(2);
		}
		else
		{
			me->set_number(number[0]);
			if ((shape[0] / 100) % 2 == 0)
				me->set_gender(1);
			else
				me->set_gender(2);
		}
		if ("/sys/sys/count"->get_new_person())
		{
			i = obj->get_save_2(sprintf("%d.armor", order));
			if (i >= 11000)
				me->set_gender(2);
			else
				me->set_gender(1);
			me->set_hair(obj->get_save_2(sprintf("%d.hair", order)));
			me->set_photo(obj->get_save_2(sprintf("%d.photo", order)));
		}
		LOGIN_D->do_user_exist(me, passwd, namelist[order - 1]);
		destruct(obj);
		return;
	}
	if (strlen(result) > 1 && (result[0] >= '0' && result[0] <= '6' || result[0] == '!'))
	{
		line = explode(result, "\n");
		size = sizeof(line);
		result = "";
		for (i = 0; i < size; i++)
		{
			if (line[i][0] == '!')
			{
				sscanf(line[i], "!%d", time);
				if (time() < time)
					me->set_vip(1);
				else
					me->set_vip(0);
				continue;
			}
			sscanf(line[i], "%d %d %d %d %s", a1, a2, a3, a4, ret);
			a1--;
			if (a1 < 0)
				a1 = 0;
			if (a1 > 5)
				a1 = 5;
			number[a1] = a2;
			if (a3 == 0)
				a3 = 10000;
			shape[a1] = a3;
			level[a1] = a4;
			namelist[a1] = ret;
			ret = "";
			switch (a3 / 10000)
			{
			case 1:
				ret = "Vô Môn Phái";
				break;
			case 2:
				ret = "Đào Hoa Nguyên";
				break;
			case 3:
				ret = "Thục Sơn";
				break;
			case 4:
				ret = "Cấm Vệ Quân";
				break;
			case 5:
				ret = "Đường Môn";
				break;
			case 6:
				ret = "Côn Luân";
				break;
			case 7:
				ret = "Vân Mộng Cốc";
				break;
			case 8:
				ret = "Mao Sơn";
				break;
			default:
				ret = obj->get_save_2(sprintf("%d.family", i + 1));
				if (ret == "")
					ret = "Vô Môn Phái";
				break;
			}
			fam[a1] = ret;
		}
		if (order == 0)
		{
			for (i = 0; i < 6; i++)
			{
				ret = sprintf("%-12s%-6s", namelist[i], fam[i]);
				send_user(me, "%c%c%c%d%c%d%s", 0x49, 9, i + 1, number[i], level[i], shape[i], ret);
			}
			// 发送玩家列表
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		}
		if (order > 6)
		{
			send_user(me, "%c%s", '!', "用户数据不存在！");
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		}
		if (number[order - 1] == 0)
		{
			send_user(me, "%c%s", '!', "用户数据不存在！");
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		}
		if (order > 1)
		{
			me->set_id(sprintf("%s#%d", me->get_id(), order));
			me->set_number(number[order - 1]);
			if ((shape[order - 1] / 100) % 2 == 0)
				me->set_gender(1);
			else
				me->set_gender(2);
		}
		else
		{
			me->set_number(number[0]);
			if ((shape[0] / 100) % 2 == 0)
				me->set_gender(1);
			else
				me->set_gender(2);
		}
		LOGIN_D->do_user_exist(me, passwd, namelist[order - 1]);

		return;
	}
	switch (result[0])
	{
	case '#':
		send_user(me, "%c%s", '!', "数据库操作错误！");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case 'S':
		send_user(me, "%c%s", '!', "此服务器未登记！");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case 'X':
		send_user(me, "%c%s", '!', "您输入了空的帐号或密码！");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case 'I':
		send_user(me, "%c%s", '!', "用户帐号不存在！");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case 'P':
		send_user(me, "%c%s", '!', "密码输入错误！");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case 'E':
		send_user(me, "%c%s", '!', "密码错误次数过多！");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	default:
		send_user(me, "%c%s", '!', "连接出错，请重新连接。");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case '0':
		name = (strlen(result) <= 1) ? "" : result;
		LOGIN_D->do_user_exist(me, passwd, name);
		return;
	}
}

// 函数：用户存在判断
void user_exist_callout(string id, string passwd, string name)
{
	object me = this_object();
	int result = get_exchange_result(me);

	remove_call_out("user_exist_callout");

	if (result == -2)
	{
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	}
	else if (result == 0)
	{
		//                LOGIN_0_D->new_login_1(me, passwd, name);    // 无此用户(打开新登录界面)
		LOGIN_0_D->new_login_3(me, name, me->get_gender());
		return;
	}
	else if (result > 0)
	{
		LOGIN_D->do_user_restore(me, id, passwd, name);
		return;
	}

	call_out("user_exist_callout", 1, id, passwd, name);
}

// 函数：用户资料载入
void user_restore_callout(string id, string passwd, string name, string acountid)
{
	object me = this_object();
	int result = get_exchange_result(me);
	int *data;

	remove_call_out("user_restore_callout");

	if (result == -2)
	{
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	}
	else if (result == 0)
	{
		send_user(me, "%c%s", '!', "您的资料出了问题，请马上通知ＧＭ。");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	}
	else if (result > 0)
	{
		if (!arrayp(data = me->get_effect_data()))
			data = ({});
		set_effect_dbase(me, data);
		if (name != "")
			me->set_name(name); // 修正姓名
		if (me->get_id() != id)
		{
			log_file("saveerror.txt", sprintf("%s loginid=%s restoreid=%s\n", short_time(), id, me->get_id()));
			send_user(me, "%c%s", '!', "您的资料出了问题，请马上通知ＧＭ。");
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		}
		if (me->get_save("bantime") > time())
		{
			send_user(me, "%c%s", '!', sprintf("您需等待%d分钟才能进入游戏。", (me->get_save("bantime") - time()) / 60));
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		}
		if (MAIN_D->get_host_type() == 4 && me->get_cash() > 300000000)
		{
			log_file("casherror.txt", sprintf("%s %s %s(%d) cash=%d\n", short_time(), id, me->get_name(), me->get_number(), me->get_cash()));
			send_user(me, "%c%s", '!', "角色数据异常，请与游戏客服联系!");
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		}
		me->set_acountid(acountid);
		LOGIN_D->enter(me, passwd);
		return;
	}

	call_out("user_restore_callout", 1, id, passwd, name, acountid);
}

// -------------------------------------------------------------

// 函数：断线处理
void net_dead()
{
	if (get_login_flag() < 2)
	{
		remove_call_out("login_timeout");
		destruct(this_object());
	}
	else
		QUIT_CMD->main(this_object(), "");
}

// 函数：重新连线处理
void reconnect() {}
