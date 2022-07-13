
// 法术＋出招  TIPS:[PF_CAST_HIT]  变异

#include <ansi.h>
#include <action.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0242
#define THIS_PERFORM    02424
#define PF_START       "02424"
#define PF_TIME        "02424#"
#define PF_NAME        "Trấn Cổ Địch Độc"

#define SKILL_LEVEL     150
#define TIME_INTERVAL   30
#define SUB_MP        	0 
#define ADD_EFFECT     	( 20000 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/150 * 100000 ) 

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 150 cấp\n    Dịch độc lan toả nhanh chóng,Độc tính cực mạnh phá huỷ lục phủ ngũ tạng địch thủ xung quanh。";
        cur_level = (level - SKILL_LEVEL)/150 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp lực tiêu hao：%d điểm\n Tái sử dụng sau: %d giây\n    Dịch độc lan toả nhanh chóng,%d Độc tính cực mạnh phá huỷ lục phủ ngũ tạng và làm chậm địch thủ xung quanh。\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Tăng %d độc tính。", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_EFFECT, cur_level*150+SKILL_LEVEL, ADD_EFFECT + 20000);     	
        return result;
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int z, i, size, d, x0, y0, poison;
        int level, mp, ret;
        object *char, item,item1;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
		if (me->get_save("02424")==0) return 1;
		
        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 level

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng “ %s ”cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }
        if( !objectp( item = present("Thạch Tín", me, 1, MAX_CARRY*4) ) )
        {
                printf( ECHO "Sử dụng “ %s ” phải có Thạch Tín“" PF_NAME );
                return 1;
        }
	poison = item->get_poison() + ADD_EFFECT;
        me->add_mp(-mp);
        item->add_amount(-0);
        if( objectp( item1 = me->get_equip(WEAPON_TYPE) ) && item1->get_name()=="Bích Hỏa Hàn Nguyệt Hoàn" ) 
        	poison += 1000;
        if( objectp( item1 = me->get_equip(WEAPON_TYPE) ) && item1->get_name()=="Thần Tiên Hạc Kim" ) 
        	poison += 3000;
	CHAR_FIGHT_D->set_enmity1(me,40);
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 3637, 1, OVER_BODY, PF_ONCE );
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        z = get_z(me);
        x = get_x(me);
        y = get_y(me);
        char = get_range_object(z, x, y, 20, USER_TYPE) + get_range_object(z, x, y, 20, CHAR_TYPE) - ({ me });
        for( i = 0, size = sizeof(char); i < size; i ++ ) if( who = char[i] )
        {	        
        	if (who->is_anti_effect()) continue;
                if ( random(100) < who->get_anti_poison() ) continue;
		if( who->can_be_fighted(me) && me->can_fight(who) ) 
		{						
                        who->set_poison( poison / 10 );
                        set_effect_2(who, EFFECT_CHAR_POISON, 5, 0);
                        send_user( who, "%c%w%w%c", 0x81, 9096, get_effect_3(who, EFFECT_CHAR_POISON), EFFECT_BAD );
                        send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9096, 1, EFFECT_BAD );
		        if ( who->get("anti_slow") ) continue;
		        if(     get_effect(who, EFFECT_CHAR_SLOW)
		        ||      get_effect(who, EFFECT_CHAR_SLOW_0) ) continue;
	                set_effect(who, EFFECT_CHAR_SLOW, 30);
	                set_effect(who, EFFECT_CHAR_SLOW_0, 32);
	                send_user( who, "%c%w%w%c", 0x81, 9012, get_effect_3(who, EFFECT_CHAR_SLOW), EFFECT_BAD );
	                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9012, 1, EFFECT_BAD );
	                send_user(who, "%c%c%c", 0x3d, 241, 1);    // 更改走路步数                        
		}        	
        }        
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 7);
        me->add_2("go_count.count2",7);

        return 1;
}

// 函数：特殊技处理
int cast_done( object me )
{
	object who;
        int level, mp, rate;

        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_ME; }

// 函数：能否使用特技
void can_perform( object me )
{
        int level, interval, interval2;
		
		if (me->get_save("02424")==0) return;
		
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
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0, 1, MAGIC_ACT_BEGIN, 0, 7, 0);
}

int perform_action_npc( object me, object who)
{
        int x,y,z, i, size, d, x0, y0, poison;
        int level, mp, ret;
        object *char;

	poison = ADD_EFFECT;
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 3637, 1, OVER_BODY, PF_ONCE );
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        z = get_z(me);
        x = get_x(me);
        y = get_y(me);
        char = get_range_object(z, x, y, 20, USER_TYPE) + get_range_object(z, x, y, 20, CHAR_TYPE) - ({ me });
        for( i = 0, size = sizeof(char); i < size; i ++ ) if( who = char[i] )
        {	        
        	if (who->is_anti_effect()) continue;
                if ( random(100) < who->get_anti_poison() ) continue;
		if( who->can_be_fighted(me) && me->can_fight(who) ) 
		{						
                        who->set_poison( poison / 10 );
                        set_effect_2(who, EFFECT_CHAR_POISON, 5, 0);
                        send_user( who, "%c%w%w%c", 0x81, 9096, get_effect_3(who, EFFECT_CHAR_POISON), EFFECT_BAD );
                        send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9096, 1, EFFECT_BAD );
		        if ( who->get("anti_slow") ) continue;
		        if(     get_effect(who, EFFECT_CHAR_SLOW)
		        ||      get_effect(who, EFFECT_CHAR_SLOW_0) ) continue;
	                set_effect(who, EFFECT_CHAR_SLOW, 30);
	                set_effect(who, EFFECT_CHAR_SLOW_0, 32);
	                send_user( who, "%c%w%w%c", 0x81, 9012, get_effect_3(who, EFFECT_CHAR_SLOW), EFFECT_BAD );
	                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9012, 1, EFFECT_BAD );
	                send_user(who, "%c%c%c", 0x3d, 241, 1);    // 更改走路步数                        
		}        	
        }        
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 7);

        return 1;
}

int cast_done_npc( object me )
{
	object who;
        int level, mp, rate;

        return 2;    // 执行成功
}