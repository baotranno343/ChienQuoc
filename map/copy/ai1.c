inherit COPY_MAP;
//副本场景
#include <ansi.h>
#include <map.h>
#include <skill.h>
#include <action.h>
#include <equip.h>
#include <cmd.h>

inherit "/inh/std/virtual";

private
static object Owner; // 用户标识(备注：记录主人，主人不在时清除此场景)
private
object *nNpc = ({}); //副本的怪
int is_ken_map() { return 1; }
int is_copy_scene() { return 1; }
// 函数：构造处理
void create()
{
        object me = this_object();

        set_client_id(896);
        set_name("Chiến Quốc Trận");

        if (!clonep(me))
                return;

        set_heart_timer(me, set_heart_timer_2(me, getoid(me) % 10)); // 心跳随机
        set_heart_loop(me, 300);                                     // 循环心跳：１分钟
        me->heart_beat();
        set_heart_beat(1);
} // 函数：心跳处理
void heart_beat() {}

// 函数：心跳处理(循环)
void heart_beat_loop(int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) { __FILE__->heart_beat_loop_callout(this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout(object map, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) // 每１分处理
{
        object who, *member;

        int i;
        member = "map/copy/ai1"->get_all_user(map);

        if (sizeof(member) == 0) // 没有玩家，删除
        {
                "map/copy/ai1"->destruct_virtual_map(map, map->get_id());
        }
}

// -------------------------------------------------------------

// 函数：清除所有物体
void cleanup_char_and_item(object map)
{
        object *item, who, npc, *nObj;
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
        //删除副本的其余怪
        nObj = map->get_copy_npc();
        for (i = 0, size = sizeof(nObj); i < size; i++)
        {
                if (!objectp(who = nObj[i]))
                        continue;
                who->remove_from_scene();
                destruct(who);
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

// 函数：取地图内的所有玩家
object *get_all_user(object map)
{
        object *item, who, *npc = ({}), *all = ({});
        int z, x, y, p, max_x, max_y;
        int i, size;

        reset_eval_cost();

        z = map->get_id();
        max_x = get_map_max_x(z);
        max_y = get_map_max_y(z);

        for (x = 0; x < max_x; x += AREA_SIZE)
                for (y = 0; y < max_y; y += AREA_SIZE)
                {
                        if (have_scene_object(z, x, y, USER_TYPE, 1))
                        {
                                item = get_scene_object(z, x, y, USER_TYPE, 1);

                                for (i = 0, size = sizeof(item); i < size; i++)
                                        if (who = item[i])
                                        {
                                                all += ({item[i]});
                                        }
                        }
                }
        for (i = 0; i < sizeof(all); i++)
        {
                if (all[i]->is_user())
                        npc += ({all[i]});
        }
        return npc;
}
void die(object who)
{

        who->add_to_scene(80, 325, 120, 3);
}
void check_outmap(int sec, object who)
{
        sec = sec - 5;
        if (who)
        {
                if (who->get_team() || !get_map_object(get_z(who))->is_ken_map())
                {
                        remove_call_out("check_outmap");
                }
                else
                {
                        if (sec > 0)
                        {
                                tell_user(who, "Sau %d giây tự động rời khỏi nếu không gia nhập lại tổ đội", sec);
                                call_out("check_outmap", 5, sec, who);
                        }
                        else
                        {
                                if (sizeof(who->get_team()) < 1)
                                {
                                        MAP_D->add_to_void(who);
                                }
                        }
                }
        }
}