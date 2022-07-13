
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;

// 函数：远程攻击的怪
 int is_caster() { return 0; }

// 函数：是否允许移动
// int is_moveable() { return 0; }    // 禁止使用 go 命令

// 函数：跟随对手(心跳之中调用)
// void follow_user() { }    // 禁止跟随敌人

// 函数：获取人物造型
int get_char_picid() { return 1102; }

// 函数：构造处理
void create()
{
        set_name("Thương Hồn");

        set_char_type(FIGHTER_TYPE);    // init_level 要用到
        
        set_head_color(0x0);

        NPC_ENERGY_D->init_level( this_object(), 110+ random(4) );    // 
        set_max_seek(4);

        setup();

        set_char_type(FIGHTER_TYPE);    // 重设类型
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：特技攻击对手
int perform_action( object who ) { return 0; }

// 函数：自动战斗(遇玩家时调用)
// void auto_fight( object who ) { }

// 函数：任务处理(有任务时调用)
void check_legend_task( object who ) 
{
	int p,i,iRate;
	object item;
	if( who->get_legend(TASK_44, 10) && !who->get_legend(TASK_44, 11) && random(100) < 23)
	{
		if ( objectp( item = present("漂亮的黄晶石", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
		{
			if ( item->get_amount() < 8 )
				item->add_amount(1);
		}
		else
		{
			item = new("item/98/0219");
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
		if ( (i=who->add_save("wggjhuangjs",1)) >= 8 )
		{
			who->set_legend(TASK_44, 11);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,64,"漂亮的床（3）(完成)" );
		}
		USER_TASK_D->send_task_intro(who,2,TID_WEIGUO,64);
		send_user(who,"%c%s",'!',sprintf(HIY"漂亮的黄晶石 %d/8",i));		
	}
	if( who->get_legend(TASK_44, 24) && !who->get_legend(TASK_44, 25) )
	{
		if ( (i=who->add_save("lituqianhun",1)) >= 10 )
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,66,"人情冷暖（1）(完成)" );
			who->set_legend(TASK_44, 25);
		}
		USER_TASK_D->send_task_intro(who,2,TID_QIGUO,66);
		send_user(who,"%c%s",'!',sprintf(HIY"Thương Hồn %d /10",i));		
	}
	if( who->get_legend(TASK_44, 27) && !who->get_legend(TASK_44, 28) && random(100) < 28)
	{
		if ( objectp( item = present("油菜籽", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
		{
			if ( item->get_amount() < 10 )
				item->add_amount(1);
		}
		else
		{
			item = new("item/98/0221");
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
		if ( (i=who->add_save("lituyoucaizi",1)) >= 10 )
		{
			who->set_legend(TASK_44, 28);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,67,"人情冷暖（2）(完成)" );
		}
		USER_TASK_D->send_task_intro(who,2,TID_QIGUO,67);
		send_user(who,"%c%s",'!',sprintf(HIY"油菜籽 %d/10",i));		
	}
	if( who->get_legend(TASK_45, 4) && !who->get_legend(TASK_45, 5) && random(100) < 20)
	{
		if ( objectp( item = present("秦国盔甲", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 ) 
		{
			if ( item->get_amount() < 5 )
				item->add_amount(1);
		}
		else
		{
			item = new("item/98/0222");
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
		if ( (i=who->add_save("qgdjjkuijia",1)) >= 5 )
		{
			who->set_legend(TASK_45, 5);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,63,"天寒地冻(完成)" );
		}
		USER_TASK_D->send_task_intro(who,2,TID_QINGUO,63);
		send_user(who,"%c%s",'!',sprintf(HIY"秦国盔甲 %d/5",i));		
	}	
	if( who->get_legend(TASK_45, 15) && !who->get_legend(TASK_45, 16) )
	{
		if ( (i=who->add_save("cwqianhun",1)) >= 12 )
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,41,"万众敬仰(完成)" );
			who->set_legend(TASK_45, 16);
		}
		USER_TASK_D->send_task_intro(who,2,TID_CHUGUO,41);
		send_user(who,"%c%s",'!',sprintf(HIY"Thương Hồn %d /12",i));		
	}
	if( who->get_legend(TASK_45, 23) && !who->get_legend(TASK_45, 24) && random(100) < 18)
	{
		item = new("item/98/0226");
		if ( !item  )
			return ;
		p = item->move(who,-1);
		if ( !p )
		{
			destruct(item);
			return;
		}
		item->add_to_user(p);
		who->set_legend(TASK_45, 24);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YUNMENZE,1,"求医（3）(完成)" );
		USER_TASK_D->send_task_intro(who,2,TID_YUNMENZE,1);
		send_user(who,"%c%s",'!',HIY"虎皮 1/1");		
	}
	if( who->get_legend(TASK_46, 8) && !who->get_legend(TASK_46, 9) && who->get_save("mxqianhun") < 30 )
	{
		if ( (i=who->add_save("mxqianhun",1)) >= 30 && who->get_save("mxdaohun") >= 30 )
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,67,"刀魂传说4(完成)" );
			who->set_legend(TASK_46, 9);
		}
		USER_TASK_D->send_task_intro(who,2,TID_QINGUO,67);
		send_user(who,"%c%s",'!',sprintf(HIY"Thương Hồn %d /30",i));		
	}		
	if( who->get_legend(TASK_46, 15) && !who->get_legend(TASK_46, 16) && who->get_save("qysqianhun") < 30 )
	{
		if ( (i=who->add_save("qysqianhun",1)) >= 30 && who->get_save("qysjianhun") >= 30 )
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,70,"平阳之乱2(完成)" );
			who->set_legend(TASK_46, 16);
		}
		USER_TASK_D->send_task_intro(who,2,TID_QINGUO,70);
		send_user(who,"%c%s",'!',sprintf(HIY"Thương Hồn %d /30",i));		
	}
	if( who->get_legend(TASK_47, 23) && !who->get_legend(TASK_47, 24) && who->get_save("xhdqianhun") < 30 )
	{
		if ( (i=who->add_save("xhdqianhun",1)) >= 30 && who->get_save("xhdjianhun") >= 30 )
		{
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,86,"索取神剑3(完成)" );
			who->set_legend(TASK_47, 24);
		}
		USER_TASK_D->send_task_intro(who,2,TID_QINGUO,86);
		send_user(who,"%c%s",'!',sprintf(HIY"Thương Hồn %d /30",i));		
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

                if( p < 7412 * rate / 100 ) ;    // NONE

/*              else if( p < 7412 * rate / 100 )    // 金钱
                {
                        if( gold >= total ) continue;

                        if( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) )
                        {
                                item = new( "/item/std/0001" );
                                TEAM_D->drop_item(item,who);
                                item->set_user_id(owner);
                                item->set_value( 800 + random(300) );
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set( "time", time() );
                                gold ++;
                        }
                }       */
/*              else if( p < 7412 * rate / 100 )    // 武器(基本)
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
/*              else if( p < 7412 * rate / 100 )    // 防具(基本)
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
                else if( p < 7419 * rate / 100 )    // 武器(门派)
                {
                        if( equip >= total2 ) continue;

                        switch( random(3) )
                        {
                       case 0 : file = WEAPON_FILE->get_weapon_file_2(90);  break;
                       case 1 : file = WEAPON_FILE->get_weapon_file_2(100);  break;
                       case 2 : file = WEAPON_FILE->get_weapon_file_2(110);  break;

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
                else if( p < 7426 * rate / 100 )    // 防具(门派)
                {
                        if( equip >= total2 ) continue;

                        switch( random(3) )
                        {
                       case 0 : file = ARMOR_FILE->get_armor_file_2(90);  break;
                       case 1 : file = ARMOR_FILE->get_armor_file_2(100);  break;
                       case 2 : file = ARMOR_FILE->get_armor_file_2(110);  break;

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
                       case 0 : file = "/item/40/4082";  break;

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
                       case 1 : file = "/item/91/9145";  break;
                       case 2 : file = "/item/stuff/0053";  break;
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
/*              else if( p < 1110000 * rate / 100 )    // 杂物５
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
