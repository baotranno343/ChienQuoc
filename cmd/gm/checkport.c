#include <equip.h>
// 函数：命令处理
int main(object me, string arg)
{
        object *user, map;
        string result, readf, *line;
        int i;
        if (is_player(me))
        {
                notify("Không đủ quyền hạn");
                return 1;
        }

        printf("Port Hiện Tại Của Server: " + MAIN_D->get_port());
        printf("Kênh Hiện Tại Của Server: " + MAIN_D->get_kenh());
        map = get_map_object(get_z(me));

        return 1;
}
