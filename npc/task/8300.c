//红娘任务NPC
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <task.h>
#include <action.h>

inherit NPC;

int hptime;
int summon_slave( object me );

// 函数：
int is_marry_task() { return 1; }

// 函数：是否不能进城
int cannot_enter_city() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "恶霸" + NPC_NAME_D->get_thief_name() );
        set_char_picid(8010);    // 蒙面人
        setup();
	set_max_hp(100);

        set( "birthday", time() );
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：复位处理
void reset() 
{
        object who;
        string *member, id;
        int i, size,iKind;

        if( gone_time( get("birthday") ) >= 3600 )    // 60 分钟
        {
                remove_from_scene();
                destruct( this_object() );
        }

}

// 函数：可以接受战斗
int can_be_fighted( object who ) 
{ 
        object owner;

	if( who->is_npc() && objectp(owner = who->get_owner()) ) who = owner;
	if( who->is_npc() ) return 0;
        if( who->get_enemy() == this_object() ) return 1;

        if( get("marry1") == who->get_number() || get("marry2") == who->get_number() ) return 1;


        send_user( who, "%c%c%w%s", ':', 3, get_char_picid(),  get_name() + ":\n    滚开！别多管闲事！" );
        return 0;
}
int can_fight( object who ) 
{ 
        object owner;
        string leader, id;
	if( who->is_npc() && objectp(owner = who->get_owner()) ) who = owner;
	if( who->is_npc() )
	{
		set_enemy(0);
		return 0;
	}
        if( get("marry1") == who->get_number() || get("marry2") == who->get_number() ) return 1;
	set_enemy(0);
        return 0;
}
// --------------------------------------------------------------- 远程调用 ----

// 函数：死亡奖励
void win_bonus( object who ) { __FILE__ ->win_bonus_callout( this_object(), who ); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout( object me, object who )
{
	object owner,user;
        if( !me->can_be_fighted(who) ) return;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return;

        if( me->get("marry1") != who->get_number() && me->get("marry2") != who->get_number() ) return;
	
	user = find_player(sprintf("%d",who->get_save_2("marry.id")));
	if ( !objectp(user) || !inside_screen_2(me, user) || user->is_die() )
	{
		me->remove_from_scene();
		destruct(me);
		send_user(who,"%c%s",'!',"夫妻任务失败！");
		return;	
	}
	who->set_save_2("marrytask.finish",1);
	user->set_save_2("marrytask.finish",1);
	send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_HONGNIANG,"红娘任务" ); 
	send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_HONGNIANG,1,"教训媒霸(完成)" ); 
	send_user( user, "%c%c%c%w%s", 0x51, 1, 1,TID_HONGNIANG,"红娘任务" ); 
	send_user( user, "%c%c%c%w%w%s", 0x51, 1, 2,TID_HONGNIANG,1,"教训媒霸(完成)" ); 

	me->remove_from_scene(FALL_ACT);
	destruct(me);
	
}

// 函数：特技攻击对手
int perform_action( object who ) 
{
	int rate;
	object me = this_object();
	rate = random(100);	
	switch(me->get("marry.type"))
	{
	case 1:
		if ( rate < 5 )
			return PF_FILE_03483->perform_action_npc(me, who);
		else if ( rate < 17 )
			return PF_FILE_02512->perform_action_npc(me, who);
		else if ( rate < 20 )
			return PF_FILE_02416->perform_action_npc(me, who);			
		break;
	case 2:
		if ( rate < 8 )
			return PF_FILE_02216->perform_action_npc(me, who);
		else if ( rate < 16 )
			return PF_FILE_02313->perform_action_npc(me, who);
		else if ( rate < 24 )
			return PF_FILE_02314->perform_action_npc(me, who);
		break;			
	case 3:
		if ( get_effect(me, EFFECT_CHAR_CHANGE) < 1)
		{
			PF_FILE_04251->cast_done_npc(me);			
		}
		if ( rate < 70 )
			return PF_FILE_04231->perform_action_npc(me, who);
		else if ( rate < 90 )
			return PF_FILE_04232->perform_action_npc(me, who);
		else if ( rate < 97 )
			return PF_FILE_04234->perform_action_npc(me, who);
		else
			return PF_FILE_04243->perform_action_npc(me, who);	
		break;
	case 4:
		if( !me->get_perform("03173") ) 
		{
			PF_FILE_03173->perform_action_npc(me,who);
		}
		if ( rate < 5 )
			return PF_FILE_02118->perform_action_npc(me, who);
		else if ( rate < 13 )
			return PF_FILE_02114->perform_action_npc(me, who);
		else if ( rate < 25 )
			return PF_FILE_02115->perform_action_npc(me, who);
		break;
	case 5:
		if( !me->get_effect(me, EFFECT_USER_HURT) ) 
		{
			PF_FILE_03632->cast_done_npc(me);
		}
		if ( rate < 10 )
			return PF_FILE_02616->perform_action_npc(me, who);
		else if ( rate < 20 )
			return PF_FILE_02615->perform_action_npc(me, who);
		break;
	case 6:
		summon_slave(me);
		if ( rate < 6 )
			return PF_FILE_04143->perform_action_npc(me, who);
		else if ( rate < 12 )
			return PF_FILE_04144->perform_action_npc(me, who);
		else if ( rate < 15 )
			return PF_FILE_04145->perform_action_npc(me, who);
		break;		
	default:
		break;
	}
	return 0;
}

//自动跟踪有任务的玩家
void heart_beat_walk()
{
	string robber;
	object *member,who,owner;
	object me = this_object(),enemy;
	int x,y,z,x0,y0,z0,x1,y1,p,i;

	if ( gone_time(hptime) >= 20+random(21) )
	{
		hptime = time();
		//瞬间移动
		enemy = get_enemy();
		if ( objectp(enemy) )
		{
			z = get_z(enemy);z0=get_z(me);
			
			if( z == z0 && distance_between(me, enemy) < 20 )
			{
				x = get_x(enemy);y = get_y(enemy);
				x0 = get_x(me);y0 = get_y(me);
			        for( i = 0; i < 10; i ++ )
			        {
			                if( p = get_valid_xy(z, abs( x + random(3) - 1 ), abs( y + random(3) - 1 ), IS_CHAR_BLOCK) )
			                {
			                        x1 = p / 1000;  y1 = p % 1000;  break;
			                }
			        }
			        if ( x1 && y1 && z && !MAP_D->is_inside_city(z, x1, y1) )
			        {
		                        send_user( get_scene_object_2(me, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, x0, y0, 9413, 1, OVER_BODY, PF_ONCE );    // 补发指令
		                        me->add_to_scene( z, x1, y1 );
		                        me->to_front_xy(x, y);
				}
			}
			
		}
	}
	member = get_range_object_2(me, me->get_max_seek(), CHAR_TYPE)+get_range_object_2(me, me->get_max_seek(), USER_TYPE)-({me});
	if ( sizeof(member) != 0 )
	{
		foreach(who in member)
		{
			if ( who->is_die() ) 
				continue;
			if ( me->can_fight(who) != 1 )
				continue;
			me->set_main_enemy(who);
			::heart_beat_walk();
			return;
		}		
	}
	owner =  me->get_enemy();
	if ( !objectp(owner) )
		return ;
        if( get_z(owner)!=get_z(me) || distance_between(me, owner) > 20 )  
        {
		me->set_enemy(0);
		return ;
	}

}


void heart_beat_attack( )
{
	string robber;
	object who;
	object me = this_object();
	
	who = me->get_enemy();
	if ( !objectp(who) )
		return ;
        if( get_z(who)!=get_z(me) || distance_between(me, who) > 20 || !who->can_fight(me) )  
        {
		me->set_enemy(0);
		return ;
	}	
	::heart_beat_attack();

}

//召唤
int summon_slave( object me )
{
        object npc;
        string arg;
        int z, x, y, x0, y0, p;
        int level, cp, pp, i, size;
	if ( me->get("robber.slave") >= 5 )
		return 0;
        level = me->get_level()-5;
        z = get_z(me);  x0 = get_x(me);  y0 = get_y(me);

        if( p = get_valid_xy(z, x0 + random(3) - 1, y0 + random(3) - 1, IS_CHAR_BLOCK) )
        {

                npc = new( "/npc/task/8301" );
		if ( !objectp(npc) )	return;

		npc->set("marry1",me->get("marry1"));
		npc->set("marry2",me->get("marry2"));
		npc->set("level", level);
		NPC_ENERGY_D->init_level(npc, level);
		if ( random(2) )
			npc->set_char_picid(52);
		else
			npc->set_char_picid(201);
                npc->set_walk_speed(6);
                npc->set_attack_speed(15);	
                npc->set_max_seek(8);
                	
                npc->add_max_hp(100);    // 小心准备 me
		npc->add_hp(100);
		npc->add_dp(level);
		npc->add_pp(level);
		
                npc->set_owner(me);
		
		npc->set_char_type(FIGHTER_TYPE); 

                x = p / 1000;  y = p % 1000;
                npc->add_to_scene( z, x, y, get_front_xy(x, y, x0, y0) );
                send_user( get_scene_object_2(npc, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(npc), 
                        41311, 1, OVER_BODY, 41312, 1, OVER_BODY, 41313, 1, UNDER_FOOT, PF_ONCE );
 
                me->add("robber.slave", 1);
                npc->set("robber.id",sprintf( "%x#", getoid(me)) );
                NPC_SLAVE_D->find_enemy(npc);    // 寻找敌人
        }

        return 1;    // 执行成功
}