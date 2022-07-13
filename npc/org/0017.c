#include <ansi.h>
#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <city.h>

inherit COMRADE;

void do_info( string arg );

// 函数：是否允许移动
int is_moveable() { return 0; }    // 禁止使用 go 命令

// 函数：是否不能加血
int no_recover() { return 1; }    // 不能使用恢复气血的法术

int no_die() {return 1;}

// 函数：跟随对手(心跳之中调用)
void follow_user() { }    // 禁止跟随敌人

// 函数：构造处理
void create()
{
        //set_name( "Tiễn Tháp" );
        set_name( "Liễu Vọng Tháp" );
        set_char_picid(9901);    // 人物缺省造型

     	set_max_hp(50000);  set_max_mp(0);
        set_ap( 500);  set_dp(300);  
        set_cp(  0);  set_pp(300);  
        set_sp(0);
        set_attack_speed(15);
        set_hp(get_max_hp());
        set_2( "talk", ([
                "info"          : (: do_info :),
        ]) );
        setup();

        set_char_type(FIGHTER_TYPE);
}

// 函数：设置等级
void set_level( int point )
{
	if (point<6) point = 0;
	else
	if (point<13) point = 1;
	else
	if (point<20) point = 2;
	else point = 3;
        switch( point )
        {
      default : set_max_hp(50000);  set_max_mp(0);
                set_ap( 500);  set_dp(300);  
                set_cp(  0);  set_pp(300);  
                set_sp(0);
                set_attack_speed(15);
                break;
       case 1 : 
       		set_char_picid(9902);
       		set_name( "Mộc Tiễn Tháp" );
       		set_max_hp(80000);  set_max_mp(0);
                set_ap(700);  set_dp(480);  
                set_cp(  0);  set_pp(480);  
                set_sp(0);
                set_attack_speed(15);
                break;
       case 2 : 
       		set_char_picid(9903);
       		set_name( "Thạch Tiễn Tháp" );
       		set_max_hp(150000);  set_max_mp(0);
                set_ap(900);  set_dp(680);  
                set_cp(  0);  set_pp(550);  
                set_sp(0);
                set_attack_speed(15);
                break;
       case 3 : 
       		set_char_picid(9904);
       		set_name( "Cao Cấp Tiễn Tháp" );
       		set_max_hp(300000);  set_max_mp(0);
                set_ap(1300);  set_dp(1000);  
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
        if (me->get_hp()==1) return 0;

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

// 函数：死亡奖励
void win_bonus( object who ) { NPC_BATTLE_D->tower_win_bonus( this_object(), who ); }

// 函数：判断可以战斗
int can_fight( object who ) 
{ 
	object me = this_object();	
        if( me->get_no_fight() ) return 0;
        if( me == who ) return 0;    // 禁止攻击自己	
        if (who->is_npc())
        {
        	if (who->get_char_type()==OFFICER_TYPE) return 0;
        	if (who->get_owner()) who = who->get_owner();        	
        }
        if( me->get_org_name() == who->get_org_name() ) return 0;    // 禁止攻击帮众    // get_org_name() 是字串运算
        if (me->get_hp()==0) return 0;
        if (who->is_npc()) return 1;
        return 0; 
}

// 函数：可以接受战斗
int can_be_fighted( object who ) 
{ 
	string result="", name;
	object orgnpc, obj;
	object me = this_object();
	int science;
        if( me->get_no_fight() ) return 0;
        if (me->get_hp()==0) return 0;        
        name = me->get_org_name();
        if (name=="") return 0;
	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );
	if (!orgnpc) return 0;        
        if( me->get_org_name() == who->get_org_name() ) 
        {
        	if (who->get_org_position()>=8)
        	{
        		obj = previous_object();
        		if (obj)
        		{
        			// 如果是技能判断调用，则直接返回
        			if (obj->get_perform_type()) return 0;
        		}
        		science = orgnpc->get_science();
        		if (me->get_hp()==0)
        		{
        			result = sprintf("该%s已经完全毁坏，重新建造一座新的防御塔需要花费%d金和%d的储备，需时%d秒，一旦决定重新建造便无法中止。你确定重新建造新防御塔吗？\n", me->get_name(), (1+science/5)*250000, (1+science/5)*50, (1+science/5)*15 );
        			result += sprintf(ESC"建造新的%s\ntalk %x# info.1\n", me->get_name(), getoid(me));
        			result += ESC"取消\nCLOSE\n";        			        			
        		}
        		else
        		if (get_effect(me, EFFECT_PROGRESS2)&&me->get_hp()>0&&me->get_progress_arg()!="1")
        		{
        			result = sprintf("该%s的当前耐久为 %d / %d，正在维修中，你要中止防御塔的维修工程吗？\n", me->get_name(), me->get_hp(), me->get_max_hp());
        			result += sprintf(ESC"维修%s\ntalk %x# info.2\n", me->get_name(), getoid(me));
        			result += ESC"取消\nCLOSE\n";        			        			
        		}
        		else
        		if (me->get_hp()<me->get_max_hp())
        		{
        			result = sprintf("该%s的当前耐久为 %d / %d，每5秒恢复500点耐久需要花费帮派资金1000金，你需要维修该防御塔吗？\n", me->get_name(), me->get_hp(), me->get_max_hp());
        			result += sprintf(ESC"维修%s\ntalk %x# info.3\n", me->get_name(), getoid(me));
        			result += ESC"取消\nCLOSE\n";        			
        		}
        		if (result!="") send_user( who, "%c%c%w%s", ':', 3, 0, result );
        	}
        	return 0;    // 禁止攻击帮众    // get_org_name() 是字串运算
        }        
        if (who->is_npc()) return 1;
        return 0; 
}

void do_info( string arg ) 
{ 
	object me = this_object();
	object who = this_player();
	string result="", name;
	object orgnpc;	
	int science, gold, store, time;
	int flag = to_int(arg);
        name = me->get_org_name();
        if (name=="") return ;
	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );
	if (!orgnpc) return ;  	
	switch(flag)
	{
	case 1:
		if (me->get_hp()>0) return;
		science = orgnpc->get_science();
		gold = (1+science/5)*250000;
		store = (1+science/5)*50;
		time = (1+science/5)*15;
		if (orgnpc->get_gold()<gold)
		{
			send_user( who, "%c%c%w%s", ':', 3, 0, "帮派资金不足！" );
			return;
		}
		if (orgnpc->get_store()<store)
		{
			send_user( who, "%c%c%w%s", ':', 3, 0, "帮派储备不足！" );
			return;
		}	
		orgnpc->add_gold(-gold);
		orgnpc->set_store(orgnpc->get_store()-store);	
		set_effect(me, EFFECT_PROGRESS2, time);
		me->set_progress_file(__FILE__);
		me->set_progress_arg("1");
		send_user( who, "%c%c%w%s", ':', 3, 0, "开始建造新的"+me->get_name() );
		break;
	case 2:
		if (get_effect(me, EFFECT_PROGRESS2)&&me->get_hp()>0&&me->get_progress_arg()!="1")
		{
			set_effect(me, EFFECT_PROGRESS2, 0 );	
			send_user( who, "%c%c%w%s", ':', 3, 0, "取消了"+me->get_name()+"的维修。" );
		}
		break;
	case 3:
		if (me->get_hp()<me->get_max_hp())
		{
		        set_effect(me, EFFECT_PROGRESS2, 5);
		        me->set_progress_file(__FILE__);	
		        me->set_progress_arg("2");	
		        send_user( who, "%c%c%w%s", ':', 3, 0, "开始维修"+me->get_name() );
		}
		break;
	}
}

// 函数：法术处理
int into_effect( object me , string arg)
{
	string name;
	object orgnpc;
	name = me->get_org_name();
	if (name=="") return 1;
	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );
	if (!orgnpc) return 1;
	if (arg=="1")
	{
		send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w", 0x68, getoid(me), me->get_hp() - me->get_max_hp() );
		me->set_hp(me->get_max_hp());
		return 1;
	}
	
	if (orgnpc->get_gold()<1000) return;
	if (me->get_hp()>=me->get_max_hp()) return;
	orgnpc->add_gold(-1000);
	me->add_hp(500);
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w", 0x68, getoid(me), -500 );
	if (me->get_hp()>=me->get_max_hp()) return;
	set_effect(me, EFFECT_PROGRESS2, 5);
}


void effect_break(object me, string arg)
{
	set_effect(me, EFFECT_PROGRESS2, 0 );	
}

// 函数：人物心跳处理
void heart_beat_walk( )    // 每 0.1 秒处理
{
        object map, who, *see, *char, me;
        string cmd;
        int z, x, y, x1, y1, dx, p, p2;
        int walk, seek, flag, *dir, i, size;
	me = this_object();
        if(     get_effect(me, EFFECT_CHAR_BUSY)
        ||      get_effect(me, EFFECT_CHAR_FAINT)
        ||      get_effect(me, EFFECT_SLEEP)
        ||      get_effect(me, EFFECT_CHAR_FAINT_2)
        ||      get_effect(me, EFFECT_CHAR_FREEZE) ) 
                return;

        if( !me->get_action() ) return;

        if( who = me->get_main_enemy() )    // 搜索何人攻击(最重要的敌人)
                me->set_enemy(who);
        else
        if (!me->get_enemy())
        {        	
                z = get_z(me);  x = get_x(me);  y = get_y(me);
                seek = me->get_max_seek();

                see = get_range_object(z, x, y, seek, USER_TYPE) + get_range_object(z, x, y, seek, CHAR_TYPE);    // 人物可见范围

                char = filter_array( see, (: objectp($1) && $1->get_org_name() != $2->get_org_name() :), me );    // 所在不同帮派    // get_org_name() 是字串运算
                
                see = filter_array( char, (: $2->can_fight($1) :), me );    // 所在不同帮派    // get_org_name() 是字串运算

                if( objectp(who = get_near_char(see, z, x, y) ) ) 
                {		           	
                	me->auto_fight(who);
                }
        }

        if( gone_time( me->get_attack_time() ) > 10 ) me->init_enemy_damage(0, 0);    // 清除伤害状态

        z = get_z(me);  x = get_x(me);  y = get_y(me);

        if( objectp( who = me->get_enemy() ) )
        {
                if( who->is_die() )
                {
                        me->set_enemy(0); 
                }
                else
                if (distance_between(me, who)>10)
                {
                        me->set_enemy(0); 
                }                
        }
}