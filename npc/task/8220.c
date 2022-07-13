//任务链boss
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <music.h>

inherit NPC;
int iAtt,iWalk,hptime;
int summon_slave(object me );
// 函数：任务链boss
int is_chain_boss() { return 1; }

// 函数：是否不能进城
int cannot_enter_city() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "恶霸" + NPC_NAME_D->get_robber_name() );
        set_char_picid(8000);    // 蒙面人
	
        setup();

        set( "birthday", time() );
        set_char_type(FIGHTER_TYPE); 
}

// 函数：复位处理
void reset() 
{
        if( gone_time( get("birthday") ) >= 2400 )    // 40 分钟
        {
                remove_from_scene();
                destruct( this_object() );
        }

}

// 函数：可以接受战斗
int can_be_fighted( object who ) 
{ 
        object owner;
        string leader, id;

	if( who->is_npc() && objectp(owner = who->get_owner()) ) who = owner;
	if( who->is_npc() ) return 0;

        if(   ( leader = who->get_leader() )
        &&    ( owner = find_player(leader) )
        &&      get("chain") ==  owner->get_number() )
                return 1;

        if( get("chain") == who->get_number() )
		return 1;
        send_user( who, "%c%c%w%s", ':',3,get_char_picid(), get_name() + "：\n    滚开！本大爷对你这些杂鱼没兴趣！" );
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
	if ( who->is_die() )
		return 0;
        if(   ( leader = who->get_leader() )
        &&    ( owner = find_player(leader) )
        &&      get("chain") ==  owner->get_number() )
                return 1;

        if( get("chain") == who->get_number() )
		return 1;

	set_enemy(0);
        return 0;
}
// 函数：特技攻击对手
int perform_action( object who ) 
{
	int rate;
	object me = this_object();
	
	if( get_z(who)!=get_z(me) || !inside_screen_2(me, who)  )
		return 0;
	rate = random(100);	
	switch(me->get("chain.type"))
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
		// 封
		if( get_effect(me, EFFECT_CHAR_NO_PF) ) return 0;
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
		// 封		
		summon_slave(me);
		if( get_effect(me, EFFECT_CHAR_NO_PF) ) return 0;
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

// 函数：死亡奖励
void win_bonus( object who )
{
	int id,i,size,x,y,z,x1,y1,z1,max_x,max_y;
	object me = this_object(),*nTeam,map;

	id = get("chain");
	z=get_z(me);
	if ( id && objectp(who=find_char(sprintf("%d",id))) && (get_z(who) == z) )
	{
		who->set_save_2("chain.status",99);	//任务完成
		who->delete("chainnpc");
		send_user(who,"%c%s",'!',"你已成功的将恶霸击杀");
	}
	x1 = get("chain_x");
	y1 = get("chain_y");
	z1 = get("chain_z");
	//把场景中的玩家踢出来
	if( !objectp( map = get_map_object(z) ) )
		return ;
	max_x = get_map_max_x(z);  max_y = get_map_max_y(z);

        for( x = 0; x < max_x; x += AREA_SIZE ) for( y = 0; y < max_y; y += AREA_SIZE )
	{
                if( have_scene_object(z, x, y, USER_TYPE, 1) )
                {
                        nTeam = get_scene_object(z, x, y, USER_TYPE, 1);

                        for( i = 0, size = sizeof(nTeam); i < size; i ++ ) 
                                if( who = nTeam[i] ) 
				{                  
					if ( who->is_pet() && !get_z(who) )
						continue;              
                                	who->add_to_scene(z1,x1,y1); 	
                                }
                }		
		
	}
	
}


//自动跟踪有任务的玩家
void heart_beat_walk()
{
	object *member,who,owner;
	object me = this_object(),enemy;
	int x,y,z,x0,y0,z0,x1,y1,p,i;

	enemy = get_enemy();
	if ( gone_time(hptime) >= 20+random(21) )
	{
		hptime = time();
		//瞬间移动
		if ( objectp(enemy) )
		{
			z = get_z(enemy);z0=get_z(me);
			
			if( z == z0 && (p=distance_between(me, enemy)) < 20 && p >1 )
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
			        if ( x1 && y1 && z )
			        {
		                        me->add_to_scene( z, x1, y1,4,9413 );
		                        me->to_front_xy(x, y);
				}
			}
			
		}
	}
	if ( !enemy || distance_between(me, enemy) > get_max_seek() )
	{
		member = get_range_object_2(me, me->get_max_seek(), CHAR_TYPE)+get_range_object_2(me, me->get_max_seek(), USER_TYPE)-({me,0});
		if ( sizeof(member) != 0 )
		{
			foreach(who in member)
			{
				if ( who->is_die() ) 
					continue;
				if ( can_fight(who) != 1 )
					continue;
				me->set_main_enemy(who);
			}		
		}
	}
	::heart_beat_walk();
}


//召唤
int summon_slave( object me )
{
        object npc;
        string arg;
        int z, x, y, x0, y0, p;
        int level, cp, pp, i, size;
	if ( me->get("chain.slave") >= 5 )
		return 0;
        level = me->get_level()-5;
        z = get_z(me);  x0 = get_x(me);  y0 = get_y(me);

        if( p = get_valid_xy(z, x0 + random(3) - 1, y0 + random(3) - 1, IS_CHAR_BLOCK) )
        {
                npc = new( "/npc/task/8221" );
		if ( !objectp(npc) )	return;
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
 
                me->add("chain.slave", 1);
                npc->set("chain",me->get("chain") );
                NPC_SLAVE_D->find_enemy(npc);    // 寻找敌人
        }

        return 1;    // 执行成功
}
//处理玩家死亡
int get_enemy_die_process() { return 1; }

void on_enemy_die(object who)
{
	who->set_die(1);
}