#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit LEGEND_ITEM;


// 函数：构造处理
void create()
{
        set_name( "Ngọc minh châu" );
        set_picid_1(3230);
        set_picid_2(3230);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.Một viên phát ra kỳ dị ánh sáng đích trong bảo khố châu."; 
}