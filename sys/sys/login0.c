
/*
 * 用户新登录模块
 */
#include <task.h>
#include <chia_kenh.h>
// 函数:生成二进制码
void SAVE_BINARY() {}

void add_pet(object who);
void add_item(object me);

// 函数:新登录准备
void new_login_1(object me, string passwd, string name) // 输入帐号密码通过，但找不到用户资料
{
	send_user(me, "%c%c", 0x49, 0x08); // 无此用户(打开新登录界面)
	db_user_clear(me, me->get_id());
	destruct(me);
	return;
}

// 函数:新登录处理
void new_login_2(object me, string id, string code, string name, int gender, int order) // 输入新登录资料:帐号、密码、姓名、性别、序号
{
	string lowId, passwd;

	passwd = passwd_decrypt(me->get("key"), code);
	if (MAIN_D->get_host_type() == 6012)
	{
		me->set_id(id);
		me->set_real_id(id);
		lowId = id;
		//		log_file("php.dat", sprintf( MAIN_D->get_php_ip()+":80\n"
		//			"GET /xq2/authentic.php?key=%s\r\n", rawurlencode(id) ) );
		db_user_authentic(me, lowId, sprintf(MAIN_D->get_php_ip() + ":80\n"
																	"GET /xq2/authentic.php?key=%s\r\n",
											 rawurlencode2(id)));
		me->user_authentic_callout_2("", name, gender, order);
		return;
	}
	// 标识密码是否合法
	if (!CHECK_D->is_legal_id(me, lowId = strlwr(id)))
		return;
	// if( !CHECK_D->is_legal_passwd(me, passwd) ) return;

	if (!CHECK_D->is_legal_name(me, name))
		return;

	// 玩家总数限制判断
	// 设置以及判断标识
	// if (MAIN_D->get_kenh() != KENH_BANG)
	// {

	// 	send_user(me, "%c%s", '!', "Vui lòng tạo nhân vật ở Kênh Bang Phái");
	// 	return;
	// }
	me->set_id(id);
	me->set_real_id(id);

	if (me->get_id() != lowId)
	{
		send_user(me, "%c%s", '!', GAME_NAME "Trò chơi đang bảo trì, hãy quay lại sau");
		destruct(me);
		return;
	}
	if (MAIN_D->get_host_type() != 4)
	{
		db_user_authentic(me, lowId, sprintf(MAIN_D->get_php_ip() + ":80\n"
																	"GET /xq2/authentic.php?id=%s&passwd=%s&region=%d&host=%d\r\n",
											 rawurlencode(lowId), rawurlencode(passwd), MAIN_D->get_region(), MAIN_D->get_host())); // 之后 destruct 要用 db_user_clear
	}
	else
	{
		db_user_authentic(me, lowId, sprintf(MAIN_D->get_php_ip() + ":80\n"
																	"GET http://%s/login2.php?t=%s&n=%s&c=%s&p=%s&r=%d&h=%d\r\n",
											 MAIN_D->get_php_ip(), short_time_2(), rawurlencode(lowId), get_ip_name(me), md5(rawurlencode(passwd) + "1aEa0l1aEGVl0YOeCQJ2E8htqPd"), MAIN_D->get_region(), MAIN_D->get_host())); // 之后 destruct 要用 db_user_clear
																																																								//	if (MAIN_D->get_region()==0)
																																																								//		log_file("php.dat", sprintf( MAIN_D->get_php_ip()+":80\n"
																																																								//			"GET http://%s/login.php?t=%s&n=%s&c=%s&p=%s&r=%d&h=%d\r\n", MAIN_D->get_php_ip(), short_time_2(), rawurlencode(lowId), get_ip_name(me), md5(rawurlencode(passwd)+"1aEa0l1aEGVl0YOeCQJ2E8htqPd"), MAIN_D->get_region(), MAIN_D->get_host() ));
	}
	//        db_user_authentic(me, lowId, passwd);    // 之后 destruct 要用 db_user_clear
	//         db_user_authentic( me, lowId, sprintf( MAIN_D->get_php_ip()+":80\n"
	//              "GET /xq2/authentic.php?id=%s&passwd=%s&region=%d&host=%d\r\n", rawurlencode(lowId), rawurlencode(passwd), MAIN_D->get_region(), MAIN_D->get_host() ) );    // 之后 destruct 要用 db_user_clear
	me->user_authentic_callout_2(passwd, name, gender, order);
}

// 函数:本地用户校验
void do_user_exist_2(object me, string passwd, string name, int gender, int order)
{
	object *user;
	string lowId;
	int i, size;

	// 判断是否在游戏中
	if (order > 1)
	{
		me->set_real_id(me->get_id());
		me->set_id(sprintf("%s#%d", me->get_id(), order));
	}
	lowId = me->get_id();

	/*
 * 注释:这里用 users() 是因为担心取到系统正 load 起来的 USER (例如 purge, 修改帮派成员之类)
 */
	if (arrayp(user = users()) // 获取所有玩家  children(USER) - ({ load_object(USER) })
		&& arrayp(user = filter_array(user - ({me}), (
														 : $1->get_id() == $2:),
									  lowId)) // 判断ＩＤ吻合(除自己外)
		&& sizeof(user))					  // 用户个数大于０
	{
		send_user(me, "%c%s", '!', "Bạn đang trong trò chơi"); // 同时新登录的情况
		db_user_clear(me, me->get_id());
		destruct(me);
		return;
	}
	db_user_exist(me, lowId);
	me->user_exist_callout_2(passwd, name, gender, order);
}

// 函数:用户姓名校验
void do_user_check_2(object me, string passwd, string name, int gender, int order)
{
	//        db_user_check( me, name, MAIN_D->get_region(), MAIN_D->get_host() );
	int shape;
	if (gender == 1)
		shape = 10000;
	else
		shape = 10100;
	if (MAIN_D->get_host_type() == 6012)
	{
		log_file("php.dat", sprintf(MAIN_D->get_php_ip() + ":80\n"
														   "GET /xq2/check.php?id=%s&name=%s&shape=%d&region=%d&host=%d&ip=%s\r\n",
									rawurlencode(me->get_id()), rawurlencode(name), shape, MAIN_D->get_region(), MAIN_D->get_host(), get_ip_name(me)));

		db_user_check(me, sprintf(MAIN_D->get_php_ip() + ":80\n"
														 "GET /xq2/check.php?id=%s&name=%s&shape=%d&region=%d&host=%d&ip=%s\r\n",
								  rawurlencode(me->get_id()), rawurlencode(name), shape, MAIN_D->get_region(), MAIN_D->get_host(), get_ip_name(me)));
	}
	if (MAIN_D->get_host_type() != 4)
		db_user_check(me, sprintf(MAIN_D->get_php_ip() + ":80\n"
														 "GET /xq2/check.php?id=%s&name=%s&shape=%d&region=%d&host=%d&ip=%s\r\n",
								  rawurlencode(me->get_id()), rawurlencode(name), shape, MAIN_D->get_region(), MAIN_D->get_host(), get_ip_name(me)));
	else
	{
		db_user_check(me, sprintf(MAIN_D->get_php_ip() + ":80\n"
														 "GET http://%s/register.php?n=%s\r\n",
								  MAIN_D->get_php_ip(), rawurlencode(strlwr(name))));
		//log_file("php.dat",  sprintf( MAIN_D->get_php_ip()+":80\n"
		//                	"GET http://%s/register.php?n=%s\r\n",
		//                	MAIN_D->get_php_ip(), rawurlencode(name)));
	}
	me->user_check_callout_2(passwd, name, gender, order);
}

void new_login_3(object me, string name, int gender);

// 函数:准备进入游戏
void enter_2(object me, string passwd, string name, int gender) // 输入帐号密码通过，并生成用户资料
{
	send_user(me, "%c%c", 0x49, 0x02); // 登录成功
	new_login_3(me, name, gender);
}

// 函数:新登录处理
void new_login_3(object me, string name, int gender)
{
	object item, who;
	int z, x, y, p, k, l, j, u, t, f;
	who = this_player();

	me->set_name(name);

	//	ID_D->add_max_id(me->get_number()); // 更新最大ＩＤ

	//      me->set_store_name("货物出售");
	me->set_max_pawn_size(1);

	switch (gender)
	{
	case 1:
		me->set_gender(1);
		me->set_con_1(30);
		me->set_spi_1(25);
		me->set_str_1(25);
		me->set_cps_1(25);
		me->set_dex_1(25);

		break;

	default:
		me->set_gender(2);
		me->set_con_1(30);
		me->set_spi_1(25);
		me->set_str_1(25);
		me->set_cps_1(25);
		me->set_dex_1(25);

		break;
	}
	"/quest/help"->send_help_tips(me, 1);
	"/quest/help"->send_help_tips(me, 49);
	me->set_potential(100);

	me->set_id_protect(0);
	me->set_id_locked(0);

	me->set_birthday(time());
	me->set_fee_start(time());
	//me->set_level(20);
	me->count_gift();
	//me->add_gift_point(80);
	USER_ENERGY_D->count_max_hp(me);
	USER_ENERGY_D->count_max_mp(me);
	me->set_hp(me->get_max_hp());
	me->set_mp(me->get_max_mp());

	//	add_pet(me);
	/*
        me->set_save_2( "hotkey.1", "14" );
        me->set_save_2( "hotkey.2", "15" );
        me->set_save_2( "hotkey.6", "51" );
        me->set_save_2( "hotkey.7", "61" );
        me->set_save_2( "hotkey.8", "12" );
        me->set_save_2( "hotkey.9", "32" );
        me->set_save_2( "hotkey.10", "31" );
        */
	me->set_hotkey("8", "99");
	me->set_hotkey("9", "61");
	me->set_hotkey("10", "51");
	me->save();

	p = get_jumpin(1, 30);
	me->set_start_place(sprintf("%d:(%d,%d)%d", 1, p / 1000, p % 1000, 3)); // 进入出生地
	LOGIN_D->enter_world(me);
	if (!me)
		return;
	"/sys/sys/id"->add_loginplayer(1);

	add_item(me);

	/*	item = new ("/item/01/0001");
	p = item->move(me,-1);
	if ( !p )
	{
		destruct(item);	
		return ;
	}
	item->add_to_user(p);*/
	me->set_legend(TASK_NEWBIE_00, 1);
	//	send_user( me, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_00,"Nhiệm Vụ Chỉ Dẫn" );
	//	send_user( me, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_00,1,"Sứ Mệnh Đưa Thư" );
	//	me->set_save_2("task.story",1);
	//	TASK_D->get_task_list(me);
	//	send_user( me, "%c%c%c%w%w", 0x51, 2, 5,8000,1,);

	//新手信物
	item = new ("item/09/0908");
	me->restore_equip(item);

	//送绑定的战国令
	item = new ("item/08/0006");
	p = item->move(me, -1);
	item->add_to_user(p);

	item = new ("item/tuiquatanthuhieu/tuiquatanthu");
	k = item->move(me, -1);
	item->add_to_user(k);

	/*item = new ("ken/hotrotanthu/tuiquatanthu");
	k = item->move(me, -1);
	item->add_to_user(k); */

	/*	item = new("item/tuiquatanthuhieu/11");
	l = item->move(me,-1);
	item->add_to_user(l);
	
	item = new("item/tuiquatanthuhieu/12");
	t = item->move(me,-1);
	item->add_to_user(t);
	
	item = new("item/tuiquatanthuhieu/13");
	f = item->move(me,-1);
	item->add_to_user(f);*/

	//	item = new("item/01/0203");
	//	u = item->move(me,-1);
	//	item->add_to_user(u);

	//	item = new("item/01/0204");
	//	j = item->move(me,-1);
	//	item->add_to_user(j);
}
//赠送宠物
void add_pet(object me)
{
	int i;
	object pet;
	string cName, *nKey;
	mapping mpPet1 = (["Gà Núi":10, "Thỏ Hoang":11, "Ong Mật":150, "Kiến Nhỏ":151]);
	mapping mpPet2 = (["Quỷ Hỏa":901, "U Linh":900, "Phi Tặc":202, "Ác Lão Đầu":250, "Ác Đồ":200, "Cuồng Đồ":201]);

	if (MAIN_D->get_host_type() == 4) //猫扑
	{
		if (time() > mktime(2007, 2, 10, 0, 0, 0))
			return;
	}

	nKey = keys(mpPet2);
	cName = nKey[random(sizeof(nKey))];
	pet = USER_BEAST_D->give_pet(me, cName, 1, 20, mpPet2[cName], 0);
	if (pet)
		pet->set_save("no_give", 1);
	nKey = keys(mpPet1);
	cName = nKey[random(sizeof(nKey))];
	pet = USER_BEAST_D->give_pet(me, cName, 1, 0, mpPet1[cName], 0);
	if (pet)
		pet->set_save("no_give", 1);
}

void add_item(object me)
{
	int p;
	object item;
	switch (random(3))
	{
	case 1:
		item = new ("item/01/7200");
		break;
	case 2:
		item = new ("item/01/7500");
		break;
	default:
		item = new ("item/01/7400");
		break;
	}
	p = item->move(me, -1);
	if (!p)
	{
		destruct(item);
		return;
	}
	item->add_to_user(p);
	me->use_equip(item);
	//	给玩家战国宝典
	item = new ("item/01/7600");
	p = item->move(me, -1);
	if (!p)
	{
		destruct(item);
		return;
	}
	item->add_to_user(p);
	//
}