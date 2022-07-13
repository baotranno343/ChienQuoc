
inherit NPC;

private
static int Level2 = 0; // 训练等级

private
static int Front; // 战争方面(1: 攻, 2: 守)

private
static int XX, YY; // 旧的坐标

private
static int DistanceX; // 同中线Ｘ距离

// 函数：是否战场战友
int is_comrade() { return 1; }

// -------------------------------------------------------------

// 函数：获取训练等级
int get_level_2() { return Level2; }

// 函数：设置训练等级
int set_level_2(int point) { return Level2 = point; }

// 函数：获取战争方面
int get_front() { return Front; }

// 函数：设置战争方面
int set_front(int flag) { return Front = flag; }

// 函数：获取旧Ｘ坐标
int get_xx() { return XX; }

// 函数：设置旧Ｘ坐标
int set_xx(int point) { return XX = point; }

// 函数：获取旧Ｙ坐标
int get_yy() { return YY; }

// 函数：设置旧Ｙ坐标
int set_yy(int point) { return YY = point; }

// 函数：获取同中线Ｘ距离
int get_distance_x() { return DistanceX; }

// 函数：设置同中线Ｘ距离
int set_distance_x(int point) { return DistanceX = point; }

// -------------------------------------------------------------

// 函数：心跳处理(循环)
void heart_beat_loop(int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) { __FILE__->heart_beat_loop_callout(this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout(object me, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) // 每１秒处理
{
        object map, *char, npc;
        int id, x, y, i, size;

        NPC_EFFECT_D->into_effect(me, effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8); // 征状处理
        if (!me)
                return; // 死亡退出

        if (me->is_send_position())
        {

                if (objectp(map = get_map_object(get_z(me)))) // 获取战场对象
                {

                        x = get_x(me);
                        y = get_y(me);

                        if (abs(x - me->get_xx()) > 1 || abs(y - me->get_yy()) > 1) // 新旧坐标 >1 时重发坐标
                        {

                                me->set_xx(x);
                                me->set_yy(y);
                                npc = me->get_manager();
                                id = getoid(me);

                                if (map->get_manager() == npc) // 攻击方
                                {
                                        char = map->get_user_dbase();
                                        for (i = 0, size = sizeof(char); i < size; i++)
                                                if (objectp(npc = char[i]))
                                                        send_user(npc, "%c%c%d%w%w", 0x54, 22, id, x, y);
                                }
                                else if (map->get_manager_2() == npc) // 防守方
                                {
                                        char = map->get_user_2_dbase();
                                        for (i = 0, size = sizeof(char); i < size; i++)
                                                if (objectp(npc = char[i]))
                                                        send_user(npc, "%c%c%d%w%w", 0x54, 22, id, x, y);
                                }
                        }
                }
        }

        if (me->add_heart_sec(1) % 8 == 0)
                NPC_HEART_D->heart_beat_8sec(me); // 每８秒处理
}

// 函数：走路处理(心跳之中调用)
void heart_beat_walk() { NPC_COMRADE_D->heart_beat_walk(this_object()); }

// 函数：判断可以战斗
int can_fight(object who) { return NPC_COMRADE_D->can_fight(this_object(), who); }

// 函数：可以接受战斗
int can_be_fighted(object who) { return NPC_COMRADE_D->can_be_fighted(this_object(), who); }
