#include <item.h>
#include <ansi.h>
#include <music.h>
#include <effect.h>
#include <skill.h>

// 函数：命令处理
int main(object me, string arg)
{
        object who, *obj, obj2;
        string id, result = "", legend;
        int *item, *index, gold;
        int amount, flag, i, size, iAccept;
        int bag, b, c, d, allcount;
        if (is_gm(me))
                return 1;
        if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
        {
                send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
                return 1;
        }
        if (gone_time(me->get_time("give")) < 1) // 时间限制
        {
                me->set_time("give", time());
                return 1;
        }
        me->set_time("give", time());

        if (!arg)
                return 1;

        obj = ({0, 0, 0, 0, 0, 0});
        item = ({0, 0, 0, 0, 0, 0});
        index = ({0, 0, 0, 0, 0, 0});

        if (sscanf(arg, "%s %x#%d %x#%d %x#%d %x#%d %x#%d %x#%d $%d", id,
                   item[0], index[0], item[1], index[1], item[2], index[2],
                   item[3], index[3], item[4], index[4], item[5], index[5], gold) != 14)
        {
                notify("Bạn muốn cho ai cái gì ?");
                return 1;
        }

        if (!(who = find_char(id)))
        {
                //              notify( "您无法找到这个人." );
                return 1;
        }
        if (me == who)
        {
                notify("Không thể tự cho chính mình !!");
                return 1;
        }
        if (who->is_user() && who->get_login_flag() < 3)
        {
                notify("Đối phương còn chưa chuẩn bị.");
                return 1;
        }
        if (who->is_die())
                return 1;
        if (who->get_save("passhanhtrang") && who->get_save("ndmkhtk") < 1)
        {
                send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của đối phương đang trong trạng thái Khoá !");
                return 1;
        }
        if (who->is_npc())
        {
                if (!inside_screen_2(me, who))
                {
                        notify("Bạn cách %s quá xa rồi.", who->get_name());
                        return 1;
                }
        }
        else
        {
                if (distance_between(me, who) > 3)
                {
                        notify("Bạn cách %s quá xa rồi.", who->get_name());
                        return 1;
                }
                if (who->get_no_give())
                {
                        notify(who->get_name() + " không nhận đồ vật này");
                        return 1;
                }
        }

        me->to_front_eachother(who);

        flag = who->is_user(); // NPC 不受 no_drop, no_give 限制
        if (flag == 1)
        {
                if (gold + who->get_cash() > who->get_max_cash())
                {
                        notify("Tiền của đối phương đã tới mức cao nhất"); // 您想给予的金额太大.
                        return 1;
                }
        }
        for (i = 0, size = 0; i < 6; i++)
                if (index[i] > 0)
                {
                        if (!objectp(obj[i] = present(sprintf("%x#", item[i]), me, 1, MAX_CARRY * 4)))
                        {
                                notify("Bạn tìm không thấy %d dạng đồ vật này", i + 1);
                                return 1;
                        }
                        if (flag && (obj[i]->get_no_drop() || obj[i]->get_no_give())) // NPC 不受 no_drop, no_give 限制
                        {
                                notify(obj[i]->get_name() + " không thể cho người khác");
                                return 1;
                        }
                        if (flag && (obj[i]->get_bind() == 2 || obj[i]->get_bind() == 4 || obj[i]->get_bind() == 3 || obj[i]->get_bind() == 5))
                        {
                                notify(obj[i]->get_name() + " không thể cho người khác");
                                return 1;
                        }
                        if (flag && obj[i]->get_name() != "Trạng Nguyên Phục" && obj[i]->get_name() != "Phụng Quan Hà Ấp" && obj[i]->get_name() != "Lễ Phục" && obj[i]->get_name() != "Hôn Sa" && obj[i]->get_name() != "Anh Hùng Y" && obj[i]->get_name() != "Tiêu Dao Y" && obj[i]->get_name() != "Phong Giả Phục" && obj[i]->get_name() != "Phong Hậu Phục" && obj[i]->get_lock_time() > 0)
                        {
                                notify(obj[i]->get_name() + " không thể cho người khác");
                                return 1;
                        }
                        if (obj[i]->is_locked() > 0)
                        {
                                notify(sprintf("%s khoá càn khôn hiệu lực còn thừa %d giờ", obj[i]->get_name(), obj[i]->is_locked() / 3600));
                                return 1;
                        }
                        if (me->get_store(sprintf("%02d", get_d(obj[i]))))
                        {
                                notify(obj[i]->get_name() + " đã dùng rồi, không thể cho người khác");
                                return 1;
                        }

                        amount = obj[i]->get_amount();
                        if ((!amount && index[i] != 1) || (amount && (index[i] < 1 || index[i] > amount)))
                        {
                                notify("Bạn cho %s số lượng không đúng", obj[i]->get_name());
                                return 1;
                        }

                        if (me->get_ride())
                        {
                                me->set_2("thucuoi.ap", 0);
                                me->set_2("thucuoi.cp", 0);
                                me->set_2("thucuoi.dp", 0);
                                me->set_2("thucuoi.pp", 0);
                                me->set_2("thucuoi.sp", 0);
                                USER_ENERGY_D->count_ap(me);
                                USER_ENERGY_D->count_cp(me);
                                USER_ENERGY_D->count_dp(me);
                                USER_ENERGY_D->count_pp(me);
                                USER_ENERGY_D->count_sp(me);
                                me->set_ride(0);
                                me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
                        }

                        if (who->is_npc()) // 给予 NPC
                        {
                                if (CHAIN_D->accept_object(me, who, obj[i])) //任务链
                                        return 1;
                                if ((iAccept = who->accept_object(me, obj[i], index[i])) > 0)
                                {
                                        if (obj[i]->is_record())
                                        {
                                                legend = sprintf("Cho %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), who->get_name(), obj[i]->get_name(), "/sys/item/item"->get_pawn_save_string(obj[i]), index[i], obj[i]->get_user_id(), get_z(me), get_x(me), get_y(me));
                                                //"/sys/user/cmd"->log_item(legend);
                                        }
                                        if (amount)
                                                printf(ECHO "Bạn lấy %s tặng cho %s.", obj[i]->get_name(), who->get_name());
                                        else
                                                printf(ECHO "Bạn lấy %s tặng cho %s.", obj[i]->get_name(), who->get_name());

                                        if (amount && index[i] < amount)
                                                obj[i]->add_amount(-index[i]);
                                        else
                                        {
                                                obj[i]->remove_from_user();
                                                destruct(obj[i]);
                                        }

                                        item[i] = 0;
                                        index[i] = 0;

                                        return 1; // continue;
                                }
                                else if (iAccept == -99)
                                        ;
                                else
                                {
                                        notify(" %s không nhận %s của bạn.", who->get_name(), obj[i]->get_name());
                                        printf(ECHO " %s không nhận %s của bạn.", who->get_name(), obj[i]->get_name());

                                        item[i] = 0;
                                        index[i] = 0;
                                        return 1; // continue;
                                }
                        }
                        else
                                size++;
                }
                else
                {
                        item[i] = 0;
                        index[i] = 0;
                }
        bag = who->have_bag();
        b = bag % 100;
        c = (bag / 100) % 100;
        d = bag / 10000;
        if (b > 0 && who->get_bag1_time() > 0 && time() > who->get_bag1_time())
                b = 0;
        if (c > 0 && who->get_bag2_time() > 0 && time() > who->get_bag2_time())
                c = 0;
        if (d > 0 && who->get_bag3_time() > 0 && time() > who->get_bag3_time())
                d = 0;
        if (who->get_reincarnation())
                b = MAX_CARRY;
        allcount = MAX_CARRY + b + c + d;

        if (USER_INVENTORY_D->get_free_count(who) < size)
        //if( sizeof_inventory(who, 1, MAX_CARRY*4) + size > allcount )
        {
                send_user(me, "%c%s", '!', who->get_name() + " Hành trang không đủ chổ");
                return 1;
        }

        if (gold < 0 || gold > me->get_cash())
        {
                notify("Bạn cho số lượng tiền không đúng");
                return 1;
        }
        if (gold > 500000000)
        {
                notify("Không thể tặng tiền mặt trên 500 triệu lượng !");
                return 1;
        }

        if (who->is_npc()) // 给予 NPC
        {
                if (!gold)
                        return 1;

                if (who->accept_money(me, gold) > 0)
                {
                        printf(ECHO "Bạn lấy %d lượng tặng cho %s.", gold, who->get_name());
                        //                        me->log_money("给npc", gold);
                        me->add_cash2(-gold);
                        me->add_gold_log("give", gold);
                        "/sys/sys/count"->add_use("give", gold);
                        legend = sprintf("Cho %s,%d,%s,%s @%s lượng 0 %d 0 %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), who->get_name(), gold, get_z(me), get_x(me), get_y(me));
                        //"/sys/user/cmd"->log_item(legend);
                        return 1;
                }
                else
                {
                        notify(who->get_name() + " Không muốn nhận Ngân lượng của bạn .");
                        return 1;
                }
        }

        if (!size && !gold)
                return 1; // 什么都没有给

        me->add_cash2(-gold);
        me->add_gold_log("give", gold);
        //        me->log_money("给玩家 "+who->get_id(), -gold);
        who->add_cash2(gold);
        who->add_gold_log("give2", gold);
        //        who->log_money("收玩家 "+me->get_id(), gold);
        if (gold > 0)
        {
                legend = sprintf("Cho %s,%d,%s,%s %s,%d,%s,%s lượng 0 %d 0 %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), who->get_name(), who->get_number(), get_ip_name(who), who->get_id(), gold, get_z(me), get_x(me), get_y(me));
                //"/sys/user/cmd"->log_item(legend);
        }

        if (gold)
                result = sprintf(" %d lượng", gold);

        for (i = 0; i < 6; i++)
        {
                if (index[i] > 0 && obj[i])
                {
                        if (amount = obj[i]->get_amount())
                                id = sprintf(" %s", obj[i]->get_name());
                        else
                                id = sprintf("%s", obj[i]->get_name());

                        if (result == "")
                                result = id;
                        else
                                result = sprintf("%s , %s", result, id); // 、
                        if (obj[i]->is_record())
                        {
                                legend = sprintf("Cho %s,%d,%s,%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), who->get_name(), who->get_number(), get_ip_name(who), who->get_id(), obj[i]->get_name(), "/sys/item/item"->get_pawn_save_string(obj[i]), index[i], obj[i]->get_user_id(), get_z(me), get_x(me), get_y(me));
                                //"/sys/user/cmd"->log_item(legend);
                        }
                        if (amount && index[i] < amount)
                        {
                                obj[i]->add_amount(-index[i]);
                                obj2 = new (get_file_name(obj[i]));
                                obj2->set_user_id(obj[i]->get_user_id());
                                if (obj[i]->get("special"))
                                        obj2->set("special", obj[i]->get("special"));
                                obj2->set_amount(index[i]);
                                index[i] = obj2->move2(who);
                                obj2->add_to_user(index[i]);
                        }
                        else
                        {
                                obj[i]->remove_from_user();
                                index[i] = obj[i]->move2(who);
                                obj[i]->add_to_user(index[i]);
                        }
                }
        }

        if (result != "")
        {
                send_user(me, "%c%w", 0x0d, MUSIC_GIVE);

                printf(ECHO "Bạn lấy %s tặng cho %s", result, who->get_name());
                write_user(who, ECHO "%s cho bạn %s", me->get_name(), result);
                log_file("give.txt", sprintf("%s : %s (%d) đã chuyển %s cho người chơi %s có số id %d\n", short_time(time()), me->get_name(), me->get_number(), result, who->get_name(), who->get_number()));
        }

        return 1;
}
