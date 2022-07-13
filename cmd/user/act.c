
#include <action.h>
#include <effect.h>
#include <equip.h>

// 函数：命令处理
int main( object me, string arg )
{
        int busy, action = DEFAULT_ACT;
	if (me->get_ride()) return 1;
        if( busy = get_effect(me, EFFECT_CHAR_BUSY) )
        {
                notify( "Bạn còn phải bận %d giây", busy );
                return 1;
        }
        if( get_heart_state(me) == FIGHT_STAT ) return 1;
        if( get_heart_state(me) == MAGIC_STAT ) return 1;
        if (get_effect_3(me, EFFECT_PROGRESS)||get_effect_3(me, EFFECT_PROGRESS2)) return 1;

        me->set_enemy(0);

        switch( arg )
        {
     case "1" : action = ATTACK_ACT;  break;
     case "2" : action = SIT_ACT;  break;
     case "3" : action = MAGIC_ACT;  break;
     case "4" : action = FALL_ACT;  break;
     case "5" : action = STAND_ACT;  break;
     case "6" : action = DEFAULT_ACT;  break;
     case "7" : action = RUN_ACT;  break;
      default : action = WAIT_ACT;  break;
        }

        switch( action )
        {
     case DEFAULT_ACT : case FALL_ACT :
                        me->set_char_action(action);  break;
        case SIT_ACT:
                        me->set_char_action(action);
                        set_effect(me, EFFECT_PROGRESS2, 3);
                        me->set_progress_file(__FILE__);
                        break;
              default : me->set_char_action(DEFAULT_ACT);
                        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), action );
                        break;
        }

        busy = get_effect(me, EFFECT_CHAR_BUSY) + 1;
        set_effect(me, EFFECT_CHAR_BUSY, busy);
        send_user(me, "%c%c%c", 0x3d, 9, busy);
        return 1;
}

// 函数：法术处理
int into_effect( object me , string arg)
{
        int add_hp, add_mp,i,size;
        string name;
        object item1,item2,*user;
        if (me->get_hp()==me->get_max_hp()&&me->get_mp()==me->get_max_mp())
        {
//                me->set_char_action(DEFAULT_ACT);
                return;
        }
        add_hp = 12;
        add_mp = 12;
        //Long Trạc Phượng Trạc
        item1 = me->get_equip(HAND_TYPE);
        if ( objectp(item1) )
        {
        	if ( item1->get_name() == "Long Trạc" )
        		name = "Phượng Trạc" ;
        	else if ( item1->get_name() == "Phượng Trạc" )
        		name = "Long Trạc" ;
        	if ( name )
        	{
        		if( arrayp( user = me->get_team() ) )
        		{
        			user -= ({0,me});
        			size = sizeof(user);
        			for(i=0;i<size;i++)
        			{
        				if ( !objectp(item2=user[i]->get_equip(HAND_TYPE)) || item2->get_name() != name )
        					continue;	
        				add_hp += add_hp / 10;
        				add_mp += add_mp / 10;
        				break;
        			}
        		}
        	}
        }
        
        me->add_hp(add_hp);
        me->add_mp(add_mp);
        set_effect(me, EFFECT_PROGRESS2, 3);
        me->set_progress_file(__FILE__);
}

void effect_break(object me, string arg)
{
	set_effect(me, EFFECT_PROGRESS2, 0);
}