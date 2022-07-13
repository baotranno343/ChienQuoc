
#include <npc.h>
#include <equip.h>

inherit NPC;

// 函数：劫镖强盗
int is_escort_robber() { return 1; }

// 函数：是否不能进城
int cannot_enter_city() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Kiếp Phiêu Cường Đạo");
        set_char_picid(200); // 蒙面人
        set_char_type(FIGHTER_TYPE);

        setup();

        set("birthday", time());
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

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

        send_user(who, "%c%s", '!', get_name() + "Không muốn đánh nhau với ngươi。");
        return 0;
}

// --------------------------------------------------------------- 远程调用 ----

// 函数：死亡奖励
void win_bonus(object who) { __FILE__->win_bonus_callout(this_object(), who); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout(object me, object who)
{
        object owner, item;

        if (objectp(owner = find_player(sprintf("%d", me->get("task")))) && objectp(item = present("Vật Phẩm Quý Bấu", owner, 1, MAX_CARRY)))
                item->set_heart_3min(); // 下个３分钟
}
