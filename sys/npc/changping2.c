
#include <ansi.h>
#include <city.h>

#define COMRADE_NPC_02 "/npc/war/changping2/0002" // 神机院主
#define COMRADE_NPC_03 "/npc/war/changping2/0003" // 武教头

#define COMRADE_NPC_95 "npc/88/1001" // 总管

#define COMRADE_NPC_10 "/npc/war/changping2/0010" // 混混
#define COMRADE_NPC_20 "/npc/war/changping2/0020" // 飞贼
#define COMRADE_NPC_30 "/npc/war/changping2/0030" // 强盗
#define COMRADE_NPC_15 "/npc/war/changping2/0015" // 狂徒
#define COMRADE_NPC_25 "/npc/war/changping2/0025" // 流氓
#define COMRADE_NPC_35 "/npc/war/changping2/0035" // 恶棍

#define COMRADE_TOWER "/npc/war/changping2/0080"  // 箭塔
#define COMRADE_TOWER2 "/npc/war/changping2/0085" // 打手

// 函数：生成二进制码
void SAVE_BINARY() {}

// 函数：五分钟公告(战争准备)
// void war_ready_notice(object map)
// {
//         string name1, name2;

//         name1 = map->get_war_attack();
//         name2 = map->get_war_defense();

//         CHAT_D->sys_channel(0, sprintf(HIR "Bang chủ chúng ta \"%s\" đã khiêu chiến, sau %d sẽ bắt đầu.", map->get_starttime() - time()));
//         CHAT_D->sys_channel(0, sprintf(HIR "\"%s\"đã khiêu chiến Bang chúng ta, sau %d giây sẽ bắt đầu..", map->get_starttime() - time()));
// }

// 函数：倒计时处理(战争开始)
void war_begin_count_down_notice(object map)
{
        object npc, npc2, npc3;
        string name1, name2, *xy;
        int p1, z1, x1, y1;
        int p2, z2, x2, y2;
        int i, size;

        name1 = map->get_war_attack();
        name2 = map->get_war_defense();

        // if (sec > 0)
        // {
        //         CHAT_D->sys_channel(0, sprintf(HIR "Sau %d giây Chiến Trường sẽ bắt đầu, mọi người nhanh chuẩn bị.", sec));
        //         CHAT_D->sys_channel(0, sprintf(HIR "Sau %d giây Chiến Trường sẽ bắt đầu, mọi người nhanh chuẩn bị", sec));
        // }
        // else
        // {
        //                log_file("test", sprintf("%s 战争开始\n", short_time()));
        map->cleanup_char_and_item(map); // 清除人物、物品

        // CHAT_D->sys_channel(0, sprintf(HIR "Cùng %s chiến đấu đã bắt đầu, mọi người mau về giúp một tay!", name2));
        // CHAT_D->sys_channel(0, sprintf(HIR "Mọi người mau gia nhập cùng %s quyết chiến!", name2));
        // CHAT_D->sys_channel(0, sprintf(HIR "Cùng %s chiến đấu đã bắt đầu, mọi người mau về giúp một tay!", name1));
        // CHAT_D->sys_channel(0, sprintf(HIR "Mọi người mau gia nhập cùng %s quyết chiến!", name1));

        z1 = map->get_id();

        p1 = "quest/changping2"->get_comrade_point(z1, 10);
        map->set_battle_x(10, p1 / 1000);
        map->set_battle_y(10, p1 % 1000);

        p1 = "quest/changping2"->get_comrade_point(z1, 11);
        map->set_battle_x(11, p1 / 1000);
        map->set_battle_y(11, p1 % 1000);

        p1 = "quest/changping2"->get_comrade_point(z1, 12);
        map->set_battle_x(12, p1 / 1000);
        map->set_battle_y(12, p1 % 1000);

        p1 = "quest/changping2"->get_comrade_point(z1, 15);
        map->set_battle_x(15, p1 / 1000);
        map->set_battle_y(15, p1 % 1000);

        p1 = "quest/changping2"->get_comrade_point(z1, 16);
        map->set_battle_x(16, p1 / 1000);
        map->set_battle_y(16, p1 % 1000);

        p1 = "quest/changping2"->get_comrade_point(z1, 17);
        map->set_battle_x(17, p1 / 1000);
        map->set_battle_y(17, p1 % 1000);

        map->make_virtual_line(); // 生成两条虚线
        map->make_battle_d();     // 生成坐标距离

        if ((p1 = "quest/changping2"->get_valid_manager_xy(z1, 1)) && (p2 = "quest/changping2"->get_valid_manager_xy(z1, 2)))
        {
                x1 = (p1 % 1000000) / 1000;
                y1 = p1 % 1000;

                z2 = z1;
                x2 = (p2 % 1000000) / 1000;
                y2 = p2 % 1000;

                // npc2 = new (COMRADE_NPC_95);
                // npc2->set_city_name(name1);
                // npc2->set_front(1);
                // npc2->add_to_scene(z1, x1, y1, 8); // 攻击方总管

                // npc3 = new (COMRADE_NPC_95);
                // npc3->set_city_name(name2);
                // npc3->set_front(2);
                // npc3->add_to_scene(z2, x2, y2, 4); // 防守方总管

                // npc2->set_manager(npc2);
                // npc3->set_manager(npc3);

                // map->set_manager(npc2);
                // map->set_manager_2(npc3);

                if ((p1 = "quest/changping2"->get_valid_manager_xy(z1, 11)))
                {
                        x1 = (p1 % 1000000) / 1000;
                        y1 = p1 % 1000;

                        npc = new (COMRADE_NPC_02);
                        npc->set_city_name(name1);
                        npc->set("warid", map->get("warid"));
                        npc->set_front(1);
                        npc->set_manager(npc2);
                        npc->add_to_scene(z1, x1, y1, 8); // 攻击方神机院主
                        npc = new (COMRADE_NPC_03);
                        npc->set_city_name(name1);
                        npc->set_front(1);
                        npc->set_manager(npc2);
                        npc->add_to_scene(z1, x1 + 2, y1 + 2, 8); // 攻击方神机院主
                }
                if ((p2 = "quest/changping2"->get_valid_manager_xy(z1, 12)))
                {
                        z2 = z1;
                        x2 = (p2 % 1000000) / 1000;
                        y2 = p2 % 1000;

                        npc = new (COMRADE_NPC_02);
                        npc->set_city_name(name2);
                        npc->set("warid", map->get("warid"));
                        npc->set_front(2);
                        npc->set_manager(npc3);
                        npc->add_to_scene(z2, x2, y2, 8); // 防守方神机院主
                        npc = new (COMRADE_NPC_03);
                        npc->set_city_name(name2);
                        npc->set_front(2);
                        npc->set_manager(npc3);
                        npc->add_to_scene(z2, x2 + 2, y2 + 2, 8); // 防守方神机院主
                }

                z1 = map->get_id();

                xy = "quest/changping2"->get_tower_array(z1, 0);
                for (i = 0, size = sizeof(xy); i < size; i++)
                {
                        if (sscanf(xy[i], "%d,%d", x1, y1) != 2)
                                continue;
                        if (get_block(z1, x1, y1) & IS_CHAR_BLOCK)
                                continue;

                        npc = new (COMRADE_TOWER2);
                        npc->set_char_picid(0202);
                        npc->set_level(0);
                        npc->set_city_name(name1);
                        npc->set("warid", map->get("warid"));
                        npc->set_front(1);
                        npc->set_manager(npc2);
                        npc->add_to_scene(z1, x1, y1, 8); // 攻击方箭塔
                        map->add_comrade(npc);
                }
                xy = "quest/changping2"->get_tower_array(z1, 1);
                for (i = 0, size = sizeof(xy); i < size; i++)
                {
                        if (sscanf(xy[i], "%d,%d", x1, y1) != 2)
                                continue;
                        if (get_block(z1, x1, y1) & IS_CHAR_BLOCK)
                                continue;

                        npc = new (COMRADE_TOWER);
                        npc->set_char_picid(9901);
                        npc->set_level(1);
                        npc->set_city_name(name1);
                        npc->set("warid", map->get("warid"));
                        npc->set_front(1);
                        npc->set_manager(npc2);
                        npc->add_to_scene(z1, x1, y1, 8); // 攻击方箭塔
                        map->add_tower(npc);
                }
                xy = "quest/changping2"->get_tower_array(z1, 2);
                for (i = 0, size = sizeof(xy); i < size; i++)
                {
                        if (sscanf(xy[i], "%d,%d", x1, y1) != 2)
                                continue;
                        if (get_block(z1, x1, y1) & IS_CHAR_BLOCK)
                                continue;

                        npc = new (COMRADE_TOWER);
                        npc->set_char_picid(9902);
                        npc->set_level(2);
                        npc->set_city_name(name1);
                        npc->set("warid", map->get("warid"));
                        npc->set_front(1);
                        npc->set_manager(npc2);
                        npc->add_to_scene(z1, x1, y1, 8); // 攻击方箭塔
                        map->add_tower(npc);
                }
                xy = "quest/changping2"->get_tower_array(z1, 3);
                for (i = 0, size = sizeof(xy); i < size; i++)
                {
                        if (sscanf(xy[i], "%d,%d", x1, y1) != 2)
                                continue;
                        if (get_block(z1, x1, y1) & IS_CHAR_BLOCK)
                                continue;

                        npc = new (COMRADE_TOWER);
                        npc->set_char_picid(9903);
                        npc->set_level(3);
                        npc->set_city_name(name1);
                        npc->set("warid", map->get("warid"));
                        npc->set_front(1);
                        npc->set_manager(npc2);
                        npc->add_to_scene(z1, x1, y1, 8); // 攻击方箭塔
                        map->add_tower(npc);
                }
                xy = "quest/changping2"->get_tower_array(z1, 4);
                for (i = 0, size = sizeof(xy); i < size; i++)
                {
                        if (sscanf(xy[i], "%d,%d", x1, y1) != 2)
                                continue;
                        if (get_block(z1, x1, y1) & IS_CHAR_BLOCK)
                                continue;

                        npc = new (COMRADE_TOWER);
                        npc->set_char_picid(9904);
                        npc->set_level(4);
                        npc->set_city_name(name1);
                        npc->set("warid", map->get("warid"));
                        npc->set_front(1);
                        npc->set_manager(npc2);
                        npc->add_to_scene(z1, x1, y1, 8); // 攻击方箭塔
                        map->add_tower(npc);
                }

                xy = "quest/changping2"->get_tower_array(z1, 5);
                for (i = 0, size = sizeof(xy); i < size; i++)
                {
                        if (sscanf(xy[i], "%d,%d", x1, y1) != 2)
                                continue;
                        if (get_block(z1, x1, y1) & IS_CHAR_BLOCK)
                                continue;

                        npc = new (COMRADE_TOWER2);
                        npc->set_char_picid(0053);
                        npc->set_level(0);
                        npc->set_city_name(name2);
                        npc->set("warid", map->get("warid"));
                        npc->set_front(2);
                        npc->set_manager(npc3);
                        npc->add_to_scene(z1, x1, y1, 4); // 防守方箭塔
                        map->add_comrade_2(npc);
                }
                xy = "quest/changping2"->get_tower_array(z1, 6);
                for (i = 0, size = sizeof(xy); i < size; i++)
                {
                        if (sscanf(xy[i], "%d,%d", x1, y1) != 2)
                                continue;
                        if (get_block(z1, x1, y1) & IS_CHAR_BLOCK)
                                continue;

                        npc = new (COMRADE_TOWER);
                        npc->set_char_picid(9901);
                        npc->set_level(1);
                        npc->set_city_name(name2);
                        npc->set("warid", map->get("warid"));
                        npc->set_front(2);
                        npc->set_manager(npc3);
                        npc->add_to_scene(z1, x1, y1, 4); // 防守方箭塔
                        map->add_tower_2(npc);
                }
                xy = "quest/changping2"->get_tower_array(z1, 7);
                for (i = 0, size = sizeof(xy); i < size; i++)
                {
                        if (sscanf(xy[i], "%d,%d", x1, y1) != 2)
                                continue;
                        if (get_block(z1, x1, y1) & IS_CHAR_BLOCK)
                                continue;

                        npc = new (COMRADE_TOWER);
                        npc->set_char_picid(9902);
                        npc->set_level(2);
                        npc->set_city_name(name2);
                        npc->set("warid", map->get("warid"));
                        npc->set_front(2);
                        npc->set_manager(npc3);
                        npc->add_to_scene(z1, x1, y1, 4); // 防守方箭塔
                        map->add_tower_2(npc);
                }
                xy = "quest/changping2"->get_tower_array(z1, 8);
                for (i = 0, size = sizeof(xy); i < size; i++)
                {
                        if (sscanf(xy[i], "%d,%d", x1, y1) != 2)
                                continue;
                        if (get_block(z1, x1, y1) & IS_CHAR_BLOCK)
                                continue;

                        npc = new (COMRADE_TOWER);
                        npc->set_char_picid(9903);
                        npc->set_level(3);
                        npc->set_city_name(name2);
                        npc->set("warid", map->get("warid"));
                        npc->set_front(2);
                        npc->set_manager(npc3);
                        npc->add_to_scene(z1, x1, y1, 4); // 防守方箭塔
                        map->add_tower_2(npc);
                }
                xy = "quest/changping2"->get_tower_array(z1, 9);
                for (i = 0, size = sizeof(xy); i < size; i++)
                {
                        if (sscanf(xy[i], "%d,%d", x1, y1) != 2)
                                continue;
                        if (get_block(z1, x1, y1) & IS_CHAR_BLOCK)
                                continue;

                        npc = new (COMRADE_TOWER);
                        npc->set_char_picid(9904);
                        npc->set_level(4);
                        npc->set_city_name(name2);
                        npc->set("warid", map->get("warid"));
                        npc->set_front(2);
                        npc->set_manager(npc3);
                        npc->add_to_scene(z1, x1, y1, 4); // 防守方箭塔
                        map->add_tower_2(npc);
                }
        }

        map->set_war(WAR_BEGIN);
        map->set_heart_sec(60); // 校正时钟    // 80 - 60 = 20 秒后出第一批怪
        // }
}

// 函数：放置战争ＮＰＣ(战争之中)
void add_comrade_to_battle(object map, int flag)
{
        object npc, npc2, npc3, orgnpc2, orgnpc3;
        string name1, name2;
        string *comrade_table, *comrade_table_2;
        int p, p2, z, x, y;
        int i, size;

        z = map->get_id();
        name1 = map->get_war_attack();
        name2 = map->get_war_defense();
        // orgnpc2 = CITY_ZHOU->get_2(sprintf("org.%s", name1));
        // orgnpc3 = CITY_ZHOU->get_2(sprintf("org.%s", name2));

        switch (flag)
        {
        default:
                comrade_table = ({COMRADE_NPC_10, COMRADE_NPC_10, COMRADE_NPC_10, COMRADE_NPC_20, COMRADE_NPC_30});
                comrade_table_2 = ({COMRADE_NPC_15, COMRADE_NPC_15, COMRADE_NPC_15, COMRADE_NPC_25, COMRADE_NPC_35});
                break;
        case 2:
                comrade_table = ({COMRADE_NPC_20, COMRADE_NPC_20, COMRADE_NPC_20, COMRADE_NPC_30, COMRADE_NPC_30});
                comrade_table_2 = ({COMRADE_NPC_25, COMRADE_NPC_25, COMRADE_NPC_25, COMRADE_NPC_35, COMRADE_NPC_35});
                break;
        case 3:
                comrade_table = ({COMRADE_NPC_10, COMRADE_NPC_10, COMRADE_NPC_10, COMRADE_NPC_20, COMRADE_NPC_30});
                comrade_table_2 = ({COMRADE_NPC_15, COMRADE_NPC_15, COMRADE_NPC_15, COMRADE_NPC_25, COMRADE_NPC_35});
                break;
        }

        npc2 = map->get_manager();
        npc3 = map->get_manager_2();

        for (i = 0, size = sizeof(comrade_table); i < size; i++)
        {
                if (map->sizeof_comrade_dbase() >= 100)
                        break;
                // if (orgnpc2->get_gold() == 0)
                // {
                //          CHAT_D->sys_channel( 0, HIR "Tài chính bang phái không đủ.");
                //         break;
                // }
                // orgnpc2->add_gold(-5);
                if (p = get_jumpin(z, 10))
                {
                        x = p / 1000;
                        y = p % 1000;

                        npc = new (comrade_table[i]);
                        npc->set_name(name1 + npc->get_name());
                        npc->set_city_name(name1);
                        npc->set("warid", map->get("warid"));
                        //  (me->get("warid") != who->get_2("changping.warid"))
                        npc->set_front(1);
                        npc->set_manager(npc2);
                        npc->add_to_scene(z, x, y, 3);
                        map->add_comrade(npc);
                }
                if (p = get_jumpin(z, 11))
                {
                        x = p / 1000;
                        y = p % 1000;

                        npc = new (comrade_table[i]);
                        npc->set_name(name1 + npc->get_name());
                        npc->set_city_name(name1);
                        npc->set("warid", map->get("warid"));
                        npc->set_front(1);
                        npc->set_manager(npc2);
                        npc->add_to_scene(z, x, y, 3);
                        map->add_comrade(npc);
                }
                if (p = get_jumpin(z, 12))
                {
                        x = p / 1000;
                        y = p % 1000;

                        npc = new (comrade_table[i]);
                        npc->set_name(name1 + npc->get_name());
                        npc->set_city_name(name1);
                        npc->set("warid", map->get("warid"));
                        npc->set_front(1);
                        npc->set_manager(npc2);
                        npc->add_to_scene(z, x, y, 3);
                        map->add_comrade(npc);
                }
        }

        for (i = 0, size = sizeof(comrade_table_2); i < size; i++)
        {
                if (map->sizeof_comrade_2_dbase() >= 100)
                        break;
                // if (orgnpc3->get_gold() == 0)
                // {
                //          CHAT_D->sys_channel( 0, HIR "Tài chính bang phái không đủ.");
                //         break;
                // }
                // orgnpc3->add_gold(-5);
                if (p = get_jumpin(z, 15))
                {
                        x = p / 1000;
                        y = p % 1000;

                        npc = new (comrade_table_2[i]);
                        npc->set_name(name2 + npc->get_name());
                        npc->set_city_name(name2);
                        npc->set("warid", map->get("warid"));
                        npc->set_front(2);
                        npc->set_manager(npc3);
                        npc->add_to_scene(z, x, y, 3);
                        map->add_comrade_2(npc);
                }
                if (p = get_jumpin(z, 16))
                {
                        x = p / 1000;
                        y = p % 1000;

                        npc = new (comrade_table_2[i]);
                        npc->set_name(name2 + npc->get_name());
                        npc->set_city_name(name2);
                        npc->set("warid", map->get("warid"));
                        npc->set_front(2);
                        npc->set_manager(npc3);
                        npc->add_to_scene(z, x, y, 3);
                        map->add_comrade_2(npc);
                }
                if (p = get_jumpin(z, 17))
                {
                        x = p / 1000;
                        y = p % 1000;

                        npc = new (comrade_table_2[i]);
                        npc->set_name(name2 + npc->get_name());
                        npc->set_city_name(name2);
                        npc->set("warid", map->get("warid"));
                        npc->set_front(2);
                        npc->set_manager(npc3);
                        npc->add_to_scene(z, x, y, 3);
                        map->add_comrade_2(npc);
                }
        }
}

// 函数：箭塔死亡奖励
void tower_win_bonus(object me, object who)
{
        object map, *char, npc;
        int id, i, size;

        if (objectp(map = get_map_object(get_z(me)))) // 获取战场对象
        {
                npc = me->get_manager();
                id = getoid(me);

                if (map->get_manager() == npc) // 攻击方
                {
                        char = map->get_user_dbase();
                        for (i = 0, size = sizeof(char); i < size; i++)
                                if (objectp(npc = char[i]))
                                        send_user(npc, "%c%c%d%w%w", 0x54, 21, id, -1, -1);
                }
                else if (map->get_manager_2() == npc) // 防守方
                {
                        char = map->get_user_2_dbase();
                        for (i = 0, size = sizeof(char); i < size; i++)
                                if (objectp(npc = char[i]))
                                        send_user(npc, "%c%c%d%w%w", 0x54, 21, id, -1, -1);
                }
        }
}

// 函数：NPC 死亡奖励
void comrade_win_bonus(object me, object who)
{
        object map, *char, npc;
        int id, i, size;

        if (objectp(map = get_map_object(get_z(me)))) // 获取战场对象
        {
                npc = me->get_manager();
                id = getoid(me);

                if (map->get_manager() == npc) // 攻击方
                {
                        char = map->get_user_dbase();
                        for (i = 0, size = sizeof(char); i < size; i++)
                                if (objectp(npc = char[i]))
                                        send_user(npc, "%c%c%d%w%w", 0x54, 22, id, -1, -1);
                }
                else if (map->get_manager_2() == npc) // 防守方
                {
                        char = map->get_user_2_dbase();
                        for (i = 0, size = sizeof(char); i < size; i++)
                                if (objectp(npc = char[i]))
                                        send_user(npc, "%c%c%d%w%w", 0x54, 22, id, -1, -1);
                }
        }
}
