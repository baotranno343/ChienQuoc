
#include <ansi.h>
#include <equip.h>

#define PLUNDER_PROTECT_TIME 120 // 战利品保护时间

int get_from(object me, string who, string what);

// 函数：命令处理
int main(object me, string arg)
{
        object *inv, item, winner;
        string id, what, file, str1, str2, result, itemid;
        int z, x, y;
        int total, amount, p, i, size, status, owner;
        int team_id;
        if (is_gm(me))
                return 1;
        if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
        {
                send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
                return 1;
        }
        //        if( gone_time( me->get_time("get") ) < 1 )    // 时间限制
        //        {
        //                me->set_time( "get", time() );
        //                return 1;
        //        }
        //        me->set_time( "get", time() );

        if (!arg)
                return 1;
        if (sscanf(arg, "%s from %s", what, id) == 2)
                return get_from(me, id, what);
        if (sscanf(arg, "%d %d", x, y) != 2)
                return 1;

        z = get_z(me);
        if (!objectp(item = get_xy_object(z, x, y, ITEM_TYPE)))
                return 1;
        if (distance_between(me, item) > 3)
                return 1;
        if (!item->is_item() || item->not_accept_get(me))
                return 1;

        team_id = item->get("team_id");
        if (team_id)
        {
                if (team_id == me->get_team_id()) //队伍分配
                        TEAM_D->distribute_item(me, item);
                else
                        notify("Bạn không thể nhặt %s!", item->get_name());
                return 1;
        }
        str1 = item->get_user_id();
        if (str1 && str1 != me->get_id())
        {
                notify("Bạn không thể nhặt %s", item->get_name());
                return 1;
        }

        if (item->is_cash())
        {
                //              me->to_front_xy(x, y);
                item->remove_from_scene();
                total = item->get_value();
                if (item->get("from"))
                {
                        result = sprintf("Nhặt %s %s,%d,%s,%s lượng 0 %d 0 %d_%d_%d", item->get("from"), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), total, get_z(me), get_x(me), get_y(me));
                        //  "/sys/user/cmd"->log_item(result);
                }
                printf(ECHO "Bạn nhặt được %d lượng.", total);
                me->add_cash2(total);
                me->add_gold_log("get", total);
                me->log_money("捡", total);
                "/sys/sys/count"->add_income("get", total);
                destruct(item);
                return 1;
        }

        if (item->get_no_get())
        {
                notify("Không thể mhặt %s", item->get_name());
                return 1;
        }
        if (item->is_thief_item() && (p = item->get("task")) && p != me->get_number())
        {
                notify("%s là của người khác", item->get_name());
                return 1;
        }
        if (item->who_can_get() && item->who_can_get() != me->get_number())
        {
                notify("%s là của người khác", item->get_name());
                return 1;
        }
        if ((total = USER_INVENTORY_D->can_carry_3(me, item)) < 1)
        {
                notify("Đồ đạc bạn đem theo quá nhiều.");
                return 1;
        }

        //      me->to_front_xy(x, y);

        if (item->is_task_item()) // 第一次捡起使命物品
        {
                status = me->get_save("tips_status");
                if ((status & 1) == 0)
                {
                        QUEST_TIPS->send_tips(me, "4");
                        status |= 1;
                        me->set_save("tips_status", status);
                }
        }
        if (item->is_record() && item->get("from"))
        {
                itemid = "/sys/sys/id"->add_max_itemid(1);
                item->set_user_id(sprintf("#%d#", itemid));
                //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item) ));
                total = item->get_amount();
                if (total == 0)
                        total = 1;
                result = sprintf("Nhặt %s %s,%d,%s,%s %s %s %d %s %d_%d_%d", item->get("from"), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), total, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                // "/sys/user/cmd"->log_item(result);
        }
        if (item->is_combined())
        {
                if (total > item->get_amount())
                        total = item->get_amount();
                printf(ECHO "Bạn nhặt được %s .", item->get_name());

                amount = USER_INVENTORY_D->carry_combined_item_3(me, item, total);

                if (amount > 0 && item->set_amount(amount))
                {
                        if (p = item->move2(me))
                        {
                                item->remove_from_scene();
                                item->add_to_user(p);

                                if (item->get("time"))
                                        item->delete ("time");
                                if (item->get("winner"))
                                        item->delete ("winner");
                        }
                }
                else
                        item->add_amount(-total);
        }
        else if (p = item->move2(me))
        {
                if (item->get_bind() == 3)
                        item->set_bind(4);
                printf(ECHO "Bạn nhặt được %s .", item->get_name());

                item->remove_from_scene();
                item->add_to_user(p);

                if (item->get("time"))
                        item->delete ("time");
                if (item->get("winner"))
                        item->delete ("winner");
        }
        return 1;
}

// 函数：抢夺物品(ＧＭ专用)
int get_from(object me, string id, string what)
{
        object who, item;
        int p, size;

        if (is_player(me))
        {
                notify("您没有足够的权限。");
                return 1;
        }

        if (!(who = find_player(id))) // find_any_char
        {
                notify("Không thể tìm thấy người này");
                return 1;
        }
        if (me == who)
        {
                notify("Bạn muốn cướp chính mình ư ？");
                return 1;
        }

        if (!objectp(item = find_user_item(what, who)))
        {
                notify("Không tìm thấy vật phẩm này");
                return 1;
        }
        /*      if( !inside_screen_2(me, who) )
        {
                notify( "Bạn cách %s quá xa rồi.", who->get_name() );
                return 1;
        }       */

        if (sizeof_inventory(me, 1, MAX_CARRY) >= MAX_CARRY)
        {
                notify("Đồ đạc bạn đem theo quá nhiều.");
                return 1;
        }

        if (get_d(item) >= HEAD_TYPE)
                switch (item->get_equip_type())
                {
                case HEAD_TYPE:
                        who->remove_equip(HEAD_TYPE);
                        break;
                case NECK_TYPE:
                        who->remove_equip(NECK_TYPE);
                        break;
                case WEAPON_TYPE:
                        who->remove_equip(WEAPON_TYPE);
                        break;
                case ARMOR_TYPE:
                        who->remove_equip(ARMOR_TYPE);
                        break;
                case WAIST_TYPE:
                        who->remove_equip(WAIST_TYPE);
                        break;
                case BOOTS_TYPE:
                        who->remove_equip(BOOTS_TYPE);
                        break;
                case HAND_TYPE:
                        who->remove_equip(HAND_TYPE);
                        break;
                }
        if (get_d(item) >= HEAD_TYPE)
        {
                notify("Không thể đạt được trang bị :" + item->get_name() + ".");
                return 1;
        }

        send_user(who, "%c%d", 0x2d, getoid(item));

        if (p = item->move(me, -1))
        {
                item->add_to_user(p);

                if (size = item->get_amount())
                        printf(ECHO "Bạn tìm trên người của %s tìm được %s", who->get_name(), item->get_name());
                else
                        printf(ECHO "Bạn tìm trên người của %s tìm được %s", who->get_name(), item->get_name());
        }

        return 1;
}
