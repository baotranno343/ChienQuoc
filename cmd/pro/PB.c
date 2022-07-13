
#include <time.h>
#include <ansi.h>
#include <cmd.h>

#include <npc.h>
#include <city.h>
#include <action.h>
#include <effect.h>
#include <skill.h>
#include <public.h>
// 函数：命令处理
int main(object me, string arg)
{
    object *member, map;
    int i, size;

    if (!is_gm2(me) && !is_god(me))
    {
        notify("Bạn không đủ quyền。");
        return 1;
    }
    i = to_int(arg);

    if (i == 0)
    {
        "tran/phuban/go"->set_open(i);
        if (get_map_object(2999))
        {
            map = get_map_object(2999);
            member = map->get_all_user(map);
            map->destruct_virtual_map(map, map->get_id());
            for (i = 0, size = sizeof(member); i < size; i++)
            {
                member[i]->add_to_scene(80, 275, 185);
            }
        }

        notify("Đóng Phụ Bản Thành Công");
        return 1;
    }
    if (i == 1)
    {
        "tran/phuban/go"->set_open(i);
        notify("Mở Phụ Bản Thành Công");
        return 1;
    }

    return 1;
}
