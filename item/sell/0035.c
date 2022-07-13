#include <ansi.h>
#include <skill.h>
#include <effect.h>

inherit ITEM;
inherit COMBINED;
inherit USABLE;

int get_item_value() {return 5 ;}
int get_item_value_2() {return 5 ;}
int get_item_number() {return 10001069 ;}
int get_item_color() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "Thiên Nguyên Đan HK" );
        set_picid_1(4116);
        set_picid_2(4116);
        set_value(20);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Theo truyền thuyết đó là loại thuốc quí của Vương Gia, Mỗi 1 giây khôi phục cho người chơi 2 điểm Nguyên Khí, \n Kéo dài trong 120 phút. Thời gian tác dụng là 2 giây.";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me, this_object()); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object item )
{
        if( get_effect_3(me, EFFECT_RECOVER_YUAN)>=298 ) 
        {
                return 0;
        }
	if ( get_effect_3(me, EFFECT_RECOVER_YUAN) )
	{
		send_user( me, "%c%c%s", 0x59, 1, sprintf("Ngươi vẫn đang còn thời gian hiệu quả Thiên Nguyên Đan,ngươi muốn sử dụng đè lên không？\n"
                        ESC "%c\n"ESC"use ! %x#\n"
			, 1, getoid(item) ) );		
		return 0;
	}
        set_effect_2(me, EFFECT_RECOVER_YUAN, 7200, 1 );
        send_user( me, "%c%w%w%c", 0x81, 298, get_effect_3(me, EFFECT_RECOVER_YUAN), EFFECT_GOOD );
        return 1;
}

// 函数：使用效果
int confirm_use( object me ) { return __FILE__ ->confirm_use_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int confirm_use_callout( object who, object item )
{
        set_effect_2(who, EFFECT_RECOVER_YUAN, 7200, 1 );
        send_user( who, "%c%w%w%c", 0x81, 298, get_effect_3(who, EFFECT_RECOVER_YUAN), EFFECT_GOOD );
	return 1;
}

void into_effect(object me)
{
	me->add_yuan(2);
}

string get_loop_desc(object me)
{
	return "Thiên Nguyên Đan：\n    Mỗi 2 giây hồi phục 1 điểm Nguyên Khí。";
}