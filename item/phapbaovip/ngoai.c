
#include <ansi.h>
#include <npc.h>
#include <skill.h>
#include <effect.h>

inherit TALISMAN;

int get_item_value() { return 100; }
int get_item_value_2() { return 100; }
int get_item_color() { return 2; }

// 函数：生效几率
int get_active_rate() { return 75; }

// 函数：生效时间
int get_time_interval() { return 30; }

// 函数：法宝识别
int get_talisman_type() { return 7; }
int get_item_number() { return 10001109; }
// 函数：构造处理
void create()
{
    set_name("Hỗn Thiên Nghi - Ngoại");
    set_picid_1(4195);
    set_picid_2(4195);
    set_unit("个");

    set_level(2);
    set_value(1000);
    set_max_lasting(9999);

    set("ap", 200);
    set("ap%", 5);
    set("dp", 200);
    set("pp", 200);
    set("hp", 700);
    set("hp%", 5);
    set("-*%", 10);
    set("-c*%", 10);
    set("/%", 5);

    setup();
}

// 函数：获取描述
string get_desc()
{
    return "Tín vật của Thiên Tử. Khi trang bị sẽ gia tăng thuộc tính nhân vật.";
}
string get_tail_desc(object me)
{
    return HIG "【Đặc tính】 Khi bị tấn công có thể giảm bớt sát thương nhận được.";
}

// 函数：可使用法宝
int is_usable_2() { return 1; }

// 函数：征状结束效果
void effect_suppress_done(object me) // 顺势推舟(自用)
{
    object *user;

    user = get_scene_object_2(me, USER_TYPE);
    send_user(me, "%c%w%w%c", 0x81, 9561, 0, EFFECT_GOOD);
    send_user(user - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 9561, 0, EFFECT_GOOD);
    send_user(user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9561, 1, OVER_BODY, PF_STOP);
}

// 函数：使用法宝效果
int get_use_effect_2(object me, object who, string arg) { return __FILE__->get_use_effect_2_callout(me, who, this_object(), arg); }

// 函数：使用法宝效果(在线更新)
int get_use_effect_2_callout(object me, object who, object item, string arg)
{
    object *user, map;

    if (!objectp(who))
        return 1;

    if (!who->is_user())
        return 1; // 必须是玩家

    if (who->get_login_flag() < 3)
        return 1; // 没有准备就绪

    if (who->is_die() || who->is_store_open() || who->get_no_fight())
        return 1; // 死亡，摆摊，安全区

    if (me == who)
        return 1; // 不能是自己

    map = get_map_object(get_z(who));
    if (map->get_no_fight())
    {
        write_user(me, ECHO "Đối phương đang đứng trong khu vực Cấm chiến đấu.");
        return 1;
    }
    if (get_z(who) == 704)
    {
        notify("Đối phương đang ở trong Nhà Ngục");
        return 1;
    }

    item->add_lasting(-10); // 使用减少耐久

    me->set_char_type(PK_TYPE); // 主动ＰＫ状态
    set_effect(me, EFFECT_USER_PK, 120);

    if (get_effect(who, EFFECT_CHAR_SUPPRESS))
        return 1; // 已被压制

    if (random(100) < item->get_active_rate()) // 成功率
    {
        user = get_scene_object_2(who, USER_TYPE);
        set_effect(who, EFFECT_CHAR_SUPPRESS, item->get_time_interval());
        send_user(who, "%c%w%w%c", 0x81, 9561, get_effect_3(who, EFFECT_CHAR_SUPPRESS), EFFECT_BAD);
        send_user(user - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9561, 1, EFFECT_BAD);
        CHAR_CHAR_D->init_loop_perform(who);
        send_user(user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9569, 1, OVER_BODY, PF_ONCE);
        send_user(user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9561, 1, OVER_BODY, PF_LOOP);

        //    write_user( me, ECHO "Pháp bảo của %s bị bạn dùng " HIY "Chuông Hám Thiên" ECHO " áp chế, đã mất đi hiệu quả pháp bảo.", who->get_name() );
        //    write_user( who, ECHO "%s của bạn bị " HIY "Chuông Hám Thiên" ECHO " áp chế, đã mất đi hiệu quả pháp bảo.", me->get_name() );
    }
    else
        write_user(me, ECHO "Bạn áp chế Pháp bảo của %s bằng " HIY "Chuông Hám Thiên" ECHO " thất bại.", who->get_name());

    return 1;
}

void start_loop_perform(object me)
{
    CHAR_CHAR_D->init_loop_perform(me);
    send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 51313, 1, UNDER_FOOT, PF_LOOP);
    me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
}
void stop_loop_perform(object me)
{
    CHAR_CHAR_D->init_loop_perform(me);
    send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 51313, 1, UNDER_FOOT, PF_STOP);
    me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
}
