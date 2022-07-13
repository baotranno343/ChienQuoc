
#include <effect.h>
#include <skill.h>

inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

// 函数：成品编号
int get_fin_type() { return 1836; }

// 函数：构造处理
void create()
{
        set_name( "Thanh Tâm Đan" );
        set_picid_1(9145);
        set_picid_2(9145);
        set_unit( "粒" );
        set_value(2000);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Một loại thuốc viên có thể làm cho con người hồi phục trạng thái bình thường, giải trừ đi trạng thái bất thường trên mình, hủy bỏ hiệu quả biến thân, thời gian tái sử dụng 30 giây";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me )
{
	int i, size, time, pos;
        int * all = ({ EFFECT_CHAR_POISON, EFFECT_CHAR_POISON_2, EFFECT_CHAR_BLOOD, EFFECT_USER_BURN, EFFECT_CHAR_LAZY, EFFECT_CHAR_SLOW, EFFECT_CHAR_NO_MOVE, EFFECT_CHAR_CHAOS, EFFECT_CHAR_BLIND, EFFECT_NO_WEAPON, EFFECT_2123_ARMORFALL, EFFECT_02614, EFFECT_02616, EFFECT_CHAR_ARMORFALL, EFFECT_CHAR_POWERFALL, EFFECT_CHAR_FALL, EFFECT_MP_FALL,EFFECT_MAGIC_CARD });      
      	if( gone_time( me->get_time("eat_9145") ) < 30 )
        {
                send_user( me, "%c%s", '!', sprintf("使用清心丹冷冻时间还剩%d秒", 30 - gone_time( me->get_time("eat_9145") )) );
                return 0;
        }
        me->set_time( "eat_9145", time() );
	size = sizeof(all);
	time = 0; pos = -1;
	for (i =0;i<size;i++) if (time < get_effect_3(me, all[i])) 
	{
		time = get_effect_3(me, all[i]);
		pos = i;
	}
        if (pos!=-1)
        {
        	if (all[pos]<96) set_effect(me, all[pos], 1);
        	else set_effect_2(me, all[pos], 1, 1);
        }
        set_effect(me, EFFECT_CHAR_9145, 3);

        return 1;
}
