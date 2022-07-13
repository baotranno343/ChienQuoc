
// 法术＋出招  TIPS:[PF_CAST_HIT]  变异

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0241
#define THIS_PERFORM    02419
#define PF_START       "02419"
#define PF_TIME        "02419#"
#define PF_NAME        "Phi Hồng Vô Tích"

#define SKILL_LEVEL     150
#define TIME_INTERVAL   0
#define SUB_MP        	0
#define SUB_YUAN        10
#define ADD_AP          0

int SKILL_LEVEL_SQUARE = SKILL_LEVEL * (SKILL_LEVEL - 1);

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 150 cấp\n    Tuyệt kĩ đã thất truyền từ lâu của Cấm Vệ Quân,xuất hồn lìa khỏi xác truy sát đối thủ, gây ra sát thương vô cùng lớn và nhả độc làm đối thủ chậm chạp.";
		result = sprintf(HIY" %s \n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Tuyệt kĩ đã thất truyền từ lâu của Cấm Vệ Quân,xuất hồn lìa khỏi xác truy sát đối thủ, gây ra sát thương vô cùng lớn và nhả độc làm đối thủ chậm chạp.", 
        	PF_NAME, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL);
        return result;	
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
		object *char, *char2;
		int z, d, x0, y0;
        int level, mp, ret,enmity;
		int f1, f2, f3, f4, act, pf;
		int i, size, size2;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
		if (me->get_save("02419")==0) return 1;
		
        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 level

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng “ %s ”cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

        if( me->get_yuan() < SUB_YUAN )
        {
                printf( ECHO "Sử dụng “ %s ”cần %d điểm Nguyên khí.", PF_NAME, SUB_YUAN );
                return 1;
        }

        if( me->get_weapon_code() == UNARMED ) 
        {
                printf( ECHO "Sử dụng “ %s ” phải trang bị binh khí.", PF_NAME );
                return 1;
        }
/*	z = get_z(me);
        if( who )
        {
                if( !inside_screen_2(me, who) ) return 1;

                x = get_x(who);  y = get_y(who);
        }
        else if( objectp( who = me->get_enemy_2() ) && inside_screen_2(me, who) )
        {
                x = get_x(who);  y = get_y(who);
        }
 //       else
		//return 1;
/*	if (get_z(who)!=z) return;
	x0 = get_x(me);
	y0 = get_y(me);
        if (me->get_gender()==2) send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 2, 60, get_d(me), 0 );
        else send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 60, get_d(me), 0 );
		if( !from_to(z, x0, y0, x - x0, y - y0, MAP_BLOCK ) ) return 0;*/

        me->set_enemy_2(who);    // 远程目标锁定

        me->add_mp(-mp);
        me->add_yuan( -SUB_YUAN );
//		set_heart_state(me, MAGIC_STAT);
//		set_heart_count_2(me, 9);

/*	if (me->get_gender()==2)
	{
        	if( !CHAR_FIGHT_D->attack_action(me, who, 3070, 10) ) return 1;
        }
        else
	{
        	if( !CHAR_FIGHT_D->attack_action(me, who, 1070, 10) ) return 1;
        }
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );      
        me->set_perform( PF_START, time() );
        

        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%d%w%w%d%w%c%c%w%c%c", 0x8a, getoid(me), time2(),
                get_x(me), get_y(me), getoid(who), 25161, 1, OVER_BODY  );

        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 51141, 1, OVER_BODY, PF_ONCE );*/
		z = get_z(me);  x0 = get_x(me);  y0 = get_y(me);

        if (me->get_gender()==2) send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 2, 60, get_d(me), 0 );
        else send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 60, get_d(me), 0 );
        
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 23169, 1, OVER_BODY, PF_ONCE );


/*        size = 1;
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
	}*/

        me->set("pf.02316", char2);
        f1 = me->get_armor_code();  f2 = me->get_head_code();  f3 = me->get_weapon_code_2();  f4 = me->get_reincarnation();
        act = 1;

//        for( i = 0, size = sizeof(char2); i < size; i ++ ) if( who = char2[i] )
 //       {
                x = get_x(who);  y = get_y(who);  d = get_front_xy(x0, y0, x, y);
		send_user( get_scene_object_2(who, USER_TYPE), "%c%w%w%d%w%w%c%d%w%c%c%c", 0x88, x0, y0, time2(), x, y, d, f1, f3, act, f4, 1 );
		send_user( get_scene_object_2(who, USER_TYPE), "%c%w%w%d%w%w%c%d%w%c%c%c", 0x88, x0, y0, time2(), x, y, d, f1, f3, act, f4, 1 );
		send_user( get_scene_object_2(who, USER_TYPE), "%c%w%w%d%w%w%c%d%w%c%c%c", 0x88, x0, y0, time2(), x, y, d, f1, f3, act, f4, 1 );
		send_user( get_scene_object_2(who, USER_TYPE), "%c%w%w%d%w%w%c%d%w%c%c%c", 0x88, x0, y0, time2(), x, y, d, f1, f3, act, f4, 1 );
		send_user( get_scene_object_2(who, USER_TYPE), "%c%w%w%d%w%w%c%d%w%c%c%c", 0x88, x0, y0, time2(), x, y, d, f1, f3, act, f4, 1 );
		send_user( get_scene_object_2(who, USER_TYPE), "%c%w%w%d%w%w%c%d%w%c%c%c", 0x88, x0, y0, time2(), x, y, d, f1, f3, act, f4, 1 );
   //     }

        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP, 0, 0, 0, 10);    // 小心准备 me
		ret += CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP, 0, 0, 0, 10);    // 小心准备 me
		ret += CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP, 0, 0, 0, 10);    // 小心准备 me
		ret += CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP, 0, 0, 0, 10);    // 小心准备 me
		ret += CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP, 0, 0, 0, 10);    // 小心准备 me
		ret += CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP, 0, 0, 0, 10);    // 小心准备 me
		ret += CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP, 0, 0, 0, 10);    // 小心准备 me

        if ( who && !who->is_die() )
        {
        	enmity = 320 + (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/10*120 + ret ;
        	CHAR_FIGHT_D->set_enmity(me,who,enmity);
        }

		me->set_enemy_3(who);
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->add_2("go_count.count2", 5);
        if (!who) return 1;
//        if (who->is_anti_effect()) return 1;
//        if ( !who->get("anti_slow") &&  ret>0)
        {
//	        if(     get_effect(who, EFFECT_CHAR_SLOW)
//	        ||      get_effect(who, EFFECT_CHAR_SLOW_0) ) return 2;    // 执行成功
			if(     get_effect(who, EFFECT_CHAR_SLOW_0)   ) return 2;
                set_effect(who, EFFECT_CHAR_SLOW, 5);
                send_user( who, "%c%w%w%c", 0x81, 9012, get_effect_3(who, EFFECT_CHAR_SLOW), EFFECT_BAD );
                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9012, 1, EFFECT_BAD );
                send_user(who, "%c%c%c", 0x3d, 241, 1);    // 更改走路步数
        }        

        return 1;
}

// 函数：特殊技处理
int cast_done( object me )
{
		object *char, who;
        string arg;
        int level, mp, rate, i, size;        
/*
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );      
        me->set_perform( PF_START, time() );
        
        who = me->get_enemy_3();
        if (!who) return 1;
        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%d%w%w%d%w%c%c%w%c%c", 0x8a, getoid(me), time2(),
                get_x(me), get_y(me), getoid(who), 21175, 1, OVER_BODY  );
        

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;


        if( me->get_weapon_code() != UNARMED ) 
        {
                printf( ECHO "使用“" PF_NAME "”得装备拳套。" );
                return 1;
        }

        me->set_perform_file(0);
//      send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_STOP );    // 删除聚气

        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 21171, 1, OVER_BODY, PF_ONCE );

//      if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功

        CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP, 0, 0, 0, 10);    // 小心准备 me
*/
        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数：能否使用特技
void can_perform( object me )
{
        int level, interval, interval2;
		if (me->get_save("02419")==0) return;
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
        if( me->get_gender()==1)
        	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 10, 1, 70, 5, 0);
        else
        	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 10, 3, 70, 5, 0);                
}

int perform_action_npc(object me, object who)
{
        int z, d, x0, y0;
        int level, mp, ret,enmity;

        me->set_enemy_2(who);    // 远程目标锁定

        if( !CHAR_FIGHT_D->attack_action(me, who, 3070, 10) ) return 1;

        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%d%w%w%d%w%c%c%w%c%c", 0x8a, getoid(me), time2(),
                get_x(me), get_y(me), getoid(who), 21175, 1, OVER_BODY  );
        
        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 21171, 1, OVER_BODY, PF_ONCE );

        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP, 0, 0, 0, 10);    // 小心准备 me
		ret += CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP, 0, 0, 0, 10);    // 小心准备 me
		ret += CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP, 0, 0, 0, 10);    // 小心准备 me
		ret += CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP, 0, 0, 0, 10);    // 小心准备 me
		ret += CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP, 0, 0, 0, 10);    // 小心准备 me
		ret += CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP, 0, 0, 0, 10);    // 小心准备 me
		ret += CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP, 0, 0, 0, 10);    // 小心准备 me

        if ( who && !who->is_die() )
        {
        	enmity = 100 + (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/10*10 ;
        	CHAR_FIGHT_D->set_enmity(me,who,enmity);
        }
        me->set_enemy_3(who);
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        if (!who) return 1;
//        if (who->is_anti_effect()) return 1;
 //       if ( !who->get("anti_slow") &&  ret>0)
        {
//	        if(     get_effect(who, EFFECT_CHAR_SLOW)
//	        ||      get_effect(who, EFFECT_CHAR_SLOW_0) ) return 2;    // 执行成功
			if(     get_effect(who, EFFECT_CHAR_SLOW_0)   ) return 2;
                set_effect(who, EFFECT_CHAR_SLOW, 10);
                send_user( who, "%c%w%w%c", 0x81, 9012, get_effect_3(who, EFFECT_CHAR_SLOW), EFFECT_BAD );
                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9012, 1, EFFECT_BAD );
                send_user(who, "%c%c%c", 0x3d, 241, 1);    // 更改走路步数
        }        

        return 1;
}