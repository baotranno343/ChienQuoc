
#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <action.h>

int is_caster(){return 1;}

inherit SLAVE;
int cannot_enter_city() { return 1; }

// 函数：获取召唤兽类型
int get_zombie_type() { return SOLDIER_TYPE_1; }     // 判断种类

// 函数：构造处理
void create()
{
        set_name("Quỷ Tốt");
        set_char_picid(4131);
        set_attack_speed(25);
        set_walk_speed(3);
        set_walk_step(2);
	set_head_color(0x2);
        setup();
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// --------------------------------------------------------------- 远程调用 ----



// 函数：特技攻击对手
int perform_action( object who ) { return __FILE__ ->perform_action_npc( this_object(), who ); }

// 函数：命令处理
int perform_action_npc( object me, object who )
{
        int level;
	object * user;
	int z, x0, y0, x1, y1;
        if( !inside_screen_2(me, who) ) return 0;

        z = get_z(me);  x0 = get_x(me);  y0 = get_y(me);  x1 = get_x(who);  y1 = get_y(who);
        if( !from_to(z, x0, y0, x1 - x0, y1 - y0, MAP_BLOCK) ) 
        {
        	NPC_SLAVE_D->follow_owner(me);
        	return 1;
        }
	user = get_scene_object_2(me, USER_TYPE);
        me->to_front_xy(x1, y1);        
        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( who->get_char_id() );
        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%d%w%w%d%w%c%c%w%c%c", 0x8a, getoid(me), time2(),
                get_x(me), get_y(me), getoid(who), 9901, 1, OVER_BODY, 9902, 1, OVER_BODY );
        return 1;
}

// 函数：法术处理
int cast_done_npc( object me )
{
        object who, owner, *user;
        string arg;
        int z, x0, y0, x1, y1, level;
        int ap, damage;
        user = get_scene_object_2(me, USER_TYPE);
        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( !objectp( who = find_char(arg) ) ) return 1;

        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 10120, 1, OVER_BODY, PF_ONCE );

        // CHAR_FIGHT_D->throwing_done(me, who, HIT_NORMAL);    // 以下复制自 CHAR_FIGHT_D ##########

        if( !who || !who->can_be_fighted(me) || !me->can_fight(who) ) return 1;

        z = get_z(me);  x0 = get_x(me);  y0 = get_y(me);  x1 = get_x(who);  y1 = get_y(who);

        if( !inside_screen_2(me, who) ) return 1;
        if( !from_to(z, x0, y0, x1 - x0, y1 - y0, MAP_BLOCK ) ) return 1;


	if (who->is_user()) owner = who;
	else owner = who->get_owner();
        if (owner) send_user( owner, "%c%d%w%c%d%w%c", 0x48, getoid(who), damage, get_d(who), getoid(me), HIT_NORMAL, 2 );
	CHAR_FIGHT_D->cast_done(me, who, 0);

        return 2;    // 执行成功
}

// 函数：死亡奖励
void win_bonus( object who ) { __FILE__ ->win_bonus_callout( this_object(), who ); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout( object me, object who )
{
	int level,level2,exp=100;
	object owner;
	
        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return ;

	level = me->get_level();
	level2 = level - who->get_level();
	exp = me->correct_exp_bonus(level, level2, exp) * who->get_online_rate() / 100;
	who->add_exp(exp);
}
