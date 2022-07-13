
#include <effect.h>
#include <skill.h>
#include <ansi.h>

inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

int get_item_value() {return 250 ;}
int get_item_value_2() {return 200 ;}
int get_item_number() {return 10001011 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name( "人参" );
        set_picid_1(4010);
        set_picid_2(4010);
        set_unit( "粒" );
        set_value(180);
        set_amount(1);
        set_record(1);
        // -- 与原装备相比增加绑定属性
        set_no_give(1);
        set_no_sell(1);
        //        
        set("effect", 600);
}

// 函数：获取描述
string get_desc() 
{ 
        return "十分名贵的药材，据说有强身健体之用。持续1小时内可提升玩家600点气血上限。";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me,this_object()); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me,object item )
{
/*      if( gone_time( me->get_time("eat") ) < 1 )
        {
                me->set_time( "eat", time() );
                return 0;
        }
        me->set_time( "eat", time() );  */

	if ( get_effect(me, EFFECT_RENSHEN) )
	{
		if (me->get_save("rs_hp")==0 || me->get_save("rs_hp")==600)
			send_user( me, "%c%c%w%s", ':', 3, 0,sprintf("你身上已经有一个人参在产生作用，你确定要覆盖它的效果吗？\n"ESC"确定\nuse ! %x#\n"ESC"取消",getoid(item))); 
		else
			send_user( me, "%c%c%w%s", ':', 3, 0,sprintf("你身上已经有一个人参王在产生作用，你确定要覆盖它的效果吗？\n"ESC"确定\nuse ! %x#\n"ESC"取消",getoid(item))); 
		return 0;
	}
        set_effect(me, EFFECT_RENSHEN, 3600);
        me->set_save("rs_hp", item->get("effect"));
        USER_ENERGY_D->count_max_hp(me);
	send_user( me, "%c%w%w%c", 0x81, 6, 3600, EFFECT_GOOD );
	send_user( me, "%c%w%s", 0x82, 6, CHAR_CHAR_D->get_loop_desc(me, 6) );
        return 1;
}

string get_loop_desc(object me)
{
	if (me->get_save("rs_hp")==0 || me->get_save("rs_hp")==600)
		return "人参：\n    持续1小时内可提升玩家600点气血上限。";
	else
		return "人参王：\n    持续1小时内可提升玩家2000点气血上限。";
}

void into_effect(object me)
{
	USER_ENERGY_D->count_max_hp(me);
	send_user( me, "%c%w%w%c", 0x81, 6, 0, EFFECT_GOOD );
}

// 函数：使用效果
int confirm_use( object me ) { return __FILE__ ->confirm_use_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int confirm_use_callout( object me, object item )
{
	set_effect(me, EFFECT_RENSHEN, 3600);
	me->set_save("rs_hp", item->get("effect"));
        USER_ENERGY_D->count_max_hp(me);
	send_user( me, "%c%w%w%c", 0x81, 6, 3600, EFFECT_GOOD );
	send_user( me, "%c%w%s", 0x82, 6, CHAR_CHAR_D->get_loop_desc(me, 6) );
        return 1;
}