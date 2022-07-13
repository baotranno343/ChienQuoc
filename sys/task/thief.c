
#include <ansi.h>
#include <music.h>
#include <task.h>

#define THIEF "/npc/task/8150"
#define THIEF_2 "/npc/task/8151"
#define TIME_LIMIT 180
#define TASK_TIME_LIMIT 1800
void send_task_list(object who);
void give_bonus(object who);

// 函数:生成二进制码
void SAVE_BINARY() {}

// 函数:开始任务
void do_task_start(object who, object me)
{
        object map, npc, item;
        string *member, name, cWord;
        int level, i, size;
        int z, x, y, p;

        if (who->get_quest("thief.flag") && who->get_quest("thief.bonus") == 1)
        {
                send_user(who, "%c%s", ':', sprintf(" %s :\n Biểu hiện của ngươi khá xuất sắc, như vậy quan phủ chúng ta có thể bớt đi rất nhiều công sức . đây là thù lao của ngươi, hãy cầm lấy đi!\n" ESC "Hoàn thành nhiệm vụ.\n" + sprintf("talk %x# bonus_thief\n", getoid(me)) + ESC "Rời khỏi.\nCLOSE\n", me->get_name()));
                return;
        }
        else if (i = who->get_quest("thief.flag"))
        {
                if (i != 1)
                {
                        name = who->get_quest("thief.thief");
                        if (stringp(name) && objectp(item = present(name, who, 1, MAX_CARRY)))
                        {
                                if (i == 3 || ((i == 2 || i == 4) && item->is_thief_item()))
                                {
                                        who->set_quest("thief.bonus", i);
                                        send_user(who, "%c%s", ':', sprintf(" %s :\n Biểu hiện của ngươi khá xuất sắc, như vậy quan phủ chúng ta có thể bớt đi rất nhiều công sức . đây là thù lao của ngươi, hãy cầm lấy đi!\n" ESC "Hoàn thành nhiệm vụ.\n" + sprintf("talk %x# bonus_thief\n", getoid(me)) + ESC "Rời khỏi.\nCLOSE\n", me->get_name()));
                                        return;
                                }
                        }
                }
                send_user(who, "%c%s", ':', me->get_name() + ":\n    事情进行得怎么样了?这点小麻烦应该不会难倒你吧?\n" ESC "Rời khỏi\nCLOSE\n");
                return;
        }

        if ((level = who->get_level()) < 10)
        {
                send_user(who, "%c%s", ':', me->get_name() + ":\n    Đạt cấp 10 rồi lại đến tìm ta\n" ESC "Rời khỏi\nCLOSE\n");
                return;
        }

        if (gone_time(who->get_quest("thief.atime")) < TIME_LIMIT)
        {
                send_user(who, "%c%s", ':', me->get_name() + ":\n    Ngươi cứ đi dạo đi, chút nữa lại đến (chờ " HIR "3 phút" NOR " rồi lại đến nhận nhiệm vụ)\n" ESC "Rời khỏi\nCLOSE\n");
                return;
        }
        who->set_quest("thief.atime", time());
        //   who->set_save("cambayquest", 1);
        switch (random(4))
        {
        case 0:
                z = ({1, 2, 3, 162, 80})[random(5)];
                if (!(p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
                        return;
                x = (p % 1000000) / 1000;
                y = p % 1000;
                if (!objectp(map = get_map_object(z)) || !map->is_scene())
                        return;
                name = NPC_NAME_D->get_thief_name();
                cWord = sprintf(" %s :\n Thư của Lão Thôn Trưởng của Tân Thủ Thôn, nói rằng tối qua có tên trộm %s đến dòm ngó thôn trang của họ . mặc dù không mất gì quý giá và quan trọng , nhưng không thể dễ dàng bỏ qua cho tên trộm cướp này .\n Theo thông tin của thôn trưởng, %s xuất hiện ở gần %s ( %d , %d ), ngươi chỉ cần cho %s một bài học là được rồi.", me->get_name(), name, name, map->get_name(), x, y, name);
                who->set("thief.name", name);
                who->set("thief.type", 1);
                who->set("thief.x", x);
                who->set("thief.y", y);
                who->set("thief.z", z);
                break;
        case 1:
                z = ({1, 2, 3, 162, 80})[random(5)];
                if (!(p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
                        return;
                x = (p % 1000000) / 1000;
                y = p % 1000;
                if (!objectp(map = get_map_object(z)) || !map->is_scene())
                        return;
                name = "/item/98/985" + random(10);
                if (!objectp(item = find_object(name)) && !objectp(item = load_object(name)))
                        return;
                cWord = sprintf(me->get_name() + ":\n    Ngày hôm qua, Bát Cô tâm sư với ta nói khổ, bà đã lỡ đánh mất thứ quan trọng\n    Lần này Bát Cô bị mất một cái %s， theo nàng miêu tả vật đó hẳn đánh rơi ở %s (%d，%d) vùng gần đó\n    Như thế nào ? %s có muốn giúp ta tìm lại không ?", item->get_name(), map->get_name(), x, y, NPC_RANK_D->get_respect_2(who));
                who->set("thief.name", name);
                who->set("thief.type", 2);
                who->set("thief.x", x);
                who->set("thief.y", y);
                who->set("thief.z", z);
                break;
        case 2:
                name = THIEF_FILE->get_buy_name(who);
                cWord = sprintf(" %s :\n %s gặp được ngươi thì tốt .\n Ta vốn muốn mua %s , nhưng lại vì bận bịu việc công vụ mà không có lúc nào ngơi tay ngơi chân được, ngươi có thể giúp ta việc này chứ?", me->get_name(), who->get_name(), name);
                who->set("thief.file", name);
                who->set("thief.type", 3);
                break;
        case 3:
                z = ({1, 2, 3, 162, 80})[random(5)];
                if (!(p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
                        return;
                x = (p % 1000000) / 1000;
                y = p % 1000;
                if (!objectp(map = get_map_object(z)) || !map->is_scene())
                        return;
                name = NPC_NAME_D->get_thief_name();
                cWord = sprintf(me->get_name() + ":\n    Kẻ trộm %s đêm qua lại xuất hiện ！ Hắn đã cướp sạch những thứ quý giá！Theo lời cấp dưới hồi báo đã thấy %s ở %s (%d，%d) vùng phụ cận\n    Nếu %s có thể đoạt lại vật phẩm mất trộm, ta sẽ trọng thưởng", name, name, map->get_name(), x, y, NPC_RANK_D->get_respect_2(who));
                who->set("thief.name", name);
                who->set("thief.type", 4);
                who->set("thief.x", x);
                who->set("thief.y", y);
                who->set("thief.z", z);
                break;
        }
        send_user(who, "%c%s", ':', cWord + "\n" + ESC + sprintf("Nhận\ntalk %x# accept_thief\n", getoid(me)) + ESC "Rời khỏi\nCLOSE\n");
}

void accept_task(object who, object me)
{
        object map, npc, item;
        string *member, name;
        int level, i, size;
        int z, x, y, p, iType, x1, y1;

        if (who->get_quest("thief.flag") && (TASK_TIME_LIMIT - gone_time(who->get_quest("thief.time")) > 0))
        {
                send_user(who, "%c%s", '!', "Hãy hoàn thành nhiệm vụ trước mắt đi");
                return;
        }

        if ((level = who->get_level()) < 10)
        {
                send_user(who, "%c%s", '!', "Cấp 10 mới có thể nhận nhiệm vụ");
                return;
        }
        iType = who->get("thief.type");
        if (!iType)
                return;
        who->delete ("thief.type");
        who->delete_quest("thief.atime");
        who->delete_quest("thief.bonus");
        // who->set_save("cambayquest", 1);
        switch (iType)
        {
        case 1:
                x = who->get("thief.x");
                y = who->get("thief.y");
                z = who->get("thief.z");
                name = who->get("thief.name");
                if (!stringp(name))
                        return;
                if (!objectp(map = get_map_object(z)) || !map->is_scene())
                        return;
                for (i = 0; i < 100; i++)
                {
                        if (p = get_valid_xy(z, abs(x + random(10) - 5), abs(y + random(10) - 5), IS_CHAR_BLOCK))
                        {
                                x1 = p / 1000;
                                y1 = p % 1000;
                                break;
                        }
                }
                if (!x1 || !y1)
                        return;
                npc = new (THIEF);
                npc->set_name("Tiểu Thâu" + name);
                NPC_ENERGY_D->init_level(npc, level - 5);
                npc->set_max_hp(who->get_max_hp() * 2);
                npc->set_max_mp(who->get_max_mp());
                npc->set_ap(who->get_dp_0() + 5 + random(10));
                npc->set_dp(who->get_ap_0() - random(15));
                npc->set_cp(who->get_pp_0() + 5 + random(15));
                npc->set_pp(who->get_cp_0() - random(15));
                npc->set_sp(who->get_sp() - random(10));
                npc->add_to_scene(z, x1, y1, 3);
                member = ({sprintf("%d", who->get_number())});
                npc->set("user", member);
                map->add_reset(npc); // 加入复位列表

                send_user(who, "%c%s", '!', sprintf("Đi" HIY " %s (%d,%d) " NOR " giáo huấn" HIY " %s " NOR ".", map->get_name(), x, y, npc->get_name()));

                if (who->get_quest("thief.flag"))
                        who->delete_quest("thief.count");
                who->set_quest("thief.flag", 1);
                who->set_quest("thief.time", time());
                who->set_quest("thief.thief", sprintf("%x#", getoid(npc)));
                who->set_quest("thief.z", z);
                who->set_quest("thief.x", x);
                who->set_quest("thief.y", y);

                npc->set("task", who->get_number());

                break;

        case 2:
                name = who->get("thief.name");
                x = who->get("thief.x");
                y = who->get("thief.y");
                z = who->get("thief.z");
                if (!objectp(map = get_map_object(z)) || !map->is_scene())
                        return;
                if (!stringp(name) || (!find_object(name) && !load_object(name)))
                        return;
                item = new (name);
                for (i = 0; i < 100; i++)
                {
                        if (p = get_valid_xy(z, abs(x + random(10) - 5), abs(y + random(10) - 5), IS_ITEM_BLOCK))
                        {
                                x1 = p / 1000;
                                y1 = p % 1000;
                                break;
                        }
                }
                if (!x1 || !y1)
                        return;
                item->add_to_scene(z, x1, y1);
                item->set_user_id(who->get_id());
                member = ({sprintf("%d", who->get_number())});
                item->set("user", member);
                map->add_reset(item); // 加入复位列表

                send_user(who, "%c%s", '!', sprintf("Đi" HIY " %s (%d,%d) " NOR " tìm về" HIY " %s " NOR ".", map->get_name(), x, y, item->get_name()));

                if (who->get_quest("thief.flag"))
                        who->delete_quest("thief.count");
                who->set_quest("thief.flag", 2);
                who->set_quest("thief.time", time());
                who->set_quest("thief.thief", item->get_name());
                who->set_quest("thief.z", z);
                who->set_quest("thief.x", x);
                who->set_quest("thief.y", y);
                who->set_quest("thief.unit", item->get_unit());
                item->set("birthday", time());
                item->set("task", who->get_number());
                break;
        case 3:
                name = who->get("thief.file");
                if (!stringp(name))
                        return;
                send_user(who, "%c%s", '!', sprintf("Tìm " HIY " %s " NOR " về lại cho Vương Bộ Đầu.", name));
                if (who->get_quest("thief.flag"))
                        who->delete_quest("thief.count");
                who->set_quest("thief.flag", 3);
                who->set_quest("thief.time", time());
                who->set_quest("thief.thief", name);
                break;
        case 4:
                x = who->get("thief.x");
                y = who->get("thief.y");
                z = who->get("thief.z");
                name = who->get("thief.name");
                if (!stringp(name))
                        return;
                if (!objectp(map = get_map_object(z)) || !map->is_scene())
                        return;
                for (i = 0; i < 100; i++)
                {
                        if (p = get_valid_xy(z, abs(x + random(10) - 5), abs(y + random(10) - 5), IS_CHAR_BLOCK))
                        {
                                x1 = p / 1000;
                                y1 = p % 1000;
                                break;
                        }
                }
                if (!x1 || !y1)
                        return;
                npc = new (THIEF_2);
                npc->set_name("Thiết Tặc " + name);
                NPC_ENERGY_D->init_level(npc, level - 5);
                npc->set_max_hp(who->get_max_hp() * 2);
                npc->set_max_mp(who->get_max_mp());
                npc->set_ap(who->get_dp_0() + 5 + random(10));
                npc->set_dp(who->get_ap_0() - random(15));
                npc->set_cp(who->get_pp_0() + 5 + random(15));
                npc->set_pp(who->get_cp_0() - random(15));
                npc->set_sp(who->get_sp() - random(10));

                npc->add_to_scene(z, x1, y1, 3);
                member = ({sprintf("%d", who->get_number())});
                npc->set("user", member);
                map->add_reset(npc); // 加入复位列表
                send_user(who, "%c%s", '!', sprintf("Đi" HIY " %s (%d,%d) " NOR " giáo huấn" HIY " %s " NOR "， tìm lại vật phẩm bị mất trộm", map->get_name(), x, y, npc->get_name()));

                if (who->get_quest("thief.flag"))
                        who->delete_quest("thief.count");
                who->set_quest("thief.flag", 4);
                who->set_quest("thief.time", time());
                who->set_quest("thief.thief", sprintf("%x#", getoid(npc)));
                who->set_quest("thief.z", z);
                who->set_quest("thief.x", x);
                who->set_quest("thief.y", y);
                npc->set("task", who->get_number());
                break;
        }
        send_task_list(who);
}

// 函数:取消任务
void do_task_cancel(object who, object me)
{
        object map, *reset, npc;
        string thief;
        int time, id, i, size;

        if (!who->get_quest("thief.flag")) // 失窃任务
        {
                return;
        }

        //        if( ( time = gone_time( who->get_quest("thief.time") ) ) < 180 )    // ３分钟
        //        {
        //                send_user( who, "%c%s", '!', sprintf( "还有 %d 秒才能取消失窃任务.", 180 - time ) );
        //                return;
        //        }

        switch (who->get_quest("thief.flag"))
        {
        default:
                break;

        case 1:
                send_user(who, "%c%s", ':', sprintf("%s:\nChúng ta đã tìm được %s， không cần làm phiền ngươi nữa\n", me->get_name(), who->get_quest("thief.thief")));

                if (objectp(map = get_map_object(who->get_quest("thief.z"))) && arrayp(reset = map->get_reset_dbase()))
                {
                        id = who->get_number();
                        for (i = 0, size = sizeof(reset); i < size; i++)
                                if (reset[i] && reset[i]->is_thief_item() && reset[i]->get("task") == id)
                                {
                                        reset[i]->set("birthday", 0);
                                        reset[i]->reset();
                                        break;
                                }
                }
                break;

        case 2:
                if (stringp(thief = who->get_quest("thief.thief")) && (npc = find_char(thief)) && npc->is_thief())
                {
                        send_user(who, "%c%s", ':', sprintf("%s:\nChúng ta đã giáo huấn %s, không cần làm phiền ngươi nữa\n", me->get_name(), npc->get_name()));

                        npc->remove_from_scene();
                        destruct(npc);
                }
                break;

        case 3:
                if (stringp(thief = who->get_quest("thief.thief")) && (npc = find_char(thief)) && npc->is_thief())
                {
                        send_user(who, "%c%s", ':', sprintf("%s:\nChúng ta đã giáo huấn %s, không cần làm phiền ngươi nữa\n", me->get_name(), npc->get_name()));

                        npc->remove_from_scene();
                        destruct(npc);
                }
                break;

        case 4:
                send_user(who, "%c%s", ':', sprintf("%s:\nChúng ta đã tìm được %s, không cần làm phiền ngươi\n", me->get_name(), who->get_quest("thief.thief")));

                if (objectp(map = get_map_object(who->get_quest("thief.z"))) && arrayp(reset = map->get_reset_dbase()))
                {
                        id = who->get_number();
                        for (i = 0, size = sizeof(reset); i < size; i++)
                                if (reset[i] && reset[i]->is_thief_item() && reset[i]->get("task") == id)
                                {
                                        reset[i]->set("birthday", 0);
                                        reset[i]->reset();
                                        break;
                                }
                }
                break;

        case 5:
                send_user(who, "%c%s", ':', sprintf("%s:\nChúng ta đã tìm được %s, không cần làm phiền ngươi\n", me->get_name(), who->get_quest("thief.thief")));

                break;
        }

        who->add_hp(-who->get_hp() / 2); // 气血、法力减少一半
                                         //      who->add_mp( - who->get_mp() / 2 );

        who->delete_quest("thief.flag");
        who->delete_quest("thief.time");
        who->delete_quest("thief.thief");
        who->delete_quest("thief.z");
        who->delete_quest("thief.x");
        who->delete_quest("thief.y");
        who->delete_quest("thief.count");
        //  who->delete_save("cambayquest");
        //      send_user( who, "%c%s", ':', sprintf( "%s:\n唉，这样的小事都做不好，将来如何承担大任?！\n", me->get_name() ) );
        write_user(who, ECHO "%s nói: “Ây, việt nhỏ như thế mà làm chưa xong, việc lớn thì phải làm thế nào ！”", me->get_name());
}

// 函数:给予奖励
void give_bonus(object who)
{
        int count, gold, exp, pot, knb, iKind, i;
        string name;
        object item;

        iKind = who->get_quest("thief.flag");
        if (iKind == 0)
                return;
        if (!(i = who->get_quest("thief.bonus")))
                return;

        if (i != 1)
        {
                name = who->get_quest("thief.thief");
                if (!stringp(name) || !objectp(item = present(name, who, 1, MAX_CARRY)))
                        return;
                if ((i == 2 || i == 4) && !item->is_thief_item())
                        return;
                item->remove_from_user();
                destruct(item);
        }

        if ((count = who->add_quest("thief.count", 1)) >= 10)
                who->delete_quest("thief.count");
        count--;
        send_user(who, "%c%c%c%w%w%w%s", 0x51, 1, 4, TID_THIEF, iKind, 0, "");
        send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_THIEF, iKind, "");
        send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_THIEF, "");

        who->delete_quest("thief.flag"); // 完成任务，删除标志
        who->delete_quest("thief.time");
        who->delete_quest("thief.thief");
        who->delete_quest("thief.z");
        who->delete_quest("thief.x");
        who->delete_quest("thief.y");
        who->delete_quest("thief.bonus");
        who->delete_quest("thief.task");
        // who->delete_save("cambayquest");
        gold = 2000 + count * 500 * 110 / (who->get_level() + 100);
        gold = gold * who->get_online_rate() / 100;
        who->add_cash(gold);
        who->add_gold_log("task", gold);
        who->log_money("王捕头赚钱", gold);
        exp = count * 50 + 50;
        exp = exp * who->get_online_rate() / 100;
        who->add_exp(exp);
        pot = count * 5 + 5;
        pot = pot * who->get_online_rate() / 100;
        who->add_potential(pot);
        "sys/sys/test_db"->add_yuanbao(who, 2);

        "/sys/sys/count"->add_income("thief", gold);
        "/sys/sys/count"->add_task("王捕头赚钱", 1);
        who->add_log("$thief", gold);
        who->add_log("&thief", exp);
        who->add_log("*thief", pot);
        who->add_log("#thief", 1);

        send_user(who, "%c%w", 0x0d, MUSIC_TASK);
        write_user(who, ECHO "Ngươi hòan hành nhiệm vụ Vương Bộ Đầu ( lượt thứ %d ), Ngân lượng %+d , Kinh nghiệm %+d , Tiềm năng %+d , Ngân Bảo +2.", count + 1, gold, exp, pot);
}

void task_giveup(object who, int iKind)
{
        object map, *reset, npc;
        string thief, *member;
        int time, id, i, size;
        if (!who->get_quest("thief.flag")) // 失窃任务
        {
                return;
        }
        if (iKind != who->get_quest("thief.flag"))
                return;
        if (gone_time(who->get_quest("thief.time")) < TIME_LIMIT)
        {
                // item = who->get_equip(HAND_TYPE);
                // if (item && item->get_item_number() == 10001078)
                // {
                //         send_user(who, "%c%c%s", 0x59, 1, sprintf("Ngươi sử dụng Phù để trừ khoảng cách thời gian nhiệm vụ của ngươi???\n" ESC "%c\n" ESC "use %x# criminal2\n", 1, getoid(item)));
                //         return;
                // }
                send_user(who, "%c%s", '!', "Hãy đợi 3 phút,Sau đó huỷ bỏ nhiệm vụ 1 lần nữa");
                return;
        }
        switch (iKind)
        {
        default:
                break;
        case 1:
        case 4:
                if (stringp(thief = who->get_quest("thief.thief")) && (npc = find_char(thief)) && npc->is_thief())
                {
                        member = npc->get("user");
                        thief = sprintf("%d", who->get_number());
                        member -= ({thief});
                        if (sizeof(member) == 0)
                        {
                                npc->remove_from_scene();
                                destruct(npc);
                        }
                }
                break;
        case 2:

                if (objectp(map = get_map_object(who->get_quest("thief.z"))) && arrayp(reset = map->get_reset_dbase()))
                {
                        id = who->get_number();
                        for (i = 0, size = sizeof(reset); i < size; i++)
                                if (reset[i] && reset[i]->is_thief_item() && reset[i]->get("task") == id)
                                {
                                        reset[i]->set("birthday", 0);
                                        reset[i]->reset();
                                        break;
                                }
                }
                break;
        }

        send_user(who, "%c%c%c%w%w%w%s", 0x51, 1, 4, TID_THIEF, iKind, 0, "");
        send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_THIEF, iKind, "");
        send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_THIEF, "");

        who->delete_quest("thief.bonus");
        who->delete_quest("thief.flag");
        who->delete_quest("thief.time");
        who->delete_quest("thief.thief");
        who->delete_quest("thief.z");
        who->delete_quest("thief.x");
        who->delete_quest("thief.y");
        who->delete_quest("thief.count");
        //   who->delete_save("cambayquest");
}

void send_task_list(object who)
{
        int iFlag;
        string name, id;
        object npc;
        if (iFlag = who->get_quest("thief.flag"))
        {

                switch (iFlag)
                {
                case 1: // 2. 失窃任务(人物)
                        if (who->get_quest("thief.bonus"))
                        {
                                send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_THIEF, "Nhiệm vụ Vương Bộ Đầu");
                                send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_THIEF, 1, "Giáo huấn Tiểu Thâu(Đã hoàn thành)");
                        }
                        else if (stringp(id = who->get_quest("thief.thief")) && (npc = find_char(id)) && npc->is_thief()) // 30 分钟
                        {
                                send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_THIEF, "Nhiệm vụ Vương Bộ Đầu");

                                send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_THIEF, 1, "Giáo huấn Tiểu Thâu");
                        }
                        else
                        {
                                send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_THIEF, "Nhiệm vụ Vương Bộ Đầu");
                                send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_THIEF, 1, "Giáo huấn Tiểu Thâu(Thất bại)");
                        }
                        break;

                case 2: // 1. 失窃任务(物品)
                        //		                if( ( iFlag = 1800 - gone_time( who->get_quest("thief.time") ) ) > 0 )    // 15 分钟
                        //		                {
                        send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_THIEF, "Nhiệm vụ Vương Bộ Đầu");
                        send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_THIEF, 2, "Tìm vật phẩm");

                        //		                }
                        break;

                case 3: // 5. 寻物任务
                        //		                if( ( iFlag = 1800 - gone_time( who->get_quest("thief.time") ) ) > 0 )    // 15 分钟
                        //		                {
                        send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_THIEF, "Nhiệm vụ Vương Bộ Đầu");
                        send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_THIEF, 3, "Mua vật phẩm");

                        //		                }
                        break;

                case 4: // 3. 失窃任务(人物)
                        if (who->get_quest("thief.bonus"))
                        {
                                send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_THIEF, "Nhiệm vụ Vương Bộ Đầu");
                                send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_THIEF, 4, "Truy bắt trộm cướp (Hoàn thành)");
                        }
                        else if (stringp(id = who->get_quest("thief.thief")) && (npc = find_char(id)) && npc->is_thief()) // 15 分钟
                        {
                                send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_THIEF, "Nhiệm vụ Vương Bộ Đầu");
                                send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_THIEF, 4, "Truy bắt trộm cướp");
                        }
                        else
                        {
                                send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_THIEF, "Nhiệm vụ Vương Bộ Đầu");
                                send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_THIEF, 4, "Truy bắt trộm cướp (Nhiệm vụ thất bại)");
                        }
                        break;
                }
        }
}
