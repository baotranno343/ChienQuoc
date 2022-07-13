
#include <effect.h>
#include <skill.h>

inherit ITEM;
inherit USABLE;

int get_item_color() { return 1; }
// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

// 函数：成品编号
int get_fin_type() { return 1827; }

// 函数：构造处理
void create()
{
        set_name( "Quy Nguyên Đan" );
        set_picid_1(9165);
        set_picid_2(9165);
        set_unit( "粒" );
        set_value(50);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Trong 1 giờ gia tăng 12% Nội kháng";
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
	send_user( me, "%c%w%w%c", 0x81, 9165, 3600, EFFECT_GOOD );
        set_effect(me, EFFECT_ITEM_9165, 3600);
	me->set_save( "9165#", 12 );
        USER_ENERGY_D->count_pp(me);
        return 1;
}


void effect_done(object me)
{
        send_user( me, "%c%w%w%c", 0x81, 9165, 0, EFFECT_GOOD );

}

// 函数：获取描述(持续)
string get_loop_desc( object me )
{
        return "Trong 1 giờ Nội kháng gia tăng 12％。\n";
}