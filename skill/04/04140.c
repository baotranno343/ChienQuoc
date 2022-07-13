
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0414
#define THIS_PERFORM    04140
#define PF_START       "04140"
#define PF_TIME        "04140#"
#define PF_NAME        "Hoá Cốt Miên Chưởng"
#define CAP_SKILL      10000

#define SKILL_LEVEL     100
#define TIME_INTERVAL   3
#define SUB_MP          300

// 函数:获取符法效果
int get_cast_seal() { return 9103; }    // 符纸逆旋

// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR " %s \n Võ công yêu cầu: Cấp 100\n Tuyệt kỹ độc môn của Ngũ Độc giáo, khi mục tiêu bị trúng chưởng mà di chuyển sẽ mất Khí Huyết.", PF_NAME);
        cur_level = me->get_save("luyenskill100")/CAP_SKILL;
        if ( cur_level < 1 )
		result = sprintf(HIY" %s ( Cấp %d )\n " HIR "Kỹ năng này chưa thể sử dụng.",
        	PF_NAME, cur_level );
		else if ( cur_level < 10 )
		result = sprintf(HIY" %s ( Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Tuyệt kỹ của Ngũ Độc giáo, khi mục tiêu di chuyển sẽ mất %d Khí Huyết ( Lực nội công càng cao càng có uy lực ).\n " HIC"Cấp tiếp theo:\n "NOR "Yêu cầu độ tu luyện: " HIR "%d " NOR "\n    Khi mục tiêu di chuyển mất %d Khí Huyết ( Lực nội công càng cao càng có uy lực ).",
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, cur_level*50, cur_level*CAP_SKILL+10000, cur_level*50+50 );
		else if ( cur_level >= 10 )
		result = sprintf(HIY" %s ( %s )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Tuyệt kỹ của Ngũ Độc giáo, khi mục tiêu di chuyển sẽ mất %d Khí Huyết ( Lực nội công càng cao càng có uy lực ).",
        	PF_NAME, "giới hạn", SKILL_LEVEL, SUB_MP, TIME_INTERVAL, cur_level*50 );
	return result;
}

// 函数:获取描述(持续)
string get_loop_desc( object me )
{
        if( get_effect(me, HOA_COT_MIEN_CHUONG ) )
                return sprintf( PF_NAME ":\nDi chuyển : -%d điểm Khí Huyết.\n", me->get("pf.hcmc") );
        else    return sprintf( PF_NAME "\n" );
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        int z, act, pf;
        int level, mp, speed;
		
        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
		if ( me->get_save("luyenskill100") < 10000 ) return 1;
	//	if (me->get_save("02610")==0) return 1;
		
        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 me

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }
		if ( me->get_fam_name() != "Mao Sơn" )
		{
				printf( ECHO "Phái Mao Sơn mới có thể sử dụng \"" PF_NAME "\"" );
                return 1;
		}
        if( who )
        {
                if( !inside_screen_2(me, who) ) return 1;

                z = get_z(who);  x = get_x(who);  y = get_y(who);

//                send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
                me->set_time( "pf", time() );

                pf = 78;    // 抄自 /sys/user/fight

                if( !( act = pf / 10 ) )    // pf: [动作序号][光影序号]
                {
		        pf = 0;  act = 1 + random(3);    // 无指定动作序号，随机
	        }

                me->to_front_xy(x, y);
                send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 70, get_d(me), getoid(who) );
        }
        else
        {
                if( !inside_screen( get_x(me), get_y(me), x, y ) ) return 1;

                z = get_z(me);
//                send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
                me->set_time( "pf", time() );

                pf = 78;    // 抄自 /sys/user/fight

                if( !( act = pf / 10 ) )    // pf: [动作序号][光影序号]
                {
		        pf = 0;  act = 1 + random(3);    // 无指定动作序号，随机
	        }

                me->to_front_xy(x, y);
                send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 70, get_d(me), 0 );
        }

        me->add_mp(-mp);

        set_heart_state(me, MAGIC_STAT);
        speed = 1;
       // if (speed<1) speed = 1;
        set_heart_count_2(me, speed);
        me->add_2("go_count.count2",speed);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%d,%d,%d,%d", level, z, x, y ) );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        return 1;
}
// 函数:法术处理
int cast_done( object me )
{
        object *char, *user, who;
        string arg;
        int z, x, y;
        int level, ap, i, size, count, ret, cur_level; 
		cur_level = me->get_save("luyenskill100")/10000;	

        if( !stringp( arg = me->get_cast_arg() ) || sscanf(arg, "%d,%d,%d,%d", level, z, x, y) != 4 ) return 1;

        char = get_scene_object(z, x, y, USER_TYPE);
		send_user( char, "%c%w%w%w%c%c%c", 0x4f, x, y, 41431, 1, OVER_BODY, PF_ONCE );
		send_user( char, "%c%w%w%w%c%c%c", 0x4f, x, y, 41432, 1, OVER_BODY, PF_ONCE );

//      if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功
	if( ( level = me->get_skill(THIS_SKILL) ) < 70 )
        	char = get_range_object(z, x, y, 5, USER_TYPE) + get_range_object(z, x, y, 5, CHAR_TYPE) - ({ me });
        else
        	char = get_range_object(z, x, y, 5, USER_TYPE) + get_range_object(z, x, y, 5, CHAR_TYPE) - ({ me });

        ap = me->get_cp();    // 小心准备 me
	count = 0;
        for( i = 0, size = sizeof(char); i < size; i ++ ) 
                if( who = char[i] ) 
                {
                	if( !who->can_be_fighted(me) || !me->can_fight(who) ) continue;
                	count ++;
                	if (count<=20) {
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 41431, 1, OVER_BODY, PF_ONCE );
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 41432, 1, OVER_BODY, PF_ONCE );
                	}
					ret = CHAR_FIGHT_D->cast_done(me, who, 0, -100);	
		        if ( who && !who->is_die() )
		        	CHAR_FIGHT_D->set_enmity(me,who,80);	
					
					if (ret>0 && who && random100()<101)
	        {	        	
				set_effect(who, HOA_COT_MIEN_CHUONG, 20);
                send_user( who, "%c%w%w%c", 0x81, 654, get_effect_3(who, HOA_COT_MIEN_CHUONG), EFFECT_BAD );
                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 654, 1, EFFECT_BAD );
			who->set("pf.hcmc", (me->get_cp()/5)+cur_level*50);
			}

                }

        return 2;    // 执行成功
}
// 函数:获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数:能否使用特技
void can_perform( object me )
{
        int interval;
        string name;
        
        int speed;
        speed=1;
     //   if (speed<1) speed = 1;
    //    if (me->get_save("02610")==0) return;	
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
	
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0,10,1, 70, speed, 0);
}
