#include <item.h>
#include <ansi.h>
#include <equip.h>

// 函数：命令处理

int mix_aohoa(object who, object item, object diamond);
int main(object me, string arg)
{
        object *item, who;
        string name, make, result, forge, index;
        int *id;
        int i, flag, level, rate;

        if (!arg)
                return 1;

        item = ({
            0,
            0,
        });
        id = ({
            0,
            0,
        });
        if (!sscanf(arg, "%x# %x#", id[0], id[1]) == 2)
                return 1;

        /*
        if( !objectp( who = find_char(name) ) ) return 1;

        if( !who->is_maker() ) return 1;

        if( !inside_screen_2(me, who) )
        {
                notify( "Bạn cách %s quá xa rồi.", who->get_name() );
                return 1;
        }

        me->to_front_eachother(who);
*/

        for (i = 0; i < 2; i++)
        {
                if (!objectp(item[i] = present(sprintf("%x#", id[i]), me, 1, MAX_CARRY * 4))) // 物品是否存在？
                {
                        send_user(me, "%c%c%c%d", 0x25, 0, 0, 0);
                        return 1;
                }
        }

        mix_aohoa(me, item[0], item[1]);

        return 1;
}

//孔中镶嵌宝石
//增加新镶嵌的石头的话必须维护mpHole

int mix_aohoa(object who, object item, object diamond)
{

        //return 1;

        if (!item->is_nangcap() || !diamond->is_aohoa())
                return 0;

        // item->set_back_type(item->get("backcolor1"));
        // item->set_back2_type(item->get("backcolor2"));
        item->set("aohoa", diamond->get("aohoa"));
        item->set_back_type(diamond->get("backtype1"));
        item->set_back2_type(diamond->get("backtype2"));
        item->set_back_color(diamond->get("backcolor1"));
        item->set_back2_color(diamond->get("backcolor2"));
        item->set_lock_time(time() + 14 * 24 * 60 * 60);
        send_user(who, "%c%d%c", 0x31, getoid(item), 0);
        diamond->remove_from_user();
        destruct(diamond);
        return 1;
}
int xoa_aohoa(object item, object me)
{

        string fileobject;
        //return 1;

        fileobject = get_file_name(item);
        item->delete ("aohoa");
        item->set_back_type(fileobject->get_back_type());
        item->set_back2_type(fileobject->get_back2_type());
        item->set_back_color(fileobject->get_back_color());
        item->set_back2_color(fileobject->get_back2_color());
        item->set_lock_time(0);
        send_user(me, "%c%d%c", 0x31, getoid(item), 0);
        me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
}