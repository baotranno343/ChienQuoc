
#include <ansi.h>
#include <map.h>
#include <effect.h>

inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：构造处理
void create()
{
        set_name("Phi Hành Phù");
        set_picid_1(0409);
        set_picid_2(0409);
        set_unit("张");
        set_value(800);
        set_amount(1);
}

// 函数：获取描述
string get_desc()
{
        return "Đưa đến theo vị trí cảnh trước mặt. Sử dụng sau 60 giây.";
}

// 函数：使用效果
int get_use_effect(object me) { return __FILE__->get_use_effect_callout(me); }

// 函数：使用效果(在线更新)
int get_use_effect_callout(object me) // 同步更改“驱神令”
{
        object map, npc;
        int z, x, y, p;
        if (me->is_store_open())
        {
                send_user(me, "%c%s", '!', "摆摊时不能使用飞行符.");
                return 0;
        }
        if (me->get_save_2("51cuanye.time"))
        {
                send_user(me, "%c%s", '!', "接受极限穿越任务后不能使用飞行符.");
                return 0;
        }
        if (me->get_save("cambayquest"))
        {
                send_user(me, "%c%s", '!', "Ngươi không thể sử dụng khi đang mang trong mình nhiệm vụ.");
                return 0;
        }
        if (objectp(map = get_map_object(get_z(me))) && map->get_map_type() == BATTLE_MAP && map->is_changping())
        {
                send_user(me, "%c%s", '!', "Trong Chiến Trường không thể sử dụng Phi Hành Phù.");
                //              write_user(me, ECHO "……可是没有任何效果.");
                return 0;
        }
        if (get_z(me) == 704)
        {
                notify("Trong Nhà Ngục không thể sử dụng");
                return 0;
        }
        if (present("Vật Phẩm Quý Bấu", me, 1, MAX_CARRY * 4))
        {
                send_user(me, "%c%s", '!', "带着Vật Phẩm Quý Bấu不能使用飞行符.");
                //              write_user(me, ECHO "……可是没有任何效果.");
                return 0;
        }
        if (present("Ngân Phiếu", me, 1, MAX_CARRY * 4))
        {
                send_user(me, "%c%s", '!', "Mang theo Ngân Phiếu không thể sử dụng.");
                //              write_user(me, ECHO "……可是没有任何效果.");
                return 0;
        }
        if (present("Cờ Hiệu Vô Song Thành", me, 1, MAX_CARRY * 4))
        {
                send_user(me, "%c%s", '!', "Mang theo Cờ Hiệu không thể sử dụng.");
                return 0;
        }
        if (objectp(npc = me->get_quest("escort.robber#")) && npc->is_escort_robber()) // 寻找蒙面人
        {
                send_user(me, "%c%s", '!', "蒙面人出现，您的行动受到影响.");
                //              write_user(me, ECHO "……可是没有任何效果.");
                return 0;
        }
        if (gone_time(me->get_time("php")) < 60)
        {
                send_user(me, "%c%s", '!', sprintf("Tái sử dụng sau %d giây", 60 - gone_time(me->get_time("php"))));
                return 0;
        }
        me->set_time("php", time());

        write_user(me, ECHO "Bạn đã dùng một tấm Phi Hành Phù……");

        if ((z = get_z(me)) && (p = get_xy_point(z, IS_CHAR_BLOCK)))
        {
                x = p / 1000;
                y = p % 1000;

                /*              if( MAP_D->is_inside_city(z, x, y) )
                {
                        write_user(me, ECHO "……可是没有任何效果.");
                        return 0;
                }       */

                /*              me->set_login_flag(2);    // 跳转保护
                set_invisible(me, 1);
                set_effect(me, EFFECT_USER_LOGIN, 4);   */

                if ((npc = me->get_quest("escort.npc"))                    // 运镖人物
                    && npc->get_owner() == me && inside_screen_2(me, npc)) // 同屏幕内
                        npc->add_to_scene(z, x, y, get_d(me), 40991, 40992, 40991, 40992);
                if ((npc = me->get_2("orgtask2.npc")) // 帮派任务
                    && npc->get_owner() == me && inside_screen_2(me, npc))
                        npc->add_to_scene(z, x, y, get_d(me));
                if (p = get_valid_xy(z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK))
                {
                        me->add_to_scene(z, p / 1000, p % 1000, get_d(me), 40991, 40992, 40991, 40992);
                }
                me->set("phihanh", 1);
                return 1;
        }
        else
        {
                write_user(me, ECHO "……Sử dụng thất bại.");
                return 0;
        }
}
