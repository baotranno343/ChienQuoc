
#include <npc.h>

private
mapping mpSoldier = ([]);
private
mapping mpZombie = ([]);
private
mapping mpTime = ([]);

void check_slave();

void insert_soldier(object npc);
void insert_zombie(object npc);

// 函数：生成二进制码
void SAVE_BINARY() {}

// 函数：构造处理
void create()
{
        object *npc;
        int i, size;

        call_out("check_slave", 10);

        npc = filter_array(livings(), (
                                          : clonep($1) && $1->is_zombie() && !objectp($1->get_owner()) && $1->get_zombie_type() <= $2:),
                           SOLDIER_TYPE_3);
        for (i = 0, size = sizeof(npc); i < size; i++)
                if (npc[i])
                        insert_soldier(npc[i]);

        npc = filter_array(livings(), (
                                          : clonep($1) && $1->is_zombie() && !objectp($1->get_owner()) && $1->get_zombie_type() >= $2:),
                           ZOMBIE_TYPE_1);
        for (i = 0, size = sizeof(npc); i < size; i++)
                if (npc[i])
                        insert_zombie(npc[i]);
}

// -------------------------------------------------------------

// 函数：检查召唤兽
void check_slave()
{
        object *zombie;
        string *id;
        int i, j, size, size2;

        remove_call_out("check_slave");
        call_out("check_slave", 5);

        reset_eval_cost();

        if ((size = sizeof(mpTime)) < 1)
                return;

        id = keys(mpTime);
        for (i = 0; i < size; i++)
                if (gone_time(mpTime[id[i]]) > 300) // 召唤兽保留１分钟
                {
                        if (!undefinedp(mpSoldier[id[i]]) && objectp(mpSoldier[id[i]]) && mpSoldier[id[i]]->is_zombie())
                        {
                                mpSoldier[id[i]]->remove_from_scene();
                                destruct(mpSoldier[id[i]]);
                        }
                        map_delete(mpSoldier, id[i]);

                        if (!undefinedp(mpZombie[id[i]]) && arrayp(mpZombie[id[i]]))
                        {
                                zombie = mpZombie[id[i]] - ({0});
                                for (j = 0, size2 = sizeof(zombie); j < size2; j++)
                                        if (zombie[j])
                                        {
                                                zombie[j]->remove_from_scene();
                                                destruct(zombie[j]);
                                        }
                        }
                        map_delete(mpZombie, id[i]);

                        map_delete(mpTime, id[i]);
                }
}

// 函数：获取天兵数组
mapping get_soldier_dbase() { return copy(mpSoldier); }

// 函数：获取僵尸数组
mapping get_zombie_dbase() { return copy(mpZombie); }

// 函数：获取时间数组
mapping get_time_dbase() { return copy(mpTime); }

// 函数：增加天兵
void insert_soldier(object npc)
{
        string id;
        int number;

        if ((number = npc->get_owner_number()) > 0)
        {
                id = sprintf("%d", number);
                npc->set_action(0);
                mpSoldier[id] = npc;
                mpTime[id] = time();
        }
}

// 函数：增加僵尸
void insert_zombie(object npc)
{
        string id;
        int number;

        if ((number = npc->get_owner_number()) > 0)
        {
                id = sprintf("%d", number);

                npc->set_action(0);
                if (undefinedp(mpZombie[id]) || !arrayp(mpZombie[id]))
                        mpZombie[id] = ({npc});
                else
                        mpZombie[id] = mpZombie[id] + ({npc}) - ({0});

                mpTime[id] = time();
        }
}

// 函数：设置僵尸(所有)
void set_all_zombie(int number, object *npc)
{
        string id = sprintf("%d", number);

        if (number > 0 && arrayp(npc))
        {
                if (sizeof(npc = npc - ({0})))
                {
                        npc->set_action(0);
                        mpZombie[id] = npc;
                        mpTime[id] = time();
                }
        }
}

// 函数：记录所有召唤兽
void save_all_slave(object owner)
{
        object npc, *zombie;
        int i, size;
        if (objectp(npc = owner->get("soldier")))
                insert_soldier(npc);
        if (arrayp(zombie = owner->get("zombie")))
        {
                size = sizeof(zombie);
                if (size > 0)
                {
                        for (i = 0; i < size; i++)
                        {
                                if (objectp(zombie[i]))
                                {
                                        zombie[i]->remove_from_scene();
                                        destruct(zombie[i]);
                                }
                        }
                }
                owner->set("zombie", 0);
        }
        if (arrayp(zombie = owner->get("zombie2")))
        {
                size = sizeof(zombie);
                if (size > 0)
                {
                        for (i = 0; i < size; i++)
                        {
                                if (objectp(zombie[i]))
                                {
                                        zombie[i]->remove_from_scene();
                                        destruct(zombie[i]);
                                }
                        }
                }
                owner->set("zombie2", 0);
        }
}

// 函数：取回所有召唤兽
void restore_all_slave(object owner)
{
        object *zombie;
        string id;
        int i, size;

        id = sprintf("%d", owner->get_number());

        if (!undefinedp(mpTime[id]))
        {
                if (gone_time(mpTime[id]) > 300) // 召唤兽保留１分钟
                {
                        if (!undefinedp(mpSoldier[id]) && objectp(mpSoldier[id]) && mpSoldier[id]->is_zombie())
                        {
                                mpSoldier[id]->remove_from_scene();
                                destruct(mpSoldier[id]);
                        }
                        map_delete(mpSoldier, id);

                        if (!undefinedp(mpZombie[id]) && arrayp(mpZombie[id]))
                        {
                                zombie = mpZombie[id] - ({0});
                                for (i = 0, size = sizeof(zombie); i < size; i++)
                                        if (zombie[i])
                                        {
                                                zombie[i]->remove_from_scene();
                                                destruct(zombie[i]);
                                        }
                        }
                        map_delete(mpZombie, id);

                        map_delete(mpTime, id);
                }
                else
                {
                        if (!undefinedp(mpSoldier[id]) && objectp(mpSoldier[id]) && mpSoldier[id]->is_zombie())
                        {
                                mpSoldier[id]->set_owner(owner);
                                mpSoldier[id]->set_action(1);
                                mpSoldier[id]->set_action_mode(2);
                                owner->set("soldier", mpSoldier[id]);
                                send_user(owner, "%c%c%d%s", 0x2c, 1, getoid(mpSoldier[id]), mpSoldier[id]->get_name());
                                send_user(owner, "%c%c%d%w%w%w", 0x2c, 2, getoid(mpSoldier[id]), 1, 2, 3);
                                send_user(owner, "%c%c%d%c", 0x2c, 3, getoid(mpSoldier[id]), mpSoldier[id]->get_hp() * 50 / mpSoldier[id]->get_max_hp());
                                send_user(owner, "%c%c%d%c", 0x2c, 4, getoid(mpSoldier[id]), mpSoldier[id]->get_mp() * 50 / (mpSoldier[id]->get_max_mp() + 1));
                                send_user(owner, "%c%c%d%c", 0x2c, 5, getoid(mpSoldier[id]), 2);
                                send_user(owner, "%c%c%d%c", 0x2c, 6, getoid(mpSoldier[id]), mpSoldier[id]->get_action_mode());
                                send_user(owner, "%c%c%d%w%w", 0x2c, 7, getoid(mpSoldier[id]), get_x(mpSoldier[id]), get_y(mpSoldier[id]));
                                send_user(owner, "%c%c%d%d", 0x2c, 8, getoid(mpSoldier[id]), mpSoldier[id]->get_char_picid());
                        }
                        map_delete(mpSoldier, id);

                        if (!undefinedp(mpZombie[id]) && arrayp(mpZombie[id]))
                        {
                                zombie = mpZombie[id] - ({0});
                                for (i = 0, size = sizeof(zombie); i < size; i++)
                                        if (zombie[i])
                                        {
                                                zombie[i]->set_owner(owner);
                                                zombie[i]->set_action(1);
                                                zombie[i]->set_action_mode(1);
                                                send_user(owner, "%c%c%d%s", 0x2c, 1, getoid(zombie[i]), zombie[i]->get_name());
                                                send_user(owner, "%c%c%d%w%w%w", 0x2c, 2, getoid(zombie[i]), 1, 2, 3);
                                                send_user(owner, "%c%c%d%c", 0x2c, 3, getoid(zombie[i]), zombie[i]->get_hp() * 50 / zombie[i]->get_max_hp());
                                                send_user(owner, "%c%c%d%c", 0x2c, 4, getoid(zombie[i]), zombie[i]->get_mp() * 50 / (zombie[i]->get_max_mp() + 1));
                                                send_user(owner, "%c%c%d%c", 0x2c, 5, getoid(zombie[i]), 2);
                                                send_user(owner, "%c%c%d%c", 0x2c, 6, getoid(zombie[i]), zombie[i]->get_action_mode());
                                                send_user(owner, "%c%c%d%w%w", 0x2c, 7, getoid(zombie[i]), get_x(zombie[i]), get_y(zombie[i]));
                                                send_user(owner, "%c%c%d%d", 0x2c, 8, getoid(zombie[i]), zombie[i]->get_char_picid());
                                        }
                                //                              zombie->set_owner(owner);
                                //                              zombie->set_action(1);
                                owner->set("zombie", zombie);
                        }
                        map_delete(mpZombie, id);

                        map_delete(mpTime, id);
                }
        }
}
