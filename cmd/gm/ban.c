
// 函数：命令处理
int main(object me, string arg)
{
        string *ip, site, result;
        int i, size;

        if (me != this_player(1) || is_player(me))
        {
                notify("Không đủ quyền lực");
                return 1;
        }

        if (!arg)
        {
                ip = CHECK_D->get_banned_ip();
                result = "Hãy nhập vào IP:\n";
                for (i = 0, size = sizeof(ip); i < size; i++)
                        result += ip[i] + "\n";
                tell_user(me, result);
        }
        else if (sscanf(arg, "+ %s", site) == 1)
        {
                if (site[ < 1] == '*' || site[ < 1] == '?' || site[ < 1] == '+')
                {
                        notify("Không thể đóng bằng *, +,? IP ở cuối.");
                        return 1;
                }
                else
                {
                        CHECK_D->add_banned_ip(site);
                        tell_user(me, "Đã baned IP này");
                }
        }
        else if (sscanf(arg, "- %s", site) == 1)
        {
                CHECK_D->remove_banned_ip(site);
                tell_user(me, "Đã huỷ bỏ baned IP này.");
        }

        return 1;
}
