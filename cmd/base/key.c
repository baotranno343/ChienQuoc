
#include <ansi.h>
#include <task.h>
#include <music.h>

// 函数：命令处理
int main(object me, string arg)
{
        int id, level;

        if (!arg)
                return 1;

        if (sscanf(arg, "%d %s", id, arg) == 2)
        {
                if (id < 1 || id > 100)
                        return 1;

                if (arg == "0")
                        me->delete_hotkey(sprintf("%d", id));
                else
                {
                        me->set_hotkey(sprintf("%d", id), arg);
                }
        }

        return 1;
}
