
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <action.h>

#define THIS_SKILL      0281
#define THIS_PERFORM    02814
#define PF_START       "02814"
#define PF_TIME        "02814#"
#define PF_NAME        "Ngạo Tuyết Tiêu Sương"

#define SKILL_LEVEL     150
#define TIME_INTERVAL   15
#define SUB_MP          ( 1000 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 150 * 1 )
#define ADD_HP          ( 10000 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 150 * 500000 )


// 函数：获取符法效果
int get_cast_seal() { return 9101; }    // 符纸顺旋

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 150 cấp\n    Tuyệt kỹ tối cao Vân Mộng Cốc,Truy kích 1 mục tiêu với Nội kình hút lấy đối thủ liên tục 5 giây và khiến đối thủ bị làm chậm 100 giây.";
        cur_level = (level - SKILL_LEVEL)/150 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Tuyệt kỹ tối cao Vân Mộng Cốc,Truy kích 1 mục tiêu với Nội kình hút lấy %d Khí Huyết đối thủ liên tục 5 giây và khiến đối thủ bị làm chậm 5 giây.\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Liên tục 5 giây hấp thụ %d Khí Huyết đối thủ。", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_HP, cur_level*150+SKILL_LEVEL, ADD_HP + 500000 );
        return result;  
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        object *user;
        int z;
        int level, mp;


        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
		if (me->get_save("02814")==0) return 1;
		
        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng “ %s ”cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

        if( who )
        {
                if( !inside_screen_2(me, who) ) return 1;

                x = get_x(who);  y = get_y(who);
        }
        else if( objectp( who = me->get_enemy_2() ) && inside_screen_2(me, who) )
        {
                x = get_x(who);  y = get_y(who);
        }
        else
        {
                z = get_z(me);

                if( !inside_screen( get_x(me), get_y(me), x, y ) ) return 1;
                if( !objectp( who = get_xy_object(z, x, y, CHAR_TYPE) ) && !objectp( who = get_xy_object(z, x, y, USER_TYPE) ) ) 
                {
                        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
                        me->set_time( "pf", time() );

                        me->to_front_xy(x, y);
                        user = get_scene_object_2(me, USER_TYPE);
                        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
                        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );
                        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

                        me->add_mp(-mp);

                        set_heart_state(me, MAGIC_STAT);
                        set_heart_count_2(me, 5);
                        me->add_2("go_count.count2",5);
                        me->set_cast_file(__FILE__);
                        me->set_cast_arg( sprintf( "%d,%d,%d", z, x, y ) );

                        return 1;
                }
        }
        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功
	if ( who->get("anti_slow") ) return 2;

        me->set_enemy_2(who);    // 远程目标锁定

        me->to_front_xy(x, y);
        user = get_scene_object_2(me, USER_TYPE);
        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

        me->add_mp(-mp);
        if ( who && !who->is_die() )
        	CHAR_FIGHT_D->set_enmity(me,who,80);
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->add_2("go_count.count2",5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s,%d", who->get_char_id(), level ) );
        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 
                5011, 1, OVER_BODY, PF_LOOP );        

        set_effect_2(me, EFFECT_PROGRESS, 5, 0);
        me->set_progress_file(__FILE__);
        me->set_progress_arg(who->get_char_id());
        me->set_enemy(0);
        send_user(me, "%c%c%w%s", 0x5a, 0, 5, "……Ngạo Tuyết……");
        set_effect(who, EFFECT_CHAR_SLOW, 5);
        send_user(who, "%c%c%c", 0x3d, 241, 1);    // 更改走路步数
        send_user(me, "%c", 0x01);
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        return 2;    // 执行成功
}


void into_effect(object me, string arg)
{
	object who, owner, *all, *team, target;
	int add, time, i, size, x, y, z;
	if (!arg) return;
	if( !objectp( who = find_char(arg) ) ) 
	{
		send_user(me, "%c%c%c", 0x5a, 1, 1);
		if( !get_effect(me, EFFECT_PROGRESS) ) return;
		set_effect_2(me, EFFECT_PROGRESS, 1, 1);
		return;
	}
	if (get_z(me)!=get_z(who)) 
	{
		send_user(me, "%c%c%c", 0x5a, 1, 1);
		if (!get_effect_3(who, EFFECT_CHAR_INVISIBLE))
			send_user(who, "%c%c%c", 0x3d, 241, 2);    // 更改走路步数
		if( !get_effect(me, EFFECT_PROGRESS) ) return;
		set_effect_2(me, EFFECT_PROGRESS, 1, 1);
		return;
	}
	if (abs(get_x(me)-get_x(who))>10||abs(get_y(me)-get_y(who))>10)
	{
		if( !get_effect(me, EFFECT_PROGRESS) ) return;
		set_effect_2(me, EFFECT_PROGRESS, 1, 1);
		return;
	}
	if (who->is_die())
	{
		__FILE__->effect_break(me, who->get_char_id());
		return ;
	}
	add = ADD_HP;	
	target = who;
	time = get_effect(who, EFFECT_CHAR_IMMORTAL);
	if (who->get_hp()<add && time>0)
	{
		set_effect(who, EFFECT_CHAR_IMMORTAL, 0);
	}
	if (who->is_nianshou())
	{
                send_user( me, "%c%s", '!', "你的伎俩对年兽是不起作用的。");
		add =0;
	}
	if (who->is_npc()) owner = who->get_owner();
	else owner = who;
        if (owner) send_user( owner, "%c%d%w%c%d%w%c", 0x48, getoid(who), add, get_d(who), getoid(me),
                0, 1 );
	send_user( me, "%c%d%w%c%d%w%c", 0x48, getoid(who), add, get_d(who), getoid(me),
                0, 1 );
        if( who->is_npc() )
        {
                if( who->get_enemy_4() == me )
                        who->set_attack_time( time() );    // 同一个人：更新持续时间
                else if( gone_time( who->get_attack_time() ) > 12 )
                {
                        who->set_enemy_4(me);
                        who->set_attack_time( time() );    // 不同的人：更新持续敌手
                }
                if( !who->get_max_damage() && who->get_action_mode()==1 ) who->init_enemy_damage(me, 0);    // 记录最强伤害(NPC)
        }                
	CHAR_DIE_D->is_enemy_die(me, who, add);
	if (time>0 && who) set_effect(who, EFFECT_CHAR_IMMORTAL, time);
	send_user( ({ me, owner }), "%c%d%w", 0x68, getoid(me), -add );
	if (!who) return;
	
        all = me->get_team();
        if (all==0) all = ({ me });
        all -= ({ 0 });
        size = sizeof(all);
        z = get_z(me), x = get_x(me), y = get_y(me);
        team = ({ });
        for (i=0;i<size;i++)
        {
        	if (all[i]==me) team += ({ all[i] });
        	else
        	if (z==get_z(all[i])&& abs(x-get_x(all[i]))<9 && abs(y-get_y(all[i]))<9)
        		team += ({ all[i] });
        }	
	size = sizeof(team);
	add /= size;
	for (i=0;i<size;i++)
	{
		who = team[i];
	        if (!who->no_recover() && !get_effect_3(who, EFFECT_USER_BURN)) 
	        {
	        	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w", 0x68, getoid(who), -add );
	        	who->add_hp(add);  
	        }
	} 	        	
	if( !get_effect(me, EFFECT_PROGRESS) ) 
	{
		if (target)
        	send_user( get_scene_object_2(target, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(target), 
                	5011, 1, OVER_BODY, PF_STOP );		
		send_user(me, "%c%c%c", 0x5a, 1, 1);
        	if (who )
        	{
        		set_effect(who, EFFECT_CHAR_SLOW, 0);
        		if (!get_effect_3(who, EFFECT_CHAR_INVISIBLE))
        			send_user(who, "%c%c%c", 0x3d, 241, 2);    // 更改走路步数		
        	}
	}
}

void effect_break(object me, string arg)
{
	object who, owner;
	int add, time;
	if (!arg) return;
	who = find_char(arg);
	if (!who) return;
        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 
               	5011, 1, OVER_BODY, PF_STOP );		
	send_user(me, "%c%c%c", 0x5a, 1, 0);
	set_effect_2(me, EFFECT_PROGRESS, 0, 0);	
}

// 函数：获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数：能否使用特技
void can_perform( object me )
{
        int interval;
        string name;
		if (me->get_save("02814")==0) return;
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
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0,10, MAGIC_ACT_BEGIN, 0, 5, 0);
}
