
#include <ansi.h>
#include <item.h>
#include <equip.h>
#include <effect.h>

#define MAX_PAWN 49 // 典当物品限制

int do_list(object me, string name, int which);
int do_pawn(object me, string name, string what, int amount, int which3);
int do_redeem(object me, string name, int which2, int amount, int which3);
int do_move(object me, string name, int which2, int which3);
int do_move_2(object me, string name, int which2, int which3);
int expand_pawn(object me, string name, int which);

// 函数:命令处理
int main(object me, string arg)
{
        string name, what;
        int which, which2, which3, amount;
        if (is_gm(me))
                return 1;
        if (gone_time(me->get_time("pawn")) < 1) // 时间限制
        {
                me->set_time("pawn", time());
                return 1;
        }
        me->set_time("pawn", time());
        if (arg == "close")
        {
                if (me->get("pawn_time") && get_effect(me, EFFECT_PROGRESS2))
                {
                        me->set("pawn_time", 0);
                        set_effect(me, EFFECT_PROGRESS2, 1);
                }
                return 1;
        }
        if (!arg)
                return 1;
        else if (sscanf(arg, "+ %s %s#%d %d", name, what, amount, which3) == 4)
                return do_pawn(me, name, what + "#", amount, which3);
        else if (sscanf(arg, "- %s %d#%d %d", name, which2, amount, which3) == 4)
                return do_redeem(me, name, which2, amount, which3);
        else if (sscanf(arg, "> %s %d %d", name, which2, which3) == 3)
                return do_move(me, name, which2, which3);
        else if (sscanf(arg, "& %s %d %d", name, which2, which3) == 3)
                return do_move_2(me, name, which2, which3);
        else if (sscanf(arg, "expand %s %d", name, which) == 2)
                return expand_pawn(me, name, which);
        else if (sscanf(arg, "%s %d", name, which) == 2)
                return do_list(me, name, which);

        return 1;
}

// 函数:当铺列示
int do_list(object me, string name, int which)
{
        mapping list;
        object who, pawn;
        string *key, file, id, prop;
        int which2, which3, total, amount, point;
        int z, x, y, p, i, size, flag;

        if (!objectp(who = find_char(name)))
                return 1;

        if (!who->is_banker())
                return 1;
        // if ( who->get_save("quankho") < 1 ) return 1;

        if ((time() - me->get("pawn_time") > 300) && !inside_screen_2(me, who))
        {
                notify("Bạn cách %s quá xa rồi.", who->get_name());
                return 1;
        }
        if (which == 0)
        {

                send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
                          sprintf("%s:\n    " + "/quest/word"->get_normal_word(who) + "\n" ESC "Ta muốn sử dụng kho\npawn %x# 1\n" ESC "Ta muốn mở rộng kho\npawn expand %x# 0\n" ESC "Ta chỉ đến xem\nCLOSE\n", who->get_name(), getoid(who), getoid(who)));

                return 1;
        }

        me->to_front_eachother(who);

        which--;
        size = me->get_max_pawn_size();

        if (which < 0 || which >= size)
        {
                notify("Bạn trước mắt chỉ có thể sử dụng %d kho", size);
                return 1;
        }

        me->set("pawn#", which);

        if (!mapp(list = me->get_pawn(sprintf("%02d", which)))) // 使用内存缓存？
        {
                pawn = new (PAWN);
                pawn->set_id(which);
                pawn->set_owner(me->get_id());
                list = pawn->get_pawn();
                destruct(pawn);
                me->set_pawn(sprintf("%02d", which), list); // 载入内存缓存
        }

        which++;
        send_user(me, "%c%c%c%d%c", 0x5b, which, 0, getoid(who), size);

        if (!mapp(list) || !(size = sizeof(key = keys(list))))
                return 1;

        if (size)
                key = sort_array(key, 1);

        for (i = 0; i < size; i++)
        {
                if (!stringp(name = list[key[i]]))
                        continue;
                if (!sscanf(name, "%s;%d;%*s", file, total) || !load_object(file))
                        continue;
                if (flag = file->get_equip_type())
                {
                        if (!sscanf(name, "%s=:%d,%*s", prop, p))
                                p = 0;
                        if (!sscanf(name, "%s+:%d,%*s", prop, point))
                                point = 0;
                        id = "";
                        if (point)
                                id = sprintf("%+d", point);
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, to_int(key[i]),
                                  file->get_picid_2(), total, 0, p, file->get_name() + id);
                }
                else if (file->is_diamond_2())
                {
                        if (!sscanf(name, "%s;%d;%d;%*s", file, total, point))
                                point = 0;
                        id = "";
                        if (point)
                                id = sprintf("%+d", point);
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, to_int(key[i]),
                                  file->get_picid_2(), total, 0, 0, file->get_name() + id);
                }
                else
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, to_int(key[i]),
                                  file->get_picid_2(), total, 0, 0, file->get_name());
        }

        return 1;
}

// 函数:Tồn nhập当铺
int do_pawn(object me, string name, string what, int amount, int which3)
{
        mapping list;
        object who, pawn, item;
        string *key, file, id, prop, result, legend, *tach_prop;
        int which, which2, total, point, no_give;
        int use, maxuse, locktime, lockutil;
        int z, x, y, p, i, size, flag;

        if (!objectp(who = find_char(name)))
                return 1;

        if (!who->is_banker())
                return 1;
        // if ( who->get_save("quankho") < 1 ) return 1;

        if ((time() - me->get("pawn_time") > 300) && !inside_screen_2(me, who))
        {
                notify("Bạn cách %s quá xa rồi.", who->get_name());
                return 1;
        }

        me->to_front_eachother(who);

        if (!(item = present(what, me, 1, MAX_CARRY * 4)))
                return 1; // present(what, me, 1, MAX_CARRY)

        if (item->get_value() <= 1 || item->get_no_drop() || item->get_no_get())
        {
                notify(item->get_name() + " không thể cầm");
                send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
                return 1;
        }
        /*              if( item->is_locked() )
                {
                        notify( item->get_name() + "已经锁定，不能典当。" );
                        send_user( me, "%c%d%c", 0x4e, getoid(item), item->get_amount() );    // 补发消息
                        return 1;
                }       */
        if (me->get_store(sprintf("%02d", get_d(item))))
        {
                notify(item->get_name() + " đã muốn bán, không thể cầm");
                send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
                return 1;
        }

        if (amount < 1)
        {
                send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
                return 1;
        }
        else if (amount > item->get_amount())
                amount = item->get_amount();

        if (which3 < 1 || which3 > MAX_PAWN)
        {
                send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
                return 1;
        }

        which = me->get("pawn#");
        pawn = new (PAWN);
        pawn->set_id(which);
        pawn->set_owner(me->get_id());
        if (pawn->get_owner() != me->get_id())
        {
                log_file("pawnerror.txt", sprintf("%s %s(%d) %s\n", short_time(), me->get_id(), me->get_number(), pawn->get_owner()));
                destruct(pawn);
                return 1;
        }
        if (mapp(list = pawn->get_pawn()))
        {
                size = sizeof(key = keys(list));
                if (size)
                        key = sort_array(key, 1);
        }
        else
        {
                list = ([]);
                size = 0;
                key = ({});
        }
        /*
                if( size >= MAX_PAWN )
                {
                        notify( "最多只能典当 %d 个物品。", MAX_PAWN );
                        send_user( me, "%c%d%c", 0x4e, getoid(item), item->get_amount() );    // 补发消息
                        destruct(pawn);  return 1;
                }
*/
        which++;

        /*              for( i = 0; i < size; i ++ ) if( to_int( key[i] ) != i + 1 ) break;
                which ++;  which3 = i + 1;    */
        if (stringp(name = list[sprintf("%02d", which3)]) && sscanf(name, "%s;%d;%s", file, total, prop) && load_object(file))
        {
                tach_prop = explode(prop, ";");

                if ((file == get_file_name(item)) && item->get_max_combined() > 1 && to_int(tach_prop[0]) == item->get_no_give())
                {
                        //  printf("tach Prop:" + tach_prop[0]);
                        // printf("file: " + file + "total: " + total + " prop: " + prop + " name: " + name);
                        if (total + amount <= item->get_max_combined())
                        {
                                total += amount;
                        }
                        else
                        {
                                amount = item->get_max_combined() - total;
                                total = item->get_max_combined();
                        }
                        if (item->is_record())
                        {
                                legend = sprintf("Tồn nhập @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                //"/sys/user/cmd"->log_item(legend);
                        }
                        if (amount < item->get_amount())
                                item->add_amount(-amount);
                        else
                        {
                                item->remove_from_user();
                                destruct(item);
                        }
                        name = sprintf("%s;%d;%s", file, total, prop);
                        pawn->set_pawn(sprintf("%02d", which3), name);
                        pawn->save();
                        me->set_pawn(sprintf("%02d", me->get("pawn#")), pawn->get_pawn()); // 更新内存缓存
                        destruct(pawn);
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which3,
                                  file->get_picid_2(), total, 0, 0, file->get_name());
                        return 1;
                }
                else
                {
                        send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
                        destruct(pawn);
                        return 1;
                }
        }

        file = get_file_name(item);
        total = item->get_amount();
        if (!load_object(file))
        {
                log_file("runtime.txt", sprintf("error file=%s name=%s", file, item->get_name()));
                return 1;
        }

        if (!stringp(id = item->get_user_id()))
                id = "-";
        locktime = item->get_lock_time();
        lockutil = item->get_lock_until();
        no_give = item->get_no_give();
        switch (item->get_item_type())
        {
        case ITEM_TYPE_EQUIP:
                prop = sprintf("%s;%d;%d;%d;%d;%s;[%s]%d,%d",
                               file, amount, no_give, item->get_lasting(), item->get_max_lasting(), ITEM_EQUIP_D->get_save_prop_string_2(item), id, locktime, lockutil);
                break;

        case ITEM_TYPE_TALISMAN:
                switch (item->get_talisman_type())
                {
                default:
                        point = 0;
                        break;
                case 2:
                        point = item->get_hp();
                        break; // 九龙神火罩
                case 9:
                        point = item->get_heart_sec();
                        break; // 招魂幡
                }
                prop = sprintf("%s;%d;%d;%d;%d;%d;[%s]%d,%d",
                               file, amount, no_give, item->get_lasting(), item->get_max_lasting(), point, id, locktime, lockutil);
                break;

        case ITEM_TYPE_POISON_2:
                prop = sprintf("%s;%d;%d;[%s]%d,%d",
                               file, amount, item->get_poison(), id, locktime, lockutil);
                break;

        case ITEM_TYPE_TREASURE:
                prop = sprintf("%s;%d;%d;%d;%d;[%s]%d,%d",
                               file, amount, item->get_map_z(), item->get_map_x(), item->get_map_y(), id, locktime, lockutil);
                break;

        case ITEM_TYPE_DIAMOND_2:
                prop = sprintf("%s;%d;%d;[%s]%d,%d",
                               file, amount, item->get_item_level(), id, locktime, lockutil);
                break;

        case ITEM_TYPE_POTENTIAL:
                prop = sprintf("%s;%d;%d;[%s]%d,%d",
                               file, amount, item->get_potential(), id, locktime, lockutil);
                break;
        case ITEM_TYPE_SPECIAL:
                prop = sprintf("%s;%d;%s;[%s]%d,%d", file, amount, item->get("special"), id, locktime, lockutil);
                break;
        case ITEM_TYPE_KIMNGUYENBAO:
                prop = sprintf("%s;%d;%d;[%s]%d,%d",
                               file, amount, "sys/sys/test_db"->get_yuanbao(item), id, locktime, lockutil);
                break;
        case ITEM_TYPE_CHIENTICH:
                prop = sprintf("%s;%d;%d;[%s]%d,%d",
                               file, amount, item->get_save_2("changping.score"), id, locktime, lockutil);
                break;
        case ITEM_TYPE_DIAMOND_3:
                prop = sprintf("%s;%d;%d;[%s]%d,%d", file, item->get_level(), no_give, id, locktime, lockutil);
                break;
        default:
                prop = sprintf("%s;%d;%d;[%s]%d,%d", file, amount, no_give, id, locktime, lockutil);
                break;
        case ITEM_TYPE_DIAMOND_100:
                prop = sprintf("%s;%d;%d;[%s]%d,%d", file, item->get_level(), no_give, id, locktime, lockutil);
                break;
        }

        //		prop = "/sys/item/item"->get_pawn_save_string(item);
        // tell_user(me, prop);
        if (item->get_amount())
                result = sprintf("Bạn lấy %s cất vào nơi %s .", item->get_name(), who->get_name());
        else
                result = sprintf("Bạn lấy %s cất vào nơi %s .", item->get_name(), who->get_name());
        notify(result);
        write_user(me, ECHO + result);

        p = item->get_item_color();
        point = item->get_item_level();
        if (item->is_record())
        {
                legend = sprintf("Tồn nhập @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                //"/sys/user/cmd"->log_item(legend);
        }
        if (total)
                item->add_amount(-amount);
        else
        {
                item->remove_from_user();
                destruct(item);
        }

        pawn->set_pawn(sprintf("%02d", which3), prop);

        if (flag = file->get_equip_type())
        {
                id = "";
                if (point)
                        id = sprintf("%+d", point);
                send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which3,
                          file->get_picid_2(), amount, 0, p, file->get_name() + id);
        }
        else if (file->is_diamond_2())
        {
                id = "";
                if (point)
                        id = sprintf("%+d", point);
                send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which3,
                          file->get_picid_2(), amount, 0, 0, file->get_name() + id);
        }
        else
                send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which3,
                          file->get_picid_2(), amount, 0, 0, file->get_name());

        pawn->save();
        me->set_pawn(sprintf("%02d", me->get("pawn#")), pawn->get_pawn()); // 更新内存缓存
        destruct(pawn);

        return 1;
}

// 函数:当铺取出
int do_redeem(object me, string name, int which2, int amount, int which3)
{
        mapping list;
        object who, pawn, item;
        string file, id, prop, result, special, legend;
        int which, amount2, total, point, no_give;
        int use, maxuse, locktime, lockutil;
        int z, x, y, p, i, size, flag, bag, b, c, d;
        if (!objectp(who = find_char(name)))
                return 1;
        bag = me->have_bag();
        b = bag % 100;
        c = (bag / 100) % 100;
        d = bag / 10000;
        if (b > 0 && me->get_bag1_time() > 0 && time() > me->get_bag1_time())
                b = 0;
        if (c > 0 && me->get_bag2_time() > 0 && time() > me->get_bag2_time())
                c = 0;
        if (d > 0 && me->get_bag3_time() > 0 && time() > me->get_bag3_time())
                d = 0;
        if (me->get_reincarnation())
                b = MAX_CARRY;
        if (!who->is_banker())
                return 1;
        // if ( who->get_save("quankho") < 1 ) return 1;
        //         if (which3%MAX_CARRY==0) return 1;
        //  判断取出位置是否有效
        if (which3 >= MAX_CARRY * 3)
        {
                if (which3 > MAX_CARRY * 3 + d)
                        return 1;
        }
        else if (which3 >= MAX_CARRY * 2)
        {
                if (which3 > MAX_CARRY * 2 + c)
                        return 1;
        }
        else if (which3 >= MAX_CARRY)
        {
                if (which3 > MAX_CARRY + b)
                        return 1;
        }

        if ((time() - me->get("pawn_time") > 300) && !inside_screen_2(me, who))
        {
                notify("Bạn cách %s quá xa rồi.", who->get_name());
                return 1;
        }

        me->to_front_eachother(who);

        if (which2 < 1 || which2 > MAX_PAWN)
                return 1;
        //              if( which3 < 1 || which3 > MAX_CARRY ) return 1;
        //              if( amount < 1 ) return 1;

        which = me->get("pawn#");
        pawn = new (PAWN);
        pawn->set_id(which);
        pawn->set_owner(me->get_id());
        if (pawn->get_owner() != me->get_id())
        {
                log_file("pawnerror.txt", sprintf("%s %s(%d) %s\n", short_time(), me->get_id(), me->get_number(), pawn->get_owner()));
                destruct(pawn);
                return 1;
        }
        if (!mapp(list = pawn->get_pawn()) || !sizeof(list) || !stringp(name = list[sprintf("%02d", which2)]) || !sscanf(name, "%s;%d;%*s", file, total) || !load_object(file))
        {
                destruct(pawn);
                return 1;
        }
        which++;

        if (which3 < 1 || which3 > MAX_CARRY * 4 || amount < 1) // 补发消息
        {
                if (flag = file->get_equip_type())
                {
                        if (!sscanf(name, "%s=:%d,%*s", prop, p))
                                p = 0;
                        if (!sscanf(name, "%s+:%d,%*s", prop, point))
                                point = 0;
                        id = "";
                        if (point)
                                id = sprintf("%+d", point);
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which2,
                                  file->get_picid_2(), total, 0, p, file->get_name() + id);
                }
                else if (file->is_diamond_2())
                {
                        if (!sscanf(name, "%s;%d;%d;%*s", file, total, point))
                                point = 0;
                        id = "";
                        if (point)
                                id = sprintf("%+d", point);
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which2,
                                  file->get_picid_2(), total, 0, 0, file->get_name() + id);
                }
                else
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which2,
                                  file->get_picid_2(), total, 0, 0, file->get_name());
                destruct(pawn);
                return 1;
        }

        if ((amount2 = USER_INVENTORY_D->can_carry_3(me, load_object(file))) < 1 || (file->is_combined() && amount > amount2))
        {
                notify("Hành trang không đủ chỗ");
                destruct(pawn);
                return 1;
        }
        switch (file->get_item_type())
        {
        case ITEM_TYPE_EQUIP:
                if (sscanf(name, "%s;%d;%d;%d;%d;%s;[%s]%d,%d", file, total, no_give, use, maxuse, prop, id, locktime, lockutil) != 9)
                {
                        pawn->delete_pawn(sprintf("%02d", which2));
                        send_user(me, "%c%c%c%c", 0x5b, which, which2, 0);
                        pawn->save();
                        destruct(pawn);
                        return 1;
                }
                item = new (file);
                if (total)
                {
                        if (amount > total)
                                amount = total;
                        item->set_amount(amount);
                }
                if (no_give == 1)
                {
                        item->set_no_give(no_give);
                        item->set_no_sell(no_give);
                }
                item->set_max_lasting(maxuse);
                item->set_lasting(use);

                ITEM_EQUIP_D->set_prop_baseon_string(item, prop);

                break;

        case ITEM_TYPE_TALISMAN:
                if (sscanf(name, "%s;%d;%d;%d;%d;%d;[%s]%d,%d", file, total, no_give, use, maxuse, point, id, locktime, lockutil) != 9)
                {
                        pawn->delete_pawn(sprintf("%02d", which2));
                        send_user(me, "%c%c%c%c", 0x5b, which, which2, 0);
                        pawn->save();
                        destruct(pawn);
                        return 1;
                }
                item = new (file);
                if (total)
                {
                        if (amount > total)
                                amount = total;
                        item->set_amount(amount);
                }
                if (no_give == 1)
                {
                        item->set_no_give(no_give);
                        item->set_no_sell(no_give);
                }
                item->set_max_lasting(maxuse);
                item->set_lasting(use);

                switch (item->get_talisman_type())
                {
                default:
                        break;
                case 2:
                        item->set_hp(point);
                        break; // 九龙神火罩
                case 9:
                        item->set_heart_sec(point);
                        break; // 招魂幡
                }

                break;

        case ITEM_TYPE_POISON_2:
                if (sscanf(name, "%s;%d;%d;[%s]%d,%d", file, total, point, id, locktime, lockutil) != 6)
                {
                        pawn->delete_pawn(sprintf("%02d", which2));
                        send_user(me, "%c%c%c%c", 0x5b, which, which2, 0);
                        pawn->save();
                        destruct(pawn);
                        return 1;
                }
                item = new (file);
                if (total)
                {
                        if (amount > total)
                                amount = total;
                        item->set_amount(amount);
                }
                item->set_poison(point);

                break;

        case ITEM_TYPE_TREASURE:
                if (sscanf(name, "%s;%d;%d;%d;%d;[%s]%d,%d", file, total, z, x, y, id, locktime, lockutil) != 8)
                {
                        pawn->delete_pawn(sprintf("%02d", which2));
                        send_user(me, "%c%c%c%c", 0x5b, which, which2, 0);
                        pawn->save();
                        destruct(pawn);
                        return 1;
                }
                item = new (file);
                if (total)
                {
                        if (amount > total)
                                amount = total;
                        item->set_amount(amount);
                }
                item->set_map_z(z);
                item->set_map_x(x);
                item->set_map_y(y);

                break;

        case ITEM_TYPE_DIAMOND_2:
                if (sscanf(name, "%s;%d;%d;[%s]%d,%d", file, total, point, id, locktime, lockutil) != 6)
                {
                        pawn->delete_pawn(sprintf("%02d", which2));
                        send_user(me, "%c%c%c%c", 0x5b, which, which2, 0);
                        pawn->save();
                        destruct(pawn);
                        return 1;
                }
                item = new (file);
                if (total)
                {
                        if (amount > total)
                                amount = total;
                        item->set_amount(amount);
                }
                item->set_item_level(point);

                break;

        case ITEM_TYPE_POTENTIAL:
                if (sscanf(name, "%s;%d;%d;[%s]%d,%d", file, total, point, id, locktime, lockutil) != 6)
                {
                        pawn->delete_pawn(sprintf("%02d", which2));
                        send_user(me, "%c%c%c%c", 0x5b, which, which2, 0);
                        pawn->save();
                        destruct(pawn);
                        return 1;
                }
                item = new (file);
                if (total)
                {
                        if (amount > total)
                                amount = total;
                        item->set_amount(amount);
                }
                item->set_potential(point);

                break;
        case ITEM_TYPE_SPECIAL:
                if (sscanf(name, "%s;%d;%s;[%s]%d,%d", file, total, special, id, locktime, lockutil) != 6)
                {
                        pawn->delete_pawn(sprintf("%02d", which2));
                        send_user(me, "%c%c%c%c", 0x5b, which, which2, 0);
                        pawn->save();
                        destruct(pawn);
                        return 1;
                }
                item = new (file);
                if (total)
                {
                        if (amount > total)
                                amount = total;
                        item->set_amount(amount);
                }
                item->set("special", special);
                break;
        case ITEM_TYPE_KIMNGUYENBAO:
                if (sscanf(name, "%s;%d;%d;[%s]%d,%d", file, total, point, id, locktime, lockutil) != 6)
                {
                        pawn->delete_pawn(sprintf("%02d", which2));
                        send_user(me, "%c%c%c%c", 0x5b, which, which2, 0);
                        pawn->save();
                        destruct(pawn);
                        return 1;
                }
                item = new (file);
                if (total)
                {
                        if (amount > total)
                                amount = total;
                        item->set_amount(amount);
                }
                //   item->set_potential(point);
                "sys/sys/test_db"->set_yuanbao(item, point);

                break;
        case ITEM_TYPE_CHIENTICH:
                if (sscanf(name, "%s;%d;%d;[%s]%d,%d", file, total, point, id, locktime, lockutil) != 6)
                {
                        pawn->delete_pawn(sprintf("%02d", which2));
                        send_user(me, "%c%c%c%c", 0x5b, which, which2, 0);
                        pawn->save();
                        destruct(pawn);
                        return 1;
                }
                item = new (file);
                if (total)
                {
                        if (amount > total)
                                amount = total;
                        item->set_amount(amount);
                }
                //   item->set_potential(point);
                //	"sys/sys/test_db"->set_yuanbao(item,point);
                item->set_save_2("changping.score", point);

                break;
        case ITEM_TYPE_DIAMOND_3:
                if (sscanf(name, "%s;%d;%d;[%s]%d,%d", file, total, no_give, id, locktime, lockutil) != 6)
                {
                        pawn->delete_pawn(sprintf("%02d", which2));
                        send_user(me, "%c%c%c%c", 0x5b, which, which2, 0);
                        pawn->save();
                        destruct(pawn);
                        return 1;
                }
                item = new (file);
                if (total)
                {
                        item->set_level(total);
                        amount = total;
                }
                if (no_give == 1)
                {
                        item->set_no_give(no_give);
                        item->set_no_sell(no_give);
                }
                break;
        default:
                if (sscanf(name, "%s;%d;%d;[%s]%d,%d", file, total, no_give, id, locktime, lockutil) != 6)
                {
                        pawn->delete_pawn(sprintf("%02d", which2));
                        send_user(me, "%c%c%c%c", 0x5b, which, which2, 0);
                        pawn->save();
                        destruct(pawn);
                        return 1;
                }
                item = new (file);
                if (total)
                {
                        if (amount > total)
                                amount = total;
                        item->set_amount(amount);
                }
                if (no_give == 1)
                {
                        item->set_no_give(no_give);
                        item->set_no_sell(no_give);
                }
                break;
        case ITEM_TYPE_DIAMOND_100:
                if (sscanf(name, "%s;%d;%d;[%s]%d,%d", file, total, no_give, id, locktime, lockutil) != 6)
                {
                        pawn->delete_pawn(sprintf("%02d", which2));
                        send_user(me, "%c%c%c%c", 0x5b, which, which2, 0);
                        pawn->save();
                        destruct(pawn);
                        return 1;
                }
                item = new (file);
                if (total)
                {
                        item->set_level(total);
                        amount = total;
                }
                if (no_give == 1)
                {
                        item->set_no_give(no_give);
                        item->set_no_sell(no_give);
                }
                break;
        }

        if (lockutil && gone_time(locktime) > lockutil) // 计算是否锁定
        {
                locktime = 0;
                lockutil = 0;
        }
        item->set_user_id(id);
        item->set_lock_time(locktime);
        item->set_lock_until(lockutil);

        if (amount < total)
        {
                switch (item->get_item_type())
                {
                case ITEM_TYPE_EQUIP:
                        prop = sprintf("%s;%d;%d;%d;%d;%s;[%s]%d,%d", file, total - amount, no_give, use, maxuse, prop, id, locktime, lockutil);
                        break;

                case ITEM_TYPE_TALISMAN:
                        prop = sprintf("%s;%d;%d;%d;%d;%d;[%s]%d,%d", file, total - amount, no_give, use, maxuse, point, id, locktime, lockutil);
                        break;

                case ITEM_TYPE_POISON_2:
                        prop = sprintf("%s;%d;%d;[%s]%d,%d", file, total - amount, point, id, locktime, lockutil);
                        break;

                case ITEM_TYPE_TREASURE:
                        prop = sprintf("%s;%d;%d;%d;%d;[%s]%d,%d", file, total - amount, z, x, y, id, locktime, lockutil);
                        break;

                case ITEM_TYPE_DIAMOND_2:
                        prop = sprintf("%s;%d;%d;[%s]%d,%d", file, total - amount, point, id, locktime, lockutil);
                        break;

                case ITEM_TYPE_POTENTIAL:
                        prop = sprintf("%s;%d;%d;[%s]%d,%d", file, total - amount, point, id, locktime, lockutil);
                        break;
                case ITEM_TYPE_SPECIAL:
                        prop = sprintf("%s;%d;%s;[%s]%d,%d", file, total - amount, special, id, locktime, lockutil);
                        break;
                case ITEM_TYPE_KIMNGUYENBAO:
                        prop = sprintf("%s;%d;%d;[%s]%d,%d", file, total - amount, point, id, locktime, lockutil);
                        break;
                case ITEM_TYPE_CHIENTICH:
                        prop = sprintf("%s;%d;%d;[%s]%d,%d", file, total - amount, point, id, locktime, lockutil);
                        break;
                case ITEM_TYPE_DIAMOND_3:
                        prop = sprintf("%s;%d;%d;[%s]%d,%d", file, item->get_level(), no_give, id, locktime, lockutil);
                        break;
                default:
                        prop = sprintf("%s;%d;%d;[%s]%d,%d", file, total - amount, no_give, id, locktime, lockutil);
                        break;
                        /*  case ITEM_TYPE_DIAMOND_100:
                                prop = sprintf( "%s;%d;[%s]%d,%d", file, item->get_level(), id, locktime, lockutil );
                                break;     */
                }

                pawn->set_pawn(sprintf("%02d", which2), prop);
                p = item->get_item_color();
                point = item->get_item_level();

                if (flag = item->get_equip_type())
                {
                        id = "";
                        if (point)
                                id = sprintf("%+d", point);
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which2,
                                  item->get_picid_2(), total - amount, 0, p, item->get_name() + id);
                }
                else if (item->is_diamond_2())
                {
                        id = "";
                        if (point)
                                id = sprintf("%+d", point);
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which2,
                                  item->get_picid_2(), total - amount, 0, 0, item->get_name() + id);
                }
                else
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which2,
                                  item->get_picid_2(), total - amount, 0, 0, item->get_name());
        }
        else
        {
                pawn->delete_pawn(sprintf("%02d", which2));
                send_user(me, "%c%c%c%c", 0x5b, which, which2, 0);
        }

        pawn->save();
        me->set_pawn(sprintf("%02d", me->get("pawn#")), pawn->get_pawn()); // 更新内存缓存
        destruct(pawn);

        if (item->get_amount())
                result = sprintf("Bạn từ nơi %s lấy ra %s .", who->get_name(), item->get_name());
        else
                result = sprintf("Bạn từ nơi %s lấy ra %s .", who->get_name(), item->get_name());
        notify(result);
        write_user(me, ECHO + result);
        if (item->is_record())
        {
                legend = sprintf("取出 @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                //"/sys/user/cmd"->log_item(legend);
        }
        z = get_z(me);

        if (item->is_combined())
        {
                amount2 = USER_INVENTORY_D->carry_combined_item(me, item, amount);

                if (amount2 > 0 && item->set_amount(amount2))
                {
                        if ((p = item->move(me, which3)) || (p = item->move2(me)))
                                item->add_to_user(p);
                        else if (p = get_valid_xy(z, get_x(me), get_y(me), IS_ITEM_BLOCK))
                        {
                                item->add_to_scene(z, p / 1000, p % 1000);
                        }
                }
                else
                        item->add_amount(-amount);
        }
        else if ((p = item->move(me, which3)) || (p = item->move2(me)))
                item->add_to_user(p);
        else if (p = get_valid_xy(z, get_x(me), get_y(me), IS_ITEM_BLOCK))
        {
                item->add_to_scene(z, p / 1000, p % 1000);
        }
        return 1;
}

// 函数:移动物品(同一当铺)
int do_move(object me, string name, int which2, int which3)
{
        mapping list;
        object who, pawn;
        string what, file, file2, id, prop;
        int which, total, amount, point;
        int z, x, y, p, i, size, flag;

        if (!objectp(who = find_char(name)))
                return 1;

        if (!who->is_banker())
                return 1;
        // if ( who->get_save("quankho") < 1 ) return 1;

        if ((time() - me->get("pawn_time") > 300) && !inside_screen_2(me, who))
        {
                notify("Bạn cách %s quá xa rồi.", who->get_name());
                return 1;
        }

        me->to_front_eachother(who);

        if (which2 < 1 || which2 > MAX_PAWN)
                return 1;
        if (which3 < 1 || which3 > MAX_PAWN)
                return 1;

        which = me->get("pawn#");
        pawn = new (PAWN);
        pawn->set_id(which);
        pawn->set_owner(me->get_id());
        if (pawn->get_owner() != me->get_id())
        {
                log_file("pawnerror.txt", sprintf("%s %s(%d) %s\n", short_time(), me->get_id(), me->get_number(), pawn->get_owner()));
                destruct(pawn);
                return 1;
        }
        if (!mapp(list = pawn->get_pawn()) || !sizeof(list) || !stringp(name = list[sprintf("%02d", which2)]) || !sscanf(name, "%s;%d;%*s", file, total) || !load_object(file))
        {
                destruct(pawn);
                return 1;
        }
        which++;

        if (!stringp(what = list[sprintf("%02d", which3)]) || !sscanf(what, "%s;%d;%*s", file2, size) || !load_object(file2)) // 移动
        {
                pawn->delete_pawn(sprintf("%02d", which2));
                send_user(me, "%c%c%c%c", 0x5b, which, which2, 0);
                pawn->set_pawn(sprintf("%02d", which3), name);

                if (flag = file->get_equip_type())
                {
                        if (!sscanf(name, "%s=:%d,%*s", prop, p))
                                p = 0;
                        if (!sscanf(name, "%s+:%d,%*s", prop, point))
                                point = 0;
                        id = "";
                        if (point)
                                id = sprintf("%+d", point);
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which3,
                                  file->get_picid_2(), total, 0, p, file->get_name() + id);
                }
                else if (file->is_diamond_2())
                {
                        if (!sscanf(name, "%s;%d;%d;%*s", file, total, point))
                                point = 0;
                        id = "";
                        if (point)
                                id = sprintf("%+d", point);
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which3,
                                  file->get_picid_2(), total, 0, 0, file->get_name() + id);
                }
                else
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which3,
                                  file->get_picid_2(), total, 0, 0, file->get_name());
        }
        else // 交换
        {
                pawn->set_pawn(sprintf("%02d", which3), name);
                send_user(me, "%c%c%c%c", 0x5b, which, which3, 0);

                if (flag = file->get_equip_type())
                {
                        if (!sscanf(name, "%s=:%d,%*s", prop, p))
                                p = 0;
                        if (!sscanf(name, "%s+:%d,%*s", prop, point))
                                point = 0;
                        id = "";
                        if (point)
                                id = sprintf("%+d", point);
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which3,
                                  file->get_picid_2(), total, 0, p, file->get_name() + id);
                }
                else if (file->is_diamond_2())
                {
                        if (!sscanf(name, "%s;%d;%d;%*s", file, total, point))
                                point = 0;
                        prop = "";
                        if (point)
                                prop = sprintf("%+d", point);
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which3,
                                  file->get_picid_2(), total, 0, 0, file->get_name() + prop);
                }
                else
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which3,
                                  file->get_picid_2(), total, 0, 0, file->get_name());

                name = what;
                file = file2;
                total = size;
                pawn->set_pawn(sprintf("%02d", which2), what);
                send_user(me, "%c%c%c%c", 0x5b, which, which2, 0);

                if (flag = file->get_equip_type())
                {
                        if (!sscanf(name, "%s=:%d,%*s", prop, p))
                                p = 0;
                        if (!sscanf(name, "%s+:%d,%*s", prop, point))
                                point = 0;
                        id = "";
                        if (point)
                                id = sprintf("%+d", point);
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which2,
                                  file->get_picid_2(), total, 0, p, file->get_name() + id);
                }
                else if (file->is_diamond_2())
                {
                        if (!sscanf(name, "%s;%d;%d;%*s", file, total, point))
                                point = 0;
                        prop = "";
                        if (point)
                                prop = sprintf("%+d", point);
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which2,
                                  file->get_picid_2(), total, 0, 0, file->get_name() + prop);
                }
                else
                        send_user(me, "%c%c%c%w%w%c%c%s", 0x5b, which, which2,
                                  file->get_picid_2(), total, 0, 0, file->get_name());
        }

        pawn->save();
        me->set_pawn(sprintf("%02d", me->get("pawn#")), pawn->get_pawn()); // 更新内存缓存
        destruct(pawn);

        return 1;
}

// 函数:移动物品(不同当铺)
int do_move_2(object me, string name, int which2, int which3)
{
        mapping list, list2;
        object who, pawn, pawn2;
        string *key, file, id, prop;
        int which, total, amount, point;
        int z, x, y, p, i, size, flag;

        if (!objectp(who = find_char(name)))
                return 1;

        if (!who->is_banker())
                return 1;
        // if ( who->get_save("quankho") < 1 ) return 1;

        if ((time() - me->get("pawn_time") > 300) && !inside_screen_2(me, who))
        {
                notify("Bạn cách %s quá xa rồi.", who->get_name());
                return 1;
        }

        me->to_front_eachother(who);

        if (which2 < 1 || which2 > MAX_PAWN)
                return 1;

        which = me->get("pawn#");
        pawn = new (PAWN);
        pawn->set_id(which);
        pawn->set_owner(me->get_id());
        if (pawn->get_owner() != me->get_id())
        {
                log_file("pawnerror.txt", sprintf("%s %s(%d) %s\n", short_time(), me->get_id(), me->get_number(), pawn->get_owner()));
                destruct(pawn);
                return 1;
        }
        if (!mapp(list = pawn->get_pawn()) || !sizeof(list) || !stringp(name = list[sprintf("%02d", which2)]) || !sscanf(name, "%s;%*s", file) || !load_object(file))
        {
                destruct(pawn);
                return 1;
        }
        which++;

        which3--;
        size = me->get_max_pawn_size();

        if (which3 < 0 || which3 >= size)
        {
                notify("Bạn trước mắt chỉ có thể sử dụng %d kho", size);
                destruct(pawn);
                return 1;
        }

        pawn2 = new (PAWN);
        pawn2->set_id(which3);
        pawn2->set_owner(me->get_id());
        if (pawn2->get_owner() != me->get_id())
        {
                log_file("pawnerror.txt", sprintf("%s %s(%d) %s\n", short_time(), me->get_id(), me->get_number(), pawn2->get_owner()));
                destruct(pawn2);
                return 1;
        }
        size = 0;

        if (mapp(list2 = pawn2->get_pawn()))
        {
                size = sizeof(key = keys(list2));
                if (size)
                        key = sort_array(key, 1);
        }

        if (size >= MAX_PAWN)
        {
                destruct(pawn);
                destruct(pawn2);
                return 1;
        }

        for (i = 0; i < size; i++)
                if (to_int(key[i]) != i + 1)
                        break;
        which3++;
        point = i + 1;

        pawn->delete_pawn(sprintf("%02d", which2));
        send_user(me, "%c%c%c%c", 0x5b, which, which2, 0);

        pawn2->set_pawn(sprintf("%02d", point), name);

        pawn->save();
        me->set_pawn(sprintf("%02d", me->get("pawn#")), pawn->get_pawn()); // 更新内存缓存
        destruct(pawn);

        pawn2->save();
        me->set_pawn(sprintf("%02d", which3 - 1), pawn2->get_pawn()); // 更新内存缓存
        destruct(pawn2);

        return 1;
}

int expand_pawn(object me, string name, int flag)
{
        int size, cash;
        object who;

        if (!objectp(who = find_char(name)))
                return 1;
        size = me->get_max_pawn_size();
        cash = 2500 * pow(2, size - 1);
        if (flag <= 0)
        {
                send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), sprintf(" %s \n Hiện tại bạn có %d ngăn, nếu cần tăng thêm, thì nhất thiết phải tốn phí là %d lượng.bạn quyết định mở thêm hay không?\n" ESC "Chấp nhận\npawn expand %x# 1\n" ESC "Rời khỏi", who->get_name(), size, cash, getoid(who)));
                return 1;
        }
        // cash = me->get_cash() - cash ;
        if (me->get_cash() - cash < 0)
        {
                send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), sprintf("%s\n    Ngân lượng của bạn hiện tại không đủ\n" ESC "Rời khỏi", who->get_name(), ));
                return 1;
        }
        me->add_cash(-cash);
        me->set_max_pawn_size(size + 1);
        send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), sprintf("%s\n    Hiện tại bạn có được %d kho\n" ESC "Rời khỏi", who->get_name(), size + 1));
        return 1;
}
