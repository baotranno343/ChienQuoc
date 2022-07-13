
#include <item.h>

inherit ITEM;
inherit USABLE;

private int Potential;                  // 潜能

int get_item_color() { return 2; }
// 函数：混沌天书
// int is_potential_item() { return 1; }

// 函数：混沌天书
int get_item_type() { return ITEM_TYPE_POTENTIAL; }

// 函数：获取潜能属性
int get_potential() { return Potential; }

// 函数：设置潜能属性
int set_potential( int point ) { return Potential = point; }

// 函数：构造处理
void create()
{
        set_name( "九转混天丹" );
        set_picid_1(9167);
        set_picid_2(9167);
        set_unit( "粒" );
        set_value(3000);
}

// 函数：获取描述
string get_desc() 
{ 
        return "能储存 8000 潜能";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object item )
{
        if( item->get_potential() < 1 )
        {
                if( me->get_potential() < 8000 )
                {
                        send_user(me, "%c%s", '!', "您得一次充满 8000 潜能。");
                        return 0;
                }
                me->add_potential( -8000 );
                item->set_potential(8000);
                write_user(me, "你将 8000 潜能充入%s。", item->get_name() );
                send_user( me, "%c%d%c", 0x31, getoid(item), 0 );

                return 0;    // 不能删除
        }
        else
        {
                me->add_potential(8000);
                return 1;
        }

        return 0;
}
