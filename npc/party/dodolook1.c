
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <task.h>

inherit NPC;
int iAtt,iWalk,hptime;
int summon_slave(object me );
//标记
int is_dodolook() { return 1; }

// 函数：是否不能进城
int cannot_enter_city() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "噬情魔" + NPC_NAME_D->get_banditi_name() );
        set_char_picid(8000);    // 蒙面人
	
        setup();

        set( "birthday", time() );
        set_char_type(FIGHTER_TYPE); 
}

// 函数：复位处理
void reset() 
{
        object who;
        string *member, id;
        int i, size;

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
        string leader, id;

	if( who->is_npc() && objectp(owner = who->get_owner()) ) who = owner;
	if( who->is_npc() ) return 0;
        if( who->get_enemy() == this_object() ) return 1;

	if ( who->get_save_2("dodolook_task.npcid") == getoid(this_object()) )
		return 1;
        send_user( who, "%c%c%w%s", ':',3,get_char_picid(), get_name() + "：\n    滚开！别多管闲事！" );
        return 0;
}
int can_fight( object who ) 
{ 
        object owner;
        string leader, id;
        
        if ( who->is_die() ) 
        {
		set_enemy(0);
		return 0;
	}
	if( who->is_npc() && objectp(owner = who->get_owner()) ) who = owner;
	if( who->is_npc() )
	{
		set_enemy(0);
		return 0;
	}
        if( who->get_enemy() == this_object() ) return 1;

	if ( who->get_save_2("dodolook_task.npcid") == getoid(this_object()) )
		return 1;
	set_enemy(0);
        return 0;
}
// 函数：特技攻击对手
int perform_action( object who ) 
{
	int rate;
	object me = this_object();
	rate = random(100);	
	switch(me->get("dodolook.type"))
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
	object me,owner,member;
	
	me = this_object();
        if( !me->can_be_fighted(who) ) return;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return;
        
        member = find_char(sprintf("%d",who->get_save_2("dodolook_task.member")));
        if ( !objectp(member) )
        {
        	send_user(who,"%c%s",'!',"此怪物不是双方齐心合力所杀，此次任务即算失败～！");
        	return ;
        }
        if ( !inside_screen_2(who,me) || !inside_screen_2(member,me) )
        {
        	send_user(who,"%c%s",'!',"此怪物不是双方齐心合力所杀，此次任务即算失败～！");
        	send_user(member,"%c%s",'!',"此怪物不是双方齐心合力所杀，此次任务即算失败～！");
        	return ;
        }
	who->set_save_2("dodolook_task.finish",1);	
	member->set_save_2("dodolook_task.finish",1);	
	send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_YUANFEN,1,"" );                  		
	send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_YUANFEN,"缘分对对碰" );     
	send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_YUANFEN,1,"消灭噬情魔(完成)" );                  		
	send_user( who, "%c%s", '!',"消灭噬情魔(完成)" );                  		

	send_user( member, "%c%c%c%w%w%s", 0x51, 1, 2,TID_YUANFEN,1,"" );                  		
	send_user( member, "%c%c%c%w%s", 0x51, 1, 1,TID_YUANFEN,"缘分对对碰" );     
	send_user( member, "%c%c%c%w%w%s", 0x51, 1, 2,TID_YUANFEN,1,"消灭噬情魔(完成)" );                  		
	send_user( member, "%c%s", '!',"消灭噬情魔(完成)" );                  		
}


//自动跟踪有任务的玩家
void heart_beat_walk()
{
	string robber;
	object *member,who,owner;
	object me = this_object(),enemy;
	int x,y,z,x0,y0,z0,x1,y1,p,i;
	//3秒处理一次
	if ( (iWalk++)%3 )
	{
		::heart_beat_walk();
		return;		
	}
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
		                        send_user( get_scene_object_2(me, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, x1, y1, 9413, 1, OVER_BODY, PF_ONCE );    // 补发指令
		                        me->add_to_scene( z, x1, y1 );
		                        me->to_front_xy(x, y);
				}
			}
			
		}
	}
	member = get_range_object_2(me, me->get_max_seek(), CHAR_TYPE)+get_range_object_2(me, me->get_max_seek(), USER_TYPE)-({me});
	member -= ({0});
	if ( sizeof(member) != 0 )
	{
		foreach(who in member)
		{
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



//召唤
int summon_slave( object me )
{
        object npc;
        string arg;
        int z, x, y, x0, y0, p;
        int level, cp, pp, i, size;
	if ( me->get("dodolook.slave") >= 5 )
		return 0;
        level = me->get_level()-10;
        z = get_z(me);  x0 = get_x(me);  y0 = get_y(me);

        if( p = get_valid_xy(z, x0 + random(3) - 1, y0 + random(3) - 1, IS_CHAR_BLOCK) )
        {
                npc = new( "/npc/party/dodolook11" );
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
                	
                npc->add_max_hp(100);    
		npc->add_hp(100);
		npc->add_dp(level);
		npc->add_pp(level);
		
                npc->set_owner(me);
		
		npc->set_char_type(FIGHTER_TYPE); 

                x = p / 1000;  y = p % 1000;
                npc->add_to_scene( z, x, y, get_front_xy(x, y, x0, y0) );
                send_user( get_scene_object_2(npc, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(npc), 
                        41311, 1, OVER_BODY, 41312, 1, OVER_BODY, 41313, 1, UNDER_FOOT, PF_ONCE );
 
                me->add("dodolook.slave", 1);
                npc->set("dodolook.id",sprintf( "%x#", getoid(me)) );
                NPC_SLAVE_D->find_enemy(npc);    // 寻找敌人
        }

        return 1;    // 执行成功
}