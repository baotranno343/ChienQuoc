
#include <city.h>
#include <equip.h>

private
object *Users = ({}); // 全体用户
private
object *Gms = ({}); // 所有ＧＭ
private
object *Players = ({}); // 所有玩家

private
object *LevelA = ({}); // 初级玩家
private
object *LevelB = ({}); // 低级玩家
private
object *LevelC = ({}); // 其它玩家

private
object *Battle = ({}); // 战争玩家

private
string User2 = "sys/sys/user2";
void add_user(object who);

// 函数：生成二进制码
void SAVE_BINARY() {}

// 函数：构造处理
void create()
{
        object *user;
        int i, size;
        if (arrayp(user = users()))
                for (i = 0, size = sizeof(user); i < size; i++)
                {
                        add_user(user[i]);
                }
}

// 函数：获取所有ＧＭ
object *get_gm()
{
        Gms -= ({0});
        return copy(Gms);
}

// 函数：获取所有玩家
object *get_player()
{
        Players -= ({0});
        return copy(Players);
}

// 函数：获取ＧＭ数目
int sizeof_gm()
{
        Gms -= ({0});
        return sizeof(Gms);
}

// 函数：获取玩家数目
int sizeof_player()
{
        Players -= ({0});
        return sizeof(Players);
}

// 函数：增加ＧＭ用户
void add_gm(object who)
{
        if (objectp(who))
                Gms = Gms - ({who, 0}) + ({who});
}

// 函数：增加玩家用户
void add_player(object who)
{
        if (objectp(who))
                Players = Players - ({who, 0}) + ({who});
}

// 函数：减少ＧＭ用户
void sub_gm(object who)
{
        if (objectp(who))
                Gms -= ({who, 0});
}

// 函数：减少玩家用户
void sub_player(object who)
{
        if (objectp(who))
                Players -= ({who, 0});
}

// -------------------------------------------------------------

// 函数：获取所有初级玩家
object *get_level_a_user()
{
        LevelA -= ({0});
        return copy(LevelA);
}

// 函数：获取所有低级玩家
object *get_level_b_user()
{
        LevelB -= ({0});
        return copy(LevelB);
}

// 函数：获取所有其它玩家
object *get_level_c_user()
{
        LevelC -= ({0});
        return copy(LevelC);
}

// 函数：获取所有战争玩家
object *get_battle_user()
{
        Battle -= ({0});
        return copy(Battle);
}

// 函数：获取初级玩家数目
int sizeof_level_a_user()
{
        LevelA -= ({0});
        return sizeof(LevelA);
}

// 函数：获取低级玩家数目
int sizeof_level_b_user()
{
        LevelB -= ({0});
        return sizeof(LevelB);
}

// 函数：获取其它玩家数目
int sizeof_level_c_user()
{
        LevelC -= ({0});
        return sizeof(LevelC);
}

// 函数：获取其它战争玩家
int sizeof_battle_user()
{
        Battle -= ({0});
        return sizeof(Battle);
}

// 函数：增加初级玩家
void add_level_a_user(object who)
{
        if (objectp(who))
                LevelA = LevelA - ({who, 0}) + ({who});
}

// 函数：增加低级玩家
void add_level_b_user(object who)
{
        if (objectp(who))
                LevelB = LevelB - ({who, 0}) + ({who});
}

// 函数：增加其它玩家
void add_level_c_user(object who)
{
        if (objectp(who))
                LevelC = LevelC - ({who, 0}) + ({who});
}

// 函数：增加战争玩家
void add_battle_user(object who)
{
        if (objectp(who))
                Battle = Battle - ({who, 0}) + ({who});
}

// 函数：减少初级玩家
void sub_level_a_user(object who)
{
        if (objectp(who))
                LevelA -= ({who, 0});
}

// 函数：减少低级玩家
void sub_level_b_user(object who)
{
        if (objectp(who))
                LevelB -= ({who, 0});
}

// 函数：减少其它玩家
void sub_level_c_user(object who)
{
        if (objectp(who))
                LevelC -= ({who, 0});
}

// 函数：减少战争玩家
void sub_battle_user(object who)
{
        if (objectp(who))
                Battle -= ({who, 0});
}

// -------------------------------------------------------------

// 函数：获取所有用户
object *get_user()
{

        Users -= ({0});
        return copy(Users);
}

// 函数：获取用户数目
int sizeof_user()
{
        Users -= ({0});
        return sizeof(Users);
}

// 函数：增加用户对象
void add_user(object who)
{
        string whoid;

        if (objectp(who) && userp(who))
        {
                whoid = who->get_id();
                //  User2->add_userid(whoid);
                User2->add_usernumber(who->get_number());
                Users = Users - ({who, 0}) + ({who});
                if (!is_player(who))
                        add_gm(who);
                else
                        add_player(who);

                if (!MAP_D->is_inside_battle(get_z(who)))
                        switch (who->get_level()) // 设置玩家种类
                        {
                        case 0..9:
                                add_level_a_user(who);
                                break;
                        case 10..29:
                                add_level_b_user(who);
                                break;
                        default:
                                add_level_c_user(who);
                                break;
                        }
                else
                        add_battle_user(who);

                //              if( who->get_leader() ) TEAM_D->add_member( who->get_leader(), who );

                CHAT_D->add_chat(who);
                CHAT_D->add_rumor(who);
                FAMILY_D->add_family(who);
                FAMILY_D->add_city(who);
                FAMILY_D->add_org(who);
        }
}

// 函数：减少用户对象
void sub_user(object who)
{
        string whoid;
        if (objectp(who) && userp(who))
        {
                whoid = who->get_id();
                //   User2->sub_userid(whoid);
                User2->sub_usernumber(who->get_number());
                if (sizeof(Users))
                {
                        Users -= ({who, 0});
                }
                if (!is_player(who))
                        sub_gm(who);
                else
                        sub_player(who);

                if (!MAP_D->is_inside_battle(get_z(who)))
                        switch (who->get_level()) // 设置玩家种类
                        {
                        case 0..9:
                                sub_level_a_user(who);
                                break;
                        case 10..29:
                                sub_level_b_user(who);
                                break;
                        default:
                                sub_level_c_user(who);
                                break;
                        }
                else
                        sub_battle_user(who);

                //              if( who->get_leader() ) TEAM_D->remove_member( who->get_leader(), who );

                CHAT_D->sub_chat(who);
                CHAT_D->sub_rumor(who);
                FAMILY_D->sub_family(who);
                FAMILY_D->sub_city(who);
                FAMILY_D->sub_org(who);
        }
}

// -------------------------------------------------------------

// 函数：用户频道(系统频道)
void user_channel(string chat)
{
        Users -= ({0});
        if (sizeof(Users))
                send_user(Users, "%c%c%d%s", 0x43, 10, 0, chat);
}

// 函数：ＧＭ频道
void gm_channel(string chat)
{
        Gms -= ({0});
        if (sizeof(Gms))
                send_user(Gms, "%c%s", '>', chat);
}

// 函数：ＧＭ频道(谣言)
void rumor_gm_channel(string chat)
{
        Gms -= ({0});
        if (sizeof(Gms))
                send_user(Gms, "%c%c%d%s", 0x43, 2, 0, chat);
}

// -------------------------------------------------------------

// 函数：保存所有数据
void save_all_data()
{
        object *user, who, me, obj;
        mapping org;
        int time, time2, i, size, level, cash, saving;
        string id, order;

        if (arrayp(user = users()))
                for (i = 0, size = sizeof(user); i < size; i++)
                {
                        if (!objectp(who = user[i]))
                                continue;
                        if (!stringp(who->get_id()))
                                continue;
                        if (who->get_login_flag() < 2)
                                continue; // 以前注释(有过玩家重起时数据全被清０)

                        if (who->get_level() >= 55)
                        {
                                who->remove_equip(NECK_TYPE);
                                who->remove_equip(WEAPON_TYPE);
                                who->remove_equip(HEAD_TYPE);
                                who->remove_equip(ARMOR_TYPE);
                                who->remove_equip(WAIST_TYPE);
                                who->remove_equip(BOOTS_TYPE);
                                who->hide_title();
                        }

                        time = gone_time(who->get_login_time());
                        who->set_game_time(who->get_game_time() + time);
                        who->add_save("login_count", -1);
                        level = who->get_level();
                        cash = who->get_cash();
                        saving = who->get_savings();
                        if (!is_player(who))
                        {
                                level = 0;
                                cash = 0;
                                saving = 0;
                        }
                        me = who;
                        if (MAIN_D->get_host_type() == 4 || MAIN_D->get_host_type() == 0 || MAIN_D->get_host_type() == 6012 || MAIN_D->get_host_type() == 1000)
                        {
                                db_user_fee(me, sprintf(MAIN_D->get_php_ip() + ":80\n"
                                                                               "GET http://%s/logout.php?t=%s&u=%d&r=%d&h=%d\r\n",
                                                        MAIN_D->get_php_ip(), short_time_2(), me->get_acountid(), MAIN_D->get_region(), MAIN_D->get_host())); // 扣费！
                                obj = new ("/inh/user/list");
                                id = me->get_id();
                                obj->set_owner(me->get_real_id());
                                if (me->get_real_id() == id)
                                        order = "1";
                                else
                                        order = id[ < 1.. < 1];
                                obj->set_save_2(order + ".number", me->get_number());
                                obj->set_save_2(order + ".shape", me->get_armor_code());
                                obj->set_save_2(order + ".level", me->get_level());
                                obj->set_save_2(order + ".gold", cash + saving);
                                obj->set_save_2(sprintf("%s.armor", order), me->get_armor_code());
                                obj->set_save_2(sprintf("%s.armorc", order), me->get_armor_color_1());
                                obj->set_save_2(sprintf("%s.hair", order), me->get_hair());
                                obj->set_save_2(sprintf("%s.hairc", order), me->get_hair_color());
                                obj->set_save_2(sprintf("%s.back", order), me->get_back());
                                obj->set_save_2(sprintf("%s.backc", order), me->get_back_color());
                                obj->set_save_2(sprintf("%s.back2", order), me->get_back2());
                                obj->set_save_2(sprintf("%s.back2c", order), me->get_back2_color());
                                obj->set_save_2(sprintf("%s.weapon", order), me->get_weapon_code_2());
                                obj->set_save_2(sprintf("%s.weaponc", order), me->get_weapon_color());
                                obj->set_save_2(sprintf("%s.weaponc2", order), me->get_weapon_color_2());
                                obj->set_save_2(sprintf("%s.family", order), me->get_fam_name());
                                obj->save();
                                destruct(obj);
                        }
                        else
                                db_user_fee(who, sprintf(MAIN_D->get_php_ip() + ":80\n"
                                                                                "GET /xq2/fee.php?id=%s&start=%d&end=%d&time=%d&count=%d&region=%d&host=%d&shape=%d&level=%d&gold=%d&ip=%s\r\n",
                                                         rawurlencode(who->get_id()), who->get_login_time(), who->get_login_time() + time, time, who->get_feetime(), MAIN_D->get_region(), MAIN_D->get_host(), who->get_armor_code(), level, cash + saving, get_ip_name(who))); // 扣费！
                        time2 = who->get_feetime() + time;
                        if (time2 >= FEE_TIME)
                        {
                                who->set_fee_start(time());
                                who->set_feetime(time2 % FEE_TIME);
                        }
                        else
                                who->set_feetime(time2);

                        who->set_quit_time(time());
                        who->set_quit_ip(get_ip_name(who)); // 注意 quit 命令

                        who->save();
                        send_user(who, "%c%c", 0x49, 0xff);
                }

        CITY_QI->save();
        CITY_HAN->save();
        CITY_ZHAO->save();
        CITY_WEI->save();
        CITY_QIN->save();
        CITY_CHU->save();
        CITY_YAN->save();
        CITY_ZHOU->save();

        if (mapp(org = CITY_ZHOU->get_2("org")) && arrayp(user = values(org)))
                for (i = 0, size = sizeof(user); i < size; i++)
                        if (user[i])
                                user[i]->save();
}
