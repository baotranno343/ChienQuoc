// make/item/make_ss_item生成

#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit USABLE;   
int get_item_color() { return 2;};
// 函数：构造处理
void create()
{
        set_name("Kim Ngưu");
        set_picid_1(3022);
        set_picid_2(4261);
        set("picid",3022);
        set_value(888);
        set_no_give(1);
}

// 函数：获取描述
string get_desc() 
{
	return "Kim Ngưu là 1 trong 12 cung Hoàng Đạo";
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
