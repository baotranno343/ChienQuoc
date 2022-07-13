
#include <effect.h>
#include <map.h>
#include <ansi.h>
void do_timnguoi();
void awaitText(object map, int stt);
void validate(object me);
// 函数：命令处理
int main(object me, string arg)
{
        object who, item, item2, npc, map, map1;
        int z, z2, x, y, x0, y0, p;
        string arg1, arg2, ben;

        if (sscanf(arg, "%s.%s", arg1, arg2) != 2)
        {

                return 1;
        }
        if (arg1 == "?")
        {
                tell_user(me, "Tiến hành tìm người tỷ thí");
                do_timnguoi();
                return;
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
                if (validate(me) != 0)
                {
                        return 1;
                }
                if (validate(who) != 0)
                {
                        return 1;
                }

                if (who->get("timnguoi") != me->get_number())
                {
                        send_user(me, "%c%s", '!', "Hết giờ chấp thuận");
                        return 1;
                }
                who->set("timnguoiAcp", 1);
                if ((z = find_map_flag(1000, 2999, 0)) > 0)
                {
                        p = 894;
                        init_virtual_map(z, p); // 生成虚拟地图
                        map = new ("/inh/std/cqmc2");
                        map->set_name("Tỷ Thí Đài");
                        map->set_client_id(p);
                        set_map_object(map, map->set_id(z));
                        map->set_no_fight(1);
                }
                if (!(p = efun::get_xy_point(894, IS_CHAR_BLOCK)))
                {

                        return 1;
                }
                x = (p % 1000000) / 1000;
                y = p % 1000;
                who->add_to_scene(z, x, y);
                me->add_to_scene(z, x, y);
                map->awaitText(map, 1);
        }
        return 1;
}
int validate(object me)
{
        object npc;
        int z;
        z = get_z(me);
        if (z != 001 && z != 10 && z != 20 && z != 30 && z != 40 && z != 50 && z != 60 && z != 70 && z != 80)
        {

                return 1;
        }

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
                send_user(me, "%c%s", '!', "Họ vừa gặp một người đeo mặt nạ.");
                return 1;
        }
        return 0;
}
void do_timnguoi()
{

        object *user, me;
        int i, size, z, lvMe, lvUser, *idArray, count;
        count = 0;
        me = this_player();
        lvMe = me->get_level();
        idArray = ({});

        if (arrayp(user = users()))
        {
                for (i = 0, size = sizeof(user); i < size; i++)
                {

                        if (user[i] == me)
                        {
                                continue;
                        }

                        //	printf(user[i]->get_number());
                        lvUser = user[i]->get_level();
                        if (lvUser <= lvMe + 10 && lvUser >= lvMe - 10)
                        {
                                if (validate(user[i]) != 0)
                                {
                                        continue;
                                }
                                idArray += ({user[i]->get_number()});
                        }
                }
        }
        if (sizeof(idArray))
        {
                //CHAT_D->vip_channel(1, sprintf(CHAT " %s : %d ", "1 ", sizeof(idArray)));
                call_out("do_timnguoiArray", 5, idArray, me);
        }
        else
        {
                tell_user(me, "Không tìm thấy người nào");
        }
        return;
}
void do_timnguoiArray(int *idArray, object me)
{
        int i, size;
        object user;
        remove_call_out("do_timnguoiArray");
        if (objectp(me))
        {
                if (me->get("timnguoiAcp") == 1 || validate(me) != 0)
                {
                        me->delete ("timnguoi");
                        me->delete ("timnguoiAcp");
                        return;
                }

                if ((size = sizeof(idArray)))
                {
                        if (user = find_player(sprintf("%d", idArray[0])))
                        {
                                me->set("timnguoi", idArray[0]);

                                //   CHAT_D->vip_channel(1, sprintf(CHAT " %s : %d ", "2 ", sizeof(idArray)));
                                send_user(user, "%c%s", ':', me->get_name() + " muốn thách đấu với bạn, có chấp nhận lời thách đấu này không ? \n" ESC "Đồng ý\n" + sprintf("timnguoi !.%d\n", me->get_number()) + ESC "Huỷ bỏ\nCLOSE\n");
                                tell_user(me, "Đã tìm thấy người chơi, vui lòng đợi xác nhận.");
                        }
                        idArray -= ({idArray[0]});
                        call_out("do_timnguoiArray", 5, idArray, me);
                        return;
                }
                if (!(size = sizeof(idArray)))
                {

                        tell_user(me, "Không tìm thấy người nào! Vui lòng quay lại sau");
                        me->delete ("timnguoi");
                }
        }
        return;
}
