#include <equip.h>
// 函数：命令处理
int main(object me, string arg)
{
        object *user;
        string result, readf, *line;
        int i;
        if (is_player(me))
        {
                notify("Không đủ quyền hạn");
                return 1;
        }
        result = "sys/sys/user2"->numberToId(to_int(arg));
        if (result != "")
        {
                printf("Tài khoản của người dùng là:  " + result);
        }
        else
        {
                printf("Không tìm thấy tài khoản ");
        }
        return 1;
}
