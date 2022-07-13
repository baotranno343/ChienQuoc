
// 自用持续技能  TIPS:[PF_SELF_LOOP]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0368
#define THIS_PERFORM    03683
#define PF_START       "03683"
#define PF_TIME        "03683#"
#define PF_NAME        "Ẩn Thân Thuật"

#define SKILL_LEVEL     4
#define TIME_INTERVAL   10
#define SUB_MP          20

int SKILL_LEVEL_SQUARE = SKILL_LEVEL * (SKILL_LEVEL - 1);

// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR " %s \n Võ công yêu cầu: Cấp 4\n Tuyệt kĩ tàng hình ẩn thân. Tốc độ di chuyển bị giảm đồng thời mỗi 10 giây tự động tiêu hao 10 điểm Pháp Lực.", PF_NAME);
        result = sprintf(HIC" %s \n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Tuyệt kĩ tàng hình ẩn thân. Tốc độ di chuyển bị giảm đồng thời mỗi 10 giây tự động tiêu hao 10 điểm Pháp Lực.\n", 
        	PF_NAME, SKILL_LEVEL, SUB_MP, TIME_INTERVAL);
        return result;
}

// 函数:获取描述(持续)
string get_loop_desc( object me )
{
        if( me->get_perform(PF_START) )
                return sprintf( PF_NAME ":\n　　Tuyệt kĩ Tàng hình Ẩn thân,tốc chạy giảm 50%%.\n" );
        else    return sprintf( PF_NAME "\n" );
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, interval, mp;
        object *user, item;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
        if (get_effect_3(me, EFFECT_CHAR_INVISIBLE))
        {
        	set_effect_2( me, EFFECT_CHAR_INVISIBLE, 1, 1 ); 
        	printf( ECHO "Bạn đã huỷ bỏ \"" PF_NAME "\" !" );
        	return 1;
        }

        interval = TIME_INTERVAL;

        if( gone_time( me->get_perform(PF_START) ) < interval ) return 1;    // 小心准备 level

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng \" %s \" cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }
		if ( objectp( item = present("Cờ Hiệu Vô Song Thành", me, 1, MAX_CARRY*4) ) )
		{
				printf( ECHO "Không thể Sử dụng \" %s \" khi mang theo Cờ Hiệu.", PF_NAME, mp );
                return 1;
		}
	/*	if ( get_z(me)==889 )
		{
				printf( ECHO "Không thể Sử dụng \" %s \" ở Vô Song Cung.", PF_NAME, mp );
                return 1;
		}*/

//        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );

        me->add_mp(-mp);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
	me->add_2("go_count.count2",9);
        interval = 30000;

        me->set_perform( PF_START, time() );
        me->set_perform( PF_TIME, interval );
//        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );

        user = get_scene_object_2(me, USER_TYPE);
        set_effect_2( me, EFFECT_CHAR_INVISIBLE, interval / 10 + 1, 10 );    // 每十秒减血
        set_effect_count( me, EFFECT_CHAR_INVISIBLE, interval % 10 );
        send_user( me, "%c%w%w%c", 0x81, 3631, 30000, EFFECT_GOOD );
        send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3631, 1, EFFECT_GOOD );
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 3631, 1, OVER_BODY, PF_ONCE );
        CHAR_CHAR_D->init_loop_perform(me);
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9000, 1, UNDER_FOOT, PF_LOOP );    // 半透明

        set_invisible(me, 1);
        if (!get_effect(me, EFFECT_03643)) send_user( me, "%c%c%c", 0x3d, 241, 1 );    // 更改走路步数

        return 1;
}

// 函数:法术处理
int cast_done( object me )
{
        object *user;
        int level, interval;

        level = me->get_skill(THIS_SKILL);
        interval = 30000;

        me->set_perform( PF_START, time() );
        me->set_perform( PF_TIME, interval );
//        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );

        user = get_scene_object_2(me, USER_TYPE);
        set_effect_2( me, EFFECT_CHAR_INVISIBLE, interval / 10 + 1, 10 );    // 每十秒减血
        set_effect_count( me, EFFECT_CHAR_INVISIBLE, interval % 10 );
        send_user( me, "%c%w%w%c", 0x81, 3631, get_effect_3(me, EFFECT_CHAR_INVISIBLE), EFFECT_GOOD );
        send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3631, 1, EFFECT_GOOD );
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 36311, 1, OVER_BODY, PF_ONCE );
        CHAR_CHAR_D->init_loop_perform(me);
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9000, 1, UNDER_FOOT, PF_LOOP );    // 半透明

        set_invisible(me, 1);
        send_user( me, "%c%c%c", 0x3d, 241, 1 );    // 更改走路步数

        return 2;    // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_ME; }

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
