
#include <ansi.h>
#include <map.h>
#include <npc.h>
#include <effect.h>
#include <skill.h>

inherit TALISMAN;

//int get_item_color() {return 2 ;}
// 函数：生效几率
int get_active_rate() { return 70; }

// 函数：法宝识别
int get_talisman_type() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Khu Thần Lệnh");
        set_picid_1(9541);
        set_picid_2(9541);
        set_unit("块");

        set_level(2);
        set_value(1000);
        set_max_lasting(3099);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Trang bị pháp bảo này, mỗi khi sử dụng có thể đưa một người chơi\nkhác trong phạm vi tầm nhìn của mình đến một vị trí\nngẫu nhiên trong khu vực, sử dụng chủ động.";
}

// 函数：可使用法宝
int is_usable_2() { return 1; }

// 函数：使用法宝效果
int get_use_effect_2(object me, object who, string arg) { return __FILE__->get_use_effect_2_callout(me, who, this_object(), arg); }

// 函数：使用法宝效果(在线更新)
int get_use_effect_2_callout(object me, object who, object item, string arg) // 同步更改“Phi Hành Phù”
{
        object map, npc;
        int z, x, y, p;

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
        if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
        {
                send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
                return 1;
        }
        if (time() - me->get_save("9541") < 120)
        {
                send_user(me, "%c%s", '!', sprintf("Phải chờ thêm %d giây nữa mới có thể sử dụng Khu Thần Lệnh.", 120 + me->get_save("9541") - time()));
                return 1;
        }

        if (objectp(map = get_map_object(get_z(who))) && map->get_map_type() == BATTLE_MAP)
        {
                send_user(me, "%c%s", '!', "Đối phương đang ở trong Chiến Trường.");
                return 1;
        }
        if (get_z(who) == 704)
        {
                notify("Đối phương đang ở trong Nhà Ngục");
                return 1;
        }
        if (who->get_save_2("51cuanye.time"))
        {
                send_user(me, "%c%s", '!', "对方接受极限穿越任务后不能使用驱神令。");
                return 0;
        }
        if (who->get_save("cambayquest"))
        {
                send_user(me, "%c%s", '!', "Đối phương không thể sử dụng khi đang mang trong mình nhiệm vụ.");
                return 1;
        }
        if (who->get_save("passhanhtrang") && who->get_save("ndmkhtk") < 1)
        {
                send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của đối phương đang trong trạng thái Khoá !");
                return 1;
        }
        if (present("钱票", who, 1, MAX_CARRY))
        {
                send_user(me, "%c%s", '!', "对方身上带着钱票。");
                return 1;
        }
        if (present("Vật Phẩm Quý Bấu", who, 1, MAX_CARRY * 4))
        {
                send_user(me, "%c%s", '!', "对方身上带着Vật Phẩm Quý Bấu。");
                return 1;
        }
        if (present("Ngân Phiếu", who, 1, MAX_CARRY * 4))
        {
                send_user(me, "%c%s", '!', "Đối phương đang làm Thương Nhân.");
                return 1;
        }
        if (objectp(npc = who->get_quest("escort.robber#")) && npc->is_escort_robber()) // 寻找蒙面人
        {
                send_user(me, "%c%s", '!', "对方刚遇到蒙面人。");
                return 1;
        }

        item->add_lasting(-100); // 使用减少耐久

        me->set_char_type(PK_TYPE); // 主动ＰＫ状态
        set_effect(me, EFFECT_USER_PK, 120);
        me->set_save("9541", time());

        if (random(100) < item->get_active_rate() // 成功率
            && (z = get_z(who)) && (p = get_xy_point(z, IS_CHAR_BLOCK)))
        {
                x = p / 1000;
                y = p % 1000;

                //              if( MAP_D->is_inside_city(z, x, y) ) return 1;

                /*              who->set_login_flag(2);    // 跳转保护
                set_invisible(who, 1);
                set_effect(who, EFFECT_USER_LOGIN, 4);   */

                if ((npc = who->get_quest("escort.npc"))                     // 运镖人物
                    && npc->get_owner() == who && inside_screen_2(who, npc)) // 同屏幕内
                        npc->add_to_scene(z, x, y, get_d(who), 40991, 40992, 40991, 40992);

                if (p = get_valid_xy(z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK))
                {
                        who->add_to_scene(z, p / 1000, p % 1000, get_d(who), 40991, 40992, 40991, 40992);
                }

                write_user(me, ECHO "Bạn sử dụng " HIY "Khu Thần Lệnh" ECHO " đem %s biến đi chỗ khác.", who->get_name());
                write_user(who, ECHO "%s sử dụng " HIY "Khu Thần Lệnh" ECHO " đem bạn biến đi chỗ khác.", me->get_name());

                return 1;
        }
        else
                write_user(me, ECHO "Ngươi đuổi %s biến đi chỗ khác bằng " HIY "Khu Thần Lệnh" ECHO " thất bại.", who->get_name());
        return 1;
}

void start_loop_perform(object me)
{
        CHAR_CHAR_D->init_loop_perform(me);
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9324, 1, UNDER_FOOT, PF_LOOP);
        me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
}
void stop_loop_perform(object me)
{
        CHAR_CHAR_D->init_loop_perform(me);
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9324, 1, UNDER_FOOT, PF_STOP);
        me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
}
