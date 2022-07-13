
#include <npc.h>

inherit NPC;

private static int Level0 = 1;          // 等级(主人)
private static int Level2 = 1;          // 等级(升级)

// 函数：是否天兵
int is_zombie() { return 1; }           // 医术杀伤

// 函数：获取召唤兽类型
int get_zombie_type() { return ZOMBIE_TYPE_3; }     // 判断种类

// -------------------------------------------------------------


// 函数：获取等级属性
int get_level_0() { return Level0; }

// 函数：设置等级属性
int set_level_0( int point ) { return Level0 = point; }

// 函数：获取等级属性
int get_level_2() { return Level2; }

// 函数：设置等级属性
int set_level_2( int point ) { return Level2 = point; }

// -------------------------------------------------------------

// 函数：获取物理攻击(基值)
int get_ap_0() 
{ 
        if( !get_owner() ) return get_ap();
        return range_value( get_ap() - 35, 0, get_ap() );
}

// 函数：获取物理防御(基值)
int get_dp_0() 
{ 
        if( !get_owner() ) return get_dp();
        return range_value( get_dp() - 35, 0, get_dp() );
}

// 函数：获取法术攻击(基值)
int get_cp_0() 
{ 
        if( !get_owner() ) return get_cp();
        return range_value( get_cp() - 35, 0, get_cp() );
}

// 函数：获取法术防御(基值)
int get_pp_0() 
{ 
        if( !get_owner() ) return get_pp();
        return range_value( get_pp() - 35, 0, get_pp() );
}

// -------------------------------------------------------------

// 函数：判断可以战斗
int can_fight( object who ) 
{ 
        if( MAP_D->is_inside_battle( get_z( this_object() ) ) ) 
                return NPC_COMRADE_D->can_fight( this_object(), who ); 
        else    return NPC_SLAVE_D->can_fight( this_object(), who ); 
}

// 函数：可以接受战斗
int can_be_fighted( object who ) 
{ 
        if( MAP_D->is_inside_battle( get_z( this_object() ) ) ) 
                return NPC_COMRADE_D->can_be_fighted( this_object(), who ); 
        else    return NPC_ATTACK_D->can_be_fighted( this_object(), who ); 
}

// 函数：走路处理(心跳之中调用)
void heart_beat_walk() { NPC_SLAVE_D->heart_beat_walk( this_object() ); }

// 函数：从场景中移除
varargs void remove_from_scene( int rm_pf, int rm_pf_2 )
{
        object me, owner;

        ::remove_from_scene(rm_pf, rm_pf_2);

        me = this_object();
        if( owner = me->get_owner() ) 
        {
        	send_user( owner, "%c%c%d", 0x2c, 0, getoid(me) );    // 更新召唤兽坐标
        }
}
