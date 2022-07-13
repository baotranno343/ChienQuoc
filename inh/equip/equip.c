
#include <ansi.h>
#include <item.h>
#include <equip.h>

private
static int Color; // 物品类别  1 蓝装 2 金装 3 紫装 4 绿装

private
int ItemLevel; // 物品等级
private
string MakeProp; // 合成记录

private
int Lasting; // 耐久度
private
int MaxLasting; // 最大耐久度

private
int iHide = 1; // 1 未鉴定 0 已鉴定

private
static object Owner; // 用户标识

private
int iBind; // 0 无绑定 1 装备后绑定 2 装备后已绑定 3 获得绑定 4 获得已绑定

private
string TinVatDesc;

string get_tinvat_desc()
{
        string desc;

        if (TinVatDesc)
                desc = TinVatDesc + "\n";
        else
                desc = "";
        return desc;
}

string set_tinvat_desc(string desc)
{
        return TinVatDesc = desc;
}

// 函数：可装备物品
int is_equip() { return 1; }

// 函数：可装备物品
int get_item_type() { return ITEM_TYPE_EQUIP; }

// 函数：可装备物品
int get_item_type_2() { return ITEM_TYPE_2_EQUIP; }

string set_name(string name);
int get_level();

// -------------------------------------------------------------

// 函数：设置函数
void setup() { Lasting = MaxLasting; }

// 函数：获取装备类别
int get_item_color() { return Color; }

// 函数：设置装备类别
int set_item_color(int type) { return Color = type; }

// 函数：获取功德价值
int get_bonus_value()
{
        switch (get_level())
        {
        case 60:
                return 1500;
        case 70:
                return 2500;
        default:
                return 0;
        }
}

// -------------------------------------------------------------

// 函数：获取等级属性
int get_item_level() { return ItemLevel; }

// 函数：设置等级属性
int set_item_level(int level)
{
        string file = get_file_name(this_object());
        if (level < 1)
                set_name(file->get_name());
        else
                set_name(sprintf("%s%+d", file->get_name(), level));

        return ItemLevel = level;
}

// 函数：增添等级属性
int add_item_level(int level) { return set_item_level(ItemLevel + level); }

// 函数：获取合成记录
string get_make_prop() { return MakeProp ? MakeProp : ""; }

// 函数：设置合成记录
string set_make_prop(string prop) { return MakeProp = prop; }

// -------------------------------------------------------------

// 函数：获取耐久度
int get_lasting() { return Lasting; }

// 函数：设置耐久度
int set_lasting(int time)
{
        object who;

        time = range_value(time, 0, MaxLasting);

        if (Lasting / 10 != time / 10 && (objectp(who = Owner) || objectp(who = environment())))
        {
                Lasting = time;
                USER_INVENTORY_D->send_lasting_tips(who);
                send_user(who, "%c%d%c", 0x31, getoid(this_object()), 0); // 更新描述
        }
        if (Lasting < 100 && objectp(who = Owner))
        {
                Lasting = 0;
                USER_EQUIP_D->count_equip_apply(who, this_object());
                if (this_object()->get_equip_type() == WEAPON_TYPE)
                        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w", 0x7c, getoid(who), UNARMED);
        }
        return Lasting = time;
}

// 函数：增加耐久度
int add_lasting(int time)
{
        if (this_object()->get_save_2("timeAuto") && this_object()->get("autoRun"))
                return;
        return set_lasting(Lasting + time);
}

// 函数：获取最大耐久度
int get_max_lasting() { return MaxLasting; }

// 函数：设置最大耐久度
int set_max_lasting(int time)
{
        object who;

        if (time < 1)
                time = 0;
        if (MaxLasting / 100 != time / 100) // 更新描述
        {
                if (objectp(who = Owner) || objectp(who = environment()))
                        send_user(who, "%c%d%c", 0x31, getoid(this_object()), 0);
        }
        if (time < Lasting)
                set_lasting(time);
        return MaxLasting = time;
}

// 函数：增加最大耐久度
int add_max_lasting(int time) { set_max_lasting(MaxLasting + time); }

// -------------------------------------------------------------

// 函数：获取用户标识
object get_owner() { return Owner; }

// 函数：设置用户标识
object set_owner(object who) { return Owner = who; }

// 函数：玩家身上取出
int remove_from_user()
{
        object who;

        if ((who = environment()) && userp(who))
        {
                send_user(who, "%c%d", 0x2d, getoid(this_object()));
                return 1;
        }
        else if (objectp(Owner) && userp(Owner))
        {
                send_user(Owner, "%c%d", 0x2d, getoid(this_object()));
                return 1;
        }
        else
                return 0;
}

// 函数：获取鉴定标志
int get_hide() { return iHide; }

// 函数：设置鉴定标志
int set_hide(int time)
{
        object who;

        if (time < 1)
                time = 0;
        if (iHide != time) // 更新描述
        {
                if (objectp(who = Owner) || objectp(who = environment()))
                        send_user(who, "%c%d%c", 0x31, getoid(this_object()), 0);
        }
        return iHide = time;
}

// 函数：获取绑定标志
int get_bind() { return iBind; }

// 函数：设置绑定标志
int set_bind(int flag) { return iBind = flag; }