
#include <skill.h>
#include <effect.h>

inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "Tích Độc Tán" );
        set_picid_1(9140);
        set_picid_2(9140);
        set_unit( "包" );
        set_value(2000);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Giải trừ trạng thái trúng độc và trong 5 giây sau sẽ không bị trúng độc";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me )
{
/*      if( gone_time( me->get_time("eat") ) < 1 )
        {
                me->set_time( "eat", time() );
                return 0;
        }
        me->set_time( "eat", time() );  */

        CHAR_CHAR_D->stop_poison_effect(me);    // 解除毒药效果

        set_effect(me, EFFECT_CHAR_9140, 5);

        return 1;
}
