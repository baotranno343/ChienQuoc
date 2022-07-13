
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0368
#define THIS_PERFORM    03686
#define PF_START       "03686"
#define PF_NAME        "Bí Sát"

#define SKILL_LEVEL     38
#define TIME_INTERVAL   40
#define SUB_MP          40

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 38 cấp\n    Tuyệt kĩ chỉ có thể sử dụng sau khi Ẩn Thân, khi tấn công có khả năng làm đối thủ bị Hôn Mê trong 30 giây. Nếu thất bại làm Hôn Mê đối thủ sẽ bị hiện thân. Khả năng thành công phụ thuộc vào đẳng cấp võ công của bản thân và cấp độ của mục tiêu.";
        result = sprintf(HIC" %s \n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Tuyệt kĩ chỉ có thể sử dụng sau khi Ẩn Thân, khi tấn công có khả năng làm đối thủ bị Hôn Mê trong 30 giây. Nếu thất bại làm Hôn Mê đối thủ sẽ bị hiện thân. Khả năng thành công phụ thuộc vào đẳng cấp võ công của bản thân và cấp độ của mục tiêu.",
        	PF_NAME, SKILL_LEVEL, SUB_MP, TIME_INTERVAL );
	return result;
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int z, act, pf;
        int level, mp, d, rate, damage;
        object *user;

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
        else if( objectp( who = me->get_enemy_2() ) && inside_screen_2(me, who) )
        {
                x = get_x(who);  y = get_y(who);
        }
        else
        {
		return 1;
        }
	if (!get_effect(me, EFFECT_CHAR_INVISIBLE))
        {
                printf( ECHO "Sử dụng \"" PF_NAME "\" phải ở trạng thái ẩn thân" );
                return 1;
        }	
	if (get_z(who)!=get_z(me)||abs(get_x(me)-get_x(who))>1||abs(get_y(me)-get_y(who))>1) 
	{
                printf( ECHO "Sử dụng \"" PF_NAME "\" cần phải đứng gần nhau" );
                return 1;		
	}        
	d = get_front_xy( get_x(who), get_y(who), get_x(me), get_y(me) );
	if ( who->get("anti_sleep") )	//抗昏迷
	{
                printf( ECHO "Không thể sử dụng" );
                return 1;		
	}
	if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 1;    // 执行成功
	me->set_enemy_2(who);    // 远程目标锁定
        pf = 20;    // 抄自 /sys/user/fight

        if( !( act = pf / 10 ) )    // pf: [动作序号][光影序号]
        {
	        pf = 0;  act = 1 + random(3);    // 无指定动作序号，随机
	}
       
        me->to_front_xy(x, y);
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 2, 100, get_d(me), getoid(who) );

        me->add_mp(-mp);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->add_2("go_count.count2",9);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( who->get_char_id() );
        me->set_perform(PF_START, time());
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        
	rate = me->get_skill(THIS_SKILL)*100;
	if (who->get_level()>0) rate /= who->get_level();
	if (rate>100) rate = 100;
	rate = rate * 9 / 10 ;
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 3686, 1, OVER_BODY, PF_ONCE );
	if ( !who->get("anti_sleep") && (random(100)<rate) && (who->is_anti_effect()==0) )
	{
                user = get_scene_object_2(who, USER_TYPE);
                set_effect(who, EFFECT_SLEEP, 30);    // 小心准备 me
                CHAR_CHAR_D->stop_loop_perform_faint(who);
                CHAR_CHAR_D->init_loop_perform(who);
                if( get_heart_state(who) == MAGIC_STAT ) send_user( user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END );    // 结束施法动作               
                send_user( who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_SLEEP), EFFECT_BAD );
                send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD );
                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9015, 10, OVER_BODY, PF_LOOP );
                me->set_enemy(0);		
                send_user(me, "%c", 0x01);
	}
	else set_effect_2(me, EFFECT_CHAR_INVISIBLE, 1, 1);

        if ( who && !who->is_die() )
        	CHAR_FIGHT_D->set_enmity(me,who,50);	
	
        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );        
        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
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
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/15+1);
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0, 10, 2, 20, 9, 0);
}
