
#include <ansi.h>
#include <equip.h>
#include <item.h>
#include <effect.h>
#include <city.h>
#include <public.h>

int buy_store_item(object buyer, object owner, object item, int amount, int pos);
int buy_store_pet(object buyer, object owner, object pet, int pos);

// 函数:命令处理
int main(object me, string arg)
{
        mapping list;
        object city, who, *inv, item, item2, money, pet, orgnpc, org_master;
        string *key, id, file, result, legend, name, dtype;
        int what, total, amount, price, value, price1, itemid;
        int z, x, y, p, i, size, count, rate, tien, soluong;

        //        if( gone_time( me->get_time("buy") ) < 1 )    // 时间限制
        //      {
        //                me->set_time( "buy", time() );
        //                return 1;
        //        }
        if (is_gm(me))
                return 1;

        if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
        {
                send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
                return 1;
        }
        if (arg == "close")
        {
                if (me->get("buy_time") && get_effect(me, EFFECT_PROGRESS2))
                {
                        me->set("buy_time", 0);
                        set_effect(me, EFFECT_PROGRESS2, 1);
                }
                return 1;
        }
        me->set_time("buy", time());
        rate = random(100);
        if (!arg || sscanf(arg, "%s %s", id, arg) != 2)
                return 1;

        if (!objectp(who = find_char(id)))
                return 1;

        if (!who->is_seller() && !who->is_seller_2() && !who->is_trader() && !who->is_store_open() && !who->is_bonus_seller() && !who->is_item_seller())
                return 1;

        if ((time() - me->get("buy_time") > 300) && !inside_screen_2(me, who) && who->is_seller() != 7010)
        {
                notify("Bạn cách %s quá xa rồi.", who->get_name());
                return 1;
        }

        me->to_front_eachother(who);
        z = get_z(me), x = get_x(me), y = get_y(me);
        ;

        total = 1;

        if (sscanf(arg, "%d %d", what, total) != 2 // what, total 顺序不能反, sscanf 有缺陷
            && sscanf(arg, "%d", what) != 1)
        {
                notify("Bạn muốn mua cái gì ??");
                return 1;
        }
        if (total < 1)
        {
                notify("Số lượng mua phải lớn hơn 0");
                return 1;
        }

        if (who->is_seller() > 0 && who->is_seller() != 2 &&
            who->is_seller() != 7000 &&
            who->is_seller() != 7001 &&
            who->is_seller() != 7002 &&
            who->is_seller() != 7009 &&
            who->is_seller() != 7010)
        {
                if (!stringp(file = who->get_2(sprintf("good.%02d", what))))
                {
                        notify(who->get_name() + "Không có đồ vật này");
                        return 1;
                }
                value = who->get_2(sprintf("price.%02d", what));
                if (!value)
                        value = file->get_value();
                if (value < 1)
                {
                        notify(who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }
                price1 = value;
                if ((amount = USER_INVENTORY_D->can_carry_3(me, load_object(file))) < 1)
                {
                        notify("Hành trang không đủ chỗ");
                        return 1;
                }
                if (total > amount)
                        total = amount;
                /*
                if( city = CITY_D->get_city_object(who) )
                {
                        if( me->get_city_name() == who->get_city_name() )
                                value += value * city->get_buy_tax() / 100;
                        else    value += value * city->get_buy_tax_2() / 100;
                }
*/
                price = value * total;
                if (price < 1 || value != price / total) // 避免溢出出问题
                {
                        notify(who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }
                if (price > me->get_cash())
                {
                        notify("Ngân lượng của bạn không đủ.");
                        return 1;
                }

                if (file->is_combined())
                {
                        if (amount = USER_INVENTORY_D->carry_combined_item_3(me, load_object(file), total))
                        {
                                item = new (file);
                                item->set_hide(0);
                                item->set_amount(amount);
                                if (item->is_record())
                                {
                                        itemid = "/sys/sys/id"->add_max_itemid(1);
                                        item->set_user_id(sprintf("#%d#", itemid));
                                        //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                                        result = sprintf("Mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                        //"/sys/user/cmd"->log_item(result);
                                }
                                if (p = item->move2(me))
                                {
                                        item->add_to_user(p);
                                }
                                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                {
                                        item->add_to_scene(z, p / 1000, p % 1000);
                                }
                        }
                }
                else
                        for (i = 0; i < total; i++)
                        {
                                item = new (file);
                                item->set_hide(0);
                                if (item->is_record())
                                {
                                        itemid = "/sys/sys/id"->add_max_itemid(1);
                                        item->set_user_id(sprintf("#%d#", itemid));
                                        //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                                        result = sprintf("Mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                        //"/sys/user/cmd"->log_item(result);
                                }
                                if (p = item->move2(me))
                                {
                                        item->add_to_user(p);
                                }
                                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                {
                                        item->add_to_scene(z, p / 1000, p % 1000);
                                }
                        }

                me->add_cash2(-price);
                me->add_gold_log("buy", price);
                //me->log_money("Mua", -price);
                result = sprintf("Giảm %s,%d,%s,%s @%s lượng 0 %d 0 %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), who->get_name(), price, get_z(me), get_x(me), get_y(me));
                //"/sys/user/cmd"->log_item(result);
                "/sys/sys/count"->add_use("buy", price);
                tell_user(me, " %s đã bán cho bạn %s .", who->get_name(), file->get_name());

                if (city = CITY_D->get_city_object(who))
                {
                        total *= price1;
                        city->add_tax(price - total);
                        city->add_cash(total);
                }
        }
        else if (who->is_seller() == 7000)
        {
                if (!stringp(file = who->get_2(sprintf("good.%02d", what))))
                {
                        notify(who->get_name() + "Không có đồ vật này");
                        return 1;
                }
                value = who->get_2(sprintf("price.%02d", what));
                if (!value)
                        value = file->get_save_2("diemnhiemvu.score");
                if (value < 1)
                {
                        notify(who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }
                price1 = value;
                if ((amount = USER_INVENTORY_D->can_carry_3(me, load_object(file))) < 1)
                {
                        notify("Hành trang không đủ chỗ");
                        return 1;
                }
                if (total > amount)
                        total = amount;
                /*
                if( city = CITY_D->get_city_object(who) )
                {
                        if( me->get_city_name() == who->get_city_name() )
                                value += value * city->get_buy_tax() / 100;
                        else    value += value * city->get_buy_tax_2() / 100;
                }
*/
                price = value * total;
                if (price < 1 || value != price / total) // 避免溢出出问题
                {
                        notify(who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }
                if (price > me->get_save_2("diemnhiemvu.score"))
                {
                        send_user(me, "%c%s", '!', sprintf("Không đủ %d điểm \"Tích luỹ Nhiệm vụ\"", price));
                        write_user(me, sprintf(ECHO "Không đủ %d điểm \"Tích luỹ Nhiệm vụ\"", price));
                        return 1;
                }

                if (file->is_combined())
                {
                        if (amount = USER_INVENTORY_D->carry_combined_item_3(me, load_object(file), total))
                        {
                                item = new (file);
                                item->set_hide(0);
                                item->set_amount(amount);
                                if (item->is_record())
                                {
                                        itemid = "/sys/sys/id"->add_max_itemid(1);
                                        item->set_user_id(sprintf("#%d#", itemid));
                                        //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                                        result = sprintf("Mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                        //"/sys/user/cmd"->log_item(result);
                                }
                                if (p = item->move2(me))
                                {
                                        item->add_to_user(p);
                                }
                                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                {
                                        item->add_to_scene(z, p / 1000, p % 1000);
                                }
                        }
                }
                else
                        for (i = 0; i < total; i++)
                        {
                                item = new (file);
                                item->set_hide(0);
                                if (item->is_record())
                                {
                                        itemid = "/sys/sys/id"->add_max_itemid(1);
                                        item->set_user_id(sprintf("#%d#", itemid));
                                        //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                                        result = sprintf("Mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                        //"/sys/user/cmd"->log_item(result);
                                }
                                if (p = item->move2(me))
                                {
                                        item->add_to_user(p);
                                }
                                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                {
                                        item->add_to_scene(z, p / 1000, p % 1000);
                                }
                        }

                me->add_save_2("diemnhiemvu.score", -price); // me->add_gold_log("buy", price);
                //me->log_money("Mua", -price);
                result = sprintf("Giảm %s,%d,%s,%s @%s lượng 0 %d 0 %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), who->get_name(), price, get_z(me), get_x(me), get_y(me));
                //"/sys/user/cmd"->log_item(result);
                "/sys/sys/count"->add_use("buy", price);
                tell_user(me, "Bạn đã dùng %d điểm \"Tích luỹ Nhiệm vụ\" đổi %s thành công !", price, file->get_name());
                send_user(me, "%c%s", ';', sprintf("Bạn đã đổi " HIY "%s " NOR "thành công", file->get_name()));
                //	USER_D->user_channel(sprintf("Bằng hữu "HIY "%s" NOR " vừa thành công đổi được:"HIY " %s  "NOR " . ", me->get_name(), file->get_name() ));

                /*    if( city = CITY_D->get_city_object(who) )
                {
                        total *= price1;
                        city->add_tax( price - total );
                        city->add_cash( total );
                }*/
        }
        else if (who->is_seller() == 7001)
        {
                if (!stringp(file = who->get_2(sprintf("good.%02d", what))))
                {
                        notify(who->get_name() + "Không có đồ vật này");
                        return 1;
                }
                value = who->get_2(sprintf("price.%02d", what));
                if (!value)
                        value = file->get_save("knb");
                if (value < 1)
                {
                        notify(who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }
                price1 = value;
                if ((amount = USER_INVENTORY_D->can_carry_3(me, load_object(file))) < 1)
                {
                        notify("Hành trang không đủ chỗ");
                        return 1;
                }
                if (total > amount)
                        total = amount;
                /*
                if( city = CITY_D->get_city_object(who) )
                {
                        if( me->get_city_name() == who->get_city_name() )
                                value += value * city->get_buy_tax() / 100;
                        else    value += value * city->get_buy_tax_2() / 100;
                }
*/
                price = value * total;
                if (price < 1 || value != price / total) // 避免溢出出问题
                {
                        notify(who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }
                if (price > "sys/sys/test_db"->get_yuanbao(me))
                {
                        send_user(me, "%c%s", '!', sprintf("Không đủ %d \"Kim Nguyên Bảo\"", price / 10));
                        write_user(me, sprintf(ECHO "Không đủ %d \"Kim Nguyên Bảo\"", price / 10));
                        return 1;
                }

                if (file->is_combined())
                {
                        if (amount = USER_INVENTORY_D->carry_combined_item_3(me, load_object(file), total))
                        {
                                item = new (file);
                                item->set_hide(0);
                                item->set_amount(amount);
                                if (item->is_record())
                                {
                                        itemid = "/sys/sys/id"->add_max_itemid(1);
                                        item->set_user_id(sprintf("#%d#", itemid));
                                        //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                                        result = sprintf("Mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                        //"/sys/user/cmd"->log_item(result);
                                }
                                if (p = item->move2(me))
                                {
                                        item->add_to_user(p);
                                }
                                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                {
                                        item->add_to_scene(z, p / 1000, p % 1000);
                                }
                        }
                }
                else
                        for (i = 0; i < total; i++)
                        {
                                item = new (file);
                                item->set_hide(0);
                                if (item->is_record())
                                {
                                        itemid = "/sys/sys/id"->add_max_itemid(1);
                                        item->set_user_id(sprintf("#%d#", itemid));
                                        //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                                        result = sprintf("Mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                        //"/sys/user/cmd"->log_item(result);
                                }
                                if (p = item->move2(me))
                                {
                                        item->add_to_user(p);
                                }
                                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                {
                                        item->add_to_scene(z, p / 1000, p % 1000);
                                }
                        }

                "sys/sys/test_db"->add_yuanbao(me, -price);
                //me->log_money("Mua", -price);
                result = sprintf("Giảm %s,%d,%s,%s @%s lượng 0 %d 0 %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), who->get_name(), price, get_z(me), get_x(me), get_y(me));
                //"/sys/user/cmd"->log_item(result);
                "/sys/sys/count"->add_use("buy", price);
                tell_user(me, "Số dư tài khoản của bạn là %d \"Ngân Bảo\"!", "sys/sys/test_db"->get_yuanbao(me));
                send_user(me, "%c%s", ';', sprintf("Bạn đã mua " HIY "%s " NOR "thành công", file->get_name()));

                /*    if( city = CITY_D->get_city_object(who) )
                {
                        total *= price1;
                        city->add_tax( price - total );
                        city->add_cash( total );
                }*/
        }
        else if (who->is_seller() == 7002)
        {
                if (!stringp(file = who->get_2(sprintf("good.%02d", what))))
                {
                        notify(who->get_name() + "Không có đồ vật này");
                        return 1;
                }
                value = who->get_2(sprintf("price.%02d", what));
                if (!value)
                        value = file->get_save("qsvst");
                if (value < 1)
                {
                        notify(who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }
                price1 = value;
                if ((amount = USER_INVENTORY_D->can_carry_3(me, load_object(file))) < 1)
                {
                        notify("Hành trang không đủ chỗ");
                        return 1;
                }
                if (total > amount)
                        total = amount;
                /*
                if( city = CITY_D->get_city_object(who) )
                {
                        if( me->get_city_name() == who->get_city_name() )
                                value += value * city->get_buy_tax() / 100;
                        else    value += value * city->get_buy_tax_2() / 100;
                }
*/
                price = value * total;
                if (price < 1 || value != price / total) // 避免溢出出问题
                {
                        notify(who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }
                if (price > TASK_LEGEND_D->check_task_item_amount(me, "Vô Song Điểm Phiếu"))
                {
                        send_user(me, "%c%s", '!', sprintf("Không đủ %d \"Vô Song Điểm Phiếu\"", price));
                        write_user(me, sprintf(ECHO "Không đủ %d \"Vô Song Điểm Phiếu\"", price));
                        return 1;
                }

                if (file->is_combined())
                {
                        if (amount = USER_INVENTORY_D->carry_combined_item_3(me, load_object(file), total))
                        {
                                item = new (file);
                                item->set_hide(0);
                                item->set_amount(amount);
                                if (item->is_record())
                                {
                                        itemid = "/sys/sys/id"->add_max_itemid(1);
                                        item->set_user_id(sprintf("#%d#", itemid));
                                        //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                                        result = sprintf("Mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                        //"/sys/user/cmd"->log_item(result);
                                }
                                if (p = item->move2(me))
                                {
                                        item->add_to_user(p);
                                }
                                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                {
                                        item->add_to_scene(z, p / 1000, p % 1000);
                                }
                        }
                }
                else
                        for (i = 0; i < total; i++)
                        {
                                item = new (file);
                                item->set_hide(0);
                                if (item->is_record())
                                {
                                        itemid = "/sys/sys/id"->add_max_itemid(1);
                                        item->set_user_id(sprintf("#%d#", itemid));
                                        //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                                        result = sprintf("Mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                        //"/sys/user/cmd"->log_item(result);
                                }
                                if (p = item->move2(me))
                                {
                                        item->add_to_user(p);
                                }
                                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                {
                                        item->add_to_scene(z, p / 1000, p % 1000);
                                }
                        }

                TASK_LEGEND_D->check_task_item1(me, "Vô Song Điểm Phiếu", price);
                //me->log_money("Mua", -price);
                result = sprintf("Giảm %s,%d,%s,%s @%s lượng 0 %d 0 %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), who->get_name(), price, get_z(me), get_x(me), get_y(me));
                //"/sys/user/cmd"->log_item(result);
                "/sys/sys/count"->add_use("buy", price);
                tell_user(me, "Bạn đã dùng %d \"Vô Song Điểm Phiếu\" để đổi %s!", price, file->get_name());
                send_user(me, "%c%s", ';', sprintf("Bạn đã đổi " HIY "%s " NOR "thành công", file->get_name()));

                /*    if( city = CITY_D->get_city_object(who) )
                {
                        total *= price1;
                        city->add_tax( price - total );
                        city->add_cash( total );
                }*/
        }
        else if (who->is_seller() == 7009)
        {
                if (!stringp(file = who->get_2(sprintf("good.%02d", what))))
                {
                        notify(who->get_name() + "Không có đồ vật này");
                        return 1;
                }
                // value = who->get_2(sprintf("price.%02d", what));
                // if (!value)
                //         value = file->get_value();
                value = 30000;
                if (value < 1)
                {
                        notify(who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }
                soluong = who->get_2(sprintf("soluong.%02d", what));
                if (!soluong || soluong == 0)
                {
                        notify(who->get_name() + " Đã hết hàng");
                        return 1;
                }
                if (total > soluong)
                {
                        notify(who->get_name() + "Không đủ hàng với số lượng này");
                        return 1;
                }
                price1 = value;
                if ((amount = USER_INVENTORY_D->can_carry_3(me, load_object(file))) < 1)
                {
                        notify("Hành trang không đủ chỗ");
                        return 1;
                }

                if (total > amount)
                        total = amount;
                /*
                if( city = CITY_D->get_city_object(who) )
                {
                        if( me->get_city_name() == who->get_city_name() )
                                value += value * city->get_buy_tax() / 100;
                        else    value += value * city->get_buy_tax_2() / 100;
                }
*/
                price = value * total;
                if (price < 1 || value != price / total) // 避免溢出出问题
                {
                        notify(who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }
                if (price > me->get_cash())
                {
                        notify("Ngân lượng của bạn không đủ.");
                        return 1;
                }

                if (file->is_combined())
                {
                        if (amount = USER_INVENTORY_D->carry_combined_item_3(me, load_object(file), total))
                        {
                                item = new (file);
                                item->set_hide(0);
                                item->set_amount(amount);
                                if (item->is_record())
                                {
                                        itemid = "/sys/sys/id"->add_max_itemid(1);
                                        item->set_user_id(sprintf("#%d#", itemid));
                                        //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                                        result = sprintf("Mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                        //"/sys/user/cmd"->log_item(result);
                                }
                                if (p = item->move2(me))
                                {
                                        item->add_to_user(p);
                                }
                                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                {
                                        item->add_to_scene(z, p / 1000, p % 1000);
                                }
                        }
                }
                else
                        for (i = 0; i < total; i++)
                        {
                                item = new (file);
                                item->set_hide(0);
                                if (item->is_record())
                                {
                                        itemid = "/sys/sys/id"->add_max_itemid(1);
                                        item->set_user_id(sprintf("#%d#", itemid));
                                        //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                                        result = sprintf("Mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                        //"/sys/user/cmd"->log_item(result);
                                }
                                if (p = item->move2(me))
                                {
                                        item->add_to_user(p);
                                }
                                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                {
                                        item->add_to_scene(z, p / 1000, p % 1000);
                                }
                        }
                //   printf("truoc: " + soluong);
                who->add_2(sprintf("soluong.%02d", what), -total);
                //  printf("sau: " + soluong);
                me->add_cash2(-price);
                me->add_gold_log("buy", price);
                //me->log_money("Mua", -price);
                result = sprintf("Giảm %s,%d,%s,%s @%s lượng 0 %d 0 %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), who->get_name(), price, get_z(me), get_x(me), get_y(me));
                //"/sys/user/cmd"->log_item(result);
                "/sys/sys/count"->add_use("buy", price);
                tell_user(me, " %s đã bán cho bạn %s .", who->get_name(), file->get_name());

                // if (city = CITY_D->get_city_object(who))
                // {
                //         total *= price1;
                //         city->add_tax(price - total);
                //         city->add_cash(total);
                // }
        }

        else if (who->is_seller() == 7010)
        {
                if (!stringp(file = who->get_2(sprintf("good.%02d", what))))
                {
                        notify(who->get_name() + "Không có đồ vật này");
                        return 1;
                }
                value = who->get_2(sprintf("price.%02d", what));
                if (!value)
                        value = file->get_save("diemtlnt");
                if (value < 1)
                {
                        notify(who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }
                price1 = value;
                if ((amount = USER_INVENTORY_D->can_carry_3(me, load_object(file))) < 1)
                {
                        notify("Hành trang không đủ chỗ");
                        return 1;
                }
                if (total > amount)
                        total = amount;
                /*
                if( city = CITY_D->get_city_object(who) )
                {
                        if( me->get_city_name() == who->get_city_name() )
                                value += value * city->get_buy_tax() / 100;
                        else    value += value * city->get_buy_tax_2() / 100;
                }
*/
                price = value * total;
                if (price < 1 || value != price / total) // 避免溢出出问题
                {
                        notify(who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }
                if (price > me->get_save("diemtlnt"))
                {
                        send_user(me, "%c%s", '!', sprintf("Không đủ %d \"Điểm Tích Lũy Nạp Thẻ\"", price));
                        write_user(me, sprintf(ECHO "Không đủ %d \"Điểm Tích Lũy Nạp Thẻ\"", price));
                        return 1;
                }

                if (file->is_combined())
                {
                        if (amount = USER_INVENTORY_D->carry_combined_item_3(me, load_object(file), total))
                        {
                                item = new (file);
                                item->set_hide(0);
                                item->set_amount(amount);
                                if (item->is_record())
                                {
                                        itemid = "/sys/sys/id"->add_max_itemid(1);
                                        item->set_user_id(sprintf("#%d#", itemid));
                                        //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                                        result = sprintf("Mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                        //"/sys/user/cmd"->log_item(result);
                                }
                                if (p = item->move2(me))
                                {
                                        item->add_to_user(p);
                                }
                                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                {
                                        item->add_to_scene(z, p / 1000, p % 1000);
                                }
                        }
                }
                else
                        for (i = 0; i < total; i++)
                        {
                                item = new (file);
                                item->set_hide(0);
                                if (item->is_record())
                                {
                                        itemid = "/sys/sys/id"->add_max_itemid(1);
                                        item->set_user_id(sprintf("#%d#", itemid));
                                        //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                                        result = sprintf("Mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                        //"/sys/user/cmd"->log_item(result);
                                }
                                if (p = item->move2(me))
                                {
                                        item->add_to_user(p);
                                }
                                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                {
                                        item->add_to_scene(z, p / 1000, p % 1000);
                                }
                        }

                me->add_save("diemtlnt", -price);
                //me->log_money("Mua", -price);
                result = sprintf("Giảm %s,%d,%s,%s @%s lượng 0 %d 0 %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), who->get_name(), price, get_z(me), get_x(me), get_y(me));
                //"/sys/user/cmd"->log_item(result);
                "/sys/sys/count"->add_use("buy", price);
                tell_user(me, "Số dư tài khoản của bạn là %d \"Điểm Tích Lũy Nạp Thẻ\"!", me->get_save("diemtlnt"));
                send_user(me, "%c%s", ';', sprintf("Bạn đã mua " HIY "%s " NOR "thành công", file->get_name()));

                /*    if( city = CITY_D->get_city_object(who) )
                {
                        total *= price1;
                        city->add_tax( price - total );
                        city->add_cash( total );
                }*/
        }
        // End here
        else if (who->is_seller() == 2) // 云游商人
        {
                if (gone_time(who->get("yunyou_buy_time")) < 5)
                {
                        notify(who->get_name() + "Nếu quá 5 giây mới có thể bán");
                        return 1;
                }
                if (!stringp(file = who->get_2(sprintf("good.%02d", what))))
                {
                        notify(who->get_name() + "Không có đồ vật này");
                        return 1;
                }
                value = who->get_2(sprintf("price.%02d", what));
                if (!value)
                        value = file->get_value();
                if (value < 1)
                {
                        notify(who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }
                dtype = file[ < 4.. < 1];
                if (file->get_item_type() == ITEM_TYPE_DIAMOND_3 && who->get_save_2("diamond." + dtype) >= 100)
                {
                        value = value * who->get_save_2("diamond." + dtype) / 100;
                        total = 1;
                }
                price1 = value;
                if ((amount = USER_INVENTORY_D->can_carry_3(me, load_object(file))) < 1)
                {
                        notify("Hành trang không đủ chỗ");
                        return 1;
                }
                if (total > who->get_2(sprintf("list.%02d", what)))
                {
                        notify(who->get_name() + "Không có nhiều đồ vật như vậy");
                        return 1;
                }

                if (city = CITY_D->get_city_object(who))
                {
                        if (me->get_city_name() == who->get_city_name())
                                value += value * city->get_buy_tax() / 100;
                        else
                                value += value * city->get_buy_tax_2() / 100;
                }

                price = value * total;
                if (price < 1 || value != price / total) // 避免溢出出问题
                {
                        notify(who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }
                if (price > me->get_cash())
                {
                        notify("Ngân lượng bạn hiện đang có không đủ.");
                        return 1;
                }

                if (file->is_combined())
                {
                        if (amount = USER_INVENTORY_D->carry_combined_item_3(me, load_object(file), total))
                        {
                                item = new (file);
                                item->set_hide(0);
                                item->set_amount(amount);
                                if (item->is_record())
                                {
                                        itemid = "/sys/sys/id"->add_max_itemid(1);
                                        item->set_user_id(sprintf("#%d#", itemid));
                                        //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                                        result = sprintf("Mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                        //"/sys/user/cmd"->log_item(result);
                                }
                                if (p = item->move2(me))
                                {
                                        item->add_to_user(p);
                                }
                                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                {
                                        item->add_to_scene(z, p / 1000, p % 1000);
                                }
                        }
                }
                else
                        for (i = 0; i < total; i++)
                        {
                                item = new (file);
                                item->set_hide(0);
                                if (item->is_record())
                                {
                                        itemid = "/sys/sys/id"->add_max_itemid(1);
                                        item->set_user_id(sprintf("#%d#", itemid));
                                        //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                                        result = sprintf("Mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                        //"/sys/user/cmd"->log_item(result);
                                }
                                if (p = item->move2(me))
                                {
                                        item->add_to_user(p);
                                }
                                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                {
                                        item->add_to_scene(z, p / 1000, p % 1000);
                                }
                        }

                me->add_cash2(-price);
                me->add_gold_log("buy", price);
                result = sprintf("Giảm %s,%d,%s,%s @%s lượng 0 %d 0 %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), who->get_name(), price, get_z(me), get_x(me), get_y(me));
                //"/sys/user/cmd"->log_item(result);
                "/sys/sys/count"->add_use("buy", price);
                if (who->add_2(sprintf("list.%02d", what), -total) < 1)
                        who->delete_2(sprintf("good.%02d", what));
                if (file->get_item_type() == ITEM_TYPE_DIAMOND_3 && who->get_save_2("diamond." + dtype) >= 100)
                {
                        who->add_save_2("diamond." + dtype, 3);
                        who->save();
                        who->set("yunyou_buy_time", time());
                        CHAT_D->sys_channel(0, sprintf(HIR "%s" HIY " lanh tay lẹ mắt lấy " HIR "%d" HIY " mua được %s " HIR "%s" HIY ".", me->get_name(), price, who->get_name(), file->get_name()));
                        tell_user(me, "Bạn lấy %d giá %s mua %s, %s tinh thạch chỉ số biến thành %d", price, who->get_name(), file->get_name(), file->get_name(), who->get_save_2("diamond." + dtype));
                }
                else
                        tell_user(me, " %s đã bán cho bạn %s .", who->get_name(), file->get_name());
        }
        else if (who->is_seller_2())
        {
                if (!stringp(file = who->get_2(sprintf("good.%02d", what))))
                {
                        notify(who->get_name() + "Không có đồ vật này");
                        return 1;
                }
                value = who->get_2(sprintf("price.%02d", what));
                if (!value)
                        value = file->get_value();
                if (value < 1)
                {
                        notify(who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }
                if (total > (size = who->get_2(sprintf("list.%02d", what))))
                {
                        notify("%s hiện tại chỉ có %s số lượng không đủ",
                               who->get_name(), file->get_name());
                        return 1;
                }

                if ((amount = USER_INVENTORY_D->can_carry_3(me, load_object(file))) < 1)
                {
                        notify("Hành trang không đủ chỗ");
                        return 1;
                }
                if (total > amount)
                        total = amount;
                price1 = value;
                if (city = CITY_D->get_city_object(who))
                {
                        if (me->get_city_name() == who->get_city_name())
                                value += value * city->get_buy_tax() / 100;
                        else
                                value += value * city->get_buy_tax_2() / 100;
                }

                price = value * total;
                if (price < 1 || value != price / total) // 避免溢出出问题
                {
                        notify(who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }
                if (price > me->get_cash())
                {
                        notify("Ngân lượng bạn hiện đang có không đủ.");
                        return 1;
                }

                if (who->add_2(sprintf("list.%02d", what), -total) < 1)
                        who->delete_2(sprintf("good.%02d", what));

                if (file->is_combined())
                {
                        if (amount = USER_INVENTORY_D->carry_combined_item_3(me, load_object(file), total))
                        {
                                item = new (file);
                                item->set_hide(0);
                                item->set_amount(amount);
                                if (item->is_record())
                                {
                                        itemid = "/sys/sys/id"->add_max_itemid(1);
                                        item->set_user_id(sprintf("#%d#", itemid));
                                        //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                                        result = sprintf("Mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                        //"/sys/user/cmd"->log_item(result);
                                }
                                if (p = item->move2(me))
                                {
                                        item->add_to_user(p);
                                }
                                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                {
                                        item->add_to_scene(z, p / 1000, p % 1000);
                                }
                        }
                }
                else
                        for (i = 0; i < total; i++)
                        {
                                item = new (file);
                                item->set_hide(0);
                                if (item->is_record())
                                {
                                        itemid = "/sys/sys/id"->add_max_itemid(1);
                                        item->set_user_id(sprintf("#%d#", itemid));
                                        //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                                        result = sprintf("Mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                        //"/sys/user/cmd"->log_item(result);
                                }
                                if (p = item->move2(me))
                                {
                                        item->add_to_user(p);
                                }
                                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                {
                                        item->add_to_scene(z, p / 1000, p % 1000);
                                }
                        }

                me->add_cash2(-price);
                me->add_gold_log("buy", price);
                result = sprintf("Giảm %s,%d,%s,%s @%s lượng 0 %d 0 %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), who->get_name(), price, get_z(me), get_x(me), get_y(me));
                //"/sys/user/cmd"->log_item(result);
                "/sys/sys/count"->add_use("buy", price);
                tell_user(me, " %s đã bán cho bạn %s .", who->get_name(), file->get_name());

                if (city = CITY_D->get_city_object(who))
                {
                        total *= price1;
                        city->add_tax(price - total);
                        city->add_cash(total);
                }
        }
        else if (who->is_trader() && (me->is_businessman() || me->get_save_2("mastertask.type") == 11 || me->get_save_2("orgtask3.type"))) // 国家商人
        {
                total = 1; // 只能一个个买

                if (!stringp(file = who->get_2(sprintf("good.%02d", what))))
                {
                        notify(who->get_name() + "Không có đồ vật này");
                        return 1;
                }
                if ((amount = USER_INVENTORY_D->can_carry_3(me, load_object(file))) < 1)
                {
                        notify("Hành trang không đủ chỗ");
                        return 1;
                }
                if ((price = file->get_buy_price() + file->get_buy_range() * who->get_buy_rate() / 1000) < 1)
                {
                        notify(who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }
                if (total > (size = who->get_2(sprintf("list.%02d", what))))
                {
                        notify("%s hiện tại chỉ có %s số lượng không đủ",
                               who->get_name(), file->get_name());
                        return 1;
                }

                if (!objectp(money = present("钱票", me, 1, MAX_CARRY * 4)))
                {
                        if (!objectp(money = present("Ngân Phiếu", me, 1, MAX_CARRY * 4)))
                        {
                                notify("Bạn không có Ngân Phiếu.");
                                return 1;
                        }
                }
                if (money->get_item_type() == ITEM_TYPE_CHEQUE)
                {
                        if (me->get_save_2("orgtask3.type") == 0)
                        {
                                notify("Bạn không có lãnh nhiệm vụ thương nhân Bang Phái");
                                return 1;
                        }
                        if (money->get_money() >= money->get_orgin_money() * 3 / 2)
                        {
                                notify("Bạn đã hoàn thành nhiệm vụ thương nhân Bang Phái");
                                return 1;
                        }
                }
                if (money->get_item_type() == ITEM_TYPE_CHEQUE2)
                {
                        if (me->get_save_2("mastertask.type") != 11)
                        {
                                notify("你没有接筹集资lượng的任务.");
                                return 1;
                        }
                        if (me->get_save_2("mastertask.status") == 99)
                        {
                                notify("你已经完成筹集资lượng的任务.");
                                return 1;
                        }
                        if (money->get_money() - money->get_orgin_money() >= me->get_save_2("mastertask.targetxy"))
                        {
                                send_user(me, "%c%s", '!', "Của ngươi Ngân Phiếu đa đạt số tiền lớn nhất !");
                                return 1;
                        }
                }
                if (price * total > money->get_money())
                {
                        notify("您手上钱票的资lượng不够.");
                        return 1;
                }
                if (who->add_2(sprintf("list.%02d", what), -total) < 1)
                        who->delete_2(sprintf("good.%02d", what));
                for (i = 0; i < total; i++)
                {
                        item = new (file);
                        item->set_hide(0);
                        item->set_buyin(price);
                        who->add_buy_rate(1);

                        if (p = item->move2(me))
                        {
                                item->add_to_user(p);
                        }
                        else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                        {
                                item->add_to_scene(z, p / 1000, p % 1000);
                        }
                }

                money->add_money(-price * total);
                money->do_look(me);
                tell_user(me, "Bạn hoa %d lượng hướng %s mua %s.", price * total, who->get_name(), item->get_name());
        }
        else if (who->is_store_open())
        {
                if (who == me)
                {
                        notify("自己的东西就不用买了吧？");
                        return 1;
                }
                if (!mapp(list = who->get_store_dbase()) || !sizeof(key = keys(list)))
                {
                        send_user(me, "%c%s", '!', who->get_name() + "gì gì đó tất cả đều bán hết");
                        return 1;
                }
                if ((price = list[sprintf("%02d", what)]) < 1)
                {
                        send_user(me, "%c%s", '!', who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }
                price1 = price;
                price *= total;
                if (price < 1 || price1 != price / total) // 避免溢出出问题
                {
                        notify(who->get_name() + "Không thèm giao dịch với bạn");
                        return 1;
                }

                if (price > me->get_cash())
                {
                        notify("Ngân lượng bạn hiện đang có không đủ.");
                        return 1;
                }

                if (price + who->get_cash() > who->get_max_cash())
                {
                        notify("Sô tiên cua đôi phương vượt qua giơi hạn, giao dịch thât bại");
                        return 1;
                }

                if (what < 100) //Vật phẩm
                {
                        if (!objectp(item = number_present(who, what, 1, MAX_CARRY)))
                        {
                                send_user(me, "%c%s", '!', who->get_name() + "Không thèm giao dịch với bạn");
                                return 1;
                        }
                        name = item->get_name();
                        total = buy_store_item(me, who, item, total, what);
                }
                else //Bảo Thú
                {
                        if (!(id = who->get_store_beast_id(sprintf("%2d", what))) || !objectp(pet = find_char(id)) || !pet->is_pet() || pet->get_owner() != who)
                        {
                                send_user(me, "%c%s", '!', who->get_name() + "Không thèm giao dịch với bạn");
                                return 1;
                        }
                        name = pet->get_firstname();
                        total = buy_store_pet(me, who, pet, what);
                }
                if (!total)
                        return 1;
                price = price1 * total;
                result = sprintf("%s dùng %d lượng mua của bạn %s, bạn giao nộp thuế %d lượng",
                                 me->get_name(), price, name, price / 100);
                log_file("wu_duty.dat", sprintf("%s %s(%d) nộp thuế %d\n", short_time(), me->get_id(), me->get_number(), price / 100));
                send_user(who, "%s", ECHO + result);
                send_user(who, "%c%c%s", 0x7b, 0xfe, result); // 交易记录
                send_user(who, "%c%c%d", 0x7b, 0xfd, price);  // 交易记录
                tell_user(me, "Bạn hoa %d  hướng %s mua %s.",
                          price, who->get_name(), name);
                me->add_cash2(-price);
                me->add_gold_log("buy2", price);
                //                me->log_money("摆摊买", -price);
                who->add_cash2(price - price / 100);
                who->add_gold_log("sell2", price - price / 100);
                //		who->log_money("摆摊卖", price*99/100);
                if (WUSHUANG->get_save("wg_duty") < 20000000)
                {
                        if ((WUSHUANG->get_save("wg_duty") + price / 100) > 20000000)
                        {
                                WUSHUANG->set_save("wg_duty", 20000000);
                                WUSHUANG->get_save_2("occupy_org");
                                orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", WUSHUANG->get_save_2("occupy_org")));
                                org_master = find_char(orgnpc->get_master());
                                MAILBOX->sys_mail(orgnpc->get_master_id(), orgnpc->get_master(), HIW "    Bạn chiếm lĩnh Vô Song Thành thuế đã đạt mức cao nhất, không thể gia tăng nữa !");
                        }
                        else
                                WUSHUANG->add_save("wg_duty", price / 100);
                        WUSHUANG->save();
                }
                result = sprintf("Mua hàng rong giảm %s,%d,%s,%s %s,%d,%s,%s lượng 0 %d 0 %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), who->get_name(), who->get_number(), get_ip_name(who), who->get_id(), price, get_z(who), get_x(who), get_y(who));
                //"/sys/user/cmd"->log_item(result);
                if (who->is_npc())
                        send_user(me, "%c%c%c%d%s", 0x28, 0, 0, getoid(who), sprintf("%-12s%s", who->get_name(), ""));
                else
                        send_user(me, "%c%c%c%d%s", 0x28, 0, 1, who->get_number(), sprintf("%-12s%s", who->get_name(), me->get_store_name()));
                if (!mapp(list = who->get_store_dbase()) || !(size = sizeof(key = keys(list))))
                        return 1;
                for (i = 0; i < size; i++)
                {
                        what = to_int(key[i]);
                        if (what < 100) //物品列表
                        {
                                if (item = number_present(who, what, 1, MAX_CARRY))
                                        send_user(me, "%c%c%d%w%w%c%c%s", 0x28, what, list[key[i]],
                                                  item->get_picid_2(), item->get_amount(), 0, item->get_item_color(), item->get_name());
                        }
                        else //宠物列表
                        {
                                if ((pet = find_char(who->get_store_beast_id(key[i]))) && pet->get_owner() == who && pet->get("store"))
                                        send_user(me, "%c%c%d%w%w%c%c%s", 0x28, what, list[key[i]],
                                                  pet->get_char_picid(), 1, 0, 0, pet->get_firstname());
                        }
                }
        }
        else if (who->is_bonus_seller())
        {
                if (!stringp(file = who->get_2(sprintf("good.%02d", what))))
                {
                        notify(who->get_name() + "Không có đồ vật này");
                        return 1;
                }
                if ((price = file->get_bonus_value()) < 1)
                {
                        notify(who->get_name() + "không nghỉ với ngươi đổi");
                        return 1;
                }

                if ((amount = USER_INVENTORY_D->can_carry_3(me, load_object(file))) < 1)
                {
                        notify("Hành trang không đủ chỗ");
                        return 1;
                }
                if (total > amount)
                        total = amount;

                price *= total;

                if (price > me->get_bonus())
                {
                        notify("您的功德点数不够.");
                        return 1;
                }

                if (file->is_combined())
                {
                        if (amount = USER_INVENTORY_D->carry_combined_item(me, load_object(file), total))
                        {
                                item = new (file);
                                item->set_hide(0);
                                item->set_amount(amount);

                                if (p = item->move2(me))
                                {
                                        item->add_to_user(p);
                                }
                                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                {
                                        item->add_to_scene(z, p / 1000, p % 1000);
                                }
                        }
                }
                else
                        for (i = 0; i < total; i++)
                        {
                                item = new (file);
                                item->set_hide(0);
                                if (p = item->move2(me))
                                {
                                        item->add_to_user(p);
                                }
                                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                {
                                        item->add_to_scene(z, p / 1000, p % 1000);
                                }
                        }

                me->add_bonus(-price);
                notify("Bạn hướng %s đoái đến %s.", who->get_name(), file->get_name());
        }
        else if (who->is_item_seller()) // 用点卡买道具！！
        {
                // 目前抄普通小贩 is_seller(), 只是取消 tax 而已

                if (!me->get_pay_money_buy_item()) // 可以通过点数Mua道具
                {
                        if (me->get("paycount") < 0)
                        {
                                notify("您的帐号余额不足, 如果您已充值, 请退出游戏再进以Mua道具.");
                                return 1;
                        }
                        if (!stringp(file = who->get_2(sprintf("good.%02d", what))))
                        {
                                notify(who->get_name() + "Không có đồ vật này");
                                return 1;
                        }
                        if ((price = file->get_item_value()) < 1)
                        {
                                notify(who->get_name() + "Không thèm giao dịch với bạn");
                                return 1;
                        }

                        if ((amount = USER_INVENTORY_D->can_carry_3(me, load_object(file))) < 1)
                        {
                                notify("Hành trang không đủ chỗ");
                                return 1;
                        }
                        if (total > amount)
                                total = amount;

                        price *= total;

                        me->set_pay_money_buy_item(1); // 通过点数Mua道具中
                        me->set_pay_type(1);
                        me->set_buy_item_cmd_string(sprintf("%x# %d %d", getoid(who), what, total));
                        log_file("buyitem.dat", sprintf("%s %s(%d) Mua%s %d\n", short_time(), me->get_id(), me->get_number(), file->get_name(), total));
                        if (MAIN_D->get_host_type() == 4 || MAIN_D->get_host_type() == 0 /*||MAIN_D->get_host_type()==1000*/)
                        {
                                db_user_pay(me, sprintf("%s:80\n"
                                                        "GET http:/"
                                                        "/%s/purchase.php?t=%s&u=%d&o=%d&n=%d&m=%d&c=%d&ip=%s&r=%d&h=%d\r\n",
                                                        MAIN_D->get_php_ip(),
                                                        MAIN_D->get_php_ip(), short_time_2(), me->get_acountid(), me->get_number(), total, price, file->get_item_number(), get_ip_name(me), MAIN_D->get_region(), MAIN_D->get_host()));
                                log_file("php.dat", sprintf("%s:80\n"
                                                            "GET http:/"
                                                            "/%s/purchase.php?t=%s&u=%d&o=%d&n=%d&m=%d&c=%d&ip=%s&r=%d&h=%d\n",
                                                            MAIN_D->get_php_ip(),
                                                            MAIN_D->get_php_ip(), short_time_2(), me->get_acountid(), me->get_number(), total, price, file->get_item_number(), get_ip_name(me), MAIN_D->get_region(), MAIN_D->get_host()));
                        }
                        else
                                db_user_pay(me, sprintf("%s:80\n"
                                                        "GET /xq2/buy.php?id=%s&time=%d&region=%d&host=%d&item=%d&point=%d&ip=%s\r\n",
                                                        MAIN_D->get_php_ip(),
                                                        rawurlencode(me->get_id()), time(), MAIN_D->get_region(), MAIN_D->get_host(), file->get_item_number(), price, get_ip_name(me))); // 扣点！
                }
                else if (me->get_pay_money_buy_item() == 8 && me->get_pay_type() == 1) // 通过点数Mua道具成功！
                {
                        me->set_pay_money_buy_item(0); // 取消通过点数Mua道具
                        me->set_pay_type(0);

                        if (!stringp(file = who->get_2(sprintf("good.%02d", what))))
                        {
                                log_file("buyitem.dat", sprintf("%s %s(%d) không có đối tượng mua\n", short_time(), me->get_id(), me->get_number()));
                                notify(who->get_name() + "Không có đồ vật này");
                                return 1;
                        }
                        if ((price = file->get_item_value()) < 1)
                        {
                                log_file("buyitem.dat", sprintf("%s %s(%d) mua thương phẩm không đúng\n", short_time(), me->get_id(), me->get_number()));
                                notify(who->get_name() + "Không thèm giao dịch với bạn");
                                return 1;
                        }

                        if ((amount = USER_INVENTORY_D->can_carry_3(me, load_object(file))) < 1)
                        {
                                log_file("buyitem.dat", sprintf("%s %s(%d) mua không đủ không vị\n", short_time(), me->get_id(), me->get_number()));
                                notify("Hành trang không đủ chỗ");
                                return 1;
                        }
                        if (total > amount)
                                total = amount;

                        price *= total;

                        if (file->is_combined())
                        {
                                if (amount = USER_INVENTORY_D->carry_combined_item(me, load_object(file), total))
                                {
                                        item = new (file);
                                        item->set_hide(0);
                                        item->set_amount(amount);
                                        count = "/sys/sys/count"->add_buy_count(1);
                                        itemid = "/sys/sys/id"->add_max_itemid(1);
                                        item->set_user_id(sprintf("#%d#", itemid));
                                        //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                                        result = sprintf("Đếm mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                        //"/sys/user/cmd"->log_item(result);
                                        if (p = item->move2(me))
                                        {
                                                item->add_to_user(p);
                                        }
                                        else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                        {
                                                item->add_to_scene(z, p / 1000, p % 1000);
                                        }
                                }
                        }
                        else
                                for (i = 0; i < total; i++)
                                {
                                        item = new (file);
                                        item->set_hide(0);
                                        count = "/sys/sys/count"->add_buy_count(1);
                                        itemid = "/sys/sys/id"->add_max_itemid(1);
                                        item->set_user_id(sprintf("#%d#", itemid));
                                        //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                                        result = sprintf("Đếm mua @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), 1, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                        //"/sys/user/cmd"->log_item(result);
                                        if (p = item->move2(me))
                                        {
                                                item->add_to_user(p);
                                        }
                                        else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                                        {
                                                item->add_to_scene(z, p / 1000, p % 1000);
                                        }
                                }
                        log_file("buyitem.dat", sprintf("%s %s(%d) Mua %s thành công %d %d\n", short_time(), me->get_id(), me->get_number(), file->get_name(), total, price));
                        tell_user(me, " %s đã bán cho bạn %s .", who->get_name(), file->get_name());
                }
        }

        return 1;
}
//摆摊Mua物品 返回实际Mua数量
int buy_store_item(object me, object who, object item, int total, int pos)
{
        object item2;
        int amount, p, z, y, x;
        string legend;

        z = get_z(me);
        x = get_x(me);
        y = get_y(me);
        if (item->get_bind() == 2 || item->get_bind() == 3 || item->get_bind() == 4)
        {
                notify("đã phong ấn, không thể mua");
                return 0;
        }
        if ((amount = USER_INVENTORY_D->can_carry_3(me, item)) < 1)
        {
                notify("Hành trang không đủ chỗ");
                return 0;
        }
        if (total > amount)
                total = amount;

        if (item->is_combined()) // total 不能超过 get_amount()
        {
                if (total > item->get_amount())
                        total = item->get_amount();
        }
        else
                total = 1; // 非叠加物品数量为 1

        if (item->is_record())
        {
                legend = sprintf("Bán hàng rong %s,%d,%s,%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), who->get_number(), get_ip_name(who), who->get_id(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), total, item->get_user_id(), get_z(who), get_x(who), get_y(who));
                "/sys/user/cmd"->log_item(legend);
        }
        if (item->is_combined() && (item->get_max_combined() > 1))
        {
                if (amount = USER_INVENTORY_D->carry_combined_item(me, item, total))
                {
                        item2 = new (get_file_name(item));
                        if (item->get("special"))
                                item2->set("special", item->get("special"));
                        item2->set_amount(amount);

                        if (p = item2->move2(me))
                        {
                                item2->add_to_user(p);
                        }
                        else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                        {
                                item2->add_to_scene(z, p / 1000, p % 1000);
                        }
                }

                if (!item->add_amount(-total))
                        who->delete_store(sprintf("%02d", pos));
        }
        else
        {
                send_user(who, "%c%d", 0x2d, getoid(item));
                if (p = item->move2(me))
                {
                        item->add_to_user(p);
                }
                else if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                {
                        item->add_to_scene(z, p / 1000, p % 1000);
                }
                who->delete_store(sprintf("%02d", pos));
        }

        return total;
}
//摆摊Mua宠物????
int buy_store_pet(object me, object who, object pet, int pos)
{
        if (pet->get_owner() != who)
                return 0;
        if (NPC_PET_D->can_carry(me, pet) != 1)
        {
                send_user(me, "%c%s", '!', "Bạn không thể mang theo Bảo thú này");
                return 0;
        }
        if (me->get_beast_amount() + 1 > me->get_beast_max_amount())
        {
                send_user(me, "%c%s", '!', "Bạn không thể mang theo nhiều Bảo thú");
                return 0;
        }
        if (pet->get("show"))
                USER_BEAST_D->hide(who, pet);
        USER_BEAST_D->remove_from_user(who, pet);
        pet->set_owner(0);
        pet->set_owner(me);
        me->add_beast(pet);
        pet->add_faith(-20);
        pet->send_info();
        pet->save();
        pet->delete ("store");
        return 1;
}