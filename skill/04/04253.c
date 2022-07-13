
// 单体远程技能  TIPS:[PF_CAST]  变异

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <action.h>

#define THIS_SKILL      0425
#define THIS_PERFORM    04253
#define PF_START       "04253"
#define PF_NAME        "Đằng Vân Giá Vũ"

#define SKILL_LEVEL     22
#define TIME_INTERVAL   12
#define SUB_MP          40

// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 22 cấp\n    Tiên thuật cưỡi mây đạp gió, có thể biến đến kế bên người chơi khác trong chớp mắt";
        result = sprintf(HIC" %s \n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Tiên thuật cưỡi mây đạp gió, có thể biến đến kế bên người chơi khác trong chớp mắt", 
        	PF_NAME, SKILL_LEVEL, SUB_MP, TIME_INTERVAL );
        return result;	
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        int z, x0, y0, d;
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 level

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
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
                        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );

                        me->add_to_scene( z, x, y, me->to_front_xy(x, y) );
                        send_user( me, "%c%w%w%w%c%c%c", 0x4f, x0, y0, 3421, 1, OVER_BODY, PF_ONCE );    // 补发指令

                        me->add_mp(-mp);

                        set_heart_state(me, MAGIC_STAT);
                        set_heart_count_2(me, 9);
                        me->add_2("go_count.count2",9);
                        me->set_cast_file(__FILE__);
                        me->set_cast_arg( sprintf( "%d,%d,%d", z, x, y ) );

                        return 1;
                }
        }

        return 1;
}

// 函数:法术处理
int cast_done( object me )    // 无目标时
{
        string arg;        

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

//      return 1;    // 打到空地

        return 2;    // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_XY2; }

// 函数:能否使用特技
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
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0, 1, MAGIC_ACT_BEGIN, 0, 9, 0);
}
