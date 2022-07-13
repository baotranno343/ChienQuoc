
// 多体远程技能  TIPS:[PF_CAST_AREA]  变异

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <equip.h>

#define THIS_SKILL 0591
#define THIS_PERFORM 05913
#define PF_START "05913"
#define PF_NAME "Độn Giáp Trận"
#define SEAL_SIZE 4 // (31×31)阵法

#define SKILL_LEVEL 30
#define TIME_INTERVAL 12
#define SUB_MP (100 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 25)
#define ADD_INTERVAL 8
#define ADD_CP (40 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 15)

// 函数：获取描述
string get_desc(object me)
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level < SKILL_LEVEL)
                return HIR + PF_NAME + "\n Võ công yêu cầu: 50 cấp\n Vật phẩm tiêu hao: Trận Kì x2\n    Thiết lập trận pháp trong phạm vi 5x5 ô sát thương liên tục trong 10 giây tất cả mục tiêu lọt vào trận pháp";
        cur_level = (level - SKILL_LEVEL) / 10 + 1;
        result = sprintf(HIC " %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Vật phẩm tiêu hao: Trận Kì x2\n    Thiết lập trận pháp trong phạm vi 5x5 ô sát thương thích ứng %d trong 4 giây tất cả mục tiêu lọt vào trận pháp.\n " HIC "Cấp tiếp theo:\n " NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Tăng thêm %d sát thương nội công.",
                         PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ((ADD_CP + me->get_cp()) * 2), cur_level * 10 + SKILL_LEVEL, ((ADD_CP + me->get_cp()) * 2) + 10);
        return result;
}

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
        object item;
        int z;
        int level, mp;

        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        if (gone_time(me->get_perform(PF_START)) < TIME_INTERVAL)
                return 1;

        if (me->get_mp() < (mp = SUB_MP)) // 小心准备 me
        {
                printf(ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp);
                return 1;
        }

        if (!objectp(item = present("Trận Kì", me, 1, MAX_CARRY * 4)))
        {
                printf(ECHO "Phải có Trận Kì mới có thể sử dụng \"" PF_NAME "\".");
                return 1;
        }
        if (who)
        {
                if (!inside_screen_2(me, who))
                        return 1;

                z = get_z(who);
                x = get_x(who);
                y = get_y(who);
        }
        else
        {
                if (!inside_screen(get_x(me), get_y(me), x, y))
                        return 1;

                z = get_z(me);
        }

        if ((get_block(z, x, y) & SEAL_BLOCK))
        //      ||      objectp( map = get_seal_object(z, x, y) ) )
        {
                printf(ECHO "Nơi này đã bố trận");
                return 1;
        }
        /*      if( !valid_map_seal(z, x, y, SEAL_SIZE) )
        {
                printf( ECHO "布阵时，不能有阻挡，或其它人在场." );
                return 1;
        }       */

        send_user(me, "%c%w%c%w", 0x50, 0, 0xff, 2); // 所有出招２秒后能使用
        me->set_time("pf", time());

        me->to_front_xy(x, y);
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN);

        me->add_mp(-mp);
        item->add_amount(-2);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->add_2("go_count.count2", 5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg(sprintf("%d,%d,%d,%d", level, z, x, y));

        return 1;
}

// 函数：法术处理
int cast_done(object me)
{
        object item;
        string arg;
        int z, x, y;
        int level, cp;

        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());

        if (!stringp(arg = me->get_cast_arg()) || sscanf(arg, "%d,%d,%d,%d", level, z, x, y) != 4)
                return 1;

        send_user(get_scene_object_2(me, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, x, y,
                  5913, 1, OVER_TILE, PF_LOOP);

        cp = me->get_cp();

        item = new ("/item/std/0591");

        item->set(SEAL_AREA, SEAL_SIZE);
        item->set(SEAL_START, time());
        item->set(SEAL_INTERVAL, ADD_INTERVAL);    // 小心准备 me
        item->set(SEAL_CP, ADD_CP + me->get_cp()); // 小心准备 me, cp
        item->set_owner(me);

        set_z(item, z);
        set_x(item, x);
        set_y(item, y);
        set_d(item, SEAL_SIZE);
        //      set_map_seal(z, x, y, d);
        set_block(z, x, y, SEAL_BLOCK);
        move_object(item, z, x, y, CHAR_TYPE);

        item->do_start(me);
        CHAR_FIGHT_D->set_enmity1(me, 50);
        return 2; // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_XY; }

// 函数：能否使用特技
void can_perform(object me)
{
        int interval;
        string name;

        if (me->get_skill(THIS_SKILL) < SKILL_LEVEL)
        {
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME);
                return;
        }
        name = PF_NAME;
        interval = TIME_INTERVAL - gone_time(me->get_perform(PF_START));
        if (interval < 0)
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name);
        else
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name);
        send_user(me, "%c%w%w%c%c%c%c%c%s", 0x64, THIS_PERFORM, SUB_MP, 0, 10, MAGIC_ACT_BEGIN, 0, 5, "Trận Kì");
}
