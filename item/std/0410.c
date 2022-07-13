
#include <ansi.h>
#include <map.h>
#include <city.h>
#include <effect.h>
#include <chia_kenh.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

int get_max_combined() { return 10000; }

// 函数：构造处理
void create()
{
        set_name("Hồi Bang Phù");
        set_picid_1(0408);
        set_picid_2(0408);
        set_unit("张");
        set_value(1400);
        set_amount(1);
}

// 函数：获取描述
string get_desc()
{
        return "Truyền tặng đần sân bang phái của mình.";
}

// 函数：使用效果
int get_use_effect(object me) { return __FILE__->get_use_effect_callout(me); }

// 函数：使用效果(在线更新)
int get_use_effect_callout(object me)
{
        object map, npc, orgnpc;
        int z, x, y, p;
        string name;

        if (me->get_org_name() == "")
        {
                send_user(me, "%c%s", '!', "Ngươi chưa gia nhập bang phái không thể sử dụng Hồi Bang Phù.");
                return 0;
        }
        if (me->get_org_name() == 0)
        {
                send_user(me, "%c%s", '!', "Ngươi chưa gia nhập bang phái không thể sử dụng Hồi Bang Phù.");
                return 0;
        }
        if (me->get_org_position() < 1)
        {
                send_user(me, "%c%s", '!', "Ngươi chưa gia nhập bang phái không thể sử dụng Hồi Bang Phù.");
                return 0;
        }
        if (MAIN_D->get_kenh() != KENH_BANG)
        {
                send_user(me, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
                return;
        }
        if (me->get_save("cambayquest"))
        {
                send_user(me, "%c%s", '!', "Ngươi không thể sử dụng khi đang mang trong mình nhiệm vụ.");
                return 0;
        }
        if (objectp(map = get_map_object(get_z(me))) && map->get_map_type() == BATTLE_MAP && map->is_changping())
        {
                send_user(me, "%c%s", '!', "Trong Chiến Trường không thể sử dụng Hồi Bang Phù");
                return 0;
        }
        if (get_z(me) == 704)
        {
                notify("Trong Nhà Ngục không thể sử dụng");
                return 0;
        }

        if (present("钱票", me, 1, MAX_CARRY))
        {
                send_user(me, "%c%s", '!', "带着钱票不能使用回帮符.");
                //              write_user(me, ECHO "……可是没有任何效果.");
                return 0;
        }
        if (present("Vật Phẩm Quý Bấu", me, 1, MAX_CARRY * 4))
        {
                send_user(me, "%c%s", '!', "带着Vật Phẩm Quý Bấu不能使用回帮符.");
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
                return 0;
        }
        name = me->get_org_name();
        orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
        if (!objectp(orgnpc))
                return;
        map = orgnpc->get("map");
        if (map == 0)
        {
                if ((z = find_map_flag(NEWBIE_MAP_BEGIN, NEWBIE_MAP_END, 0)) > 0)
                {
                        p = 886;
                        init_virtual_map(z, p); // 生成虚拟地图
                        map = new ("/inh/std/org");
                        map->set_client_id(p);
                        set_map_object(map, map->set_id(z));
                        orgnpc->set("map", map);
                        orgnpc->set("z", z);
                        map->set_name(name);
                        "/sys/sys/manager"->init_org_place(z, name, orgnpc);
                }
                else
                        return;
        }
        else
        {
                z = orgnpc->get("z");
        }
        if (random(2))
                p = get_jumpin(z, 11);
        else
                p = get_jumpin(z, 12);
        write_user(me, ECHO "Bạn đã sử dụng Hồi Bang Phù……");

        if (p)
        {
                x = p / 1000;
                y = p % 1000;
                send_user(me, "%c%c%w%s", 0x5a, 0, 3, "Hồi Bang Phù……");
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
