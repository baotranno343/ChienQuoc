#include <item.h>
#include <equip.h>
#include <ansi.h>

inherit DBASE_F;

private
string Name; // 中文名称

private
string ProductID; // 制作者的名字

private
int PicId1; // 地表外型
private
int PicId2; // 道具栏外型

private
int Value; // 物体价值
private
int BonusValue; // 功德价值
private
string Unit; // 物体单位
private
int Level; // 等级属性

private
int NoDrop; // 不可丢弃(不能drop, give, exchange, store)(死亡不掉)
private
int NoGet; // 不可直接取得(不能get)(死亡不掉)
private
int NoGive; // 不可给予(不能give, exchange, store)(死亡不掉)
private
int NoSell; // 不可售卖(不能sell)

static int RecordMessage; // 是否记录来源及走向信息
static int NoSave;        // 是否存盘

/*
Value: -1  不能 sell, pawn
        0  不能 sell, pawn；丢弃会消失
        1  不能 pawn

有 NoDrop, NoGet, NoGive, NoSell 标志，或者 Value <= 1 不能 pawn
*/

private
string UserID; // 最初获得者
private
int LockTime; // 锁定开始
private
int LockUntil; // 锁定时间

private
int DropTime; // 丢弃时间

// 函数：道具识别
int is_item() { return 1; }

// -------------------------------------------------------------

// 函数：获取物品名称
string get_name() { return Name; }

// 函数：设置物品名称
string set_name(string name)
{
        object who;
        int id;

        if ((who = environment()) && who->get_login_flag() > 1)
        {
                id = getoid(this_object());
                send_user(who, "%c%c%d%s", 0x3d, 6, id, name);
                send_user(who, "%c%d%c", 0x31, id, 0);
        }

        return Name = name;
}

// 函数：物体识别处理
int id(string arg)
{
        if (!arg || arg == "")
                return 0;
        if (arg[ < 1] == '#')
                return arg != sprintf("%x#", getoid(this_object())) ? 0 : 1;
        return arg != get_name() ? 0 : 1;
}

// 函数：获取地表外型
int get_picid_1() { return PicId1; }

// 函数：设置地表外型
int set_picid_1(int id) { return PicId1 = id; }

// 函数：获取道具栏外型
int get_picid_2() { return PicId2; }

// 函数：设置道具栏外型
int set_picid_2(int id) { return PicId2 = id; }

// 函数：获取道具价值
int get_value() { return Value; }

// 函数：设置道具价值
int set_value(int value) { return Value = value; }

// 函数：获取功德价值
int get_bonus_value() { return BonusValue; }

// 函数：设置功德价值
int set_bonus_value(int value) { return BonusValue = value; }

// 函数：获取道具单位
string get_unit() { return Unit; }

// 函数：设置道具单位
string set_unit(string unit) { return Unit = unit; }

// 函数：获取等级属性
int get_level() { return Level; }

// 函数：设置等级属性
int set_level(int point) { return Level = point; }

// 函数：判断不可丢弃
int get_no_drop() { return NoDrop; }

// 函数：设置不可丢弃
int set_no_drop(int flag) { return NoDrop = flag; }

// 函数：判断不可获取
int get_no_get() { return NoGet; }

// 函数：设置不可获取
int set_no_get(int flag) { return NoGet = flag; }

// 函数：判断不可给予
int get_no_give() { return NoGive; }

// 函数：设置不可给予
int set_no_give(int flag) { return NoGive = flag; }

// 函数：判断不可售卖
int get_no_sell() { return NoSell; }

// 函数：设置不可售卖
int set_no_sell(int flag) { return NoSell = flag; }

// 函数：获取制作者
string get_product_id() { return ProductID; }

// 函数：设置制作者
string set_product_id(string id) { return ProductID = id; }

// -------------------------------------------------------------

// 函数：获取最初获得者
string get_user_id() { return UserID; }

// 函数：设置最初获得者
string set_user_id(string id) { return UserID = id; }

// 函数：获取锁定开始
int get_lock_time() { return LockTime; }

// 函数：设置锁定开始
int set_lock_time(int time) { return LockTime = time; }

// 函数：获取锁定时间
int get_lock_until() { return LockUntil; }

// 函数：设置锁定时间
int set_lock_until(int time) { return LockUntil = time; }

// 函数：是否道具锁定
int is_locked()
{
        return LockUntil - gone_time(LockTime);
}

// 函数：设置道具锁定
int set_locked(int time)
{
        LockTime = time();
        return LockUntil = time;
}

// 函数：获取丢弃时间
int get_drop_time() { return DropTime; }

// 函数：设置丢弃时间
int set_drop_time(int time) { return DropTime = time; }

// -------------------------------------------------------------

// 函数：显示物品描述
void do_look(object who) // 用于道具栏物品
{
        object item = this_object();

        send_user(who, "%c%d%s", 0x31, getoid(item), ITEM_ITEM_D->get_look_string(who, item));
}

// 函数：显示物品描述
void do_look_2(object who, int what, int type)
{
        object item = this_object();

        switch (type)
        {
        case 0: // 用于地表物品
                send_user(who, "%c%d%s", 0x32, getoid(item), ITEM_ITEM_D->get_look_string(who, item));
                break;

        case 1: // 用于小贩物品(货物不显示卖出价)
                send_user(who, "%c%c%s", 0x33, what, ITEM_ITEM_D->get_look_string(who, item, 1));
                break;

        case 2: // 用于钱庄物品
                send_user(who, "%c%c%s", 0x34, what, ITEM_ITEM_D->get_look_string(who, item));
                break;

        case 3: // 用于小贩物品(货物不显示卖出价-B)
                send_user(who, "%c%c%s", 0x33, what, ITEM_ITEM_D->get_look_string(who, item, 2));
                break;
        }
}

// -------------------------------------------------------------

// 函数：移到目标身上
int move(mixed what, int index)
{
        object who;

        if (objectp(what))
                who = what; // 寻找目的
        else if (!stringp(what))
                return 0;
        else if (!(who = load_object(what)))
                return 0;

        if (sizeof_inventory(who, 1, MAX_CARRY * 4) >= MAX_CARRY * 4)
                return 0; // 空间判断
        switch (index)    // 移动道具
        {
        default:
                move_item(who, index, MAX_CARRY * 4);
                break;
        case 0:
                move_item(who, 0, 0);
                break;
        case -1:
                move_item(who, 1, MAX_CARRY);
                break;
        }

        if (!environment())
                return 0; // 目的不存在

        return get_d(this_object());
}

// 在玩家身上寻找一个合适的位置进行放置
int move2(object me)
{
        object item = this_object();
        int bag, b, c, d, pos;
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
        pos = get_d(item);
        set_d(item, 0);
        move_item(me, 1, MAX_CARRY);
        if (get_d(item))
        {
                return get_d(item);
        }
        if (b > 0)
        {
                move_item(me, MAX_CARRY + 1, MAX_CARRY + b);
                if (get_d(item))
                {
                        return get_d(item);
                }
        }
        if (c > 0)
        {
                move_item(me, MAX_CARRY * 2 + 1, MAX_CARRY * 2 + c);
                if (get_d(item))
                {
                        return get_d(item);
                }
        }
        if (d > 0)
        {
                move_item(me, MAX_CARRY * 3 + 1, MAX_CARRY * 3 + d);
                if (get_d(item))
                {
                        return get_d(item);
                }
        }
        set_d(item, pos);
        return 0; // 目的不存在
}

// 函数：移到目标身上(用于 inventory.c)
int restore_move(mixed what, int index)
{
        object who;

        if (objectp(what))
                who = what; // 寻找目的
        else if (!stringp(what))
                return 0;
        else if (!(who = load_object(what)))
                return 0;

        switch (index) // 移动道具
        {
        default:
                move_item(who, index, index);
                break;
        case 0:
                move_item(who, 0, 0);
                break;
        case -1:
                move_item(who, 1, MAX_CARRY);
                break;
        }

        if (!environment())
                return 0; // 目的不存在

        return get_d(this_object());
}

// 函数：移到目标身上(只用于 equip.c)
int remove_equip(object who, int index)
{
        if (index < 1)
                this_object()->move2(who);
        else
                move_item(who, index, MAX_CARRY * 4);
        return get_d(this_object());
}

// 函数：列示给新玩家(对方进场景)
void show_to_user(object who)
{
        object leader;
        string owner;
        int team_id;
        string id;
        object item = this_object();
        team_id = item->get("team_id");
        if (team_id)
        {
                if (team_id == who->get_team_id())
                        send_user(who, "%c%d%w%w%w%c%s", 0x2e, getoid(item), get_x(item), get_y(item), get_picid_1(), item->get_item_color(), get_name());
                return;
        }
        id = item->get_user_id();
        if (!id || id == who->get_id())
                send_user(who, "%c%d%w%w%w%c%s", 0x2e, getoid(item), get_x(item), get_y(item), get_picid_1(), item->get_item_color(), get_name());
}

// 函数：列示给玩家看(新进入场景)
void show_to_scene(object *user, int x, int y)
{
        object leader;
        string owner;
        int team_id, size, i;
        object item = this_object();
        object who;
        string id;

        team_id = item->get("team_id");
        user -= ({0});

        if (team_id)
        {
                size = sizeof(user);
                for (i = 0; i < size; i++)
                {
                        if (objectp(who = user[i]) && team_id == who->get_team_id())
                                send_user(who, "%c%d%w%w%w%c%s", 0x2e, getoid(item), get_x(item), get_y(item), get_picid_1(), item->get_item_color(), get_name());
                }
                return;
        }
        // dis game

        id = item->get_user_id();

        if (item->get_bind() == 5)
                send_user(user, "%c%d%w%w%w%c%s", 0x2e, getoid(item), get_x(item), get_y(item), get_picid_1(), item->get_item_color(), get_name());
        else
        {
                if (!id)
                {
                        send_user(user, "%c%d%w%w%w%c%s", 0x2e, getoid(item), x, y, get_picid_1(), item->get_item_color(), get_name());
                }
                else
                {

                        size = sizeof(user);
                        for (i = 0; i < size; i++)
                        {

                                if (objectp(who = user[i]) && id == who->get_id())
                                {

                                        send_user(who, "%c%d%w%w%w%c%s", 0x2e, getoid(item), get_x(item), get_y(item), get_picid_1(), item->get_item_color(), get_name());
                                        break;
                                }
                        }
                }
        }
}

// 函数：进入场景处理
void add_to_scene(int z, int x, int y)
{
        object item, *user;
        object obj;
        item = this_object();
        set_z(item, z);
        set_x(item, x);
        set_y(item, y);
        set_block(z, x, y, ITEM_BLOCK);
        move_object(item, z, x, y, ITEM_TYPE);
        show_to_scene(get_scene_object_2(item, USER_TYPE), x, y);
        set_drop_time(time());
        if (item->is_record() || item->is_cash())
        {
                obj = previous_object();
                if (obj)
                {
                        if (obj->is_npc())
                        {
                                item->set("from", sprintf("@%s", obj->get_name()));
                        }
                        else
                                item->set("from", sprintf("其他 %s", get_file_name(obj)));
                }
        }
}

// 函数：删除给玩家看(对方离场景)
void remove_to_user(object who)
{
        send_user(who, "%c%d", 0x2f, getoid(this_object()));
}

// 函数：从场景中移除
void remove_from_scene()
{
        object obj = this_object();
        remove_block(get_z(obj), get_x(obj), get_y(obj), ITEM_BLOCK);
        send_user(get_scene_object_2(obj, USER_TYPE), "%c%d", 0x2f, getoid(obj));
}

// 函数：加入玩家身上
int add_to_user(int index)
{
        object who, item = this_object(), obj, *all;
        int type, locate, level, color, itemid, total, i, size;
        string result;
        if (!((who = environment()) || (who = item->get_owner())) || !userp(who))
                return 0;
        type = item->get_item_type_2();
        locate = item->get_equip_type();
        if (locate > 100)
                locate -= 100;
        if (item->get_level() > 0)
                level = item->get_level();
        else
                level = item->get("level");
        color = item->get_item_color();
        send_user(who, "%c%d%c%w%w%c%c%c%c%s", 0x2b, getoid(item), index,
                  item->get_picid_2(), item->get_amount(), type,
                  color, level, locate, get_name());
        /*                
        send_user( who, "%c%d%c%w%w%c%c%c%s", 0x2b, getoid(item), index, 
                item->get_picid_2(), item->get_amount(), type,
                item->get_item_color(), item->get_level(), get_name() );
*/
        if (item->is_record() && item->get("from") == 0 && who->get_login_flag() == 3 && !get_user_id())
        {
                // 设置唯一编号和失效时间
                itemid = "/sys/sys/id"->add_max_itemid(1);
                set_user_id(sprintf("#%d#", itemid));
                //log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
                obj = previous_object();
                all = previous_object(-1);
                all -= ({item, 0});
                size = sizeof(all);
                for (i = size - 1; i >= 0; i--)
                {
                        if (all[i]->is_npc())
                        {
                                obj = all[i];
                                break;
                        }
                }
                result = "";
                total = item->get_amount();
                if (total == 0)
                        total = 1;
                if (obj && obj->is_npc())
                {
                        item->set("from", sprintf("npc %s", obj->get_name()));
                        result = sprintf("获得 @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", obj->get_name(), who->get_name(), who->get_number(), get_ip_name(who), who->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), total, item->get_user_id(), get_z(who), get_x(who), get_y(who));
                }
                else
                {
                        if (obj)
                        {
                                item->set("from", sprintf("其他 %s", get_file_name(obj)));
                                result = sprintf("获得 @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", get_file_name(obj), who->get_name(), who->get_number(), get_ip_name(who), who->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), total, item->get_user_id(), get_z(who), get_x(who), get_y(who));
                        }
                }
                //"/sys/user/cmd"->log_item(result);
        }
        if (item->is_equip() && item->get_equip_type() != FAMILY_TYPE)
        {
                if (item->get_level() >= 30 && item->get_hide())
                        "/quest/help"->send_help_tips(who, 7);
                if (item->get_bind())
                        "/quest/help"->send_help_tips(who, 24);
                if (item->get_item_color() > 0)
                        "/quest/help"->send_help_tips(who, 30);
        }
        else if (type >= ITEM_TYPE_2_ADD_HP && type <= ITEM_TYPE_2_EVER_EXTRA)
        {
                "/quest/help"->send_help_tips(who, 9);
                "/quest/help"->send_help_tips(who, 11);
        }
        else if (type >= ITEM_TYPE_2_CON_HP && type <= ITEM_TYPE_2_CON_ALL)
        {
                "/quest/help"->send_help_tips(who, 10);
                "/quest/help"->send_help_tips(who, 11);
        }
        else if (item->is_task_item())
        {
                "/quest/help"->send_help_tips(who, 17);
        }
        else if (item->get_item_type() == ITEM_TYPE_DIAMOND_3)
                "/quest/help"->send_help_tips(who, 31);
        //        if( !get_user_id() ) set_user_id( who->get_id() );    // 最初获得者
        return 1;
}

// 函数：玩家身上取出
int remove_from_user()
{
        object who;

        if ((who = environment()) && userp(who))
        {
                send_user(who, "%c%d", 0x2d, getoid(this_object()));
                return 1;
        }
        else
                return 0;
}

// 判断物品是否在身上
int if_in_user(object who)
{
        object me;
        if (me = environment())
        {
                if (me == who)
                        return 1;
        }
        return 0;
}

// -------------------------------------------------------------

// 函数：复位处理
void reset()
{
        if (gone_time(get_drop_time()) > 180) // 十分钟刷新
        {
                remove_from_scene();
                destruct(this_object());
        }
}

// 是否需要记录
int is_record()
{
        object item = this_object();
        //    if (RecordMessage>0||item->get_item_value()||(item->get_item_color()!=0 && item->get_item_color()!=4 )) return 1;
        if (item->get_item_color() > 4)
                return 1;
        return 0;
}

int set_record(int flag)
{
        RecordMessage = flag;
}

string get_item_make_desc()
{
        object item = this_object();
        string make, color;
        int size;
        if (!clonep(item))
                return "";
        make = item->get("make");
        size = strlen(make);
        if (size == 0)
                return "";
        if (size <= 2)
                color = NOR;
        else if (size <= 4)
                color = PPM;
        else if (size <= 6)
                color = HIC;
        else if (size <= 9)
                color = HIY;
        else
                color = HIR;
        if (item->get_equip_type() != BACK_TYPE)
                return sprintf(" %s+%d%s", color, size, NOR);
        else
                return sprintf(" %s+%d%s", color, size, NOR);
}

// 函数：判断不可存盘
int get_no_save() { return NoSave; }

// 函数：设置不可存盘
int set_no_save(int flag) { return NoSave = flag; }