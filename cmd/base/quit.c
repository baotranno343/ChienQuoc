
#include <ansi.h>
#include <equip.h>
#include <cmd.h>
#include <city.h>

#define LOGIN_LOG "loginfo.txt" // 连线记录日志

string get_name() { return "Thoát tuyến Tinh Linh"; }

// 函数:命令处理
int main(object me, string arg)
{
        int time, time2, level, cash, saving;
        object obj;
        string id, order;

        if (me->get_idle_time() > 200)
                "/sys/sys/id"->add_netdead_count(1);
        else if (me->get_idle_time() == 200)
                "/sys/sys/id"->add_kick_count(1);
        else
                "/sys/sys/id"->add_quit_count(1);
        me->set("quit", 1);

        if (me->get_level() >= 10)
        {
                /*	me->remove_equip(NECK_TYPE);
    me->remove_equip(WEAPON_TYPE);
        me->remove_equip(HEAD_TYPE);
    me->remove_equip(ARMOR_TYPE);
    me->remove_equip(WAIST_TYPE);
    me->remove_equip(BOOTS_TYPE);*/
                me->hide_title();
        }
        if (arrayp(me->get_team()))
                TEAM_CMD->main(me, sprintf("x %d", me->get_number()));

        time = gone_time(me->get_login_time());
        me->set_game_time(me->get_game_time() + time);

        //        db_user_fee( me, me->get_login_time(), time, me->get_feetime() );    // 扣费!
        level = me->get_level();
        cash = me->get_cash();
        saving = me->get_savings();
        if (!is_player(me))
        {
                level = 0;
                cash = 0;
                saving = 0;
        }
        if (MAIN_D->get_host_type() == 4 || MAIN_D->get_host_type() == 0 || MAIN_D->get_host_type() == 1000)
        {
                db_user_fee(me, sprintf(MAIN_D->get_php_ip() + ":80\n"
                                                               "GET http:/"
                                                               "/%s/logout2.php?t=%s&u=%d&r=%d&h=%d\r\n",
                                        MAIN_D->get_php_ip(), short_time_2(), me->get_acountid(), MAIN_D->get_region(), MAIN_D->get_host())); // 扣费!
                                                                                                                                              // log_file("php.dat", sprintf( MAIN_D->get_php_ip()+":80\n"
                                                                                                                                              //               	"GET http:/""/%s/logout.php?t=%s&u=%d&r=%d&h=%d\r\n",
                                                                                                                                              //                	MAIN_D->get_php_ip(), short_time_2(), me->get_acountid(), MAIN_D->get_region(), MAIN_D->get_host() ) );    // 扣费!
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
                db_user_fee(me, sprintf(MAIN_D->get_php_ip() + ":80\n"
                                                               "GET /xq2/fee.php?id=%s&start=%d&end=%d&time=%d&count=%d&region=%d&host=%d&shape=%d&level=%d&gold=%d&ip=%s\r\n",
                                        rawurlencode(me->get_id()), me->get_login_time(), me->get_login_time() + time, time, me->get_feetime(), MAIN_D->get_region(), MAIN_D->get_host(), me->get_armor_code(), level, cash + saving, get_ip_name(me))); // 扣费!
        if (me->get_perform("03191"))
                me->delete_perform("03191");

        time2 = me->get_feetime() + time;
        if (time2 >= FEE_TIME)
        {
                me->set_fee_start(time());
                me->set_feetime(time2 % FEE_TIME);
        }
        else
                me->set_feetime(time2);

        me->set_quit_time(time());
        me->set_quit_ip(get_ip_name(me));
        "/cmd/std/openbox"->before_quit(me);
        "/cmd/std/zgdict"->before_quit(me);

        tell_user(me, "Đang rời trò chơi……"); // 被调用，不要用 printf
        call_out("do_quit", 1, me);
        USER_D->sub_user(me);
        return 1;
}

private
int do_quit(object me)
{
        object who, *inv, *zombie, map;
        string name;
        int number, z, x, y, p, i, size;

        if (!objectp(me))
                return 1;

        me->add_save("login_count", -1);

        if (number = me->get_2("exchange.name")) // 关闭交易关联
        {
                if ((who = find_player(sprintf("%d", number))))
                {
                        who->delete_2("exchange");
                        send_user(who, "%c%c", 0x26, 0); // 关闭交易窗口
                }
        }

        USER_SLAVE_D->save_all_slave(me); // 召唤兽保留１分钟

        /*      number = me->get_number();
        z = get_z(me);  x = get_x(me);  y = get_y(me);
        inv = all_inventory(me, 0, 0);
        for( i = 0, size = sizeof(inv); i < size; i ++ )
                if(     inv[i] && inv[i]->is_thief_item()    // 特殊任务物品
                &&    ( p = get_valid_xy( z, x + random(3) - 1, y + random(3) - 1, IS_ITEM_BLOCK ) ) )
        {
                inv[i]->set("task", number);
                inv[i]->add_to_scene(z, p / 1000, p % 1000);
        }       */

        record_login(me, me->get_id(), 0);

        write_user(me, ECHO "Hoan nghênh lần sau lại đến !");

        USER_D->gm_channel(sprintf(HIR " %s : %s ( %d ) thoát khỏi trò chơi.", get_name(), me->get_name(), me->get_number()));
        log_file(LOGIN_LOG, sprintf("%s %s %d %s - - %s %d %d\n", me->get_id(), me->get_name(), me->get_number(), get_ip_name(me), short_time(), me->get_cash() + me->get_savings(), me->get_exp()));

        //        me->send_to_friend(0);
        me->leave_friends();
        me->prepare_save();
        db_user_quit(me, me->get_id());

        if ((name = me->get_org_name()) && name != "" // 更新帮派信息
            && objectp(who = CITY_ZHOU->get_2(sprintf("org.%s", name))) && (number = me->get_number()) && who->get_member_id(number))
        {
                who->set_member_level(number, me->get_level());
                who->set_member_family(number, me->get_fam_name());
                who->set_member_quit(number, time()); // 设置帮众离线
        }
        z = get_z(me);
        if (MAP_D->is_inside_battle(z))
        {
                if (objectp(map = get_map_object(z)))
                {
                        map->sub_user(me);
                        map->sub_user_2(me);
                }
        }
        // changping2
        if (objectp(map = get_map_object(z)) && map->is_changping2())
        {
                map->sub_user(me);
                map->sub_user_2(me);
        }
        if (me->get_perform("05016#"))
        {
                me->set_perform("05016#", 0);
                me->set_perform("05016", 0);
        }
        if (me->get_2("changping")) //长平之战报名的，取消报名
        {
                "npc/88/8800"->delete_sign_up(me);
        }
        "sys/party/mingren"->check_mingren_downline(me);
        // 从场景中移除
        if (file_exist(sprintf("data/infoitem/%d.dat", me->get_number())))
                rm(sprintf("data/infoitem/%d.dat", me->get_number()));

        if (file_exist(sprintf("isLogin/%s.dat", me->get_real_id())))
                rm(sprintf("isLogin/%s.dat", me->get_real_id()));

        // if (file_exist(sprintf("isNumber/%d.dat", me->get_number())))
        //         rm(sprintf("isNumber/%d.dat", me->get_number()));

        me->remove_from_scene();
        send_user(me, "%c%d", 0x58, getoid(me));
        me->before_destruct();
        me->destruct_all_pet();
        destruct(me);

        return 1;
}
