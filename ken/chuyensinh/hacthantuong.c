#include <item.h>
#include <ansi.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;

int get_item_value() { return 800; }
int get_item_value_2() { return 800; }

inherit "/inh/equip/equip";

#define PICID 1287

int get_item_color()
{
    return 2;
};
// 函数：构造处理
void create()
{
    set_name("Hắc Thần Tướng");
    set_picid_1(4063);
    set_picid_2(4063);
    set_bind(1);
    set_value(444);
    set_hide(0);
    set_no_sell(1);
    set_no_give(1);
    setup();
}

// 函数：获取描述
string get_desc()
{
    return "Thần Tướng Chuyển Sinh, sau khi triệu hồi tăng 20% Ngoại Công và \n20% Nội Công cùng 5% Bạo Kích cho chủ nhân";
}

// 函数：使用效果
int get_use_effect(object me)
{
    return __FILE__->get_use_effect_callout(me, this_object());
}

// 函数：使用效果(在线更新)
int get_use_effect_callout(object me, object item)
{
    object *obj, zombie, npc;
    int size, index, p, z, x, y;

    if (item->get_bind() == 1)
    {
        item->set_bind(2);
    }

    //处理时间控制上面的。

    obj = me->get("zombie");
    size = sizeof(obj);
    if (size)
    {
        for (index = 0; index < size; index++)
        {
            zombie = obj[index];
            if (!objectp(zombie))
                continue;
            send_user(get_scene_object_2(zombie, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, get_x(zombie), get_y(zombie), 9414, 1, OVER_BODY, PF_ONCE);
            send_user(me, "%c%c%d", 0x2c, 0, getoid(zombie));
            zombie->remove_from_scene();
            destruct(zombie);
        }
        item->set_no_drop(0);
        item->set_no_get(0);
        item->set_no_give(0);
        me->delete ("12pet_item");
        me->delete ("zombie");
        me->delete_2("jiguan");
        USER_ENERGY_D->count_all_prop(me);
        return 0;
    }

    item->set_no_drop(1);
    item->set_no_get(1);
    item->set_no_give(1);
    npc = new ("/npc/std/jiguan");
    npc->set_name(get_name());
    npc->set_char_picid(PICID);

    npc->upgrade_level(1);
    npc->set_owner(me);
    npc->set_action_mode(2);
    z = get_z(me);
    x = get_x(me);
    y = get_y(me);
    p = get_valid_xy(z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK);
    x = p / 1000;
    y = p % 1000;
    npc->add_to_scene(z, x, y, 3);
    me->add("zombie", ({npc}));
    me->set("12pet_item", item);
    me->delete_2("jiguan");
    me->set_2("jiguan.ap", 20);
    me->set_2("jiguan.cp", 20);
    me->set_2("jiguan.do", 500);
    USER_ENERGY_D->count_ap(me);
    USER_ENERGY_D->count_cp(me);
    USER_ENERGY_D->count_hit_rate(me);
    return 0;
}

//
string get_tail_desc()
{
    object item = this_object();
    string desc;
    desc = HIG "(Thần Thú Vĩnh Viễn)";

    return desc;
}