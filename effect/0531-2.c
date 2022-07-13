#include <effect.h>
#include <skill.h>

// 函数：被魅惑状态(ＮＰＣ)
void into_effect_2( object me ) 
{
        object owner, *zombie;
        object *char;
        int i, size;
        
	owner = me->get_owner();
	if (owner)
	{
	        if( objectp( owner = me->get_owner() ) && owner->is_user() )
	        {
	                if( arrayp( zombie = owner->get("zombie") ) ) owner->set( "zombie", zombie - ({ me, 0 }) );
	        }
	        move_object( me, get_z(me), get_x(me), get_y(me), CHAR_TYPE );
	        me->set_owner(0);
	        me->set_char_type( get_file_name(me)->get_char_type() );
	        me->set_name( get_file_name(me)->get_name() );	
	        me->set_action(1);
	        me->be_zombie(0);
	        set_effect( me, EFFECT_NPC_0531_2, 300 );
	        me->stop_fight();
	        char = get_range_object_2(me, 5, CHAR_TYPE) + get_range_object_2(me, 5, USER_TYPE) - ({ me });
	        for( i = 0, size = sizeof(char); i < size; i ++ )
        	        if( char[i] && char[i]->get_enemy() == me ) char[i]->stop_fight();	        	        
	}
	else
	{
		if (get_effect(me, EFFECT_NPC_0531_1)) set_effect( me, EFFECT_NPC_0531_2, 20 );
		else
		{
			me->remove_from_scene();
			destruct(me);
		}
	}	       
}
