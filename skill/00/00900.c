
#include <ansi.h>
#include <item.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>

#define THIS_PERFORM    00900
#define PF_NAME        "Sử dụng Pháp Bảo"

// 函数：获取描述
string get_desc( object me ) 
{ 
        return "[ " PF_NAME " ]\n Pháp Bảo đã được sử dụng\n"; 
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        object item;

        if( !objectp( item = me->get_equip(HAND_TYPE) ) ) return 1;

        if(     item->get_item_type() != ITEM_TYPE_TALISMAN    // 不是法宝
        ||     !item->is_usable_2() )    // Không thể sử dụng
        {
                send_user( me, "%c%s", '!', sprintf( "Không thể sử dụng %s .", item->get_name() ) );
                return 1;
        }

        if( get_effect(me, EFFECT_CHAR_SUPPRESS) ) 
        {
                send_user( me, "%c%s", '!', sprintf( "%s bị áp chế", item->get_name() ) );
                return 1;
        }

        if( item->get_lasting() >= 100 ) item->get_use_effect_2(me, who, arg);    // 耐久度足够

        return 1;
}

// 函数：获取指令类型
int get_perform_type() { return ON_TALISMAN; }

// 函数：能否使用指令
void can_perform( object me )
{
        object item;

        if( !objectp( item = me->get_equip(HAND_TYPE) ) ) return;	
        if(     item->get_item_type() != ITEM_TYPE_TALISMAN    // 不是法宝
        ||     !item->is_usable_2() )    // Không thể sử dụng
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 0, 0, PF_NAME );
                return ;
        }        
        send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME );
}
