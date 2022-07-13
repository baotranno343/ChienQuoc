
#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      11005
#define THIS_PERFORM    03162
#define PF_START       "03162"
#define PF_TIME        "03162#"
#define PF_TIME1	"02422#"
// Cổ vũ sĩ khí
#define PF_NAME        "鼓舞士气" 

#define SKILL_LEVEL     33
#define TIME_INTERVAL   10
#define SKILL_LEVEL1     20
#define TIME_INTERVAL1   2
#define ADD_AP		10 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/16
#define ADD_TIME	10 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL1)/10

// 函数：命令处理
int perform_03162_npc( object me, object who )
{
        int level, interval, mp, i, size, z,x,y;
        object *user, *team, *all;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        interval =TIME_INTERVAL;

//        if( gone_time( me->get_perform(PF_START) ) < interval ) return 1;    // 小心准备 level

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 3);
        interval = 20 + (level-SKILL_LEVEL)/10;

        me->set_perform( PF_TIME, interval );
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        
	all = ({ me }) + me->get("guard");
        size = sizeof(all);
        z = get_z(me), x = get_x(me), y = get_y(me);
        team = ({ });
        for (i=0;i<size;i++)
        {
		if ( !objectp(all[i]) )
			continue;
        	if (all[i]==me) team += ({ all[i] });
        	else
        	if (z==get_z(all[i])&& abs(x-get_x(all[i]))<9 && abs(y-get_y(all[i]))<9)
        		team += ({ all[i] });
        }
	size = sizeof(team);
	for (i=0;i<size;i++)
	{
		who = team[i];
	        user = get_scene_object_2(who, USER_TYPE);
	        set_effect(who, EFFECT_EXCITE, interval);
	        send_user( who, "%c%w%w%c", 0x81, 3162, get_effect_3(who, EFFECT_EXCITE), EFFECT_GOOD );
	        send_user( user, "%c%d%w%c%c", 0x83, getoid(who), 3162, 1, EFFECT_GOOD );
	        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 3162, 1, OVER_BODY, PF_ONCE );
	        who->set_save(PF_TIME, ADD_AP);
	}        
        return 1;
}

// 函数：命令处理
int perform_02422_npc( object me, object who )
{
        int level, interval, mp, z, add, level2;
        object *user;
        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        interval = TIME_INTERVAL1;

        who = me;
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 3);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s,%d", who->get_char_id(), level ) );
	return 1;
}

// 函数：法术处理
int cast_done_npc( object me )
{
        int level, interval, mp, z, add, level2, i, size, x, y;
        object *user, who, *all, *team;
        string arg;

        interval = ADD_TIME;
        if( !stringp( arg = me->get_cast_arg() ) ) return 2;
        who = me;

        me->set_perform( PF_TIME1, interval );
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );

        add = 20;
        all = ({ me }) + me->get("guard");
        size = sizeof(all);
        z = get_z(me), x = get_x(me), y = get_y(me);
        team = ({ });
        for (i=0;i<size;i++)
        {
		if ( !objectp(all[i]) )
			continue;
        	if (all[i]==me) team += ({ all[i] });
        	else
        	if (z==get_z(all[i])&& abs(x-get_x(all[i]))<9 && abs(y-get_y(all[i]))<9)
        		team += ({ all[i] });
        }
	size = sizeof(team);
	for (i=0;i<size;i++)
	{
		who = team[i];
	        user = get_scene_object_2(who, USER_TYPE);
	        set_effect(who, EFFECT_DODGE, interval);
	        send_user( who, "%c%w%w%c", 0x81, 2422, get_effect_3(who, EFFECT_DODGE), EFFECT_GOOD );
	        send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 2422, 1, EFFECT_GOOD );
	        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 2710, 1, OVER_BODY, PF_ONCE );
	        who->set_save("02422#", add);

	}        		
        return 2;    // 执行成功
}

int perform_action_npc( object me, object who )
{
	if ( random(2) )
	{
		return perform_03162_npc(me,who);
	}
	else
	{
		return perform_02422_npc(me,who);
	}
}