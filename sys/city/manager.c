
#include <ansi.h>
#include <city.h>

#define MIN_ORG_MEMBER 6 // Bang Chúng人数下限

// 函数:生成二进制码
void SAVE_BINARY() {}
// 函数:对话处理
void do_look(object who, object me)
{
        string cmd;
        string name1, name2, *name;
        int id, number, i, size;

        id = getoid(me);

        name1 = who->get_org_name();
        name2 = me->get_org_name();

        if (stringp(name1) && stringp(name2) && name1 == name2) // 本帮Bang Chúng
        {
                send_user(who, "%c%c%d%c%s", 0x95, 10, id, who->get_org_position(), me->get_org_name());

                size = me->sizeof_member_dbase();
                name = me->get_all_member();

                for (i = 0; i < size; i++)
                {
                        number = to_int(name[i]);
                        send_user(who, "%c%c%d%d%c%d%d%c%s", 0x95, 11, number,
                                  me->get_member_time(number), me->get_member_quit(number) ? 0 : 1,
                                  me->get_member_gold(number), me->get_member_all_contribute(number), me->get_member_level(number),
                                  sprintf("%-12s%s", me->get_member_name(number), me->get_member_rank(number)));
                }
        }
        else if (stringp(name1) && name1 != "") // 别帮人士
        {
                send_user(who, "%c%s", ':', me->get_name() + ":\n Vị này " + NPC_RANK_D->get_respect(who) + ", xin hỏi biệt lai vô dạng ?\n");
        }
        else // 无帮人士
        {
                cmd = sprintf("talk %x# join.?\n", id);
                send_user(who, "%c%s", ':', me->get_name() + ":\n Vị này " + NPC_RANK_D->get_respect(who) + ", muốn gia nhập bang không ?\n" ESC "Xin gia nhập\n" + cmd + ESC "Rời khỏi\nCLOSE\n");
        }
}

// 函数:查看信息
void do_info(object who, object me, string arg)
{
        string name1, name2, *name;
        int id, number, i, size;

        id = getoid(me);

        name1 = who->get_org_name();
        name2 = me->get_org_name();

        if (stringp(name1) && stringp(name2) && name1 == name2) // 本帮Bang Chúng
        {
                number = to_int(arg);

                if (!number) // 显示Bang Phái界面
                {
                        send_user(who, "%c%c%d%c%s", 0x95, 10, id, who->get_org_position(), me->get_org_name());

                        size = me->sizeof_member_dbase();
                        name = me->get_all_member();

                        for (i = 0; i < size; i++)
                        {
                                number = to_int(name[i]);
                                if (me->get_member_id(number) == 0)
                                {
                                        me->delete_member_info(number);
                                        continue;
                                }
                                send_user(who, "%c%c%d%d%c%d%d%c%s", 0x95, 11, number,
                                          me->get_member_time(number), me->get_member_quit(number) ? 0 : 1,
                                          me->get_member_gold(number), me->get_member_all_contribute(number), me->get_member_level(number),
                                          sprintf("%-12s%s", me->get_member_name(number), me->get_member_rank(number)));
                        }
                }
                else if (me->get_member_id(number)) // 显示个人信息
                {
                        if (number == who->get_number()) // 点中自己，更新信息
                        {
                                me->set_member_name(number, who->get_name());
                                me->set_member_gender(number, who->get_gender());
                                me->set_member_level(number, who->get_level());
                                me->set_member_family(number, who->get_fam_name());
                                me->set_member_job(number, who->get_occupation());
                                me->set_member_job_level(number, who->get_occupation_level());
                        }
                        send_user(who, "%c%c%d%c%d%d%s", 0x95, 12, number,
                                  me->get_member_gender(number), me->get_photo(number),
                                  me->get_member_quit(number), sprintf("%-8s%-8s%s", me->get_member_family(number), me->get_member_job(number), me->get_member_rank(number)));
                }
        }
}

// -------------------------------------------------------------

// 函数:任命Bang Chúng
void do_appoint(object who, object me, string arg)
{
        object char;
        string name1, name2, name3;
        string cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, cmd7, id, *member;
        int number, level, flag, trader_flag;

        name1 = who->get_org_name();
        name2 = me->get_org_name();

        if (stringp(name1) && stringp(name2) && name1 == name2 && who->get_org_position() >= ORG_PRESBYTER) // 本帮官员
        {
                if (sscanf(arg, "%d.%d", number, level) != 2)
                {
                        number = to_int(arg);

                        if (me->get_member_id(number))
                        {
                                cmd1 = sprintf("talk %x# appoint.%d.1\n", getoid(me), number);
                                cmd2 = sprintf("talk %x# appoint.%d.2\n", getoid(me), number);
                                cmd3 = sprintf("talk %x# appoint.%d.3\n", getoid(me), number);
                                cmd4 = sprintf("talk %x# appoint.%d.4\n", getoid(me), number);
                                cmd5 = sprintf("talk %x# appoint.%d.5\n", getoid(me), number);
                                cmd6 = sprintf("talk %x# appoint.%d.6\n", getoid(me), number);
                                cmd7 = sprintf("talk %x# appoint.%d.7\n", getoid(me), number);
                                send_user(who, "%c%s", ':', me->get_name() + ":\nNgày phải nhậm mệnh " + me->get_member_name(number) + " chức vụ gì ?\n" ESC "Phó Bang Chủ.\n" + cmd1 + ESC "Trưởng Lão.\n" + cmd2 + ESC "Đường Chủ.\n" + cmd3 + ESC "Hương Chủ.\n" + cmd4 + ESC "Tinh Anh.\n" + cmd5 + ESC "Thương Nhân.\n" + cmd6 + ESC "Phổ Thông Bang Chúng.\n" + cmd7 + ESC "Ta muốn suy nghĩ……\nCLOSE\n");
                        }
                        return;
                }

                if (me->get_member_id(number))
                {
                        if ("sys/sys/user2"->check_id_online(number) != 0)
                        {
                                send_user(who, "%c%s", '!', " Người chơi này đang ở khác kênh với bạn. Người chơi phải đăng xuất hoặc ở cùng kênh với bạn !");
                                return;
                        }
                        if (who->get_org_position() < ORG_PRESBYTER)
                        {
                                send_user(who, "%c%s", '!', "Bạn ở \"" + name2 + "\" chức vị rất thấp");
                                return;
                        }
                        if (!(char = find_player(sprintf("%d", number))))
                        {
                                char = new (USER);
                                char->set_id(me->get_member_id(number));
                                if (!char->restore())
                                {
                                        id = me->get_member_id(number);
                                        if (id == me->get_master_id_2())
                                        {
                                                me->set_master_2(0);
                                                me->set_master_id_2("");
                                                me->set_master_name_2("－－");
                                        }
                                        member = me->get_presbyter();
                                        if (arrayp(member) && member_array(id, member) != -1)
                                        {
                                                member -= ({id});
                                                me->set_presbyter(member);
                                        }
                                        member = me->get_manager4();
                                        if (arrayp(member) && member_array(id, member) != -1)
                                        {
                                                member -= ({id});
                                                me->set_manager4(member);
                                        }
                                        else if ((member = me->get_manager5()) && arrayp(member) && member_array(id, member) != -1)
                                        {
                                                member -= ({id});
                                                me->set_manager5(member);
                                        }
                                        else if ((member = me->get_manager6()) && arrayp(member) && member_array(id, member) != -1)
                                        {
                                                member -= ({id});
                                                me->set_manager6(member);
                                        }
                                        me->save();
                                        send_user(who, "%c%s", '!', " Vị này không tồn tại !");
                                        destruct(char);
                                        return;
                                }
                                flag = 1; // 离线
                        }
                        if (char == who && level != 8)
                        {
                                send_user(who, "%c%s", '!', "Không thể chính mình điều chỉnh chức vị của chính mình !");
                                return;
                        }

                        name3 = char->get_org_name();
                        if (!stringp(name3) || name3 == "" || name3 != name2) // 双保险，可删除
                        {
                                id = me->get_member_id(number);
                                if (id == me->get_master_id_2())
                                {
                                        me->set_master_2(0);
                                        me->set_master_id_2("");
                                        me->set_master_name_2("－－");
                                }
                                member = me->get_presbyter();
                                if (arrayp(member) && member_array(id, member) != -1)
                                {
                                        member -= ({id});
                                        me->set_presbyter(member);
                                }
                                member = me->get_manager4();
                                if (arrayp(member) && member_array(id, member) != -1)
                                {
                                        member -= ({id});
                                        me->set_manager4(member);
                                }
                                else if ((member = me->get_manager5()) && arrayp(member) && member_array(id, member) != -1)
                                {
                                        member -= ({id});
                                        me->set_manager5(member);
                                }
                                else if ((member = me->get_manager6()) && arrayp(member) && member_array(id, member) != -1)
                                {
                                        member -= ({id});
                                        me->set_manager6(member);
                                }
                                me->save();
                                send_user(who, "%c%s", '!', char->get_name() + "Không phải \"" + name2 + "\" bang chúng");
                                if (flag)
                                        destruct(char);
                                return;
                        }
                        if (char->get_org_position() >= who->get_org_position() && char->get_id() != who->get_id()) // 权限判断！
                        {
                                send_user(who, "%c%s", '!', "Bạn ở \"" + name2 + "\" chức vị rất thấp");
                                if (flag)
                                        destruct(char);
                                return;
                        }
                        else if (char->get_org_position() >= ORG_MASTER && level != 6 && level != 8) // Bang Chủ
                        {
                                send_user(who, "%c%s", '!', char->get_name() + "Là \"" + name2 + "\" Bang Chủ");
                                if (flag)
                                        destruct(char);
                                return;
                        }

                        id = char->get_id();
                        if (level != 6 && level != 8)
                        {
                                if (id == me->get_master_id_2())
                                {
                                        me->set_master_2(0);
                                        me->set_master_id_2("");
                                        me->set_master_name_2("－－");
                                        char->delete_title("C002");
                                }
                                member = me->get_presbyter();
                                if (arrayp(member) && member_array(id, member) != -1)
                                {
                                        member -= ({id});
                                        me->set_presbyter(member);
                                        char->delete_title("C003");
                                }
                                member = me->get_manager4();
                                if (arrayp(member) && member_array(id, member) != -1)
                                {
                                        member -= ({id});
                                        me->set_manager4(member);
                                        char->delete_title("C004");
                                }
                                else if ((member = me->get_manager5()) && arrayp(member) && member_array(id, member) != -1)
                                {
                                        member -= ({id});
                                        me->set_manager5(member);
                                        char->delete_title("C005");
                                }
                                else if ((member = me->get_manager6()) && arrayp(member) && member_array(id, member) != -1)
                                {
                                        member -= ({id});
                                        me->set_manager6(member);
                                        char->delete_title("C006");
                                }
                        }
                        member = me->get_trader();
                        if (arrayp(member) && member_array(id, member) != -1)
                                trader_flag = 1;
                        switch (level)
                        {
                        case 1:
                                if (who->get_org_position() < ORG_MASTER) // 权限不足
                                {
                                        send_user(who, "%c%s", '!', "Bạn ở \"" + name2 + "\" chức vị rất thấp");
                                        if (flag)
                                                destruct(char);
                                        return;
                                }
                                if (me->get_master_2())
                                {
                                        send_user(who, "%c%s", '!', "\"" + name2 + "\"  chức vụ Phó Bang Chủ không trống");
                                        if (flag)
                                                destruct(char);
                                        return;
                                }
                                me->set_master_2(number);
                                me->set_master_id_2(me->get_member_id(number));
                                me->set_master_name_2(me->get_member_name(number));
                                me->set_member_rank(number, "Phó Bang Chủ");
                                if (trader_flag)
                                        me->set_member_rank(number, "Phó Bang Chủ Thương Nhân");
                                char->set_org_position(ORG_MASTER_2);
                                char->set_org_title("Phó Bang Chủ");
                                char->add_title("C002");
                                char->show_title("C002");
                                break;
                        case 2:
                                member = me->get_presbyter();
                                if (member == 0)
                                        member = ({});
                                if (sizeof(member) >= 4)
                                {
                                        send_user(who, "%c%s", '!', "\"" + name2 + "\" chức vụ Trưởng Lão không trống");
                                        if (flag)
                                                destruct(char);
                                        return;
                                }
                                member -= ({0});
                                member -= ({char->get_id()});
                                member += ({char->get_id()});
                                me->set_presbyter(member);
                                me->set_member_rank(number, "Trưởng Lão");
                                if (trader_flag)
                                        me->set_member_rank(number, "Trưởng Lão Thương Nhân");
                                char->set_org_position(ORG_PRESBYTER);
                                char->set_org_title("Trưởng Lão");
                                char->add_title("C003");
                                char->show_title("C003");
                                break;
                        case 3:
                                member = me->get_manager4();
                                if (member == 0)
                                        member = ({});
                                if (sizeof(member) >= 6)
                                {
                                        send_user(who, "%c%s", '!', "\"" + name2 + "\" chức vụ Đường Chủ không trống");
                                        if (flag)
                                                destruct(char);
                                        return;
                                }
                                member -= ({0});
                                member -= ({char->get_id()});
                                member += ({char->get_id()});
                                me->set_manager4(member);
                                me->set_member_rank(number, "Đường Chủ");
                                if (trader_flag)
                                        me->set_member_rank(number, "Đường Chủ Thương Nhân");
                                char->set_org_position(ORG_TANGZHU);
                                char->set_org_title("Đường Chủ");
                                char->add_title("C004");
                                char->show_title("C004");
                                break;
                        case 4:
                                member = me->get_manager5();
                                if (member == 0)
                                        member = ({});
                                if (sizeof(member) >= 10)
                                {
                                        send_user(who, "%c%s", '!', "\"" + name2 + "\" chức vụ Hương Chủ không trống");
                                        if (flag)
                                                destruct(char);
                                        return;
                                }
                                member -= ({0});
                                member -= ({char->get_id()});
                                member += ({char->get_id()});
                                me->set_manager5(member);
                                me->set_member_rank(number, "Hương Chủ");
                                if (trader_flag)
                                        me->set_member_rank(number, "Hương Chủ Thương Nhân");
                                char->set_org_position(ORG_XIANGZHU);
                                char->set_org_title("Hương Chủ");
                                char->add_title("C005");
                                char->show_title("C005");
                                break;
                        case 5:
                                member = me->get_manager6();
                                if (member == 0)
                                        member = ({});
                                if (sizeof(member) >= 16)
                                {
                                        send_user(who, "%c%s", '!', "\"" + name2 + "\" chức vụ Tinh Anh không trống");
                                        if (flag)
                                                destruct(char);
                                        return;
                                }
                                member -= ({0});
                                member -= ({char->get_id()});
                                member += ({char->get_id()});
                                me->set_manager6(member);
                                me->set_member_rank(number, "Tinh Anh");
                                if (trader_flag)
                                        me->set_member_rank(number, "Tinh Anh Thương Nhân");
                                char->set_org_position(ORG_JINGYING);
                                char->set_org_title("Tinh Anh");
                                char->add_title("C006");
                                char->show_title("C006");
                                break;
                        case 6:
                                if (char->get_level() < 40)
                                {
                                        send_user(who, "%c%s", '!', "Đảm nhiệm Thương Nhân cần đạt cấp 40");
                                        if (flag)
                                                destruct(char);
                                        return;
                                }
                                member = me->get_trader();
                                if (member == 0)
                                        member = ({});
                                if (sizeof(member) >= 4)
                                {
                                        send_user(who, "%c%s", '!', "\"" + name2 + "\" chức vụ Thương Nhân không trống");
                                        if (flag)
                                                destruct(char);
                                        return;
                                }
                                member -= ({0});
                                member -= ({char->get_id()});
                                member += ({char->get_id()});
                                me->set_trader(member);
                                me->set_member_rank(number, "Thương Nhân");
                                if (char->get_org_position() > 1)
                                        me->set_member_rank(number, char->get_org_title() + "Thương Nhân");
                                //                                char->set_org_position(ORG_TRADER);
                                char->add_title("C007");
                                char->show_title("C007");
                                break;
                        case 7:
                                me->set_member_rank(number, "－－");
                                char->set_org_position(ORG_MEMBER);
                                char->set_org_title("Bang Chúng");
                                if (trader_flag)
                                        me->set_member_rank(number, "Thương Nhân");
                                char->add_title("C008");
                                char->show_title("C008");
                                break;
                        case 8:
                                if ((member = me->get_trader()) && arrayp(member) && member_array(id, member) != -1)
                                {
                                        member -= ({id});
                                        me->set_trader(member);
                                        char->delete_title("C007");
                                        me->set_member_rank(char->get_number(), char->get_org_title());
                                }
                                break;
                        }
                        if (level != 7 && level != 6 && level != 8)
                                char->delete_title("C008");
                        if (level != 8)
                        {
                                write_user(who, ECHO "Ngài nhậm mệnh %s (%d) là \"%s\" %s！",
                                           char->get_name(), char->get_number(), name2,
                                           me->get_member_rank(number) != "－－" ? me->get_member_rank(number) : "Bang Chúng");
                        }
                        else
                        {
                                write_user(who, ECHO "Ngài giải trừ %s (%d) chức vụ Thương Nhân !",
                                           char->get_name(), char->get_number());
                        }
                        send_user(who, "%c%c%d%d%c%d%d%c%s", 0x95, 11, number,
                                  me->get_member_time(number), me->get_member_quit(number) ? 0 : 1,
                                  me->get_member_gold(number), me->get_member_all_contribute(number), me->get_member_level(number),
                                  sprintf("%-12s%s", me->get_member_name(number), me->get_member_rank(number)));

                        char->save();
                        me->save();
                        if (level != 8)
                                char->log_legend(sprintf("Ngài bị %s (%d) nhâm mệnh là \"%s\" %s！",
                                                         who->get_name(), who->get_number(), name2, me->get_member_rank(number) != "－－" ? me->get_member_rank(number) : "Bang Chúng"));
                        else
                                char->log_legend(sprintf("Ngài bị %s (%d) giải trừ chức vụ Thương Nhân !",
                                                         who->get_name(), who->get_number()));
                        if (level != 8)
                                FAMILY_D->org_channel(name2, 0, sprintf(HIR "%s nhâm mệnh %s (%d) vì bổn bang %s !", who->get_name(), char->get_name(), char->get_number(), me->get_member_rank(number) != "－－" ? me->get_member_rank(number) : "Bang Chúng"));
                        else
                                FAMILY_D->org_channel(name2, 0, sprintf(HIR "%s giải trừ %s (%d) chức vụ Thương Nhân !", who->get_name(), char->get_name(), char->get_number()));

                        if (flag)
                                destruct(char);
                        else
                                send_user(char, "%c%c%c%s", 0x3d, 49,
                                          char->get_org_position(), char->get_org_name());
                }
        }
}

// 函数:Bang Chủ让位
void do_demise(object who, object me, string arg)
{
        object char;
        string name1, name2, name3, *member;
        string cmd, id, result;
        int number;

        name1 = who->get_org_name();
        name2 = me->get_org_name();

        if (stringp(name1) && stringp(name2) && name1 == name2 && who->get_org_position() >= ORG_MASTER) // Bang Chủ
        {
                if (who->get_number() != me->get_master())
                {
                        send_user(who, "%c%s", '!', "Chỉ có Bang Chủ mới có thể thoái vị");
                        return;
                }
                if (!sscanf(arg, "@.%d", number))
                {
                        if (number == who->get_number())
                        {
                                send_user(who, "%c%s", '!', "Không thể tự nhường chức vị cho chính mình");
                                return;
                        }
                        if (!(char = find_player(arg)))
                        {
                                send_user(who, "%c%s", '!', "Mục tiêu được nhường chức vị không có trong trò chơi");
                                return;
                        }
                        number = to_int(arg);
                        if (me->get_demisstime() > 0)
                        {
                                me->set_demissnumber(0);
                                me->set_demisstime(0);
                                send_user(who, "%c%s", '!', "Bạn huỷ bỏ nhường ngôi !");
                                FAMILY_D->org_channel(name2, 0, sprintf(HIR "%s(%d) huỷ bỏ nhường ngôi", who->get_name(), who->get_number()));
                                return;
                        }
                        if (me->get_member_id(number))
                        {
                                cmd = sprintf("talk %x# demise.@.%d\n", getoid(me), number);
                                send_user(who, "%c%s", ':', sprintf("Ngươi đem chức vị Bang Chủ nhường cho %s (%d), sau đó tiếp tục làm thành viên bình thường, có phải không ?\n", me->get_member_name(number), number) + ESC "Đúng vậy\n" + cmd + ESC "Ta muốn suy nghĩ……\nCLOSE\n");
                        }
                        return;
                }
                if (me->get_member_id(number))
                {
                        if (number == who->get_number())
                        {
                                send_user(who, "%c%s", '!', "Không thể tự nhường chức vị cho chính mình");
                                return;
                        }
                        if (!(char = find_player(sprintf("%d", number))))
                        {
                                send_user(who, "%c%s", '!', "Mục tiêu được nhường chức vị không có trong trò chơi");
                                return;
                        }
                        me->set_demissnumber(number);
                        me->set_demisstime(time() + 24 * 3600);
                        FAMILY_D->org_channel(name2, 0, sprintf(HIR "Bang Chủ %s ưu ái %s (%d) nhường chức vị, 24h sau sẽ có hiệu lực", who->get_name(), me->get_member_name(number), number));
                        return;
                }
        }
}

void do_demise2(object me, int number)
{
        object who;
        object char, char2;
        string name1, name2, name3, *member;
        string cmd, id, result;
        int flag1, flag2;
        name2 = me->get_org_name();
        if (me->get_member_id(number))
        {

                if (number == me->get_master())
                        return;
                if (!(char = find_player(sprintf("%d", number))))
                {
                        if ("sys/sys/user2"->check_id_online(number) != 0)
                        {

                                return;
                        }
                        char = new (USER);
                        char->set_id(me->get_member_id(number));
                        if (!char->restore())
                        {
                                return;
                        }
                        flag1 = 1; // 离线
                }
                if (!(who = find_player(sprintf("%d", me->get_master()))))
                {
                        if ("sys/sys/user2"->check_id_online(me->get_master()) != 0)
                        {
                                return;
                        }
                        who = new (USER);
                        who->set_id(me->get_member_id(me->get_master()));
                        if (!who->restore())
                        {
                                if (flag1 == 1)
                                        destruct(char);
                                return;
                        }
                        flag2 = 1; // 离线
                }

                name3 = char->get_org_name();
                if (!stringp(name3) || name3 == "" || name3 != name2) // 双保险，可删除
                {
                        send_user(who, "%c%s", '!', char->get_name() + "Không phải \"" + name2 + "\" bang chúng");
                        if (flag1 == 1)
                                destruct(char);
                        if (flag2 == 1)
                                destruct(who);
                        return;
                }

                id = char->get_id();
                if (id == me->get_master_id_2())
                {
                        me->set_master_2(0);
                        me->set_master_id_2("");
                        me->set_master_name_2("－－");
                        char->delete_title("C002");
                }
                member = me->get_presbyter();
                if (arrayp(member) && member_array(id, member) != -1)
                {
                        member -= ({id});
                        me->set_presbyter(member);
                        char->delete_title("C003");
                }
                member = me->get_manager4();
                if (arrayp(member) && member_array(id, member) != -1)
                {
                        member -= ({id});
                        me->set_manager4(member);
                        char->delete_title("C004");
                }
                if ((member = me->get_manager5()) && arrayp(member) && member_array(id, member) != -1)
                {
                        member -= ({id});
                        me->set_manager5(member);
                        char->delete_title("C005");
                }
                if ((member = me->get_manager6()) && arrayp(member) && member_array(id, member) != -1)
                {
                        member -= ({id});
                        me->set_manager6(member);
                        char->delete_title("C006");
                }
                if ((member = me->get_trader()) && arrayp(member) && member_array(id, member) != -1)
                {
                        member -= ({id});
                        me->set_trader(member);
                }
                me->set_master(number);
                me->set_master_id(me->get_member_id(number));
                me->set_master_name(me->get_member_name(number));
                me->set_member_rank(number, "Bang Chủ");
                me->set_member_rank(who->get_number(), "－－");

                char->set_org_position(ORG_MASTER);
                char->set_org_title("Bang Chủ");
                char->delete_title("C008");
                char->delete_title("C007");
                char->delete_title("C006");
                char->delete_title("C005");
                char->delete_title("C004");
                char->delete_title("C003");
                char->delete_title("C002");
                char->add_title("C001");
                char->show_title("C001");
                who->delete_title("C001");
                who->set_org_position(ORG_MEMBER);
                who->set_org_title("－－");
                who->add_title("C008");
                who->show_title("C008");

                result = sprintf("Ngài nhường ngôi Bang Chủ cho %s(%d) !", char->get_name(), char->get_number());
                write_user(who, ECHO + result);
                who->log_legend(result);
                result = sprintf("%s(%d) nhường ngôi Bang Chủ cho bạn !", who->get_name(), who->get_number());
                write_user(char, ECHO + result);
                me->add_favour(-100);
                me->add_stable(-300);
                char->log_legend(result);
                FAMILY_D->org_channel(name2, 0, sprintf(HIR "%s đem Bang Chủ nhường ngôi cho %s(%d) !", who->get_name(), char->get_name(), char->get_number()));
                WUSHUANG->check_org_title(char);
                WUSHUANG->check_org_title(who);
                if (flag1)
                {
                        char->save();
                        destruct(char);
                }
                else
                {
                        send_user(char, "%c%c%c%s", 0x3d, 49,
                                  char->get_org_position(), char->get_org_name());
                }
                if (flag2)
                {
                        who->save();
                        destruct(who);
                }
                else
                {
                        send_user(who, "%c%c%c%s", 0x3d, 49,
                                  who->get_org_position(), who->get_org_name());
                }
                me->set_demissnumber(0);
                me->set_demisstime(0);
        }
}

// void do_banish2(string who, object me, string id2, int id, int sl)
// {
//         object char;
//         string name2;
//         int kenh, flag, stt, i;
//         string *list = MAIN_D->getlist();
//         name2 = me->get_org_name();
//         kenh = MAIN_D->get_kenh();
//         if ("sys/sys/user2"->check_id_online(id) != 0 && sl <= sizeof(list) + 1)
//         {
//                 if (sl == sizeof(list))
//                 {
//                         for (i = 0; i < sizeof(list); i++)
//                         {
//                                 if (kenh == to_int(list[i]))
//                                         continue;

//                                 ghi_file(sprintf("bang/check%s.txt", list[i]), sprintf("\nkicknumber %d", id));
//                         }
//                 }
//                 stt = member_array(sprintf("%d", kenh), list) + 1;
//                 if (stt >= sizeof(list))
//                 {
//                         stt = 0;
//                 }
//                 kenh = to_int(list[stt]);
//                 // if (kenh > sizeof(list))
//                 //         kenh = 1;
//                 ghi_file(sprintf("bang/check%d.txt", kenh), sprintf("\ndo_banish %s:%s:%s:%d:%d", name2, who, id2, id, sl + 1));
//                 return;
//         }
//         if (!(char = find_player(sprintf("%d", id))))
//         {
//                 char = new (USER);

//                 char->set_id(id2);
//                 if (!char->restore())
//                 {
//                         destruct(char);
//                         return;
//                 }
//                 flag = 1;
//         }
//         // FAMILY_D->org_channel(name2, 0, sprintf(HIR "%s đem %s(%d) trục xuất ra bang !", who, char->get_name(), char->get_number()));
//         char->set_org_name("");
//         char->set_org_position(0);
//         char->set_org_title("");
//         char->set_org_time(time());
//         char->delete_title("C001");
//         char->delete_title("C002");
//         char->delete_title("C003");
//         char->delete_title("C004");
//         char->delete_title("C005");
//         char->delete_title("C006");
//         char->delete_title("C007");
//         char->delete_title("C008");
//         char->save();
//         tell_user(char, sprintf(HIR "%s đem bạn trục xuất ra bang !", who));
//         if (flag)
//                 destruct(char);
//         else
//         {
//                 send_user(char, "%c%c", 0x95, 255); // 关闭所有Bang Phái界面
//                 send_user(char, "%c%c%c%c", 0x3d, 49, 0, 0);
//         }
//         return;
// }
void do_banish2(string who, object me, string id2, int id)
{
        object char;
        string name2;
        int kenh, flag, stt, i, checkkenh;
        string *list = MAIN_D->getlist();
        name2 = me->get_org_name();
        kenh = MAIN_D->get_kenh();

        if ((checkkenh = "sys/sys/user2"->check_id_online(id)) && checkkenh != kenh)
        {

                ghi_file(sprintf("bang/check%d.txt", checkkenh), sprintf("\ndo_banish %s:%s:%s:%d", name2, who, id2, id));
                return;
        }
        if (!(char = find_player(sprintf("%d", id))))
        {
                char = new (USER);

                char->set_id(id2);
                if (!char->restore())
                {
                        destruct(char);
                        return;
                }
                flag = 1;
        }
        // FAMILY_D->org_channel(name2, 0, sprintf(HIR "%s đem %s(%d) trục xuất ra bang !", who, char->get_name(), char->get_number()));
        char->set_org_name("");
        char->set_org_position(0);
        char->set_org_title("");
        char->set_org_time(time());
        char->delete_title("C001");
        char->delete_title("C002");
        char->delete_title("C003");
        char->delete_title("C004");
        char->delete_title("C005");
        char->delete_title("C006");
        char->delete_title("C007");
        char->delete_title("C008");
        char->save();
        tell_user(char, sprintf(HIR "%s đem bạn trục xuất ra bang !", who));
        if (flag)
                destruct(char);
        else
        {
                send_user(char, "%c%c", 0x95, 255); // 关闭所有Bang Phái界面
                send_user(char, "%c%c%c%c", 0x3d, 49, 0, 0);
        }
        return;
}

// 函数:放逐出帮
void do_banish(object who, object me, string arg)
{
        object char;
        string name1, name2, name3, cmd, id, *member;

        int number, flag, contrib, i, id2, flag2;
        int kenh = MAIN_D->get_kenh(), j;

        name1 = who->get_org_name();
        name2 = me->get_org_name();

        if (stringp(name1) && stringp(name2) && name1 == name2 && who->get_org_position() > ORG_PRESBYTER) // 本帮官员
        {
                sscanf(arg, "%d", number);

                if (me->get_member_id(number))
                {
                        if (!(char = find_player(sprintf("%d", number))))
                        {
                                if ("sys/sys/user2"->check_id_online(number) != 0)
                                {
                                        flag2 = 1;
                                }
                                char = new (USER);
                                char->set_id(me->get_member_id(number));
                                if (!char->restore())
                                {
                                        me->delete_member_info(number);
                                        me->add_total(-1);
                                        send_user(who, "%c%s", '!', " Vị này không tồn tại !");
                                        destruct(char);
                                        return;
                                }
                                flag = 1; // 离线
                        }

                        name3 = char->get_org_name();
                        if (!stringp(name3) || name3 == "" || name3 != name2) // 双保险，可删除
                        {
                                me->delete_member_info(number);
                                me->add_total(-1);
                                send_user(who, "%c%s", '!', char->get_name() + "Không phải \"" + name2 + "\" bang chúng");
                                if (flag)
                                        destruct(char);
                                return;
                        }

                        if (char->get_org_position() >= who->get_org_position()) // 权限判断！
                        {
                                send_user(who, "%c%s", '!', "Bạn ở \"" + name2 + "\" chức vị rất thấp");
                                if (flag)
                                        destruct(char);
                                return;
                        }

                        id = char->get_id();
                        if (id == me->get_master_id_2())
                        {
                                me->set_master_2(0);
                                me->set_master_id_2("");
                                me->set_master_name_2("－－");
                        }
                        member = me->get_presbyter();
                        if (arrayp(member) && member_array(id, member) != -1)
                        {
                                member -= ({id});
                                me->set_presbyter(member);
                        }
                        member = me->get_manager4();
                        if (arrayp(member) && member_array(id, member) != -1)
                        {
                                member -= ({id});
                                me->set_manager4(member);
                        }
                        if ((member = me->get_manager5()) && arrayp(member) && member_array(id, member) != -1)
                        {
                                member -= ({id});
                                me->set_manager5(member);
                        }
                        if ((member = me->get_manager6()) && arrayp(member) && member_array(id, member) != -1)
                        {
                                member -= ({id});
                                me->set_manager6(member);
                        }
                        if ((member = me->get_trader()) && arrayp(member) && member_array(id, member) != -1)
                        {
                                member -= ({id});
                                me->set_trader(member);
                        }
                        contrib = me->get_member_contribute(number);
                        me->delete_member_info(number);
                        send_user(who, "%c%c%d", 0x95, 13, number);
                        send_user(who, "%c%c%d", 0x95, 95, number);
                        me->add_total(-1);
                        // 如果对方是禅让的, 则取消禅让
                        if (me->get_demisstime() > 0)
                        {
                                if (me->get_demissnumber() == number)
                                {
                                        me->set_demisstime(0);
                                        me->set_demissnumber(0);
                                }
                        }

                        char->set_org_name("");
                        char->set_org_position(0);
                        char->set_org_title("");
                        char->set_org_time(time());
                        char->delete_title("C001");
                        char->delete_title("C002");
                        char->delete_title("C003");
                        char->delete_title("C004");
                        char->delete_title("C005");
                        char->delete_title("C006");
                        char->delete_title("C007");
                        char->delete_title("C008");
                        if (flag2)
                        {
                                ghi_file(sprintf("bang/check%d.txt", "sys/sys/user2"->check_id_online(number)), sprintf("\ndo_banish %s:%s:%s:%d", name2, who->get_name(), char->get_id(), number));
                                //     for (j = 1; j < 4; j++)
                                //     {
                                //           if (kenh == j)
                                //                 continue;
                                //       ghi_file(sprintf("bang/check%d.txt", j), sprintf("\ndo_banish %s:%s:%d", me->get_org_name(), who->get_name(), number));
                                //}
                        }
                        else
                        {
                                char->save();
                        }
                        char->log_legend(sprintf("Bạn bị %s(%d) trục xuất ra khỏi \"%s\", Cống hiến : %d !", who->get_name(), who->get_number(), name2, contrib));
                        FAMILY_D->org_channel(name2, 0, sprintf(HIR "%s đem %s(%d) trục xuất ra bang !", who->get_name(), char->get_name(), char->get_number()));
                        WUSHUANG->check_org_title(char);
                        if (flag)
                                destruct(char);
                        else
                        {
                                send_user(char, "%c%c", 0x95, 255); // 关闭所有Bang Phái界面
                                send_user(char, "%c%c%c%c", 0x3d, 49,
                                          0, 0);
                        }
                }
                else
                {
                        me->delete_member_info(number);
                }
        }
}
// 函数:退出Bang Phái (有Ngân Phiếu不能离帮)
void do_exit(object who, object me, string arg)
{
        string name1, name2, cmd, *member, id;
        int number, flag, contrib;
        object item;

        name1 = who->get_org_name();
        name2 = me->get_org_name();

        if (stringp(name1) && stringp(name2) && name1 == name2) // 本帮Bang Chúng
        {
                if (present("Ngân Phiếu", who, 1, MAX_CARRY * 4))
                {
                        send_user(me, "%c%s", '!', "Ngươi có Ngân Phiếu trong người, không thể ly giúp");
                        return;
                }
                if (who->get_org_position() >= ORG_MASTER)
                {
                        send_user(who, "%c%s", '!', "Bạn ở \"" + name2 + "\" chức vị quá cao, không thể chủ động ly giúp");
                        return;
                }
                id = who->get_id();
                if (!arg || arg != "@")
                {
                        cmd = sprintf("talk %x# exit.@\n", getoid(me));
                        send_user(who, "%c%s", ':', "Ngươi quyết định hy sinh Cống hiến cũng phải rời khỏi \"" + name2 + "\" phải không ?\n" ESC "Đúng vậy\n" + cmd + ESC "Ta muốn suy nghĩ……\nCLOSE\n");
                        return;
                }
                if (id == me->get_master_id_2())
                {
                        me->set_master_2(0);
                        me->set_master_id_2("");
                        me->set_master_name_2("－－");
                }
                member = me->get_presbyter();
                if (arrayp(member) && member_array(id, member) != -1)
                {
                        member -= ({id});
                        me->set_presbyter(member);
                }
                member = me->get_manager4();
                if (arrayp(member) && member_array(id, member) != -1)
                {
                        member -= ({id});
                        me->set_manager4(member);
                }
                if ((member = me->get_manager5()) && arrayp(member) && member_array(id, member) != -1)
                {
                        member -= ({id});
                        me->set_manager5(member);
                }
                if ((member = me->get_manager6()) && arrayp(member) && member_array(id, member) != -1)
                {
                        member -= ({id});
                        me->set_manager6(member);
                }
                if ((member = me->get_trader()) && arrayp(member) && member_array(id, member) != -1)
                {
                        member -= ({id});
                        me->set_trader(member);
                }
                number = who->get_number();
                contrib = me->get_member_contribute(number);
                me->delete_member_info(number);
                send_user(who, "%c%c%d", 0x95, 23, number);
                send_user(who, "%c%c%d", 0x95, 96, number);
                me->add_total(-1);

                who->set_org_name("");
                who->set_org_position(0);
                who->set_org_title("");
                who->set_org_time(time());
                who->delete_title("C001");
                who->delete_title("C002");
                who->delete_title("C003");
                who->delete_title("C004");
                who->delete_title("C005");
                who->delete_title("C006");
                who->delete_title("C007");
                who->delete_title("C008");
                who->log_legend(sprintf("Bạn rời khỏi \"%s\", Cống hiến: %d !", name2, contrib));
                FAMILY_D->org_channel(name2, 0, sprintf(HIR "%s rời khỏi bổn bang", who->get_name()));

                send_user(who, "%c%c", 0x95, 255); // 关闭所有Bang Phái界面
                send_user(who, "%c%c%c%c", 0x3d, 49,
                          0, 0);
                WUSHUANG->check_org_title(who);
        }
}

// -------------------------------------------------------------

// 函数:Bang Phái金库
void do_savings(object who, object me, string arg)
{
        string name1, name2, result;
        int id, gold, i, size, number;

        id = getoid(me);

        name1 = who->get_org_name();
        name2 = me->get_org_name();

        if (stringp(name1) && stringp(name2) && name1 == name2) // 本帮Bang Chúng
        {
                gold = to_int(arg);

                if (!gold)
                {
                        send_user(who, "%c%c%d%d%s", 0x95, 60, id, me->get_gold(), me->get_org_name());
                }
                else
                {
                        if (gold < 1)
                        {
                                send_user(who, "%c%s", '!', "Quyên tiền phải là chính số nguyên");
                                return;
                        }
                        if (gold > who->get_cash())
                        {
                                send_user(who, "%c%s", '!', sprintf("Bạn trên người chỉ có %d lượng", who->get_cash()));
                                return;
                        }
                        if (me->get_gold() >= me->get_grade() * 40000000)
                        {
                                send_user(who, "%c%s", '!', sprintf("\"%s\" Bang Phái tài chính đã đạt hạn mức cao nhất !", me->get_org_name()));
                                return;
                        }
                        if (gold + me->get_gold() >= me->get_grade() * 40000000)
                                gold = me->get_grade() * 40000000 - me->get_gold();

                        who->add_cash(-gold);
                        who->add_gold_log("org", gold);
                        who->log_money("Bang Phái", -gold);
                        "/sys/sys/count"->add_use("org", gold);
                        send_user(who, "%c%c%d", 0x95, 61, me->add_gold(gold));

                        id = who->get_number();
                        send_user(who, "%c%c%d", 0x95, 62, me->set_member_gold(id, me->get_member_gold(id) + gold));

                        result = sprintf("Bạn xuất ra %d lượng hiến cho \"%s\".", gold, me->get_org_name());
                        send_user(who, "%c%s", '!', result);
                        write_user(who, ECHO + result);

                        result = sprintf(HIR "%s(%d) xuất ra %d lượng hiến cho Bang !", who->get_name(), who->get_number(), gold);
                        if (gold >= 100000)
                                FAMILY_D->org_channel(name2, 0, result);
                        if (gold >= 10000)
                        {
                                number = who->get_number();
                                me->set_member_contribute(number, me->get_member_contribute(number) + gold / 10000);
                                send_user(who, "%c%c%w%s", ':', 3, 0, sprintf("Bởi vì ngươi vì Bang phái cống hiến không ít, ngươi chiếm được %d điểm cống hiến bang phái", gold / 10000));
                        }
                }
        }
}
