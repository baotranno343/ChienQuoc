
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <music.h>
#include <skill.h>

inherit NPC;
int hptime,sumtime;//召唤时间。
void summon_guard();

// 函数：是否不能进城
int cannot_enter_city() { return 1; }

// 函数：构造处理
void create()
{
        set_name("劫匪");
        set_char_picid(0252);    // 强盗
        set_char_type(FIGHTER_TYPE);
        set_walk_speed(WALK_SPEED_4);
        set_attack_speed(20);
        set_level(95);

        setup();

        set( "birthday", time() );
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：复位处理
void reset() 
{
	int i;
	object npc,me=this_object();
        if( gone_time( get("birthday") ) >= 1200 )    // 20 分钟
        {
		for(i=0;i<4;i++)
		{
			if ( objectp(npc=me->get(sprintf("guard%d",i))) )//如果宠物存在的话
			{
				npc->remove_from_scene();//从场景中移出。
				destruct(npc);//销毁宠物。
			}
		}
                remove_from_scene(3321);//使用技能
                destruct( this_object() );
        }
}

// --------------------------------------------------------------- 远程调用 ----

// 函数：死亡奖励
void win_bonus( object who ) { __FILE__ ->win_bonus_callout( this_object(), who ); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout( object me, object who )
{
        object owner, *team,npc,freeman;
        int level, level2, exp, exp2, pot, pot2;
        int id, i, index,size;
	for(i=0;i<2;i++)
	{
		if ( objectp(npc=me->get(sprintf("guard%d",i))) )//如果劫匪NPC死亡了,那么的话,就要将两个卫士从清除掉。
		{
			npc->remove_from_scene();
			destruct(npc);
		}
	}
        if( !me->can_be_fighted(who) ) return;//不可以接受战斗。
        if( owner = who->get_owner() ) who = owner;//有主人。
        if( who->is_npc() ) return;//是NPC。
        if(who->is_leader()&&arrayp(team = who->get_team())&& sizeof(team)> 1)
	{
		team = me->correct_bonus_team1(team,20);
		size = sizeof(team);
	}
	else
	{
		size = 1;
	}
        if(size > 1)
	{
		for(index = 0; index < size; index++)
		{
			if(team[index])
			{
				if(team[index]->get_number()== me->get("task"))//组队队员里面有放出劫匪的玩家。
				{
					exp = 3000 + random(2001);
					pot = 300 + random(201);
					team[index]->add_exp(exp);
					team[index]->add_potential(pot);
				}
				else//队伍里面没有放劫匪的玩家
				{
					exp = 2000 + random(2001);
					pot = 200  + random(201);
					team[index]->add_exp(exp);
					team[index]->add_potential(pot);
					id = me->get("task");
					if(freeman = find_player(sprintf("%d",id)))
					{
						exp = 1000 + random(1001);
						pot = 100  + random(101);
						freeman->add_exp(exp);
						freeman->add_potential(pot);
					}
					
					
				}//else
			}//if(team[index])
		}//for(index
	}
	else// 单个人的情况
	{
		if((id = me->get("task")) && (id == who->get_number()))//是放劫匪出来的那个玩家杀死的。
		{
			exp = 3000 + random(2001);
			pot = 300 + random(201);
			who->add_exp(exp);
			who->add_potential(pot);			
		}
		else
		{	
			exp = 2000 + random(2001);
			pot = 200  + random(201);
			who->add_exp(exp);
			who->add_potential(pot);
			id = me->get("task");
			if(freeman = find_player(sprintf("%d",id)))
			{
				exp = 1000 + random(1001);
				pot = 100  + random(101);
				freeman->add_exp(exp);
				freeman->add_potential(pot);
			}
		}		
	}
}

void heart_beat_walk()
{
	int x,y,z,x0,y0,z0,i,x1,y1,p;
	object enemy,me;
	
	enemy = get_enemy();//获得攻击者。
	me = this_object();//劫匪
	if ( enemy && (!sumtime || gone_time(sumtime) > 60 ))//召唤时间已经过了一分钟。
	{
		sumtime = time();
		summon_guard();		
	}
	if ( gone_time(hptime) >= 20+random(21) )//hptime已经超过20~40
	{
		hptime = time();
		//瞬间移动
		if ( objectp(enemy) )
		{
			z = get_z(enemy);z0=get_z(me);//获得对手的地图。
			
			if( z == z0 && distance_between(me, enemy) < 20 )
			{
				x = get_x(enemy);y = get_y(enemy);
				x0 = get_x(me);y0 = get_y(me);
			        for( i = 0; i < 10; i ++ )
			        {
			                if( p = get_valid_xy(z, abs( x + random(3) - 1 ), abs( y + random(3) - 1 ), IS_CHAR_BLOCK) )
			                {
			                        x1 = p / 1000;  y1 = p % 1000;  break;//从中取得一个x,y.
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

	::heart_beat_walk();	
}

void summon_guard()
{
	int i,x,y,z,p,level;
	object npc,me=this_object();
	
	x = get_x(me);y = get_y(me);z = get_z(me);
	level = me->get_level();
	for(i=0;i<2;i++)
	{
		if ( objectp(npc=get(sprintf("guard%d",i))) )//如果guard0/guard1存在的话。
		{
			npc->remove_from_scene();
			destruct(npc);
		}
		p = get_valid_xy(z, x + random(10) - 5, y + random(10) - 5, IS_CHAR_BLOCK);
		if ( !p )
			continue;
		npc = new("npc/task/8006");	
		if ( !npc )
			break;
		set(sprintf("guard%d",i),npc);
		NPC_ENERGY_D->init_level(npc, level);
		npc->set_ap(npc->get_ap()*7/10);//加入场景。
		npc->add_to_scene( z, p / 1000, p % 1000);
		npc->set_owner(me);//设置为自己的。
		NPC_SLAVE_D->find_enemy(npc);    // 寻找敌人
		send_user( get_scene_object_2(npc, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(npc), 
                        41311, 1, OVER_BODY, 41312, 1, OVER_BODY, 41313, 1, UNDER_FOOT, PF_ONCE );
	}
	
}


