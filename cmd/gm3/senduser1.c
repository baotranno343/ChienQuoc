
// 函数：命令处理
int main(object me, string arg)
{
        int so1, so2, so3, so4, so5;

        if (is_player(me))
        {
                notify("Không đủ quyền hạn");
                return 1;
        }
        if (arg && sscanf(arg, "%d %d %d %d", so1, so2, so3, so4) == 4)
        {
                send_user(me, "%c%c%c%c%c", 0x45, so1, so2, so3, so4);
        }
        else if (arg && sscanf(arg, "%d %d %d", so1, so2, so3) == 3)
        {
                send_user(me, "%c%c%c%c", 0x45, so1, so2, so3);
        }
        else if (arg && sscanf(arg, "%d %d", so1, so2) == 2)
        {
                send_user(me, "%c%c%c", 0x45, so1, so2);
        }

        else
                return 1;

        printf("so1:  " + so1);
        printf("so2: " + so2);
        printf("so3: " + so3);
        printf("so4: " + so4);

        return 1;
}
