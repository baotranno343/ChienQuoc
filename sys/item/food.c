#include <effect.h>
#include <skill.h>
#include <ansi.h>
#include <item.h>
#include <equip.h>

// 函数：生成二进制码
void SAVE_BINARY() { }

void effect_recover_break( object me );

int get_use_effect(object me, object obj)
{
	object *user,owner;
	int type, effect, time;
	type = obj->get_item_type_2();
	user = get_scene_object_2(me, USER_TYPE);
	if ( me->is_pet() )
		owner = me->get_owner();
	if (me->get_level() < obj->get("level"))
	{
		if ( owner )
			send_user( owner, "%c%s", '!', HIY"Bạn "+me->get_name()+" cấp bậc không đủ, không thể dùng.");
		else		
			send_user( me, "%c%s", '!', HIY"Bạn cấp bậc không đủ, không thể dùng.");
		return 0;
	}
	if ( time = obj->get_recover_count() );
	else if (obj->get_fin_type()>0) time = 7;
	else time = 10;
	switch(type)
	{
	case ITEM_TYPE_2_CON_HP:
	      	if( gone_time( me->get_time("add_con_hp") ) < 2 )
	      	{
	      		if (me->get("food_level")>= obj->get("level"))
	      		{      			
	              		return 0;
			}	              		
	      	}
	      	me->set_time( "add_con_hp", time() );  	
	      	me->set("temp_add_hp", obj->get("add_hp")/time);
	      	effect = 9154;      	
	      	set_effect_2(me, EFFECT_CON_HP_MP, time, 2);
	      	break;	
	case ITEM_TYPE_2_CON_MP:
	      	if( gone_time( me->get_time("add_con_mp") ) < 2 )
	      	{
	      		if (me->get("food_level")>= obj->get("level"))
	      		{	      		
	              		return 0;
			}	              		
	      	}
	      	me->set_time( "add_con_mp", time() );  	
	      	me->set("temp_add_mp", obj->get("add_mp")/time);
	      	effect = 9156;
	      	set_effect_2(me, EFFECT_CON_MP, time, 2);
	      	break;	
	case ITEM_TYPE_2_CON_ALL:
	      	if( gone_time( me->get_time("add_con_all") ) < 2 )
	      	{
	      		if (me->get("food_level")>= obj->get("level"))
	      		{      			
	              		return 0;
			}	              		
	      	}
	      	me->set_time( "add_con_all", time() );  	
	      	me->set("temp_add_hp", obj->get("add_hp")/time);
	      	me->set("temp_add_mp", obj->get("add_mp")/time);
	      	effect = 9158;
	      	set_effect_2(me, EFFECT_CON_HP_MP, time, 2);
	      	set_effect_2(me, EFFECT_CON_MP, time, 2);
	      	break;		
	default:		
		return 0;	      	      		      				
	}
	if ( !owner )
	{
		send_user( me, "%c%c%c%w", 0x30, obj->get_item_type_2(), obj->get("level"), 2 );    // 更新使用间隔	
		send_user( me, "%c%w%w%c", 0x81, effect, 2*time, EFFECT_GOOD );
	}
	else
		send_user( owner, "%c%c%c%w", 0x30, obj->get_item_type_2(), obj->get("level"), 2 );    // 更新使用间隔	
	send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), effect, 1, EFFECT_GOOD );	
	return 1;
}

void into_effect(object me)
{
	if( !get_effect(me, EFFECT_CON_HP_MP) ) effect_recover_break(me);
	if (me->get("temp_add_hp")) me->add_hp(me->get("temp_add_hp"));	
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE );
}

void into_effect2(object me)
{
	if( !get_effect(me, EFFECT_CON_MP) ) effect_recover_break(me);
	if (me->get("temp_add_mp")) me->add_mp(me->get("temp_add_mp"));
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE );
}

// 函数：停止休整
void effect_recover_break( object me )
{
        set_effect(me, EFFECT_CON_HP_MP, 0);
        send_user( me, "%c%w%w%w%w%w%w%c", 0x81, 9154, 0, 9156, 0, 9158, 0, EFFECT_GOOD );
        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%w%w%c%c", 0x83, getoid(me), 9154, 9156, 9158, 0, EFFECT_GOOD );
}
// 函数：停止休整
void effect_recover_break2( object me )
{
        set_effect(me, EFFECT_CON_MP, 0);
        send_user( me, "%c%w%w%w%w%w%w%c", 0x81, 9154, 0, 9156, 0, 9158, 0, EFFECT_GOOD );
        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%w%w%c%c", 0x83, getoid(me), 9154, 9156, 9158, 0, EFFECT_GOOD );
}

// 函数：获取描述(持续)加血
string get_loop_desc( object me )
{
	string result = "";
	if (me->get("temp_add_hp"))  result +="Mỗi 2 giây phục hồi khí huyết.\n";
        return result;
}

// 函数：获取描述(持续)加法
string get_loop_desc2( object me )
{
	string result = "";
        if (me->get("temp_add_mp"))  result +="Mỗi 2 giây phục hồi pháp lực.\n";
        return result;
}

// 函数：获取描述(持续)加血和加法
string get_loop_desc3( object me )
{
	string result = "";
	if (me->get("temp_add_hp"))  result +="Mỗi 2 giây phục hồi khí huyết.\n";
        if (me->get("temp_add_mp"))  result +="Mỗi 2 giây phục hồi pháp lực.\n";
        return result;
}