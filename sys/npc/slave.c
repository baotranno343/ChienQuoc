
#include <cmd.h>
#include <ansi.h>
#include <skill.h>
#include <effect.h>

// 函数：生成二进制码
void SAVE_BINARY() {}

/*
object get_near_object2(object * char, int z, int x, int y)
{
	int i, size, min, cur_i;
	int x0, y0, z0, dx, dy;
	size = sizeof(char);
	cur_i = -1;
	if ( size==0 ) return 0;	
	for (i=0;i<size;i++)
	{
		if (!char[i]) continue;
		z0 = get_z(char[i]);
		x0 = get_x(char[i]);
		y0 = get_y(char[i]);
		if (z0!=z) continue;
		if (cur_i==-1)
		{
			dx = abs(x-x0);
			dy = abs(y-y0);
			if (dx>dy) min=dx;
			else min=dy;
			cur_i = i;
		}
		else
		{
			dx = abs(x-x0);
			dy = abs(y-y0);
			if (dx>dy) dy=dx;
			if (min>dy)
			{
				min = dy;
				cur_i = i;
			}			
		}
	}
	if (cur_i==-1) return 0;
	return char[cur_i];
}       */

int upgrade_level_need(object me);
void follow_owner(object me);

// 函数：召唤兽升级
void upgrade_level(object me)
{
        object owner;
        string result;
        int level, ret;

        level = me->get_level_2();
        ret = upgrade_level_need(me);
        // send_user(owner, "%c%s", '!', sprintf("%d", ret));

        if (ret > 0)
                return;
        me->set("mk", -ret);
        level++;
        me->set_level_2(level);
        me->upgrade_level(level);
        me->upgrade_level_2(level);

        if (objectp(owner = me->get_owner()) && owner->is_user())
        {
                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9045, 1, OVER_BODY, PF_ONCE);

                result = sprintf(HIC "%s tăng lên cấp %d!", me->get_name(), level);
                send_user(owner, "%c%s", '!', result);
                send_user(owner, "%s", ECHO + result);
                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9045, 1, OVER_BODY, PF_ONCE);
        }
}

// 函数：获取升级所需
int upgrade_level_need(object me)
{
        int level1, level2, level3, need, max_level;
        object owner;
        owner = me->get_owner();
        if (!owner)
                return MAX_NUMBER;
        level1 = owner->get_level();
        level2 = me->get_level_0();
        level3 = me->get_level_2();
        max_level = me->get_max_level0();
        if (max_level == 0)
                max_level = 3;
        if (level3 >= max_level)
                return MAX_NUMBER;
        //	need = 100 + level3 * (level1+level2)* level2 / 3;
        need = (level2 + level3) * (level2 + level3) * (level2 + level3) / 40 * 2;
        need -= me->get("mk");
        return range_value(need, -MAX_NUMBER, MAX_NUMBER);
}

// 函数：搜索敌人(心跳之中调用)
void find_enemy(object me)
{
        object who, *see, *char, npc;
        object soldier, *zombie;
        int z, x, y, z1, x1, y1, p;
        int i, size;

        if (!objectp(who = me->get_owner()))
                return;

        if (distance_between(me, who) >= 25 && me->get_action() != 0) // 回到主人身边
        {
                z = get_z(who);
                x = get_x(who);
                y = get_y(who);
                if (p = get_valid_xy(z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK))
                {
                        x1 = p / 1000;
                        y1 = p % 1000;
                        me->add_to_scene(z, x1, y1, get_front_xy(x1, y1, x, y), 9413, 0, 9413, 0);
                }
        }
        if (me->get_action() == 0)
                return; // 不攻击
        if (me->get_action_mode() != 1)
                return; // 在回主人身边的时候不攻击

        if (objectp(me->get_enemy()))
                return; // 有对手就不寻找

        if (objectp(npc = who->get_enemy()) && inside_screen_2(who, npc) && inside_screen_2(me, npc)) // 主人攻击目标
        {
                if (me->get_enemy() != npc)
                        me->set_fight_time(time());
                me->set_enemy(npc);
                return;
        }
        /*
        z = get_z(me);  x = get_x(me);  y = get_y(me);
        see = get_range_object(z, x, y, 10, USER_TYPE) + get_range_object(z, x, y, 10, CHAR_TYPE);    // 天兵可见范围

        char = filter_array( see, (: objectp($1) && $1->get_enemy() == $2 :), who );    // 对主人有敌意

        if( objectp(npc = get_near_char(char, z, x, y) ) )
        {
                if( me->get_enemy() != npc ) me->set_fight_time( time() );
                me->set_enemy(npc);
                return;
        }

        char = filter_array( see, (: objectp($1) && $1->get_enemy() == $2 :), me );    // 对自己有敌意

        if( objectp(npc = get_near_char(char, z, x, y) ) )
        {
                if( me->get_enemy() != npc ) me->set_fight_time( time() );
                me->set_enemy(npc);
                return;
        }

        char = ({ });

        if( objectp( soldier = who->get("soldier") ) )    // 其它天兵攻击目标
        {
                if( objectp( npc = soldier->get_enemy() ) ) char += ({ npc });
        }
        if( arrayp( zombie = who->get("zombie") ) )
        {
                for( i = 0, size = sizeof(zombie); i < size; i ++ ) 
                        if( zombie[i] && objectp( npc = zombie[i]->get_enemy() ) ) char += ({ npc });
        }
        char = see - ( see - char );  

        if( objectp(npc = get_near_char(char, z, x, y) ) )
        {
                if( me->get_enemy() != npc ) me->set_fight_time( time() );
                me->set_enemy(npc);
                return;
        }

        char = ({ });

        if( objectp( soldier = who->get("soldier") ) )    // 对其它天兵有敌意
        {
                char += filter_array( see, (: objectp($1) && $1->get_enemy() == $2 :), soldier );
        }
        if( arrayp( zombie = who->get("zombie") ) )
        {
                for( i = 0, size = sizeof(zombie); i < size; i ++ ) if( zombie[i] )
                        char += filter_array( see, (: objectp($1) && $1->get_enemy() == $2 :), zombie[i] );
        }

        if( objectp(npc = get_near_char(char, z, x, y) ) )
        {
                if( me->get_enemy() != npc ) me->set_fight_time( time() );
                me->set_enemy(npc);
                return;
        }

        if(     objectp( npc = who->get_enemy() )    // who->get_main_enemy()
        &&      inside_screen_2(who, npc) && inside_screen_2(me, npc) )    // 对主人造成伤害
        {
                if( me->get_enemy() != npc ) me->set_fight_time( time() );
                me->set_enemy(npc);
                return;
        }
       
        if (me->get_action_mode()!=1) return;	// 不主动攻击别人        

        if( inside_screen_2(me, who) )    // 搜索(主人)最近怪物
        {
                if( MAP_D->is_inside_battle(z) )    // 战场之上
                {
                        char = filter_array( see, (: objectp($1) && $1->get_org_name() != $2->get_org_name() && $1->is_seller()==0 :), who );    // 所在不同帮派

                        if( objectp(npc = get_near_char(char, z, x, y) ) )
                        {
                                if( me->get_enemy() != npc ) me->set_fight_time( time() );
                                me->set_enemy(npc);
                                return;
                        }
                }
                else    // 平时场景
                {
                        x = get_x(who);  y = get_y(who);
                        if( npc = get_near_object(z, x, y, 10, CHAR_TYPE) )
                                if( npc->is_badman() ) me->start_fight(npc);
                }
        }
*/
}

// 函数：人物心跳处理
void heart_beat_walk(object me) // 每 0.1 秒处理
{
        object owner, who;
        string cmd;
        int x, y, x1, y1, p, walk;
        owner = me->get_owner();
        if (get_effect(me, EFFECT_CHAR_BUSY) || get_effect(me, EFFECT_CHAR_FAINT) || get_effect(me, EFFECT_SLEEP) || get_effect(me, EFFECT_CHAR_FAINT_2) || get_effect(me, EFFECT_CHAR_FREEZE))
                return;
        who = me->get_main_enemy();
        if (me->get_action() == 2 && me->get_action_mode() != 1 && !who)
        {
                follow_owner(me);
                return;
        }
        if (time() - me->get("2122") < 6)
                ;
        else if (who) // 搜索何人攻击(最重要的敌人)
        {
                if (me->get_enemy() != who)
                        me->set_fight_time(time());
                me->set_enemy(who);
        }
        else
                find_enemy(me); // 搜索攻击对象

        if (gone_time(me->get_fight_time()) > 110) // 110 秒打不死
        {
                me->init_enemy_damage(0, 0); // 清除伤害状态
                me->set_enemy(0);
                find_enemy(me); // 搜索攻击对象
        }
        x = get_x(me);
        y = get_y(me);

        if (objectp(who = me->get_enemy()) && !who->is_die())
                me->follow_user();
        else if (objectp(owner = me->get_owner()))
        {
                if (me->get_action() == 0)
                        return;
                follow_owner(me);
                return;
        }
        x = abs(x - get_x(me));
        y = abs(y - get_y(me));
        walk = (x > y) ? x : y;

        if (walk > 0)
        {
                set_heart_state(me, WALK_STAT);
                set_heart_count_2(me, me->get_walk_speed() * walk); // walk * 10 / 4
                                                                    //                if (owner) tell_user(owner, "时间 %d 步数 %d 间隔 %d 步速 %d", get_heart_timer(me), walk, get_heart_count_2(me), me->get_walk_speed() );
        }
}

// 函数：判断可以战斗
int can_fight(object me, object who)
{
        object owner, enemy;

        if (me->get_no_fight())
                return 0;
        if (me == who)
                return 0; // 禁止攻击自己

        if (!(owner = me->get_owner()))
                return 0;
        if (owner == who)
                return 0; // 禁止攻击主人

        if (me->get_enemy() == who)
                return 1; // 有对手则继续

        if ((enemy = who->get_enemy()) == me || enemy == owner)
                return 1; // 攻击敌意对象

        return owner->can_fight(who); // 主人能否攻击
}

void add_slave_exp(object me, int exp)
{
        object *npc, *zombie, soldier;
        int i, size, exp2, maxlevel;
        npc = ({});
        if (objectp(soldier = me->get("soldier")))
        {
                if (soldier->get_level_2() < 5)
                        npc += ({soldier});
        }
        if (arrayp(zombie = me->get("zombie")) && arrayp(zombie = filter_array(zombie - ({0}), (
                                                                                                   : $1->get_owner() == $2:),
                                                                               me)) // 清除叛变的怪
            && (size = sizeof(zombie)))                                             // zombie -= ({ 0 })
        {
                for (i = 0; i < size; i++)
                        if (soldier = zombie[i])
                        {
                                maxlevel = soldier->get_max_level0();
                                if (maxlevel == 0)
                                        maxlevel = 3;
                                if (soldier->get_level_2() < maxlevel)
                                        npc += ({soldier});
                        }
        }
        size = sizeof(npc);
        if (size == 0)
                return;
        exp2 = exp * 20 / 50 / size;
        if (exp2 < 1)
                exp2 = 1;
        for (i = 0; i < size; i++)
        {
                npc[i]->add("mk", exp2);
                upgrade_level(npc[i]);
        }
}

void follow_owner(object me)
{
        object owner, who;
        string cmd;
        int x, y, z, x1, y1, p, walk;
        x = get_x(me);
        y = get_y(me);
        if (objectp(owner = me->get_owner()))
        {
                x1 = get_x(owner);
                y1 = get_y(owner);
                z = get_z(owner);
                if (z != get_z(owner) || distance_between(me, owner) >= 25 && me->get_action() != 0) // 回到主人身边
                {
                        if (p = get_valid_xy(z, x1 + random(3) - 1, y1 + random(3) - 1, IS_CHAR_BLOCK))
                        {
                                x1 = p / 1000;
                                y1 = p % 1000;
                                me->add_to_scene(z, x1, y1, get_front_xy(x1, y1, x, y), 9413, 0, 9413, 0);
                        }
                        return;
                }

                if (abs(x - x1) < 2 && abs(y - y1) < 2)
                {
                        me->set_action(me->get_next_action());
                        return;
                }

                if (x1 > x)
                        x1--;
                else if (x1 < x)
                        x1++;
                if (y1 > y)
                        y1--;
                else if (y1 < y)
                        y1++;

                if (x != x1 || y != y1)
                {
                        if (p = get_valid_path(get_z(me), x, y, x1, y1))
                        {
                                cmd = sprintf("%d", p);

                                switch (me->get_walk_step())
                                {
                                case 0:
                                case 1:
                                        if (strlen(cmd) > 1)
                                                cmd = cmd[0..0];
                                        break;
                                case 2:
                                        if (strlen(cmd) > 2)
                                                cmd = cmd[0..1];
                                        break;
                                default:
                                        break;
                                }
                                GO_CMD->main_npc(me, cmd);
                        }
                }
        }

        x = abs(x - get_x(me));
        y = abs(y - get_y(me));
        walk = (x > y) ? x : y;

        if (walk > 0)
        {
                set_heart_state(me, WALK_STAT);
                set_heart_count_2(me, me->get_walk_speed() * walk); // walk * 10 / 4
                                                                    //                if (owner) tell_user(owner, "时间 %d 步数 %d 间隔 %d 步速 %d", get_heart_timer(me), walk, get_heart_count_2(me), me->get_walk_speed() );
        }
}