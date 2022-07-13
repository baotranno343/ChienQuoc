#include <item.h>
#include <ansi.h>
int mix1(object me, object *item);
int mix_limit_time_item(object item1, object item2);

// 函数：命令处理
int main(object me, string arg)
{
        object *item, who;
        string name, file, result;
        int *id;
        int i, level, d;
        if (!arg)
                return 1;

        item = ({
            0,
            0,
        });
        id = ({
            0,
            0,
        });

        if (sscanf(arg, "%s %x# %x#", name,
                   id[0], id[1]) != 3)
        {
                notify("Bạn muốn hợp thành đồ gì?");
                return 1;
        }
        if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
        {
                send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
                return 1;
        }
        /*        
        if( !objectp( who = find_char(name) ) ) return 1;

        if( !who->is_maker() ) return 1;

        if( !inside_screen_2(me, who) )
        {
                notify( "Bạn cách %s quá xa rồi.", who->get_name() );
                return 1;
        }

        me->to_front_eachother(who);
*/
        for (i = 0; i < 2; i++)
        {
                if (!objectp(item[i] = present(sprintf("%x#", id[i]), me, 1, MAX_CARRY * 4))) // 物品是否存在？
                {
                        return 1;
                }
        }
        if (item[0] == item[1])
                return 1;

        //限时法宝合成
        if (name == "time_limit")
                return mix_limit_time_item(item[0], item[1]);

        for (i = 0; i < 2; i++)
        {
                if (item[i]->get_item_type() != ITEM_TYPE_DIAMOND_3)
                {
                        notify("%s không phải bảo thạch", item[i]->get_name());
                        return 1;
                }
                if (!item[i]->get_real_name())
                {
                        notify("%s không phải bảo thạch", item[i]->get_name());
                        return 1;
                }
        }
        if (item[0]->get_real_name() != item[1]->get_real_name())
        {
                notify("Bảo thạch không cùng loại.");
                return 1;
        }
        if (item[0]->get_diamond_type() == "forge" && item[1]->get_diamond_type() == "forge")
        {
                return mix1(me, ({item[0], item[1]})); //锻造石合成
        }
        if (item[0]->get_diamond_type() != item[1]->get_diamond_type())
        {
                notify("Bảo thạch không cùng loại.");
                return 1;
        }
        if (item[0]->get_no_give() || item[1]->get_no_give())
        {
                notify("Loại bảo thạch này không thể hợp thành!");
                return 1;
        }
        level = item[0]->get_level();
        if (level != item[1]->get_level())
        {
                notify("Cấp bậc không tương xứng.");
                return 1;
        }
        if (level >= 10)
        {
                notify("Cấp bậc của Bảo thạch đã đạt 10.");
                return 1;
        }
        if (me->get_strength() < 5)
        {
                notify("Thể lực không đủ 5 điểm.");
                return 1;
        }
        me->add_strength(-5);
        item[1]->set_level(level + 1);
        if (item[0]->is_record())
        {
                result = sprintf("合成消失 %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item[0]->get_name(), "/sys/item/item"->get_pawn_save_string(item[0]), 1, item[0]->get_user_id(), get_z(me), get_x(me), get_y(me));
                //"/sys/user/cmd"->log_item(result);
        }
        item[0]->remove_from_user();
        destruct(item[0]);
        d = get_d(item[1]);
        item[1]->add_to_user(d);
        //        send_user( me, "%c%d%c", 0x31, getoid(item[0]), 0 );
        file = get_file_name(item[1]);
        write_user(me, ECHO "Bạn hợp thành %d cấp %s và nhận được %d cấp %s.", level, file->get_name(), level + 1, file->get_name());
        return 1;
}

//合成锻造石
int mix1(object me, object *item)
{
        string file, result, index, name;
        int level, d;
        index = item[0]->get_forge_index();
        if (index != item[1]->get_forge_index())
        {
                notify("Đoạn Thạch không tương xứng.");
                return 1;
        }
        if (item[0]->get_no_give() || item[1]->get_no_give())
        {
                notify("Loại đoạn thạch này không thể hợp thành!");
                return 1;
        }
        if (item[0]->is_huynhde() && item[1]->is_huynhde())
        {
                notify("Cả hai viên Đoạn Thạch đều là Đoạn Thạch Thuộc Huynh Đệ!");
                return 1;
        }

        if (index != "1" && index != "2")
        {
                notify("Đoạn Thạch này không thể hợp thành.");
                return 1;
        }
        if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
        {
                send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
                return 1;
        }
        name = item[0]->get_name();
        result = sprintf("合成消失 %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item[0]->get_name(), "/sys/item/item"->get_pawn_save_string(item[0]), 1, item[0]->get_user_id(), get_z(me), get_x(me), get_y(me));
        //"/sys/user/cmd"->log_item(result);
        item[0]->remove_from_user();
        destruct(item[0]);
        d = get_d(item[1]);
        item[0] = item[1];
        result = sprintf("合成消失 %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item[0]->get_name(), "/sys/item/item"->get_pawn_save_string(item[0]), 1, item[0]->get_user_id(), get_z(me), get_x(me), get_y(me));
        //"/sys/user/cmd"->log_item(result);
        item[0]->remove_from_user();
        destruct(item[0]);
        if (index == "1")
                item[0] = new ("/item/sell/1032");
        else
                item[0] = new ("/item/sell/2032");
        if (d = item[0]->move(me, d))
        {
                item[0]->add_to_user(d);
        }
        write_user(me, ECHO "Bạn hợp thành %s và nhận được %s.", name, item[0]->get_name());
        return 1;
}

int mix_limit_time_item(object item1, object item2)
{
        int d, time, time1, time2;

        if (item1->is_limit_time_item() && item2->is_limit_time_item() && get_file_name(item1) == get_file_name(item2))
        {
                if (item1->get_lock_time() == 0)
                        item1->get_desc();
                time1 = item1->get_lock_time() - time();
                if (item2->get_lock_time() == 0)
                        item2->get_desc();
                time2 = item2->get_lock_time() - time();

                if (time1 < 0)
                        time1 = 0;
                if (time2 < 0)
                        time2 = 0;
                time = time1 + time2;

                item1->remove_from_user();
                destruct(item1);

                if (time <= 0)
                {
                        item2->remove_from_user();
                        destruct(item2);
                }
                else
                {
                        item2->set_lock_time(time() + time);
                        d = get_d(item2);
                        item2->add_to_user(d);
                }
                return 1;
        }
}
