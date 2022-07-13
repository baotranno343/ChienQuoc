
// 飞行技能  TIPS:[PF_FLY]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <map.h>

#define THIS_SKILL 0418
#define THIS_PERFORM 04182
#define PF_START "04182"
#define PF_NAME "Xuyên Không Thành"

#define SKILL_LEVEL 16
#define SUB_MP 30

// 函数:获取符法效果
int get_cast_seal() { return 9103; } // 符纸逆旋

// 函数:获取描述
string get_desc(object me)
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level < SKILL_LEVEL)
                return HIR + PF_NAME + "\n Võ công yêu cầu: 16 cấp\n Vật phẩm tiêu hao: 1 Bùa Giấy\n    Lập tức di chuyển đến vị trí đã định vị.";
        result = sprintf(HIC " %s \n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Vật phẩm tiêu hao: 1 Bùa Giấy\n    Lập tức di chuyển đến vị trí đã định vị.",
                         PF_NAME, SKILL_LEVEL, SUB_MP);
        return result;
}

// 函数:命令处理
int main(object me, object who, int x, int y, string arg)
{
        object *user, map, item, item1;
        string result, fly;
        int p, z, i, size, *pos;
        int level, mp;

        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        if (me->get_perform(PF_START) == time())
                return 1;

        if (objectp(item1 = present("Cờ Hiệu Vô Song Thành", me, 1, MAX_CARRY * 4)))
        {
                notify("Mang theo Cờ Hiệu không thể sử dụng");
                return 1;
        }
        if (me->get_mp() < (mp = SUB_MP)) // 小心准备 level
        {
                printf(ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp);
                return 1;
        }

        if (!objectp(item = present("Bùa Giấy", me, 1, MAX_CARRY * 4)))
        {
                printf(ECHO "Phải có Bùa Giấy mới có thể sử dụng \"" PF_NAME "\".");
                return 1;
        }

        if (sscanf(arg, "%d", p))
        {
                fly = me->get_fly(sprintf("%d", p));
                if (!stringp(fly) || sscanf(fly, "%d,%d,%d", z, x, y) != 3)
                {
                        printf(ECHO "Bạn tới %d xuyên không hành thất bại", p);
                        return 1;
                }
                if (me->get_save_2("51cuanye.time"))
                {
                        printf(ECHO "接受极限穿越任务后不能使用\"" PF_NAME "\".");
                        return 1;
                }
                if (me->get_save("cambayquest"))
                {
                        //  send_user(me, "%c%s", '!', "Đối phương không thể sử dụng khi đang mang trong mình nhiệm vụ.");
                        printf(ECHO "Ngươi không thể sử dụng khi đang mang trong mình nhiệm vụ.\"" PF_NAME "\".");
                        return 1;
                }
                if (present("钱票", me, 1, MAX_CARRY))
                {
                        printf(ECHO "带着钱票不能使用\"" PF_NAME "\".");
                        return 1;
                }
                if (present("Vật Phẩm Quý Bấu", me, 1, MAX_CARRY))
                {
                        printf(ECHO "Mang theo Vật Phẩm Quý Bấu không thể sử dụng \"" PF_NAME "\".");
                        return 1;
                }
                if (MAP_D->is_inside_city(get_z(me), get_x(me), get_y(me)))

                {
                        printf(ECHO "Không thể sử dụng khi đang ở trong thành");
                        // notify("Không thể sử dụng khi đang ở trong thành");
                        return 1;
                }
                if (objectp(who = me->get_quest("escort.robber#")) && who->is_escort_robber()) // 寻找蒙面人
                {
                        printf(ECHO "Người bịt mặt xuất hiện, hành động của bạn bị ảnh hưởng");
                        return 1;
                }
                if (MAP_D->is_inside_city(z, x, y))
                {
                        printf(ECHO "Không thể sử dụng \"" PF_NAME "\" vào bên trong thành");
                        return 1;
                }
                if (get_z(me) == 704)
                {
                        notify("Trong Nhà Ngục không thể sử dụng");
                        return 1;
                }
                if (objectp(map = get_map_object(z)))
                {
                        switch (map->get_map_type())
                        {
                        case CAVE_MAP:
                                printf(ECHO "Nơi này không thể sử dụng \"" PF_NAME "\".");
                                return 1;
                        case BATTLE_MAP:
                                printf(ECHO "Chiến Trường không thể sử dụng \"" PF_NAME "\".");
                                return 1;
                        }
                }
                send_user(me, "%c%w%c%w", 0x50, 0, 0xff, 2); // 所有出招２秒后能使用
                me->set_time("pf", time());

                user = get_scene_object_2(me, USER_TYPE);
                send_user(user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN);
                send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP);

                me->add_mp(-mp);
                item->add_amount(-1);

                set_heart_state(me, MAGIC_STAT);
                set_heart_count_2(me, 5);
                me->add_2("go_count.count2", 5);
                me->set_cast_file(__FILE__);
                me->set_cast_arg(sprintf("%d,%d,%d,%d", level, z, x, y));
        }
        else
        {
                pos = ({});
                for (i = 0; i < MAX_POSITION; i++)
                {
                        fly = me->get_fly(sprintf("%d", i + 1));
                        if (fly == 0 || sscanf(fly, "%d,%d,%d", z, x, y) != 3)
                        {
                                z = 0;
                                x = 0;
                                y = 0;
                        }
                        pos += ({z});
                        pos += ({x});
                        pos += ({y});
                }
                send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w", 0x89, THIS_PERFORM,
                          pos[0], pos[1], pos[2], pos[3], pos[4], pos[5], pos[6], pos[7], pos[8],
                          pos[9], pos[10], pos[11], pos[12], pos[13], pos[14], pos[15], pos[16], pos[17],
                          pos[18], pos[19], pos[20], pos[21], pos[22], pos[23], pos[24], pos[25], pos[26],
                          pos[27], pos[28], pos[29], pos[30], pos[31], pos[32], pos[33], pos[34], pos[35],
                          pos[36], pos[37], pos[38], pos[39], pos[40], pos[41], pos[42], pos[43], pos[44],
                          pos[45], pos[46], pos[47]);
        }

        return 1;
}

// 函数:法术处理
int cast_done(object me)
{
        object map;
        string arg, name;
        int z, x, y, p;
        int level;

        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());

        if (!stringp(arg = me->get_cast_arg()) || sscanf(arg, "%d,%d,%d,%d", level, z, x, y) != 4)
                return 1;

        if (me->is_die())
                return 1;

        if (!(p = get_valid_xy(z, x, y, IS_CHAR_BLOCK)))
        {
                write_user(me, ECHO "Không thể đi!"); // 提示旧坐标
                return 1;
        }

        {
                x = p / 1000;
                y = p % 1000;
                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 0, 1, OVER_BODY, PF_ONCE);

                me->set_login_flag(2); // 跳转保护
                set_invisible(me, 1);
                set_effect(me, EFFECT_USER_LOGIN, 4);

                me->add_to_scene(z, x, y, get_d(me), 41821, 41822, 41821, 41822);

                if (objectp(map = get_map_object(z)))
                        name = map->get_name();
                else
                        name = "Chưa Xác Lập Vị Trí";

                send_user(me, "%c%s", '!', sprintf("Bạn thành công tới" HIY " %s(%d,%d) " NOR ".", name, x, y));
        }

        return 2; // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_ME; }

// 函数:能否使用特技
void can_perform(object me)
{
        if (me->get_skill(THIS_SKILL) < SKILL_LEVEL)
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME);
        else
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME);
        send_user(me, "%c%w%w%c%c%c%c%c%s", 0x64, THIS_PERFORM, SUB_MP, 0, 1, MAGIC_ACT_BEGIN, 0, 5, "Bùa Giấy");
}
