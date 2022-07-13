
// 单体远程技能  TIPS:[PF_CAST]  变异

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0417
#define THIS_PERFORM    04179
#define PF_START       "04179"
#define PF_TIME        "04179#"
#define PF_NAME        "Ảo Ảnh Kiếm Pháp"

#define SKILL_LEVEL     150
#define TIME_INTERVAL   5
#define SUB_MP          200 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 150 * 1
#define ADD_CP		100 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 150 * 10

// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level, size;
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR " %s \n Võ công yêu cầu: Cấp 150\n Tuyệt kĩ kiếm pháp của Mao Sơn, vừa uỷ mị vừa mạnh mẽ tấn công nhiều mục tiêu", PF_NAME);
        cur_level = (level - SKILL_LEVEL)/150 + 1;
        size = 9 + (level/ 80 )*50;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Tuyệt kĩ kiếm pháp vừa uỷ mị vừa mạnh mẽ của Mao Sơn, tăng thêm %d điểm Nội Công khi biến hóa thành vô số ảo ảnh sát thương %d mục tiêu trong tầm nhìn.\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Tăng thêm %d điểm Nội Công，Biến hoá thành %d ảo ảnh sát thương mục tiêu. ", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_CP, size, cur_level*150+SKILL_LEVEL, ADD_CP + 10,  9 + ((cur_level*15+SKILL_LEVEL)/ 80 )*50 );
        return result;	}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        object *char, *char2;
        int z, x0, y0, d;
        int level, mp;
        int f1, f2, f3, f4, act, pf;
        int i, size, size2;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
		if (me->get_save("04179")==0) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 me

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }
        if( get_effect(me, EFFECT_CHAR_NO_PF) ) 
        {
        	notify( "Bạn bị trạng thái phong ấn" );
        	return 1;
        }
        if( me->get_weapon_code() != SWORD )
//		if( me->get_weapon_code() != BLADE )
        {
                printf( ECHO "Sử dụng\"" PF_NAME "\" phải trang bị kiếm" );
                return 1;
        }

        z = get_z(me);  x0 = get_x(me);  y0 = get_y(me);

        if (me->get_gender()==2) send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 2, 60, get_d(me), 0 );
        else send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 60, get_d(me), 0 );
        
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 23169, 1, OVER_BODY, PF_ONCE );

        me->add_mp(-mp);

        size = 9 + (level/ 80 )*50;
        size2 = size;

        char = get_range_object(z, x0, y0, 20, USER_TYPE) + get_range_object(z, x0, y0, 20, CHAR_TYPE);    // 7 x 7 随机

        char = char - ({ me }) ;
        char2 = copy(char);
        for( i = 0, size = sizeof(char); i < size; i ++ ) if( who = char[i] )
        {
        	if( !who->can_be_fighted(me) || !me->can_fight(who) )
        		char2 -= ({ who });
        }
	size = sizeof(char2);
	if (size>size2)
	{
		size = size - size2;
		for( i = 0; i < size; i ++ ) char2 -= ({ char2[ random( sizeof(char2) ) ] });
	}

        me->set("pf.02316", char2);
        f1 = me->get_armor_code();  f2 = me->get_head_code();  f3 = me->get_weapon_code_2();  f4 = me->get_reincarnation();
        act = 1;

        for( i = 0, size = sizeof(char2); i < size; i ++ ) if( who = char2[i] )
        {
                x = get_x(who);  y = get_y(who);  d = get_front_xy(x0, y0, x, y);
		send_user( get_scene_object_2(who, USER_TYPE), "%c%w%w%d%w%w%c%d%w%c%c%c", 0x88, x0, y0, time2(), x, y, d, f1, f3, act, f4, 1 );
	//	send_user( get_scene_object_2(who, USER_TYPE), "%c%w%w%d%w%w%c%d%w%c%c%c", 0x88, x0, y0, time2(), x, y, d, f1, f3, act, f4, 1 );
	//	send_user( get_scene_object_2(who, USER_TYPE), "%c%w%w%d%w%w%c%d%w%c%c%c", 0x88, x0, y0, time2(), x, y, d, f1, f3, act, f4, 1 );
	//	send_user( get_scene_object_2(who, USER_TYPE), "%c%w%w%d%w%w%c%d%w%c%c%c", 0x88, x0, y0, time2(), x, y, d, f1, f3, act, f4, 1 );
	//	send_user( get_scene_object_2(who, USER_TYPE), "%c%w%w%d%w%w%c%d%w%c%c%c", 0x88, x0, y0, time2(), x, y, d, f1, f3, act, f4, 1 );
	//	send_user( get_scene_object_2(who, USER_TYPE), "%c%w%w%d%w%w%c%d%w%c%c%c", 0x88, x0, y0, time2(), x, y, d, f1, f3, act, f4, 1 );
	//	send_user( get_scene_object_2(who, USER_TYPE), "%c%w%w%d%w%w%c%d%w%c%c%c", 0x88, x0, y0, time2(), x, y, d, f1, f3, act, f4, 1 );
        }

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
          me->add_2("go_count.count2",5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%d", level ) );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        return 1;
}

// 函数:法术处理
int cast_done( object me )
{
        object *char, who;
        string arg;
        int level, i, size, ret;        

        if( !stringp( arg = me->get_cast_arg() ) || sscanf(arg, "%d", level) != 1 ) return 1;

        if( !arrayp( char = me->get("pf.02316") ) ) return 2;    // 执行成功

        for( i = 0, size = sizeof(char); i < size; i ++ ) 
                if( who = char[i] ) 
                {
                	ret = CHAR_FIGHT_D->cast_done(me, who, ADD_CP);
					ret += CHAR_FIGHT_D->cast_done(me, who, ADD_CP);
					ret += CHAR_FIGHT_D->cast_done(me, who, ADD_CP);
                        if ( who && !who->is_die() )
        			CHAR_FIGHT_D->set_enmity(me,who,100);	
                }

        return 2;    // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_ME; }

// 函数:能否使用特技
void can_perform( object me )
{
        int interval;
        string name;
		if (me->get_save("04179")==0) return;
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
				if( me->get_gender()==1)
        	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 1, 1, 1, 60, 5, 0);
        else
        	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 1, 1, 2, 60, 5, 0);
}
