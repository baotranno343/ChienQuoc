#include <item.h>
#include <ansi.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

int get_item_value() {return 50 ;}
int get_item_value_2() {return 35 ;}
int get_item_number() {return 10001017 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name( "友情呼唤" );
        set_picid_1(3857);
        set_picid_2(3857);
	set_record(1);
        set_value(666);
        set_amount(1);
        // -- 与原装备相比增加绑定属性
        set_no_give(1);
        set_no_sell(1);
        //        
}

// 函数：获取描述
string get_desc() 
{ 
        return "上面写着“天长地久，友谊永存”几个字。可以将指定的队友快速召唤到自己身边。冷却时间2秒。";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me )
{
        object map, *team, npc;
        string str1, str2;
	if( !objectp( map = get_map_object( get_z(me) ) ) )
		return 0;
	if( map->is_copy_scene() )
        {
                send_user(me, "%c%s", '!', "在副本内不能使用。");
                return 0;
        }
        if( map->is_changping() )
        {
                send_user(me, "%c%s", '!', "在这里不能使用。");
                return 0;
        }
	send_user( me, "%c%c%d%d%s", '?', 3, 0, me->get_save("fly"), "你希望召唤哪位队友？请在下面输入队友的ID。\n"
                        ESC "goto2 ?.%s\n" );	                        
	return 0;	                        
} 