
// 函数：命令处理
int main(object me, string arg)
{
        object *user;
        string result;
        int i, size, diem;

        if (is_player(me))
        {
                notify("Không đủ quyền hạn");
                return 1;
        }
        if (!arg)
                return 1;
        if (arg == 0)
                return 1;
        if (sscanf(arg, "%d", diem) == 1)
        {
                if (arrayp(user = USER_D->get_user()))
                {
                        size = sizeof(user);
                        result = sprintf("Hiện tại có %d người chơi :\n", size);
                        if (size < 200)
                        {
                                for (i = 0; i < size; i++)
                                        if (user[i])
                                        {
                                                user[i]->add_knbkhoa(diem * 10);

                                                tell_user(user[i], sprintf("Bạn đã được tặng %d KNB Khóa", diem));
                                        }
                        }
                        tell_user(me, "Tặng KNB Thành CÔng");
                }
                else
                        tell_user(me, "Hiện tại không có người chơi");
        }
        return 1;
}
