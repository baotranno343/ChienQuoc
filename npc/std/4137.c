
#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <action.h>

int is_caster(){return 1;}

inherit SLAVE;

int get_max_level0() { return 3;}
int is_smart_caster() {return 1;}

// 函数：获取召唤兽类型
int get_zombie_type() { return SOLDIER_TYPE_1; }     // 判断种类

// 函数：构造处理
void create()
{
        set_name("Song Phủ Vương");
        set_char_picid(9970);

        setup();
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// --------------------------------------------------------------- 远程调用 ----

// 函数：升级处理
void upgrade_level( int level ) { __FILE__ ->upgrade_level_callout( this_object(), level ); }

// 函数：升级处理(在线更新)
void upgrade_level_callout( object me, int level )
{
        switch( level )
        {
       case 1 : me->set_char_type(SLAVE_TYPE_1);
                break;
       case 2 : me->set_char_type(SLAVE_TYPE_2);                
                break;
       case 3 : me->set_char_type(SLAVE_TYPE_3);
                break;
       case 4 : me->set_char_type(SLAVE_TYPE_4);
                break;
      default : me->set_char_type(SLAVE_TYPE_5);
                me->set_char_picid(4141);

                break;
        }
        me->set_attack_speed(25);
        me->set_walk_speed(3);
        me->set_walk_step(2);
}

// 函数：升级处理
void upgrade_level_2( int level ) { __FILE__ ->upgrade_level_2_callout( this_object(), level ); }

// 函数：升级处理(在线更新)
void upgrade_level_2_callout( object me, int level )
{
        object owner;
        int hp, cp, pp, level0;

        if( level > 1 ) if( objectp( owner = me->get_owner() ) && owner->is_user() )
        {
        	level0 = me->get_level_0();
                cp = owner->get_cp();
                pp = owner->get_pp();
                me->add_max_hp( 90 );  
                me->add_max_mp( 30 );  
                me->set_hp(me->get_max_hp());
                me->set_mp(me->get_max_mp());
                me->add_dp( 5 );
                me->add_cp( 15 );
                me->add_pp( 5 );
        }
}

// 函数：特技攻击对手
int perform_action( object who ) { return __FILE__ ->perform_action_npc( this_object(), who ); }

// 函数：命令处理
int perform_action_npc( object me, object who )
{
        int level;
	object * user;
	int z, x0, y0, x1, y1;
        if( !inside_screen_2(me, who) ) return 0;
        level = me->get_level_0();
        if (me->get_mp()<5) 
        {
        	NPC_SLAVE_D->follow_owner(me);
        	if (time() - me->get("say_time") >20)
        	{
        		"/cmd/base/say"->say(me, "Chém...Chém...");
        		me->set("say_time", time());
        	}
        	return 1;
        }
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
        level = me->get_level_0();
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
	if (me)
	{
		me->add_mp(-5);
		owner = me->get_owner();
		if (owner) send_user( owner, "%c%c%d%c", 0x2c, 4, getoid(me), me->get_mp()*50/me->get_max_mp());
	}
        return 2;    // 执行成功
}

