
#include <cmd.h>
#include <skill.h>
#include <effect.h>

// 函数：状态保护进入
// 说明：状态保护汇总，用于所有需要状态保护的征状在结束时调用，
//       以进入相应保护状态。注意出招时要判断是否处于保护状态！

void into_effect( object me, int flag )    // 玩家使用
{
        object *user, *inv, item, owner;
        int point, i, size;

        switch( flag )
        {
     	    case EFFECT_SLEEP : user = get_scene_object_2(me, USER_TYPE);
     				CHAR_CHAR_D->init_loop_perform(me);
                                send_user( me, "%c%w%w%c", 0x81, 9002, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9002, 0, EFFECT_BAD );
                                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9015, 1, OVER_BODY, PF_STOP );
                                me->set_enemy(0);
                                break;        	
     case EFFECT_CHAR_FAINT_0 : user = get_scene_object_2(me, USER_TYPE);
     				CHAR_CHAR_D->init_loop_perform(me);
                                send_user( me, "%c%w%w%c", 0x81, 9002, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9002, 0, EFFECT_BAD );
                                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9002, 1, OVER_BODY, PF_STOP );
                                set_effect(me, EFFECT_CHAR_FAINT_0, 2);
                                me->set_enemy(0);
                                break;

     case EFFECT_CHAR_FAINT_3 : user = get_scene_object_2(me, USER_TYPE);
     				CHAR_CHAR_D->init_loop_perform(me);
                                send_user( me, "%c%w%w%c", 0x81, 9002, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9002, 0, EFFECT_BAD );
                                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9002, 1, OVER_BODY, PF_STOP );
                                set_effect(me, EFFECT_CHAR_FAINT_3, 10);
                                me->set_enemy(0);
                                break;

    case EFFECT_CHAR_FREEZE_0 : // set_effect(me, EFFECT_CHAR_FREEZE_0, 2);  
    				me->set_enemy(0);
                                break;

      case EFFECT_CHAR_SHUT_0 : user = get_scene_object_2(me, USER_TYPE);
                                send_user( me, "%c%w%w%c", 0x81, 3482, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3482, 0, EFFECT_BAD );
                                CHAR_CHAR_D->init_loop_perform(me);
                                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 34821, 1, UNDER_FOOT, PF_STOP );
                                // set_effect(me, EFFECT_CHAR_SHUT_0, 2);  
                                break;

     case EFFECT_CHAR_NO_PF_0 : // set_effect(me, EFFECT_CHAR_NO_PF_0, 2);  
                                CHAR_CHAR_D->effect_no_pf_done(me);
                                break;

      case EFFECT_CHAR_LAZY_0 : send_user(me, "%c%c%c", 0x3d, 241, 2);    // 恢复走路步数
                                user = get_scene_object_2(me, USER_TYPE);
                                send_user( me, "%c%w%w%c", 0x81, 9013, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9013, 0, EFFECT_BAD );
        			send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9012, 1, OVER_BODY, PF_STOP );
                                set_effect(me, EFFECT_CHAR_LAZY_0, 2);
                                break;

      case EFFECT_CHAR_SLOW_0 : user = get_scene_object_2(me, USER_TYPE);
                                send_user( me, "%c%w%w%c", 0x81, 9012, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9012, 0, EFFECT_BAD );
                                set_effect(me, EFFECT_CHAR_SLOW_0, 2);  
                                send_user(me, "%c%c%c", 0x3d, 241, 2);    // 恢复走路步数
				send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 34821, 1, UNDER_FOOT, PF_STOP );
                                break;

     case EFFECT_CHAR_DREAM_1 : GO_CMD->main( me, sprintf( "%d,%d %d", get_x(me), get_y(me), random(8) + 1 ), 1 );    // 随机走路(系统校验)
                                set_effect_2(me, EFFECT_CHAR_DREAM, 6, 1);
                                send_user( me, "%c%w%w%c", 0x81, 9016, get_effect_3(me, EFFECT_CHAR_DREAM), EFFECT_BAD );
//                              send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9016, 1, EFFECT_BAD );
                                break;

     case EFFECT_CHAR_DREAM_0 : GO_CMD->main( me, sprintf( "%d,%d %d", get_x(me), get_y(me), random(8) + 1 ), 1 );    // 随机走路(系统校验)

                                if( !get_effect_3(me, EFFECT_CHAR_DREAM) )    // 循环征状 set_effect_2
                                {
                                        send_user(me, "%c%c%c", 0x3d, 240, 0);    // 客户端走路
                                        user = get_scene_object_2(me, USER_TYPE);
                                        send_user( me, "%c%w%w%c", 0x81, 9016, 0, EFFECT_BAD );
                                        send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9016, 0, EFFECT_BAD );
                                        set_effect(me, EFFECT_CHAR_DREAM_0, 2);
                                        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 53112, 1, OVER_BODY, PF_STOP );
                                        CHAR_CHAR_D->init_loop_perform(me);
                                }
				
                                break;

     case EFFECT_CHAR_CHAOS_0 : send_user(me, "%c%c%c", 0x3d, 242, 0);    // 鼠标正常
                                user = get_scene_object_2(me, USER_TYPE);
                                send_user( me, "%c%w%w%c", 0x81, 9018, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9018, 0, EFFECT_BAD );
                                set_effect(me, EFFECT_CHAR_CHAOS_0, 2);  
                                break;

     case EFFECT_CHAR_WOUND_0 : user = get_scene_object_2(me, USER_TYPE);
                                send_user( me, "%c%w%w%c", 0x81, 9020, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9020, 0, EFFECT_BAD );
                                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9020, 1, OVER_BODY, PF_STOP );
                                set_effect(me, EFFECT_CHAR_WOUND_0, 2);  

                                USER_ENERGY_D->count_ap(me);
                                USER_ENERGY_D->count_dp(me);
                                break;
     case EFFECT_CON_RECOVER :  user = get_scene_object_2(me, USER_TYPE);
                                point = me->get_save("05115");
                                send_user( user, "%c%d%w", 0x68, getoid(me), -point );
                                if (!me->no_recover()) me->add_hp(point);
                                if( !get_effect_3(me, EFFECT_CON_RECOVER) )    // 循环征状 set_effect_2
                                {
                                	send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 5115, 1, OVER_BODY, PF_STOP );
                                        me->set_save("05115", 0);
                                }                                
                                break;                                
     case EFFECT_CHAR_BLOOD_0 : point = me->get_con() / 10;
     				if (me->is_user())
     					if (me->get_save("char_blood")) point = me->get_save("char_blood");
     				if (me->is_npc())
     					if (me->get("char_blood")) point = me->get("char_blood");     				     				
		               	if (me->is_nianshou())	point =0;
                                send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w", 0x68, getoid(me), point );
                                if( me->add_hp(-point) < 1 ) me->set_hp(1);                 
                                if( !me ) return;

                                if( !get_effect_3(me, EFFECT_CHAR_BLOOD) )    // 循环征状 set_effect_2
                                {
                                	me->delete_save("char_blood");
                                        user = get_scene_object_2(me, USER_TYPE);
                                        send_user( me, "%c%w%w%c", 0x81, 9022, 0, EFFECT_BAD );
                                        send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9022, 0, EFFECT_BAD );
                                        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9022, 1, OVER_BODY, PF_STOP );
                                        set_effect(me, EFFECT_CHAR_BLOOD_0, 2);
                                        me->set_save("char_blood", 0);
                                }
                                break;

     case EFFECT_CHAR_BLIND_0 : send_user(me, "%c%c%c", 0x3d, 243, 0);    // 玩家正常
                                user = get_scene_object_2(me, USER_TYPE);
                                send_user( me, "%c%w%w%c", 0x81, 9024, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9024, 0, EFFECT_BAD );
                                set_effect(me, EFFECT_CHAR_BLIND_0, 2);  
                                break;

      case EFFECT_USER_BURN_0 : point = me->get_save("pf.burn");
		               	if (me->is_nianshou())	point =0;
		               	point += random(20);
                                send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w", 0x68, getoid(me), point );
				if( me->add_hp(-point) < 1 ) me->set_hp(1);
                                if( !get_effect_3(me, EFFECT_USER_BURN) )    // 循环征状 set_effect_2
                                {
                                	me->delete_save("pf.burn");
                                        user = get_scene_object_2(me, USER_TYPE);
                                        send_user( me, "%c%w%w%c", 0x81, 9026, 0, EFFECT_BAD );
                                        send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9026, 0, EFFECT_BAD );
                                        set_effect(me, EFFECT_USER_BURN_0, 2);  
                                        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9026, 1, OVER_BODY, PF_STOP );
                                }
                                break;
     case EFFECT_CHAR_NO_MOVE : user = get_scene_object_2(me, USER_TYPE);
     				CHAR_CHAR_D->init_loop_perform(me);
                                send_user( me, "%c%w%w%c", 0x81, 9002, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9002, 0, EFFECT_BAD );
                                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9012, 1, OVER_BODY, PF_STOP );
                                send_user( user, "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(me), 34721, 10, UNDER_FOOT, 34722, 10, UNDER_FOOT, PF_STOP );
                                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 34821, 10, UNDER_FOOT, PF_STOP );
                                send_user(me, "%c%c%c", 0x3d, 241, 2);
                                me->set_enemy(0);
                                break;    
	case EFFECT_1808:       user = get_scene_object_2(me, USER_TYPE);
				CHAR_CHAR_D->init_loop_perform(me);
                                send_user( me, "%c%w%w%c", 0x81, 1808, 0, EFFECT_GOOD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 1808, 0, EFFECT_GOOD );
                                USER_ENERGY_D->count_max_hp(me);
                                break;    
	case EFFECT_1809:       user = get_scene_object_2(me, USER_TYPE);
				CHAR_CHAR_D->init_loop_perform(me);
                                send_user( me, "%c%w%w%c", 0x81, 1809, 0, EFFECT_GOOD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 1809, 0, EFFECT_GOOD );
                                USER_ENERGY_D->count_max_mp(me);
                                break;    
	case EFFECT_1810:       user = get_scene_object_2(me, USER_TYPE);
				CHAR_CHAR_D->init_loop_perform(me);
                                send_user( me, "%c%w%w%c", 0x81, 1810, 0, EFFECT_GOOD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 1810, 0, EFFECT_GOOD );
                                USER_ENERGY_D->count_sp(me);
                                break;   
	case EFFECT_1811:       user = get_scene_object_2(me, USER_TYPE);
				CHAR_CHAR_D->init_loop_perform(me);
                                send_user( me, "%c%w%w%c", 0x81, 1811, 0, EFFECT_GOOD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 1811, 0, EFFECT_GOOD );
                                USER_ENERGY_D->count_dp(me);
                                break;                                                                                                                                               
	case EFFECT_CHAR_IGNORE:
        			send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 42531, 1, OVER_BODY, PF_STOP );                
                                break;  
	case EFFECT_CHAR_GOOD_BAD:
        			send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 42531, 1, OVER_BODY, PF_STOP );                
                                break;  
	case EFFECT_CHAR_SOUL_LOCK:
        			send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 42531, 1, OVER_BODY, PF_STOP );                
                                break;  

        }
}

void into_effect_2( object me, int flag )    // NPC 使用
{
        object *user, owner;
        int point;

        switch( flag )
        {
     	    case EFFECT_SLEEP : user = get_scene_object_2(me, USER_TYPE);
     				CHAR_CHAR_D->init_loop_perform(me);
                                send_user( me, "%c%w%w%c", 0x81, 9002, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9002, 0, EFFECT_BAD );
                                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9015, 1, OVER_BODY, PF_STOP );
                                me->set_enemy(0);
                                break;         	
     case EFFECT_CHAR_FAINT_0 : user = get_scene_object_2(me, USER_TYPE);
     				CHAR_CHAR_D->init_loop_perform(me);
                                send_user( me, "%c%w%w%c", 0x81, 9002, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9002, 0, EFFECT_BAD );
                                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9002, 1, OVER_BODY, PF_STOP );
                                set_effect(me, EFFECT_CHAR_FAINT_0, 2);
                                me->set_enemy(0);
                                break;

     case EFFECT_CHAR_FAINT_3 : user = get_scene_object_2(me, USER_TYPE);
                                send_user( me, "%c%w%w%c", 0x81, 9002, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9002, 0, EFFECT_BAD );
                                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9002, 1, OVER_BODY, PF_STOP );
                                set_effect(me, EFFECT_CHAR_FAINT_3, 10);
                                me->set_enemy(0);
                                break;

    case EFFECT_CHAR_FREEZE_0 : // set_effect(me, EFFECT_CHAR_FREEZE_0, 2);  
    				me->set_enemy(0);
                                break;

      case EFFECT_CHAR_SHUT_0 : user = get_scene_object_2(me, USER_TYPE);
                                send_user( me, "%c%w%w%c", 0x81, 3482, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3482, 0, EFFECT_BAD );
                                CHAR_CHAR_D->init_loop_perform(me);
                                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 34821, 1, UNDER_FOOT, PF_STOP );
                                // set_effect(me, EFFECT_CHAR_SHUT_0, 2);  
                                break;

     case EFFECT_CHAR_NO_PF_0 : // set_effect(me, EFFECT_CHAR_NO_PF_0, 2);  
                                CHAR_CHAR_D->effect_no_pf_done(me);
                                break;

      case EFFECT_CHAR_LAZY_0 : send_user(me, "%c%c%c", 0x3d, 241, 2);    // 恢复走路步数
                                user = get_scene_object_2(me, USER_TYPE);
                                send_user( me, "%c%w%w%c", 0x81, 9013, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9013, 0, EFFECT_BAD );
                                set_effect(me, EFFECT_CHAR_LAZY_0, 2);  
        			send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9012, 1, OVER_BODY, PF_STOP );
                                break;

      case EFFECT_CHAR_SLOW_0 : user = get_scene_object_2(me, USER_TYPE);
                                send_user( me, "%c%w%w%c", 0x81, 9012, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9012, 0, EFFECT_BAD );
                                set_effect(me, EFFECT_CHAR_SLOW_0, 2);  
				send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 34821, 1, UNDER_FOOT, PF_STOP );
                                break;

     case EFFECT_CHAR_DREAM_1 : GO_CMD->main_npc( me, sprintf("%d", random(8) + 1 ) );    // 随机走路(系统不需校验)
                                set_effect_2(me, EFFECT_CHAR_DREAM, 6, 1);
                                send_user( me, "%c%w%w%c", 0x81, 9016, get_effect_3(me, EFFECT_CHAR_DREAM), EFFECT_BAD );
//                              send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9016, 1, EFFECT_BAD );
                                break;

     case EFFECT_CHAR_DREAM_0 : GO_CMD->main_npc( me, sprintf("%d", random(8) + 1 ) );    // 随机走路(系统不需校验)

                                if( !get_effect_3(me, EFFECT_CHAR_DREAM) )    // 循环征状 set_effect_2
                                {
                                        user = get_scene_object_2(me, USER_TYPE);
                                        send_user( me, "%c%w%w%c", 0x81, 9016, 0, EFFECT_BAD );
                                        send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9016, 0, EFFECT_BAD );
                                        set_effect(me, EFFECT_CHAR_DREAM_0, 2);
                                        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 53112, 1, OVER_BODY, PF_STOP );
                                        CHAR_CHAR_D->init_loop_perform(me);
                                }

                                break;

     case EFFECT_CHAR_CHAOS_0 : user = get_scene_object_2(me, USER_TYPE);
                                send_user( me, "%c%w%w%c", 0x81, 9018, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9018, 0, EFFECT_BAD );
                                set_effect(me, EFFECT_CHAR_CHAOS_0, 2);  
                                break;

     case EFFECT_CHAR_WOUND_0 : user = get_scene_object_2(me, USER_TYPE);
                                send_user( me, "%c%w%w%c", 0x81, 9020, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9020, 0, EFFECT_BAD );
                                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9020, 1, OVER_BODY, PF_STOP );
                                set_effect(me, EFFECT_CHAR_WOUND_0, 2);  
                                break;
     case EFFECT_CON_RECOVER :  user = get_scene_object_2(me, USER_TYPE);
                                point = me->get("05115");
                                send_user( user, "%c%d%w", 0x68, getoid(me), -point );
                                me->add_hp(point);
                                if( !get_effect_3(me, EFFECT_CON_RECOVER) )    // 循环征状 set_effect_2
                                {
                                	send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 5115, 1, OVER_BODY, PF_STOP );
                                        me->set("05115", 0);
                                }                                
                                break;   
//     case EFFECT_CHAR_BLOOD_0 : point = me->get("char_blood");
//                                if (me->is_user()) owner = me;
//     				else owner = me->get_owner();
//                                //if (owner) 
//                                send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w", 0x68, getoid(me), point );
//                                if( me->add_hp(-point) < 1 ) me->set_hp(1);                 
//                                if( !me ) return;
//
//                                if( !get_effect_3(me, EFFECT_CHAR_BLOOD) )    // 循环征状 set_effect_2
//                                {
//                                        user = get_scene_object_2(me, USER_TYPE);
//                                        send_user( me, "%c%w%w%c", 0x81, 9022, 0, EFFECT_BAD );
//                                        send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9022, 0, EFFECT_BAD );
//                                        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9022, 1, OVER_BODY, PF_STOP );
//                                        set_effect(me, EFFECT_CHAR_BLOOD_0, 2);
//                                }
//
//                                break;

     case EFFECT_CHAR_BLIND_0 : user = get_scene_object_2(me, USER_TYPE);
                                send_user( me, "%c%w%w%c", 0x81, 9024, 0, EFFECT_BAD );
                                send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9024, 0, EFFECT_BAD );
                                set_effect(me, EFFECT_CHAR_BLIND_0, 2);
                                break;

//      case EFFECT_USER_BURN_0 : point = me->get_2("pf.burn");
//                                send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w", 0x68, getoid(me), point );
//				if( me->add_hp(-point) < 1 ) me->set_hp(1);                 
//      				if( !get_effect_3(me, EFFECT_USER_BURN) )    // 循环征状 set_effect_2
//                                {
//                                	me->delete_2("pf.burn");
//                                        user = get_scene_object_2(me, USER_TYPE);
//                                        send_user( me, "%c%w%w%c", 0x81, 9026, 0, EFFECT_BAD );
//                                        send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9026, 0, EFFECT_BAD );
//                                        set_effect(me, EFFECT_USER_BURN_0, 2);  
//                                        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9026, 1, OVER_BODY, PF_STOP );
//                                }
//                                break;
     case EFFECT_CHAR_NO_MOVE : user = get_scene_object_2(me, USER_TYPE);
     				CHAR_CHAR_D->init_loop_perform(me);
                                send_user( user, "%c%d%w%c%c", 0x83, getoid(me), 9002, 0, EFFECT_BAD );
                                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9002, 1, OVER_BODY, PF_STOP );
                                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9012, 1, OVER_BODY, PF_STOP );
                                send_user( user, "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(me), 34721, 10, UNDER_FOOT, 34722, 10, UNDER_FOOT, PF_STOP );
                                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 34821, 10, UNDER_FOOT, PF_STOP );
                                me->set_enemy(0);
                                break;                                                                
        }
}
