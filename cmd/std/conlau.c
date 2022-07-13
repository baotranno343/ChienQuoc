
#include <effect.h>
#include <map.h>
#include <ansi.h>

// 函数：命令处理
int main(object me, string arg)
{
        object who, item, item2, npc, map, map1;
        int z, x, y, x0, y0, p;
        string arg1, arg2, ben;
        if (sscanf(arg, "%s.%s", arg1, arg2) != 2)
                return 1;
        if (arg1 == "?") // 使用Thiên Lý Hữu Tình的人
        {
                item2 = present("Thiên Lý Hữu Tình", me, 1, MAX_CARRY);
                if (!item2)
                        return 1;
                if (!(who = find_any_char(arg2)))
                {
                        notify("Bạn đưa vào số ID ko có hiệu lực");
                        return 1;
                }
                if (!who->is_user())
                {
                        notify("Bạn đưa vào số ID ko phải người chơi");
                        return 1;
                }
                if (me == who)
                {
                        send_user(me, "%c%s", '!', "Không thể tự gọi chính mình");
                        return 1;
                }
                if (!me->get_leader() || me->get_leader() != who->get_leader())
                {
                        notify("Số ID bạn đưa vào không phải thành viên trong nhóm");
                        return 1;
                }
                if (get_z(who) == 704)
                {
                        notify("Đối phương đang ở trong Nhà Ngục");
                        return 1;
                }
                if (get_z(who) == 888)
                {
                        notify("Đối Phương ở Vô Song Thành không thể sử dụng");
                        return 1;
                }
                if (get_z(who) == 889)
                {
                        notify("Đối Phương ở Vô Song Cung không thể sử dụng");
                        return 1;
                }
                if (objectp(map = get_map_object(get_z(who))))
                {
                        switch (map->get_map_type())
                        {
                                //  case CAVE_MAP : send_user( me, "%c%s", '!', "Đối phương ở Hang động, không thể truyền tống" );
                                //                    return 1;
                        case BATTLE_MAP:
                                send_user(me, "%c%s", '!', "Đối phương ở Chiến Trường, không thể truyền tống");
                                return 1;
                        }
                }
                else
                        return 1;
                if (who->get_login_flag() < 3)
                {
                        send_user(me, "%c%s", '!', "Đối phương còn chưa chuẩn bị");
                        return 1;
                }
                if (who->is_die())
                {
                        send_user(me, "%c%s", '!', "Đối phương đã chết");
                        return 1;
                }
                if (who->is_store_open())
                {
                        send_user(me, "%c%s", '!', "Đối phương đang bán hàng rong");
                        return 1;
                }
                if (who->get_save("cambayquest"))
                {
                        send_user(me, "%c%s", '!', "Đối phương không thể sử dụng khi đang mang trong mình nhiệm vụ.");
                        return 1;
                }
                if (present("Vật Phẩm Quý Bấu", who, 1, MAX_CARRY * 4))
                {
                        send_user(me, "%c%s", '!', "Đối phương đang áp tiêu, không thể sử dụng.");
                        return 1;
                }
                if (present("Ngân Phiếu", who, 1, MAX_CARRY * 4))
                {
                        send_user(me, "%c%s", '!', "Đối phương đang làm Thương Nhân.");
                        return 1;
                }
                if (present("Cờ Hiệu Vô Song Thành", who, 1, MAX_CARRY * 4))
                {
                        send_user(me, "%c%s", '!', "Đối phương đang mang theo Cờ Hiệu.");
                        return 1;
                }
                if (objectp(npc = who->get_quest("escort.robber#")) && npc->is_escort_robber()) // 寻找蒙面人
                {
                        send_user(me, "%c%s", '!', "对方刚遇到蒙面人.");
                        return 1;
                }
                who->set("conlau_fly", me);
                ben = me->get_gender() == 1 ? "anh ấy" : "cô ấy";
                send_user(who, "%c%s", ':', me->get_name() + " sử dụng Thiên Lý Hữu Tình tìm thấy bạn đang ở " + map->get_name() + " và kêu gọi bạn đến bên cạnh " + ben + ", bạn muốn đến không ?\n" ESC "Đồng ý\n" + sprintf("conlau !.%d\n", me->get_number()) + ESC "Huỷ bỏ\nCLOSE\n");
                item2->add_amount(-1);
                write_user(me, ECHO "Bạn sử dụng" HIY " Thiên Lý Hữu Tình" ECHO ", xin chờ hồi đáp");
                return 1;
        }
        if (arg1 == "!")
        {
                if (!(who = find_any_char(arg2)))
                {
                        return 1;
                }
                if (!who->is_user())
                {
                        return 1;
                }
                if (me == who)
                {
                        send_user(me, "%c%s", '!', "Không thể tự gọi chính mình");
                        return 1;
                }
                if (me->get("conlau_fly") != who)
                        return 1;
                if (!me->get_leader() || me->get_leader() != who->get_leader())
                {
                        notify("Bạn không thể truyền tống đến chỗ đội hữu");
                        return 1;
                }
                if (me->get_save("cambayquest"))
                {
                        notify("Ngươi không thể sử dụng khi đang mang trong mình nhiệm vụ.");
                        return 1;
                }
                if (get_z(me) == 704)
                {
                        notify("Trong Nhà Ngục không thể sử dụng");
                        return 1;
                }
                if (get_z(me) == 888)
                {
                        notify("Ở Vô Song Thành không thể sử dụng");
                        return 1;
                }
                if (get_z(me) == 889)
                {
                        notify("Ở Vô Song Cung không thể sử dụng");
                        return 1;
                }
                if (objectp(map = get_map_object(get_z(me))))
                {
                        switch (map->get_map_type())
                        {
                                //	  case CAVE_MAP : send_user( me, "%c%s", '!', "Bạn ở Hang động, không thể truyền tống" );
                                //                       return 1;
                        case BATTLE_MAP:
                                send_user(me, "%c%s", '!', "Bạn ở Chiến Trường, không thể truyền tống");
                                return 1;
                        }
                }
                else
                        return 1;
                if (objectp(map1 = get_map_object(get_z(who))))
                {
                        if (map1->is_copy_scene())
                        {
                                send_user(me, "%c%s", '!', "Không thể truyền tống lúc đang trong Phó bản");
                                return 1;
                        }
                }
                else
                        return 1;
                if (me->is_die())
                {
                        return 1;
                }
                if (me->is_store_open())
                {
                        send_user(me, "%c%s", '!', "Bạn đang bán hàng rong");
                        return 1;
                }
                if (present("Vật Phẩm Quý Bấu", me, 1, MAX_CARRY * 4))
                {
                        send_user(me, "%c%s", '!', "Bạn đang áp tiêu, không thể sử dụng.");
                        return 1;
                }
                if (present("Ngân Phiếu", me, 1, MAX_CARRY * 4))
                {
                        send_user(me, "%c%s", '!', "Đang làm Thương Nhân không thể sử dụng.");
                        return 1;
                }
                if (present("Cờ Hiệu Vô Song Thành", me, 1, MAX_CARRY * 4))
                {
                        send_user(me, "%c%s", '!', "Mang theo Cờ Hiệu không thể sử dụng.");
                        return 1;
                }
                if (objectp(npc = me->get_quest("escort.robber#")) && npc->is_escort_robber()) // 寻找蒙面人
                {
                        send_user(me, "%c%s", '!', "您刚遇到蒙面人.");
                        return 1;
                }
                z = get_z(who);
                x0 = get_x(who);
                y0 = get_y(who);
                if (p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK))
                {
                        x = p / 1000;
                        y = p % 1000;

                        me->set_login_flag(2); // 跳转保护
                        set_invisible(me, 1);
                        set_effect(me, EFFECT_USER_LOGIN, 4);

                        me->add_to_scene(z, x, y, get_front_xy(x, y, x0, y0));

                        tell_user(me, "Bạn đi đến: %d (%d, %d)", z, x, y);

                        me->delete ("conlau_fly"); // fix lệnh xài thiên lý
                        return 1;
                }
                else
                {
                        if (who)
                                notify("Bạn không tới được nơi %s .", who->get_name());
                        else
                                notify("Bạn không tới được nơi đó");
                        return 1;
                }
        }
        return 1;
}
