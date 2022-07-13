
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
int get_char_picid() { return 0954; }

// 函数：构造处理
void create()
{
        set_name("Thổ Tinh");

        set_char_type(FIGHTER_TYPE);    // init_level 要用到
        
        set_head_color(0x0);

        NPC_ENERGY_D->init_level( this_object(), 96+ random(4) );    // 
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

	if( who->get_legend(TASK_33, 7) && !who->get_legend(TASK_33, 8) && who->get_save("cgswtujing") < 6 )
	{
		if ( (i=who->add_save("cgswtujing",1)) >= 6 && who->get_save("cgswsuijing") >= 7)
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,35,"多管闲事(完成)" );
			who->set_legend(TASK_33, 8);
		}
		USER_TASK_D->send_task_intro(who,2,TID_CHUGUO,35);
		send_user(who,"%c%s",'!',sprintf(HIY"Thổ Tinh %d/6",i));		
	}
	if( who->get_legend(TASK_33, 10) && !who->get_legend(TASK_33, 11) && random(100) < 30 )
	{
		if ( objectp( item = present("铁观音茶", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
		{
			if ( item->get_amount() < 20 )
				item->add_amount(1);
		}
		else
		{
			item = new("item/98/0155");
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
		if ( (i=who->add_save("cgswtiegy",1)) >= 20 )
		{
			who->set_save("cgswtiegy",20);
			who->set_legend(TASK_33, 11);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,36,"铁观音茶(完成)" );
		}
		USER_TASK_D->send_task_intro(who,2,TID_CHUGUO,36);
		send_user(who,"%c%s",'!',sprintf(HIY"铁观音茶 %d/20",i));		
	}
	if( who->get_legend(TASK_33, 13) && !who->get_legend(TASK_33, 14) && random(100) < 30 )
	{
		if ( objectp( item = present("玫瑰花", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
		{
			if ( item->get_amount() < 11 )
				item->add_amount(1);
		}
		else
		{
			item = new("item/98/0156");
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
		if ( (i=who->add_save("cgswmeigui",1)) >= 11 )
		{
			who->set_save("cgswmeigui",11);
			who->set_legend(TASK_33, 14);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,37,"玫瑰花(完成)" );
		}
		USER_TASK_D->send_task_intro(who,2,TID_CHUGUO,37);
		send_user(who,"%c%s",'!',sprintf(HIY"玫瑰花 %d/11",i));		
	}
	if( who->get_legend(TASK_33, 19) && !who->get_legend(TASK_33, 20) )
	{
		if ( who->get_save("cgbxmuz") == 0 && random(100) < 22 )
		{
			item = new("item/98/0157");
			if ( !item  )
				return ;
			p = item->move(who,-1);
			if ( !p )
			{
				destruct(item);
				return;
			}
			item->add_to_user(p);
			who->set_save("cgbxmuz",1);
			send_user(who,"%c%s",'!',sprintf(HIY"工匠的木槌 %d/1",1));		
		}
		else if ( who->get_save("cgbxpaoz") == 0 && random(100) < 22 )
		{
			item = new("item/98/0158");
			if ( !item  )
				return ;
			p = item->move(who,-1);
			if ( !p )
			{
				destruct(item);
				return;
			}
			item->add_to_user(p);
			who->set_save("cgbxpaoz",1);
			send_user(who,"%c%s",'!',sprintf(HIY"工匠的刨子 %d/1",1));		
		}
		if (  who->get_save("cgbxmuz") && who->get_save("cgbxpaoz") )
		{
			who->set_legend(TASK_33, 20);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,39,"保持距离(完成)" );
		}
		USER_TASK_D->send_task_intro(who,2,TID_CHUGUO,39);
	}
	if( who->get_legend(TASK_33, 27) && !who->get_legend(TASK_33, 28) && who->get_save("lidetujing") < 30 )
	{
		if ( (i=who->add_save("lidetujing",1)) >= 30 && who->get_save("lidejinjing") >= 30)
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,38,"证明实力(完成)" );
			who->set_legend(TASK_33, 28);
		}
		USER_TASK_D->send_task_intro(who,2,TID_WEIGUO,38);
		send_user(who,"%c%s",'!',sprintf(HIY"Thổ Tinh %d/30",i));		
	}
	if( who->get_legend(TASK_35, 17) && !who->get_legend(TASK_35, 18) && who->get_save("wlhtujing1") < 30 )
	{
		if ( (i=who->add_save("wlhtujing1",1)) >= 30 && who->get_save("wlhsuijing1") >= 30)
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,58,"勇闯虚陵洞(完成)" );
			who->set_legend(TASK_35, 18);
		}
		USER_TASK_D->send_task_intro(who,2,TID_WEIGUO,58);
		send_user(who,"%c%s",'!',sprintf(HIY"Thổ Tinh %d/30",i));		
	}
	if( who->get_legend(TASK_39, 28) && !who->get_legend(TASK_39, 29) )
	{
		if ( who->get_save("gsbtieku") == 0 && random(100) < 20 )
		{
			item = new("item/98/0191");
			if ( !item  )
				return ;
			p = item->move(who,-1);
			if ( !p )
			{
				destruct(item);
				return;
			}
			item->add_to_user(p);
			who->set_save("gsbtieku",1);
			send_user(who,"%c%s",'!',sprintf(HIY"铁箍 %d/1",1));		
			USER_TASK_D->send_task_intro(who,2,TID_ZHOUGUO,8);
		}
		else if ( who->get_save("gsbmutou") < 5 && random(100) < 23 )
		{
			if ( objectp( item = present("修理的木头", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
			{
				if ( item->get_amount() < 5 )
					item->add_amount(1);
			}
			else
			{
				item = new("item/98/0192");
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
			i=who->add_save("gsbmutou",1);
			USER_TASK_D->send_task_intro(who,2,TID_ZHOUGUO,8);
			send_user(who,"%c%s",'!',sprintf(HIY"修理的木头 %d/5",i));		
		}
		if (  who->get_save("gsbtieku") && who->get_save("gsbmutou") >=5 )
		{
			who->set_legend(TASK_39, 29);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,8,"四面楚歌（4）(完成)" );
		}
	}
	if( who->get_legend(TASK_43, 23) && !who->get_legend(TASK_43, 24) && who->get_save("qggjtuj") < 5 )
	{
		if ( (i=who->add_save("qggjtuj",1)) >= 5 && who->get_save("qggjguixr") >= 6 && who->get_save("qggjtiangmzs") >= 8)
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,60,"黎明前的黑暗(完成)" );
			who->set_legend(TASK_43, 24);
		}
		USER_TASK_D->send_task_intro(who,2,TID_QINGUO,60);
		send_user(who,"%c%s",'!',sprintf(HIY"Thổ Tinh %d/5",i));		
	}
	if( who->get_legend(TASK_45, 26) && !who->get_legend(TASK_45, 27) && random(100) < 18)
	{
		item = new("item/98/0227");
		if ( !item  )
			return ;
		p = item->move(who,-1);
		if ( !p )
		{
			destruct(item);
			return;
		}
		item->add_to_user(p);
		who->set_legend(TASK_45, 27);
		USER_TASK_D->send_task_intro(who,2,TID_YUNMENZE,2);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YUNMENZE,2,"求医（4）(完成)" );
		send_user(who,"%c%s",'!',HIY"宝鼎 1/1");		
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

                if( p < 6968 * rate / 100 ) ;    // NONE

/*              else if( p < 6968 * rate / 100 )    // 金钱
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
/*              else if( p < 6968 * rate / 100 )    // 武器(基本)
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
/*              else if( p < 6968 * rate / 100 )    // 防具(基本)
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
                else if( p < 6982 * rate / 100 )    // 武器(门派)
                {
                        if( equip >= total2 ) continue;

                        switch( random(3) )
                        {
                       case 0 : file = WEAPON_FILE->get_weapon_file_2(70);  break;
                       case 1 : file = WEAPON_FILE->get_weapon_file_2(80);  break;
                       case 2 : file = WEAPON_FILE->get_weapon_file_2(90);  break;

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
                else if( p < 6996 * rate / 100 )    // 防具(门派)
                {
                        if( equip >= total2 ) continue;

                        switch( random(3) )
                        {
                       case 0 : file = ARMOR_FILE->get_armor_file_2(70);  break;
                       case 1 : file = ARMOR_FILE->get_armor_file_2(80);  break;
                       case 2 : file = ARMOR_FILE->get_armor_file_2(90);  break;

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
                        switch( random(1) )
                        {
                       case 0 : file = "/item/40/4074";  break;

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
                        switch( random(4) )
                        {
                       case 0 : file = "/item/stuff/0130";  break;
                       case 1 : file = "/item/stuff/0053";  break;
                       case 2 : file = "/item/stuff/0030";  break;
                       case 3 : file = "/item/stuff/0195";  break;

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
/*              else if( p < 1010000 * rate / 100 )    // 杂物５
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
