
// 暗器技能  TIPS:[PF_THROWING]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0261
#define THIS_PERFORM    02615
#define PF_START       "02615"
#define PF_NAME        "Bách Bộ Xuyên Dương"

#define SKILL_LEVEL     20
#define TIME_INTERVAL   6
#define SUB_MP          10 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/10 * 2
#define ADD_DAMAGE     	50 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/10 * 40
#define ADD_RATE     	1000 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/10*100

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR" %s \nVõ công yêu cầu: Cấp 20\n Nhắm kỹ mục tiêu trước khi tung sát chiêu ám khí, tăng thêm 50 điểm Ngoại Công và tăng 10%% khả năng ra đòn Bạo Kích khi sát thương mục tiêu.", PF_NAME);
        cur_level = (level - SKILL_LEVEL)/10 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Nhắm kỹ mục tiêu trước khi tung sát chiêu ám khí, tăng thêm %d điểm Ngoại Công và tăng %d%% khả năng ra đòn Bạo Kích khi sát thương mục tiêu.\n " HIC"Cấp tiếp theo:\n "NOR"Võ công yêu cầu: "HIR"Cấp %d \n" NOR "    Nhắm kỹ mục tiêu trước khi tung sát chiêu ám khí, tăng thêm %d điểm Ngoại Công và tăng %d%% khả năng ra đòn Bạo Kích khi sát thương mục tiêu.", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_DAMAGE, (ADD_RATE)/100, cur_level*10+SKILL_LEVEL, ADD_DAMAGE + 40, (ADD_RATE)/100 + 1);
        return result;
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int z, act, pf;
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 me

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

        if( me->get_weapon_code() != THROWING ) 
        {
                printf( ECHO "Sử dụng \"" PF_NAME "\" phải trang bị ám khí" );
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
                z = get_z(me);

                if( !inside_screen( get_x(me), get_y(me), x, y ) ) return 1;
                if( !objectp( who = get_xy_object(z, x, y, CHAR_TYPE) ) && !objectp( who = get_xy_object(z, x, y, USER_TYPE) ) ) 
                {
//                        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
                        me->set_time( "pf", time() );

	                pf = 64;    // 抄自 /sys/user/fight

                	if( !( act = pf / 10 ) )    // pf: [动作序号][光影序号]
                	{
		                pf = 0;  act = 1 + random(3);    // 无指定动作序号，随机
	                }

                        me->to_front_xy(x, y);
                        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 2, 30, get_d(me), 0 );

                        me->add_mp(-mp);

                        set_heart_state(me, MAGIC_STAT);
                        set_heart_count_2(me, 9);
                        me->add_2("go_count.count2",9);
                        me->set_cast_file(__FILE__);
                        me->set_cast_arg( sprintf( "%d,%d,%d", z, x, y ) );

                        return 1;
                }
        }

//        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        me->set_enemy_2(who);    // 远程目标锁定

        me->add_mp(-mp);
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->add_2("go_count.count2",9);
        set_effect(me, EFFECT_PROGRESS2, 3);
        me->set_progress_file(__FILE__);
        me->set_progress_arg( who->get_char_id());
        me->set_enemy(0);
        send_user(me, "%c", 0x01);
	send_user(me, "%c%c%w%s", 0x5a, 0, 3, "Bách Bộ Xuyên Dương……");
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        return 1;
}

// 函数：法术处理
int into_effect( object me , string arg)
{
        object who;
        int z, x, y, pf, act;
        int level, rate;
        int interval, sub_effect;
	send_user(me, "%c%c%c", 0x5a, 1, 1);        

        if( !objectp( who = find_char(arg) ) ) return 1;

        me->to_front_xy(x, y);
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 2, 30, get_d(me), getoid(who) );
        
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 26159, 1, OVER_BODY, PF_ONCE );
        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 26151, 1, OVER_BODY, PF_ONCE );

        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功

	me->set("add_damage", ADD_DAMAGE);
	rate = me->get_double_rate();
	me->set_double_rate(rate+ADD_RATE);
        CHAR_FIGHT_D->throwing_done(me, who, HIT_NONE);    // 小心准备 me
        if ( who && !who->is_die() )
        	CHAR_FIGHT_D->set_enmity(me,who,90);	

        me->set("add_damage", 0);
        me->set_double_rate(rate);
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
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/10+1);
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0, 10, MAGIC_ACT_BEGIN, 0, 9, 0);
}

void effect_break(object me, string arg)
{
	send_user(me, "%c%c%c", 0x5a, 1, 0);
	set_effect(me, EFFECT_PROGRESS2, 0 );	
}
