
#include <ansi.h>
#include <map.h>
#include <effect.h>

inherit TALISMAN;

// 函数：生效几率
int get_active_rate() { return 60; }

// 函数：法宝识别
int get_talisman_type() { return 4; }

// 函数：构造处理
void create()
{
        set_name( "Linh Tê Hoàn" );
        set_picid_1(9531);
        set_picid_2(9531);
        set_unit( "个" );

        set_level(1);
        set_value(5000);
        set_max_lasting(5099);

        setup();
}

// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm đặc biệt có thể triệu hồi người\n chơi khác đến bên cạnh bản thân.";
}

// 函数：可使用法宝
int is_usable_2() { return 1; }

// 函数：使用法宝效果
int get_use_effect_2( object me, object who, string arg ) { return __DIR__ "9531" ->get_use_effect_2_callout( me, who, this_object(), arg ); }

// 函数：使用法宝效果(在线更新)
int get_use_effect_2_callout( object me, object who, object item, string arg )    // 同步更改“神游”
{
        object map, *team, npc;
        string str1, str2;

        if( !arg || arg == "" )
        {
                send_user( me, "%c%c%d%d%s", '?', 3, 0, me->get_save("fly"), "您想传送哪位玩家到自己身边？请输入对方的数字ＩＤ：\n"
                        ESC "pf2 00900.%s\n" );
                return 1;
        }
        else
        {
                if( to_int(arg) ) me->set_save( "fly", to_int(arg) );    // 记录前次飞的人

                if( !objectp( who = find_player(arg) ) )
                {
                        send_user( me, "%c%s", '!', "您找不到这位玩家。" );
                        return 1;
                }
                if( me == who )
                {
                        send_user( me, "%c%s", '!', "您不能传送您自己。" );
                        return 1;
                }
                if( !( ( str1 = me->get_leader() ) && ( str2 = who->get_leader() ) && str1 == str2 )
                &&  !( ( str1 = me->get_org_name() ) && ( str2 = who->get_org_name() ) && str1 == str2 ) )
                {
                        send_user( me, "%c%s", '!', "对方不是您的队友或帮友。" );
                        return 1;
                }
		if( who->get_save_2("51cuanye.time") )
		{
			send_user(me, "%c%s", '!', "对方接受极限穿越任务，不能传送。");
			return 1;
		}
                if( who->get_no_fly() )
                {
                        send_user( me, "%c%s", '!', "对方设置了禁飞开关。" );
                        return 1;
                }
                if( MAP_D->is_inside_city( get_z(me), get_x(me), get_y(me) ) )
                {
                        send_user( me, "%c%s", '!', "城内不能使用此法宝。" );
                        return 1;
                }
                if( MAP_D->is_inside_city( get_z(who), get_x(who), get_y(who) ) )
                {
                        send_user( me, "%c%s", '!', "对方在城内，不能使用此法宝。" );
                        return 1;
                }
                if( objectp( map = get_map_object( get_z(me) ) ) )
                {
                        switch( map->get_map_type() )
                        {
                case CAVE_MAP : send_user( me, "%c%s", '!', "地底不能使用此法宝。" );
                                return 1;
              case BATTLE_MAP : send_user( me, "%c%s", '!', "战场不能使用此法宝。" );
                                return 1;
                        }
                }
                if( objectp( map = get_map_object( get_z(who) ) ) )
                {
                        switch( map->get_map_type() )
                        {
                case CAVE_MAP : send_user( me, "%c%s", '!', "对方在地下，不能使用此法宝。" );
                                return 1;
              case BATTLE_MAP : send_user( me, "%c%s", '!', "对方在战场，不能使用此法宝。" );
                                return 1;
                        }
                }
                if( who->get_login_flag() < 3 )
                {
                        send_user( me, "%c%s", '!', "对方还没有准备就绪呢。" );
                        return 1;
                }
                if( who->is_die() )
                {
                        send_user( me, "%c%s", '!', "对方已经死亡。" );
                        return 1;
                }
                if( who->is_store_open() )
                {
                        send_user( me, "%c%s", '!', "对方正在摆摊。" );
                        return 1;
                }
                if( who->get_no_fight() )
                {
                        send_user( me, "%c%s", '!', "对方在安全区。" );
                        return 1;
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

                if( arrayp( team = me->get("pending_fly") ) )
                        me->set( "pending_fly", team - ({ who, 0 }) + ({ who }) );
                else    me->set( "pending_fly", ({ who }) );

                who->set("pending_fly", me);

                send_user( who, "%c%s", ':', me->get_name() + "对您使用了" HIY "灵犀闪现" NOR "，是否接收传送？\n" 
                                ESC "接受。\n" + sprintf( "pf2 00903 %d\n", me->get_number() ) +
                                ESC "放弃。\nCLOSE\n" );
                write_user(me, ECHO "您使用了" HIY "灵犀闪现" ECHO "，正等待对方的回应。");
        }

        return 1;
}

// 函数：接收法宝效果
int accept_use_effect_2( object me, object who ) { return __DIR__ "9531" ->accept_use_effect_2_callout(me, who); }

// 函数：接收法宝效果(在线更新)
int accept_use_effect_2_callout( object me, object who )    // 同步更改“神游”
{
        object map, npc;
        string str1, str2;
        int z, x0, y0, x, y, p;

        if( me == who )
        {
                send_user( me, "%c%s", '!', "您不能传送您自己。" );
                return 1;
        }
        if( !( ( str1 = me->get_leader() ) && ( str2 = who->get_leader() ) && str1 == str2 )
        &&  !( ( str1 = me->get_org_name() ) && ( str2 = who->get_org_name() ) && str1 == str2 ) )
        {
                send_user( me, "%c%s", '!', "对方不是您的队友或帮友。" );
                return 1;
        }

        if( who->get_no_fly() )
        {
                send_user( me, "%c%s", '!', "对方设置了禁飞开关。" );
                return 1;
        }
        if( MAP_D->is_inside_city( get_z(me), get_x(me), get_y(me) ) )
        {
                send_user( me, "%c%s", '!', "城内不能使用此法宝。" );
                return 1;
        }
        if( MAP_D->is_inside_city( get_z(who), get_x(who), get_y(who) ) )
        {
                send_user( me, "%c%s", '!', "对方在城内，不能使用此法宝。" );
                return 1;
        }
        if( objectp( map = get_map_object( get_z(me) ) ) )
        {
                switch( map->get_map_type() )
                {
        case CAVE_MAP : send_user( me, "%c%s", '!', "地底不能使用此法宝。" );
                        return 1;
      case BATTLE_MAP : send_user( me, "%c%s", '!', "战场不能使用此法宝。" );
                        return 1;
                }
        }
        if( objectp( map = get_map_object( get_z(who) ) ) )
        {
                switch( map->get_map_type() )
                {
        case CAVE_MAP : send_user( me, "%c%s", '!', "对方在地下，不能使用此法宝。" );
                        return 1;
      case BATTLE_MAP : send_user( me, "%c%s", '!', "对方在战场，不能使用此法宝。" );
                        return 1;
                }
        }
        if( who->get_login_flag() < 3 )
        {
                send_user( me, "%c%s", '!', "对方还没有准备就绪呢。" );
                return 1;
        }
        if( who->is_die() )
        {
                send_user( me, "%c%s", '!', "对方已经死亡。" );
                return 1;
        }
        if( who->is_store_open() )
        {
                send_user( me, "%c%s", '!', "对方正在摆摊。" );
                return 1;
        }
        if( who->get_no_fight() )
        {
                send_user( me, "%c%s", '!', "对方在安全区。" );
                return 1;
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

        z = get_z(me);  x0 = get_x(me);  y0 = get_y(me);

        if( p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK) )
        {
                x = p / 1000;  y = p % 1000;
                who->add_to_scene( z, x, y, get_front_xy(x, y, x0, y0), 40971, 0, 40971, 0 );
        }

        return 1;
}
