#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit USABLE;   

// 函数：成品编号
int get_fin_type() { return 2331; }

// 函数：构造处理
void create()
{
        set_name( "Càn Khôn Nang" );
        set_picid_1(7104);
        set_picid_2(7104);
        set_value(1000);
        set("bag", 24);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Bao vải nhỏ thường được người đi xa sử dụng,\n Có thể tăng không gian túi cho người sử dụng thêm 24 ngăn.\n Bao vải sau 10 ngày sẽ tự động bị hỏng."; 
}

// 函数：使用效果
int get_use_effect( object me ) { return "/cmd/std/bag" ->get_use_effect(me, this_object()); }
