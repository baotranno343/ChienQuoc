#include <ansi.h>
#include <equip.h>

// 函数：命令处理
int main(object me, string arg)
{
        object obj;

        if (gone_time(me->get_time("remove")) < 1) // 时间限制
        {
                me->set_time("remove", time());
                return 1;
        }
        if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
        {
                send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
                return 1;
        }
        if (me->get_perform("03191"))
        {
                notify("Trạng thái Cuồng Bạo không thể thay đổi trang bị");
                return 1;
        }
        if (me->get_perform("03192"))
        {
                notify("Trạng thái Phòng Thủ không thể thay đổi trang bị");
                return 1;
        }
        // if (me->get_perform("03333"))
        // {
        //         notify("Làm nhiệm vụ sư gia không thể thay đổi trang bị");
        //         return 1;
        // }
        me->set_time("remove", time());

        if (arg)
                switch (arg)
                {
                case "1":
                        me->remove_equip(HEAD_TYPE);
                        break;
                case "2":
                        me->remove_equip(NECK_TYPE);
                        break;
                case "3":
                        me->remove_equip(WEAPON_TYPE);
                        break;
                case "4":
                        me->remove_equip(ARMOR_TYPE);
                        break;
                case "5":
                        me->remove_equip(WAIST_TYPE);
                        break;
                case "6":
                        me->remove_equip(BOOTS_TYPE);
                        break;
                case "7":
                        me->remove_equip(HAND_TYPE);
                        break;
                        //               case "8" : me->remove_equip(FAMILY_TYPE);  break;
                case "9":
                        me->remove_equip(BACK_TYPE);
                        break;
                case "10":
                        me->remove_equip(FASHION_TYPE);
                        break;
                }

        return 1;
}
