
// 单体远程技能  TIPS:[PF_CAST]  变异

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <equip.h>
#include <cmd.h>
#include <effect.h>

#define THIS_SKILL      0329
#define THIS_PERFORM    03294
#define PF_START       "03294"
#define PF_NAME        "Hồi Thiên Thuật"

#define SKILL_LEVEL     40
#define TIME_INTERVAL   (3600 - (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/8*180)
#define SUB_MP          250 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/8*20

// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 40 cấp\n Vật phẩm tiêu hao:Hồi Thiên Tâm Pháp\n    Thần thuật của thượng tiên đắc đạo, có thể cải tử hoàn sinh người chết.";
        cur_level = (level - SKILL_LEVEL)/8 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau:%d giây\n Vật phẩm tiêu hao:Hồi Thiên Tâm Pháp\n    Thần thuật của thượng tiên đắc đạo, có thể cải tử hoàn sinh người chết.\n " HIC"Cấp tiếp theo:\n"NOR "Võ công yêu cầu: Cấp %d \n     Thời gian tái sử dụng giảm còn %d giây", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL/60, cur_level*8+SKILL_LEVEL, TIME_INTERVAL/60-3 );
	return result;  
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        int z;
        int level, mp;
        object item;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }
        if( get_effect(me, EFFECT_CHAR_NO_PF) ) 
        {
        	notify( "Bạn bị trạng thái phong ấn" );
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
                z = get_z(me);

                if( !inside_screen( get_x(me), get_y(me), x, y ) ) return 1;
                if( !objectp( who = get_xy_object(z, x, y, USER_TYPE) ) ) return 1;

/*              if( !objectp( who = get_xy_object(z, x, y, CHAR_TYPE) ) && !objectp( who = get_xy_object(z, x, y, USER_TYPE) ) ) 
                {
                        me->set_perform( PF_START, time() );
                        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
                        me->set_time( "pf", time() );

                        me->to_front_xy(x, y);
                        user = get_scene_object_2(me, USER_TYPE);
                        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );

                        me->add_mp(-mp);

                        set_heart_state(me, MAGIC_STAT);
                        set_heart_count_2(me, 9);
                        me->set_cast_file(__FILE__);
                        me->set_cast_arg( sprintf( "%d,%d,%d", z, x, y ) );

                        return 1;
                }       */
        }
	if(!who->is_user())
	{
		printf( ECHO "Đối với đối phương không thể sử dụng \"" PF_NAME "\"." );
		return 1;
	}
        if(who->get_login_flag() < 3 )
        {
                printf( ECHO "Đối phương chưa chuẩn bị" );
                return 1;
        }
        if( !who->is_die() )
        {
                printf( ECHO "Đối với người sống không thể sử dụng \"" PF_NAME "\"." );
                return 1;
        }
	if ("/sys/user/attack"->can_use_help(me, who)==0)
	{				
		printf( ECHO "Đối với đôií phương không thể sử dụng " PF_NAME );
		return 1;				
	}        
        if( !objectp( item = present("Hồi Thiên Tâm Pháp", me, 1, MAX_CARRY*4) ) )
        {
                printf( ECHO "Phải có Hồi Thiên Tâm Pháp mới có thể sử dụng \"" PF_NAME "\"." );
                return 1;
        }       
        item->add_amount(-1); 
        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

//      me->set_enemy_2(who);    // 远程目标锁定

        me->to_front_xy(x, y);
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );

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

// 函数:法术处理
int cast_done( object me )
{
        object who;
        string arg;
        int level, rate;        

        if( !stringp( arg = me->get_cast_arg() ) || sscanf(arg, "%s,%d", arg, level) != 2 ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;

        if( !inside_screen_2(me, who) ) return 1;
/*        
        if (who->is_die()==2)
        {
                printf( ECHO "对方已获得救援." );
                return 1;
        }        
*/        
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 3294, 1, OVER_BODY, PF_ONCE );
        who->set_die(2);
        who->set("pf.05114", me);
        who->set("pf.x", get_x(me));
        who->set("pf.y", get_y(me));
        DESC_CMD->main(who, "me");
        write_user( me, HIR "Bạn cứu %s(%d),  hãy chờ đối phương chấp nhận", who->get_name(), who->get_number() );        
        me->to_front_eachother(who);
        return 2;    // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_CHAR; }

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
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/8+1);
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
	send_user(me, "%c%w%w%c%c%c%c%c%s", 0x64, THIS_PERFORM, SUB_MP, 1, 10*10, MAGIC_ACT_BEGIN, 0, 5, "Hồi Thiên Tâm Pháp");
}
