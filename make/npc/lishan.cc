
// 自动生成：/make/npc/makelishan.c

#include <npc.h>
#include <equip.h>
#include <skill.h>

inherit "/inh/npc/copy_npc";

//副本怪
int is_copy_npc() { return 1; }

// 函数：远程攻击的怪
%s int is_caster() { return 1; }

// 函数：是否允许移动
%s int is_moveable() { return 0; }    // 禁止使用 go 命令

// 函数：跟随对手(心跳之中调用)
%s void follow_user() { }    // 禁止跟随敌人

// 函数：获取人物造型
int get_char_picid() { return %04d; }

// 函数：构造处理
void create()
{
        set_name("%s");

        set_char_type(%s);    // init_level 要用到
        
        set_head_color(0x%x);
	set_walk_speed(%d);
	set_attack_speed(%d);
        NPC_ENERGY_D->init_copy_npc( this_object(), %d+ random(%d),({"%s","%s","%s"}) );    // 
        set_max_seek(%d);
	set_walk_step(2);
	set_enmity_flag(1);
        setup();

	set("anti_05311",1);	//不能迷魂
        set_char_type(%s);    // 重设类型
}

// 函数：获取装备代码
int get_weapon_code() { return %s; }

// 函数：特技攻击对手
int perform_action( object who ) { return %s->perform_action_npc( this_object(), who ); }

// 函数：自动战斗(遇玩家时调用)
%s void auto_fight( object who ) { }

// 函数：任务处理(有任务时调用)
%s void check_legend_task( object who ) { USER_TASK_D->kill_legend_npc( who, this_object() ); }

// 函数：掉宝奖励
void drop_items( object who ) { __FILE__ ->drop_items_callout( this_object(), who ); }

// 函数：掉宝奖励(在线更新)
void drop_items_callout( object me, object who )
{
        object item, leader;
        string file, owner, id;
        int p, rate, i, size, gold, equip, total, total2 ;
        int z, x, y;

        z = get_z(me);  x = get_x(me);  y = get_y(me);
        id = who->get_leader();
        if (!id) owner = who->get_id();
        else
        {
        	if ( leader = find_player(id ) )
        	{
        		owner = leader->get_id();
		}      
		else
			owner = who->get_id();  		
	}

%s      p = random(100);  size = ( p > 2 ) ? 1 : ( p > 0 ) ? 2 : 8;  total = 2;  total2 = 3;
%s      p = random(100);  size = ( p > 40 ) ? 3 : 10;  total = 2;  total2 = 3;

        rate = me->correct_drop_rate( me->get_level() - who->get_level() ) * who->get_online_rate() / 100;

        for( i = 0; i < size; i ++ )
        {
                p = random(%d);

                if( p < %d * rate / 100 ) ;    // NONE

%s              else if( p < %d * rate / 100 )    // 金钱
                {
                        if( gold >= total ) continue;

                        if( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) )
                        {
                                item = new( "/item/std/0001" );
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                item->set_value( %d + random(%d) );
                                item->add_to_scene(z, p / 1000, p %% 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                                gold ++;
                        }
                }       %s
%s              else if( p < %d * rate / 100 )    // 武器(基本)
                {
                        if( equip >= total2 ) continue;

                        file = WEAPON_FILE->get_weapon_file_0(%d);
                        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                        {
                                item = new(file);
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                ITEM_EQUIP_D->init_equip_prop(item);
                                item->add_to_scene(z, p / 1000, p %% 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                                equip ++;
                        }
                }       %s
%s              else if( p < %d * rate / 100 )    // 防具(基本)
                {
                        if( equip >= total2 ) continue;

                        file = ARMOR_FILE->get_armor_file_0(%d);
                        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                        {
                                item = new(file);
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                ITEM_EQUIP_D->init_equip_prop(item);
                                item->add_to_scene(z, p / 1000, p %% 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                                equip ++;
                        }
                }       %s
%s              else if( p < %d * rate / 100 )    // 武器(门派)
                {
                        if( equip >= total2 ) continue;

                        switch( random(%d) )
                        {
%s
                      default : break;
                        }
                        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                        {
                                item = new(file);
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                ITEM_EQUIP_D->init_equip_prop(item);
                                item->add_to_scene(z, p / 1000, p %% 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                                equip ++;
                        }
                }       %s
%s              else if( p < %d * rate / 100 )    // 防具(门派)
                {
                        if( equip >= total2 ) continue;

                        switch( random(%d) )
                        {
%s
                      default : break;
                        }
                        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                        {
                                item = new(file);
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                ITEM_EQUIP_D->init_equip_prop(item);
                                item->add_to_scene(z, p / 1000, p %% 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                                equip ++;
                        }
                }       %s
%s              else if( p < %d * rate / 100 )    // 杂物１
                {
                        switch( random(%d) )
                        {
%s
                      default : break;
                        }
                        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                        {
                                item = new(file);
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                item->add_to_scene(z, p / 1000, p %% 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                        }
                }       %s
%s              else if( p < %d * rate / 100 )    // 杂物２
                {
                        switch( random(%d) )
                        {
%s
                      default : break;
                        }
                        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                        {
                                item = new(file);
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                item->add_to_scene(z, p / 1000, p %% 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                        }
                }       %s
%s              else if( p < %d * rate / 100 )    // 杂物３
                {
                        switch( random(%d) )
                        {
%s
                      default : break;
                        }
                        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                        {
                                item = new(file);
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                item->add_to_scene(z, p / 1000, p %% 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                        }
                }       %s
%s              else if( p < %d * rate / 100 )    // 杂物４
                {
                        switch( random(%d) )
                        {
%s
                      default : break;
                        }
                        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                        {
                                item = new(file);
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                item->add_to_scene(z, p / 1000, p %% 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                        }
                }       %s
%s              else if( p < %d * rate / 100 )    // 杂物５
                {
                        switch( random(%d) )
                        {
%s
                      default : break;
                        }
                        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                        {
                                item = new(file);
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                item->add_to_scene(z, p / 1000, p %% 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                        }
                }       %s

        }       
}
