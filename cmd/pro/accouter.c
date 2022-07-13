
#include <equip.h>

// 函数：命令处理
int main(object me, string arg)
{
        object *inv, item, who = me, char, pawn;
        int i, size, type, total;
        string *ids = ({}), *key, name, file, id;
        mapping list;
        if (is_player(me))
        {
                notify("您没有足够的权限。");
                return 1;
        }
        if (!arg)
                return 1;
        ids = explode(arg, " ");
        if (sizeof(ids) != 2)
                return 1;
        type = to_int(ids[1]);
        if (type < 0)
                return 1;
        arg = ids[0];
        if (!(who = find_player(arg)))
        {
                id = strlwr(arg);
                if (!user_exist(id))
                {
                        notify("这个用户并不存在！");
                        return 1;
                }

                who = new (USER);
                who->set_id(id);
                if (!who->restore())
                {
                        send_user(me, "%c%s", '!', "这个用户并不存在！");
                        destruct(who);
                        return 1;
                }

                if (char = find_player(sprintf("%d", who->get_number())))
                {
                        send_user(me, "%c%s", '!', "该用户处于在线状态！");
                        return 1;
                }
        }
        else
        {
                send_user(me, "%c%s", '!', "该用户处于在线状态！");
                return 1;
        }
        if (type == 0) // 查询道具
        {
                who->restore_inventory();
                inv = who->get_all_equip();
                for (i = 0, size = sizeof(inv); i < size; i++)
                        if (objectp(item = inv[i]))
                                send_user(me, "%c%c%d%c%w%s", 0xac, 0, who->get_number(), get_d(item), item->get_amount(), item->get_name());
                inv = all_inventory(who, 1, MAX_CARRY);
                for (i = 0, size = sizeof(inv); i < size; i++)
                        if (objectp(item = inv[i]))
                                send_user(me, "%c%c%d%c%w%s", 0xac, 0, who->get_number(), get_d(item), item->get_amount(), item->get_name());
                send_user(me, "%c%c%d%d", 0xac, 3, who->get_number(), who->get_cash());
                who->before_destruct();
                destruct(who);
                return 1;
        }
        if (type == 1)
                send_user(me, "%c%c%d%c", 0xac, 8, who->get_number(), who->get_max_pawn_size());
        type--;
        pawn = new (PAWN);
        pawn->set_id(type);
        pawn->set_owner(who->get_id());
        list = pawn->get_pawn();
        destruct(pawn);
        if (!mapp(list) || !(size = sizeof(key = keys(list))))
        {
                destruct(who);
                return 1;
        }
        if (size)
                key = sort_array(key, 1);

        for (i = 0; i < size; i++)
        {
                if (!stringp(name = list[key[i]]))
                        continue;
                if (!sscanf(name, "%s;%d;%*s", file, total) || !load_object(file))
                        continue;
                send_user(me, "%c%c%d%c%c%w%s", 0xac, 5, who->get_number(), type + 1, to_int(key[i]), total, file->get_name());
        }
        send_user(me, "%c%c%d%d", 0xac, 4, who->get_number(), who->get_savings());
        destruct(who);
        return 1;
}
