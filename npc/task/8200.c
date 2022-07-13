
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit NPC;

// 函数：被剿Thổ Phỉ
int is_banditi() { return 1; }

// 函数：是否不能进城
int cannot_enter_city() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Thổ Phỉ" + NPC_NAME_D->get_banditi_name());
        set_char_picid(0251); // Thổ Phỉ

        switch (random(5))
        {
        default:
                set_weapon_code(UNARMED);
                break;
        case 1:
                set_weapon_code(BLADE);
                break;
        case 2:
                set_weapon_code(SWORD);
                break;
        case 3:
                set_weapon_code(SPEAR);
                break;
        case 4:
                set_weapon_code(STICK);
                break;
        }
        set_walk_speed(4);
        set_attack_speed(15);

        set_max_seek(4);
        setup();

        set("birthday", time());
}

// 函数：复位处理
void reset()
{
        object who;
        string *member, id;
        int i, size;

        if (gone_time(get("birthday")) >= 1800) // 30 分钟
        {
                remove_from_scene();
                destruct(this_object());
        }
        else
        {
                member = get("user");
                id = sprintf("%x#", getoid(this_object()));
                //   for (i = 0, size = sizeof(member); i < size; i++)
                if (!(who = find_player(sprintf("%d", member))) || who->get_task("banditi") != id)
                {
                        remove_from_scene();
                        destruct(this_object());
                }
                else
                        set("user", member);
        }
}

// 函数：可以接受战斗
int can_be_fighted(object who)
{
        object owner;
        string leader, id;

        if (who->get_enemy() == this_object())
                return 1;

        if (owner = who->get_owner())
                who = owner;
        if (who->is_npc())
                return 0;

        if (stringp(id = who->get_task("banditi")) && id == sprintf("%x#", getoid(this_object())))
                return 1;

        send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Cút ngay! Không thấy lão tử à !");
        return 0;
}

// --------------------------------------------------------------- 远程调用 ----

// 函数：死亡奖励
void win_bonus(object who) { __FILE__->win_bonus_callout(this_object(), who); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout(object me, object who)
{
        object owner, *team, *team2, map;
        string id, id2, name;
        int level, level2, exp, exp2, pot, pot2, time, x, y, z;
        int i, size;

        if (!me->can_be_fighted(who))
                return;

        if (owner = who->get_owner())
                who = owner;
        if (who->is_npc())
                return;

        // team = who->get_team();
        // if (sizeof(team) == 0)
        //         team = ({who});
        // team = me->correct_bonus_team1(team, 20);
        // if ((size = sizeof(team)) < 1)
        //         return;

        id = sprintf("%x#", getoid(me));

        // for (i = 0, team2 = ({}); i < size; i++)
        // {
        //         if (team[i] && stringp(id2 = team[i]->get_task("banditi")) && id == id2)
        //                 team2 += ({team[i]});
        // }

        // if ((size = sizeof(team = team2)) < 1)
        //         return;

        level = me->get_level();

        z = me->get("xy.z");
        x = me->get("xy.x");
        y = me->get("xy.y");

        map = get_map_object(get_z(me));
        name = map ? map->get_name() : "无名地图";

        send_user(who, "%c%w", 0x0d, MUSIC_TASK);
        write_user(who, ECHO "Nhiệm vụ hoàn thành, tìm vệ đội trưởng.");
        who->delete_task("banditi");
        who->delete_task("banditi_time");
        who->set_task("banditi_bonus", level); //找卫队长领奖
        who->set_task("banditi_map", name);
        who->set_task("banditi_name", me->get_name());
        who->set_task("banditi_x", x);
        who->set_task("banditi_y", y);

        TASK_BANDITI_D->clear_task_desc(who);
        TASK_BANDITI_D->send_task_list(who);

        if ((level2 = who->get_level()) >= 8 && level2 < 10 && !who->get_legend(TASK_NEWBIE_00, 20))
        {
                who->set_legend(TASK_NEWBIE_00, 20);
                USER_TASK_D->auto_give_task(who);
        }
}
