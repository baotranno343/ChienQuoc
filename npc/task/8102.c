
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <cmd.h>

inherit NPC;

// 函数：劫镖强盗
int is_escort_robber() { return 1; }

// 函数：是否不能进城
int cannot_enter_city() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Ác Cái");
        set_char_picid(452); // 蒙面人
        set_char_type(FIGHTER_TYPE);

        setup();

        set("birthday", time());
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：获取当前ＨＰ
int get_hp() { return get_max_hp(); } // 无法杀死

// 函数：设置当前ＨＰ
int set_hp(int point) { return get_max_hp(); }

// 函数：增添当前ＨＰ
int add_hp(int point) { return get_max_hp(); }

// 函数：获取气血比例
int get_hp_cent() { return 50; }

// 函数：复位处理
void reset()
{
        object owner, item;

        if (gone_time(get("birthday")) >= 600) // 10 分钟
        {
                if (objectp(owner = find_player(sprintf("%d", get("task")))) && objectp(item = present("Vật Phẩm Quý Bấu", owner, 1, MAX_CARRY)))
                        item->set_heart_3min(); // 下个３分钟

                remove_from_scene();
                destruct(this_object());
        }
}

// 函数：可以接受战斗
int can_be_fighted(object who)
{
        object owner;
        int id;

        if (who->get_enemy() == this_object())
                return 1;

        if (owner = who->get_owner())
                who = owner;
        if (who->is_npc())
                return 0;

        id = who->get_number();
        if (get("task") == id || get("task2") == id)
                return 1;

        send_user(who, "%c%s", '!', get_name() + "Không muốn đánh nhau với anh.");
        return 0;
}

// --------------------------------------------------------------- 远程调用 ----

// 函数：攻击处理(心跳之中调用)
void heart_beat_attack() { __FILE__->heart_beat_attack_callout(this_object()); }

// 函数：攻击处理(在线更新)
void heart_beat_attack_callout(object me) // 禁止战斗，自动乞讨
{
        object owner;
        int gold;

        if (objectp(owner = find_player(sprintf("%d", me->get("task")))))
        {
                if (distance_between(me, owner) <= 3) // 三格之内
                {
                        if (gone_time(me->get("wordtime")) > 15)
                        {
                                SAY_CMD->say(me, "Người tốt bụng … Hãy thương xót tôi …");
                                me->set("wordtime", time());
                        }
                        if (me->get("begtime") == 0)
                        {
                                me->set("begtime", time());
                        }

                        if (gone_time(me->get("begtime")) >= 3 && random(100) < 20)
                        {
                                me->set("begtime", time());
                                gold = random(5) + 1;

                                if (gold <= owner->get_cash())
                                {
                                        owner->add_cash(-gold);
                                        owner->add_gold_log("pay", gold);
                                        owner->log_money("蒙面人", -gold);
                                        "/sys/sys/count"->add_use("biao", gold);
                                        write_user(owner, ECHO "Bạn thở dài, đưa %d vàng cho %s。", gold, me->get_name());
                                        SAY_CMD->say(me, "Bạn là một người tốt!");
                                        call_out("destruct_npc_callout", 3, me, owner); // 清除蒙面人
                                }
                        }
                }
        }
}

// 函数：死亡奖励
void win_bonus(object who) { __FILE__->win_bonus_callout(this_object(), who); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout(object me, object who) // 玩家死亡调用
{
        object owner, item;

        if (objectp(owner = find_player(sprintf("%d", me->get("task")))) && objectp(item = present("Vật Phẩm Quý Bấu", owner, 1, MAX_CARRY)))
                item->set_heart_3min(); // 下个３分钟
}

// 函数：删除自己(在线更新)
void destruct_npc_callout(object me, object who)
{
        if (!me)
                return;
        me->win_bonus(who); // 清除蒙面人
        me->remove_from_scene();
        destruct(me);
}