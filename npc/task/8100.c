
#include <npc.h>
#include <ansi.h>
#include <cmd.h>
#include <effect.h>

inherit SLAVE;

private
static object Owner; // 用户标识

int get_char_type() { return 160; }

int get_max_level0() { return 1; }

// 函数：获取气血比例(不显示血条，超过50)
int get_hp_cent() { return 60; }

// 函数：获取用户标识
object get_owner() { return Owner; }

// 函数：设置用户标识
object set_owner(object who) { return Owner = who; }

void do_push(string arg);

void follow_owner(object me);

// 函数：构造处理
void create()
{
        object me = this_object();

        set_name("Thân Hữu");
        NPC_EQUIP_D->init_figure(this_object(), RICH_LADY, FEMALE, 20);

        set_2("talk", (["push":(
                                   : do_push:),
        ]));

        setup();

        set("birthday", time());

        if (!clonep(me))
                return;

        set_heart_timer(me, set_heart_timer_2(me, getoid(me) % 10)); // 心跳随机
        set_heart_loop(me, 10);                                      // 循环心跳：１秒钟
        me->heart_beat();
        set_heart_beat(1);
}

// 函数：允许走路
int is_moveable() { return 1; } // 能使用 go 命令

int can_fight(object who) { return 0; }

int can_be_fighted(object who)
{
        if (who->get_quest("escort.flag")                                                // 运镖任务
            && who->get_quest("escort.leader") == 1                                      // 队长接镖
            && who->get_quest("escort.escort") == sprintf("%x#", getoid(this_object()))) // 找对人了
        {
                set_owner(who);
                who->set_quest("escort.npc", this_object());
        }
        return 0;
}

// -------------------------------------------------------------

// 函数：对话处理
void do_look(object who)
{
        if (who->get_quest("escort.flag")                                                // 运镖任务
            && who->get_quest("escort.leader") == 1                                      // 队长接镖
            && who->get_quest("escort.escort") == sprintf("%x#", getoid(this_object()))) // 找对人了
        {
                set_owner(who);
                who->set_quest("escort.npc", this_object());
        }
}

// 变量：随机对话
string *TalkTableNPC = ({
    "Cứu mạng ~ có yêu quái kìa!#09",
    "Chạy mau#10",
    "Nhanh lên nhanh lên#52",
    "Oa, Yêu quái kia có hình người#24",
    "Ôh, bộ dạng xấu như vậy là ai kia ?#67",
});

int sizeof_talk_npc = sizeof(TalkTableNPC);

// 变量：随机对话
string *TalkTableUser = ({
    "Đi mau đi mau, nhiều đang nhìn xấu hổ quá đi#26",
    "Người kia như thế nào nhìn chằm chằm ngừoi ta#24",
});

int sizeof_talk_user = sizeof(TalkTableUser);

// 变量：随机对话
string *TalkTableUser2 = ({
    "Lấy chồng cha mẹ không có khác biệt lắm ?!#05",
    "Bọn hộ đều đang làm đâu?#67",
});

int sizeof_talk_user2 = sizeof(TalkTableUser2);

// 变量：随机对话
string *TalkTableLost = ({
    "Từ từ kẻo ngã#50",
    "Đừng chạy nhanh như vậy, người ta mệt rồi#68",
    "Phong cảnh thật đẹp#33 không muốn đi nữa",
});

int sizeof_talk_lost = sizeof(TalkTableLost);

// 变量：随机对话
string *TalkTableNone = ({
    "Ngươi không thể bỏ lại người khác nửa đường#75",
    "Còn chưa tới à, mệt chết#05",
    "Nhanh lên, trời sắp mưa rồi#52",
    "Nhàm chán à, để ta hát ngươi nghe nha !?#63",
    "Ngươi buồn không? Ta hát \"Trên đời chỉ có mụ mụ\" cho ngươi nghe……#75",
});

int sizeof_talk_none = sizeof(TalkTableNone);

// -------------------------------------------------------------

private
static int HeartSec = 0; // 心跳计时

// 函数：获取心跳计时
int get_heart_sec() { return HeartSec; }

// 函数：设置心跳计时
int set_heart_sec(int point) { return HeartSec = point; }

// 函数：增添心跳计时
int add_heart_sec(int point) { return set_heart_sec(HeartSec + point); }

// 函数：心跳处理(循环)
void heart_beat_loop(int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) { __FILE__->heart_beat_loop_callout(this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout(object me, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) // 每１秒处理
{
        object *char, owner;
        string *result;
        int z, x, y, p;
        /*
        if( objectp( owner = me->get_owner() ) )
        {
                if( distance_between(me, owner) > 1 && inside_screen_2(me, owner) )    // 跟随：每秒３步
                {
                        z = get_z(owner);  x = get_x(owner);  y = get_y(owner);
                        if( p = get_valid_path( z, get_x(me), get_y(me), x, y ) )
                                GO_CMD->main_npc( me, sprintf("%d", p) );
                        else    GO_CMD->main_npc( me, sprintf("%d", random(8) + 1) );    // 随机走路
                        x = get_x(owner);  y = get_y(owner);
                        if( p = get_valid_path( z, get_x(me), get_y(me), x, y ) )
                                GO_CMD->main_npc( me, sprintf("%d", p) );                                                
                }
                else    GO_CMD->main_npc( me, sprintf("%d", random(8) + 1) );    // 随机走路
        }
*/
        p = me->add_heart_sec(1);

        if (p % 60 == 0) // 每１分处理以下
        {
                if (p % 120 == 0) // 每２分处理以下
                {
                        z = get_z(me);
                        x = get_x(me);
                        y = get_y(me);
                        result = ({});

                        char = get_range_object(z, x, y, 10, CHAR_TYPE);

                        if (arrayp(char) && sizeof(char))
                                result += ({TalkTableNPC[random(sizeof_talk_npc)]});

                        if (objectp(owner = me->get_owner()))
                        {
                                char = get_range_object(z, x, y, 10, USER_TYPE) - ({owner, me});
                                if (!inside_screen_2(me, owner))
                                        result += ({TalkTableLost[random(sizeof_talk_lost)]});
                        }
                        else
                                char = get_range_object(z, x, y, 10, USER_TYPE) - ({me});

                        if (arrayp(char) && sizeof(char))
                        {
                                p = random(sizeof(char));
                                if (char[p] && char[p]->get_gender() == 1)
                                        result += ({TalkTableUser[random(sizeof_talk_user)]});
                                else
                                        result += ({TalkTableUser2[random(sizeof_talk_user2)]});
                        }
                        else
                                result += ({TalkTableNone[random(sizeof_talk_none)]});

                        SAY_CMD->say(me, result[random(sizeof(result))]);
                }

                if (objectp(owner = me->get_owner()) && owner->get_quest("escort.flag") == 2 && gone_time(owner->get_quest("escort.time")) >= 2400) // 40 分钟
                {
                        //                        write_user(owner, ECHO "运镖任务失败，请回报尉迟老镖头。");
                        //                        send_user(owner, "%c%s", '!', "运镖任务失败，请回报尉迟老镖头。");
                        me->remove_from_scene();
                        destruct(me);
                        return;
                }

                if (gone_time(me->get("birthday")) >= 2400) // 40 分钟
                {
                        me->remove_from_scene();
                        destruct(me);
                        return;
                }
        }
}

// 函数：从场景中移除
varargs void remove_from_scene(int rm_pf, int rm_pf_2)
{
        object me, owner;

        ::remove_from_scene(rm_pf, rm_pf_2);

        me = this_object();
        if (owner = me->get_owner())
                send_user(owner, "%c%c%d%w%w", 0x54, 11, getoid(me), -1, -1); // 更新召唤兽坐标
}

// 函数：推开处理
void do_push(string arg) { __FILE__->do_push_callout(this_player(), this_object(), arg); }

// 函数：推开处理(在线更新)
void do_push_callout(object who, object me, string arg)
{
        int z, x, y, p;

        z = get_z(me);
        x = get_x(me);
        y = get_y(me);

        if (distance_between(me, who) > 1)
        {
                send_user(who, "%c%s", '!', "Khoảng cách của ngươi và " + me->get_name() + " quá xa");
                return;
        }

        if (arg == "1")
        {
                if (who->get_mp() < 10)
                {
                        send_user(who, "%c%s", '!', "Đẩy ra " + me->get_name() + " cần 10 điểm Pháp Lực");
                        return;
                }
                who->add_mp(-10);

                switch (get_d(who))
                {
                case 1:
                        x++;
                        break;
                case 2:
                        x++;
                        y--;
                        break;
                default:
                        y--;
                        break;
                case 4:
                        x--;
                        y--;
                        break;
                case 5:
                        x--;
                        break;
                case 6:
                        x--;
                        y++;
                        break;
                case 7:
                        y++;
                        break;
                case 8:
                        x++;
                        y++;
                        break;
                }

                if (get_block(z, x, y) & IS_CHAR_BLOCK)
                        return;

                me->add_to_scene(z, x, y, get_d(me));

                write_user(who, ECHO "Bạn đem " + me->get_name() + " đẩy ra");
                //              write_user( me, ECHO "%s(%d)把您推开。", who->get_name(), who->get_number() );
        }
        else if (arg == "2")
        {
                if (who->get_mp() < 30)
                {
                        send_user(who, "%c%s", '!', "Ném ra " + me->get_name() + " cần 30 điểm Pháp Lực");
                        return;
                }
                who->add_mp(-30);

                if (!(p = get_valid_xy(z, x + random(10) - 5, y + random(10) - 5, IS_CHAR_BLOCK)))
                        return;

                x = p / 1000;
                y = p % 1000;
                me->add_to_scene(z, x, y, get_front_xy(x, y, get_x(who), get_y(who)));
                who->to_front_eachother(me);

                write_user(who, ECHO "Bạn đem " + me->get_name() + " ném ra ngoài");
                //              write_user( me, ECHO "%s(%d)把您扔了出去。", who->get_name(), who->get_number() );
        }
}

void heart_beat_walk() // 每 0.1 秒处理
{
        object owner, who, me;
        string cmd;
        int x, y, x1, y1, p, walk;
        me = this_object();
        owner = me->get_owner();
        if (get_effect(me, EFFECT_CHAR_BUSY) || get_effect(me, EFFECT_CHAR_FAINT) || get_effect(me, EFFECT_SLEEP) || get_effect(me, EFFECT_CHAR_FAINT_2) || get_effect(me, EFFECT_CHAR_FREEZE))
                return;
        follow_owner(me);
}

void follow_owner(object me)
{
        object owner, who;
        string cmd;
        int x, y, z, x1, y1, p, walk;
        x = get_x(me);
        y = get_y(me);
        if (objectp(owner = me->get_owner()))
        {
                x1 = get_x(owner);
                y1 = get_y(owner);
                z = get_z(owner);
                if (z != get_z(owner) || distance_between(me, owner) >= 25 && me->get_action() != 0) // 远了就不动
                {
                        return;
                }
                if (abs(x - x1) < 2 && abs(y - y1) < 2)
                {
                        me->set_action(me->get_next_action());
                        return;
                }

                if (x1 > x)
                        x1--;
                else if (x1 < x)
                        x1++;
                if (y1 > y)
                        y1--;
                else if (y1 < y)
                        y1++;

                if (x != x1 || y != y1)
                {
                        if (p = get_valid_path(get_z(me), x, y, x1, y1))
                        {
                                cmd = sprintf("%d", p);

                                switch (me->get_walk_step())
                                {
                                case 0:
                                case 1:
                                        if (strlen(cmd) > 1)
                                                cmd = cmd[0..0];
                                        break;
                                case 2:
                                        if (strlen(cmd) > 2)
                                                cmd = cmd[0..1];
                                        break;
                                default:
                                        break;
                                }
                                GO_CMD->main_npc(me, cmd);
                        }
                }
        }

        x = abs(x - get_x(me));
        y = abs(y - get_y(me));
        walk = (x > y) ? x : y;

        if (walk > 0)
        {
                set_heart_state(me, WALK_STAT);
                set_heart_count_2(me, me->get_walk_speed() * walk); // walk * 10 / 4
                                                                    //                if (owner) tell_user(owner, "时间 %d 步数 %d 间隔 %d 步速 %d", get_heart_timer(me), walk, get_heart_count_2(me), me->get_walk_speed() );
        }
}