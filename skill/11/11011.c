#include <ansi.h>
#include <action.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <cmd.h>

#define THIS_SKILL      11011
#define THIS_PERFORM    11011
#define PF_NAME        "Bách Vạn Lôi Minh"

int perform_action_npc( object me, object who )
{
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        set_heart_state(me, MAGIC_STAT);
	me->set_attack_speed(80);
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9102, 1, UNDER_FOOT, PF_LOOP );
	SAY_CMD->say(me, "Loài người ngu xuẩn!!Bổn Vương muốn các ngươi nếm mùi địa ngục!"); 

        set_effect_2(me, EFFECT_PROGRESS, 4, 2);
        me->set_progress_file(__FILE__);
        me->set_enemy(0);

        return 1;
}

void into_effect(object me, string arg)
{
        object *user, *char, who;
        int z, x, y,*xy,x0,y0,p;
        int level, mp, rate, i, size;

        z = get_z(me);  x = get_x(me);  y = get_y(me);
	xy = ({});
	size=0;
	for(i=0;i<121;i++)		//发送效果
        {
        	x0 = x+random(10)-7;
        	y0 = y+random(10)-7;
        	if ( x0<=0 || y0<=0 )
        		continue;
        	p = x0*1000+y0;
        	if ( member_array(p,xy) != -1 )
        		continue;
        	xy+=({p,});
        	size++;
                send_user( get_scene_object(z, x0, y0, USER_TYPE), "%c%w%w%w%c%c%w%c%c%c", 0x4f, x0, y0, 
                        25161, 1, OVER_BODY, 25162, 1, OVER_BODY, PF_ONCE );
		if ( size>=5 )
			break;                  
        }
        char = get_range_object(z, x, y, 4, USER_TYPE) + get_range_object(z, x, y, 4, CHAR_TYPE) - ({ me });
        for( i = 0, size = sizeof(char); i < size; i ++ ) if( who = char[i] ) 
        {
                if( !who->can_be_fighted(me) || !me->can_fight(who) ) continue;
                CHAR_FIGHT_D->cast_done(me, who);
        }	
	if( !get_effect_3(me, EFFECT_PROGRESS) ) 
	{
		me->set_attack_speed(10);
		send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );
		send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9102, 1, UNDER_FOOT, PF_STOP );
	}
}