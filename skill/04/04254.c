
// 飞行技能  TIPS:[PF_FLY]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <map.h>
#include <city.h>

#define THIS_SKILL 0425
#define THIS_PERFORM 04254
#define PF_START "04254"
#define PF_NAME "Long Du Tứ Hải"

#define SKILL_LEVEL 25
#define TIME_INTERVAL 2
#define SUB_MP 50

// 函数:获取符法效果
// int get_cast_seal() { return 42100; }    // 符纸顺旋

// 函数:获取描述
string get_desc(object me)
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level < SKILL_LEVEL)
                return HIR + PF_NAME + "\n Võ công yêu cầu: 25 cấp\n Vật phẩm tiêu hao: 2 lá Bùa Giấy\n    Có thể lập tức dịch chuyển đến bên người chơi khác theo số ID riêng. Nếu họ đang ở nơi an toàn hay trong động sâu thì không thể dùng pháp thuật này";
        result = sprintf(HIC " %s \n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Vật phẩm tiêu hao: 2 lá Bùa Giấy\n Tái sử dụng sau: %d giây\n    Có thể lập tức dịch chuyển đến bên người chơi khác theo số ID riêng. Nếu họ đang ở nơi an toàn hay trong động sâu thì không thể dùng pháp thuật này",
                         PF_NAME, SKILL_LEVEL, SUB_MP, TIME_INTERVAL);
        return result;
}

// 函数:命令处理
int main(object me, object who, int x, int y, string arg) // 同步更改\"灵犀环\"
{
        object *user, map, item, item1;
        string name;
        int level, mp;

        if (to_int(arg))
                me->set_save("fly", to_int(arg)); // 记录前次飞的人

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
                printf(ECHO "Phải có Bùa Giấy mới sử dụng được \"" PF_NAME "\".");
                return 1;
        }
        if (get_z(me) == 704)
        {
                notify("Trong Nhà Ngục không thể sử dụng");
                return 1;
        }
        if (me->get_save_2("51cuanye.time"))
        {
                printf(ECHO "接受极限穿越任务后不能使用\"" PF_NAME "\".");
                return 1;
        }
        if (me->get_save("cambayquest"))
        {
                notify("Ngươi phương không thể sử dụng khi đang mang trong mình nhiệm vụ.");
                //   send_user(me, "%c%s", '!', "Đối phương không thể sử dụng khi đang mang trong mình nhiệm vụ.");
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
        if (present("Ngân Phiếu", me, 1, MAX_CARRY))
        {
                printf(ECHO "Mang theo Ngân Phiếu không thể sử dụng \"" PF_NAME "\".");
                return 1;
        }
        if (objectp(who = me->get_quest("escort.robber#")) && who->is_escort_robber()) // 寻找蒙面人
        {
                printf(ECHO "蒙面人出现，您的行动受到影响.");
                return 1;
        }
        if (MAP_D->is_inside_city(get_z(me), get_x(me), get_y(me)))

        {
                notify("Không thể sử dụng khi đang ở trong thành");
                return 1;
        }
        if (!arg || arg == "")
        {
                send_user(me, "%c%c%d%d%s", '?', 3, 0, me->get_save("fly"), "Bạn muốn bay đến người nào? Xin hãy điền số ID:\n" ESC "pf 4254.%s\n");
                return 1;
        }
        else if (arg == "0")
        {
                notify("Nhân vật không tồn tại.");
                return 1;
        }
        else
        {
                if (!objectp(who = find_player(arg)))
                {
                        notify("Không tìm thấy người này.");
                        return 1;
                }
                if (who->get_no_fly())
                {
                        printf(ECHO "Đối phương đã thiết lập cấm bay");
                        return 1;
                }
                if (who->get_save("cambayquest"))
                {
                        printf(ECHO "Đối phương không thể sử dụng khi đang mang trong mình nhiệm vụ.");
                        //   send_user(me, "%c%s", '!', "Đối phương không thể sử dụng khi đang mang trong mình nhiệm vụ.");
                        return 1;
                }
                if (MAP_D->is_inside_city(get_z(who), get_x(who), get_y(who)))
                {
                        printf(ECHO "Đối phương ở trong thành, không thể sử dụng \"" PF_NAME "\".");
                        return 1;
                }

                if (get_z(who) == 704)
                {
                        notify("Đối phương đang ở trong Nhà Ngục");
                        return 1;
                }
                if (get_z(who) == 888)
                {
                        notify("Đối phương đang ở trong Vô Song Thành");
                        return 1;
                }
                if (get_z(who) == 889)
                {
                        notify("Đối phương đang ở trong Vô Song Cung");
                        return 1;
                }
                if (get_z(who) == 910)
                {
                        notify("Đối phương đang ở trong Bãi Luyện Tập");
                        return 1;
                }
                if (get_z(who) == 920)
                {
                        notify("Đối phương đang ở trong Bãi Luyện Tập");
                        return 1;
                }
                if (objectp(map = get_map_object(get_z(who))))
                {
                        switch (map->get_map_type())
                        {
                        case CAVE_MAP:
                                printf(ECHO "Đối phương đang trong hang động, không thể sử dụng \"" PF_NAME "\".");
                                return 1;
                        case BATTLE_MAP:
                                printf(ECHO "Đối phương đang trong chiến trường, không thể sử dụng \"" PF_NAME "\".");
                                return 1;
                        }
                        if (map->is_copy_scene())
                        {
                                printf(ECHO "Đối phương ở trong phó bản, không thể sử dụng \"" PF_NAME "\".");
                                return 1;
                        }
                }
                if (who->get_login_flag() < 3)
                {
                        printf(ECHO "Đối phương chưa chuẩn bị");
                        return 1;
                }
                /*                if( who->is_die() )
                {
                        printf( ECHO "Đối phương đã chết, không thể sử dụng\"" PF_NAME "\"." );
                        return 1;
                }*/
        }

        send_user(me, "%c%w%c%w", 0x50, 0, 0xff, 2); // 所有出招２秒后能使用
        me->set_time("pf", time());
        item->add_amount(-2);

        user = get_scene_object_2(me, USER_TYPE);
        send_user(user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN);
        //      send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

        me->add_mp(-mp);
        //      item->add_amount(-2);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->add_2("go_count.count2", 5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg(sprintf("%s,%d,%d,%d,%d", who->get_char_id(), level, get_z(who), get_x(who), get_y(who)));
        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());
        return 1;
}

// 函数:法术处理
int cast_done(object me)
{
        object who;
        string arg;
        int z, x, y, x0, y0, p;
        int level;

        if (!stringp(arg = me->get_cast_arg()) || sscanf(arg, "%s,%d,%d,%d,%d", arg, level, z, x, y) != 5)
                return 1;
        //      if( !objectp( who = find_char(arg) ) ) return 1;

        if (me->is_die())
                return 1;

        x0 = x;
        y0 = y;

        if (arg[ < 1] == '#') // 本帮总管(NPC)
        {
                if ((p = 18 - level / 10) > 0 && (p = get_valid_xy(z, x0 + random(p) - p / 2, y0 + random(p) - p / 2, IS_CHAR_BLOCK)))
                {
                        x = p / 1000;
                        y = p % 1000;
                        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 0, 1, OVER_BODY, PF_ONCE);
                        me->add_to_scene(z, x, y, get_d(me), 4291, 0, 4291, 0); // get_front_xy(x, y, x0, y0)
                }
                else
                        return 1;

                return 2; // 执行成功
        }

        if (!objectp(who = find_char(arg)))
                return 1;

        if ((p = 18 - level / 10) > 0 && (p = get_valid_xy(z, x0 + random(p) - p / 2, y0 + random(p) - p / 2, IS_CHAR_BLOCK)))
        {
                x = p / 1000;
                y = p % 1000;
                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 0, 1, OVER_BODY, PF_ONCE);

                me->set_login_flag(2); // 跳转保护
                set_invisible(me, 1);
                set_effect(me, EFFECT_USER_LOGIN, 4);

                me->add_to_scene(z, x, y, get_d(me), 4291, 0, 4291, 0); // get_front_xy(x, y, x0, y0)
        }
        else
                return 1;

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
