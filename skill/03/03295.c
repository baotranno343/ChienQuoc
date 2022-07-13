
// 自用持续技能  TIPS:[PF_SELF_LOOP]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0329
#define THIS_PERFORM    03295
#define PF_START       "03295"
#define PF_TIME        "03295#"
#define PF_NAME        "Chu Thiên Cường Hoá"

#define SKILL_LEVEL     19
#define TIME_INTERVAL   2
#define SUB_MP          100 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/11*40
#define ADD_AP		30 + (me->get_skill(THIS_SKILL) - 8)/11*22

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 19 cấp\n    Cường Hoá pháp thuật Tiểu Chu Thiên, đồng thời khi thi triển Tiểu Chu Thiên có thể chỉ sử dụng 1 lần là có thể buff cho tất cả thành viên trong nhóm trong phạm vi nhìn thấy.";
        cur_level = (level - SKILL_LEVEL)/11 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Vật phẩm tiêu hao： Chu Thiên Tâm Pháp \n    Chu thiên pháp chú có khả năng gia tăng %d Ngoại Kháng và Nội Kháng của bản thân và toàn Nhóm trong 15 phút.\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Chu thiên pháp chú có khả năng gia tăng %d Ngoại Kháng và Nội Kháng của bản thân và toàn Nhóm trong 15 phút.",
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_AP, cur_level*11+SKILL_LEVEL, ADD_AP+22 );
	return result;
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, interval, mp, z, add, level2;
        object *user, owner, item;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
        if (me->get_save("03295")==0) return 1;

        interval = TIME_INTERVAL;

        if( gone_time( me->get_perform(PF_START) ) < interval ) return 1;    // 小心准备 level

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }
        if( get_effect(me, EFFECT_CHAR_NO_PF) ) 
        {
        	notify( "Ngươi bị trúng trạng thái phong ấn." );
        	return 1;
        }        
        if( !objectp( item = present("Chu Thiên Tâm Pháp", me, 1, MAX_CARRY*4) ) )
        {
                printf( ECHO "Phải có Chu Thiên Tâm Pháp mới có thể sử dụng \"" PF_NAME "\"." );
                return 1;
        }  
        item->add_amount(-1);        
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );

        me->add_mp(-mp);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->add_2("go_count.count2",5);
        me->set_cast_file(__FILE__);
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
	return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        int level, interval, mp, x, y, z, add, level2, i, size;
        object *user, who, owner, *char;
        string arg;
        interval = 900;

        me->set_perform( PF_TIME, interval );
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 3292, 1, OVER_BODY, PF_ONCE );        
        z = get_z(me), x = get_x(me), y = get_y(me);
        char = get_range_object(z, x, y, 20, USER_TYPE) + get_range_object(z, x, y, 20, CHAR_TYPE);        
        size = sizeof(char);
	for (i=0;i<size;i++) if (who = char[i])
	{
		if (who->is_anti_effect()) continue;
		if (who->is_user() && (me!=who))
		{
			if (!me->get_leader()||me->get_leader()!=who->get_leader()) continue;
		}
		if (who->is_npc())
		{
			owner = who->get_owner();
			if (!owner) continue;
			if (!me->get_leader()||me->get_leader()!=owner->get_leader()) continue;
		}
	        level2 = who->get_level();
	        if ( level > level2+8) add = ADD_AP - (level-level2-8)/11*22;
	        else add = ADD_AP;
		user = get_scene_object_2(who, USER_TYPE);
		if (add >= who->get_save("03291#") && add >= who->get("03291#"))
		{
			set_effect(who, EFFECT_USER_DP, interval);
			send_user( who, "%c%w%w%c", 0x81, 3291, get_effect_3(who, EFFECT_USER_DP), EFFECT_GOOD );
			send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 3291, 1, EFFECT_GOOD );
			
			if (who->is_user()) 
			{
				who->set_save("03291#", add);
				USER_ENERGY_D->count_dp(who);
			}
			else
			{
				who->add_dp(-who->get("03291#"));
				who->set("03291#", add);
				who->add_dp(add);
			}
		}
		if (add >= who->get_save("03292#") && add >= who->get_save("03292#"))
		{
			set_effect(who, EFFECT_USER_PP, interval);
			send_user( who, "%c%w%w%c", 0x81, 3292, get_effect_3(who, EFFECT_USER_DP), EFFECT_GOOD );
			send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 3292, 1, EFFECT_GOOD );
			
			if (who->is_user()) 
			{
				who->set_save("03292#", add);
				USER_ENERGY_D->count_pp(who);
			}
			else
			{
				who->add_pp(-who->get("03292#"));
				who->set("03292#", add);
				who->add_pp(add);			
			}
		}
		send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 32511, 1, OVER_BODY, PF_ONCE );
	}
        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_ME; }

// 函数：能否使用特技
void can_perform( object me )
{
        int interval;
        string name;
        if (me->get_save("03295")==0) return;
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
	send_user(me, "%c%w%w%c%c%c%c%c%s", 0x64, THIS_PERFORM, SUB_MP, 1, 1, MAGIC_ACT_BEGIN, 0, 5, "Chu Thiên Tâm Pháp");
}

void effect_done(object me)
{
	if (me->is_user())
	{
		me->set_save("03291#", 0);
		USER_ENERGY_D->count_dp(me);
	}
	else
	{
		me->add_dp(-me->get("03291#"));
		me->set("03291#", 0);					
	}
        send_user( me, "%c%w%w%c", 0x81, 3291, 0, EFFECT_GOOD );
        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3291, 0, EFFECT_GOOD );

}

void effect_done2(object me)
{
	if (me->is_user())
	{
		me->set_save("03292#", 0);
		USER_ENERGY_D->count_pp(me);
	}
	else
	{
		me->add_pp(-me->get("03292#"));
		me->set("03292#", 0);
					
	}	
        send_user( me, "%c%w%w%c", 0x81, 3292, 0, EFFECT_GOOD );
        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3292, 0, EFFECT_GOOD );

}