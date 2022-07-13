
// 暗器技能  TIPS:[PF_THROWING]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <equip.h>
#include <effect.h>

#define THIS_SKILL      0161
#define THIS_PERFORM    01611
#define PF_START       "01611"
#define PF_NAME        "Đầu Xạ"

// 函数：获取描述
string get_desc( object me )
{
        return "［" PF_NAME "］单体远程攻击，再次使用需间隔 1 秒\n";
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int z, act, pf;

        if( me->get_perform(PF_START) == time() ) return 0;
        if( me->get_weapon_code() != THROWING ) 
        {
                return 0;
        }
        if( who )
        {
                if( !inside_screen_2(me, who) ) return 0;

                x = get_x(who);  y = get_y(who);
        }
        else 
        {
        	return 0;
        }        
	if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 0;    // 执行成功
        me->set_enemy_2(who);    // 远程目标锁定
        me->set_enemy(who);

        pf = 60;    // 抄自 /sys/user/fight

        if( !( act = pf / 10 ) )    // pf: [动作序号][光影序号]
        {
	        pf = 0;  act = 1 + random(3);    // 无指定动作序号，随机
	}
	if( get_effect(me, EFFECT_CHAR_INVISIBLE) ) set_effect_2(me, EFFECT_CHAR_INVISIBLE, 1, 1 ); 
        me->to_front_xy(x, y);
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), act, pf, get_d(me), getoid(who) );

        set_heart_state(me, MAGIC_STAT);
//        set_heart_count_2(me, 3);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( who->get_char_id() );	
        return 2;
}

// 函数：法术处理
int cast_done( object me )
{
        object who;
        string arg;
        int z, x, y;

//        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );      
        me->set_perform( PF_START, time() );

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( sscanf(arg, "%d,%d,%d", z, x, y) == 3 )
        {
//              send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, x, y, 16121, 1, OVER_BODY, PF_ONCE );

                return 1;    // 打到空地
        }
        if( !objectp( who = find_char(arg) ) ) return 1;

//      send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 16121, 1, OVER_BODY, PF_ONCE );

        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功
//	set_heart_count_2(me, 10);
        CHAR_FIGHT_D->throwing_done(me, who, HIT_THROWING);
        

        return 2;    // 执行成功
}

// 函数：命令处理
int perform_action_npc( object me, object who )
{
        int act, pf;

        if( !inside_screen_2(me, who) ) return 0;

        pf = 60;    // 抄自 /sys/user/fight

        if( !( act = pf / 10 ) )    // pf: [动作序号][光影序号]
        {
	        pf = 0;  act = 1 + random(3);    // 无指定动作序号，随机
	}

        me->to_front_xy( get_x(who), get_y(who) );
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), act, pf, get_d(me), getoid(who) );

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( who->get_char_id() );

        return 1;
}

// 函数：法术处理
int cast_done_npc( object me )
{
        object who;
        string arg;
        int z, x, y;

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( !objectp( who = find_char(arg) ) ) return 1;

//      send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 16121, 1, OVER_BODY, PF_ONCE );

       if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功

        CHAR_FIGHT_D->throwing_done(me, who, HIT_THROWING);

        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数：能否使用特技
void can_perform( object me )
{
        send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME );
}
