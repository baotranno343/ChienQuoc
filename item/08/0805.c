// make/item/make_ss_item生成

#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit USABLE;   
int get_item_value() {return 300 ;}
int get_item_value_2() {return 300 ;}
int get_item_number() {return 10001079 ;}
int get_item_color() { return 2;};
// 函数：构造处理
void create()
{
        set_name("Rắn");
        set_picid_1(3012);
        set_picid_2(4249);
        set("picid",3012);
        set_value(888);
        set_no_give(1);
}

// 函数：获取描述
string get_desc() 
{
	return "Rắn là 1 trong 12 con giáp";
}
// 函数：使用效果
int get_use_effect( object me )
{
	send_user( me, "%c%c%w%s", ':', 3, 0,sprintf("Sử dụng sẽ đạt được Thần thú, muốn sử dụng không ?\n"ESC"Chấp nhận\nuse ! %x#\n"ESC"Hủy bỏ",getoid(this_object()))); 
	return 0;
}
// 函数：使用效果
int confirm_use( object me ) 
{ 
	return "sys/user/beast"->use_shenshou_item(me,this_object());
}
