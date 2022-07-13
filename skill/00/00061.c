
#include <ansi.h>
#include <item.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>

#define THIS_PERFORM 0061
#define PF_NAME "Sử dụng tín vật"

// 函数：获取描述
string get_desc(object me)
{
        return "[ " PF_NAME " ]\n Dùng tín vật\n ";
}

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
        object item;

        if (!objectp(item = me->get_equip(FAMILY_TYPE)))
                return 1;
        item->get_use_effect(me);
        return 1;
}

// 函数：获取指令类型
int get_perform_type() { return ON_ME_7; }

// 函数：能否使用指令
void can_perform(object me)
{
        object item;
        send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 60, 0, PF_NAME);
}
