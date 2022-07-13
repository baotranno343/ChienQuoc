
#include <ansi.h>

// 函数:命令处理
int main(object me, string arg)
{
        object who, item, infoit;
        string name, id, org, chuoi1, chuoi2, *chuoi, result, iditem;
        int t, kenh, i, so1, so2, so3;

        string *list = MAIN_D->getlist();
        kenh = MAIN_D->get_kenh();
        if ((org = me->get_org_name()) == "")
                return 1;
        if (me->get_org_position() == 0)
                return 1;

        /*      if( me->is_die() )
        {
                notify( "您死了，帮派频道已被禁止." );
                return 1;
        }       */

        if (!is_god(me) && gone_time(me->get_time("ot")) < 3)
        {
                notify("Không nên sử dụng kênh Bang Phái thường xuyên");
                return 1;
        }
        if (get_z(me) == 704)
        {
                notify("Trong Nhà Ngục không thể sử dụng Kênh này");
                return 1;
        }
        me->set_time("ot", time());

        if (!arg)
        {
                notify("Bạn muốn nói gì ?");
                return 1;
        }

        if (me->sizeof_chblk_dbase()) // 判断能否使用频道
        {
                t = gone_time(me->get_chblk("time"));
                me->add_chblk("chat", -t);
                me->add_chblk("rumor", -t);
                me->add_chblk("trade", -t);
                me->add_chblk("city", -t);
                me->add_chblk("family", -t);
                me->add_chblk("org", -t);
                me->add_chblk("say", -t);
                me->set_chblk("time", time());

                if (me->get_chblk("chat") < 1 && me->get_chblk("rumor") < 1 && me->get_chblk("trade") < 1 && me->get_chblk("city") < 1 && me->get_chblk("family") < 1 && me->get_chblk("org") < 1 && me->get_chblk("say") < 1)
                        me->init_chblk_dbase();

                if ((t = me->get_chblk("org")) > 0)
                {
                        notify("%s kênh sau %d phút sẽ mở ra", org, t / 60 + 1);
                        return 1;
                }
        }
        "/quest/help"->send_help_tips(me, 44);
        "/quest/help"->send_help_tips(me, 45);
        if (!me->get_org_open()) // 使用可以打开频道
        {
                me->set_org_open(1);
                FAMILY_D->add_org(me);
        }
        //name = sprintf( NAME_LEFT "%s" NAME_RIGHT, me->get_name() );
        name = sprintf("%c+%d,%s=%d%c-", '\t', 255 * 256 * 256 + 102 * 256, me->get_name(), me->get_number(), '\t');
        name = replace_string(name, "#", "＃");

        if (arg[0] == '#' && (arg[1] < '0' || arg[1] > '9'))
        {
                arg = arg[1.. < 1];

                FAMILY_D->org_channel(org, me->get_number(), sprintf(CHAT "%s%s", name, arg));
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

                FAMILY_D->org_channel(org, me->get_number(), CHAT + arg);
        }
        else
        {
                FAMILY_D->org_channel(org, me->get_number(), sprintf(CHAT "[Kênh %d] %s : %s", kenh, name, arg));
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
                        ghi_file(sprintf("bang/check%s.txt", list[i]), sprintf("\not %s:[Kênh %d] %s:%s", org, kenh, name, arg));
                }
        }

        return 1;
}
