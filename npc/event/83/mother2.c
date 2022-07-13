
#include <npc.h>
#include <ansi.h>
#include <cmd.h>
#include <effect.h>

inherit SLAVE;

private
static object Owner; // 用户标识

// 函数：获取用户标识
object get_owner() { return Owner; }

// 函数：设置用户标识
object set_owner(object who) { return Owner = who; }

void do_push(string arg);

void follow_owner(object me);
int get_char_picid() { return 0450; }
// 函数：构造处理
void create()
{
        object me = this_object();

        set_name(HIY "Mẹ");
        set_walk_speed(1);
        set_max_seek(12);
        set_walk_step(2);
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
        if (this_object()->get("mother2") != who->get_number())
                return 0;
        if (TASK_LEGEND_D->check_task_item_amount(who, this_object()->get("thucan")) < 1)
                return 0;
        TASK_LEGEND_D->check_task_item1(who, this_object()->get("thucan"), 1);
        who->add_save("diemhieuthao", 1);
        who->add_potential(5 + random(5));
        who->add_exp(500 + random(1000));
        write_user(who, "Bạn tặng hoa cho mẹ, nhận được " HIY "1 điểm Hiếu Thảo.");
        this_object()->remove_from_scene();
        destruct(this_object());
        return 0;
}

// -------------------------------------------------------------

// 函数：对话处理
void do_look(object who)
{
        if (this_object()->get("mother2") != who->get_number())
                return 0;
}

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
        p = me->add_heart_sec(1);

        if (p % 1 == 0)
        {
                if (p % 2 == 0)
                {
                        z = get_z(me);
                        x = get_x(me);
                        y = get_y(me);

                        char = get_range_object(z, x, y, 10, CHAR_TYPE);
                        if (objectp(owner = me->get_owner()))
                                SAY_CMD->say(me, sprintf("%s, hôm nay con biết ngày gì chứ? Mẹ thích %s quá #25", owner->get_name(), me->get("thucan")));
                }

                if (gone_time(me->get("birthday")) >= 300)
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

void heart_beat_walk()
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
                set_heart_count_2(me, me->get_walk_speed() * walk);
        }
}