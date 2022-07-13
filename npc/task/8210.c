
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <music.h>

inherit NPC;
int iAtt,iWalk,hptime;
int summon_slave(object me );
// 函数：被剿强盗
int is_robber() { return 1; }

// 函数：门派人物
int is_boss() { return 1; }

// 函数：是否不能进城
int cannot_enter_city() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "Tội Phạm " + NPC_NAME_D->get_robber_name() );
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
        else
        {
                member = get("user");
                id = sprintf( "%x#", getoid( this_object() ) );
                for( i = 0, size = sizeof(member); i < size; i ++ )
                        if( !( who = find_player( member[i] ) ) || who->get_task("robber") != id ) member[i] = "";
                if( sizeof( member -= ({ "" }) ) < 1 )
                {
                        remove_from_scene();
                        destruct( this_object() );
                }
                else    set("user", member);
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

        if( stringp( id = who->get_task("robber") )
        &&      id == sprintf( "%x#", getoid( this_object() ) ) )
		return 1;
        send_user( who, "%c%c%w%s", ':',3,get_char_picid(), get_name() + "：\n    Cút ngay ! bổn đại gia không có hứng thú" );
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
        if( who->get_enemy() == this_object() ) return 1;

        if( stringp( id = who->get_task("robber") )
        &&      id == sprintf( "%x#", getoid( this_object() ) ) )
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
	switch(me->get("robber.type"))
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

//int perform_action( object who )
//{ 
//
//        switch( get_fam_name() )
//        {
//      default : return 0;
//case "桃花源" : if( get_level() >= 36 && random(100) < 5 )
//                {
//                        if( random(2) ) return PF_FILE_02114->perform_action_npc(me, who); 
//                        else return PF_FILE_02117->perform_action_npc(me, who); 
//                }
//                else if( get_level() >= 33 && random(100) < 5 )
//                        return PF_FILE_02114->perform_action_npc(me, who); 
//                return 0;
//  case "蜀山" : if( get_weapon_code() == BLADE )
//                {
//                        if( get_level() >= 15 && random(100) < 5 )
//                                return PF_FILE_02212->perform_action_npc(me, who); 
//                }
//                else if( get_weapon_code() == SWORD )
//                {
//                        if( get_level() >= 27 && random(100) < 5 )
//                        {
//                                if( random(2) ) return PF_FILE_02313->perform_action_npc(me, who); 
//                                else return PF_FILE_02314->perform_action_npc(me, who); 
//                        }
//                        else if( get_level() >= 19 && random(100) < 5 )
//                                return PF_FILE_02313->perform_action_npc(me, who); 
//                }
//                return 0;
//case "禁卫军" : if( get_weapon_code() == SPEAR )
//                {
//                        if( get_level() >= 16 && random(100) < 5 )
//                                return PF_FILE_02412->perform_action_npc(me, who); 
//                }
//                else if( get_weapon_code() == STICK )
//                {
//                        if( get_level() >= 47 && random(100) < 5 )
//                        {
//                                if( random(2) ) return PF_FILE_02513->perform_action_npc(me, who); 
//                                else return PF_FILE_02514->perform_action_npc(me, who); 
//                        }
//                        else if( get_level() >= 22 && random(100) < 5 )
//                                return PF_FILE_02513->perform_action_npc(me, who); 
//                }
//                return 0;
//  case "唐门" : if( get_level() >= 35 && random(100) < 5 )
//                        return PF_FILE_02615->perform_action_npc(me, who); 
//                else    return PF_FILE_01611->perform_action_npc(me, who); 
//  case "茅山" : if( !objectp( me->get("soldier") ) )
//                {
//                        if( get_level() >= 42 ) PF_FILE_04133->perform_action_npc(me, who);
//                        else if( get_level() >= 28 ) PF_FILE_04132->perform_action_npc(me, who);
//                        else if( get_level() >= 16 ) PF_FILE_04131->perform_action_npc(me, who);
//                }
//                return 1;    // 只召唤，不攻击
//case "昆仑山" : if( get_level() >= 38 && random(100) < 3 )
//                {
//                        if( !get_effect(me, EFFECT_CHAR_CHANGE) ) PF_FILE_04251->perform_action_npc(me, who);
//                }
//                else    PF_FILE_04232->perform_action_npc(me, who);
//                return 1;
//case "云梦泽" : return 0;    // 普通攻击，带毒
//        }
//        return 0;
//}

// --------------------------------------------------------------- 远程调用 ----

// 函数：死亡奖励
void win_bonus( object who )
{
	object owner,*team,*team2,map;
	object me = this_object();
	string id,id2;
	int i,size,level;
	
        if( !me->can_be_fighted(who) ) return;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return;
	team = who->get_team();
	if ( sizeof(team) < 1 ) team = ({who});
        team = me->correct_bonus_team( team );
        if( ( size = sizeof(team) ) < 1 ) return;
	if( !objectp( map = get_map_object(get_z(me)) ) || !map->is_scene() ) return;	
        id = sprintf( "%x#", getoid(me) );

        for( i = 0, team2 = ({ }); i < size; i ++ )
        {
                if(     team[i]
                &&      stringp( id2 = team[i]->get_task("robber") )
                &&      id == id2 )
                        team2 += ({ team[i] });
        }

        if( ( size = sizeof( team = team2 ) ) < 1 ) return;
        level = me->get_level();
        for( i = 0; i < size; i ++ ) if( team[i] )
        {
        	team[i]->set_task("robber.bonus",1);
        	team[i]->set_task("robber.level",level);        	
        	team[i]->set_task("robber.name",me->get_name());  
        	team[i]->set_task("robber.map",map->get_name());  
        	TASK_ROBBER_D->clear_task_desc(team[i]);
        	TASK_ROBBER_D->send_task_list(team[i]);
        }
}

// 函数：掉宝奖励
void drop_items( object me, object who )
{
        object item;
        string file;
        int p, rate, level, level2;
        int z, x, y;

        z = get_z(me);  x = get_x(me);  y = get_y(me);

        p = random(10000);  level = me->get_level();

        rate = me->correct_drop_rate( level - who->get_level() );
	rate = rate * who->get_online_rate()/100;
        if( p < 6340 * rate / 100 ) ;    // NONE

        else if( p < 8340 * rate / 100 )    // 金钱
        {
                if( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) )
                {
                        item = new( "/item/std/0001" );
                        item->set_value( level * 100 + random(1001) );
                        item->add_to_scene(z, p / 1000, p % 1000);
                        item->set("winner", who);
                        item->set( "time", time() );
                }
        }
        else if( p < 9840 * rate / 100 )    // 特殊药物
        {
                switch( random(2) )
                {
               case 0 : file = "/item/91/9102";  break;
               case 1 : file = "/item/91/9112";  break;
                }
                if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                {
                        item = new( file );
                        item->add_to_scene(z, p / 1000, p % 1000);
                        item->set("winner", who);
                        item->set( "time", time() );
                }
        }
        else if( p < 9930 * rate / 100 )    // 武器、装备
        {
                level2 = range_value(level - 5, 30, 80);

                if( random(2) ) 
                        file = ARMOR_FILE->get_armor_file_2(level2);
                else    file = WEAPON_FILE->get_weapon_file_2(level2);
                if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                {
                        item = new( file );
                        ITEM_EQUIP_D->init_equip_prop(item);
                        item->add_to_scene(z, p / 1000, p % 1000);
                        item->set("winner", who);
                        item->set( "time", time() );
                }
        }
        else if( p < 9950 * rate / 100 )    // 装备
        {
                if( level < 80 ) 
                        return;
                else if( level < 90 ) 
                        file = ARMOR_FILE->get_armor_file_2(90);
                else if( random(2) ) 
                        file = ARMOR_FILE->get_armor_file_2(90);
                else    file = ARMOR_FILE->get_armor_file_2(100);
                if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                {
                        item = new( file );
                        ITEM_EQUIP_D->init_equip_prop(item);
                        item->add_to_scene(z, p / 1000, p % 1000);
                        item->set("winner", who);
                        item->set( "time", time() );
                }
        }
        else if( p < 9970 * rate / 100 )    // 武器
        {
                if( level < 80 ) 
                        return;
                else if( level < 90 ) 
                        file = WEAPON_FILE->get_weapon_file_2(90);
                else if( random(2) ) 
                        file = WEAPON_FILE->get_weapon_file_2(90);
                else    file = WEAPON_FILE->get_weapon_file_2(100);
                if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                {
                        item = new( file );
                        ITEM_EQUIP_D->init_equip_prop(item);
                        item->add_to_scene(z, p / 1000, p % 1000);
                        item->set("winner", who);
                        item->set( "time", time() );
                }
        }
        else if( p < 10000 * rate / 100 )    // 宝石
        {
                file = STONE_FILE->get_stone_file();
                if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                {
                        item = new(file);
                        item->add_to_scene(z, p / 1000, p % 1000);
                        item->set("winner", who);
                        item->set( "time", time() );
                }
        }
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
		robber = sprintf( "%x#", getoid(me) );
		foreach(who in member)
		{
				
			if ( who->is_die() ) 
				continue;
			if( (owner = who->get_owner()) && (owner->get_task("robber") != robber) ) 
			{
				continue;	
			}
			else if (  !(owner = who->get_owner()) && who->get_task("robber") != robber )
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
	//3秒处理一次
	if ( (iAtt++)%3 )	
	{
		::heart_beat_attack();
		return;		
	}	
	who = me->get_enemy();
	if ( !objectp(who) )
		return ;
        if( get_z(who)!=get_z(me) || distance_between(me, who) > 20 || !who->can_fight(me) )  
        {
		me->set_enemy(0);
		return ;
	}	
//	robber = sprintf( "%x#", getoid(me) );
//	if ( who->get_task("robber") != robber )
//	{
//		me->set_enemy(0);
//		return ;
//	}
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
                npc = new( "/npc/task/8211" );
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
 
                me->add("robber.slave", 1);
                npc->set("robber.id",sprintf( "%x#", getoid(me)) );
                NPC_SLAVE_D->find_enemy(npc);    // 寻找敌人
        }

        return 1;    // 执行成功
}