
// 开关技能  TIPS:[PF_SWITCH]

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0221
#define THIS_PERFORM    02217
#define PF_FLAG        "02217"
#define PF_TIME        "02217#"
#define PF_NAME        "Bá Đao Nộ Hào Khí"

#define SKILL_LEVEL     150
#define TIME_INTERVAL   2
#define SUB_MP          0
#define SUB_YUAN        0
#define ADD_AP		1000 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/150 * 2000

int perform_done( object me, object who );

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR " %s \n Võ công yêu cầu: Cấp 150\n Đao pháp tung hoàng chiến trường như chốn không người, tăng thêm 1000 điểm Ngoại Công và sát thương tất cả mục tiêu xung quanh.", PF_NAME);
        cur_level = (level - SKILL_LEVEL)/150 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Đao pháp tung hoàng chiến trường như chốn không người, tăng thêm %d điểm Ngoại Công và sát thương tất cả mục tiêu xung quanh.\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Tăng thêm %d điểm Ngoại Công。", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL, ADD_AP, cur_level*150+SKILL_LEVEL, ADD_AP + 2000  );
        return result;	
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
		if (me->get_save("02217")==0) return 1;
		
        if( gone_time( me->get_perform(PF_FLAG) ) < TIME_INTERVAL ) return 1;    // 小心准备 me

        if( me->get_yuan() < SUB_YUAN )
        {
                printf( ECHO "Sử dụng “ %s ”cần %d điểm Nguyên khí.", PF_NAME, SUB_YUAN );
                return 1;
        }

        if( me->get_weapon_code() != BLADE )
		if( me->get_weapon_code() != SWORD ) 
        {
                printf( ECHO "Sử dụng “ %s ” phải trang bị binh khí.", PF_NAME );
                return 1;
        }
	me->set_perform( PF_FLAG, time() );
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        
        me->add_yuan( -SUB_YUAN );
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 2, 40, get_d(me), 0 );
	perform_done(me, 0);
        return 1;
}

// 函数：特殊技处理
int perform_done( object me, object who )
{
        object *char;
        int mp, i, size;

	if (me->get_skill(THIS_SKILL)>=61)
        	char = get_range_object_2(me, 20, USER_TYPE) + get_range_object_2(me, 20, CHAR_TYPE) - ({ me });
        else
        	char = get_range_object_2(me, 20, USER_TYPE) + get_range_object_2(me, 20, CHAR_TYPE) - ({ me });

        for( i = 0, size = sizeof(char); i < size; i ++ ) 
                if( who = char[i] ) 
                {
                	if (!who->can_be_fighted(me) || !me->can_fight(who)) continue;
                	CHAR_FIGHT_D->attack_done(me, who, HIT_STICK, ADD_AP);
		        if ( who && !who->is_die() )
		        	CHAR_FIGHT_D->set_enmity(me,who,80);                	
                }
        return 2;    // 执行成功
}

// 函数：命令处理(动作)
int perform_action_npc( object me, object who )
{
        if( !CHAR_FIGHT_D->attack_action(me, who, 2040) ) return 0;

        set_heart_state(me, FIGHT_STAT);
        set_heart_count_2(me, 7);
        me->set_perform_2_file(__FILE__);

        return 1;    // 执行成功
}

// 函数：命令处理
int perform_done_npc( object me, object who )
{
        object *char;
        int i, size;

        if( distance_between(me, who) > 1 ) return 0;

        me->set_perform_2_file(0);

        char = get_range_object_2(me, 1, USER_TYPE) - ({ me });    // + get_range_object_2(me, 1, CHAR_TYPE)

        for( i = 0, size = sizeof(char); i < size; i ++ ) 
                if( who = char[i] ) 
                {
                	CHAR_FIGHT_D->attack_done(me, who, HIT_STICK);
		        if ( who && !who->is_die() )
		        	CHAR_FIGHT_D->set_enmity(me,who,80);	
                }
	me->delete_perform(PF_FLAG);
        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_ME; }

// 函数：能否使用特技
void can_perform( object me )
{
        int interval;
        string name;
		if (me->get_save("02217")==0) return;
        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/10+1);
        send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 1, 2, 40, 7, 0);
}
