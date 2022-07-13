
#include <npc.h>

inherit ITEM;
inherit LEGEND_ITEM;
#define ROBBER_1 "/npc/task/8101"
#define ROBBER_2 "/npc/task/8102"
#define ROBBER_3 "/npc/task/8103"
#define ROBBER_4 "/npc/task/8104"

private
static object Owner; // 用户标识

// 函数：获取用户标识
object get_owner() { return Owner; }

// 函数：设置用户标识
object set_owner(object who) { return Owner = who; }

// -------------------------------------------------------------

// 函数：构造处理
void create()
{
        object item = this_object();

        set_name("Vật Phẩm Quý Bấu");
        set_picid_1(0001);
        set_picid_2(0001);
        set_unit("件");
        set_value(0);

        //      set_no_drop(1);
        set_no_get(1);
        set_no_give(1);
        set_no_sell(1);

        set("birthday", time());

        if (!clonep(item))
                return;

        set_heart_timer(item, set_heart_timer_2(item, getoid(item) % 10)); // 心跳随机
        set_heart_loop(item, 100);                                         // 循环心跳：１０秒钟
        item->heart_beat();
        set_heart_beat(1);
}

// 函数：获取描述
string get_desc()
{
        return "Dùng cho nhiệm vụ áp tiêu";
}

// 函数：丢弃确认
string get_drop_confirm()
{
        return "Vứt bỏ thì không thể hoàn thành nhiệm vụ áp tiêu\n";
}

// -------------------------------------------------------------

// 函数：心跳处理
void heart_beat() {}

private
static int Heart = random(180) + 1;
private
static int HeartSec = 0; // 心跳计时

// 函数：获取心跳
int get_heart() { return Heart; }

// 函数：获取心跳计时
int get_heart_sec() { return HeartSec; }

// 函数：设置心跳计时
int set_heart_sec(int point) { return HeartSec = point; }

// 函数：增添心跳计时
int add_heart_sec(int point) { return set_heart_sec(HeartSec + point); }

// 函数：设置心跳
void set_heart_3min()
{
        HeartSec = -(180 - Heart % 180); // ３分钟剩余( 3 * 60 )
        Heart = random(180) + 1;         // 下个３分钟
}

// 函数：心跳处理(循环)
void heart_beat_loop(int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) { __FILE__->heart_beat_loop_callout(this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout(object item, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) // 每１０秒处理
{
        object owner, map, npc;
        int z, x, y, p;

        if (item->add_heart_sec(10) >= item->get_heart())
        {
                if ((owner = environment(item)) && userp(owner)                       // 玩家身上
                    && !owner->is_die()                                               // 玩家非死亡
                    && owner->get_quest("escort.random") < 6                          // 最多次数６
                    && !owner->get_quest("escort.robber#")                            // 还有蒙面人
                    && (z = get_z(owner)) && (x = get_x(owner)) && (y = get_y(owner)) // 有效坐标
                    && !MAP_D->is_inside_city(z, x, y)                                // 不在城内
                    && !get_jumpout(z, x, y))                                         // 非跳转点内
                {
                        if (!(p = get_valid_xy(z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK)))
                                return;

                        x = p / 1000;
                        y = p % 1000;

                        if (!objectp(map = get_map_object(z)) || !map->is_scene())
                                return;

                        p = random(100);

                        if (p < 40)
                                npc = new (ROBBER_1);
                        else if (p < 70)
                                npc = new (ROBBER_2);
                        else if (p < 100)
                                npc = new (ROBBER_3);

                        npc->set_max_seek(4);
                        if (p < 40)
                        {
                                NPC_ENERGY_D->init_level(npc, owner->get_level() - 5);
                                npc->set_walk_speed(5);
                                npc->set_attack_speed(2);
                        }
                        else
                        {
                                npc->set_max_hp(owner->get_max_hp() * 2);
                                npc->set_max_mp(owner->get_max_mp());
                                npc->set_ap(owner->get_dp_0() + 5);
                                npc->set_dp(owner->get_ap_0() + 5);
                                npc->set_cp(owner->get_pp_0() + 5);
                                npc->set_pp(owner->get_cp_0() + 5);
                                npc->set_sp(owner->get_sp());
                                npc->set_walk_speed(WALK_SPEED_1);
                                npc->set_attack_speed(ATTACK_SPEED_2);
                        }

                        npc->set("task", owner->get_number());
                        npc->add_to_scene(z, x, y, get_front_xy(x, y, get_x(owner), get_y(owner)));
                        npc->set_enemy(owner);

                        if (p = owner->get_quest("escort.id"))
                                npc->set("task2", p); // 记录队友ＩＤ

                        map->add_reset(npc); // 加入复位列表

                        owner->add_quest("escort.random", 1); // 记录随机事件
                        owner->set_quest("escort.robber", sprintf("%x#", getoid(npc)));
                        owner->set_quest("escort.robber#", npc);

                        send_user(owner, "%c%s", '!', npc->get_name() + " xuất hiện, hành động của bạn bị ảnh hưởng");
                }
        }
}
