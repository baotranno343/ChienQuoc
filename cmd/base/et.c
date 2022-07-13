
#include <ansi.h>

// 函数:命令处理
int main(object me, string arg)
{
        object who;
        string name, id, legend;
        int t;

        if (!me->is_store_open())
                return 1;

        /*      if( me->is_die() )
        {
                notify( "您死了，交易频道已被禁止." );
                return 1;
        }       */
        if (me->get_level() < 15)
        {
                notify("Cấp bậc chưa đạt tới cấp 15");
                return 1;
        }
        if (!is_god(me) && gone_time(me->get_time("et")) < 3)
        {
                notify("Không nên sử dụng kênh Giao Dịch thường xuyên");
                return 1;
        }
        if (get_z(me) == 704)
        {
                notify("Trong Nhà Ngục không thể sử dụng Kênh này");
                return 1;
        }
        if (!is_god(me) && me->get_cash() < 200)
        {
                notify("Ngân lượng không đủ 200");
                return 1;
        }
        me->set_time("et", time());

        if (!arg)
        {
                notify("Bạn muốn nói gì ?");
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

                if ((t = me->get_chblk("trade")) > 0)
                {
                        notify("Giao Dịch kênh sau %d phút sẽ mở ra", t / 60 + 1);
                        return 1;
                }
        }
        "/quest/help"->send_help_tips(me, 44);
        "/quest/help"->send_help_tips(me, 45);
        if (!me->get_trade_open()) // 使用可以打开频道
        {
                me->set_trade_open(1);
                CHAT_D->add_chat(me); // trade 与 chat 共用
        }
        //name = sprintf( NAME_LEFT "%s" NAME_RIGHT, me->get_name() );
        if (!is_god(me))
        {
                me->add_cash2(-200);
                legend = sprintf("Tán Gẫu %s,%d,%s,%s @%s 金 0 %d 0 %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "交易", 200, get_z(me), get_x(me), get_y(me));
                //"/sys/user/cmd"->log_item(legend);
        }
        name = sprintf("%c+%d,%s=%d%c-", '\t', 0xffffff, me->get_name(), me->get_number(), '\t');
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
                                notify("Không tìm thấy người này");
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
                CHAT_D->chat_channel(me->get_number(), sprintf(CHAT "%s : %s", name, arg));

        return 1;
}
