
#include <effect.h>
#include <skill.h>
#include <ansi.h>

inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

int get_item_value() {return 25 ;}
int get_item_value_2() {return 20 ;}
//int get_item_number() {return 10001011 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name( "Nhân Sâm" );
        set_picid_1(4010);
        set_picid_2(4010);
        set_unit( "粒" );
        set_value(180);
	//	set_save("knb",20);
        set_amount(1);
        set_record(1);
        set("effect", 600);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Loại dược liệu vô cùng quý giá, tương truyền có tác dụng tráng kiện cơ thể. Khi sử dụng sẽ tăng thêm 600 điểm Khí Huyết tối đa trong vòng 1 giờ.";
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
			send_user( me, "%c%c%w%s", ':', 3, 0,sprintf("Bạn hiện đang có hiệu quả Nhân Sâm, bạn muốn sử dụng đè lên không ?\n"ESC"Xác nhận\nuse ! %x#\n"ESC"Huỷ bỏ",getoid(item))); 
		else
			send_user( me, "%c%c%w%s", ':', 3, 0,sprintf("Bạn hiện đang có hiệu quả Nhân Sâm Vương, bạn muốn sử dụng đè lên không ?？\n"ESC"Xác nhận\nuse ! %x#\n"ESC"Huỷ bỏ",getoid(item))); 
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
		return "Nhân Sâm:\n    Trong 1 giờ gia tăng 600 Khí Huyết.";
	else
		return "Nhân Sâm Vương:\n    Trong 1 giờ gia tăng 2000 Khí Huyết";
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