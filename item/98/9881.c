#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit LEGEND_ITEM;
int is_huodan() { return 1;}

// 函数：构造处理
void create()
{
        set_name( "Giấy Xuất Hàng" );
        set_picid_1(3854);
        set_picid_2(3854);
        set_unit( "封" );
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.Giấy viết Chủ Tiệm Tạp Hóa thường dùng, để ghi chép tình hình bán hàng."; 
}