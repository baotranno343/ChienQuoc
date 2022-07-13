#include <item.h>
#include <ansi.h>
#include <equip.h>
#include <action.h>

// 函数：命令处理
int main(object me, string arg)
{
        mapping list;
        object city, who, pawn, item, pet;
        string *key, file, name, dtype;
        int what, tax, i, size, price;
        if (gone_time(me->get_time("list")) < 1) // 时间限制
        {
                me->set_time("list", time());
                return 1;
        }
        me->set_time("list", time());

        if (!arg)
                return 1;

        if (sscanf(arg, "%s,%d", arg, what) == 2)
                ; // what 当铺号
        if (!objectp(who = find_char(arg)))
                return 1;
        if (/*!who->is_seller() && */ who->is_seller() > 6999 && !who->is_seller_2() && !who->is_trader() && !who->is_store_open() && !who->is_bonus_seller() && !who->is_item_seller())
                return 1;

        if ((time() - me->get("buy_time") > 300) && !inside_screen_2(me, who))
        {
                notify("Bạn cách %s quá xa rồi.", who->get_name());
                return 1;
        }
        "/quest/help"->send_help_tips(me, 5);
        if (who->is_seller() || who->is_seller_2())
        {
                if (!mapp(list = who->get_2("good")) || !(size = sizeof(key = keys(list))))
                {
                        notify(who->get_name() + " Tất cả đều đã bán hết.");
                        return 1;
                }

                if (city = CITY_D->get_city_object(who))
                {
                        if (me->get_city_name() == who->get_city_name())
                                tax = city->get_buy_tax();
                        else
                                tax = city->get_buy_tax_2();
                }
                tax = 0;
                if (size)
                        key = sort_array(key, 1);
                send_user(me, "%c%c%c%d%s", 0x28, 0, 0, getoid(who), sprintf("%-12s%s", who->get_name(), ""));
                for (i = 0; i < size; i++)
                {
                        file = list[key[i]];
                        price = who->get_2(sprintf("price.%s", key[i]));
                        if (!price)
                                price = file->get_value();
                        dtype = file[ < 4.. < 1];
                        if (file->get_item_type() == ITEM_TYPE_DIAMOND_3 && who->get_save_2("diamond." + dtype) >= 100)
                                send_user(me, "%c%c%d%w%w%c%c%s", 0x28, to_int(key[i]), price * who->get_save_2("diamond." + dtype) / 100,
                                          file->get_picid_2(), file->get_amount(), 0, file->get_item_color(), file->get_name());
                        else
                                send_user(me, "%c%c%d%w%w%c%c%s", 0x28, to_int(key[i]), price * (100 + tax) / 100,
                                          file->get_picid_2(), file->get_amount(), 0, file->get_item_color(), file->get_name());
                }
        }
        else if (who->is_trader() && (me->is_businessman() || me->get_save_2("mastertask.type") == 11 || me->get_save_2("orgtask3.type")))
        {
                if (!mapp(list = who->get_2("good")) || !(size = sizeof(key = keys(list))))
                {
                        notify(who->get_name() + " Tất cả đều đã bán hết.");
                        return 1;
                }
                if (size)
                        key = sort_array(key, 1);
                send_user(me, "%c%c%c%d%s", 0x28, 0, 0, getoid(who), sprintf("%-12s%s", who->get_name(), ""));
                for (i = 0; i < size; i++)
                {
                        file = list[key[i]];
                        send_user(me, "%c%c%d%w%w%c%c%s", 0x28, to_int(key[i]),
                                  file->get_buy_price() + file->get_buy_range() * who->get_buy_rate() / 1000,
                                  file->get_picid_2(), file->get_amount(), 0, file->get_item_color(), file->get_name());
                }
        }
        else if (who->is_store_open())
        {
                if (!mapp(list = who->get_store_dbase()) || !(size = sizeof(key = keys(list))))
                {
                        send_user(me, "%c%c%c%d%s", 0x28, 0, 1, who->get_number(), sprintf("%-12s%s", who->get_name(), who->get_store_name()));
                        return 1;
                }
                if (size)
                        key = sort_array(key, 1);
                send_user(me, "%c%c%c%d%s", 0x28, 0, 1, who->get_number(), sprintf("%-12s%s", who->get_name(), who->get_store_name()));
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
                                                  pet->get_char_picid(), 1, pet->get_blood(), 0, pet->get_firstname());
                        }
                }
        }
        else if (who->is_bonus_seller())
        {
                if (!mapp(list = who->get_2("good")) || !(size = sizeof(key = keys(list))))
                {
                        notify(who->get_name() + " Tất cả đều đã bán hết.");
                        return 1;
                }

                if (size)
                        key = sort_array(key, 1);
                send_user(me, "%c%c%c%d%s", 0x29, 0, 0, getoid(who), sprintf("%-12s%s", who->get_name(), ""));
                for (i = 0; i < size; i++)
                {
                        file = list[key[i]];
                        send_user(me, "%c%c%d%w%w%c%c%s", 0x29, to_int(key[i]), file->get_bonus_value() / 10,
                                  file->get_picid_2(), file->get_amount(), 0, file->get_item_color(), file->get_name());
                }
        }
        else if (who->is_item_seller()) // 用点卡买道具！！
        {
                // 目前抄普通小贩 is_seller()，只是取消 tax 而已
                // 并且，item 要提供其点数，以及其唯一标识, 这里借用：get_value(), 8888

                if (!mapp(list = who->get_2("good")) || !(size = sizeof(key = keys(list))))
                {
                        notify(who->get_name() + " Tất cả đều đã bán hết.");
                        return 1;
                }

                if (size)
                        key = sort_array(key, 1);
                send_user(me, "%c%c%c%d%s", 0x29, 0, 0, getoid(who), sprintf("%-12s%s", who->get_name(), ""));
                for (i = 0; i < size; i++)
                {
                        file = list[key[i]];
                        send_user(me, "%c%c%d%w%w%c%c%s", 0x29, to_int(key[i]), file->get_item_value(),
                                  file->get_picid_2(), file->get_amount(), 0, file->get_item_color(), file->get_name());
                }
        }
        return 1;
}
