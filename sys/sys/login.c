
#include <map.h>
#include <effect.h>

/*
 * 用户正常登录模块
 */

#include <ansi.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <city.h>

#define SERVER INI_DIR "server.ini" // ＧＳ标识文件
#define WELCOME "welcome.txt"       // 欢迎信息文件
#define LOGIN_LOG "loginfo.txt"     // 连线记录日志

private
string welcome;

private
static int logintime;

// 函数:生成二进制码
void SAVE_BINARY() {}

// 函数:构造处理
private
void create()
{
        string *line, lemma, content;
        int i, size;

        // 读出检查设置
        line = explode(read_file(SERVER), "\n");
        MAIN_D->set_host_type(0);

        // 历遍检查设置
        for (i = 0, size = sizeof(line); i < size; i++)
        {
                if (line[i][0] == '#' || line[i] == "")
                        continue;
                if (line[i][ < 1] <= ' ')
                        line[i] = line[i][0.. < 2]; // UNIX 格式
                if (line[i][0] == '#' || line[i] == "")
                        continue;
                if (!sscanf(line[i], "%s : %s", lemma, content))
                {
                        log_file(ERROR, sprintf("错误: " SERVER " 第 %d 行检查定义错.\n", i + 1));
                        continue;
                }
                switch (lemma)
                {
                case "region":
                        MAIN_D->set_region(to_int(content));
                        break;
                case "host":
                        MAIN_D->set_host(to_int(content));
                        break;
                case "hosttype":
                        MAIN_D->set_host_type(to_int(content));
                        break;
                }
        }

        if (file_exist(WELCOME))
                welcome = read_file("/" WELCOME);
}

string get_name() { return "Sợi nối Yêu ma"; }

// 函数:连线处理
void logon(object me)
{
        string ip = get_ip_name(me);
        int key1, key2, key3, key4, key5, key6, key7, key8;
        // 判断地址是否允许
        if (!CHECK_D->is_passed_ip(ip) && CHECK_D->is_banned_ip(ip))
        {
                send_user(me, "%c%s", '!', "Thật xin lỗi địa chỉ " + ip + " ở " GAME_NAME " không được hoan nghênh");
                destruct(me);
        }
        else
        {
                key1 = random(MAX_NUMBER);
                key2 = random(MAX_NUMBER);
                key3 = random(MAX_NUMBER);
                key4 = random(MAX_NUMBER);
                key5 = random(MAX_NUMBER);
                key6 = random(MAX_NUMBER);
                key7 = random(MAX_NUMBER);
                key8 = MAIN_D->get_absolute_random_number(); // key8 = random(MAX_NUMBER);
                if (MAIN_D->get_host_type() == 0)
                {
                        key1 = 100;
                        key2 = 100;
                        key3 = 100;
                        key4 = 100;
                        key5 = 100;
                        key6 = 100;
                        key7 = 100;
                        key8 = 100;
                }
                me->set("key", sprintf("%08X%08X%08X%08X%08X%08X%08X%08X", key1, key2, key3, key4, key5, key6, key7, key8));
                send_user(me, "%c%c%w%d%d%d%d%d%d%d%d%d", 0x49, 0x01, 1, key1, key2, key3, key4, key5, key6, key7, key8, time()); // time() 防加速器
                me->enable_logon_cmds();
        }
}

// 函数:登录处理
void connect(object me, string id, string code, int order)
{
        string lowId, passwd, lowId2, passwd2, result;
        object *user;
        int size, time, number;
        passwd = passwd_decrypt(me->get("key"), code);

        if (me->get_login_flag() >= 2)
                return;
        if (me->get_id() != "" && me->get_id() != 0)
                return;

        if (MAIN_D->get_host_type() == 6012)
        {
                lowId = id;
                me->set_id(id);
                me->set_real_id(id);
                log_file("php.dat", sprintf(MAIN_D->get_php_ip() + ":80\n"
                                                                   "GET /xq2/authentic.php?key=%s\r\n",
                                            id));
                log_file("php.dat", sprintf(MAIN_D->get_php_ip() + ":80\n"
                                                                   "GET /xq2/authentic.php?key=%s\r\n",
                                            rawurlencode2(id)));
                db_user_authentic(me, lowId, sprintf(MAIN_D->get_php_ip() + ":80\n"
                                                                            "GET /xq2/authentic.php?key=%s\r\n",
                                                     rawurlencode2(id)));
                me->authentic_callout();
                me->user_authentic_callout("", order);
                return;
        }

        // 标识密码是否合法
        if (!CHECK_D->is_legal_id(me, lowId = strlwr(id)))
                return;
        // if( !CHECK_D->is_legal_passwd(me, passwd) ) return;
        if (!"sys/sys/check2"->is_legal_user(me, lowId = strlwr(id), passwd))
                return;

        // 玩家总数限制判断
        // 设置以及判断标识

        me->set_id(id);
        me->set_real_id(id);
        user = USER_D->get_user();
        size = sizeof(user);
        if (size >= "/sys/sys/count"->get_max_user() && id != "ten" && order == 0)
        {
                send_user(me, "%c%s", '!', GAME_NAME "Nhân số đã đạt tối đa, quay trở lại sau");
                destruct(me);
                return;
        }
        /*
        // 台湾版本 8:00 到 20:00 限制进游戏，只有 ten 和 gm1 两个号例外
        if (MAIN_D->get_host_type()==1005)
        {
        	time = (time() / 3600);
        	send_user( me, "%c%s", '!', sprintf("time mod 3600 =%d 当前时间为%d", time, time % 24 ) );
        	destruct(me);
        	return;
        	if ( (time<8||time>=20) && id!="ten" && id!= "gm1" )
	        {
	                send_user( me, "%c%s", '!', "封测维护中，游戏伺服器尚未开启." );
	                destruct(me);
	                return;
	        }
        }
*/
        if (me->get_id() != lowId)
        {
                send_user(me, "%c%s", '!', GAME_NAME "Trò chơi đang bảo trì, hãy quay lại sau");
                destruct(me);
                return;
        }

        if ("/sys/sys/count"->get_test() == 1)
        {
                number = "/sys/sys/id"->get_max_id();
                number++;
                "/sys/sys/id"->add_max_id(number);
                me->set_number(number);
                me->set_name(sprintf("Thí nghiệm %d", number));
                me->set_login_flag(3);
                me->set("is_gm", 1);
                me->login_timeout();
                me->enable_player();
                me->setup();
                send_user(me, "%c%c", 0x49, 0x02); // 登录成功
                USER_D->add_user(me);
                tell_user(me, "Thí nghiệm người tiến vào");
                if (is_gm(me))
                        tell_user(me, "Quyền hạn thiết lập thành công");
                USER_D->gm_channel(sprintf(HIR " %s : %s ( %d ) do %s nối vào.",
                                           get_name(), me->get_name(), me->get_number(), get_ip_name(me)));
                MAP_D->add_to_void(me);
                return;
        }
        lowId2 = rawurlencode(lowId);
        passwd2 = rawurlencode(passwd);
        //db_user_authentic(me, lowId, passwd);    // 之后 destruct 要用 db_user_clear
        if (MAIN_D->get_host_type() != 4)
        {
                db_user_authentic(me, lowId, sprintf(MAIN_D->get_php_ip() + ":80\n"
                                                                            "GET /xq2/authentic.php?id=%s&passwd=%s&region=%d&host=%d\r\n",
                                                     lowId2, passwd2, MAIN_D->get_region(), MAIN_D->get_host())); // 之后 destruct 要用 db_user_clear
        }
        else
        {
                result = sprintf(MAIN_D->get_php_ip() + ":80\n"
                                                        "GET http://%s/login2.php?t=%s&n=%s&c=%s&p=%s&r=%d&h=%d\r\n",
                                 MAIN_D->get_php_ip(), short_time_2(), lowId2, get_ip_name(me), md5(passwd2 + "1aEa0l1aEGVl0YOeCQJ2E8htqPd"), MAIN_D->get_region(), MAIN_D->get_host());
                db_user_authentic(me, lowId, result); // 之后 destruct 要用 db_user_clear
                                                      //	if (MAIN_D->get_region()==0)
                                                      //		log_file("testphp.dat", result );
        }
        me->authentic_callout();
        me->user_authentic_callout(passwd, order);
}

// 函数:本地用户校验
void do_user_exist(object me, string passwd, string name)
{
        object *user, body, temp, *alluser;
        string lowId, ip1, ip2, realid;
        int i, size, acountid;

        // 判断是否在游戏中

        lowId = me->get_id();
        acountid = me->get_acountid();
        realid = me->get_real_id();
        if (me->get_login_flag() >= 2)
                return;

        /*
 * 注释:这里用 users() 是因为担心取到系统正 load 起来的 USER (例如 purge, 修改帮派成员之类)
 */
        alluser = users();
        alluser -= ({me});
        alluser -= ({0});
        if (realid != "sys/sys/user2"->numberToId(me->get_number()))
        {
                send_user(me, "%c%s", '!', "Tài khoản của bạn có vấn đề vui lòng liên hệ với admin");
                db_user_clear(me, me->get_id());
                destruct(me);
                return;
        }
        if (arrayp(alluser) // 获取所有玩家  children(USER) - ({ load_object(USER) })
            && sizeof(alluser) > 0 && arrayp(user = filter_array(alluser - ({me}), (
                                                                                       : $1->get_id() == $2:),
                                                                 lowId)) // 判断ＩＤ吻合(除自己外)
            && sizeof(user)                                              // 用户个数大于０
            && objectp(body = user[0]))                                  // 取第一个用户
        {
                if (body->get_login_flag() < 2) // 登录中用户
                {
                        db_user_clear(body, body->get_id());
                        destruct(body);
                }
                else if (body->is_user())
                {
                        /*    if( body->get( "quit" ) )    // 退出中用户
                        {
                                send_user( me, "%c%s", '!', "Quit hoạt động không hoàn chỉnh, không quá nhanh chóng đăng nhập" );
                                db_user_clear( me, me->get_id() );
                                destruct(me);
                                return;
                        }*/
                        ip1 = get_ip_name(me);
                        ip2 = get_ip_name(body);

                        if ((is_gm(body) && CHECK_D->check_gm_ip(ip1, 1) != 1) || (is_gm2(body) && CHECK_D->check_gm_ip(ip1, 2) != 1) || (is_gm3(body) && CHECK_D->check_gm_ip(ip1, 3) != 1) || (is_god(body) && CHECK_D->check_gm_ip(ip1, 4) != 1))
                        {
                                send_user(me, "%c%s", '!', "Tài khoản không được phép đăng nhập vào IP này");
                                db_user_clear(me, me->get_id());
                                destruct(me);
                                return;
                        }
                        if (is_gm3(body) && "/sys/sys/count"->get_can_gm3() == 0)
                        {
                                send_user(me, "%c%s", '!', "Hiện nay không cho phép hoạt động số đăng nhập");
                                db_user_clear(me, me->get_id());
                                destruct(me);
                                return;
                        }
                        tell_user(me, HIR "Một ai đó trong %s với tài khoản của bạn, bạn sẽ đá anh ta ra khỏi trò chơi", ip1 == ip2 ? ip2 : RED + ip2 + HIR);
                        tell_user(body, HIR "Một người nào đó trong %s với tài khoản của bạn, %s của bạn ra khỏi trò chơi", ip1 == ip2 ? ip1 : RED + ip1 + HIR, ip2);
                        // me->delete_save("ndmkk");
                        // body->delete_save("ndmkk");
                        me->delete_save("ndmkhtk");
                        body->delete_save("ndmkhtk");
                        record_login(body, body->get_id(), 0);
                        record_login(body, body->get_id(), 1);
                        // log_file

                        temp = new (USER);
                        exec(temp, body);
                        destruct(temp); // 将被重连者断线

                        LOGIN_1_D->reconnect(me, body);
                        return;
                }
        }
        alluser -= ({me});
        alluser -= ({0});

        if (arrayp(alluser) // 获取所有玩家  children(USER) - ({ load_object(USER) })
            && sizeof(alluser) > 0 && arrayp(user = filter_array(alluser, (
                                                                              : $1->get_real_id() == $2:),
                                                                 realid)) // 判断ＩＤ吻合(除自己外)
            && sizeof(user)                                               // 用户个数大于０
            && objectp(body = user[0]))                                   // 取第一个用户
        {
                send_user(me, "%c%s", '!', "Đã cùng một tài khoản trong game");
                db_user_clear(me, me->get_id());
                destruct(me);
                return;
        }
        db_user_exist(me, lowId);
        me->user_exist_callout(lowId, passwd, name);
}

// 函数:获取用户资料
void do_user_restore(object me, string id, string passwd, string name)
{
        db_user_restore(me, me->get_id());
        me->user_restore_callout(id, passwd, name, me->get_acountid());
}

private
void enter_world(object me);

// 函数:准备进入游戏
void enter(object me, string passwd) // 输入帐号密码通过，并取到用户资料
{
        if (me->get_save("khoanhanvat") >= 1)
        {
                send_user(me, "%c%s", '!', "Nhân vật này đã bị Khoá");
                destruct(me);
                return;
        }
        send_user(me, "%c%c", 0x49, 0x02); // 登录成功
        enter_world(me);
        "sys/party/mingren"->check_mingren_upline(me);
}

// 函数:进入游戏处理
void enter_world(object me)
{
        object *user, map, city, mailbox, npc, item;
        string id, name, ip1, ip2, start_place, cTmp;
        int number, z, x, y, d, p, level, point, time;

        /*
 * 注释:这里不能用 users() 是因为担心:
 *       1, 系统正 load 起来的 USER (例如 purge, 修改帮派成员之类) 数据的唯一性
 *       2, 连线到一半的 USER 可能还没有成为 users() 成员
 */
        // 重要:防止复制 BUG(确认无相同ＩＤ)(禁止后来的玩家登录)
        if (arrayp(user = children(USER) - ({load_object(USER)})) // 获取所有玩家  users()
            && arrayp(user = filter_array(user - ({me}), (
                                                             : $1->get_id() == $2:),
                                          me->get_id())) // 判断ＩＤ吻合(除自己外)
            && sizeof(user))                             // 用户个数大于０
        {
                db_user_clear(me, me->get_id());
                destruct(me);
                return;
        }
        if ("/sys/sys/count"->get_test() == 1)
        {
                me->set("is_gm", 1);
                me->delete_save_2("Newbie.Login");
                if (!me->get_name())
                        me->set_name(sprintf("Vai trò %d", me->get_number()));
        }
        me->setup();
        if ((is_gm(me) && CHECK_D->check_gm_ip(get_ip_name(me), 1) != 1) || (is_gm2(me) && CHECK_D->check_gm_ip(get_ip_name(me), 2) != 1) || (is_gm3(me) && CHECK_D->check_gm_ip(get_ip_name(me), 3) != 1) || (is_god(me) && CHECK_D->check_gm_ip(get_ip_name(me), 4) != 1))
        {
                send_user(me, "%c%s", '!', "Tài khoản không được phép đăng nhập vào IP này");
                db_user_clear(me, me->get_id());
                destruct(me);
                return;
        }
        if (is_gm3(me) && "/sys/sys/count"->get_can_gm3() == 0)
        {
                send_user(me, "%c%s", '!', "Hiện nay không cho phép hoạt động số đăng nhập");
                db_user_clear(me, me->get_id());
                destruct(me);
                return;
        }
        USER_D->add_user(me);
        if ((is_gm(me) || is_gm3(me)) && ("/sys/sys/count"->get_test() == 0))
                me->set_name("Quản Lý Viên");

        // 清除重复登录玩家

        ip1 = me->get_quit_ip();
        ip2 = get_ip_name(me);
        if (ip1)
                tell_user(me, "Lần trước bạn là tuyến nối %s từ %s .\n", short_time(me->get_quit_time()), ip1 == ip2 ? ip1 : HIR + ip1 + NOR);
        tell_user(me, "Bây giờ bạn là tuyến nối %s từ %s .\n", short_time(), ip2);

        me->set_fam_name(me->get_fam_name());
        /*
        level = me->get_level();
        point = level * me->get_gift_point_times();
        if (me->get_save("testbonus")) point += 2* level;

        if (  me->get_con_2()+me->get_spi_2()+ me->get_str_2()+me->get_cps_2()+me->get_dex_2()+me->get_gift_point() >point)
        {
        	level = "/sys/user/exp"->get_level(me);
        	me->set_level(level);
        	me->set_max_level(level);
        	me->set_save("errorlevel", 1);
        	point = level * me->get_gift_point_times();
        	if (me->get_save("testbonus")) point += 2* level;
        	if ( me->get_con_2()+me->get_spi_2()+ me->get_str_2()+me->get_cps_2()+me->get_dex_2()+me->get_gift_point() >point)
        	{
		        me->set_con_2(0);
		        me->set_spi_2(0);
		        me->set_str_2(0);
		        me->set_cps_2(0);
		        me->set_dex_2(0);
		        me->set_gift_point(point);
        	}
        }
*/
        if (welcome && welcome != "")
                tell_user(me, "%s", welcome); // 显示欢迎信息( "%s" 的方法可使用 % 号在文本中)
                                              /*
	if (me->get_pk()>=5 ||get_effect(me, EFFECT_USER_PK))
	{
	        me->set_attack_mode(0);
	        write_user(me, "Hình thức tấn công của bạn: Tấn công không hạn chế.");
	}
	else
	{
	        me->set_attack_mode(1);
        	write_user(me, "Hình thức tấn công của bạn: Hoàn toàn bảo hộ.");
        }
*/
        if (me->get_pk() >= 100)
        {
                set_effect(me, EFFECT_USER_PK, 0);
        }
        me->set_attack_mode(1);
        //  me->delete_save("ndmkk");
        me->delete_save("ndmkhtk");
        MAILBOX->sys_mail(me->get_id(), me->get_number(), sprintf("Chào mừng bằng hữu %s đến với Chiến Quốc", me->get_name()));
        time = me->get_save("suicide");
        if (time > 0)
        {
                write_user(me, HIY "Bạn quyết định tự sát, hãy cân nhắc lại kĩ càng");
        }
        me->set_attack_move(0);
        me->count_gift();
        me->restore_inventory();
        me->restore_beast();
        me->disable_logon_cmds();
        USER_SUIT_D->check_suit_equip(me);
        send_user(me, "%c%c%d", 0x49, 10, get_heart_timer(me));
        me->set_2("go_count.time2", get_heart_timer(me));

        me->set_login_flag(2);
        if (get_effect(me, EFFECT_MAGIC_CARD))
                MAGIC_CARD_D->effect_break(me);

        record_login(me, me->get_id(), 1);
        me->send_legend();

        send_user(me, "%c%c%c%s", 0x3d, 49, me->get_org_position(), me->get_org_name()); //必须发
        // 进入初始场景

        if (stringp(start_place = me->get_start_place()) && sscanf(start_place, "%d:(%d,%d)%d", z, x, y, d) == 4 // 前次退出点
            && z < 1000 && (p = get_valid_xy(z, x, y, IS_CHAR_BLOCK)))
        {
                me->add_to_scene(z, p / 1000, p % 1000, d);
                /*	if ( random(100) < 30 ) {
				me->add_to_scene(80, 352, 196, d);
				}
				else if ( random(100) < 40 ) {
				me->add_to_scene(80, 387, 196, d);
				}
				else if ( random(100) < 50 ) {
				me->add_to_scene(80, 361, 146, d);
				}
				else if ( random(100) < 60 ) {
				me->add_to_scene(80, 340, 132, d);
				}
				else if ( random(100) < 70 ) {
				me->add_to_scene(80, 197, 227, d);
				}
				else if ( random(100) < 80 ) {
				me->add_to_scene(80, 287, 215, d);
				}
				else {
				me->add_to_scene(80, 244, 124, d);
				}	*/
        }
        else if (stringp(start_place = me->get_start_place()) && sscanf(start_place, "%d:(%d,%d)%d", z, x, y, d) == 4 // 前次退出点
                 && z > 999 && (p = get_valid_xy(z, x, y, IS_CHAR_BLOCK)) && objectp(map = get_map_object(z)) && map->is_ken_map())
        {
                me->add_to_scene(z, p / 1000, p % 1000, d);
                map->check_outmap(60, me);
        }
        else
                MAP_D->add_to_void(me); // 移入 VOID 场景
        CONNECT_D->init_user(me);

        //      if( me->is_die() && get_effect(me, EFFECT_USER_DIE) ) set_effect(who, EFFECT_USER_DIE, 1);    // 登录时死亡玩家自动复活

        //      me->save();
        if (me->get_perform("03191") && me->get_fam_name() != "Đào Hoa Nguyên")
        {
                me->set_perform("03191", 0);
        }
        if (me->get_perform("03192") && me->get_fam_name() != "Đào Hoa Nguyên")
        {
                me->set_perform("03192", 0);
        }
        if (me->get_perform("02221#") && me->get_fam_name() != "Thục Sơn")
        {
                me->set_perform("02221#", 0);
        }
        if (me->get_perform("02222#") && me->get_fam_name() == "Thục Sơn")
        {
                me->set_perform("02222#", 0);
        }

        if (me->get_save("login_count") > 2)
                log_file("errlogin.txt", sprintf("id:%s number:%d\n", me->get_id(), me->get_number()));
        me->add_save("login_count", 1);
        USER_D->gm_channel(sprintf(HIR "%s : %s (%d) do %s nối vào.",
                                   get_name(), me->get_name(), me->get_number(), get_ip_name(me)));
        log_file(LOGIN_LOG, sprintf("%s %s %d %s %s - - [%x#] kết nối với nhập\n", me->get_id(), me->get_name(), me->get_number(), get_ip_name(me), short_time(), getoid(me)));

        //        me->send_to_friend(1);
        me->receive_friends();
        me->send_black();

        mailbox = new (MAILBOX);
        mailbox->set_owner(me->get_id());
        if (mailbox->check_mails2(me))
                send_user(me, "%c", 0x4d);
        destruct(mailbox);

        me->set_login_time(time());
        //        me->clean_online_time();    // 清除沉迷时间

        //        me->add_strength( gone_time( me->get_quit_time() ) / 360 );    // 离线也可恢复体力
        set_effect(me, EFFECT_USER_LOGIN, 20);

        if (city = CITY_D->get_city_object(me))
                city->pay_salary_baseon_contribute(me);

        me->login_timeout(); // 清除限时进程

        USER_SLAVE_D->restore_all_slave(me); // 召唤兽保留１分钟

        if (me->get_quest("escort.flag") == 1               // 运镖任务(物品)
            && stringp(id = me->get_quest("escort.robber")) // 寻找蒙面人
            && objectp(npc = find_char(id)) && npc->is_escort_robber() && present("Vật Phẩm Quý Bấu", me, 1, MAX_CARRY * 4))
        {
                npc->start_fight(me);
                me->set_quest("escort.robber#", npc);
                send_user(me, "%c%s", '!', "Kẻ lạ xuất hiện, hành động bị ảnh hưởng.");
        }

        if ((name = me->get_org_name()) && name != "") // 更新帮派信息
        {
                // if (!CITY_ZHOU->get_2(sprintf("org.%s", name)))
                // {

                //         CITY_QI->load_zhou();
                // }
                npc = CITY_ZHOU->get_2(sprintf("org.%s", name));
                if (objectp(npc))
                {
                        if ((number = me->get_number()) && npc->get_member_id(number))
                        {
                                npc->set_member_quit(number, 0);
                                npc->set_member_id(number, me->get_id());
                        }
                }
                else
                {
                        me->set_org_name("");
                        me->set_org_position(0);
                        me->delete_title("C001");
                        me->delete_title("C002");
                        me->delete_title("C003");
                        me->delete_title("C004");
                        me->delete_title("C005");
                        me->delete_title("C006");
                        me->delete_title("C007");
                        me->delete_title("C008");
                        send_user(me, "%c%c%c%c", 0x3d, 49, 0, 0);
                }
        }

        if ((z = 60 - gone_time(me->get_save_2("familyuse"))) > 0) //信物冻结时间
        {
                send_user(me, "%c%c%c%w", 0x30, 0, 8, z);
        }
        if ((z = me->get_extra_double_time() - me->get_game_time()) > 0)
                send_user(me, "%c%w%w%c", 0x81, 9998, z, EFFECT_GOOD);
        if ((z = me->get_extra_exp_time() - time()) > 0)
                send_user(me, "%c%w%w%c", 0x81, 9999, z, EFFECT_GOOD);

        // 检查门派
        if (me->get_fam_name() && !me->get_save("famrec"))
        {
                "/sys/sys/count"->add_family(me->get_fam_name(), 1);
                me->set_save("famrec", 1);
        }
        CHAR_CHAR_D->send_loop_perform(me, me);   // 显示持续效果
        CHAR_CHAR_D->send_loop_perform_2(me, me); // 显示持续图标
                                                  //-----------------------------------------------------------------------------
        if (item = me->get_equip(HAND_TYPE))
                if (item->get("time_item"))
                {
                        if (time() < item->get_lock_time() || item->get_lock_time() == 0)
                        {
                                item->start_loop_perform(me);
                        }
                }
        if (item = me->get_equip(BACK_TYPE))
        {
                item->get_equip_effect(me);
        }
        if (item = me->get_equip(FASHION_TYPE))
        {
                item->get_equip_effect(me);
        }
        //-----------------------------------------------------------------------------
        if (get_effect_3(me, EFFECT_CHAR_INVISIBLE))
        {
                if (get_effect_3(me, EFFECT_03643) || me->get_save("no_visible"))
                        send_user(me, "%c%c%c", 0x3d, 241, 2);
        }
        me->add_title("X");
        me->send_title_list();

        if (me->get_vip())
                "item/sell/0061"->vip_effect(me);
        USER_RANK_D->online_rank(me, 0);
        send_user(me, "%c%c%c", 0xA2, 10, me->get_save_2("online_rank.level")); //修为等级

        "sys/party/vstfix"->check_org_title(me); //检查无双称谓
        if (me->have_title("Z888"))
        {
                CHAT_D->sys_channel(0, HIY "Cung nghênh Vô Song Thành Chủ đại danh vang dội " HIG + me->get_name() + HIY " Đăng nhập Chiến Quốc Loạn Thế Anh Hùng!");
                if (WUSHUANG->get_save("wg_duty") > 20000000)
                        MAILBOX->sys_mail(me->get_id(), me->get_number(), HIW "Bạn chiếm lĩnh Vô Song Thành thuế đã đạt tối đa, thuế sẽ không còn tăng");
        }
}
