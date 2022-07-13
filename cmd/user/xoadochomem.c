
// 函数：命令处理
int main(object me, string arg)
{
        object item, *inv;
        int i;

        if (!arg)
        {
                notify("Bạn muốn gì ?");
                return 1;
        }

        if (!(item = find_any_object(arg)))
        {
                notify("Không tìm thấy.");
                return 1;
        }
        if (item == me)
        {
                notify("Bạn muốn gì ?");
                return 1;
        }

        else if (item->is_item())
        {
                if (!item->remove_from_user())
                        item->remove_from_scene();
        }

        item->before_destruct();
        destruct(item);

        if (item)
        {
                notify("Bạn đã phá huỷ.");
                return 1;
        }

        return 1;
}
