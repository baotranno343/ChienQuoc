
#include <effect.h>

inherit ITEM;
inherit USABLE;

int get_item_color() { return 1; }
// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

// 函数：成品编号
int get_fin_type() { return 1825; }

// 函数：构造处理
void create()
{
        set_name( "Kim Cang Tán" );
        set_picid_1(9163);
        set_picid_2(9163);
        set_unit( "包" );
        set_value(50);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Trong 1 giờ gia tăng 12% Ngoại kháng";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me )
{
	int time;
/*      if( gone_time( me->get_time("eat") ) < 1 )
        {
                me->set_time( "eat", time() );
                return 0;
        }
        me->set_time( "eat", time() );  */
        time =  get_effect_3(me, EFFECT_USER_DP);
        if (time>0)
        {
        	send_user(me, "%c%s", '!', sprintf("Gia tăng Ngoại kháng còn lại %d giây", time) );
        	return 0;
        }
	me->set_save("03291#", me->get_dp()*12/100);
        set_effect(me, EFFECT_USER_DP, 3600);
        USER_ENERGY_D->count_dp(me);

        return 1;
}
