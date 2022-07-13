
#include <item.h>
#include <equip.h>

private
int HaveBag; // 拥有包裹
private
int Bag1Time; // 第一个背包的结束时间
private
int Bag2Time; // 第二个背包的结束时间
private
int Bag3Time; // 第三个背包的结束时间

private
static string *Inventory; // 道具数组
private
string *InvE;
private
string *Inv1;
private
string *Inv2;
private
string *Inv3;
private
string *Inv4;

// -------------------------------------------------------------

// 函数：是否拥有包裹
int have_bag() { return HaveBag; }

// 函数：设置拥有包裹
int set_have_bag(int flag)
{
        /*
        if( HaveBag != flag )
        {
                HaveBag = flag;    // 提前更新
                USER_INVENTORY_D->send_max_carry_flag( this_object() );
        }
*/
        return HaveBag = flag;
}

int get_bag1_time() { return Bag1Time; }
int get_bag2_time() { return Bag2Time; }
int get_bag3_time() { return Bag3Time; }

int set_bag1_time(int flag) { return Bag1Time = flag; }
int set_bag2_time(int flag) { return Bag2Time = flag; }
int set_bag3_time(int flag) { return Bag3Time = flag; }

// -------------------------------------------------------------

// 函数：获取道具数组
string *get_inventory() { return copy(Inventory); }

// 函数：清除道具数组
void init_inventory()
{
        Inventory = ({});
        InvE = ({});
        Inv1 = ({});
        Inv2 = ({});
        Inv3 = ({});
        Inv4 = ({});
}

void add_inv(string tui, string item)
{
        if (tui == "inve")
                InvE += ({item});
        else if (tui == "inv1")
                Inv1 += ({item});
        else if (tui == "inv2")
                Inv2 += ({item});
        else if (tui == "inv3")
                Inv3 += ({item});
        else if (tui == "inv4")
                Inv4 += ({item});
}
// 函数：保存道具物体
void save_inventory()
{
        object me, *inv, item;
        string id, file, tui;
        int amount, no_give, index, point, locktime, lockutil;
        int i, size;

        // Inventory = ({ });
        InvE = ({});
        Inv1 = ({});
        Inv2 = ({});
        Inv3 = ({});
        Inv4 = ({});

        me = this_object();
        inv = me->get_all_equip() + all_inventory(me, 0, 0);

        for (i = 0, size = sizeof(inv); i < size; i++)
                if (item = inv[i])
                {
                        if (item->get_no_save()) //不保存，下线就消失
                                continue;
                        file = get_file_name(item);
                        amount = item->get_amount();
                        no_give = item->get_no_give();
                        index = get_d(item);
                        switch (index)
                        {
                        case 101..110:
                                tui = "inve";
                                break;
                        case 25..48:
                                tui = "inv2";
                                break;
                        case 49..72:
                                tui = "inv3";
                                break;
                        case 73..96:
                                tui = "inv4";
                                break;
                        default:
                                tui = "inv1";
                                break;
                        }

                        if (!stringp(id = item->get_user_id()))
                                id = "-";
                        locktime = item->get_lock_time();
                        lockutil = item->get_lock_until();

                        switch (item->get_item_type())
                        {
                        case ITEM_TYPE_EQUIP:
                                add_inv(tui, sprintf("%s;%d;%d;%d;%d;%d;%s;[%s]%d,%d",
                                                     file, amount, no_give, index, item->get_lasting(), item->get_max_lasting(), ITEM_EQUIP_D->get_save_prop_string(item), id, locktime, lockutil));
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
                                add_inv(tui, sprintf("%s;%d;%d;%d;%d;%d;%d;[%s]%d,%d",
                                                     file, amount, no_give, index, item->get_lasting(), item->get_max_lasting(), point, id, locktime, lockutil));
                                break;

                        case ITEM_TYPE_POISON_2:
                                add_inv(tui, sprintf("%s;%d;%d;%d;[%s]%d,%d",
                                                     file, amount, index, item->get_poison(), id, locktime, lockutil));
                                break;

                        case ITEM_TYPE_GOOD:
                                add_inv(tui, sprintf("%s;%d;%d;%d;[%s]%d,%d",
                                                     file, amount, index, item->get_buyin(), id, locktime, lockutil));
                                break;
                        case ITEM_TYPE_CHEQUE2:
                        case ITEM_TYPE_CHEQUE:
                                add_inv(tui, sprintf("%s;%d;%d;%d;%d;[%s]%d,%d",
                                                     file, amount, index, item->get_orgin_money(), item->get_money(), id, locktime, lockutil));
                                break;

                        case ITEM_TYPE_TREASURE: // xem xet
                                add_inv(tui, sprintf("%s;%d;%d;%d;%d;%d;[%s]%d,%d",
                                                     file, amount, index, item->get_map_z(), item->get_map_x(), item->get_map_y(), id, locktime, lockutil));
                                break;

                        case ITEM_TYPE_DIAMOND_2:
                                add_inv(tui, sprintf("%s;%d;%d;%d;[%s]%d,%d",
                                                     file, amount, index, item->get_item_level(), id, locktime, lockutil));
                                break;

                        case ITEM_TYPE_POTENTIAL:
                                add_inv(tui, sprintf("%s;%d;%d;%d;[%s]%d,%d",
                                                     file, amount, index, item->get_potential(), id, locktime, lockutil));
                                break;
                        case ITEM_TYPE_SPECIAL:
                                add_inv(tui, sprintf("%s;%d;%d;%s;[%s]%d,%d", file, amount, index, item->get("special"), id, locktime, lockutil));
                                break;
                        // case ITEM_TYPE_HUYENTHU:
                        //         add_inv(tui, sprintf("%s;%d;%d;[%s]%d,%d", file, amount, index, id, locktime, lockutil));
                        //         break;
                        case ITEM_TYPE_KIMNGUYENBAO:
                                add_inv(tui, sprintf("%s;%d;%d;%d;[%s]%d,%d",
                                                     file, amount, index, "sys/sys/test_db"->get_yuanbao(item), id, locktime, lockutil));
                                break;
                        case ITEM_TYPE_CHIENTICH:
                                add_inv(tui, sprintf("%s;%d;%d;%d;[%s]%d,%d",
                                                     file, amount, index, item->get_save_2("changping.score"), id, locktime, lockutil));
                                break;
                        case ITEM_TYPE_DIAMOND_3:
                                add_inv(tui, sprintf("%s;%d;%d;%d;[%s]%d,%d", file, item->get_level(), no_give, index, id, locktime, lockutil));
                                break;
                        default:
                                add_inv(tui, sprintf("%s;%d;%d;%d;[%s]%d,%d", file, amount, no_give, index, id, locktime, lockutil));
                                break;
                        case ITEM_TYPE_DIAMOND_100:
                                add_inv(tui, sprintf("%s;%d;%d;%d;[%s]%d,%d", file, item->get_level(), no_give, index, id, locktime, lockutil));
                                break;
                        }
                }
}

// 函数：读取道具物体
void restore_inventory()
{
        object me, item;
        string id, file, prop, special;
        int amount, no_give, index, use, maxuse, locktime, lockutil;
        int point, point2, point3;
        int i, size;

        me = this_object();
        Inventory = ({});
        if (arrayp(InvE) && sizeof(InvE))
                Inventory += InvE;
        if (arrayp(Inv1) && sizeof(Inv1))
                Inventory += Inv1;
        if (arrayp(Inv2) && sizeof(Inv2))
                Inventory += Inv2;
        if (arrayp(Inv3) && sizeof(Inv3))
                Inventory += Inv3;
        if (arrayp(Inv4) && sizeof(Inv4))
                Inventory += Inv4;
        if (arrayp(Inventory) && sizeof(Inventory))
                for (i = 0, size = sizeof(Inventory); i < size; i++)
                {
                        sscanf(Inventory[i], "%s;%*s", file);
                        if (!load_object(file))
                                continue;

                        switch (file->get_item_type())
                        {
                                // 1
                        case ITEM_TYPE_EQUIP:
                                if (sscanf(Inventory[i], "%s;%d;%d;%d;%d;%d;%s;[%s]%d,%d", file, amount, no_give, index, use, maxuse, prop, id, locktime, lockutil) != 10)
                                {

                                        continue;
                                }

                                item = new (file);
                                if (amount)
                                        item->set_amount(amount);
                                if (no_give == 1)
                                {
                                        item->set_no_give(no_give);
                                        item->set_no_sell(1);
                                }

                                item->set_max_lasting(maxuse);
                                item->set_lasting(use);

                                ITEM_EQUIP_D->set_prop_baseon_string(item, prop);

                                break;
                                // 2
                        case ITEM_TYPE_TALISMAN:
                                if (file->get_name() == "Đồng tâm khóa" && !me->get_save_2("marry"))
                                        continue;
                                if (sscanf(Inventory[i], "%s;%d;%d;%d;%d;%d;%d;[%s]%d,%d", file, amount, no_give, index, use, maxuse, point, id, locktime, lockutil) != 10)
                                {

                                        continue;
                                }
                                item = new (file);
                                if (amount)
                                        item->set_amount(amount);
                                if (no_give == 1)
                                {
                                        item->set_no_give(no_give);
                                        item->set_no_sell(1);
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
                                if (sscanf(Inventory[i], "%s;%d;%d;%d;[%s]%d,%d", file, amount, index, point, id, locktime, lockutil) != 7)
                                        continue;

                                item = new (file);
                                if (amount)
                                        item->set_amount(amount);
                                item->set_poison(point);

                                break;

                        case ITEM_TYPE_GOOD:
                                if (sscanf(Inventory[i], "%s;%d;%d;%d;[%s]%d,%d", file, amount, index, point, id, locktime, lockutil) != 7)
                                        continue;

                                item = new (file);
                                if (amount)
                                        item->set_amount(amount);
                                item->set_buyin(point);

                                break;

                        case ITEM_TYPE_CHEQUE2:
                        case ITEM_TYPE_CHEQUE:
                                if (sscanf(Inventory[i], "%s;%d;%d;%d;%d;[%s]%d,%d", file, amount, index, point, point2, id, locktime, lockutil) != 8)
                                        continue;

                                item = new (file);
                                if (amount)
                                        item->set_amount(amount);
                                item->set_orgin_money(point);
                                item->set_money(point2);

                                break;

                        case ITEM_TYPE_TREASURE:
                                if (sscanf(Inventory[i], "%s;%d;%d;%d;%d;%d;[%s]%d,%d", file, amount, index, point, point2, point3, id, locktime, lockutil) != 9)
                                        continue;

                                item = new (file);
                                if (amount)
                                        item->set_amount(amount);
                                item->set_map_z(point);
                                item->set_map_x(point2);
                                item->set_map_y(point3);

                                break;

                        case ITEM_TYPE_DIAMOND_2:
                                if (sscanf(Inventory[i], "%s;%d;%d;%d;[%s]%d,%d", file, amount, index, point, id, locktime, lockutil) != 7)
                                {
                                        point = 0;
                                        if (sscanf(Inventory[i], "%s;%d;%d;[%s]%d,%d", file, amount, index, id, locktime, lockutil) != 6)
                                        {
                                                if (sscanf(Inventory[i], "%s;%d;%d;%d", file, amount, index, point) != 4)
                                                        continue;
                                                id = "-";
                                                locktime = 0;
                                                lockutil = 0;
                                        }
                                }
                                item = new (file);
                                if (amount)
                                        item->set_amount(amount);
                                item->set_item_level(point);

                                break;

                        case ITEM_TYPE_POTENTIAL:
                                if (sscanf(Inventory[i], "%s;%d;%d;%d;[%s]%d,%d", file, amount, index, point, id, locktime, lockutil) != 7)
                                {
                                        point = 0;
                                        if (sscanf(Inventory[i], "%s;%d;%d;[%s]%d,%d", file, amount, index, id, locktime, lockutil) != 6)
                                        {
                                                if (sscanf(Inventory[i], "%s;%d;%d;%d", file, amount, index, point) != 4)
                                                        continue;
                                                id = "-";
                                                locktime = 0;
                                                lockutil = 0;
                                        }
                                }
                                item = new (file);
                                if (amount)
                                        item->set_amount(amount);
                                item->set_potential(point);

                                break;
                        case ITEM_TYPE_SPECIAL:
                                if (sscanf(Inventory[i], "%s;%d;%d;%s;[%s]%d,%d", file, amount, index, special, id, locktime, lockutil) != 7)
                                        continue;

                                item = new (file);
                                if (amount)
                                        item->set_amount(amount);
                                item->set("special", special);
                                break;

                        // case ITEM_TYPE_HUYENTHU:
                        //         if (sscanf(Inventory[i], "%s;%d;%d;[%s]%d,%d", file, amount, index, id, locktime, lockutil) != 6)
                        //                 continue;
                        //         item = new (file);
                        //         if (amount)
                        //                 item->set_amount(amount);
                        //         break;
                        case ITEM_TYPE_KIMNGUYENBAO:
                                if (sscanf(Inventory[i], "%s;%d;%d;%d;[%s]%d,%d", file, amount, index, point, id, locktime, lockutil) != 7)
                                {
                                        point = 0;
                                        if (sscanf(Inventory[i], "%s;%d;%d;[%s]%d,%d", file, amount, index, id, locktime, lockutil) != 6)
                                        {
                                                if (sscanf(Inventory[i], "%s;%d;%d;%d", file, amount, index, point) != 4)
                                                        continue;
                                                id = "-";
                                                locktime = 0;
                                                lockutil = 0;
                                        }
                                }
                                item = new (file);
                                if (amount)
                                        item->set_amount(amount);
                                //  item->set_potential(point);
                                "sys/sys/test_db"->set_yuanbao(item, point);

                                break;
                        case ITEM_TYPE_CHIENTICH:
                                if (sscanf(Inventory[i], "%s;%d;%d;%d;[%s]%d,%d", file, amount, index, point, id, locktime, lockutil) != 7)
                                {
                                        point = 0;
                                        if (sscanf(Inventory[i], "%s;%d;%d;[%s]%d,%d", file, amount, index, id, locktime, lockutil) != 6)
                                        {
                                                if (sscanf(Inventory[i], "%s;%d;%d;%d", file, amount, index, point) != 4)
                                                        continue;
                                                id = "-";
                                                locktime = 0;
                                                lockutil = 0;
                                        }
                                }
                                item = new (file);
                                if (amount)
                                        item->set_amount(amount);
                                //  item->set_potential(point);
                                //	"sys/sys/test_db"->set_yuanbao(item,point);
                                item->set_save_2("changping.score", point);

                                break;
                                // 3
                        case ITEM_TYPE_DIAMOND_3:
                                if (sscanf(Inventory[i], "%s;%d;%d;%d;[%s]%d,%d", file, amount, no_give, index, id, locktime, lockutil) != 7)
                                {

                                        continue;
                                }

                                item = new (file);
                                if (amount)
                                        item->set_level(amount);
                                if (no_give == 1)
                                {
                                        item->set_no_give(no_give);
                                        item->set_no_sell(1);
                                }

                                break;
                                // 4
                        default:
                                if (sscanf(Inventory[i], "%s;%d;%d;%d;[%s]%d,%d", file, amount, no_give, index, id, locktime, lockutil) != 7)
                                {
                                        continue;
                                }
                                item = new (file);
                                if (amount)
                                        item->set_amount(amount);
                                if (no_give == 1)
                                {
                                        item->set_no_give(no_give);
                                        item->set_no_sell(1);
                                }
                                break;
                                // 5
                        case ITEM_TYPE_DIAMOND_100:
                                if (sscanf(Inventory[i], "%s;%d;%d;%d;[%s]%d,%d", file, amount, no_give, index, id, locktime, lockutil) != 7)
                                {
                                        // no_give = 0;
                                        // if (sscanf(Inventory[i], "%s;%d;%d;[%s]%d,%d", file, amount, index, id, locktime, lockutil) != 6)
                                        continue;
                                }

                                item = new (file);
                                if (amount)
                                        item->set_level(amount);
                                if (no_give == 1)
                                {
                                        item->set_no_give(no_give);
                                        item->set_no_sell(1);
                                }

                                break;
                        }
                        item->set_user_id(id);
                        item->set_lock_time(locktime);
                        item->set_lock_until(lockutil);
                        if (HEAD_TYPE <= index && index <= FASHION_TYPE)
                        {
                                if (me->restore_equip(item))
                                        continue;
                                else
                                        index = -1;
                        }
                        else if (number_present(me, index, 0, 0))
                                index = -1; // 容错性

                        index = item->restore_move(me, index);
                        item->add_to_user(index);
                }

        USER_INVENTORY_D->send_lasting_tips(me);

        // Inventory = ({ });
}

// 函数：消除之前处理
void before_destruct()
{
        object *inv;
        int i, size;

        inv = this_object()->get_all_equip() + all_inventory(this_object(), 0, 0);
        for (i = 0, size = sizeof(inv); i < size; i++)
                if (inv[i])
                        destruct(inv[i]);
}
