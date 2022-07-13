
#include <ansi.h>
#include <map.h>
#include <effect.h>

inherit TALISMAN;

// 函数：生效几率
int get_active_rate() { return 100; }

// 函数：法宝识别
int get_talisman_type() { return 6; }

// 函数：构造处理
void create()
{
        set_name( "土行珠" );
        set_picid_1(9551);
        set_picid_2(9551);
        set_unit( "颗" );

        set_level(1);
        set_value(5000);
        set_max_lasting(1499);

        setup();
}

// 函数：获取描述
string get_desc() 
{ 
        return "传送自己到当前场景的指定坐标";
}

// 函数：可使用法宝
int is_usable_2() { return 1; }

// 函数：使用法宝效果
int get_use_effect_2( object me, object who, string arg ) { return __DIR__ "9551" ->get_use_effect_2_callout( me, who, this_object(), arg ); }

// 函数：使用法宝效果(在线更新)
int get_use_effect_2_callout( object me, object who, object item, string arg )
{
        object map, npc;
        int z, x, y, p;

        if( !arg || arg == "" )
        {
                send_user( me, "%c%c%d%s", '?', 16, 8, "您想传送到当前场景的哪里？请输入坐标：X,Y (取值 0～999)\n"
                        ESC "pf2 00900.%s\n" );
                return 1;
        }
        else
        {
                if( sscanf(arg, "%d,%d", x, y) != 2 )    // && sscanf(arg, "%d，%d", x, y) != 2
                {
                        send_user( me, "%c%s", '!', "坐标输入错误！" );
                        return 1;
                }

                z = get_z(me);

                if( me->get_login_flag() < 3 ) return 1;    // 没有准备就绪
                if( me->is_die() )
                {
                        send_user( me, "%c%s", '!', "死亡状态下不能使用土行珠。" );
                        return 1;                	
        	}
		if( me->get_save_2("51cuanye.time") )
		{
			send_user(me, "%c%s", '!', "接受极限穿越任务后不能使用土行珠。");
			return 0;
		}
                if( me->is_store_open() )
                {
                        send_user( me, "%c%s", '!', "摆摊状态下不能使用土行珠。" );
                        return 1;                	
        	}        
                if( me->get_no_fight() )
                {
                        send_user( me, "%c%s", '!', "安全区不能使用土行珠。" );
                        return 1;                	
        	}         		
                if( objectp( map = get_map_object( get_z(me) ) ) && map->get_map_type() == BATTLE_MAP )
                {
                        send_user( me, "%c%s", '!', "在战场不能使用土行珠。" );
                        return 1;
                }
		if( map->is_copy_scene() )
	        {
	                send_user(me, "%c%s", '!', "在副本内不能使用土行珠。");
	                return 1;
	        }
                if( present("钱票", me, 1, MAX_CARRY) )
                {
                        send_user( me, "%c%s", '!', "带着钱票不能使用土行珠。" );
                        return 1;
                }
                if( present("贵重物品", me, 1, MAX_CARRY*4) )
                {
                        send_user( me, "%c%s", '!', "带着贵重物品不能使用土行珠。" );
                        return 1;
                }       
                if( objectp( npc = me->get_quest("escort.robber#") ) && npc->is_escort_robber() )    // 寻找蒙面人
                {
                        send_user( me, "%c%s", '!', "您现在正遇到蒙面人呢。" );
                        return 1;
                }

                item->add_lasting(-1);    // 使用减少耐久

                if(     random(100) < item->get_active_rate()    // 成功率
                &&    ( p = get_valid_xy(z, x, y, IS_CHAR_BLOCK) ) )
                {
                        x = p / 1000;  y = p % 1000;

                        if( MAP_D->is_inside_city(z, x, y) )
                        {
                                send_user( me, "%c%s", '!', "不能传送到城内。" );
                                return 1;
                        }

/*                      me->set_login_flag(2);    // 跳转保护
                        set_invisible(me, 1);
                        set_effect(me, EFFECT_USER_LOGIN, 4);   */
/*
                        if(   ( npc = me->get_quest("escort.npc") )    // 运镖人物
                        &&      npc->get_owner() == me
                        &&      inside_screen_2(me, npc) )    // 同屏幕内
                                npc->add_to_scene( z, x, y, get_d(me), 40991, 40992, 40991, 40992 );
*/
                        if( p = get_valid_xy( z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK ) )
                        {
                                me->add_to_scene( z, p / 1000, p % 1000, get_d(me), 40991, 40992, 40991, 40992 );
                        }

//                      write_user( me, ECHO "您使用" HIY "奇门土遁" ECHO "成功了。" );
                }
                else    write_user( me, ECHO "您使用" HIY "奇门土遁" ECHO "失败了。" );
        }

        return 1;
}
