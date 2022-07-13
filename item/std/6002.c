#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit USABLE;   

int get_item_value() {return 500 ;}
int get_item_value_2() {return 500 ;}
//int get_item_number() {return 10002001 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name( "Túi Càn Khôn" );
        set_picid_1(9601);
        set_picid_2(9601);
        set_value(5000);
	//	set_save("knb",500);
        set("bag", 24);
        set_record(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Túi thần Càn Khôn có thể chứa cả thiên địa Nhật Nguyệt bên trong. \n Gia tăng thêm 24 ngăn cho hành trang khi sử dụng.\n Túi Càn Khôn sau 30 ngày sẽ tự động bị hỏng."; 
}

// 函数：使用效果
int get_use_effect( object me ) { return "/cmd/std/bag" ->get_use_effect(me, this_object()); }
