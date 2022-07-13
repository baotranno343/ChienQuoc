
#include <ansi.h>

#define SUMMON_LOG "gm/summon.txt" // 召唤日志文件

// 函数：命令处理
int main1(object me, string arg)
{
        object who;
        int z, x, y, x0, y0, p;

        if (is_player(me))
        {
                notify("Bạn không có đủ quyền truy cập.");
                return 1;
        }

        if (!arg)
        {
                send_user(me, "%c%c%d%s", '?', 16, 10, sprintf("Mời nhân vật。\n\nVui lòng nhập số của đối phươngＩＤ：\n" ESC "summon %%s\n"));
                return 1;
        }

        if (!(who = find_any_char(arg)))
        {
                notify("Bạn không thể tìm thấy người này。");
                return 1;
        }
        else if (!clonep(who))
        {
                notify("Không thể triệu hồi nhân vật này.");
                return 1;
        }
        else if (who == me)
        {
                notify("Bạn không thể tự gãi mình.");
                return 1;
        }

        z = get_z(me);
        x0 = get_x(me);
        y0 = get_y(me);

        if (p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK))
        {
                x = p / 1000;
                y = p % 1000;
                who->add_to_scene(z, x, y, get_front_xy(x, y, x0, y0), 40971, 0, 40971, 0);
                tell_user(me, HIY "Bạn đã mời %s đến đây。", who->get_name());
                write_user(who, HIY "%s Mời bạn đến đây。", me->get_name());

                if (userp(who))
                        log_file(SUMMON_LOG, sprintf("%s %s mời %s(%s)đến %d (%d,%d)。\n",
                                                     short_time(), me->get_id(), who->get_name(), who->get_id(), z, x, y));

                return 1;
        }
        else
        {
                notify(who->get_name() + "Không thể đến với bạn.");
                return 1;
        }

        return 1;
}

int main(object me, string arg)
{
        int i, size;
        string *player;

        if (is_player(me))
        {
                notify("您没有足够的权限。");
                return 1;
        }
        player = explode(arg, ",");
        if ((size = sizeof(player)) == 0)
        {
                main1(me, arg);
                return 1;
        }
        for (i = 0; i < size; i++)
        {
                main1(me, player[i]);
        }
        return 1;
}