
// 多体远程技能  TIPS:[PF_CAST_AREA]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0424
#define THIS_PERFORM    04243
#define PF_START       "04243"
#define PF_NAME        "Khốn Ma Trận"

#define SKILL_LEVEL     31
#define TIME_INTERVAL   12
#define SUB_MP          50

// 函数：获取符法效果
int get_cast_seal() { return 9102; }    // 符纸顺旋
int cast_done( object me );

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 31 cấp\n Vật phẩm tiêu hao: 6 lá Bùa Giấy\n    mục tiêu Phong Toả 3x3 trong khu vực tất cả hành động của kẻ địch khiến bất động trong 6 giây .Kỹ năng này đối với người chơi vô hiệu";
        result = sprintf(HIC" %s \n " NOR "Võ công yêu cầu: Cấp %d \n Vật phẩm tiêu hao: 6 lá Bùa Giấy\n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    mục tiêu Phong Toả 3x3 trong khu vực tất cả hành động của kẻ địch khiến bất động trong 6 giây .Kỹ năng này đối với người chơi vô hiệu",
        	PF_NAME, SKILL_LEVEL, SUB_MP, TIME_INTERVAL );
        return result;
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        object *user, item;
        int z;
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

        if( !objectp( item = present("Bùa Giấy", me, 1, MAX_CARRY*4) ) )    // || item->get_amount() < 2
        {
                printf( ECHO "Phải có Bùa Giấy mới có thể sử dụng \"" PF_NAME "\"." );    // "使用\"" PF_NAME "\"得准备两张符纸."
                return 1;
        }

        if( who )
        {
                if( !inside_screen_2(me, who) ) return 1;

                z = get_z(who);  x = get_x(who);  y = get_y(who);
        }
        else
        {
                if( !inside_screen( get_x(me), get_y(me), x, y ) ) return 1;

                z = get_z(me);
        }

        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );
        me->to_front_xy(x, y);
        user = get_scene_object_2(me, USER_TYPE);
        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        me->add_mp(-mp);
        set_heart_count_2(me, 5);
        me->add_2("go_count.count2",5);
        item->add_amount(-6);
        me->set_cast_arg( sprintf( "%d,%d,%d,%d", level, z, x, y ) );
	cast_done(me);
        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        object *char, who, *user;
        string arg;
        int z, x, y;
        int level, i, size, ret;

        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_STOP );
                send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );

        if( !stringp( arg = me->get_cast_arg() ) || sscanf(arg, "%d,%d,%d,%d", level, z, x, y) != 4 ) return 1;

        char = get_scene_object(z, x, y, USER_TYPE);
        send_user( char, "%c%w%w%w%c%c%w%c%c%c", 0x4f, x, y, 
                34829, 1, OVER_BODY, 34829, 1, OVER_BODY, PF_ONCE );

//      if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功

        char = get_range_object(z, x, y, 5, CHAR_TYPE) + get_range_object(z, x, y, 5, USER_TYPE) - ({ me });

        for( i = 0, size = sizeof(char); i < size; i ++ ) if( who = char[i] ) 
        {
        	if( !who->can_be_fighted(me) || !me->can_fight(who) ) continue;
	        if(     get_effect(who, EFFECT_CHAR_FAINT)
	        ||      get_effect(who, EFFECT_CHAR_FAINT_0) ) continue;    // 执行成功
	        if (who->get_perform("02222#")) continue;
	        if(     get_effect(who, EFFECT_CHAR_NO_MOVE) ) return 1;    // 执行成功
	        if (who->is_anti_effect()) continue;
	        ret = CHAR_FIGHT_D->cast_done(me, who, 0, -100); 
	        if (ret==0) continue;
	        if (!who) continue;
	        if (who->is_user()) continue;
                user = get_scene_object_2(who, USER_TYPE);
                set_effect(who, EFFECT_CHAR_NO_MOVE, 6);    // 小心准备 me
                if( get_heart_state(who) == MAGIC_STAT ) send_user( user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END );    // 结束施法动作               
                send_user( who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_NO_MOVE), EFFECT_BAD );
                send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD );
                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 34821, 10, UNDER_FOOT, PF_LOOP );
                CHAR_CHAR_D->init_loop_perform(who);
        	
        }

        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数：能否使用特技
void can_perform( object me )
{
        int level, interval, interval2;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }

        interval = TIME_INTERVAL;    // 小心准备 me
        interval2 = interval - gone_time( me->get_perform(PF_START) );
        if( interval2 < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), interval, 0, PF_NAME );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), interval, interval2, PF_NAME );
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 1, 10, MAGIC_ACT_BEGIN, 0, 5, 0);
}
