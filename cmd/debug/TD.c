
#include <ansi.h>

// 函数：命令处理
int main(object me, string arg)
{
        object who;

        if (is_player(me))
        {
                notify("Không đủ quyền hạn.");
                return 1;
        }

        if (!arg)
                return 1;

        // if (arg == "none")
        // {
        //         who->set_snooper(0);
        //         tell_user(me, "Huỷ bỏ theo dõi");
        //         return 1;
        // }

        if (!arg)
        {
                notify("Muốn làm gì?");
                return 1;
        }

        if (!(who = find_player(arg)))
        {
                notify("Không tìm thấy người này");
                return 1;
        }
        if (who->get_snooper())
        {
                who->set_snooper(0);
                tell_user(me, "Huỷ bỏ theo dõi");
                return 1;
        }
        else
        {
                who->set_snooper(me);
                tell_user(me, "Bạn bắt đầu theo dõi %s(%d).", who->get_name(), who->get_number());

                return 1;
        }
        return 1;
}
