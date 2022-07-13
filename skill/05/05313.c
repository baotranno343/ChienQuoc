
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <action.h>

#define THIS_SKILL      0531
#define THIS_PERFORM    05313
#define PF_START       "05313"
#define PF_NAME        "Thôi Miên Thuật"

#define SKILL_LEVEL     20
#define TIME_INTERVAL   40
#define SUB_MP          90

// 函数：获取符法效果
int get_cast_seal() { return 9101; }    // 符纸顺旋

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 20 cấp\n Vật phẩm tiêu hao: Mê Thần Tán\n    Tung bột thôi miên, khiến đối thủ bị Mộng Du trong 30 giây";
        result = sprintf(HIC" %s \n " NOR "Võ công yêu cầu: Cấp %d \n Vật phẩm tiêu hao: Mê Thần Tán\n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Tung bột thôi miên, khiến đối thủ bị Mộng Du trong 30 giây", 
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

        if( who )
        {
                if( !inside_screen_2(me, who) ) return 1;

                x = get_x(who);  y = get_y(who);
        }
        else if( objectp( who = me->get_enemy_2() ) && inside_screen_2(me, who) )
        {
                x = get_x(who);  y = get_y(who);
        }
        else
        {
        	return 1;
        }
        if (who->is_anti_effect()) return 1;
     /*   if( !objectp( item = present("Mê Thần Tán", me, 1, MAX_CARRY) ) )
        {
                printf( ECHO "Phải có Mê Thần Tán mới sử dụng được \"" PF_NAME "\"." );
                return 1;
        }*/
		if( !objectp( item = present("Mê Thần Tán", me, 1, MAX_CARRY*4) ) )    // || item->get_amount() < 3
        {
                printf( ECHO "Phải có Mê Thần Tán mới có thể sử dụng \"" PF_NAME "\"." );    // "使用\"" PF_NAME "\"得准备三张符纸."
                return 1;
        }
        item->add_amount(-1); 
        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        me->set_enemy_2(who);    // 远程目标锁定

        me->to_front_xy(x, y);
        user = get_scene_object_2(me, USER_TYPE);
        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

        me->add_mp(-mp);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->add_2("go_count.count2",5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s,%d", who->get_char_id(), level ) );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        object *user, who;
        string arg;
        int z, x, y;
        int level, ret;
        int cp, cp0, cp2, pp, pp0, pp2, asp, dsp;
        int rate, damage, id, double_flag, random;               

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;
        if( sscanf(arg, "%s,%d", arg, level) != 2 ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;

        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 
                5313, 1, OVER_BODY, PF_ONCE );

        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功

        cp = me->get_cp();  cp0 = me->get_cp_0(); 
        pp = who->get_pp();  pp0 = who->get_pp_0();
        asp = me->get_sp();  dsp = who->get_sp();

        // 判断能否命中

        rate = asp * 86 / range_value(dsp, 1, MAX_NUMBER);    // asp * 43 * 100 / 50 / dsp
        rate += me->get_hit_rate_2() - who->get_dodge_rate_2();    // 附加命中－附加闪避＋特殊技附加命中    // + hit_rate
        if( get_effect(me, EFFECT_CHAR_BLIND) ) rate /= 2;    // 失明(命中减半)
        if (get_effect(who, EFFECT_DODGE)) rate -= 20;
        rate = range_value(rate, 5, 97);
        if( random(100) < rate )
        {
	        if( who->get("anti_dream") || get_effect_3(who, EFFECT_CHAR_DREAM) ) return 2;    // 执行成功
                set_effect_2(who, EFFECT_CHAR_DREAM, 15, 2);
                send_user( who, "%c%w%w%c", 0x81, 9016, get_effect_3(who, EFFECT_CHAR_DREAM), EFFECT_BAD );
                send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 53112, 1, OVER_BODY, PF_LOOP );
                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9016, 1, EFFECT_BAD );        	
                CHAR_CHAR_D->init_loop_perform(who);
	        if ( who && !who->is_die() )
	        	CHAR_FIGHT_D->set_enmity(me,who,30);
        }
        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数：能否使用特技
void can_perform( object me )
{
        int interval;
        string name;

        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL )
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }
	name = PF_NAME;
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
	send_user(me, "%c%w%w%c%c%c%c%c%s", 0x64, THIS_PERFORM, SUB_MP, 0,10, MAGIC_ACT_BEGIN, 0, 5, "Trận Kì");
}
