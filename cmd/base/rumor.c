
#include <ansi.h>

// 函数:命令处理
int main(object me, string arg)
{
        object who;
        string name, id, legend;
        int t, number;

        if (me->is_die())
        {
                notify("Bạn đã chết, kênh Tán Gẫu bị cấm");
                return 1;
        }
        if (me->get_level() < 15)
        {
                notify("Đạt tới cấp 15 mới có thể sử dung kênh Tán Gẫu");
                return 1;
        }
        if (!is_god(me) && gone_time(me->get_time("rumor")) < 120)
        {
                notify("Không nên sử dụng thường xuyên");
                return 1;
        }
        if (get_z(me) == 704)
        {
                notify("Trong Nhà Ngục không thể sử dụng Kênh này");
                return 1;
        }
        if (!is_god(me) && me->get_cash() < 1000)
        {
                notify("Ngân lượng không đủ 1000");
                return 1;
        }
        me->set_time("rumor", time());

        if (!arg)
        {
                notify("Bạn muốn nói cái gì ?");
                return 1;
        }

        if (me->sizeof_chblk_dbase()) // 判断能否使用频道
        {
                t = gone_time(me->get_chblk("time"));
                me->add_chblk("chat", -t);
                me->add_chblk("say", -t);
                me->add_chblk("rumor", -t);
                me->add_chblk("trade", -t);
                me->add_chblk("city", -t);
                me->add_chblk("family", -t);
                me->add_chblk("org", -t);
                me->set_chblk("time", time());

                if (me->get_chblk("chat") < 1 && me->get_chblk("rumor") < 1 && me->get_chblk("trade") < 1 && me->get_chblk("city") < 1 && me->get_chblk("family") < 1 && me->get_chblk("org") < 1 && me->get_chblk("say") < 1)
                        me->init_chblk_dbase();

                if ((t = me->get_chblk("rumor")) > 0)
                {
                        notify("Kệnh Tán Gẫu sau %d phút nữa sẽ mở ra", t / 60 + 1);
                        return 1;
                }
        }
        "/quest/help"->send_help_tips(me, 44);
        "/quest/help"->send_help_tips(me, 45);
        "/quest/help"->send_help_tips(me, 54);
        if (!me->get_rumor_open()) // 使用可以打开频道
        {
                me->set_rumor_open(1);
                CHAT_D->add_rumor(me);
        }
        //name = sprintf( NAME_LEFT "%s" NAME_RIGHT, me->get_name() );
        name = sprintf("%c+%d,%s=%d%c-", '\t', 0xff0000 + 246, me->get_name(), me->get_number(), '\t');
        name = replace_string(name, "#", "＃");
        if (!is_god(me))
        {
                me->add_cash2(-1000);
                "/sys/sys/count"->add_use("rumor", 1000);
                legend = sprintf("Tán Gẫu %s,%d,%s,%s @%s 金 0 %d 0 %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "谣言", 1000, get_z(me), get_x(me), get_y(me));
                //"/sys/user/cmd"->log_item(legend);
        }
        if (arg[0] == '#' && (arg[1] < '0' || arg[1] > '9'))
        {
                arg = arg[1.. < 1];

                if (!is_player(me) || random(5)) // ＧＭ造谣不漏
                {
                        CHAT_D->rumor_player_channel(0, sprintf(CHAT "%s %s", "Một người nào đó", arg));
                        CHAT_D->rumor_gm_channel(0, sprintf("%s %s " HIM "-> %s (%d)", "Một người nào đó", arg, me->get_name(), me->get_number()));
                }
                else
                {
                        number = me->get_number();
                        CHAT_D->rumor_player_channel(number, sprintf(CHAT "%s %s", name, arg));
                        CHAT_D->rumor_gm_channel(number, sprintf("%s %s " HIM "-> %s (%d)", name, arg, me->get_name(), me->get_number()));
                }
        }
        else if (arg[0] == '*')
        {
                arg = arg[1.. < 1];

                if (!is_player(me) || random(5))
                {
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
                                arg = EMOTE_D->do_emote(me, "Một người nào đó", arg, who);
                        }
                        else
                                arg = EMOTE_D->do_emote(me, "Một người nào đó", arg, 0);

                        if (!arg)
                                return 1;

                        CHAT_D->rumor_player_channel(0, CHAT + arg);
                        CHAT_D->rumor_gm_channel(0, sprintf(CHAT "%s " HIM "-> %s (%d)", arg, me->get_name(), me->get_number()));
                }
                else
                {
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

                        number = me->get_number();
                        CHAT_D->rumor_player_channel(number, CHAT + arg);
                        CHAT_D->rumor_gm_channel(number, sprintf(CHAT "%s " HIM "-> %s (%d)", arg, me->get_name(), me->get_number()));
                }
        }
        else
        {
                if (!is_player(me) || random(5))
                {
                        CHAT_D->rumor_player_channel(0, sprintf(CHAT "%s: %s", "Một người nào đó", arg));
                        CHAT_D->rumor_gm_channel(0, sprintf(CHAT "%s: %s " HIM "-> %s (%d)", "Một người nào đó", arg, me->get_name(), me->get_number()));
                }
                else
                {
                        number = me->get_number();
                        CHAT_D->rumor_player_channel(number, sprintf(CHAT "%s: %s", name, arg));
                        CHAT_D->rumor_gm_channel(number, sprintf(CHAT "%s: %s " HIM "-> %s (%d)", name, arg, me->get_name(), me->get_number()));
                }
        }

        return 1;
}
