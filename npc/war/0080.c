#include <ansi.h>
#include <city.h>
#include <npc.h>
#include <equip.h>
#include <skill.h>

inherit COMRADE;

// 函数：是否允许移动
int is_moveable() { return 0; }    // 禁止使用 go 命令

int is_anti_effect() {return 1;}   // 禁止effect

// 函数：是否不能加血
int no_recover() { return 1; }    // 不能使用恢复气血的法术

// 函数：跟随对手(心跳之中调用)
void follow_user() { }    // 禁止跟随敌人

int get_comrade_type() {return 80;}

// 函数：构造处理
void create()
{
        //set_name( "箭塔" );
        set_name( " " );
        set_char_picid(9901);    // 人物缺省造型

        set_walk_speed(10);  set_attack_speed(15);
        set_max_seek(10);    // 全屏搜索
	set_level(1);
        setup();

        set_char_type(FIGHTER_TYPE);
}

// 函数：设置等级
void set_level( int point )
{
        switch( point )
        {
       case 1 : 
       		set_name("了望塔");
       		set_max_hp(5000);  set_max_mp(0);
                set_ap(300);  set_dp(120);  
                set_cp(  0);  set_pp(120);  
                set_sp(0);		
                set_attack_speed(15);
                break;
       case 2 : 
       		set_name("木箭塔");
       		set_char_picid(9902);
       		set_max_hp(10000);  set_max_mp(0);
                set_ap(450);  set_dp(300);  
                set_cp(  0);  set_pp(300);  
                set_sp(0);		
                set_attack_speed(15);
                break;         
       case 3 : 
       		set_name("石箭塔");
       		set_char_picid(9903);
       		set_max_hp(20000);  set_max_mp(0);
                set_ap(600);  set_dp(680);  
                set_cp(  0);  set_pp(500);  
                set_sp(0);		
                set_attack_speed(15);
                break;         
       case 4 : 
       		set_name("高级箭塔");
       		set_char_picid(9904);
       		set_max_hp(40000);  set_max_mp(0);
                set_ap(750);  set_dp(1000);  
                set_cp(  0);  set_pp(890);  
                set_sp(0);		
                set_attack_speed(10);
                break;                                    
        }
}

// 函数：获取装备代码
int get_weapon_code() { return THROWING; }

// 函数：特技攻击对手
int perform_action( object who ) { return __FILE__ ->perform_action_npc( this_object(), who ); }

// 函数：命令处理
int perform_action_npc( object me, object who )
{
        int x, y;

        x = get_x(who);  y = get_y(who);
        if( !inside_screen_2(me, who) ) return 0;

        me->to_front_xy(x, y);
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 0, get_d(me), getoid(who) );

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( who->get_char_id() );

        return 1;
}

// 函数：法术处理
int cast_done_npc( object me )
{
        object who, owner;
        string arg;
        int z, x0, y0, x1, y1;
        int ap, damage;

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( !objectp( who = find_char(arg) ) ) return 1;

        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 10120, 1, OVER_BODY, PF_ONCE );

        // CHAR_FIGHT_D->throwing_done(me, who, HIT_NORMAL);    // 以下复制自 CHAR_FIGHT_D ##########

        if( !who || !who->can_be_fighted(me) || !me->can_fight(who) ) return 1;

        z = get_z(me);  x0 = get_x(me);  y0 = get_y(me);  x1 = get_x(who);  y1 = get_y(who);

        if( !inside_screen_2(me, who) ) return 1;
        if( !from_to(z, x0, y0, x1 - x0, y1 - y0, MAP_BLOCK ) ) return 1;
        CHAR_FIGHT_D->throwing_done(me, who, HIT_NORMAL);
/*
        ap = me->get_ap();

        me->to_front_xy(x1, y1);

        if( who->is_npc() )
        {
                if( who->get_enemy_4() == me ) 
                        who->set_attack_time( time() );    // 同一个人：更新持续时间
                else if( gone_time( who->get_attack_time() ) > 5 )
                {
                        who->set_enemy_4(me);
                        who->set_attack_time( time() );    // 不同的人：更新持续敌手
                }
                if( !who->get_max_damage() ) who->init_enemy_damage(me, 0);    // 记录最强伤害(NPC)
        }

        damage = ap - ap * 100 / 10 / 100;

	if (who->is_user()) owner = who;
	else owner = who->get_owner();
        if (owner) send_user( owner, "%c%d%w%c%d%w%c", 0x48, getoid(who), damage, get_d(who), getoid(me), HIT_NORMAL, 2 );

        if( who->is_user() ) CHAR_FIGHT_D->wear_down(who);    // 击中减少耐久

        CHAR_DIE_D->is_enemy_die(me, who, damage);
        if( me->get_hp() < 1 ) CHAR_DIE_D->is_enemy_die(who, me, 0);
*/
        return 2;    // 执行成功
}

// 函数：掉宝奖励
void win_bonus( object who ) { __FILE__ ->win_bonus2( this_object(), who ); }

// 函数：掉宝奖励(在线更新)
void win_bonus2( object me, object who )
{
	int random, number;
	object item;
	string id, owner;
	string name, result, leader, file;
	object orgnpc, *team;
	int size, i, level2, exp2, level, exp;	
	int p, x, y, z;
	int drop = 5;
	if (who->is_npc())
	{
		who = who->get_owner();
	}
	if (!who) return;
	if (who->is_npc()) return;	
	
	if (random(100)<30)
	{
                if( load_object( file = "sys/item/product"->get_random_mid_product() ) )
                {
                        item = new( file );
                }
		if (!item) return;
	        id = who->get_leader();
	        if (!id) owner = who->get_id();
	        z = get_z(me);  x = get_x(me);  y = get_y(me);	
	        TEAM_D->drop_item(item,who);
	        item->set_user_id(owner);
	        if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
	        {
		        item->add_to_scene(z, p / 1000, p % 1000);
		        item->set("winner", who);
		        item->set( "time", time() );
		}
		else destruct(item);
	}
	
        name = who->get_org_name();
        if (name=="") return;
	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );	
	if (!objectp(orgnpc)) return;        
	orgnpc->add_wood(drop);
	result = sprintf("你消灭了%s，为帮派获得了%d个木材。", me->get_name(), drop);
	tell_user( who, ECHO + result );	
	
	number = who->get_number();
	orgnpc->set_member_contribute(number, orgnpc->get_member_contribute(number)+5);
	result = sprintf("你消灭了%s，得到了%d点帮派贡献。", me->get_name(), 5);
	tell_user( who, ECHO + result );	
	
        if( (leader=who->get_leader()) && arrayp( team = who->get_team() ) && sizeof(team) > 1 )
        {
                team = me->correct_bonus_team(team);
                size = sizeof(team);
        }
        else    size = 1;

        exp = NPC_ENERGY_D->get_exp_bonus(level);    // 查表取值
        switch(me->get_char_picid())
        {
        case 9901: exp = 500; break;
        case 9902: exp = 1000; break;
        case 9903: exp = 2000; break;
        case 9904: exp = 4000; break;
        }       
        if( size > 1 )    // 多人
        {
                for( i = 0; i < size; i ++ ) if( team[i] )
                {
                        exp2 = exp*(10+size-1)/10;
                        if (exp2<1) exp2 = 1;
                        exp2 = exp2 * team[i]->get_online_rate() / 100; 
                        team[i]->add_exp(exp2);
			NPC_SLAVE_D->add_slave_exp(team[i], exp2);
			NPC_PET_D->fight_bonus(team[i],me,size,0,0);
                        team[i]->add_log("&battle", exp2);
			team[i]->add_log("#battle", 1);                        	
                }
        }
        else    // 单人
        {
        	exp2 = exp;
        	exp2 = exp2 * who->get_online_rate() / 100; 
                who->add_exp(exp2);
                NPC_SLAVE_D->add_slave_exp(who, exp2);
		NPC_PET_D->fight_bonus(who,me,1,0,0);

                who->add_log("&battle", exp2);                
                who->add_log("#battle", 1);
        }
	
	
}


void upgrade(int level)
{
	int hp;
	object me = this_object();
	hp = me->get_max_hp();
        me->set_max_hp(me->get_max_hp()*12/10);
        me->add_ap(30);
        me->add_hp(me->get_max_hp()-hp);
        me->set_level(level);
}