
#include <equip.h>
#include <effect.h>
#include <skill.h>

inherit TALISMAN;

int get_item_value() { return 100; }
int get_item_value_2() { return 100; }
//int get_item_color() {return 2 ;}
int is_tieuhuy() { return 2; }
private
int HP = 600; // 当前气血

// 函数：获取最大气血
int get_max_hp() { return 600; }

// 函数：获取当前气血
int get_hp() { return HP; }

// 函数：设置当前气血
int set_hp(int point)
{
        object who;

        point = range_value(point, 0, get_max_hp());

        if (HP != point && (objectp(who = get_owner()) || objectp(who = environment())))
                send_user(who, "%c%d%c", 0x31, getoid(this_object()), 0); // 更新描述

        return HP = point;
}

// 函数：增添当前气血
int add_hp(int point) { return set_hp(HP + point); }

// 函数：生效几率
int get_active_rate() { return 75; }

// 函数：法宝识别
int get_talisman_type() { return 2; }

// 函数：构造处理
void create()
{
        object me = this_object();

        set_name("Cửu Long Thần Hỏa Trảo");
        set_picid_1(9511);
        set_picid_2(9511);
        set_unit("个");

        set_level(2);
        set_value(1000);
        set_max_lasting(28099);

        set("dp", 300);
        set("pp", 300);
        set("hp", 200);

        setup();

        if (!clonep(me))
                return;

        set_heart_timer(me, set_heart_timer_2(me, getoid(me) % 10)); // 心跳随机
        set_heart_loop(me, 100);                                     // 循环心跳：１０秒钟
        me->heart_beat();
        set_heart_beat(1);
}

// 函数：心跳处理
void heart_beat() {}

// 函数：心跳处理(循环)
void heart_beat_loop(int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) { __FILE__->heart_beat_loop_callout(this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout(object me, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) // 每１０秒处理
{
        object owner;

        if (objectp(owner = me->get_owner()) || objectp(owner = environment()))
        {
                if (!get_effect(owner, EFFECT_CHAR_SUPPRESS) && owner->get_equip(HAND_TYPE) == me)
                {
                        if (!me->is_die())
                                me->add_hp(me->get_level() * 50);
                }
        }
}

// 函数：获取描述
string get_desc()
{
        return "Sau khi trang bị Pháp Bảo này, có tỷ lệ\nhấp thu 75% sát thương nhận được.";
}

void start_loop_perform(object me)
{
        CHAR_CHAR_D->init_loop_perform(me);
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9321, 1, UNDER_FOOT, PF_LOOP);
        me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
}
void stop_loop_perform(object me)
{
        CHAR_CHAR_D->init_loop_perform(me);
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9321, 1, UNDER_FOOT, PF_STOP);
        me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
}
