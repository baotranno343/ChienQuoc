
inherit ITEM;
inherit USABLE;

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "Bồi Nguyên Đan" );
        set_picid_1(9170);
        set_picid_2(9170);
        set_unit( "粒" );
        set_value(50);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Gia tăng tối đa 150 Khí Huyết vĩnh viễn";
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

        if( me->get_mascot("hp") == 0 )
        {
                me->add_mascot("hp", 1);
                USER_ENERGY_D->count_max_hp(me);
                return 1;
        }
        else 
        {
                send_user(me, "%c%s", '!', get_name() + " Cả đời chỉ có thể sử dụng 5 lần。" );
                return 0;
        }
}
