
#include <ansi.h>
#include <item.h>
#include <city.h>

// 函数：命令处理
int main(object me, string arg)
{
        object city, who, item, money;
        string id, legend;
        int flag, amount, tax, value, value2;

        if (!arg)
                return 1;
        else if (sscanf(arg, "? %s %s", id, arg) == 2)
                flag = 1;
        else if (sscanf(arg, "! %s %s", id, arg) == 2)
                flag = 3;
        else if (sscanf(arg, "%s %s", id, arg) == 2)
                flag = 2;
        else
                return 1;

        if (!objectp(who = find_char(id)))
                return 1;

        if (!who->is_seller() && !who->is_trader())
                return 1;
        if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
        {
                send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
                return 1;
        }
        if (who->is_trader() && flag == 2)
                flag = 1;

        if ((time() - me->get("buy_time") > 300) && !inside_screen_2(me, who))
        {
                notify("Bạn cách %s quá xa rồi.", who->get_name());
                return 1;
        }

        me->to_front_eachother(who);

        if (sscanf(arg, "%s %d", arg, amount) == 2)
        {
                if (!(item = present(arg, me, 1, MAX_CARRY * 4)))
                        return 1;

                if (item->get_amount())
                {
                        if (amount < 1)
                                amount = 1;
                        if (amount > item->get_amount())
                                amount = item->get_amount();
                }
                else
                        amount = 1;
        }
        else
        {
                if (!(item = present(arg, me, 1, MAX_CARRY * 4)))
                        return 1;

                if (!(amount = item->get_amount()))
                        amount = 1;
        }

        if (item->get_no_sell() && !item->is_thuongnhan())
        {
                notify(item->get_name() + " không thể bán");
                return 1;
        }
        if (item->get_bind() == 5)
        {
                notify(item->get_name() + " không thể bán");
                return 1;
        }
        if (item->is_locked() > 0)
        {
                notify(sprintf("%s Khoá càn khôn mất hiệu lực còn thừa %d giờ", item->get_name(), item->is_locked() / 3600));
                return 1;
        }
        if (me->get_store(sprintf("%02d", get_d(item))))
        {
                notify(item->get_name() + " không thể bán");
                return 1;
        }

        if (flag == 1) // 输入商品个数
        {
                if (who->is_seller())
                {
                        if ((value = item->get_value()) < 1)
                        {
                                notify("Ta nơi này không thu %s.", item->get_name());
                                return 1;
                        }

                        // if( item->is_combined() ) value *= item->get_amount();
                        // value *= amount;

                        if (!(value2 = item->get_max_lasting()))
                                value2 = value / 2;
                        else
                                value2 = value / 2 * (item->get_lasting() * 100 / value2) / 100; // 小心越界
                        if (city = CITY_D->get_city_object(who))
                        {
                                if (me->get_city_name() == who->get_city_name())
                                        tax = city->get_sell_tax();
                                else
                                        tax = city->get_sell_tax_2();
                        }

                        send_user(me, "%c%c%d%d%s", '?', 2, amount, value2, sprintf("%s giá %d lượng， bạn tính bán ra bao nhiêu？(thuế %d%%)\n" ESC "sell ! %x# %s %%s\n", item->get_name(), value2, tax, getoid(who), arg));

                        return 1;
                }
                else if (who->is_trader() && (me->is_businessman() || me->get_save_2("mastertask.type") == 11 || me->get_save_2("orgtask3.type")))
                {
                        if (item->get_item_type() != ITEM_TYPE_GOOD)
                        {
                                notify("Ta nơi này chỉ lấy đặc sản thương phẩm");
                                return 1;
                        }
                        else if (who->get_city_name() == item->get_city_name())
                        {
                                notify("Ta nơi này không thu đặc sản bản địa");
                                return 1;
                        }
                        else
                        {
                                // value *= amount;

                                value = item->get_sell_price() + item->get_sell_range() * who->get_sell_rate() / 1000;

                                send_user(me, "%c%c%d%d%s", '?', 2, amount, value, sprintf("%s giá %d lượng， bạn tính bán ra bao nhiêu？\n" ESC "sell ! %x# %s %%s\n", item->get_name(), value, getoid(who), arg));
                        }

                        return 1;
                }
        }
        else if (flag == 2) // 确认卖出？
        {
                if ((item->get_item_color() == 1 || item->get_item_color() == 2 || item->get_item_color() == 3 || item->confirm_sell_item()) && !item->get_hide()) // 蓝色、黄色装备，指定道具
                {
                        send_user(me, "%c%s", ':', sprintf(" %s là vật phẩm đặc biệt, bạn chắc chắn muốn bán không?\n" ESC "Bán ra !\nsell ! %x# %x# %d\n" ESC "Rời khỏi.\nCLOSE\n", item->get_name(), getoid(who), getoid(item), amount));
                }
                else
                        main(me, sprintf("! %x# %x# %d", getoid(who), getoid(item), amount));
        }
        else if (flag == 3) // 售出商品
        {
                if (gone_time(me->get_time("sell")) < 1) // 时间限制
                {
                        return 1;
                }
                me->set_time("sell", time());

                if (who->is_seller())
                {
                        if ((value = item->get_value()) < 1)
                        {
                                notify("Ta nơi này không thu %s.", item->get_name());
                                return 1;
                        }

                        // if( item->is_combined() ) value *= item->get_amount();
                        value *= amount;

                        if (!(value2 = item->get_max_lasting()))
                                value2 = value / 2;
                        else
                                value2 = value / 2 * (item->get_lasting() * 100 / value2) / 100; // 小心越界
                        if (city = CITY_D->get_city_object(who))
                        {
                                if (me->get_city_name() == who->get_city_name())
                                        tax = city->get_sell_tax();
                                else
                                        tax = city->get_sell_tax_2();

                                value2 -= value2 * tax / 100;

                                city->add_tax(value2 * tax / (100 - tax));
                                city->add_cash(-value2);
                        }

                        notify("Bạn đã bán %s được %d lượng.", item->get_name(), value2);
                        write_user(me, ECHO "Bạn đã bán %s được %d lượng.", item->get_name(), value2);
                        if (item->is_record())
                        {
                                legend = sprintf("Bán ra %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), who->get_name(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                //"/sys/user/cmd"->log_item(legend);
                        }
                        if (amount < item->get_amount())
                        {
                                item->add_amount(-amount);
                        }
                        else
                        {
                                item->remove_from_user();
                                destruct(item);
                        }

                        me->add_cash2(value2);
                        me->add_gold_log("sell", value2);
                        legend = sprintf("Nhận được @%s %s,%d,%s,%s 金 0 %d 0 %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), value2, get_z(me), get_x(me), get_y(me));
                        //"/sys/user/cmd"->log_item(legend);
                        "/sys/sys/count"->add_income("sell", value2);
                        return 1;
                }
                else if (who->is_trader() && (me->is_businessman() || me->get_save_2("mastertask.type") == 11 || me->get_save_2("orgtask3.type")))
                {
                        if (item->get_item_type() != ITEM_TYPE_GOOD)
                        {
                                notify("Ta nơi này chỉ thua đặc sản thương phẩm");
                                return 1;
                        }
                        else if (who->get_city_name() == item->get_city_name())
                        {
                                notify("Ta không thu đặc sản bản địa");
                                return 1;
                        }
                        if (!objectp(money = present("钱票", me, 1, MAX_CARRY * 4)))
                        {
                                if (!objectp(money = present("Ngân Phiếu", me, 1, MAX_CARRY * 4)))
                                {
                                        notify("您做生意得出示商会的钱票.");
                                        return 1;
                                }
                        }
                        if (money->get_item_type() == ITEM_TYPE_CHEQUE)
                        {
                                if (me->get_save_2("orgtask3.type") == 0)
                                {
                                        notify("Bạn không có nhận nhiệm vụ thương nhân");
                                        return 1;
                                }
                        }
                        if (money->get_item_type() == ITEM_TYPE_CHEQUE2)
                        {
                                if (me->get_save_2("mastertask.type") != 11)
                                {
                                        notify("你没有接筹集资金的任务.");
                                        return 1;
                                }
                                if (me->get_save_2("mastertask.status") == 99)
                                {
                                        notify("你已经完成筹集资金的任务.");
                                        return 1;
                                }
                        }
                        value *= amount;

                        value = item->get_sell_price() + item->get_sell_range() * who->get_sell_rate() / 1000;

                        notify("Bạn bán ra %s được %d lượng", item->get_name(), value);
                        write_user(me, ECHO "Bạn bán ra %s được %d lượng", item->get_name(), value);

                        if ((value2 = (value - item->get_buyin()) / 100) > 0) // 赚到 1% 奖励
                        {
                                //                                me->add_occupation_exp(value2);    // 商人经验 +1%, 诚信 +1%, 智谋 +1%
                                //                                me->add_gift_cx(value2);
                                //                                me->add_gift_zm(value2);

                                //                                write_user( me, ECHO "您的商人经验 %+d, 诚信 %+d, 智谋 %+d.", value2, value2, value2 );
                        }

                        if (amount < item->get_amount())
                                item->add_amount(-amount);
                        else
                        {
                                item->remove_from_user();
                                destruct(item);
                        }

                        who->add_sell_rate(-1);
                        money->add_money(value);
                        money->do_look(me);
                        if (money->get_item_type() == ITEM_TYPE_CHEQUE2)
                        {
                                if (money->get_money() - money->get_orgin_money() >= me->get_save_2("mastertask.targetxy"))
                                {
                                        me->set_save_2("mastertask.status", 98);
                                        TASK_MASTER_D->send_task_desc(me, 1);
                                        send_user(me, "%c%s", '!', sprintf("Nhiệm vụ thương nhân đã hoàn thành, hãy quay về bẩm báo cho %s.", "/sys/task/quest1"->get_manager_name(me->get_fam_name())));
                                }
                        }

                        return 1;
                }
        }

        return 1;
}
