
// 法术＋出招  TIPS:[PF_CAST_HIT]  变异

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0212
#define THIS_PERFORM    02122
#define PF_START       "02122"
#define PF_NAME        "Khiêu Trận"

#define SKILL_LEVEL     9
#define TIME_INTERVAL   5
#define SUB_MP        	0
#define SUB_YUAN        4

#define ADD_ENMITY	450 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/10*100

// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 9 cấp\n    Thu hút tất cả quái vật trong phạm vi 9x9 xung quanh không ngừng tấn công mình.";
        result = sprintf(HIC" %s \n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Thu hút tất cả quái vật trong phạm vi 9x9 xung quanh không ngừng tấn công mình.", 
        	PF_NAME, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL);
        return result;
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        int z, i, size, d, x0, y0;
        int level, mp, ret,enmity;
        object *char;

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

        if( me->get_weapon_code() != UNARMED )
        {
                printf( ECHO "Sử dụng \"" PF_NAME "\" phải trang bị triển thủ" );
                return 1;
        }

        me->add_mp(-mp);
        me->add_yuan( -SUB_YUAN );

	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 0, get_d(me), 0 );
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        z = get_z(me);
        x = get_x(me);
        y = get_y(me);
        char = get_range_object(z, x, y, 4, CHAR_TYPE) - ({ me });
        for( i = 0, size = sizeof(char); i < size; i ++ ) if( who = char[i] )
        {	        
		if( who->can_be_fighted(me) && me->can_fight(who) ) 
		{
			ret = CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, 0, 0, -100);    // 小心准备 me	
			if (ret==0) continue;
			if (!who) continue;
			who->set_enemy(me);
//			who->set_main_enemy(me);
//			who->set_enemy_4(me);
//			who->set_attack_time( time() ); 
//			who->init_enemy_damage(me, 1000000); 
//			who->set_fight_time( time() );
			who->set("2122", time());
			who->init_enemy_damage(me, 1); 
			who->follow_user();
			send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 2122, 1, OVER_BODY, PF_ONCE );
			enmity = ADD_ENMITY ;
        		CHAR_FIGHT_D->set_enmity(me,who,enmity);
		}        	
        }        
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 7);
         me->add_2("go_count.count2",7);

        return 1;
}

// 函数:特殊技处理
int cast_done( object me )
{
	object who;
        int level, mp, rate;

        return 2;    // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_ME; }

// 函数:能否使用特技
void can_perform( object me )
{
        int level, interval, interval2;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL )
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }

        interval = TIME_INTERVAL;    // 小心准备 level
        interval2 = interval - gone_time( me->get_perform(PF_START) );
        if( interval2 < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), interval, 0, PF_NAME );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), interval, interval2, PF_NAME );
        send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 1, 1, 0, 7, 0);
}
