
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
int get_char_picid() { return 0550; }

// 函数：构造处理
void create()
{
        set_name("Yên Quốc Đao Thuẫn Binh");

        set_char_type(FIGHTER_TYPE);    // init_level 要用到
        
        set_head_color(0x0);

        NPC_ENERGY_D->init_level( this_object(), 135+ random(5) );    // 
        set_max_seek(4);

        setup();

        set_char_type(FIGHTER_TYPE);    // 重设类型
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：特技攻击对手
int perform_action( object who ) { return 0; }    // XXXXX->perform_action_npc( this_object(), who ); }

// 函数：自动战斗(遇玩家时调用)
// void auto_fight( object who ) { }

// 函数：任务处理(有任务时调用)
void check_legend_task( object who )
{
	int p,i;
	object item;
	if( who->get_legend(TASK_13, 22) && !who->get_legend(TASK_13, 23) && random(100) < 25)
	{
		if ( objectp( item = present("泥雕", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
		{
			if ( item->get_amount() < 10 )
				item->add_amount(1);
		}
		else
		{
			item = new("item/98/0055");
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
		if ( (i=who->add_save_2("gdsnidiao",1)) >= 10 )
		{
			who->set_save_2("gdsnidiao",10);
			who->set_legend(TASK_13, 23);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,20,"泥雕(完成)" );
		}
		USER_TASK_D->send_task_intro(who,2,TID_YANGUO,20);
		send_user(who,"%c%s",'!',sprintf(HIY"泥雕 %d/10",i));		
	}	
	if( who->get_legend(TASK_13, 28) && !who->get_legend(TASK_13, 29) && who->get_save_2("jjdaodunbing") < 20)
	{
		if ( (i=who->add_save_2("jjdaodunbing",1)) >= 20 )
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,22,"安全隐患(完成)" );
			who->set_save_2("jjdaodunbing",20);
			who->set_legend(TASK_13, 29);
		}

		USER_TASK_D->send_task_intro(who,2,TID_YANGUO,22);
		send_user(who,"%c%s",'!',sprintf(HIY"Yên Quốc Đao Thuẫn Binh %d/20",i));		
	}
	if( who->get_legend(TASK_14, 7) && !who->get_legend(TASK_14, 8) && random(100) < 18)
	{
		if ( objectp( item = present("圆环", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
		{
			if ( item->get_amount() < 3 )
				item->add_amount(1);
		}
		else
		{
			item = new("item/98/0058");
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
		if ( (i=who->add_save_2("ysyuanhuan",1)) >= 3 )
		{
			who->set_save_2("ysyuanhuan",3);
			who->set_legend(TASK_14, 8);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,25,"浑仪（1）(完成)" );
		}
		USER_TASK_D->send_task_intro(who,2,TID_YANGUO,25);
		send_user(who,"%c%s",'!',sprintf(HIY"圆环 %d/3",i));		
	}
	if( who->get_legend(TASK_14, 10) && !who->get_legend(TASK_14, 11) && random(100) < 15)
	{
		item = new("item/98/0059");
		if ( !item  )
			return ;
		p = item->move(who,-1);
		if ( !p )
		{
			destruct(item);
			return;
		}
		item->add_to_user(p);
		who->set_legend(TASK_14, 11);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,26,"浑仪（2）(完成)" );
		USER_TASK_D->send_task_intro(who,2,TID_YANGUO,26);
		send_user(who,"%c%s",'!',sprintf(HIY"轴 %d/1",1));		
	}
	if( who->get_legend(TASK_15, 9) && !who->get_legend(TASK_15, 10) && random(100) < 18)
	{
		if ( objectp( item = present("灵芝", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
		{
			if ( item->get_amount() < 3 )
				item->add_amount(1);
		}
		else
		{
			item = new("item/98/0063");
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
		if ( (i=who->add_save_2("frlingzhi",1)) >= 3 )
		{
			who->set_save_2("frlingzhi",3);
			who->set_legend(TASK_15, 10);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,31,"夫人的怪病（2）(完成)" );
		}
		USER_TASK_D->send_task_intro(who,2,TID_YANGUO,31);
		send_user(who,"%c%s",'!',sprintf(HIY"灵芝 %d/3",i));		
	}
	if( who->get_legend(TASK_15, 15) && !who->get_legend(TASK_15, 16) && random(100) < 25)
	{
		if ( objectp( item = present("发夹", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
		{
			if ( item->get_amount() < 10 )
				item->add_amount(1);
		}
		else
		{
			item = new("item/98/0065");
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
		if ( (i=who->add_save_2("cqfajia",1)) >= 10 )
		{
			who->set_save_2("cqfajia",10);
			who->set_legend(TASK_15, 16);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,33,"饰品店(完成)" );
		}
		USER_TASK_D->send_task_intro(who,2,TID_YANGUO,33);
		send_user(who,"%c%s",'!',sprintf(HIY"发夹 %d/10",i));		
	}
	if( who->get_legend(TASK_15, 18) && !who->get_legend(TASK_15, 19) && random(100) < 34)
	{
		if ( objectp( item = present("辣椒", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
		{
			if ( item->get_amount() < 20 )
				item->add_amount(1);
		}
		else
		{
			item = new("item/98/0066");
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
		if ( (i=who->add_save_2("cflajiao",1)) >= 20 )
		{
			who->set_save_2("cflajiao",20);
			who->set_legend(TASK_15, 19);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,34,"爱吃辣的客人(完成)" );
		}
		USER_TASK_D->send_task_intro(who,2,TID_YANGUO,34);
		send_user(who,"%c%s",'!',sprintf(HIY"辣椒 %d/20",i));		
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

                if( p < 5395 * rate / 100 ) ;    // NONE

                else if( p < 5595 * rate / 100 )    // 金钱
                {
                        if( gold >= total ) continue;

                        if( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) )
                        {
                                item = new( "/item/std/0001" );
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                item->set_value( 450 + random(90) );
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                                gold ++;
                        }
                }         
/*              else if( p < 5595 * rate / 100 )    // 武器(基本)
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
                }       */
/*              else if( p < 5595 * rate / 100 )    // 防具(基本)
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
                }       */
                else if( p < 5651 * rate / 100 )    // 武器(门派)
                {
                        if( equip >= total2 ) continue;

                        switch( random(3) )
                        {
                       case 0 : file = WEAPON_FILE->get_weapon_file_2(30);  break;
                       case 1 : file = WEAPON_FILE->get_weapon_file_2(40);  break;
                       case 2 : file = WEAPON_FILE->get_weapon_file_2(50);  break;

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
                }         
                else if( p < 5712 * rate / 100 )    // 防具(门派)
                {
                        if( equip >= total2 ) continue;

                        switch( random(3) )
                        {
                       case 0 : file = ARMOR_FILE->get_armor_file_2(30);  break;
                       case 1 : file = ARMOR_FILE->get_armor_file_2(40);  break;
                       case 2 : file = ARMOR_FILE->get_armor_file_2(50);  break;

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
                }         
                else if( p < 9350 * rate / 100 )    // 杂物１
                {
                        switch( random(3) )
                        {
                       case 0 : file = "/item/40/4052";  break;
                       case 1 : file = "/item/40/4031";  break;
                       case 2 : file = "/item/40/4030";  break;

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
                else if( p < 9850 * rate / 100 )    // 杂物２
                {
                        switch( random(5) )
                        {
                       case 0 : file = "/item/stuff/0047";  break;
                       case 1 : file = "/item/stuff/0047";  break;
                       case 2 : file = "/item/stuff/0190";  break;
                       case 3 : file = "/item/stuff/0049";  break;
                       case 4 : file = "/item/32/3285";  break;

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
                else if( p < 9950 * rate / 100 )    // 杂物３
                {
                        switch( random(2) )
                        {
                       case 0 : file = "/item/stuff/0312";  break;
                       case 1 : file = "/item/stuff/0032";  break;

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
                else if( p < 10000 * rate / 100 )    // 杂物４
                {
                        switch( random(1) )
                        {
                       case 0 : file = "/item/stuff/0311";  break;

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
/*              else if( p < 610000 * rate / 100 )    // 杂物５
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
