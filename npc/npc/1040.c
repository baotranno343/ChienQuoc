
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>
inherit BADMAN;

// 函数：远程攻击的怪
   int is_caster() { return 1; }

// 函数：是否允许移动
// int is_moveable() { return 0; }    // 禁止使用 go 命令

// 函数：跟随对手(心跳之中调用)
// void follow_user() { }    // 禁止跟随敌人

// 函数：获取人物造型
int get_char_picid() { return 0402; }

// 函数：构造处理
void create()
{
        set_name("Quy Tiên Nhân");

        set_char_type(FIGHTER_TYPE);    // init_level 要用到
        
        set_head_color(0x0);

        NPC_ENERGY_D->init_level( this_object(), 100+ random(4) );    // 
        set_max_seek(6);

        setup();

        set_char_type(FIGHTER_TYPE);    // 重设类型
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：特技攻击对手
int perform_action( object who ) { return PF_FILE_04232->perform_action_npc( this_object(), who ); }

// 函数：自动战斗(遇玩家时调用)
// void auto_fight( object who ) { }

// 函数：任务处理(有任务时调用)
void check_legend_task( object who )
{
	int p,i,iRate;
	object item;

	if( who->get_legend(TASK_36, 3) && !who->get_legend(TASK_36, 4) )
	{
		if ( who->get_save("qwwmzhuhjs") < 3 && random(100) < 25 )
		{
			if ( objectp( item = present("完美朱红晶石", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
			{
	
				if ( item->get_amount() < 3 )
					item->add_amount(1);
			}
			else
			{
	
				item = new("item/98/0162");
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
			i=who->add_save("qwwmzhuhjs",1);
			send_user(who,"%c%s",'!',sprintf(HIY"完美朱红晶石 %d/3",i));		
			USER_TASK_D->send_task_intro(who,2,TID_QIGUO,51);
		}
		else if ( who->get_save("qwwmbaijs") < 4 && random(100) < 26 )
		{
			if ( objectp( item = present("完美白晶石", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
			{
	
				if ( item->get_amount() < 4 )
					item->add_amount(1);
			}
			else
			{
	
				item = new("item/98/0163");
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
			i=who->add_save("qwwmbaijs",1);
			send_user(who,"%c%s",'!',sprintf(HIY"完美白晶石 %d/4",i));		
			USER_TASK_D->send_task_intro(who,2,TID_QIGUO,51);
		}
		else if ( who->get_save("qwwmhuangjs") < 3 && random(100) < 25 )
		{
			if ( objectp( item = present("完美黄晶石", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
			{
	
				if ( item->get_amount() < 3 )
					item->add_amount(1);
			}
			else
			{
	
				item = new("item/98/0164");
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
			i=who->add_save("qwwmhuangjs",1);
			send_user(who,"%c%s",'!',sprintf(HIY"完美黄晶石 %d/3",i));		
			USER_TASK_D->send_task_intro(who,2,TID_QIGUO,51);
		}
		if ( who->get_save("qwwmzhuhjs") >= 3 && who->get_save("qwwmbaijs") >= 4 && who->get_save("qwwmhuangjs") >= 3 )
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,51,"完美宝石（2）(完成)" );
			who->set_legend(TASK_36, 4);
		}
	}
	if( who->get_legend(TASK_36, 6) && !who->get_legend(TASK_36, 7) )
	{
		if ( who->get_save("qwgushihui") < 5 && random(100) < 26 )
		{
			if ( objectp( item = present("古石灰", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
			{
	
				if ( item->get_amount() < 5 )
					item->add_amount(1);
			}
			else
			{
	
				item = new("item/98/0165");
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
			i=who->add_save("qwgushihui",1);
			send_user(who,"%c%s",'!',sprintf(HIY"古石灰 %d/5",i));		
			USER_TASK_D->send_task_intro(who,2,TID_QIGUO,52);
		}
		else if ( who->get_save("qwcishi") < 7 && random(100) < 28 )
		{
			if ( objectp( item = present("慈石", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
			{
	
				if ( item->get_amount() < 7 )
					item->add_amount(1);
			}
			else
			{
	
				item = new("item/98/0166");
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
			i=who->add_save("qwcishi",1);
			send_user(who,"%c%s",'!',sprintf(HIY"慈石 %d/7",i));		
			USER_TASK_D->send_task_intro(who,2,TID_QIGUO,52);
		}
		else if ( who->get_save("qwxionghuang") < 3 && random(100) < 25 )
		{
			if ( objectp( item = present("雄黄", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
			{
	
				if ( item->get_amount() < 3 )
					item->add_amount(1);
			}
			else
			{
	
				item = new("item/98/0167");
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
			i=who->add_save("qwxionghuang",1);
			send_user(who,"%c%s",'!',sprintf(HIY"雄黄 %d/3",i));		
			USER_TASK_D->send_task_intro(who,2,TID_QIGUO,52);
		}
		if ( who->get_save("qwgushihui") >= 5 && who->get_save("qwcishi") >= 7 && who->get_save("qwxionghuang") >= 3 )
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,52,"完美宝石（3）(完成)" );
			who->set_legend(TASK_36, 7);
		}
	}
	if( who->get_legend(TASK_36, 11) && !who->get_legend(TASK_36, 12) && who->get_save("qgdjjguixr") < 11 )
	{
		if ( (i=who->add_save("qgdjjguixr",1)) >= 11 && who->get_save("qgdjjguanzx") >= 8 )
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,53,"临危不惧(完成)" );
			who->set_legend(TASK_36, 12);
		}
		USER_TASK_D->send_task_intro(who,2,TID_QIGUO,53);
		send_user(who,"%c%s",'!',sprintf(HIY"Quy Tiên Nhân %d /11",i));		
	}
	if( who->get_legend(TASK_36, 20) && !who->get_legend(TASK_36, 21) )
	{
		if ( who->get_save("qgbxfansu") < 8 && random(100) < 23 )
		{
			if ( objectp( item = present("番薯", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
			{
	
				if ( item->get_amount() < 8 )
					item->add_amount(1);
			}
			else
			{
	
				item = new("item/98/0169");
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
			i=who->add_save("qgbxfansu",1);
			send_user(who,"%c%s",'!',sprintf(HIY"番薯 %d/8",i));		
			USER_TASK_D->send_task_intro(who,2,TID_QIGUO,56);
		}
		else if ( who->get_save("qgbxsanyao") < 5 && random(100) < 20 )
		{
			if ( objectp( item = present("山药", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
			{
	
				if ( item->get_amount() < 5 )
					item->add_amount(1);
			}
			else
			{
	
				item = new("item/98/0170");
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
			i=who->add_save("qgbxsanyao",1);
			send_user(who,"%c%s",'!',sprintf(HIY"山药 %d/5",i));		
			USER_TASK_D->send_task_intro(who,2,TID_QIGUO,56);
		}
		
		if ( who->get_save("qgbxfansu") >= 8 && who->get_save("qgbxsanyao") >= 5 )
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,56,"远征(完成)" );
			who->set_legend(TASK_36, 21);
		}
	}
	if( who->get_legend(TASK_36, 26) && !who->get_legend(TASK_36, 27) )
	{
		if ( who->get_save("qwlijian") < 10 && random(100) < 27 )
		{
			if ( objectp( item = present("利剑", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
			{
	
				if ( item->get_amount() < 10 )
					item->add_amount(1);
			}
			else
			{
	
				item = new("item/98/0171");
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
			i=who->add_save("qwlijian",1);
			send_user(who,"%c%s",'!',sprintf(HIY"利剑 %d/10",i));		
			USER_TASK_D->send_task_intro(who,2,TID_QIGUO,58);
		}
		else if ( who->get_save("qwkuaidao") < 10 && random(100) < 26 )
		{
			if ( objectp( item = present("快刀", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
			{
	
				if ( item->get_amount() < 10 )
					item->add_amount(1);
			}
			else
			{
	
				item = new("item/98/0172");
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
			i=who->add_save("qwkuaidao",1);
			send_user(who,"%c%s",'!',sprintf(HIY"快刀 %d/10",i));		
			USER_TASK_D->send_task_intro(who,2,TID_QIGUO,58);
		}
		
		if ( who->get_save("qwlijian") >= 10 && who->get_save("qwkuaidao") >= 10 )
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,58,"大齐的崛起(完成)" );
			who->set_legend(TASK_36, 27);
		}
	}

	if( who->get_legend(TASK_37, 10) && !who->get_legend(TASK_37, 11) )
	{
		if ( who->get_save("mtxianxf") < 1 && random(100) < 25 )
		{
	
			item = new("item/98/0174");
			if ( !item  )
				return ;
			p = item->move(who,-1);
			if ( !p )
			{
				destruct(item);
				return;
			}
			item->add_to_user(p);

			i=who->add_save("mtxianxf",1);
			send_user(who,"%c%s",'!',sprintf(HIY"现行粉 %d/1",i));		
			USER_TASK_D->send_task_intro(who,2,TID_DONGHAIDAO,2);
		}
		else if ( who->get_save("mtnuomi") < 8 && random(100) < 30 )
		{
			if ( objectp( item = present("糯米", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
			{
	
				if ( item->get_amount() < 8 )
					item->add_amount(1);
			}
			else
			{
	
				item = new("item/98/0175");
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
			i=who->add_save("mtnuomi",1);
			send_user(who,"%c%s",'!',sprintf(HIY"糯米 %d/8",i));		
			USER_TASK_D->send_task_intro(who,2,TID_DONGHAIDAO,2);
		}
		else if ( who->get_save("mtbaohd") < 1 && random(100) < 25 )
		{
	
			item = new("item/98/0176");
			if ( !item  )
				return ;
			p = item->move(who,-1);
			if ( !p )
			{
				destruct(item);
				return;
			}
			item->add_to_user(p);

			i=who->add_save("mtbaohd",1);
			send_user(who,"%c%s",'!',sprintf(HIY"保和丹 %d/1",i));		
			USER_TASK_D->send_task_intro(who,2,TID_DONGHAIDAO,2);
		}
		if ( who->get_save("mtxianxf") >= 1 && who->get_save("mtnuomi") >= 8 && who->get_save("mtbaohd") >= 1 )
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_DONGHAIDAO,2,"肖独贵（4）(完成)" );
			who->set_legend(TASK_37, 11);
		}
	}
	if( who->get_legend(TASK_43, 23) && !who->get_legend(TASK_43, 24) && who->get_save("qggjguixr") < 6 )
	{
		if ( (i=who->add_save("qggjguixr",1)) >= 6 && who->get_save("qggjtuj") >= 5 && who->get_save("qggjtiangmzs") >= 8)
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,60,"黎明前的黑暗(完成)" );
			who->set_legend(TASK_43, 24);
		}
		USER_TASK_D->send_task_intro(who,2,TID_QINGUO,60);
		send_user(who,"%c%s",'!',sprintf(HIY"Quy Tiên Nhân %d /6",i));		
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

                if( p < 6804 * rate / 100 ) ;    // NONE

                else if( p < 7054 * rate / 100 )    // 金钱
                {
                        if( gold >= total ) continue;

                        if( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) )
                        {
                                item = new( "/item/std/0001" );
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                item->set_value( 810 + random(240) );
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                                gold ++;
                        }
                }         
/*              else if( p < 7054 * rate / 100 )    // 武器(基本)
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
/*              else if( p < 7054 * rate / 100 )    // 防具(基本)
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
                else if( p < 7066 * rate / 100 )    // 武器(门派)
                {
                        if( equip >= total2 ) continue;

                        switch( random(3) )
                        {
                       case 0 : file = WEAPON_FILE->get_weapon_file_2(80);  break;
                       case 1 : file = WEAPON_FILE->get_weapon_file_2(90);  break;
                       case 2 : file = WEAPON_FILE->get_weapon_file_2(100);  break;

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
                else if( p < 7078 * rate / 100 )    // 防具(门派)
                {
                        if( equip >= total2 ) continue;

                        switch( random(3) )
                        {
                       case 0 : file = ARMOR_FILE->get_armor_file_2(80);  break;
                       case 1 : file = ARMOR_FILE->get_armor_file_2(90);  break;
                       case 2 : file = ARMOR_FILE->get_armor_file_2(100);  break;

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
                        switch( random(2) )
                        {
                       case 0 : file = "/item/40/4077";  break;
                       case 1 : file = "/item/40/4047";  break;

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
                        switch( random(3) )
                        {
                       case 0 : file = "/item/stuff/0130";  break;
                       case 1 : file = "/item/stuff/0053";  break;
                       case 2 : file = "/item/stuff/0195";  break;

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
                       case 0 : file = "/item/41/4109";  break;
                       case 1 : file = "/item/stuff/0310";  break;

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
                       case 0 : file = "/item/stuff/0309";  break;

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
/*              else if( p < 1030000 * rate / 100 )    // 杂物５
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
