 
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;

// 函数：远程攻击的怪
// int is_caster() { return 1; }

// 函数：是否允许移动
// int is_moveable() { return 0; }    // 禁止使用 go 命令

// 函数：跟随对手(心跳之中调用)
// void follow_user() { }    // 禁止跟随敌人

// 函数：获取人物造型
int get_char_picid() { return 0150; }

// 函数：构造处理
void create()
{
        set_name("Ong Mật");

        set_char_type(FIGHTER_TYPE);    // init_level 要用到
        
        set_head_color(0xfac1);

        NPC_ENERGY_D->init_level( this_object(), 2+ random(2) );    // 
        set_max_seek(4);

        setup();

        set_char_type(FIGHTER_TYPE);    // 重设类型
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：特技攻击对手
int perform_action( object who ) { return 0; }    // XXXXX->perform_action_npc( this_object(), who ); }

// 函数：自动战斗(遇玩家时调用)
void auto_fight( object who ) { }

// 函数：任务处理(有任务时调用)
void check_legend_task( object who ) 
{
	int p,i;
	object item;
	//掉铁锤
	if ( who->get_legend(TASK_48, 15) && !who->get_legend(TASK_48, 16) && random(100) < 45 )
	{
		item = new( "/item/98/9882" );
		if ( item )
		{
			p =item->move(who, -1);
	               	if ( p == 0 )
	                {
	                	destruct(item); 
				return;
	                }
	                else
	                {
	                	who->set_legend(TASK_48, 16);
	                	item->add_to_user(p);
	                	send_user(who,"%c%s",'!',"你得到了铁锤");
	                	send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,107,"修理店老板的铁锤(完成)" );
	                	USER_TASK_D->send_task_intro(who,2,TID_NEWBIE_01,107);
	                }
	        }
	}
	if( who->get_legend(TASK_NEWBIE_02, 24) && !who->get_legend(TASK_NEWBIE_02, 25) && who->get_save_2("xiaomao_fengmi") <3)
	{
		if ( objectp( item = present("蜜糖", who, 1, MAX_CARRY) ) && item->is_mitang() == 1 ) 
		{
			if ( item->get_amount() < 3 )
				item->add_amount(1);
		}
		else
		{
			item = new("item/98/9891");
			if ( !item  )
				return ;
			p = item->move(who,-1);
			if ( !p )
			{
				destruct(item);
				return;
			}
			item->add_to_user(p);
		}
		if ( (i=who->add_save_2("xiaomao_fengmi",1)) >= 3 )
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YEWAI,1,"" );
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YEWAI,"清溪" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YEWAI,1,"美味的蜜糖(已经完成)" );
			who->set_save_2("xiaomao_fengmi",3);
		}
		else
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YEWAI,1,"" );
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YEWAI,"清溪" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YEWAI,1,"美味的蜜糖" );
		}
		
		send_user(who,"%c%s",'!',sprintf(HIY"蜜糖 %d/3",i));		
	}
	if( who->get_legend(TASK_NEWBIE_02, 26) && !who->get_legend(TASK_NEWBIE_02, 27) && who->get_save_2("xiaomifeng" )< 8 )	
	{
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YEWAI,2,"" );
		send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YEWAI,"清溪" );
		if ( (i=who->add_save_2("xiaomifeng",1)) >= 8 )
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YEWAI,2,"乱蛰人的小蜜蜂(已经完成)" );
		}
		else
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YEWAI,2,"乱蛰人的小蜜蜂" );
		send_user( who, "%c%s",'!',sprintf("乱蛰人的小蜜蜂 %d/8",i));
	}
	if ( who->get_legend(TASK_48, 18) && !who->get_legend(TASK_48, 19) && who->get_save("new_chy") < 8 )
	{
		i = who->add_save("new_chy",1);
		if ( i >= 8 )
		{
			who->set_legend(TASK_48, 19);
	                send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,108,"妖言惑众(完成)" );
			i = 8;
		}
		send_user(who,"%c%s",'!',sprintf("妖言惑众 完成 %d/8",i));
		USER_TASK_D->send_task_intro(who,2,TID_NEWBIE_01,108);	
	}
	//掉雄黄散
	if ( who->get_legend(TASK_48,23) && !who->get_legend(TASK_48,24) && random(100)<40 )
	{
		item = new("item/98/0199");
		if ( !item  )
			return ;
		p = item->move(who,-1);
		if ( !p )
		{
			destruct(item);
			return;
		}
		item->add_to_user(p);
		who->set_legend(TASK_48, 24);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,110,"疑难杂症（2）(完成)" );
		USER_TASK_D->send_task_intro(who,2,TID_NEWBIE_01,110);
		send_user(who,"%c%s",'!',HIY"Bột Hùng Hoàng 1/1");		
	}
}
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

        p = random(100);  size = ( p > 2 ) ? 1 : ( p > 0 ) ? 2 : 8;  total = 2;  total2 = 3;
//      p = random(100);  size = ( p > 40 ) ? 3 : 10;  total = 2;  total2 = 3;

        rate = me->correct_drop_rate( me->get_level() - who->get_level() ) * who->get_online_rate() / 100;

        for( i = 0; i < size; i ++ )
        {
                p = random(10000);

                if( p < 3840 * rate / 100 ) ;    // NONE

/*              else if( p < 3840 * rate / 100 )    // 金钱
                {
                        if( gold >= total ) continue;

                        if( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) )
                        {
                                item = new( "/item/std/0001" );
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                item->set_value( 0 + random(0) );
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                                gold ++;
                        }
                }       */
                else if( p < 3984 * rate / 100 )    // 武器(基本)
                {
                        if( equip >= total2 ) continue;

                        file = WEAPON_FILE->get_weapon_file_0(0);
                        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                        {
                                item = new(file);
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                ITEM_EQUIP_D->init_equip_prop(item);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                                equip ++;
                        }
                }         
                else if( p < 4200 * rate / 100 )    // 防具(基本)
                {
                        if( equip >= total2 ) continue;

                        file = ARMOR_FILE->get_armor_file_0(0);
                        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                        {
                                item = new(file);
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                ITEM_EQUIP_D->init_equip_prop(item);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                                equip ++;
                        }
                }         
/*              else if( p < 4200 * rate / 100 )    // 武器(门派)
                {
                        if( equip >= total2 ) continue;

                        switch( random(0) )
                        {

                      default : break;
                        }
                        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                        {
                                item = new(file);
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                ITEM_EQUIP_D->init_equip_prop(item);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                                equip ++;
                        }
                }       */
/*              else if( p < 4200 * rate / 100 )    // 防具(门派)
                {
                        if( equip >= total2 ) continue;

                        switch( random(0) )
                        {

                      default : break;
                        }
                        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                        {
                                item = new(file);
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                ITEM_EQUIP_D->init_equip_prop(item);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                                equip ++;
                        }
                }       */
                else if( p < 9400 * rate / 100 )    // 杂物１
                {
                        switch( random(1) )
                        {
                       case 0 : file = "/item/40/4005";  break;

                      default : break;
                        }
                        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                        {
                                item = new(file);
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                        }
                }         
                else if( p < 9900 * rate / 100 )    // 杂物２
                {
                        switch( random(1) )
                        {
                       case 0 : file = "/item/stuff/0169";  break;

                      default : break;
                        }
                        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                        {
                                item = new(file);
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                        }
                }         
                else if( p < 10000 * rate / 100 )    // 杂物３
                {
                        switch( random(1) )
                        {
                       case 0 : file = "/item/41/4111";  break;

                      default : break;
                        }
                        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                        {
                                item = new(file);
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                        }
                }         
/*              else if( p < 10000 * rate / 100 )    // 杂物４
                {
                        switch( random(0) )
                        {

                      default : break;
                        }
                        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                        {
                                item = new(file);
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                        }
                }       */
/*              else if( p < 40000 * rate / 100 )    // 杂物５
                {
                        switch( random(0) )
                        {

                      default : break;
                        }
                        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                        {
                                item = new(file);
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                        }
                }       */

        }       
}
