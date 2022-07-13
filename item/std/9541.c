
#include <ansi.h>
#include <map.h>
#include <npc.h>
#include <effect.h>

inherit TALISMAN;

// 函数：生效几率
int get_active_rate() { return 50; }

// 函数：法宝识别
int get_talisman_type() { return 5; }

// 函数：构造处理
void create()
{
        set_name( "驱神令" );
        set_picid_1(9541);
        set_picid_2(9541);
        set_unit( "块" );

        set_level(1);
        set_value(5000);
        set_max_lasting(4099);

        setup();
}

// 函数：获取描述
string get_desc() 
{ 
        return "传送其它玩家到当前场景的随机位置";
}

// 函数：可使用法宝
int is_usable_2() { return 1; }

// 函数：使用法宝效果
int get_use_effect_2( object me, object who, string arg ) { return __DIR__ "9541" ->get_use_effect_2_callout( me, who, this_object(), arg ); }

// 函数：使用法宝效果(在线更新)
int get_use_effect_2_callout( object me, object who, object item, string arg )    // 同步更改“飞行符”
{
        object map, npc;
        int z, x, y, p;

        if( !objectp(who) ) return 1;

        if( !who->is_user() ) return 1;    // 必须是玩家

        if( who->get_login_flag() < 3 ) return 1;    // 没有准备就绪

        if( who->is_die() || who->is_store_open() || who->get_no_fight() ) return 1;    // 死亡，摆摊，安全区

        if( me == who ) return 1;    // 不能是自己
        if ( time() - me->get_save("9541")<600)
        {
                send_user( me, "%c%s", '!', sprintf("还需间隔%d秒才能使用驱神令。", 600+me->get_save("9541")-time()) );
                return 1;        	
        }

        if( objectp( map = get_map_object( get_z(who) ) ) && map->get_map_type() == BATTLE_MAP )
        {
                send_user( me, "%c%s", '!', "对方现在还在战场。" );
                return 1;
        }
	if( who->get_save_2("51cuanye.time") )
	{
		send_user(me, "%c%s", '!', "对方接受极限穿越任务后不能使用驱神令。");
		return 0;
	}        
        if( present("钱票", who, 1, MAX_CARRY) )
        {
                send_user( me, "%c%s", '!', "对方身上带着钱票。" );
                return 1;
        }
        if( present("贵重物品", who, 1, MAX_CARRY*4) )
        {
                send_user( me, "%c%s", '!', "对方身上带着贵重物品。" );
                return 1;
        }       
        if( objectp( npc = who->get_quest("escort.robber#") ) && npc->is_escort_robber() )    // 寻找蒙面人
        {
                send_user( me, "%c%s", '!', "对方刚遇到蒙面人。" );
                return 1;
        }

        item->add_lasting(-1);    // 使用减少耐久

        me->set_char_type( PK_TYPE );    // 主动ＰＫ状态
        set_effect(me, EFFECT_USER_PK, 120);
        me->set_save("9541", time());

        if(     random(100) < item->get_active_rate()    // 成功率
        &&    ( z = get_z(who) )
        &&    ( p = get_xy_point(z, IS_CHAR_BLOCK) ) )
        {
                x = p / 1000;  y = p % 1000;

//              if( MAP_D->is_inside_city(z, x, y) ) return 1;

/*              who->set_login_flag(2);    // 跳转保护
                set_invisible(who, 1);
                set_effect(who, EFFECT_USER_LOGIN, 4);   */

                if(   ( npc = who->get_quest("escort.npc") )    // 运镖人物
                &&      npc->get_owner() == who
                &&      inside_screen_2(who, npc) )    // 同屏幕内
                        npc->add_to_scene( z, x, y, get_d(who), 40991, 40992, 40991, 40992 );

                if( p = get_valid_xy( z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK ) )
                {
                        who->add_to_scene( z, p / 1000, p % 1000, get_d(who), 40991, 40992, 40991, 40992 );
                }

                write_user( me, ECHO "您使用" HIY "驱神逐鬼" ECHO "把%s驱逐了。", who->get_name() );
                write_user( who, ECHO "%s使用" HIY "驱神逐鬼" ECHO "把您驱逐了。", me->get_name() );

                return 1;
        }
        else    write_user( me, ECHO "您对%s使用" HIY "驱神逐鬼" ECHO "失败了。", who->get_name() );	
        return 1;
}
