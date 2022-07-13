#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit USABLE;   

int get_item_value() {return 750 ;}
int get_item_value_2() {return 750 ;}
//int get_item_number() {return 10001071 ;}
int get_item_color() {return 2 ;}

// 函数：构造处理
void create()
{
        set_name( "Túi Hỗn Nguyên Càn Khôn" );
        set_picid_1(9601);
        set_picid_2(9601);
        set_value(20000);
        set("bag", 24);
        set("lasting", 1);	// 永久可用
}

// 函数：获取描述
string get_desc() 
{ 
        return "Túi tiền thần kỳ trăm năm mới luyện thành, có khả năng gia tăng 24 ô cho hành trang\nThời hạn sử dụng vĩnh viễn."; 
}

string get_short()
{
	return "Túi tiền thần kỳ trăm năm mới luyện thành, có khả năng gia tăng 24 ô cho hành trang\nThời hạn sử dụng vĩnh viễn.";
}

// 函数：使用效果
int get_use_effect( object me ) { return "/cmd/std/bag" ->get_use_effect(me, this_object()); }
