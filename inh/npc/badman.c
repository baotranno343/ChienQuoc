
#include <npc.h>

inherit SLAVE;

private static int Zombie = 0;          // 召唤兽(被魅惑)
private static int BeenSlave = 0;       // 曾被魅惑

// 函数：是否野外的怪
int is_badman() { return 1; }

// 函数：是否不能进城
int cannot_enter_city() { return 1; }

// -------------------------------------------------------------

// 函数：是否天兵
int is_zombie() { return Zombie; }      // 医术杀伤

// 函数：设置天兵
int be_zombie( int flag ) { return Zombie = flag; }

// 函数：是否曾被魅惑
int is_have_been_slave() { return BeenSlave; }

// 函数：设置曾被魅惑
int have_been_slave( int flag ) { return BeenSlave = flag; }

// -------------------------------------------------------------

// 函数：攻击处理(心跳之中调用)
void heart_beat_walk() 
{
        if( Zombie ) 
                NPC_SLAVE_D->heart_beat_walk( this_object() ); 
        else    NPC_HEART_D->heart_beat_walk( this_object() ); 
}

// 函数：判断可以战斗
int can_fight( object who )
{
        if( Zombie ) 
                return NPC_SLAVE_D->can_fight( this_object(), who ); 
        else if( MAP_D->is_inside_battle( get_z( this_object() ) ) ) 
                return NPC_COMRADE_D->can_fight( this_object(), who ); 
        else    return NPC_ATTACK_D->can_fight( this_object(), who ); 
}

// 函数：可以接受战斗
int can_be_fighted( object who ) 
{ 
        if( MAP_D->is_inside_battle( get_z( this_object() ) ) ) 
                return NPC_COMRADE_D->can_be_fighted( this_object(), who ); 
        else    return NPC_ATTACK_D->can_be_fighted( this_object(), who ); 
}

// --------------------------------------------------------------- 远程调用 ----

// 函数：升级处理
void upgrade_level( int level ) { __FILE__ ->upgrade_level_callout( this_object(), level ); }

// 函数：升级处理(在线更新)
void upgrade_level_callout( object me, int level )
{
        switch( level )
        {
      default : me->set_char_type(SLAVE_TYPE_1);
                me->set_walk_speed(WALK_SPEED_1);
                break;
       case 2 : me->set_char_type(SLAVE_TYPE_2);
                me->set_walk_speed(WALK_SPEED_1);
                break;
       case 3 : me->set_char_type(SLAVE_TYPE_3);
                me->set_walk_step(2);
                me->set_walk_speed(WALK_SPEED_1);
                break;
       case 4 : me->set_char_type(SLAVE_TYPE_4);
                me->set_walk_step(2);
                me->set_walk_speed(WALK_SPEED_1);
                break;
       case 5 : me->set_char_type(SLAVE_TYPE_5);
                me->set_walk_step(2);
                me->set_walk_speed(WALK_SPEED_1);
                break;
        }
}

// 函数：升级处理
void upgrade_level_2( int level ) { __FILE__ ->upgrade_level_2_callout( this_object(), level ); }

// 函数：升级处理(在线更新)
void upgrade_level_2_callout( object me, int level )
{
        object owner;
        int hp, cp, pp;

        if( level > 1 ) if( objectp( owner = me->get_owner() ) && owner->is_user() )
        {
                cp = owner->get_cp();
                pp = owner->get_pp();
                me->add_max_hp( 40 );  
                me->set_hp(me->get_max_hp());
                me->set_mp(me->get_max_mp());
                me->add_ap( 8 );
                me->add_dp( 10 );
                me->add_cp( 8 );
                me->add_pp( 10 );
                me->add_sp( 10 );
        }
}

// 函数：获取人物名称
string get_short() 
{
	string name;
	
	name = get_name();
	if ( get("is_baobao") )
		name += " Bảo Bảo";
        if (get_level()) 
        	name = sprintf(" %s ( Cấp %d )",name, get_level() );
	return name;
}

int get_id_color() 
{ 
	if ( get("is_baobao") )	
		return 0xF6FB19; 
	return 0;
}
