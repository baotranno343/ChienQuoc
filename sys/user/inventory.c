
#include <ansi.h>
#include <equip.h>

// 函数：生成二进制码
void SAVE_BINARY() {}

// 用于判断身上是否有可用的空格，不理会超时的Bao Khoả中占用的东西
int get_free_count(object me)
{
        int bag, b, c, d, count;
        if (!me->is_user())
                return 0;
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
        count = MAX_CARRY - sizeof_inventory(me, 1, MAX_CARRY);
        if (b > 0)
                count = count + b - sizeof_inventory(me, MAX_CARRY + 1, MAX_CARRY + b);
        if (c > 0)
                count = count + c - sizeof_inventory(me, MAX_CARRY * 2 + 1, MAX_CARRY * 2 + c);
        if (d > 0)
                count = count + d - sizeof_inventory(me, MAX_CARRY * 3 + 1, MAX_CARRY * 3 + d);
        return count;
}

// 函数：发送物品栏状态
void send_max_carry_flag(object me)
{
        int a, b, c, d, bag, old;

        a = MAX_CARRY;
        b = 0;
        c = 0;
        d = 0;
        bag = me->have_bag();
        old = bag;
        b = bag % 100;
        c = (bag / 100) % 100;
        d = bag / 10000;
        /*
        if( bag & BAG_TYPE_1 ) b = MAX_CARRY_2;    // Bao Khoả
        if( bag & BAG_TYPE_2 ) c = MAX_CARRY;    // Bách Bảo Nang
        if( bag & BAG_TYPE_3 ) d = MAX_CARRY;    // Túi Càn Khôn
*/
        if (b > 0)
        {
                if (time() > me->get_bag1_time() && me->get_bag1_time() > 0)
                {
                        switch (b)
                        {
                        case 6:
                                b = 1;
                                break;
                        case 12:
                                b = 2;
                                break;
                        case 24:
                                b = 3;
                                break;
                        }
                }
        }
        if (c > 0)
        {
                if (time() > me->get_bag2_time() && me->get_bag2_time() > 0)
                {
                        switch (c)
                        {
                        case 6:
                                c = 1;
                                break;
                        case 12:
                                c = 2;
                                break;
                        case 24:
                                c = 3;
                                break;
                        }
                }
        }
        if (d > 0)
        {
                if (time() > me->get_bag3_time() && me->get_bag3_time() > 0)
                {
                        switch (d)
                        {
                        case 6:
                                d = 1;
                                break;
                        case 12:
                                d = 2;
                                break;
                        case 24:
                                d = 3;
                                break;
                        }
                }
        }
        //        if( me->get_reincarnation() ) b = MAX_CARRY;
        send_user(me, "%c%c%d", 0x3d, 72, d * 1000000 + c * 10000 + b * 100 + a);
}

// 函数：能携带的数量
int can_carry(object me, object item)
{
        object *inv;
        string file;
        int total, amount, max_amount, i, size;

        total = 0;

        if (item->is_combined())
        {
                if (sizeof_inventory(me, 1, MAX_CARRY) < MAX_CARRY)
                        return item->get_max_combined();

                file = get_file_name(item);
                inv = all_inventory(me, 1, MAX_CARRY);
                for (i = 0, size = sizeof(inv); i < size; i++)
                {
                        if (inv[i]->is_combined() && get_file_name(inv[i]) == file && (amount = inv[i]->get_amount()) < (max_amount = inv[i]->get_max_combined()) && inv[i]->get_no_give() == item->get_no_give())
                        {
                                total += max_amount - amount;
                                if (total >= max_amount)
                                        break;
                        }
                }
        }
        else if (sizeof_inventory(me, 1, MAX_CARRY) < MAX_CARRY)
                return MAX_CARRY - sizeof_inventory(me, 1, MAX_CARRY);

        return total;
}

// 函数：能携带的数量(由 move 调用)
int can_carry_2(object me, object item, int begin, int end)
{
        object *inv;
        string file;
        int total, amount, max_amount, i, size;

        total = 0;

        if (item->is_combined())
        {
                if (sizeof_inventory(me, begin, end) < end - begin + 1)
                        return item->get_max_combined();

                file = get_file_name(item);
                inv = all_inventory(me, begin, end);
                for (i = 0, size = sizeof(inv); i < size; i++)
                {
                        if (inv[i]->is_combined() && get_file_name(inv[i]) == file && (amount = inv[i]->get_amount()) < (max_amount = inv[i]->get_max_combined()) && inv[i]->get_no_give() == item->get_no_give())
                        {
                                total += max_amount - amount;
                                if (total >= max_amount)
                                        break;
                        }
                }
        }
        else if (sizeof_inventory(me, begin, end) < end - begin + 1)
                return end - begin + 1 - sizeof_inventory(me, begin, end);

        return total;
}

// 函数：携带可叠加物品(由 buy, get, pawn 调用)
int carry_combined_item(object me, object item, int total)
{
        object *inv;
        string file;
        int total2, amount, max_amount, i, size;

        if (item->is_combined())
        {
                total2 = total;

                file = get_file_name(item);
                inv = all_inventory(me, 1, MAX_CARRY);
                for (i = 0, size = sizeof(inv); i < size; i++)
                {
                        if (inv[i]->is_combined() && get_file_name(inv[i]) == file && inv[i]->get("special") == item->get("special") && inv[i]->get_lock_until() == item->get_lock_until() && (amount = inv[i]->get_amount()) < (max_amount = inv[i]->get_max_combined()) && inv[i]->get_no_give() == item->get_no_give())
                        {

                                if (amount + total2 <= max_amount)
                                {
                                        inv[i]->add_amount(total2);
                                        total2 = 0;
                                        break;
                                }
                                else
                                {
                                        total2 -= max_amount - amount;
                                        inv[i]->set_amount(max_amount);
                                }
                        }
                }

                return total2;
        }
        else
                return 0;
}

// 函数：携带可叠加物品(由 move 调用)
int carry_combined_item_2(object me, object item, int total, int begin, int end)
{
        object *inv;
        string file;
        int total2, amount, max_amount, i, size;

        if (item->is_combined())
        {
                total2 = total;

                file = get_file_name(item);
                inv = all_inventory(me, begin, end);
                for (i = 0, size = sizeof(inv); i < size; i++)
                {
                        if (inv[i]->is_combined() && get_file_name(inv[i]) == file && inv[i]->get("special") == item->get("special") && (amount = inv[i]->get_amount()) < (max_amount = inv[i]->get_max_combined()) && inv[i]->get_no_give() == item->get_no_give())
                        {
                                if (amount + total2 <= max_amount)
                                {
                                        inv[i]->add_amount(total2);
                                        total2 = 0;
                                        break;
                                }
                                else
                                {
                                        total2 -= max_amount - amount;
                                        inv[i]->set_amount(max_amount);
                                }
                        }
                }

                return total2;
        }
        else
                return 0;
}

// -------------------------------------------------------------

// 函数：发送耐久度提示
string send_lasting_tips(object me)
{
        object *equip;
        string result = "";
        int i, p, max;

        equip = me->get_all_equip();
        for (i = 0; i < MAX_EQUIP; i++)
                if (equip[i])
                {
                        p = equip[i]->get_lasting();
                        max = equip[i]->get_max_lasting();

                        switch ((max < 1) ? 0 : p * 100 / max)
                        {
                        case 0..1:
                                result += sprintf(FLASH HIR "%s %3d/%3d\n", equip[i]->get_name(), p / 100, max / 100);
                                break;
                        case 2..5:
                                result += sprintf(HIR "%s %3d/%3d\n", equip[i]->get_name(), p / 100, max / 100);
                                break;
                        case 6..20:
                                result += sprintf(HIY "%s %3d/%3d\n", equip[i]->get_name(), p / 100, max / 100);
                                break;
                        default:
                                break;
                        }
                }

        if (result == "")
                send_user(me, "%c%c", 0x27, 0);
        else
        {
                "/quest/help"->send_help_tips(me, 6);
                send_user(me, "%c%s", 0x27, result);
        }
}
//返回1表示所有物品已经给予玩家,返回0则表示不够位置,全部不能给予玩家
int items_addto_user(object who, object *nObj)
{
        int i, size, j, count, amount, p;
        object *inv, item, item1;
        mapping mpTmp = ([]);
        string file;

        if (!(count = sizeof(nObj)))
                return 0;
        inv = all_inventory(who, 1, MAX_CARRY);
        for (i = 0, size = sizeof(inv); i < size; i++)
        {
                item = inv[i];
                if (!objectp(item))
                        continue;
                if (item->is_combined())
                        mpTmp[item] = item->get_max_combined() - item->get_amount();
                else
                        mpTmp[item] = 0;
        }
        for (j = 0; j < count; j++)
        {
                item1 = nObj[j];
                if (!objectp(item1))
                        continue;
                if (!item1->is_combined())
                {
                        mpTmp[item1] = 0;
                        continue;
                }
                file = get_file_name(item1);
                amount = item1->get_amount();
                for (i = 0, size = sizeof(inv); i < size; i++)
                {
                        item = inv[i];
                        if (!objectp(item))
                                continue;
                        if (get_file_name(item) != file)
                                continue;
                        if (!mpTmp[item])
                                continue;
                        if (amount < mpTmp[item])
                        {
                                amount = 0;
                                mpTmp[item] -= amount;
                        }
                        else
                        {
                                amount -= mpTmp[item];
                                mpTmp[item] = 0;
                        }
                        if (!amount)
                                break;
                }
                if (!amount)
                        continue;
                mpTmp[item1] = item1->get_max_combined() - amount;
        }
        if (sizeof(mpTmp) > MAX_CARRY)
                return 0;
        for (j = 0; j < count; j++)
        {
                item1 = nObj[j];
                if (!objectp(item1))
                        continue;
                if (item1->is_combined())
                {
                        i = carry_combined_item(who, item1, item1->get_amount());
                        if (i)
                        {
                                item1->set_amount(i);
                                p = item1->move(who, -1);
                                if (!p)
                                        return 0;
                                item1->add_to_user(p);
                        }
                }
                else
                {
                        p = item1->move(who, -1);
                        if (!p)
                                return 0;
                        item1->add_to_user(p);
                }
        }
        return 1;
}
//计算道具栏的空格数
int count_empty_carry(object who)
{
        object *inv;

        inv = all_inventory(who, 1, MAX_CARRY);
        return MAX_CARRY - sizeof(inv);
}

int send_carry_desc(object me, int type)
{
        int bag, level, limit;
        string result;
        int *bag_count = ({0, 0, 0});
        if (type > 2 || type < 0)
                return 1;
        bag = me->have_bag();
        bag_count[0] = bag % 100;
        bag_count[1] = (bag / 100) % 100;
        bag_count[2] = bag / 10000;
        if (bag_count[type] == 0)
                return 1;
        switch (bag_count[type])
        {
        case 6:
                result = "Bao Khoả";
                break;
        case 12:
                result = "Bách Bảo Nang";
                break;
        default:
                result = "Túi Càn Khôn";
                break;
        }
        switch (type)
        {
        case 0:
                limit = me->get_bag1_time();
                break;
        case 1:
                limit = me->get_bag2_time();
                break;
        default:
                limit = me->get_bag3_time();
                break;
        }
        if (limit == 0)
                return 1;
        if (limit == -1)
                result = "Vĩnh Viễn";
        else if (time() > limit)
                result = sprintf(HIR "%s đã hết hạn sử dụng\n", result);
        else
                result = sprintf("%s còn %d ngày sử dụng\n", result, (limit - time()) / (24 * 3600));
        send_user(me, "%c%d%s", 0x31, 25 + type * 24, result);
        return 1;
}

// 函数：携带可叠加物品(由 get 调用)
int carry_combined_item_3(object me, object item, int total)
{
        object *inv;
        string file;
        int total2, amount, max_amount, i, size;

        if (item->is_combined())
        {
                total2 = total;

                file = get_file_name(item);
                inv = all_inventory(me, 1, MAX_CARRY * 4);
                for (i = 0, size = sizeof(inv); i < size; i++)
                {
                        if (inv[i]->is_combined() && get_file_name(inv[i]) == file && inv[i]->get("special") == item->get("special") && inv[i]->get_lock_until() == item->get_lock_until() && (amount = inv[i]->get_amount()) < (max_amount = inv[i]->get_max_combined()) && inv[i]->get_no_give() == item->get_no_give())
                        {
                                if (amount + total2 <= max_amount)
                                {
                                        inv[i]->add_amount(total2);
                                        total2 = 0;
                                        break;
                                }
                                else
                                {
                                        total2 -= max_amount - amount;
                                        inv[i]->set_amount(max_amount);
                                }
                        }
                }

                return total2;
        }
        else
                return 0;
}

// 函数：能携带的数量 (全部查找)
int can_carry_3(object me, object item)
{
        object *inv;
        string file;
        int total, amount, max_amount, i, size, allcount;
        int bag, b, c, d;
        if (!me->is_user())
                return 0;
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
        allcount = MAX_CARRY + b + c + d;
        total = 0;

        if (item->is_combined())
        {
                if (__FILE__->get_free_count(me) > 0)
                        return item->get_max_combined();

                file = get_file_name(item);
                inv = all_inventory(me, 1, MAX_CARRY * 4);
                for (i = 0, size = sizeof(inv); i < size; i++)
                {
                        if (inv[i]->is_combined() && get_file_name(inv[i]) == file && (amount = inv[i]->get_amount()) < (max_amount = inv[i]->get_max_combined()) && inv[i]->get_no_give() == item->get_no_give())
                        {
                                total += max_amount - amount;
                                if (total >= max_amount)
                                        break;
                        }
                }
        }
        else if (__FILE__->get_free_count(me) > 0)
                return __FILE__->get_free_count(me);

        return total;
}