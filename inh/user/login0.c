private
static int *numberlist = ({0, 0, 0, 0, 0, 0});
private
static int *shapelist = ({0, 0, 0, 0, 0, 0});
private
static int *levellist = ({0, 0, 0, 0, 0, 0});
private
static string *namelist = ({" ", " ", " ", " ", " ", " "});
private
static string *famlist = ({" ", " ", " ", " ", " ", " "});
// 函数：用户密码校验
void user_authentic_callout_2(string passwd, string name, int gender, int order)
{
	object me = this_object();
	string result = get_exchange_urs_string(me), Id;
	string *line, ret;
	int i, size, a1, a2, a3, a4, time, armor;
	remove_call_out("user_authentic_callout_2");
	me->set_gender(gender);
	if (result == "")
	{
		call_out("user_authentic_callout_2", 1, passwd, name, gender, order); // 继续等待结果
		return;
	}
	if (MAIN_D->get_host_type() == 6012)
	{
		line = explode(result, " ");
		if (sizeof(line) != 3)
		{
			switch (result[0])
			{
			case '#':
				send_user(me, "%c%s", '!', "数据库操作错误!");
				db_user_clear(me, me->get_id());
				destruct(me);
				return;
			case 'S':
				send_user(me, "%c%s", '!', "此服务器未登记!");
				db_user_clear(me, me->get_id());
				destruct(me);
				return;
			case 'X':
				send_user(me, "%c%s", '!', "您输入了空的KEY!");
				db_user_clear(me, me->get_id());
				destruct(me);
				return;
			case 'I':
				send_user(me, "%c%s", '!', "用户帐号不存在!");
				db_user_clear(me, me->get_id());
				destruct(me);
				return;
			case 'P':
				send_user(me, "%c%s", '!', "传入KEY错误!");
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
		LOGIN_0_D->do_user_exist_2(me, "", name, gender, order);
		return;
	}
	if (MAIN_D->get_host_type() == 4 || MAIN_D->get_host_type() == 0 /*||MAIN_D->get_host_type()==1000*/)
	{
		if (MAIN_D->get_host_type() == 0)
		{
			result = "ok:1:1";
		}
		/*	if (MAIN_D->get_host_type()==1000)
			{
				result = "ok:1:1";
			}	*/
		line = explode(result, ":");
		if (sizeof(line) <= 1)
		{
			send_user(me, "%c%s", '!', "连接出错，请重新连接." + result);
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		}
		switch (line[0])
		{
		case "ok":
			me->set_acountid(to_int(line[1]));
			break;
		case "fail":
			if (sizeof(line) <= 2)
				send_user(me, "%c%s", '!', "连接出错，请重新连接.");
			else
			{
				switch (to_int(line[2]))
				{
				case 1:
					send_user(me, "%c%s", '!', "时间戳过期.");
					break;
				case 2:
					send_user(me, "%c%s", '!', "密钥错误.");
					break;
				case 3:
					send_user(me, "%c%s", '!', "您的帐号不存在或者没有激活该大区.");
					break;
				case 4:
					send_user(me, "%c%s", '!', "密码错误.");
					break;
				case 5:
					send_user(me, "%c%s", '!', "尝试次数过多.");
					break;
				default:
					send_user(me, "%c%s", '!', "连接出错，请重新连接.");
					break;
				}
			}
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		default:
			send_user(me, "%c%s", '!', "连接出错，请重新连接." + result);
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		}
		LOGIN_0_D->do_user_exist_2(me, passwd, name, gender, order);
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
			numberlist[a1] = a2;
			shapelist[a1] = a3;
			levellist[a1] = a4;
			namelist[a1] = ret;
		}
		if (order > 0)
		{
			if (order > 6)
				order = 6;
			if (numberlist[order - 1] > 0)
			{
				send_user(me, "%c%s", '!', "用户数据不存在!");
				db_user_clear(me, me->get_id());
				destruct(me);
				return;
			}
			if ("/sys/sys/count"->get_new_person())
			{
				if (gender == 1)
					shapelist[order - 1] = 10000;
				else
					shapelist[order - 1] = 11000;
			}
			else
			{
				if (gender == 1)
					shapelist[order - 1] = 10000;
				else
					shapelist[order - 1] = 10100;
			}
			namelist[order - 1] = name;
		}
		//       		if (order>1) me->set_id(sprintf("%s#%d", me->get_id(), order));
		LOGIN_0_D->do_user_exist_2(me, passwd, name, gender, order);
		return;
	}
	switch (result[0])
	{
	case '#':
		send_user(me, "%c%s", '!', "数据库操作错误!");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case 'S':
		send_user(me, "%c%s", '!', "此服务器未登记!");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case 'X':
		send_user(me, "%c%s", '!', "您输入了空的帐号或密码!");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case 'I':
		send_user(me, "%c%s", '!', "用户帐号不存在!");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case 'P':
		send_user(me, "%c%s", '!', "密码输入错误!");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case 'E':
		send_user(me, "%c%s", '!', "密码错误次数过多!");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	default:
		send_user(me, "%c%s", '!', "连接出错，请重新连接.");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case '0': // name = ( strlen(result) <= 1 ) ? "" : result[1..<1];
		LOGIN_0_D->do_user_exist_2(me, passwd, name, gender, order);
		return;
	}
}

// 函数：用户存在判断
void user_exist_callout_2(string passwd, string name, int gender, int order)
{
	object me = this_object();
	int result = get_exchange_result(me);

	remove_call_out("user_exist_callout_2");

	if (result == -2)
	{
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	}
	else if (result == 0)
	{
		LOGIN_0_D->do_user_check_2(me, passwd, name, gender, order);
		return;
	}
	else if (result > 0)
	{
		send_user(me, "%c%s", '!', "您已经新建了游戏角色!");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	}

	call_out("user_exist_callout_2", 1, passwd, name, gender, order);
}

// 函数：用户姓名校验
void user_check_callout_2(string passwd, string name, int gender, int order)
{
	object me = this_object(), obj;
	string result = get_exchange_urs_string(me);
	int i, size, count, armor;
	string ret, *line, Owner, name1, name2;

	remove_call_out("user_check_callout_2");

	if (result == "")
	{
		call_out("user_check_callout_2", 1, passwd, name, gender, order); // 继续等待结果
		return;
	}
	if (MAIN_D->get_host_type() == 6012)
	{
		switch (result[0])
		{
		case '#':
			send_user(me, "%c%s", '!', "数据库操作错误!");
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		case 'S':
			send_user(me, "%c%s", '!', "此服务器未登记!");
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		case 'X':
			send_user(me, "%c%s", '!', "您输入了不正确的数据!");
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		case 'N':
			send_user(me, "%c%s", '!', "这个中文名已经有人用了!");
			send_user(me, "%c%c", 0xff, 0x11);
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		default:
			send_user(me, "%c%s", '!', "连接出错，请重新连接.");
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			i = to_int(result);
			if (order == 0)
				order = 1;
			Owner = me->get_id();
			name1 = sprintf("data/%c/%c/%c/%s/list.txt", Owner[0], Owner[1], Owner[2], Owner);
			name2 = sprintf("data/%c/%c/%c/%s/list" SAVE_EXTENSION, Owner[0], Owner[1], Owner[2], Owner);
			if (file_size(name1) > 0)
			{
				rename(name1, name2);
			}
			obj = new ("/inh/user/list");
			obj->set_owner(me->get_real_id());
			obj->set_save_2(sprintf("%d.number", order), i);
			obj->set_save_2(sprintf("%d.name", order), name);
			if (gender == 1)
				obj->set_save_2(sprintf("%d.shape", order), 10000);
			else
				obj->set_save_2(sprintf("%d.shape", order), 10100);
			obj->set_save_2(sprintf("%d.armor", order), me->get_armor_code());
			obj->set_save_2(sprintf("%d.armorc", order), me->get_armor_color_1());
			obj->set_save_2(sprintf("%d.hair", order), me->get_hair());
			obj->set_save_2(sprintf("%d.hairc", order), me->get_hair_color());
			obj->set_save_2(sprintf("%d.back", order), me->get_back());
			obj->set_save_2(sprintf("%d.backc", order), me->get_back_color());
			obj->set_save_2(sprintf("%d.back2", order), me->get_back2());
			obj->set_save_2(sprintf("%d.back2c", order), me->get_back2_color());
			obj->set_save_2(sprintf("%d.weapon", order), me->get_weapon_code_2());
			obj->set_save_2(sprintf("%d.weaponc", order), me->get_weapon_color());
			obj->set_save_2(sprintf("%d.photo", order), me->get_photo());
			obj->save();
			count = 0;
			for (i = 0; i < 6; i++)
			{
				if (obj->get_save_2(sprintf("%d.number", i + 1)) == 0)
					continue;
				count++;
				numberlist[i] = obj->get_save_2(sprintf("%d.number", i + 1));
				shapelist[i] = obj->get_save_2(sprintf("%d.shape", i + 1));
				levellist[i] = obj->get_save_2(sprintf("%d.level", i + 1));
				namelist[i] = obj->get_save_2(sprintf("%d.name", i + 1));
				if ("/sys/sys/count"->get_new_person() == 0)
				{
					switch (shapelist[i] / 10000)
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
					shapelist[i] = obj->get_save_2(sprintf("%d.armor", i + 1));
					switch (shapelist[i] % 10)
					{
					case 1:
						ret = "Vô Môn Phái";
						break;
						/*	case 2:
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
				famlist[i] = ret;
			}
			if (count == 1)
				"/sys/sys/id"->add_newuser(1);
			"/sys/sys/id"->add_charnumber(1);
			for (i = 0; i < 6; i++)
			{
				if (i > 0 && numberlist[i] == 0)
					continue;
				ret = sprintf("%-12s%-6s", namelist[i], famlist[i]);

				if ("/sys/sys/count"->get_new_person() == 0)
					send_user(me, "%c%c%c%d%c%d%s", 0x49, 9, i + 1, numberlist[i], levellist[i], shapelist[i], ret);
				else
				{
					armor = obj->get_save_2(sprintf("%d.armor", i + 1));
					if (armor == 0)
					{
						if ((shapelist[i] / 100) % 2 == 1)
							armor = 10001;
						else
							armor = 11001;
					}
					send_user(me, "%c%c%c%d%c%d%w%w%w%w%w%w%w%w%w%w%s", 0x49, 11, i + 1, numberlist[i], levellist[i],
							  obj->get_save_2(sprintf("%d.armor", i + 1)),
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
			db_user_clear(me, me->get_id());
			destruct(me);
			//                me->set_number( to_int(result) );
			//                LOGIN_0_D->enter_2(me, passwd, name, gender);
			destruct(obj);
			return;
		}
		return;
	}
	if (MAIN_D->get_host_type() == 4 || MAIN_D->get_host_type() == 0 || MAIN_D->get_host_type() == 1000)
	{
		if (MAIN_D->get_host_type() == 0)
		{
			i = "/sys/sys/id"->get_max_id();
			result = sprintf("ok:%d", i + 1);
			"/sys/sys/id"->add_max_id(i + 1);
		}
		if (MAIN_D->get_host_type() == 1000)
		{

			i = "/sys/sys/id"->get_max_id();

			result = sprintf("ok:%d", i + 1);
			"/sys/sys/id"->add_max_id(i + 1);
		}
		// log_file("php.dat", sprintf("new result=%s\n", result));
		line = explode(result, ":");
		if (sizeof(line) <= 1)
		{
			send_user(me, "%c%s", '!', "连接出错，请重新连接." + result);
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		}
		if (line[0] != "ok")
		{
			send_user(me, "%c%s", '!', "已经有相同的角色名.");
			db_user_clear(me, me->get_id());
			destruct(me);
			return;
		}
		i = to_int(line[1]);
		if (!file_exist(sprintf("data/numberToId/%d.dat", i)))
			ghi_file(sprintf("data/numberToId/%d.dat", i), me->get_real_id());
		if (order == 0)
			order = 1;
		Owner = me->get_id();
		name1 = sprintf("data/%c/%c/%c/%s/list.txt", Owner[0], Owner[1], Owner[2], Owner);
		name2 = sprintf("data/%c/%c/%c/%s/list" SAVE_EXTENSION, Owner[0], Owner[1], Owner[2], Owner);
		if (file_size(name1) > 0)
		{
			rename(name1, name2);
		}
		obj = new ("/inh/user/list");
		obj->set_owner(me->get_real_id());
		obj->set_save_2(sprintf("%d.number", order), i);
		obj->set_save_2(sprintf("%d.name", order), name);
		if (gender == 1)
			obj->set_save_2(sprintf("%d.shape", order), 10000);
		else
			obj->set_save_2(sprintf("%d.shape", order), 10100);
		obj->set_save_2(sprintf("%d.armor", order), me->get_armor_code());
		obj->set_save_2(sprintf("%d.armorc", order), me->get_armor_color_1());
		obj->set_save_2(sprintf("%d.hair", order), me->get_hair());
		obj->set_save_2(sprintf("%d.hairc", order), me->get_hair_color());
		obj->set_save_2(sprintf("%d.back", order), me->get_back());
		obj->set_save_2(sprintf("%d.backc", order), me->get_back_color());
		obj->set_save_2(sprintf("%d.back2", order), me->get_back2());
		obj->set_save_2(sprintf("%d.back2c", order), me->get_back2_color());
		obj->set_save_2(sprintf("%d.weapon", order), me->get_weapon_code_2());
		obj->set_save_2(sprintf("%d.weaponc", order), me->get_weapon_color());
		obj->set_save_2(sprintf("%d.photo", order), me->get_photo());
		obj->save();
		count = 0;
		for (i = 0; i < 6; i++)
		{
			if (obj->get_save_2(sprintf("%d.number", i + 1)) == 0)
				continue;
			count++;
			numberlist[i] = obj->get_save_2(sprintf("%d.number", i + 1));
			shapelist[i] = obj->get_save_2(sprintf("%d.shape", i + 1));
			levellist[i] = obj->get_save_2(sprintf("%d.level", i + 1));
			namelist[i] = obj->get_save_2(sprintf("%d.name", i + 1));
			if ("/sys/sys/count"->get_new_person() == 0)
			{
				switch (shapelist[i] / 10000)
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
				shapelist[i] = obj->get_save_2(sprintf("%d.armor", i + 1));
				switch (shapelist[i] % 10)
				{
				case 1:
					ret = "Vô Môn Phái";
					break;
					/*	case 2:
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
			famlist[i] = ret;
		}
		if (count == 1)
			"/sys/sys/id"->add_newuser(1);
		"/sys/sys/id"->add_charnumber(1);
		for (i = 0; i < 6; i++)
		{
			if (i > 0 && numberlist[i] == 0)
				continue;
			ret = sprintf("%-12s%-6s", namelist[i], famlist[i]);
			if ("/sys/sys/count"->get_new_person() == 0)
				send_user(me, "%c%c%c%d%c%d%s", 0x49, 9, i + 1, numberlist[i], levellist[i], shapelist[i], ret);
			else
			{
				armor = obj->get_save_2(sprintf("%d.armor", i + 1));
				if (armor == 0)
				{
					if ((shapelist[i] / 100) % 2 == 1)
						armor = 10001;
					else
						armor = 11001;
				}
				send_user(me, "%c%c%c%d%c%d%w%w%w%w%w%w%w%w%w%w%s", 0x49, 11, i + 1, numberlist[i], levellist[i],
						  obj->get_save_2(sprintf("%d.armor", i + 1)),
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
		//	"sys/sys/user2"->add_id_number_file(me->get_number(), me->get_real_id());
		db_user_clear(me, me->get_id());
		destruct(me);
		//                me->set_number( to_int(result) );
		//                LOGIN_0_D->enter_2(me, passwd, name, gender);
		destruct(obj);
		return;
	}
	switch (result[0])
	{
	case '#':
		send_user(me, "%c%s", '!', "数据库操作错误!");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case 'S':
		send_user(me, "%c%s", '!', "此服务器未登记!");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case 'X':
		send_user(me, "%c%s", '!', "您输入了不正确的数据!");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case 'I':
		send_user(me, "%c%s", '!', "您的帐号不存在!");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case '-':
		send_user(me, "%c%s", '!', "无法增加新的玩家号!");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case 'N':
		send_user(me, "%c%s", '!', "这个中文名已经有人用了!");
		send_user(me, "%c%c", 0xff, 0x11);
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case 'U':
		send_user(me, "%c%s", '!', "中文名含有敏感字串!");
		send_user(me, "%c%c", 0xff, 0x11);
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	default:
		send_user(me, "%c%s", '!', "连接出错，请重新连接.");
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		if (order == 0)
			numberlist[0] = to_int(result);
		else
			numberlist[order - 1] = to_int(result);
		for (i = 0; i < 6; i++)
		{
			if (numberlist[i] == 0)
				continue;
			switch (shapelist[i] / 10000)
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
			famlist[i] = ret;
		}
		for (i = 0; i < 6; i++)
		{
			if (i > 0 && numberlist[i] == 0)
				continue;
			ret = sprintf("%-12s%-6s", namelist[i], famlist[i]);
			send_user(me, "%c%c%c%d%c%d%s", 0x49, 9, i + 1, numberlist[i], levellist[i], shapelist[i], ret);
		}
		db_user_clear(me, me->get_id());
		destruct(me);
		//                me->set_number( to_int(result) );
		//                LOGIN_0_D->enter_2(me, passwd, name, gender);
		return;
	}
}
