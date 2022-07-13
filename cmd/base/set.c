
#include <ansi.h>
#include <task.h>
#include <effect.h>
#include <skill.h>
#include <npc.h>
#include <city.h>
#include <action.h>
#include <public.h>

// 函数:命令处理
int main(object me, string arg)
{
        object who, map;
        string data, str1, str2;
        int level;
        level = me->get_level();

        if (arg && sscanf(arg, "%s %s", arg, data) == 2)
                switch (arg)
                {
                case "lock":
                        me->set_enemy_2(0); // 取消攻击目标(暗器，法术，医术，施毒锁定)，指令:set lock 0
                        break;

                case "?":
                        if (level < 40)
                        {
                                notify("Ngươi không đủ quyền hạn");
                                return 1;
                        }
                        if (data == "attack")
                        {
                                switch (me->get_attack_mode())
                                {
                                case 0:
                                        data = "Tấn công tự do";
                                        break;
                                case 2:
                                        data = "伏击保护";
                                        break;
                                default:
                                        data = "完全保护";
                                        break;
                                }
                                send_user(me, "%c%c%w%s", ':', 3, 0, "您的攻击模式是“" + data + "”，您想更改为:(热键: Ctrl+H)\n" ESC "完全保护，仅攻击ＮＰＣ.\nset attack 1\n"
                                                                         //                                        ESC "伏击保护，以攻击红名玩家.但你也将处于自由攻击状态.\nset attack 2\n"
                                                                         ESC "Tấn công tự do，与同等状态的玩家可以互相攻击.\nset attack 0\n" ESC "维持原样.\nCLOSE\n");
                        }
                        break;
                case "attack":
                        if (me->get_level() < 40)
                        {
                                me->set_attack_mode(1);
                                write_user(me, ECHO "Dưới 40 không thể PK !");
                                break;
                        }
                        switch (data)
                        {
                        case "1":
                                if (me->get_pk() >= 5)
                                        break;
                                if (get_effect(me, EFFECT_USER_PK))
                                        break;
                                send_user(me, "%c%c%w%s", ':', 3, 0, "你将进入完全保护状态，你不会受到任何玩家的攻击，也不会伤害到任何类型玩家.\n" ESC "确定\nset !attack 1\n" ESC "取消\nCLOSE\n");
                                break;
                        default:
                                send_user(me, "%c%c%w%s", ':', 3, 0, "你将处于无限制攻击状态，你与同等状态的玩家可以互相攻击\n" ESC "确定\nset !attack 0\n" ESC "取消\nCLOSE\n");
                                break;
                        }
                        break;
                case "!attack":
                        if (level < 40)
                        {
                                notify("Ngươi không đủ quyền hạn");
                                return 1;
                        }
                        if (me->get("autoRun"))
                        {
                                notify("Đang bật Auto không thể thay đổi");
                                return 1;
                        }
                        switch (data)
                        {
                        case "3":
                                /*                     
                     		if (me->get_attack_mode()==0)
                     		{
                     			write_user(me, ECHO "您的攻击模式将在十分钟后转换");
                     			
                     			me->set_attack_mode(me->get_attack_mode()); 
                     			break;
                     		}
                     		
                     		if (me->get_pk()>=5) 
                     		{
                     			me->set_attack_mode(me->get_attack_mode()); 
                     			break;
                     		}  */

                                me->set_attack_mode(0);
                                //	set_effect(me, EFFECT_USER_PK, 600);
                                //                     		send_user( me, "%c%w%w%c", 0x81, 2214, 0, EFFECT_GOOD );
                                me->set_pk(me->get_pk());
                                if (me->get_pk() < 100 && get_effect(me, EFFECT_USER_PK))
                                {
                                        me->set_char_type(PK_TYPE); // 主动ＰＫ状态
                                        set_effect(me, EFFECT_USER_PK, get_effect(me, EFFECT_USER_PK));
                                }
                                write_user(me, "Hình thức tấn công: Tự Do !");
                                //								write_user(me, ECHO "Hình thức tấn công của bạn: Tự Do");
                                break;

                        case "2":
                                /*                     
                     		if (me->get_attack_mode()==0)
                     		{
                     			write_user(me, ECHO "您的攻击模式将在十分钟后转换");
                     			
                     			me->set_attack_mode(me->get_attack_mode()); 
                     			break;
                     		}
                     		
                     		if (me->get_pk()>=5) 
                     		{
                     			me->set_attack_mode(me->get_attack_mode()); 
                     			break;
                     		}  */

                                me->set_attack_mode(2);
                                //	set_effect(me, EFFECT_USER_PK, 600);
                                //                     		send_user( me, "%c%w%w%c", 0x81, 2214, 0, EFFECT_GOOD );
                                me->set_pk(me->get_pk());
                                if (me->get_pk() < 100 && get_effect(me, EFFECT_USER_PK))
                                {
                                        me->set_char_type(PK_TYPE); // 主动ＰＫ状态
                                        set_effect(me, EFFECT_USER_PK, get_effect(me, EFFECT_USER_PK));
                                }
                                write_user(me, "Hình thức tấn công: Theo Bang !");
                                //								write_user(me, ECHO "Hình thức tấn công của bạn: Tự Do");
                                break;
                        case "1":
                                /*                     
                     		if (me->get_attack_mode()==0)
                     		{
                     			write_user(me, ECHO "您的攻击模式将在十分钟后转换");
                     			
                     			me->set_attack_mode(me->get_attack_mode()); 
                     			break;
                     		}
                     		
                     		if (me->get_pk()>=5) 
                     		{
                     			me->set_attack_mode(me->get_attack_mode()); 
                     			break;
                     		}  */

                                me->set_attack_mode(3);
                                //	set_effect(me, EFFECT_USER_PK, 600);
                                //                     		send_user( me, "%c%w%w%c", 0x81, 2214, 0, EFFECT_GOOD );
                                me->set_pk(me->get_pk());
                                if (me->get_pk() < 100 && get_effect(me, EFFECT_USER_PK))
                                {
                                        me->set_char_type(PK_TYPE); // 主动ＰＫ状态
                                        set_effect(me, EFFECT_USER_PK, get_effect(me, EFFECT_USER_PK));
                                }
                                write_user(me, "Hình thức tấn công: Theo Quốc Gia !");
                                //								write_user(me, ECHO "Hình thức tấn công của bạn: Tự Do");
                                break;

                        default:
                                if (MAIN_D->get_host_type() == 6012)
                                {
                                        send_user(me, "%c%%s", ':', "PK系统尚未开放!");
                                        break;
                                }

                                me->set_attack_mode(1);
                                //	set_effect(me, EFFECT_USER_PK, 0);
                                //                      		send_user( who, "%c%w%w%c", 0x81, 2214, 600, EFFECT_GOOD );
                                me->set_pk(me->get_pk());
                                if (me->get_pk() < 100 && get_effect(me, EFFECT_USER_PK))
                                {
                                        me->set_char_type(PK_TYPE); // 主动ＰＫ状态
                                        set_effect(me, EFFECT_USER_PK, get_effect(me, EFFECT_USER_PK));
                                }
                                //                                write_user(me, ECHO "Hình thức tấn công của bạn: Hoà Bình");
                                write_user(me, "Hình thức tấn công: Hoà Bình !");
                                break;
                        }
                        break;
                case "give":
                        me->set_no_give(data == "0");
                        break;
                case "fly":
                        me->set_no_fly(data == "0");
                        break;
                case "trans":
                        me->set_no_trans(data == "0");
                        break;
                case "trade":
                        me->set_no_trade(data == "0");
                        break;
                case "team":
                        me->set_no_team(data == "0");
                        break;
                case "friend":
                        me->set_no_friend(data == "0");
                        break;
                case "tell":
                        me->set_no_tell(data == "0");
                        break;
                case "chat":
                        if (data == "1")
                        {
                                me->set_chat_open(1);
                                CHAT_D->add_chat(me);
                        }
                        else
                        {
                                me->set_chat_open(0);
                                CHAT_D->sub_chat(me);
                        }
                        break;
                case "rumor":
                        if (data == "1")
                        {
                                me->set_rumor_open(1);
                                CHAT_D->add_rumor(me);
                        }
                        else
                        {
                                me->set_rumor_open(0);
                                CHAT_D->sub_rumor(me);
                        }
                        break;
                case "ct":
                        if (data == "1")
                        {
                                me->set_city_open(1);
                                FAMILY_D->add_city(me);
                        }
                        else
                        {
                                me->set_city_open(0);
                                FAMILY_D->sub_city(me);
                        }
                        break;
                case "ot":
                        if (data == "1")
                        {
                                me->set_org_open(1);
                                FAMILY_D->add_org(me);
                        }
                        else
                        {
                                me->set_org_open(0);
                                FAMILY_D->sub_org(me);
                        }
                        break;
                case "ft":
                        if (data == "1")
                        {
                                me->set_family_open(1);
                                FAMILY_D->add_family(me);
                        }
                        else
                        {
                                me->set_family_open(0);
                                FAMILY_D->sub_family(me);
                        }
                        break;
                case "say":
                        me->set_say_open(data == "1");
                        break;
                case "tt":
                        me->set_team_open(data == "1");
                        break;
                case "et":
                        me->set_trade_open(data == "1");
                        break;
                case "channel":
                        if (data == "1")
                        {
                                me->set_chat_open(1);
                                CHAT_D->add_chat(me);
                                me->set_rumor_open(1);
                                CHAT_D->add_rumor(me);
                                me->set_city_open(1);
                                FAMILY_D->add_city(me);
                                me->set_org_open(1);
                                FAMILY_D->add_org(me);
                                me->set_family_open(1);
                                FAMILY_D->add_family(me);
                                me->set_say_open(1);
                                me->set_team_open(1);
                                me->set_trade_open(1);
                        }
                        else
                        {
                                me->set_chat_open(0);
                                CHAT_D->sub_chat(me);
                                me->set_rumor_open(0);
                                CHAT_D->sub_rumor(me);
                                me->set_city_open(0);
                                FAMILY_D->sub_city(me);
                                me->set_org_open(0);
                                FAMILY_D->sub_org(me);
                                me->set_family_open(0);
                                FAMILY_D->sub_family(me);
                                me->set_say_open(0);
                                me->set_team_open(0);
                                me->set_trade_open(0);
                        }
                        break;
                case "protect":
                        if (strlen(data) > 10)
                                data = data[0..9];
                        me->set_id_protect(data);
                        break;
                case "locked":
                        me->set_id_locked(data == "1");
                        break;
                case "mode":
                        me->set_mode(data == "1");
                        break;
                case "mouse":
                        me->set_mouse(data == "1");
                        break;
                }
        else if (!is_player(me))
        {
                if (!arg)
                        who = me;
                else if (!objectp(who = find_player(arg)))
                {
                        notify("您找不到这位玩家.");
                        return 1;
                }

                tell_user(me, "%s(%d)设定的环境:\n", who->get_name(), who->get_number());
                tell_user(me, "攻击模式: %-4d禁止飞行: %d", who->get_attack_mode(), who->get_no_fly());
                tell_user(me, "禁止给予: %-4d禁止传送: %d", who->get_no_give(), who->get_no_trans());
                tell_user(me, "禁止交友: %-4d禁止组队: %d", who->get_no_friend(), who->get_no_team());
                tell_user(me, "禁止私聊: %d", who->get_no_tell());
                tell_user(me, "禁止交易: %d", who->get_no_trade());

                tell_user(me, "公众: %-4d谣言: %-4d国家: %-4d帮派: %-4d门派: %-4d本地: %-4d队伍: %-4d交易: %-4d",
                          who->get_chat_open(), who->get_rumor_open(), who->get_city_open(), who->get_org_open(),
                          who->get_family_open(), who->get_say_open(), who->get_team_open(), who->get_trade_open());

                tell_user(me, "密码保护: %-4s用户锁定: %d", who->get_id_protect(), who->get_id_locked());
        }

        return 1;
}

// 函数:获取描述(持续)
string get_loop_desc(object me)
{
        return HIR "Hiệu ứng PK";
}