
#include <ansi.h>
#include <map.h>
#include <effect.h>
#include <skill.h>

inherit TALISMAN;

//int get_item_color() {return 2 ;}
// 函数：生效几率
int get_active_rate() { return 100; }
int is_tieuhuy() { return 2; }
// 函数：法宝识别
int get_talisman_type() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Thổ Hành Châu");
        set_picid_1(9551);
        set_picid_2(9551);
        set_unit("颗");

        set_level(2);
        set_value(1000);
        set_max_lasting(3099);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Trang bị pháp bảo này, mỗi khi sử dụng có thể di chuyển\nđến một vị trí nào trong khu vực mà người\nchơi chỉ định, sử dụng chủ động.";
}

// 函数：可使用法宝
int is_usable_2() { return 1; }

// 函数：使用法宝效果
int get_use_effect_2(object me, object who, string arg) { return __FILE__->get_use_effect_2_callout(me, who, this_object(), arg); }

// 函数：使用法宝效果(在线更新)
int get_use_effect_2_callout(object me, object who, object item, string arg)
{
        object map, npc;
        int z, x, y, p;

        if (!arg || arg == "")
        {
                send_user(me, "%c%c%d%s", '?', 16, 8, "Bạn muốn đến vị trí nào trên bản đồ ? Hãy nhập vào toạ độ X,Y (giá trị từ 0 đến 999)\n" ESC "pf2 00900.%s\n");
                return 1;
        }
        else
        {
                if (sscanf(arg, "%d,%d", x, y) != 2) // && sscanf(arg, "%d，%d", x, y) != 2
                {
                        send_user(me, "%c%s", '!', "Toạ độ sai !");
                        return 1;
                }

                z = get_z(me);

                if (me->get_login_flag() < 3)
                        return 1; // 没有准备就绪
                if (me->is_die())
                {
                        send_user(me, "%c%s", '!', "Chết rồi không thể sử dụng.");
                        return 1;
                }
                if (me->get_save("cambayquest"))
                {
                        send_user(me, "%c%s", '!', "Ngươi không thể sử dụng khi đang mang trong mình nhiệm vụ.");
                        return 1;
                }
                if (me->get_save_2("51cuanye.time"))
                {
                        send_user(me, "%c%s", '!', "接受极限穿越任务后不能使用土行珠。");
                        return 0;
                }
                if (me->is_store_open())
                {
                        send_user(me, "%c%s", '!', "Bạn đang mở Cửa hàng bán rong, không thể sử dụng Pháp bảo này.");
                        return 1;
                }
                if (get_z(me) == 704)
                {
                        notify("Trong Nhà Ngục không thể sử dụng");
                        return 1;
                }
                if (get_z(me) == 888)
                {
                        notify("Trong VST không thể sử dụng");
                        return 1;
                }
                if (get_z(me) == 889)
                {
                        notify("Trong VSC không thể sử dụng");
                        return 1;
                }
                if (get_z(me) == 910)
                {
                        notify("Trong Bãi Luyện Tập không thể sử dụng");
                        return 1;
                }
                if (get_z(me) == 920)
                {
                        notify("Trong Bãi Luyện Tập không thể sử dụng");
                        return 1;
                }
                /*                if( me->get_no_fight() )
                {
                        send_user( me, "%c%s", '!', "Trong khu vực an toàn không thể sử dụng Pháp bảo này." );
                        return 1;                	
        	}     */
                if (objectp(map = get_map_object(get_z(me))) && map->get_map_type() == BATTLE_MAP)
                {
                        send_user(me, "%c%s", '!', "Trong Chiến Trường không thể sử dụng Pháp bảo này.");
                        return 1;
                }
                if (map->is_copy_scene())
                {
                        send_user(me, "%c%s", '!', "Trong Phó Bản không thể sử dụng Pháp bảo này.");
                        return 1;
                }
                if (map->is_camsudung())
                {
                        send_user(me, "%c%s", '!', "Trong Phó Bản này không thể sử dụng Pháp bảo này.");
                        return 1;
                }
                if (present("钱票", me, 1, MAX_CARRY))
                {
                        send_user(me, "%c%s", '!', "带着钱票不能使用土行珠。");
                        return 1;
                }
                if (present("Vật Phẩm Quý Bấu", me, 1, MAX_CARRY * 4))
                {
                        send_user(me, "%c%s", '!', "带着Vật Phẩm Quý Bấu不能使用土行珠。");
                        return 1;
                }
                if (present("Ngân Phiếu", me, 1, MAX_CARRY * 4))
                {
                        send_user(me, "%c%s", '!', "Đang làm Thương nhân không thể sử dụng.");
                        return 1;
                }
                if (present("Cờ Hiệu Vô Song Thành", me, 1, MAX_CARRY * 4))
                {
                        send_user(me, "%c%s", '!', "Mang theo Cờ Hiệu không thể sử dụng.");
                        return 1;
                }
                if (objectp(npc = me->get_quest("escort.robber#")) && npc->is_escort_robber()) // 寻找蒙面人
                {
                        send_user(me, "%c%s", '!', "您现在正遇到蒙面人呢。");
                        return 1;
                }

                item->add_lasting(-100); // 使用减少耐久

                if (random(100) < item->get_active_rate() // 成功率
                    && (p = get_valid_xy(z, x, y, IS_CHAR_BLOCK)))
                {
                        x = p / 1000;
                        y = p % 1000;

                        /*                        if( MAP_D->is_inside_city(z, x, y) )
                        {
                                send_user( me, "%c%s", '!', "Không thể truyền tống vào bên trong thành." );
                                return 1;
                        }
*/
                        /*                      me->set_login_flag(2);    // 跳转保护
                        set_invisible(me, 1);
                        set_effect(me, EFFECT_USER_LOGIN, 4);   */
                        /*
                        if(   ( npc = me->get_quest("escort.npc") )    // 运镖人物
                        &&      npc->get_owner() == me
                        &&      inside_screen_2(me, npc) )    // 同屏幕内
                                npc->add_to_scene( z, x, y, get_d(me), 40991, 40992, 40991, 40992 );
*/
                        if (p = get_valid_xy(z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK))
                        {
                                me->add_to_scene(z, p / 1000, p % 1000, get_d(me), 40991, 40992, 40991, 40992);
                        }

                        //                      write_user( me, ECHO "您使用" HIY "奇门土遁" ECHO "成功了。" );
                }
                else
                        write_user(me, ECHO "Bạn sử dụng " HIY "Thổ Hành Châu" ECHO " thất bại.");
        }

        return 1;
}

void start_loop_perform(object me)
{
        CHAR_CHAR_D->init_loop_perform(me);
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9322, 1, UNDER_FOOT, PF_LOOP);
        me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
}
void stop_loop_perform(object me)
{
        CHAR_CHAR_D->init_loop_perform(me);
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9322, 1, UNDER_FOOT, PF_STOP);
        me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
}
