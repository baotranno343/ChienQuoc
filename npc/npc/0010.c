
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
int get_char_picid() { return 0010; }

// 函数：构造处理
void create()
{
        set_name("Gà Núi");

        set_char_type(FIGHTER_TYPE);    // init_level 要用到
        
        set_head_color(0x0);

        NPC_ENERGY_D->init_level( this_object(), 1+ random(2) );    // 
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

void check_legend_task_call( object who,object npc ) 
{ 
	int i,p;
	object item;
	if( who->get_legend(TASK_40, 17) && !who->get_legend(TASK_40, 18) && who->get_save("dplbxiaogw") < 3 )
	{
		if ( (i=who->add_save("dplbxiaogw",1)) >= 3 )
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,32,"锻炼自己(完成)" );
			who->set_legend(TASK_40, 18);
		}
		USER_TASK_D->send_task_intro(who,2,TID_NEWBIE_01,32);
		send_user(who,"%c%s",'!',sprintf(HIY"锻炼自己 %d/3",i));		
	}
	if ( who->get_legend(TASK_48, 1) && who->get_save("new_sj") < 5 )
	{
		i = who->add_save("new_sj",1);
		if ( i >= 5 )
		{
			who->set_legend(TASK_48, 2);
	                send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,101,"Thủ Thuật Nhỏ (Hoàn thành)" );
			i = 5;
		}
		send_user(who,"%c%s",'!',sprintf("Thủ Thuật Nhỏ( Hoàn thành) %d /5",i));
		USER_TASK_D->send_task_intro(who,2,TID_NEWBIE_01,101);	
	}
	if ( who->get_legend(TASK_NEWBIE_02,4) && !who->get_legend(TASK_NEWBIE_02,5) && who->get_save_2("newbie_sanji") < 10 )
	{
		i = who->add_save_2("newbie_sanji",1);
		if ( i >= 10 )
		{
			who->set_legend(TASK_NEWBIE_02,5);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,15,"讨厌的山鸡(已经完成)" );
			i = 10;
		}
		send_user(who,"%c%s",'!',sprintf("讨厌的山鸡 完成 %d/10",i));
		USER_TASK_D->send_task_intro(who,2,TID_NEWBIE_01,15);	
	}
	if( who->get_legend(TASK_41, 1) && !who->get_legend(TASK_41, 2) && who->get_save("wdzxiaosj") < 5 )
	{
		if ( (i=who->add_save("wdzxiaosj",1)) >= 5 )
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,31,"妖言惑众(完成)" );
			who->set_legend(TASK_41, 2);
		}
		USER_TASK_D->send_task_intro(who,2,TID_NEWBIE_01,31);
		send_user(who,"%c%s",'!',sprintf(HIY"Gà Núi %d/5",i));		
	}
	if ( who->get_legend(TASK_41,6) && !who->get_legend(TASK_41,7) && random(100)<40 )
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
		who->set_legend(TASK_41, 7);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,28,"疑难杂症（2）(完成)" );
		USER_TASK_D->send_task_intro(who,2,TID_NEWBIE_01,28);
		send_user(who,"%c%s",'!',HIY"雄黄散 1/1");		
	}
	if ( who->get_legend(TASK_41,13) && !who->get_legend(TASK_41,14) && random(100)<45 )
	{
		if ( objectp( item = present("百合花", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
		{
			if ( item->get_amount() < 3 )
				item->add_amount(1);
			p = 1;
		}
		else
		{
			item = new("item/98/0202");
			if ( item  )
			{
				p = item->move(who,-1);
				if ( !p )
				{
					destruct(item);
				}
				else
					item->add_to_user(p);
			}
		}
		if ( p )
		{		
			if ( (i=who->add_save("wdzbaihh",1)) >= 3 )
			{
				who->set_legend(TASK_41,14);
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,30,"装饰房屋(完成)" );
			}
			send_user(who,"%c%s",'!',sprintf(HIY"百合花 %d/3",i));
			USER_TASK_D->send_task_intro(who,2,TID_NEWBIE_01,30);
		}			
	}
}
// 函数：任务处理(有任务时调用)
void check_legend_task( object who ) { __FILE__->check_legend_task_call(who,this_object()); }

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
/*if(who->get_save_2("kiemtradanhanchua.score") == 1)
{
				if(who->add_save_2("soquaicandiet.score")>=3)
				{
								send_user(who,"%c%s",'!',sprintf("Nhiệm vụ Sứ giả đã hoàn thành"));
								return 0;
				}
				who->add_save_2("soquaicandiet.score",1);
				send_user(who,"%c%s",'!',sprintf("Đã giết được %d/3",who->get_save_2("soquaicandiet.score")));
}*/
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

                if( p < 4322 * rate / 100 ) ;    // NONE

/*              else if( p < 4322 * rate / 100 )    // 金钱
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
                else if( p < 4376 * rate / 100 )    // 武器(基本)
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
                else if( p < 4700 * rate / 100 )    // 防具(基本)
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
/*              else if( p < 4700 * rate / 100 )    // 武器(门派)
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
/*              else if( p < 4700 * rate / 100 )    // 防具(门派)
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
                else if( p < 9900 * rate / 100 )    // 杂物１
                {
                        switch( random(2) )
                        {
                       case 0 : file = "/item/40/4002";  break;
                       case 1 : file = "/item/40/4001";  break;

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
/*              else if( p < 9900 * rate / 100 )    // 杂物２
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
/*              else if( p < 10000 * rate / 100 )    // 杂物５
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
