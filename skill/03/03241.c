
// 单体远程技能  TIPS:[PF_CAST]  变异

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0324
#define THIS_PERFORM    03241
#define PF_START       "03241"
#define PF_NAME        "Long Đằng Cửu Thiên"

#define SKILL_LEVEL     43
#define TIME_INTERVAL   10
#define SUB_MP          15
#define SUB_YUAN        5

int SKILL_LEVEL_SQUARE = SKILL_LEVEL * (SKILL_LEVEL - 1);

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        return sprintf( "［" PF_NAME "］Nháy mắt di chuyển kĩ năng，có thể nháy mắt di chuyển đến phạm vi đã định。Pháp lực tiêu hao： %d， Nguyên khí tiêu hao： %d， Tái sử dụng sau %d giây，%s%d cấp có thể dùng\n",
                SUB_MP, SUB_YUAN, TIME_INTERVAL, level < SKILL_LEVEL ? HIR : "", SKILL_LEVEL );
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int z, x0, y0, d;
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 level

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng “ %s ”cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

        if( me->get_yuan() < SUB_YUAN )
        {
                printf( ECHO "Sử dụng “ %s ”cần %d điểm Nguyên khí.", PF_NAME, SUB_YUAN );
                return 1;
        }

        if( who )
        {
                if( !inside_screen_2(me, who) ) return 1;

                x = get_x(who);  y = get_y(who);
        }
/*      else if( objectp( who = me->get_enemy_2() ) && inside_screen_2(me, who) )
        {
                x = get_x(who);  y = get_y(who);
        }       */
        else
        {
                z = get_z(me);  x0 = get_x(me);  y0 = get_y(me);    // 下面要用到 x0, y0

                if( !inside_screen(x0, y0, x, y) ) return 1;
                if( !objectp( who = get_xy_object(z, x, y, CHAR_TYPE) ) && !objectp( who = get_xy_object(z, x, y, USER_TYPE) ) ) 
                {
                        if( !inside_map(z, x, y) ) return 1;    // 坐标非法
                        if( get_block(z, x, y) & IS_CHAR_BLOCK ) return 1;    // 无法落脚
                        if( !from_to( z, x0, y0, x - x0, y - y0, MAP_BLOCK ) ) return 1;    // 无法穿越

                        me->set_perform( PF_START, time() );

                        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 32411, 1, OVER_BODY, PF_ONCE );

                        me->add_to_scene( z, x, y, me->to_front_xy(x, y) );
                        send_user( me, "%c%w%w%w%c%c%c", 0x4f, x0, y0, 32411, 1, OVER_BODY, PF_ONCE );    // 补发指令

                        me->add_mp(-mp);
                        me->add_yuan( -SUB_YUAN );

                        set_heart_state(me, MAGIC_STAT);
                        set_heart_count_2(me, 9);
                        me->set_cast_file(__FILE__);
                        me->set_cast_arg( sprintf( "%d,%d,%d", z, x, y ) );

                        return 1;
                }
        }

        return 1;
}

// 函数：法术处理
int cast_done( object me )    // 无目标时
{
        string arg;

        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

//      return 1;    // 打到空地

        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_XY2; }

// 函数：能否使用特技
void can_perform( object me )
{
        int interval;

        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }

        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, PF_NAME );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, PF_NAME );
}
