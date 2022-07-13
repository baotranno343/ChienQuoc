
// 注意：任何失败返回，都应当补发消息

#include <ansi.h>

// 函数：命令处理
int main(object me, string arg)
{
        object *inv, item, item2;
        string result;
        int amount, total;
        int z, x, y, p, flag;

        if (!arg)
                return 1;

        if (sscanf(arg, "! %s", arg))
                flag = 1; // 强行丢掉垃圾

        if (sscanf(arg, "%s#%d", arg, amount) != 2)
                return 1;
        if (amount < 1)
                return 1;
        arg += "#";

        if (!objectp(item = present(arg, me, 1, MAX_CARRY * 4)))
                return 1; // 您找不到这样东西.
        if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
        {
                send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
                return 1;
        }
        /*
        if( gone_time( me->get_time("drop") ) < 1 )    // 时间限制
        {
                me->set_time( "drop", time() );
                send_user( me, "%c%d%c", 0x4e, getoid(item), item->get_amount() );    // 补发消息
                return 1;
        }
        me->set_time( "drop", time() );
*/
        if (get_d(item) < 1)
        {
                send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
                return 1;
        }

        z = get_z(me);
        x = get_x(me);
        y = get_y(me);

        if (item->get_no_drop())
        {
                notify("Bạn không thể vứt bỏ %s .", item->get_name());
                send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
                return 1;
        }
        if (item->is_locked() > 0)
        {
                notify(sprintf("%s mất hiệu quả Khoá Càn Khôn còn %d giờ.", item->get_name(), item->is_locked() / 3600));
                send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
                return 1;
        }
        if (me->get_store(sprintf("%02d", get_d(item))))
        {
                notify(item->get_name() + "已经上架，不能丢弃.");
                send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
                return 1;
        }
        //        //测试用
        //        if ( MAIN_D->get_host_type() == 0 || MAIN_D->get_host_type() == 1000 )
        //        {
        //        	p = get_valid_xy(z ,x, y, IS_CHAR_BLOCK);
        //        	if ( p )
        //			{
        //			item->remove_from_user();
        //			item->add_to_scene(z, p / 1000, p % 1000);
        //			}
        //        	return 1;
        //       }
        //       东西丢地下直接消失
        //        if( !item->is_char() && !item->get_value() )    // 丢弃垃圾
        {
                if (!flag) // 丢弃警告
                {
                        //                        send_user( me, "%c%c%w%s", ':', 3, 0, item->get_name() + "被丢弃后将会消失.\n"
                        //                                        ESC "丢弃.\n" + sprintf( "drop ! %x#%d\n", getoid(item), amount ) +
                        //                                        ESC "我再想想……\nCLOSE\n" );
                        send_user(me, "%c%c%s", 0x59, 1, sprintf(" %s sau khi bị bỏ đi sẽ biến mất.Bạn quyết định muốn vứt bỏ đi phải không?\n" ESC "%c\n" ESC "drop ! %x#%d\n"
                                                                 //                                ESC "%c\n"ESC"team cancel\n",
                                                                 ,
                                                                 item->get_name(), 1, getoid(item), amount));

                        send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
                        return 1;
                }
                else // 垃圾消失
                {
                        if (item->is_record())
                        {
                                result = sprintf("Vứt bỏ %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item->get_name(), "/sys/item/item"->get_pawn_save_string(item), amount, item->get_user_id(), get_z(me), get_x(me), get_y(me));
                                //   "/sys/user/cmd"->log_item(result);
                        }
                        if (!(total = item->get_amount()))
                        {
                                printf(ECHO "Bạn quăng %s đi, %s biến mất ngay sau đó.", item->get_name(), item->get_name());
                                // log_file("drop.txt", sprintf("%s : %s (%d) đã vứt %s \n", short_time(time()), me->get_name(), me->get_number(), item->get_name()));
                                send_user(me, "%c%d", 0x2d, getoid(item));
                                destruct(item);
                        }
                        else if (amount >= total)
                        {
                                printf(ECHO "Bạn quăng %s đi, %s biến mất ngay sau đó.", item->get_name(), item->get_name());
                                send_user(me, "%c%d", 0x2d, getoid(item));
                                // log_file("drop.txt", sprintf("%s : %s (%d) đã vứt %s \n", short_time(time()), me->get_name(), me->get_number(), item->get_name()));
                                destruct(item);
                        }
                        else
                        {
                                printf(ECHO "Bạn quăng %s đi, %s biến mất ngay sau đó.", item->get_name(), item->get_name());
                                item->add_amount(-amount);
                        }
                        return 1;
                }
        }
        return 1;
}
