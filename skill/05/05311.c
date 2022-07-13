
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <npc.h>

#define THIS_SKILL      0531
#define THIS_PERFORM    05311
#define PF_START       "05311"
#define PF_NAME        "Mê Hồn"

#define SKILL_LEVEL     15
#define TIME_INTERVAL   3
#define SUB_MP          25

#define MAX_ZOMBIE      1

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 15 cấp\n    Mê hồn quái vật để thu phục. Khả năng Mê hồn thành công phụ thuộc vào cấp độ võ công";
        result = sprintf(HIC" %s \n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Mê hồn quái vật để thu phục. Khả năng Mê hồn thành công phụ thuộc vào cấp độ võ công", 
        	PF_NAME, SKILL_LEVEL, SUB_MP, TIME_INTERVAL);
        return result;
}

// 函数：获取描述(持续)
string get_loop_desc( object me )
{
        if( get_effect(me, EFFECT_NPC_0531_2) )
                return sprintf( PF_NAME "：\n　　%s Mê Hồn.\n\nLiên tục thời gian： %s\n",
                        me->get_name(), get_effect(me, EFFECT_NPC_0531_2) );
        else    return sprintf( PF_NAME "\n" );
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int z;
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

        if( who )
        {
                if( !inside_screen_2(me, who) ) return 1;

                x = get_x(who);  y = get_y(who);
        }
        else if( objectp( who = me->get_enemy_2() ) && inside_screen_2(me, who) )
        {
                x = get_x(who);  y = get_y(who);
        }
        else
        {
                z = get_z(me);

                if( !inside_screen( get_x(me), get_y(me), x, y ) ) return 1;
                if( !objectp( who = get_xy_object(z, x, y, CHAR_TYPE) ) && !objectp( who = get_xy_object(z, x, y, USER_TYPE) ) ) 
                {
                        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
                        me->set_time( "pf", time() );

                        me->to_front_xy(x, y);
                        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );

                        me->add_mp(-mp);

                        set_heart_state(me, MAGIC_STAT);
                        set_heart_count_2(me, 5);
                        me->add_2("go_count.count2",5);
                        me->set_cast_file(__FILE__);
                        me->set_cast_arg( sprintf( "%d,%d,%d", z, x, y ) );

                        return 1;
                }
        }
	if (who->is_anti_effect()) return 1;
        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        me->set_enemy_2(who);    // 远程目标锁定

        me->to_front_xy(x, y);
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );

        me->add_mp(-mp);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
         me->add_2("go_count.count2",5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s,%d", who->get_char_id(), level ) );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        object *user, *char, soldier;
        object map, who, enemy;
        string arg;
        int z, x, y, p;
        int level, rate, i, size;        

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( sscanf(arg, "%d,%d,%d", z, x, y) == 3 )
        {
                send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%w%c%c%c", 0x4f, x, y, 
                        53111, 1, OVER_BODY, 53112, 1, OVER_BODY, PF_ONCE );

                return 1;    // 打到空地
        }
        if( sscanf(arg, "%s,%d", arg, level) != 2 ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;

        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who), 
                5311, 1, OVER_BODY, 5311, 1, OVER_BODY, PF_ONCE );

        if( who->get_owner() == me ) return 2;    // 执行成功
        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功

        if( who->is_badman() )    // 只能控制野外的怪
        {
        	if (who->get_char_type()==FIGHTER_TYPE_2 || who->get("anti_05311"))
                {
                        write_user( me, ECHO "Bạn không thể khống chế %s.", who->get_name() );
                        return 2;    // 执行成功
                }   
        	if (who->get_level()>me->get_level())
                {
                        write_user( me, ECHO "Bạn không khống chế được %s.", who->get_name() );
                        return 2;    // 执行成功
                }                      	
                soldier = me->get("soldier");
                if (objectp(soldier))
                {
                        write_user( me, "Bạn đã mê hồn quái vật" );
                        return 2;    // 执行成功
                }  

	        if ( who && !who->is_die() )
	        	CHAR_FIGHT_D->set_enmity(me,who,80);

//                if( size < MAX_ZOMBIE && size < level / 19 )
                {
                        rate = 7 + ( level + me->get_level() - who->get_level() * 2 ) / 3;

                        if( rate < 1 )
                        {
                                write_user( me, ECHO "Bạn không thể khống chế %s.", who->get_name() );
                                return 2;    // 执行成功
                        }

                        if( rate > 7 ) rate = 7;
                        
//                        if(me->get_real_id()=="ten") rate = 100;

                        if( random(100) < rate )
                        {
                                if( enemy = who->get_owner() )    // 取消原主人
                                {
                                        enemy->set("soldier", 0);
                                }

                                if(     who->get_char_type() == FIGHTER_TYPE_2 
                                &&     !who->is_have_been_slave() )    // 首次被魅惑时
                                {
                                        p = who->get_hp();  who->add_max_hp( - p / 3 );  who->set_hp(p);
                                        p = who->get_mp();  who->add_max_mp( - p / 3 );  who->set_mp(p);
                                        who->add_ap( - who->get_ap() / 3 );
                                        who->add_dp( - who->get_dp() / 3 );
                                        who->add_cp( - who->get_cp() / 3 );
                                        who->add_pp( - who->get_pp() / 3 );
                                        who->add_sp( - who->get_sp() / 3 );
                                }
                                who->have_been_slave(1);    // 记录曾被魅惑，不再掉宝
                                if ( (enemy = who->get_enemy()) && (enemy->get_enemy()== who) ) enemy->set_enemy(0);  
                                who->set_enemy(0);          
                                who->init_enemy_damage(0, 0);      
                                user = get_scene_object_2(who, USER_TYPE);
                                if( get_heart_state(who) == MAGIC_STAT ) send_user( user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END );    // 结束施法动作               
                                if( me->get_enemy() == who ) me->stop_fight();    // me->set_enemy(0);
                                who->set_owner(me);
                                who->upgrade_level( who->get_level_2() );
                                who->set_name( sprintf( "%s(%s)", get_file_name(who)->get_name(), me->get_name() ) );
                                who->set_level_0(level);    // 迷魂诀

                                who->set_city_name( me->get_city_name() );    // 用于战场
                                who->set_org_name( me->get_org_name() );

//                              who->set_action(1);
                                who->be_zombie(1);
//                                set_effect( who, EFFECT_NPC_0531_2, (30 + level) * 60 );
                                z = get_z(who);  x = get_x(who);  y = get_y(who);
                                move_object(who, z, x, y, USER_TYPE);

                                if( map = get_map_object(z) ) 
                                {
                                        map->delete_fighter(who);
                                        map->delete_caster(who);
                                        map->delete_boss(who);
                                }

                                me->set("soldier", who );

                                who->stop_fight();

                                char = get_range_object(z, x, y, 20, USER_TYPE) + get_range_object(z, x, y, 20, CHAR_TYPE) - ({ who });
                                for( i = 0, size = sizeof(char); i < size; i ++ )
                                        if( char[i] && char[i]->get_enemy() == who ) char[i]->stop_fight();

                                who->Action_Mode(2);
			        send_user(me, "%c%c%d%s", 0x2c, 1, getoid(who), who->get_name() );
			        send_user(me, "%c%c%d%w%w%w", 0x2c, 2, getoid(who), 1, 2, 3 );
			        send_user(me, "%c%c%d%c", 0x2c, 3, getoid(who), 50 );
			        send_user(me, "%c%c%d%c", 0x2c, 4, getoid(who), 50 );
			        send_user(me, "%c%c%d%c", 0x2c, 5, getoid(who), 2 );
			        send_user(me, "%c%c%d%c", 0x2c, 6, getoid(who), 2 );			                                        
			        send_user(me, "%c%c%d%w%w", 0x2c, 7, getoid(who), get_x(who), get_y(who) );
        			send_user(me, "%c%c%d%d", 0x2c, 8, getoid(who), who->get_char_picid() );
                                return 2;    // 执行成功
                        }
                        else 
                        {
//                              CHAR_DIE_D->is_enemy_die(me, who, 0);

                                if( random(100) < 50 )
                                {
                                        who->set_action(0);    // 被我魅惑
                                        user = get_scene_object_2(who, USER_TYPE);
                                        set_effect(who, EFFECT_NPC_0531_1, 10);
                                      send_user( who, "%c%w%w%c", 0x81, 5311, get_effect_3(who, EFFECT_NPC_0531_1), EFFECT_GOOD );
                                        send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 5311, 1, EFFECT_GOOD );
                                        CHAR_CHAR_D->init_loop_perform(who);
                                        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 5311, 1, OVER_BODY, PF_LOOP );
                                }

                                return 2;    // 执行成功
                        }
                }
        }
        else if( who->is_zombie() )    // 只能魅惑野外的怪，及玩家的召唤兽    // who->is_badman() || who->is_zombie()
        {
//              CHAR_DIE_D->is_enemy_die(me, who, 0);

	        if ( who && !who->is_die() )
	        	CHAR_FIGHT_D->set_enmity(me,who,80);

                rate = 7 + ( level + me->get_level() - who->get_level() * 2 ) / 3;

                if( rate < 1 )
                {
                        write_user( me, ECHO "Bạn không thể mê hồn %s.", who->get_name() );
                        return 2;    // 执行成功
                }

                if( random(100) < 50 )
                {
                        who->set_action(0);    // 被我魅惑
                        user = get_scene_object_2(who, USER_TYPE);
                        set_effect(who, EFFECT_NPC_0531_1, 10);
//                      send_user( who, "%c%w%w%c", 0x81, 5311, get_effect_3(who, EFFECT_NPC_0531_1), EFFECT_GOOD );
                        send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 5311, 1, EFFECT_GOOD );
                        CHAR_CHAR_D->init_loop_perform(who);
                        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 5311, 1, OVER_BODY, PF_LOOP );
                }

                return 2;    // 执行成功
        }

        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数：能否使用特技
void can_perform( object me )
{
	int interval;
        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }

        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, PF_NAME );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, PF_NAME );
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0,10, MAGIC_ACT_BEGIN, 0, 5, 0);
}
