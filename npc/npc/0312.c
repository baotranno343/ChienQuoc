
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
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
        set_name("Độc Thứ Phong");

        set_char_type(FIGHTER_TYPE); // init_level 要用到

        set_head_color(0xe1c2);

        NPC_ENERGY_D->init_level(this_object(), 31 + random(3)); //
        set_max_seek(4);

        setup();

        set_char_type(FIGHTER_TYPE); // 重设类型
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：特技攻击对手
int perform_action(object who) { return 0; } // XXXXX->perform_action_npc( this_object(), who ); }

// 函数：自动战斗(遇玩家时调用)
// void auto_fight( object who ) { }

// 函数：任务处理(有任务时调用)
void check_legend_task(object who)
{
        int p, i, iRate;
        object item;
        i = random(100);
        iRate = i;
        if (who->get_legend(TASK_07, 22) && !who->get_legend(TASK_07, 23) && i < 25 && who->get_save_2("ssylianou") < 3)
        {
                if (objectp(item = present("莲藕", who, 1, MAX_CARRY)) && item->is_legend_item() == 1)
                {

                        if (item->get_amount() < 3)
                                item->add_amount(1);
                }
                else
                {

                        item = new ("item/98/0028");
                        if (!item)
                                return;
                        p = item->move(who, -1);
                        if (!p)
                        {
                                destruct(item);
                                return;
                        }
                        item->add_to_user(p);
                }
                i = who->add_save_2("ssylianou", 1);
                send_user(who, "%c%s", '!', sprintf(HIY "莲藕 %d/3", i));
                USER_TASK_D->send_task_intro(who, 2, TID_WEIGUO, 26);
        }
        else if (who->get_legend(TASK_07, 22) && !who->get_legend(TASK_07, 23) && i < 47 && who->get_save_2("ssyyumi") < 2)
        {
                if (objectp(item = present("玉米", who, 1, MAX_CARRY)) && item->is_legend_item() == 1)
                {

                        if (item->get_amount() < 2)
                                item->add_amount(1);
                }
                else
                {

                        item = new ("item/98/0029");
                        if (!item)
                                return;
                        p = item->move(who, -1);
                        if (!p)
                        {
                                destruct(item);
                                return;
                        }
                        item->add_to_user(p);
                }
                i = who->add_save_2("ssyyumi", 1);
                send_user(who, "%c%s", '!', sprintf(HIY "玉米 %d/2", i));
                USER_TASK_D->send_task_intro(who, 2, TID_WEIGUO, 26);
        }
        //	else if( who->get_legend(TASK_07, 22) && !who->get_legend(TASK_07, 23) && i < 75 && who->get_save_2("ssyluobo") < 4)
        //	{
        //		if ( objectp( item = present("萝卜", who, 1, MAX_CARRY) ) && item->is_legend_item() == 1 )
        //		{
        //
        //			if ( item->get_amount() < 4 )
        //				item->add_amount(1);
        //		}
        //		else
        //		{
        //
        //			item = new("item/98/0030");
        //			if ( !item  )
        //				return ;
        //			p = item->move(who,-1);
        //			if ( !p )
        //			{
        //				destruct(item);
        //				return;
        //			}
        //			item->add_to_user(p);
        //		}
        //		i = who->add_save_2("ssyluobo",1);
        //		send_user(who,"%c%s",'!',sprintf(HIY"萝卜 %d/4",i));
        //	}
        if (who->get_save_2("ssylianou") >= 3 && who->get_save_2("ssyyumi") >= 2 && who->get_save_2("ssyluobo") >= 4)
        {
                send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_WEIGUO, 26, "挑剔的晚餐(完成)");
                who->set_legend(TASK_07, 23);
        }
}
// 函数：掉宝奖励
void drop_items(object who) { __FILE__->drop_items_callout(this_object(), who); }

// 函数：掉宝奖励(在线更新)
void drop_items_callout(object me, object who)
{
        object item, leader;
        string file, owner, id;
        int p, rate, i, size, gold, equip, total, total2;
        int z, x, y;

        z = get_z(me);
        x = get_x(me);
        y = get_y(me);
        id = who->get_leader();
        if (who->get_save_2("kiemtradanhanchua.score") == 3)
        {
                who->add_save_2("soquaicandiet2.score", 1);
                send_user(who, "%c%s", '!', sprintf("Đã giết được %d/20", who->get_save_2("soquaicandiet2.score")));
                if (who->get_save_2("soquaicandiet2.score") > 19)
                {
                        //				send_user(who,"%c%s",'!',sprintf("Nhiệm vụ Sứ giả đã hoàn thành"));
                        who->set_login_flag(2); // 跳转保护
                        set_invisible(who, 1);
                        set_effect(who, EFFECT_USER_LOGIN, 4);
                        who->add_to_scene(001, 143, 103);
                        return 0;
                }
        }
        if (!id)
                owner = who->get_id();
        else
        {
                if (leader = find_player(id))
                {
                        owner = leader->get_id();
                }
                else
                        owner = who->get_id();
        }

        p = random(100);
        size = (p > 2) ? 1 : (p > 0) ? 2
                                     : 8;
        total = 2;
        total2 = 3;
        //      p = random(100);  size = ( p > 40 ) ? 3 : 10;  total = 2;  total2 = 3;

        rate = me->correct_drop_rate(me->get_level() - who->get_level()) * who->get_online_rate() / 100;

        for (i = 0; i < size; i++)
        {
                p = random(10000);

                if (p < 4528 * rate / 100)
                        ; // NONE

                /*              else if( p < 4528 * rate / 100 )    // 金钱
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
                /*              else if( p < 4528 * rate / 100 )    // 武器(基本)
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
                /*              else if( p < 4528 * rate / 100 )    // 防具(基本)
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
                else if (p < 4678 * rate / 100) // 武器(门派)
                {
                        if (equip >= total2)
                                continue;

                        switch (random(2))
                        {
                        case 0:
                                file = WEAPON_FILE->get_weapon_file_2(20);
                                break;
                        case 1:
                                file = WEAPON_FILE->get_weapon_file_2(10);
                                break;

                        default:
                                break;
                        }
                        if (load_object(file) && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
                        {
                                item = new (file);
                                TEAM_D->drop_item(item, who);
                                item->set_user_id(owner);
                                ITEM_EQUIP_D->init_equip_prop(item);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set("time", time());
                                equip++;
                        }
                }
                /*              else if( p < 4678 * rate / 100 )    // 防具(门派)
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
                else if (p < 9350 * rate / 100) // 杂物１
                {
                        switch (random(2))
                        {
                        case 0:
                                file = "/item/40/4005";
                                break;
                        case 1:
                                file = "/item/40/4038";
                                break;

                        default:
                                break;
                        }
                        if (load_object(file) && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
                        {
                                item = new (file);
                                TEAM_D->drop_item(item, who);
                                item->set_user_id(owner);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set("time", time());
                        }
                }
                else if (p < 9850 * rate / 100) // 杂物２
                {
                        switch (random(2))
                        {
                        case 0:
                                file = "/item/stuff/0169";
                                break;
                        case 1:
                                file = "/item/stuff/0144";
                                break;

                        default:
                                break;
                        }
                        if (load_object(file) && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
                        {
                                item = new (file);
                                TEAM_D->drop_item(item, who);
                                item->set_user_id(owner);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set("time", time());
                        }
                }
                else if (p < 9950 * rate / 100) // 杂物３
                {
                        switch (random(2))
                        {
                        case 0:
                                file = "/item/stuff/0312";
                                break;
                        case 1:
                                file = "/item/stuff/0032";
                                break;

                        default:
                                break;
                        }
                        if (load_object(file) && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
                        {
                                item = new (file);
                                TEAM_D->drop_item(item, who);
                                item->set_user_id(owner);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set("time", time());
                        }
                }
                else if (p < 10000 * rate / 100) // 杂物４
                {
                        switch (random(1))
                        {
                        case 0:
                                file = "/item/stuff/0311";
                                break;

                        default:
                                break;
                        }
                        if (load_object(file) && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
                        {
                                item = new (file);
                                TEAM_D->drop_item(item, who);
                                item->set_user_id(owner);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set("time", time());
                        }
                }
                /*              else if( p < 410000 * rate / 100 )    // 杂物５
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
