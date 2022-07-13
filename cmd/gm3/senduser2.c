#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

// 函数：命令处理
int main(object me, string arg)
{
        int so, so1, so2, so3, so4, so5, i, min, max;
        if (is_player(me))
        {
                notify("Không đủ quyền hạn");
                return 1;
        }
        if (arg && sscanf(arg, "%d %d %d %d %d %d", min, max, so, so1, so2, so3) == 6)
        {
                for (i = min; i < max; i++)
                {
                        // send_user(me, "%c%c%c%c%c", 0x45, i, so1, so2, so3);
                        send_user(me, "%w%d%d%d", so, i, so1, so2);
                }
        }
        else if (arg && sscanf(arg, "%d %d %d %d %d", min, max, so, so1, so2) == 5)
        {
                for (i = min; i < max; i++)
                {
                        // send_user(me, "%c%c%c%c", 0x45, i, so1, so2);
                        send_user(me, "%w%d%d", so, i, so1);
                }
        }
        else if (arg && sscanf(arg, "%d %d %d %d", min, max, so, so1) == 4)
        {
                for (i = min; i < max; i++)
                {
                        // send_user(me, "%c%c%c", 0x45, i, so1);
                        send_user(me, "%w%d", so, i);
                }
        }

        else
                return 1;
        printf("min:  " + min);
        printf("max: " + max);
        printf("so1:  " + so1);
        printf("so2: " + so2);
        printf("so3: " + so3);
        printf("so4: " + so4);
        return 1;
}
