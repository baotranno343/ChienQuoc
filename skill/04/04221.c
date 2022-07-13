
// 法术＋出招  TIPS:[PF_CAST_HIT]  变异

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <action.h>

#define THIS_SKILL      0422
#define THIS_PERFORM    04221
#define PF_START       "04221"
#define PF_NAME        "Phá Chú"

#define SKILL_LEVEL     10
#define TIME_INTERVAL   0
#define SUB_MP          0

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 10 cấp\n    Hóa giải 1 bùa chú nguyền rùa trên người đồng đội.";
        result = sprintf(HIC" %s \n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Hóa giải 1 bùa chú nguyền rùa trên người đồng đội.", 
        	PF_NAME, SKILL_LEVEL, SUB_MP, TIME_INTERVAL);
        return result;
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int z, d, x0, y0;
        int level, mp, ret;
        object *user, owner;
        int i, size, time, pos;
        int * all = ({ EFFECT_CHAR_POWERFALL, EFFECT_CHAR_FALL, EFFECT_MP_FALL, EFFECT_CHAR_ARMORFALL, });

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 level

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }
	z = get_z(me);
        if( who )
        {
                if( !inside_screen_2(me, who) ) return 1;
                if (me!=who)
                {
	        	if (who->is_user())
	        	{
		        	if (!me->get_leader()||me->get_leader()!=who->get_leader())
			        {
			                printf( ECHO "Chính mình hoặc đồng đội mới có thể sử dụng " PF_NAME );
			                return 1;
			        }
			}
			else
			{
				owner  = who->get_owner();
				if (owner!=me)
				{
			        	if (!owner || !me->get_leader()||me->get_leader()!=owner->get_leader())
				        {
				                printf( ECHO "Chính mình hoặc đồng đội mới có thể sử dụng " PF_NAME );
				                return 1;
				        }
				}			       			
			}
			if ("/sys/user/attack"->can_use_help(me, who)==0)
			{				
				printf( ECHO "Đối với đối phương không thể sử dụng " PF_NAME );
				return 1;				
			}
		}
                x = get_x(who);  y = get_y(who);
        }
        else
		return 1;
	if (get_z(who)!=z) return;
	x0 = get_x(me);
	y0 = get_y(me);

        me->set_enemy_2(who);    // 远程目标锁定

        me->add_mp(-mp);
       	CHAR_FIGHT_D->set_enmity2(me,who,20);  //设置仇恨值

//      set_heart_state(me, MAGIC_STAT);
//      set_heart_count_2(me, 9);

        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );      
        me->set_perform( PF_START, time() );        

        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 4221, 1, OVER_BODY, PF_ONCE );

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->add_2("go_count.count2",5);
	size = sizeof(all);
	time = 0; pos = -1;
	for (i =0;i<size;i++) if (time < get_effect_3(who, all[i])) 
	{
		time = get_effect_3(who, all[i]);
		pos = i;
	}
	if (pos!=-1)
	{
		if (all[pos]<96) set_effect(who, all[pos], 1);
		else set_effect_2(who, all[pos], 1, 1);
	}
        
        return 1;
}

// 函数：特殊技处理
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
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/10+1);
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0, 10, MAGIC_ACT_BEGIN, 0, 5, 0);
}
