
#include <ansi.h>
#include <item.h>
#include <map.h>
#include <effect.h>

inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：回城符识别
// int is_fly_seal() { return 1; }

// 函数：回城符识别
int get_item_type() { return ITEM_TYPE_FLY_SEAL; }
int get_max_combined() { return 10000; }

// 函数：构造处理
void create()
{
        set_name("Hồi Thành Phù");
        set_picid_1(0407);
        set_picid_2(0407);
        set_unit("张");
        set_value(1500);
        set_amount(1);
}

// 函数：获取描述
string get_desc()
{
        return "Gửi tới thành mà đã đi qua gần đây";
}

// 函数：使用效果
int get_use_effect(object me) { return __FILE__->get_use_effect_callout(me); }

// 函数：使用效果(在线更新)
int get_use_effect_callout(object me)
{
        object map, npc;
        int z, x, y, p;

        if (me->get_level() < 10)
        {
                send_user(me, "%c%s", '!', "你的等级太低了，不适合路途的颠簸.");
                return 0;
        }
        if (me->get_save_2("51cuanye.time"))
        {
                send_user(me, "%c%s", '!', "接受极限穿越任务后不能使用回城符.");
                return 0;
        }
        if (me->get_save("cambayquest"))
        {
                send_user(me, "%c%s", '!', "Ngươi không thể sử dụng khi đang mang trong mình nhiệm vụ.");
                return 0;
        }
        if (objectp(map = get_map_object(get_z(me))) && map->get_map_type() == BATTLE_MAP && map->is_changping())
        {
                send_user(me, "%c%s", '!', "Trong Chiến Trường không thể sử dụng Hồi Thành Phù");
                //              write_user(me, ECHO "……可是没有任何效果.");
                return 0;
        }
        if (get_z(me) == 704)
        {
                notify("Trong Nhà Ngục không thể sử dụng");
                return 0;
        }
        if (present("钱票", me, 1, MAX_CARRY))
        {
                send_user(me, "%c%s", '!', "带着钱票不能使用回城符.");
                //              write_user(me, ECHO "……可是没有任何效果.");
                return 0;
        }
        if (present("Vật Phẩm Quý Bấu", me, 1, MAX_CARRY * 4))
        {
                send_user(me, "%c%s", '!', "带着Vật Phẩm Quý Bấu不能使用回城符.");
                //              write_user(me, ECHO "……可是没有任何效果.");
                return 0;
        }
        if (present("Ngân Phiếu", me, 1, MAX_CARRY * 4))
        {
                send_user(me, "%c%s", '!', "Mang theo Ngân Phiếu không thể sử dụng.");
                //              write_user(me, ECHO "……可是没有任何效果.");
                return 0;
        }
        if (objectp(npc = me->get_quest("escort.robber#")) && npc->is_escort_robber()) // 寻找蒙面人
        {
                send_user(me, "%c%s", '!', "蒙面人出现，您的行动受到影响.");
                //              write_user(me, ECHO "……可是没有任何效果.");
                return 0;
        }
        write_user(me, ECHO "Bạn đã sử dụng Hồi Thành Phù……");
        p = me->get_latest_city();
        if (p == 0)
                p = 110;
        z = p / 100;
        p = get_jumpin(z, p % 100);

        /*      if( p ) 
        {
                z = 1;  p = get_jumpin(1, 10);
        }       */

        if (p)
        {
                x = p / 1000;
                y = p % 1000;

                send_user(me, "%c%c%w%s", 0x5a, 0, 3, "Hồi Thành Phù……");
                me->set_2("travel.z", z);
                me->set_2("travel.p", p);
                me->set_2("travel.money", 0);
                set_effect(me, EFFECT_TRAVEL, 3);
                return 1;
        }
        else
        {
                write_user(me, ECHO "……可是没有任何效果.");
                return 0;
        }
}
