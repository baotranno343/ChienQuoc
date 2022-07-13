
#include <ansi.h>
#include <city.h>
#include <chia_kenh.h>
#define MAX_ORG_MEMBER 80 // 帮众人数上限

// 函数：生成二进制码
void SAVE_BINARY() {}

// 函数：申请入帮
int do_join(object who, object me, string arg)
{
        string name1, name2, name3, name4;
        string cmd;
        // if (MAIN_D->get_kenh() != KENH_BANG)
        // {
        //         send_user(who, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
        //         return;
        // }
        if (gone_time(who->get("time_join")) < 10)
        {
                send_user(who, "%c%s", '!', "Vui lòng thử lại sau 10 giây");
                return 0;
        }

        name1 = who->get_org_name();
        name2 = me->get_org_name();
        if (stringp(name1) && name1 != "")
        {
                send_user(who, "%c%s", '!', "Bạn đã là \"" + name1 + "\" Bang Chúng");
                return 0;
        }

        name3 = who->get_city_name();
        name4 = me->get_city_name();

        if (name3 != "" && name3 != name4)
        {
                send_user(who, "%c%s", '!', "Gia nhập \"" + name2 + "\" cần có " + name4 + " Hộ tịch");
                return 0;
        }

        send_user(who, "%c%s", '!', "Bạn xin gia nhập \"" + name2 + "\".");
        who->set("time_join", time());
        if (MAIN_D->get_kenh() != KENH_BANG)
        {
                ghi_file(sprintf("bang/check%d.txt", KENH_BANG), sprintf("\ndo_join %d:%s:%s", who->get_number(), who->get_id(), name2));
                return 1;
        }

        me->init_join_info(who->get_number(), who->get_id(), who->get_name(),
                           who->get_gender(), who->get_level(),
                           who->get_fam_name(), who->get_armor_code(), time());
        return 1;
}

// 函数：申请信息
void do_apply(object who, object me, string arg)
{
        string name1, name2, *name;
        int id, number, i, size;
        if (MAIN_D->get_kenh() != KENH_BANG)
        {
                send_user(who, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
                return;
        }
        id = getoid(me);

        name1 = who->get_org_name();
        name2 = me->get_org_name();

        if (stringp(name1) && stringp(name2) && name1 == name2) // 本帮帮众
        {
                number = to_int(arg);

                if (!number) // 显示帮派界面
                {
                        send_user(who, "%c%c%d%c%s", 0x95, 20, id, who->get_org_position(), me->get_org_name());

                        size = me->sizeof_join_dbase();
                        name = me->get_all_join();

                        for (i = 0; i < size; i++)
                        {
                                number = to_int(name[i]);
                                send_user(who, "%c%c%d%w%s", 0x95, 21, number,
                                          me->get_join_level(number), me->get_join_name(number));
                        }
                }
                else // 显示详细信息
                {
                        if (me->get_join_family(number) == 0)
                                send_user(who, "%c%c%d%c%d%d%s", 0x95, 22, number,
                                          me->get_join_gender(number), me->get_photo(number),
                                          me->get_join_time(number), " ");
                        else
                                send_user(who, "%c%c%d%c%d%d%s", 0x95, 22, number,
                                          me->get_join_gender(number), me->get_photo(number),
                                          me->get_join_time(number), me->get_join_family(number));
                }
        }
}
// void do_accept3(object me, string id, string arg, int sl)
//  {
//          object char;
//          string name1, name2, name3, name4;
//          string *list = MAIN_D->getlist();
//          int number, kenh, flag, stt, i;
//          name2 = me->get_org_name();
//          kenh = MAIN_D->get_kenh();
//          number = to_int(arg);
//          if ("sys/sys/user2"->check_id_online(number) != 0 && sl <= (sizeof(list) + 1))
//          {
//                  if (sl == sizeof(list))
//                  {
//                          for (i = 0; i < sizeof(list); i++)
//                          {
//                                  if (kenh == to_int(list[i]))
//                                          continue;

//                                 ghi_file(sprintf("bang/check%s.txt", list[i]), sprintf("\nkicknumber %d", number));
//                         }
//                 }
//                 stt = member_array(sprintf("%d", kenh), list) + 1;
//                 if (stt >= sizeof(list))
//                 {
//                         stt = 0;
//                 }
//                 kenh = to_int(list[stt]);
//                 // if (kenh > sizeof(list))
//                 //         kenh = 1;
//                 ghi_file(sprintf("bang/check%d.txt", kenh), sprintf("\ndo_accept %s:%s:%s:%d", name2, id, arg, sl + 1));
//                 return;
//         }

//         if (!(char = find_player(sprintf("%d", number))))
//         {
//                 char = new (USER);
//                 char->set_id(id);
//                 if (!char->restore())
//                 {
//                         destruct(char);
//                         return;
//                 }

//                 flag = 1;
//         }
//         char->set_org_position(ORG_MEMBER);
//         char->set_org_name(name2);
//         char->set_org_title("－－");
//         char->set_org_time(time());
//         char->add_title("C008");
//         char->show_title("C008");
//         name3 = char->get_city_name();
//         name4 = me->get_city_name();
//         if (!stringp(name3) || name3 == "" || name3 != name4)
//         {
//                 char->set_city_name(name4);
//         }
//         char->save();

//         FAMILY_D->org_channel(name2, 0, sprintf(HIR "%s(%d) gia nhập Bang %s!", char->get_name(), char->get_number(), name2));
//         if (flag)
//                 destruct(char);
// }
void do_accept3(object me, string id, string arg)
{
        object char;
        string name1, name2, name3, name4;
        string *list = MAIN_D->getlist();
        int number, kenh, flag, stt, i, checkkenh;
        name2 = me->get_org_name();
        kenh = MAIN_D->get_kenh();
        number = to_int(arg);

        if ((checkkenh = "sys/sys/user2"->check_id_online(number)) && checkkenh != kenh)
        {

                ghi_file(sprintf("bang/check%d.txt", checkkenh), sprintf("\ndo_accept %s:%s:%s", name2, id, arg));
                return;
        }
        if (!(char = find_player(sprintf("%d", number))))
        {
                char = new (USER);
                char->set_id(id);
                if (!char->restore())
                {
                        destruct(char);
                        return;
                }

                flag = 1;
        }
        char->set_org_position(ORG_MEMBER);
        char->set_org_name(name2);
        char->set_org_title("－－");
        char->set_org_time(time());
        char->add_title("C008");
        char->show_title("C008");
        name3 = char->get_city_name();
        name4 = me->get_city_name();
        if (!stringp(name3) || name3 == "" || name3 != name4)
        {
                char->set_city_name(name4);
        }
        char->save();

        FAMILY_D->org_channel(name2, 0, sprintf(HIR "%s(%d) gia nhập Bang %s!", char->get_name(), char->get_number(), name2));
        if (flag)
                destruct(char);
}
// 函数：接收入帮
void do_accept(object who, object me, string arg)
{
        object char;
        string name1, name2, name3, name4;
        int number, flag, j, kenh = MAIN_D->get_kenh(), flag2;

        name1 = who->get_org_name();
        name2 = me->get_org_name();

        if (stringp(name1) && stringp(name2) && name1 == name2 && who->get_org_position() >= ORG_XIANGZHU) // 本帮官员
        {
                if (me->sizeof_member_dbase() >= me->get_max_number())
                {
                        send_user(who, "%c%s", '!', "\"" + name2 + "\" nhân số quá nhiều");
                        return;
                }

                number = to_int(arg);

                if (stringp(me->get_join_id(number)) && sizeof(me->get_join_id(number)) >= 3)
                {
                        if (!(char = find_player(arg)))
                        {

                                if ("sys/sys/user2"->check_id_online(number) != 0)
                                {
                                        flag2 = 1;
                                }
                                char = new (USER);
                                char->set_id(me->get_join_id(number));
                                if (!char->restore())
                                {
                                        send_user(who, "%c%s", '!', "Vị này không tồn tại !");
                                        destruct(char);
                                        return;
                                }
                                flag = 1; // 离线
                        }

                        name3 = char->get_org_name();
                        if (stringp(name3) && name3 != "" && char->get_org_position() > 0)
                        {
                                send_user(who, "%c%s", '!', me->get_join_name(number) + "Đã là \"" + name3 + "\" Bang Chúng");
                                if (flag)
                                        destruct(char);
                                return;
                        }
                        name3 = char->get_city_name();
                        name4 = me->get_city_name();

                        if (!stringp(name3) || name3 == "" || name3 != name4)
                        {
                                char->set_city_name(name4);
                        }
                        char->set_org_position(ORG_MEMBER);
                        char->set_org_name(name2);
                        char->set_org_title("－－");
                        char->set_org_time(time());
                        char->add_title("C008");
                        char->show_title("C008");
                        if (flag2)
                        {
                                // for (j = 1; j < 4; j++)
                                //{
                                //      if (kenh == j)
                                //            continue;
                                ghi_file(sprintf("bang/check%d.txt", "sys/sys/user2"->check_id_online(number)), sprintf("\ndo_accept %s:%s:%s", me->get_org_name(), char->get_id(), arg));

                                //}
                        }
                        else
                        {
                                char->save();
                        }
                        char->log_legend(sprintf("Bạn xin gia nhập \"%s\"！", name2));
                        me->init_member_info(char->get_number(), char->get_id(), char->get_name(),
                                             char->get_armor_code(), char->get_gender(), char->get_level(),
                                             char->get_fam_name(),
                                             char->get_org_title(), time(), flag ? char->get_quit_time() : 0);
                        send_user(who, "%c%c%d%d%c%d%d%c%s", 0x95, 11, char->get_number(),
                                  time(), !flag, 0, 0, char->get_level(), sprintf("%-12s%s", char->get_name(), char->get_org_title()));
                        me->delete_join_info(number);
                        send_user(who, "%c%c%d", 0x95, 23, number);
                        send_user(who, "%c%c%d", 0x95, 96, number);
                        me->add_total(1);

                        FAMILY_D->org_channel(name2, 0, sprintf(HIR "%s tiếp nhận %s(%d) gia nhập Bang !", who->get_name(), char->get_name(), char->get_number()));
                        WUSHUANG->check_org_title(char);
                        if (flag)
                                destruct(char);
                        else
                        {
                                send_user(char, "%c%c%c%s", 0x3d, 49,
                                          char->get_org_position(), char->get_org_name());
                        }
                }
        }
        else
                send_user(who, "%c%s", '!', "Bạn không có quyền nhận người khác gia nhập Bang");
}

// 函数：拒绝入帮
void do_refuse(object who, object me, string arg)
{
        string name1, name2;
        int number;
        if (MAIN_D->get_kenh() != KENH_BANG)
        {
                send_user(who, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
                return;
        }
        name1 = who->get_org_name();
        name2 = me->get_org_name();

        if (stringp(name1) && stringp(name2) && name1 == name2 && who->get_org_position() > ORG_TANGZHU) // 本帮官员
        {
                number = to_int(arg);

                if (me->get_join_id(number))
                {
                        me->delete_join_info(number);
                        send_user(who, "%c%c%d", 0x95, 23, number);
                        send_user(who, "%c%c%d", 0x95, 96, number);
                }
        }
        else
                send_user(who, "%c%s", '!', "Bạn không có quyền cự tuyệt người khác gia nhập Bang");
}
