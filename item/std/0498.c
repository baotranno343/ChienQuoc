
#include <ansi.h>
#include <map.h>
#include <effect.h>

inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：构造处理
void create()
{
        set_name( "转移符" );
        set_picid_1(0408);
        set_picid_2(0408);
        set_unit( "张" );
        set_value(8000);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "直接将使用者传送回战场中的帮派总管处";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me )
{
        object map;
        string name;
        int z, x, y, p;        

        z = get_z(me);

        if( !objectp( map = get_map_object(z) ) || map->get_map_type() != BATTLE_MAP ) 
        {
                send_user(me, "%c%s", '!', "只能在战场使用转移符。");
                return 0;
        }
	write_user(me, ECHO "您祭起一张转移符……");
        name = me->get_org_name();

        if( name == map->get_war_attack() ) p = get_jumpin(z, 1);
        else if( name == map->get_war_defense() ) p = get_jumpin(z, 2);

        if( p )
        {
                x = p / 1000;  y = p % 1000;

                me->set_login_flag(2);    // 跳转保护
                set_invisible(me, 1);
                set_effect(me, EFFECT_USER_LOGIN, 4);

                me->add_to_scene( z, x, y, get_d(me), 40971, 0, 40971, 0 );

                return 1;
        }
        else
        {
                write_user(me, ECHO "……可是没有任何效果。");
                return 0;
        }
}
