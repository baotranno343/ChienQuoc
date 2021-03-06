
#include <ansi.h>
#include <map.h>
#include <skill.h>
#include <action.h>
#include <equip.h>
#include <cmd.h>
#include <effect.h>
#include <item.h>
inherit "/inh/std/virtual";

private
static object Owner; // 用户标识(备注：记录主人，主人不在时清除此场景)
int iForbbit = 0;    // 戒严标志

// -------------------------------------------------------------
int noFight = 0;
// 函数：获取地型类别
int get_map_type() { return CAVE_MAP; }
int get_no_fight() { return noFight; }
int set_no_fight(int num) { return noFight = num; }
// 函数：虚拟场景识别
int is_virtual_scene() { return 2; }
int is_ken_map2() { return 1; }
// 戒严标志处理
int set_forbbit(int flag) { return iForbbit = flag; }
int get_forbbit() { return iForbbit; }

// 函数：构造处理
void create()
{
        object me = this_object();

        set_client_id(891);
        set_name("Thi Đấu CQMC");

        if (!clonep(me))
                return;

        set_heart_timer(me, set_heart_timer_2(me, getoid(me) % 10)); // 心跳随机
        set_heart_loop(me, 300);                                     // 循环心跳：１分钟
        me->heart_beat();
        set_heart_beat(1);
}

// -------------------------------------------------------------

// 函数：获取用户标识
object get_owner() { return Owner; }

// 函数：设置用户标识
object set_owner(object who) { return Owner = who; }

// -------------------------------------------------------------

// 函数：心跳处理
void heart_beat() {}

// 函数：心跳处理(循环)
void heart_beat_loop(int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) { __FILE__->heart_beat_loop_callout(this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout(object map, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) // 每１分处理
{
        object who, *member;

        int i;
        member = map->get_users(map);
        //  CHAT_D->vip_channel(1, sprintf(CHAT " %s : %s ", "test1", "test1"));
        // 没有玩家，删除

        if (sizeof(member) < 2 || map->get("finish")) // 没有玩家，删除
        {
                map->destruct_virtual_map(map, map->get_id());
        }
}

// -------------------------------------------------------------

void cleanup_badman(object map)
{
        object *npc, *all, who;
        int z, x, y, p, max_x, max_y;
        int i, size;

        reset_eval_cost();
        z = map->get_id();
        max_x = get_map_max_x(z);
        max_y = get_map_max_y(z);
        all = ({});
        for (x = 0; x < max_x; x += AREA_SIZE)
                for (y = 0; y < max_y; y += AREA_SIZE)
                {
                        if (have_scene_object(z, x, y, CHAR_TYPE, 1))
                        {
                                npc = get_scene_object(z, x, y, USER_TYPE, 1);
                                all += npc;
                        }
                }
        for (i = 0, size = sizeof(all); i < size; i++)
                if (who = all[i])
                {
                        who->remove_from_scene();
                        destruct(who);
                }
}

object *get_users(object map)
{
        object *player, *all;
        int z, x, y, p, max_x, max_y;
        int i, size;

        reset_eval_cost();
        z = map->get_id();
        max_x = get_map_max_x(z);
        max_y = get_map_max_y(z);
        all = ({});
        for (x = 0; x < max_x; x += AREA_SIZE)
                for (y = 0; y < max_y; y += AREA_SIZE)
                {
                        if (have_scene_object(z, x, y, USER_TYPE, 1))
                        {
                                player = get_scene_object(z, x, y, USER_TYPE, 1);
                                all += player;
                        }
                }
        return all;
}

// 函数：清除所有物体
void cleanup_char_and_item(object map)
{
        object *item, who, npc;
        int z, x, y, p, max_x, max_y;
        int i, size;

        reset_eval_cost();

        z = map->get_id();
        max_x = get_map_max_x(z);
        max_y = get_map_max_y(z);

        for (x = 0; x < max_x; x += AREA_SIZE)
                for (y = 0; y < max_y; y += AREA_SIZE)
                {
                        if (have_scene_object(z, x, y, ITEM_TYPE, 1))
                        {
                                item = get_scene_object(z, x, y, ITEM_TYPE, 1);

                                for (i = 0, size = sizeof(item); i < size; i++)
                                        if (who = item[i])
                                        {
                                                who->remove_from_scene();
                                                destruct(who);
                                        }
                        }
                        if (have_scene_object(z, x, y, CHAR_TYPE, 1))
                        {
                                item = get_scene_object(z, x, y, CHAR_TYPE, 1);

                                for (i = 0, size = sizeof(item); i < size; i++)
                                        if (who = item[i])
                                        {
                                                who->remove_from_scene();
                                                destruct(who);
                                        }
                        }
                        if (have_scene_object(z, x, y, USER_TYPE, 1))
                        {
                                item = get_scene_object(z, x, y, USER_TYPE, 1);

                                for (i = 0, size = sizeof(item); i < size; i++)
                                        if (who = item[i])
                                                MAP_D->add_to_void(who); // 移入 VOID 场景
                        }
                }
}

// 函数：删除虚拟场景
void destruct_virtual_map(object map, int id)
{
        if (!map->is_virtual_scene())
                return;

        cleanup_char_and_item(map);
        free_virtual_map(id);
        destruct(map);
}

// 在切磋的死亡callout处理
void begin_fight_die()
{
        call_out("message1", 2);
}

void message1()
{
        remove_call_out("message1");
        if (!Owner)
                return;
        send_user(Owner, "%c%s", '!', "Không cần dễ dàng buông tha, ta sẽ không làm khó ngươi!");
        send_user(get_scene_object_2(Owner, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(Owner),
                  51141, 1, OVER_BODY, 51142, 1, OVER_BODY, 51143, 1, UNDER_FOOT, 51144, 1, UNDER_FOOT, PF_ONCE);
        call_out("message2", 2);
}

void message2()
{
        remove_call_out("message1");
        remove_call_out("message2");
        if (!Owner)
                return;
        send_user(Owner, "%c%s", '!', "Ngươi lại một lần nữa đứng lên!");
        Owner->set_die(0);
        Owner->set_hp(Owner->get_max_hp());
        Owner->set_mp(Owner->get_max_mp());
}
// void die(object who)
// {
//         who->add_to_scene(80, 325, 120, 3);
// }
void awaitText(object map, int stt)
{
        object *mem;
        int i;
        mem = map->get_users(map);
        if (sizeof(mem) < 2)
        {
                remove_call_out("awaitText");
                map->destruct_virtual_map(map, map->get_id());
        }
        for (i = 0; i < sizeof(mem); i++)
        {
                if (stt == 1)
                {
                        send_user(mem[i], "%c%c%s", 0xA5, 1, "Đã Vào Bản Đồ Tỷ Thý");
                }
                if (stt == 2)
                {
                        send_user(mem[i], "%c%c%s", 0xA5, 1, "Bắt Đầu Đánh Sau 3 Giây");
                }
                if (stt == 3)
                {
                        send_user(mem[i], "%c%c%s", 0xA5, 1, "3");
                }
                if (stt == 4)
                {
                        send_user(mem[i], "%c%c%s", 0xA5, 1, "2");
                }
                if (stt == 5)
                {
                        send_user(mem[i], "%c%c%s", 0xA5, 1, "1");
                }
                if (stt == 6)
                {
                        send_user(mem[i], "%c%c%s", 0xA5, 1, "Bắt Đầu");
                        map->set_no_fight(0);
                }
        }
        if (stt != 6)
                call_out("awaitText", 2, map, (stt + 1));
        else
        {
                remove_call_out("awaitText");
        }
        return;
}