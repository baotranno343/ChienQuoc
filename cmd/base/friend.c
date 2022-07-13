
#include <ansi.h>

// 函数:命令处理
int main(object me, string arg)
{
        object who, *user;
        string name, *key;
        int id, i, size;
        mapping friends;

        if (!arg)
                return 1;
        if (arg == "refresh")
        {
                if (is_player(me) && gone_time(me->get_time("friend")) < 1)
                {
                        return 1;
                }
                me->set_time("friend", time());
                me->refresh_friend();
                return 1;
        }
        if (sscanf(arg, "+ %d", id))
        {
                if (!(who = find_player(sprintf("%d", id))))
                {
                        notify("Không tìm thấy người này.");
                        return 1;
                }
                if (me == who)
                {
                        notify("Không thể tự thêm chính mình làm bằng hữu.");
                        return 1;
                }
                if (who->get_no_friend())
                {
                        notify("Đối phương đã không muốn kết bạn.");
                        return 1;
                }
                if (is_god(who))
                {
                        notify("Không Thể Kết Bạn Với Quản Trị Viên.");
                        return 1;
                }
                friends = me->get_friend_dbase();
                key = keys(friends);
                size = sizeof(key);
                if (size >= 5)
                {
                        notify("Số lượng bằng hữu đã đạt tối đa 10 người rồi.");
                        return 1;
                }
                me->add_friend(who, 0);
                "/cmd/base/black"->main(me, sprintf("- %d", who->get_number()));
                if (who->get_friend_id(me->get_number()))
                {
                        send_user(who, "%c%c%d", 0x46, 9, me->get_number());
                        send_user(me, "%c%c%d", 0x46, 9, who->get_number());
                }
                else
                        send_user(me, "%c%c%d", 0x46, 9, who->get_number());
        }
        else if (sscanf(arg, "* %d", id))
        {
                if (!(who = find_player(sprintf("%d", id))))
                {
                        notify("Không tìm thấy người này.");
                        return 1;
                }
                if (me == who)
                {
                        notify("Không thể tự thêm chính mình làm bằng hữu.");
                        return 1;
                }
                if (who->get_no_friend())
                {
                        notify("Đối phương đã không muốn kết bạn.");
                        return 1;
                }
                friends = me->get_friend_dbase();
                key = keys(friends);
                size = sizeof(key);
                if (size >= 10)
                {
                        notify("Số lượng bằng hữu đã đạt tối đa 10 người rồi.");
                        return 1;
                }
                me->add_friend(who, 1);
                send_user(me, "%c%c%d", 0x46, 9, who->get_number());
        }
        else if (sscanf(arg, "/ %d", id))
        {
                me->set_notify(id, 0);
        }
        else if (sscanf(arg, "! %d", id))
        {
                me->set_notify(id, 1);
        }
        else if (sscanf(arg, "- %d", id))
        {
                send_user(me, "%c%s", ':', sprintf(HIR "%s ( %d ) " NOR "là bằng hữu của bạn, bạn chắc chắn muốn đoạn tuyệt không ?\n" ESC "Ta quyết định đoạn tuyệt\nfriend x %d\n" ESC "Ta phải suy nghĩ lại……\nCLOSE\n", me->get_friend_name(id), id, id));
        }
        else if (sscanf(arg, "x %d", id))
        {
                me->remove_friend(id);
        }
        else if (sscanf(arg, "? %s", name))
        {
                if (!objectp(who = find_player(name)))
                {
                        if (!arrayp(user = users()) // 获取所有玩家
                            || !arrayp(user = filter_array(user - ({me}), (
                                                                              : $1->get_name() == $2:),
                                                           name)) // 判断名字吻合(除自己外)
                            || !sizeof(user)                      // 用户个数大于０
                            || !objectp(who = user[0]))           // 取第一个用户
                        {
                                notify("Tuần tra không có người này.");
                                return 1;
                        }
                }

                if (!objectp(who))
                {
                        notify("Tuần tra không có người này.");
                        return 1;
                }

                send_user(me, "%c%c%d%s", 0x46, 2, who->get_number(),
                          sprintf("%-12s Nhân vật : %s \nSố ID : %d \nGiới Tính : %s\n"
                                  "Quốc Gia : %s \nMôn Phái : %s \nBang Phái : %s \nCấp Bậc : %d \n",
                                  who->get_name(), who->get_name(), who->get_number(),
                                  who->get_gender() == 1 ? "Nam" : "Nữ",
                                  who->get_city_name(), who->get_fam_name(), who->get_org_position() > 0 ? who->get_org_name() : "",
                                  who->get_level()));
        }

        return 1;
}
