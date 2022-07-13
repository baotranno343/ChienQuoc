
#include <ansi.h>
#include <equip.h>

inherit "/inh/item/poison2";

// 函数：构造处理
void create()
{
        set_name( "鹤顶红粉" );
        set_picid_1(9131);
        set_picid_2(9131);
        set_unit( "瓶" );
        set_value(2000);
}

// 函数：获取描述
string get_desc() 
{ 
        return "涂在武器上，使武器具有毒性";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object item )
{
        object weapon;

        if( !objectp( weapon = me->get_equip(WEAPON_TYPE) ) )
        {
                send_user(me, "%c%s", '!', "请装备需要涂毒的武器。" );
                return 0;
        }
        else if( weapon->get_poison() )
        {
                send_user(me, "%c%s", '!', weapon->get_name() + "已经涂了毒了。" );
                return 0;
        }
        else
        {
                weapon->set_poison( item->get_poison() );
                write_user( me, ECHO "您小心翼翼地将%s均匀地涂沫在%s上。", item->get_name(), weapon->get_name() );
                send_user( me, "%c%d%c", 0x31, getoid(weapon), 0 );    // 更新描述
                return 1;
        }
}
