
#include <ansi.h>

// 函数:命令处理
int main(object me, string arg)
{
        object who, item, infoit;
        string name, id, legend, chuoi1, chuoi2, *chuoi, result, iditem;
        int t, level, time, i, kenh, so1, so2, so3;

        string *list = MAIN_D->getlist();
        kenh = MAIN_D->get_kenh();
        /*      if( me->is_die() )
        {
                notify( "您死了，公众频道已被禁止." );
                return 1;
        }       */

        level = me->get_level();
        if (!is_god(me) && level < 15)
        {
                notify("Đạt tới cấp 15 mới có thể sử dụng kênh này");
                return 1;
        }
        if (get_z(me) == 704)
        {
                notify("Trong Nhà Ngục không thể sử dụng Kênh này");
                return 1;
        }
        if (level <= 20)
                time = 30;
        else
                time = 20;
        if (!is_god(me) && gone_time(me->get_time("chat")) < time)
        {
                notify("Bạn vui lòng không sử dụng liên tục Kênh Thế Giới trong thời gian quá ngắn.");
                return 1;
        }
        if (!is_god(me) && me->get_cash() < 200)
        {
                notify("Ngân lượng của bạn không đủ 200 lượng.");
                return 1;
        }
        me->set_time("chat", time());

        if (!arg)
        {
                notify("Bạn muốn nói gì ?");
                return 1;
        }
        "/quest/help"->send_help_tips(me, 44);
        "/quest/help"->send_help_tips(me, 45);
        "/quest/help"->send_help_tips(me, 54);
        if (me->sizeof_chblk_dbase()) // 判断能否使用频道
        {
                t = gone_time(me->get_chblk("time"));
                me->add_chblk("chat", -t);
                me->add_chblk("rumor", -t);
                me->add_chblk("trade", -t);
                me->add_chblk("city", -t);
                me->add_chblk("family", -t);
                me->add_chblk("say", -t);
                me->add_chblk("org", -t);
                me->set_chblk("time", time());

                if (me->get_chblk("chat") < 1 && me->get_chblk("rumor") < 1 && me->get_chblk("trade") < 1 && me->get_chblk("city") < 1 && me->get_chblk("family") < 1 && me->get_chblk("org") < 1 && me->get_chblk("say") < 1)
                        me->init_chblk_dbase();

                if ((t = me->get_chblk("chat")) > 0)
                {
                        notify("Tán gẫu sau %d phút nữa sẽ mở ra", t / 60 + 1);
                        return 1;
                }
        }

        if (!me->get_chat_open()) // 使用可以打开频道
        {
                me->set_chat_open(1);
                CHAT_D->add_chat(me);
        }
        if (!is_god(me))
        {
                me->add_cash2(-200);
                "/sys/sys/count"->add_use("chat", 200);
                legend = sprintf("Tán Gẫu %s,%d,%s,%s @%s lượng 0 %d 0 %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "公众", 200, get_z(me), get_x(me), get_y(me));
                // "/sys/user/cmd"->log_item(legend);
        }
        //name = sprintf( NAME_LEFT "%s" NAME_RIGHT, me->get_name() );
        name = sprintf("%c+%d,%s=%d%c-", '\t', 243 * 256 + 229, me->get_name(), me->get_number(), '\t');
        name = replace_string(name, "#", "＃");

        if (arg[0] == '#' && (arg[1] < '0' || arg[1] > '9'))
        {
                arg = arg[1.. < 1];

                CHAT_D->chat_channel(me->get_number(), sprintf(CHAT "%s%s", name, arg));
        }
        else if (arg[0] == '*')
        {
                arg = arg[1.. < 1];

                if (sscanf(arg, "%s %s", arg, id) == 2)
                {
                        if (id == "i" || id == "me")
                        {
                                who = me;
                        }
                        else if (!(who = find_char(id)))
                        {
                                notify("Không thể tìm thấy người này");
                                return 1;
                        }
                        arg = EMOTE_D->do_emote(me, name, arg, who);
                }
                else
                        arg = EMOTE_D->do_emote(me, name, arg, 0);

                if (!arg)
                        return 1;

                CHAT_D->chat_channel(me->get_number(), CHAT + arg);
        }
        else
        {

                CHAT_D->chat_channel(me->get_number(), sprintf(CHAT " [Kênh %d] %s : %s ", kenh, name, arg));
                chuoi = explode(arg, "/");
                if (chuoi)
                {
                        for (i = 0; i < sizeof(chuoi); i++)
                        {
                                if (sscanf(chuoi[i], "%s]=%s", chuoi1, chuoi2) == 2)
                                {

                                        if (sscanf(chuoi2, "%d,%d,%d", so1, so2, so3) == 3)
                                        {

                                                iditem = sprintf("%x#", so2);
                                                if (objectp(item = find_any_object(iditem)))
                                                {

                                                        result = ITEM_ITEM_D->get_look_string(me, item);
                                                        infoit = new ("inh/user/infoitem");
                                                        infoit->set_id(me->get_number());
                                                        infoit->restore();
                                                        infoit->set_Infoitem(so2, result);
                                                        infoit->save();
                                                        infoit->destruct();
                                                        // "inh/user/infoitem"->set_id(me->get_number());
                                                        // result = ITEM_ITEM_D->get_look_string(me, item);
                                                        // "inh/user/infoitem"->set_Infoitem(so2, result);
                                                        // "inh/user/infoitem"->save();
                                                        // arg = replace_string(arg, sprintf("%d", so2), sprintf("%s:%d", me->get_id(), get_d(item)));
                                                }
                                        }
                                }
                        }
                }
                for (i = 0; i < sizeof(list); i++)
                {
                        if (kenh == to_int(list[i]))
                                continue;
                        ghi_file(sprintf("bang/check%s.txt", list[i]), sprintf("\nchat [Kênh %d] %s:%s", kenh, name, arg));
                }
        }
        return 1;
}
