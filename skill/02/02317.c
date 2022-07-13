
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <npc.h>

#define THIS_SKILL      0231
#define THIS_PERFORM    02317
#define PF_START       "02317"
#define PF_NAME        "Luân Hồi Thuật"

#define SKILL_LEVEL     150
#define TIME_INTERVAL   30  
#define SUB_MP          ( 100 - ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 150 * 1 )
#define ADD_INTERVAL    ( 5 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 150 * 5 )


// 函数:获取符法效果
int get_cast_seal() { return 9102; }    // 符纸逆旋

// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 150 cấp\n    Đạo thuật có khả năng biến kẻ địch thành một động vật. Trong hình thể động vật sẽ không thể sử dụng bất cứ phép thuật hay kỹ năng nào (Nhưng có thể sử dụng vật phẩm).";
        cur_level = (level - SKILL_LEVEL)/150 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Đạo thuật có khả năng biến kẻ địch thành một động vật. Trong hình thể động vật sẽ không thể sử dụng bất cứ phép thuật hay kỹ năng nào (Nhưng có thể sử dụng vật phẩm).Bị biến thân,Né tránh gia tăng 300%%，Thân thủ gia tăng 50%%.\n    Sử dụng với quái vật và Boss không có hiệu quả.\n    Xác xuất biến thân thành công dựa vào cấp bậc của mình và địch nhân.\n    Biến thân thuật hiểu qua trong %d giây.\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Biến thân thuật hiệu quả kéo dài %d giây.",
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_INTERVAL, cur_level*150+SKILL_LEVEL, ADD_INTERVAL+5 );
	return result;
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        object *user, item;
        int z;
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
		if (me->get_save("02317")==0) return 1;
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
                z = get_z(me);

                if( !inside_screen( get_x(me), get_y(me), x, y ) ) return 1;
                if( !objectp( who = get_xy_object(z, x, y, CHAR_TYPE) ) && !objectp( who = get_xy_object(z, x, y, USER_TYPE) ) ) 
                {
                        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
                        me->set_time( "pf", time() );

                        me->to_front_xy(x, y);
                        user = get_scene_object_2(me, USER_TYPE);
                        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
                        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

                        me->add_mp(-mp);
//                        item->add_amount(-0);

                        set_heart_state(me, MAGIC_STAT);
                        set_heart_count_2(me, 5);
                        me->add_2("go_count.count2",5);
                        me->set_cast_file(__FILE__);
                        me->set_cast_arg( sprintf( "%d,%d,%d", z, x, y ) );

                        return 1;
                }
        }

        if( me == who )
        {
                printf( ECHO "Chính mình không thể sử dụng \"" PF_NAME "\"." );
                return 1;
        }
        if( !who->can_be_fighted(me) || !me->can_fight(who) )
        {
                printf( ECHO "Chỉ có thể sử dụng với người\"" PF_NAME "\"." );
                return 1;
        }
        if( who->get_char_type()!=FIGHTER_TYPE && !who->is_user() )
        {
                printf( ECHO "Không thể sử dụng với đối phương\"" PF_NAME "\"." );
                return 1;
        }
        
        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        me->set_enemy_2(who);    // 远程目标锁定

        me->to_front_xy(x, y);
        user = get_scene_object_2(me, USER_TYPE);
        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

        me->add_mp(-mp);
//        item->add_amount(-0);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->add_2("go_count.count2",5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s,%d", who->get_char_id(), level ) );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        return 1;
}

// 函数:法术处理
int cast_done( object me )
{
        object *user, who;
        string arg;
        int z, x, y, type;
        int level, level2, rate, interval;        

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( sscanf(arg, "%d,%d,%d", z, x, y) == 3 )
        {
                send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%w%c%c%c", 0x4f, x, y, 
                        42321, 2, OVER_BODY, 42321, 2, OVER_BODY, PF_ONCE );

                return 1;    // 打到空地
        }
        if( sscanf(arg, "%s,%d", arg, level) != 2 ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;

        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 以下为附加效果！

        if( get_effect(who, EFFECT_MAGIC_4243) ) return 2;    // 执行成功

	if ( who->get("no_sk04211") ) return 1;

	level2 = who->get_level();
	if (level>level2) rate = 95;
	else rate = 95 * level / level2;
	if (rate<5) rate = 5;
        if( get_effect(me, EFFECT_CHAR_BLIND) ) rate /= 2;    // 失明(命中减半)

        if( random(100) < rate )    // 随机失败
        {
                interval = ADD_INTERVAL;    // 小心准备 me
                if( get_effect(who, EFFECT_MAGIC_CARD) )	//有变身
			set_effect(who, EFFECT_MAGIC_CARD, 0);
                set_effect(who, EFFECT_MAGIC_4243, interval);
                switch(random(3))
                {
                case 0:
                	type = 10; break;
                case 1:
                	type = 11; break;
                default:
                	type = 304; break;
                }
                
                if (who->is_user()) who->set_save("pf#4243", type);
                else who->set("pf#4243", type);
                who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who) );       
                send_user( who, "%c%w%w%c", 0x81, 4243, get_effect_3(who, EFFECT_MAGIC_4243), EFFECT_BAD );                                
                send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who), 42431, 1, OVER_BODY, 42432, 1, OVER_BODY, PF_ONCE );
	        if ( who && !who->is_die() )
	        	CHAR_FIGHT_D->set_enmity(me,who,120);
                return 2;         
        }
        return 2;    // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数:能否使用特技
void can_perform( object me )
{
        int level, interval, interval2;
		if (me->get_save("02317")==0) return;
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
	send_user(me, "%c%w%w%c%c%c%c%c%s", 0x64, THIS_PERFORM, SUB_MP, 0, 10, MAGIC_ACT_BEGIN, 0, 5, "Bùa Giấy");
}

void into_effect(object who)
{
        send_user( who, "%c%w%w%c", 0x81, 4243, 0, EFFECT_BAD );
        send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 4243, 0, EFFECT_BAD );	
	who->add_to_scene(get_z(who), get_x(who), get_y(who));   
}

// 函数:获取描述(持续)
string get_loop_desc( object me )
{
	return PF_NAME + ":\n　　Biến thân Động vật\n";
}

int perform_action_npc( object me, object who)
{
        object *user, item;
        int x,y,z;
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;

    	
        if( !who )
        	return 0;
        
	if( !inside_screen_2(me, who) ) return 1;

	x = get_x(who);  y = get_y(who);

        if( me == who )
        {
                return 1;
        }
        if( !who->can_be_fighted(me) || !me->can_fight(who) )
        {
                return 1;
        }
        if( who->get_char_type()!=FIGHTER_TYPE && !who->is_user() )
        {
                return 1;
        }
        
        me->set_enemy_2(who);    // 远程目标锁定

        me->to_front_xy(x, y);
        user = get_scene_object_2(me, USER_TYPE);
        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s,%d", who->get_char_id(), level ) );
        return 1;
}

// 函数:法术处理
int cast_done_npc( object me )
{
        object *user, who;
        string arg;
        int z, x, y, type;
        int level, level2, rate, interval;

        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( sscanf(arg, "%d,%d,%d", z, x, y) == 3 )
        {
                send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%w%c%c%c", 0x4f, x, y, 
                        42321, 2, OVER_BODY, 42321, 2, OVER_BODY, PF_ONCE );

                return 1;    // 打到空地
        }
        if( sscanf(arg, "%s,%d", arg, level) != 2 ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;

        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 以下为附加效果！

        if( get_effect(who, EFFECT_MAGIC_4243) ) return 2;    // 执行成功

	if ( who->get("no_sk04211") ) return 1;

	level2 = who->get_level();
	if (level>level2) rate = 95;
	else rate = 95 * level / level2;
	if (rate<5) rate = 5;
        if( get_effect(me, EFFECT_CHAR_BLIND) ) rate /= 2;    // 失明(命中减半)

        if( random(100) < rate )    // 随机失败
        {
                interval = ADD_INTERVAL;    // 小心准备 me
                if( get_effect(who, EFFECT_MAGIC_CARD) )	//有变身
			set_effect(who, EFFECT_MAGIC_CARD, 0);
                set_effect(who, EFFECT_MAGIC_4243, interval);
                switch(random(3))
                {
                case 0:
                	type = 10; break;
                case 1:
                	type = 11; break;
                default:
                	type = 304; break;
                }
                
                if (who->is_user()) who->set_save("pf#4243", type);
                else who->set("pf#4243", type);
                who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who) );       
                send_user( who, "%c%w%w%c", 0x81, 4243, get_effect_3(who, EFFECT_MAGIC_4243), EFFECT_BAD );                                
                send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who), 42431, 1, OVER_BODY, 42432, 1, OVER_BODY, PF_ONCE );
	        if ( who && !who->is_die() )
	        	CHAR_FIGHT_D->set_enmity(me,who,120);
                return 2;         
        }
        return 2;    // 执行成功
}