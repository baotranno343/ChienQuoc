#include <public.h>
#include <time.h>
#include <ansi.h>
// 函数:获取时间字串
void xoa_save(object user, int flag)
{
        mixed *mixTime;
        int iTime = time();
        mixTime = localtime(iTime);
        // object *user;
        // int size, i;
        // if (arrayp(user = USER_D->get_user()))
        // {
        //         size = sizeof(user);
        //         if (size < 200)
        //         {
        //CHAT_D->sys_channel(0, HIR + size);
        // for (i = 0; i < size; i++)
        if (flag == 1) // chyạ khi qua ngày mới
        {
                if (user)
                {
                        if (mixTime[TIME_YDAY] != user->get_save("now_day"))
                        {
                                user->set_save("now_day", mixTime[TIME_YDAY]);
                                user->clean_cuthudaotime();
                                tell_user(user, sprintf("Đã thiết lập lại thời gian cự thú đảo"));
                                //
                                if (user->get_save("cambayquest"))
                                        user->delete_save("cambayquest");
                                if (user->get_save("lsk"))
                                        user->delete_save("lsk");
                                if (user->get_save("kcdt"))
                                        user->delete_save("kcdt");
                                //
                                if (user->get_save_2("ptt"))
                                        user->delete_save_2("ptt");
                                //
                                if (user->get_save("gtt.day"))
                                        user->delete_save("gtt.day");

                                if (user->get_save_2("banditi"))
                                        user->delete_save_2("banditi");

                                if (user->get_save_2("apTieu"))
                                        user->delete_save_2("apTieu");
                        }
                }
                return;
        }
        if (flag == 2) // chạy khi reload
        {
                if (user)
                {
                        if (user->get_save("cambayquest"))
                                user->delete_save("cambayquest");
                        // tell_user(user, sprintf("Đã thiết lập lại cự thú đảo"));
                }
        }
        //         }
        // }
        return;
}
// 函数:获取时间字串
void thongbao_event(string arg)
{
        string *list = MAIN_D->getlist();
        int kenh = MAIN_D->get_kenh(), i;
        for (i = 0; i < sizeof(list); i++)
        {
                if (kenh == to_int(list[i]))
                        continue;
                ghi_file(sprintf("bang/check%s.txt", list[i]), sprintf("\nthongbao %s", arg));
        }
        return;
}
void check_chientruong(object me)
{
        string *titlect = ({"P001", "P002", "P003", "P004", "P005", "P006", "P007", "P008", "P009", "P010", "P011"});
        mixed *mixTime;
        int i, iTime = time();
        mixTime = localtime(iTime);

        if (me->get_save_2("changping.scoretime") != mixTime[TIME_MON])
        {
                me->set_save_2("changping.scoretime", mixTime[TIME_MON]);
                me->set_save_2("changping.score", (me->get_save_2("changping.score") / 2));
                tell_user(me, "Hôm nay là ngày đầu tháng, điểm chiến trường của bạn đã bị chia đôi.");
        }
        for (i = 0; i < sizeof(titlect); i++)
        {

                if (me->have_title(titlect[i]))
                {

                        if (me->get_save_2("changping.ranktime") > 0 && time() > me->get_save_2("changping.ranktime"))
                        {

                                me->delete_save_2("changping.ranktime");
                                me->delete_title(titlect[i]);
                                tell_user(me, "Danh hiệu chiến trường của bạn đã hết hạn, danh hiệu của bạn đã bị xóa");
                        }
                        else
                        {

                                me->show_title(titlect[i]);
                        }

                        break;
                }
        }
        return;
}
void nap_the(object me)
{
        int i, knb, tichluy;
        string *napthe;

        if (file_exist(sprintf("napthe/%d.dat", me->get_number())))
        {
                napthe = explode(read_file(sprintf("napthe/%d.dat", me->get_number())), "\n");
                if (sizeof(napthe))
                {

                        for (i = 0; i < sizeof(napthe); i++)
                        {
                                if (napthe[i][0] >= '0' && napthe[i][0] <= '9')
                                {
                                        if (me->get_save_2("napthe.check") != 1)
                                                me->set_save_2("napthe.check", 1);
                                        knb = to_int(napthe[i]) * 75 / 1000;
                                        tichluy = to_int(napthe[i]) / 1000;
                                        me->add_save("diemtlnt", tichluy);
                                        "/sys/sys/test_db"->add_yuanbao(me, knb);
                                        send_user(me, "%c%c%w%s", ':', 3, 5302, sprintf("Nhân viên chuyển Kim Nguyên Bảo : \nBạn đã nạp thành công  %d Kim Nguyên Bảo, hãy kiểm tra tài khoản của bạn ! \n" ESC "Xác nhận\nCLOSE", knb / 10));
                                        tell_user(me, "Bạn vừa nạp thành công %d Kim Nguyên Bảo, điểm tích lũy nạp thẻ của bạn tăng lên %d điểm", knb / 10, tichluy);
                                        log_file("napthe.dat", sprintf("%s %s(%d) nạp thành công %d Kim Nguyên Bảo\n", short_time(), me->get_id(), me->get_number(), knb / 10));
                                }
                        }
                }
                rm(sprintf("napthe/%d.dat", me->get_number()));
        }
        return;
}
object check_dame_max(object me)
{
        string *key, id_dame_max;
        int i, dame_max = 0;
        mapping usersdame;
        object who;
        if (objectp(me) && me->is_count_dame_boss())
        {
                if (usersdame = me->get_2("dame"))
                {
                        for (i = 0; i < sizeof(key = keys(usersdame)); i++)
                        {
                                if (to_int(usersdame[key[i]]) > dame_max)
                                {
                                        id_dame_max = key[i];
                                        dame_max = to_int(usersdame[key[i]]);
                                }
                        }

                        // for (i = 0; i < sizeof(usersdame); i++)
                        // {
                        // 	printf(usersdame[0]);
                        // }
                        if (!who = find_any_char(id_dame_max))
                        {
                                CHAT_D->sys_channel(0, sprintf("Nguời chơi gây dame nhiều nhất không có trong game"));
                                return 0;
                        }
                        CHAT_D->sys_channel(0, sprintf("Người chơi có ID là: %s, đã gây sát thương nhiều nhất: %d sát thương và nhận được phần thưởng", id_dame_max, dame_max));
                        return who;
                }
        }
        return 0;
}
void say_dame_max(object me)
{
        string *key, id_dame_max;
        int i, dame_max = 0;
        mapping usersdame;
        object who;
        if (objectp(me) && me->is_count_dame_boss())
        {
                if (usersdame = me->get_2("dame"))
                {
                        for (i = 0; i < sizeof(key = keys(usersdame)); i++)
                        {
                                if (to_int(usersdame[key[i]]) > dame_max)
                                {
                                        id_dame_max = key[i];
                                        dame_max = to_int(usersdame[key[i]]);
                                }
                        }
                }

                if (!who = find_any_char(id_dame_max))
                {
                        "/cmd/base/say"->say(me, sprintf("Không có người gây game nhiều nhất"));
                        return;
                }
                "/cmd/base/say"->say(me, sprintf("Người chơi có ID là: %s, đã gây sát thương nhiều nhất: %d sát thương", id_dame_max, dame_max));
                //    me->delete_2("dame");
                // CHAT_D->sys_channel(0, sprintf("Sát Thương Đã Reset "));
        }
        return;
}
void getItemAround(object me)
{
        object *who;
        int z, x, y, i, dy;
        z = get_z(me);
        x = get_x(me);
        y = get_y(me);

        if (who = get_scene_object(z, x, y, ITEM_TYPE))
        {
                for (i = 0; i < sizeof(who); i++)
                        if (who[i]->get_user_id() == me->get_id())
                        {
                                "cmd/std/get"->main(me, sprintf("%d %d", get_x(who[i]), get_y(who[i])));
                        }
        }
}