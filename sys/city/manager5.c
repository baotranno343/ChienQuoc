
#include <ansi.h>
#include <map.h>
#include <city.h>
#include <skill.h>
#include <time.h>

#define DAY 86400

// 函数：生成二进制码
void SAVE_BINARY() {}

int is_war_time()
{
        mixed *mxTime;
        int iTime, day, hour;
        iTime = time();
        mxTime = localtime(iTime);
        day = mxTime[TIME_WDAY];
        hour = mxTime[TIME_HOUR];
        switch (day)
        {
        case 5:
        case 6:
                if (hour >= 17 && hour <= 18)
                        return 1;
                break;
        case 0:
                if (hour >= 11 && hour <= 12)
                        return 1;
                break;
        }
        return 0;
}

// 函数：发动战争
void do_war(object who, object me, string arg)
{
        object map, *char, npc, soldier, orgnpc;
        mapping org;
        string name1, name2, name, cmd, result;
        int id, z, x, y, p, i, size, time, number;

        id = getoid(me);

        name1 = who->get_org_name();
        name2 = me->get_org_name();
        if (stringp(name1) && stringp(name2) && name1 == name2) // 本帮帮众
        {
                if (gone_time(me->get_war()) > DAY) // 没有发生战争(开战超过一天)
                {
                        if (!arg || arg == "")
                        {
                                send_user(who, "%c%c%d%c%c%s", 0x95, 50, id, who->get_org_position(), 0, me->get_org_name());

                                if (who->get_org_position() > ORG_PRESBYTER // 本帮副帮主
                                    && mapp(org = CITY_ZHOU->get_2("org")) && arrayp(char = values(org)))
                                        for (i = 0, size = sizeof(char); i < size; i++)
                                                if (objectp(npc = char[i]))
                                                {
                                                        if (me == npc)
                                                                continue; // 不显示本帮

                                                        send_user(who, "%c%c%d%d%s", 0x95, 51, getoid(npc), npc->get_power(),
                                                                  sprintf("%-12s%s", npc->get_org_name(), npc->get_master_name()));
                                                }

                                return;
                        }
                        else if (who->get_org_position() > ORG_PRESBYTER) // 本帮副帮主
                        {
                                if (sscanf(arg, "@.%s", name) && objectp(npc = find_char(name)) && npc->is_org_officer() && npc != me)
                                {
                                        if (me->get_war())
                                        {
                                                npc = me->get_enemy_95();
                                                if (npc)
                                                {
                                                        send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Các ngươi đem cùng " + npc->get_org_name() + " triển khai một hồi quyết chiến, ngươi không thể tái hướng mặt khác bang hội khiêu chiến.\n" ESC "Rời khỏi\nCLOSE\n");
                                                        return;
                                                }
                                        }
                                        // if (time() < me->get_create_time() + 30 * 24 * 3600)
                                        // {
                                        //         send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Bổn bang thành lập chưa đủ 1 tháng, không thể khai chiến\n" ESC "Rời khỏi\nCLOSE\n");
                                        //         return;
                                        // }
                                        // if (time() < npc->get_create_time() + 30 * 24 * 3600)
                                        // {
                                        //         send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Bang Phái đối phương thành lập chưa đủ 1 tháng, không thể khai chiến\n" ESC "Rời khỏi\nCLOSE\n");
                                        //         return;
                                        // }
                                        // if (abs(me->get_grade() - npc->get_grade()) > 1)
                                        // {
                                        //         send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Cấp bậc 2 Bang chênh lệch không quá 1 bậc mới có thể khai chiến\n" ESC "Rời khỏi\nCLOSE\n");
                                        //         return;
                                        // }
                                        // if (!is_war_time())
                                        // {
                                        //         send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Hiện tại không phải thời gian khai chiến\n" ESC "Rời khỏi\nCLOSE\n");
                                        //         return;
                                        // }
                                        // if (who->get_strength() < 200)
                                        // {
                                        //         send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Thể lực không đủ 200, không thể khai chiến\n" ESC "Rời khỏi\nCLOSE\n");
                                        //         return;
                                        // }
                                        // if (who->get_cash() < 1000000)
                                        // {
                                        //         send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Tiền mặt không đủ 100 vạn, không thể khai chiến\n" ESC "Rời khỏi\nCLOSE\n");
                                        //         return;
                                        // }
                                        // if (me->get_stable() < 100)
                                        // {
                                        //         send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Bồn bang trước mắt Yên ổn rất thấp, không nên khai chiến\n" ESC "Rời khỏi\nCLOSE\n");
                                        //         return;
                                        // }
                                        // if (me->get_favour() < 50)
                                        // {
                                        //         send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Bồn bang trước mắt Nhân khí rất thấp, không nên khai chiến\n" ESC "Rời khỏi\nCLOSE\n");
                                        //         return;
                                        // }

                                        name = npc->get_org_name();
                                        if (npc->get_war())
                                        {
                                                send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "\"" + name + "\" đã khai chiến với bang phái khác");
                                                return;
                                        }
                                        if (!(z = find_map_flag(BATTLE_MAP_BEGIN, BATTLE_MAP_END, 0))) // 查找空白战场
                                        {
                                                send_user(who, "%c%s", '!', "Không thể hướng \"" + name + "\" khai chiến");
                                                return;
                                        }
                                        /*
                                                                                switch( get_z(npc) )    // 查找对应战场
                                                                                {
                                                                              case 10 : p = 910;  break;
                                                                              case 20 : p = 920;  break;
                                                                              case 30 : p = 930;  break;
                                                                              case 40 : p = 940;  break;
                                                                              case 50 : p = 950;  break;
                                                                              case 60 : p = 960;  break;
                                                                              case 70 : p = 970;  break;
                                                                              default : send_user( who, "%c%s", '!', "Không thể hướng \"" + name + "\" khai chiến" );
                                                                                        return;
                                                                                }
                                        */
                                        p = 910;
                                        /*
                                                                                if (MAIN_D->get_host()==1) p = 910;
                                                                                else
                                                                                {
                                                                                        send_user( who, "%c%s", '!', "Không thể hướng \"" + name + "\" khai chiến" );
                                                                                        return;
                                                                                }
                                        */
                                        who->set_strength(0);
                                        who->add_cash(-1000000);

                                        init_virtual_map(z, p); // 生成虚拟地图

                                        map = new (BATTLE); // 生成虚拟对象
                                        map->set_client_id(p);
                                        set_map_object(map, map->set_id(z));
                                        time = time() / 3600;
                                        if (time % 2 == 1)
                                                time += 3;
                                        else
                                                time += 2;
                                        me->set_war(time * 3600);
                                        npc->set_war(time * 3600); // 记录战争时间
                                        me->set_battle(z);
                                        npc->set_battle(z); // 记录战场编号
                                        me->set_enemy_95(npc);
                                        npc->set_enemy_95(me); // 记录敌方总管
                                        me->set_wood(0);
                                        npc->set_wood(0);
                                        me->set_level1(1);
                                        npc->set_level1(1);
                                        me->set_level2(1);
                                        npc->set_level2(1);
                                        me->set_level3(1);
                                        npc->set_level3(1);
                                        map->set_war_attack(name2);
                                        map->set_war_defense(name); // 记录战争双方
                                        map->set_heart_sec(0);      // 校正时钟
                                        map->set_war(WAR_READY);    // 记录战争准备
                                        map->set_starttime(1);
                                        /*
                                                                                if (MAIN_D->get_host()==1)
                                                                                {
                                                                                        me->set_war( time()+60 );  npc->set_war( time()+60 ); map->set_starttime( time()+60 );
                                                                                        if (MAIN_D->get_host_type()==1)
                                                                                        {
                                                                                                me->set_war( time()+3600 );  npc->set_war( time()+3600 );  map->set_starttime( time()+3600 );
                                                                                        }
                                                                                }
                                        */
                                        NPC_BATTLE_D->war_ready_notice(map);

                                        // 重新刷新窗口

                                        send_user(who, "%c%c%d%c%c%s", 0x95, 50, id, who->get_org_position(), 1, me->get_org_name());

                                        send_user(who, "%c%c%d%d%s", 0x95, 51, getoid(npc), npc->get_power(),
                                                  sprintf("%-12s%s", npc->get_org_name(), npc->get_master_name()));
                                        send_user(who, "%c%c%s", 0x95, 52, short_time(npc->get_create_time()));
                                }
                                else if (sscanf(arg, "?.%s", name) && objectp(npc = find_char(name)) && npc->is_org_officer() && npc != me)
                                {
                                        if (me->get_battle() > 0 && me->get_war() > 0 && me->get_battle() == npc->get_battle())
                                                ;
                                        else
                                        {
                                                send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Cùng đối phương Bang Phái không bị vây trạng thái khiêu chiến\n" ESC "Rời khỏi\nCLOSE\n");
                                                return;
                                        }
                                        if (time() < me->get_war())
                                        {
                                                send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Chiến tranh đã bắt đầu rồi, không thể bỏ dỡ\n" ESC "Rời khỏi\nCLOSE\n");
                                                return;
                                        }

                                        if (who->get_strength() < 100)
                                        {
                                                send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Thể lực không đủ 100, không thể bỏ dỡ chiến tranh\n" ESC "Rời khỏi\nCLOSE\n");
                                                return;
                                        }
                                        if (me->get_gold() < 300000)
                                        {
                                                send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Bổn bang trước mắt tài chính không đủ 30 vạn, không thể bỏ dở chiến tranh\n" ESC "Rời khỏi\nCLOSE\n");
                                                return;
                                        }

                                        z = me->get_battle();
                                        map = get_map_object(z);
                                        if (map)
                                                map->destruct_virtual_map(map, z);
                                        who->add_strength(-100);
                                        me->add_gold(-300000);
                                        me->set_war(0);
                                        npc->set_war(0);
                                        me->set_battle(0);
                                        npc->set_battle(0);
                                        me->set_enemy_95(0);
                                        npc->set_enemy_95(0);

                                        NPC_BATTLE_D->war_stop_notice(map);

                                        // 重新刷新窗口

                                        send_user(who, "%c%c%d%c%c%s", 0x95, 50, id, who->get_org_position(), 0, me->get_org_name());

                                        send_user(who, "%c%c%d%d%s", 0x95, 51, getoid(npc), npc->get_power(),
                                                  sprintf("%-12s%s", npc->get_org_name(), npc->get_master_name()));
                                        send_user(who, "%c%c%s", 0x95, 52, short_time(npc->get_create_time()));
                                }
                                else if (objectp(npc = find_char(arg)) && npc->is_org_officer() && npc != me)
                                {
                                        if (me->get_battle() > 0 && me->get_war() > 0 && me->get_battle() == npc->get_battle() && time() > me->get_war()) // 宣战但是还没有开打
                                        {
                                                cmd = sprintf("talk %x# war.?.%s\n", getoid(me), arg);
                                                send_user(who, "%c%s", ':', "Nếu huỷ bỏ\"" HIR + npc->get_org_name() + NOR "\" tuyên chiến. phải bồi thường 30 vạn và tiêu hao 100 điểm thể lực, xác nhận không ?\n" ESC "Xác nhận\n" + cmd + ESC "Rời khỏi\nCLOSE\n");
                                                return;
                                        }

                                        cmd = sprintf("talk %x# war.@.%s\n", getoid(me), arg);
                                        send_user(who, "%c%s", ':', "Với \"" HIR + npc->get_org_name() + NOR "\" khiêu chiến phải tiêu hao tài chính 100 vạn，giảm 50 điểm Nhân khí, giảm 100 điểm Yên ổn. Mỗi lần tuyên chiến tiêu hao 200 điểm thể lực \nBạn với\"" HIR + npc->get_org_name() + NOR "\" muốn khiêu chiến không?\n" ESC "Xác nhận\n" + cmd + ESC "Rời khỏi\nCLOSE\n");
                                        return;
                                }
                        }
                }
                else // 已经发生战争
                {
                        if (!arg || arg == "")
                        {
                                send_user(who, "%c%c%d%c%c%s", 0x95, 50, id, who->get_org_position(), 1, me->get_org_name());

                                if (objectp(npc = me->get_enemy_95()))
                                {
                                        send_user(who, "%c%c%d%d%s", 0x95, 51, getoid(npc), npc->get_power(),
                                                  sprintf("%-12s%s", npc->get_org_name(), npc->get_master_name()));
                                        send_user(who, "%c%c%s", 0x95, 52, short_time(npc->get_create_time()));
                                }

                                return;
                        }
                        else if (objectp(npc = me->get_enemy_95()) && arg == sprintf("%x#", getoid(npc)) && (z = me->get_battle()) && objectp(map = get_map_object(z)))
                        {
                                orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name1));
                                if (!objectp(orgnpc))
                                        return;
                                number = who->get_number();
                                if (time() - orgnpc->get_member_time() < 7 * 3600 * 24)
                                {
                                        send_user(who, "%c%s", '!', "Bạn gia nhập Bang chưa đủ 1 tuần, không thể tham gia chiến tranh");
                                        return;
                                }
                                if (name1 == map->get_war_attack())
                                {
                                        if (map->get_war() != WAR_BEGIN)
                                        {
                                                send_user(who, "%c%s", '!', "Hiện tại không thể vào Chiến Trường");
                                                return;
                                        }
                                        if (time() < who->get_save("org_die") + 120)
                                        {
                                                send_user(who, "%c%s", '!', sprintf("Bạn phải chờ đợi %d giây mới có thể vào Chiến trường", who->get_save("org_die") + 120 - time()));
                                                return;
                                        }
                                        who->delete_save("org_die");
                                        map->sub_user(who);
                                        if (map->sizeof_user_dbase() >= 20)
                                        {
                                                send_user(who, "%c%s", '!', "Hiện tại tham chiến nhân số đã đủ");
                                                return;
                                        }
                                        else if (p = get_jumpin(z, 1))
                                        {
                                                x = p / 1000;
                                                y = p % 1000;
                                                who->set_2("jiguan.z", get_z(who));
                                                who->set_2("jiguan.x", get_x(who));
                                                who->set_2("jiguan.y", get_y(who));
                                                soldier = who->get("soldier");
                                                if (soldier)
                                                        soldier->set_manager(map->get_manager());
                                                who->set_manager(map->get_manager());
                                                who->add_to_scene(z, x, y, 3, 40971, 0, 40971, 0);
                                                map->add_user(who);
                                                CHAR_CHAR_D->init_loop_perform(who);
                                                send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 9005, 1, OVER_BODY, PF_LOOP);

                                                map->show_to_user(who);
                                                map->show_to_scene(who);
                                                send_user(who, "%c%c", 0x95, 255);

                                                switch (who->get_level()) // 设置玩家种类
                                                {
                                                case 0..9:
                                                        USER_D->sub_level_a_user(who);
                                                        break;
                                                case 10..29:
                                                        USER_D->sub_level_b_user(who);
                                                        break;
                                                default:
                                                        USER_D->sub_level_c_user(who);
                                                        break;
                                                }
                                                USER_D->add_battle_user(who);
                                        }
                                }
                                else if (name1 == map->get_war_defense())
                                {
                                        if (map->get_war() != WAR_BEGIN)
                                        {
                                                send_user(who, "%c%s", '!', "Hiện tại không thể vào Chiến Trường");
                                                return;
                                        }
                                        map->sub_user_2(who);
                                        if (map->sizeof_user_2_dbase() >= 20)
                                        {
                                                send_user(who, "%c%s", '!', "Hiện tại tham chiến nhân số đã đủ");
                                                return;
                                        }
                                        if (time() < who->get_save("org_die") + 120)
                                        {
                                                send_user(who, "%c%s", '!', sprintf("Bạn phải chờ đợi %d giây mới có thể vào Chiến trường", who->get_save("org_die") + 120 - time()));
                                                return;
                                        }
                                        who->delete_save("org_die");
                                        if (p = get_jumpin(z, 2))
                                        {
                                                x = p / 1000;
                                                y = p % 1000;
                                                who->set_2("jiguan.z", get_z(who));
                                                who->set_2("jiguan.x", get_x(who));
                                                who->set_2("jiguan.y", get_y(who));
                                                soldier = who->get("soldier");
                                                if (soldier)
                                                        soldier->set_manager(map->get_manager_2());
                                                who->set_manager(map->get_manager_2());
                                                who->add_to_scene(z, x, y, 3, 40971, 0, 40971, 0);
                                                map->add_user_2(who);
                                                CHAR_CHAR_D->init_loop_perform(who);
                                                send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 9006, 1, OVER_BODY, PF_LOOP);

                                                map->show_to_user(who);
                                                map->show_to_scene(who);
                                                send_user(who, "%c%c", 0x95, 255);

                                                switch (who->get_level()) // 设置玩家种类
                                                {
                                                case 0..9:
                                                        USER_D->sub_level_a_user(who);
                                                        break;
                                                case 10..29:
                                                        USER_D->sub_level_b_user(who);
                                                        break;
                                                default:
                                                        USER_D->sub_level_c_user(who);
                                                        break;
                                                }
                                                USER_D->add_battle_user(who);
                                        }
                                }
                        }
                }
        }
}

// 函数：帮派信息
void do_org(object who, object me, string arg)
{
        object npc;
        string name1, name2;
        int id, time;

        id = getoid(me);

        name1 = who->get_org_name();
        name2 = me->get_org_name();
        time = me->get_gradetime();
        if (time > 0)
        {
                if (time < time())
                {
                        me->set_gradetime(0);
                        me->set_grade(me->get_grade() + 1);
                        FAMILY_D->org_channel(name2, 0, sprintf(HIR "Bang phái Quy mô tăng 1, hiện quy mô là %d.", me->get_grade()));
                }
        }

        if (stringp(name1) && stringp(name2) && name1 == name2)
        {
                send_user(who, "%c%c%d%d%d%s", 0x95, 70, getoid(me), me->get_member_contribute(who->get_number()), me->get_member_all_contribute(who->get_number()), sprintf("%-12s%s", name1, who->get_org_title()));
                send_user(who, "%c%c%c%c%c%d%d%d%d%d", 0x95, 71, me->get_grade(), me->get_science(), me->get_train(), me->get_power(), me->get_favour(), me->get_stable(), me->get_store(), me->get_gold());
                send_user(who, "%c%c%w%w", 0x95, 14, me->sizeof_member_dbase(), me->get_max_number());
        }
}
