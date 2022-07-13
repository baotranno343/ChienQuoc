
// 自用技能  TIPS:[PF_SELF]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0348
#define THIS_PERFORM    03481
#define PF_START       "03481"
#define PF_NAME        "Thiền Trị"

#define SKILL_LEVEL     5
#define TIME_INTERVAL   20
#define SUB_MP          0
#define SUB_YUAN        2
#define ADD_TIME	(5 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/11)
#define ADD_HP		(30 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/11 * 5)

// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level, interval, add_time, add_hp;
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR" %s \n Võ công yêu cầu: Cấp 5\n Tự trị thương, hồi phục 150 điểm Khí Huyết trong 10 giây.", PF_NAME);
        cur_level = (level - SKILL_LEVEL)/11 + 1;
        interval = 20 + (level-SKILL_LEVEL)/11;
        add_time = ADD_TIME;
        add_hp = ADD_HP;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Tự trị thương, trong %d giây hồi phục %d điểm Khí Huyết.\n " HIC"Cấp tiếp theo:\n "NOR"Võ công yêu cầu: " HIR "Cấp %d " NOR"\n    Tự trị thương, trong %d giây hồi phục %d điểm Khí Huyết.", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL, add_time * 2, add_time * add_hp, cur_level*11+SKILL_LEVEL, (add_time+1)*2, (add_time+1) * (add_hp+5) );
	return result;  
}

// 函数:获取描述(持续)
string get_loop_desc( object me )
{
        if( me->get_perform(PF_START) )
                return sprintf( " %s :\n Mỗi 2 giây hồi phục %d điểm Khí Huyết\n", PF_NAME, me->get("pf.recover") );
        else    return sprintf( PF_NAME "\n" );
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 level

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }
        if( me->get_yuan() < SUB_YUAN )
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Nguyên khí.", PF_NAME, SUB_YUAN );
                return 1;
        }
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );

        me->add_mp(-mp);
        me->add_yuan( -SUB_YUAN );

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->add_2("go_count.count2",9);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%d", level ) );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        return 1;
}

// 函数:法术处理
int cast_done( object me )
{
        object *user;
        string arg;
        int level, hp, interval;        

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;
        level = to_int(arg);

        interval = ADD_TIME;    // 小心准备 level
        hp = ADD_HP;    // 小心准备 level
        me->set("pf.recover", hp);

        user = get_scene_object_2(me, USER_TYPE);
        set_effect_2(me, EFFECT_USER_RECOVER, ADD_TIME, 2);
        send_user( me, "%c%w%w%c", 0x81, 3481, get_effect_3(me, EFFECT_USER_RECOVER), EFFECT_GOOD );
        send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3481, 1, EFFECT_GOOD );
        send_user(me, "%c%c%w%s", 0x5a, 0, interval*2, "Sử dụng Thiền Trị……");

        if( get_effect(me, EFFECT_CHAR_WOUND) ) set_effect(me, EFFECT_CHAR_WOUND, 1);    // 负伤状态
        if( get_effect(me, EFFECT_CHAR_BLOOD) ) set_effect(me, EFFECT_CHAR_BLOOD, 1);    // 流血状态

        return 2;    // 执行成功
}

// 函数:停止休整
void effect_recover_break( object me )
{
        set_effect(me, EFFECT_USER_RECOVER, 0);
        send_user( me, "%c%w%w%c", 0x81, 3481, 0, EFFECT_GOOD );
        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3481, 0, EFFECT_GOOD );
        send_user(me, "%c%c%c", 0x5a, 1, 0);    // send_user(me, "%c%c", 0x5a, 255);
}

// 函数:法术处理
void effect_recover_done( object me )
{
        int hp;

        if( !get_effect(me, EFFECT_USER_RECOVER) ) effect_recover_break(me);    // 循环征状 set_effect_2

        hp = me->get("pf.recover");

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 3481, 1, OVER_BODY, PF_ONCE );
        send_user(me, "%c%d%w", 0x68, getoid(me), -hp);
        if (!me->no_recover() && !get_effect_3(me, EFFECT_USER_BURN)) me->add_hp(hp);  
        
}

// 函数:获取特技类型
int get_perform_type() { return ON_ME; }

// 函数:能否使用特技
void can_perform( object me )
{
        int interval;
        string name;
        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/11+1);
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 1, MAGIC_ACT_BEGIN, 0, 9, 0);
}