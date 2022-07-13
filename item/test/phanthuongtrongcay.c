#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;

int get_item_color() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "Phần thưởng Trồng Cây" );
        set_picid_1(3859);
        set_picid_2(3859);
        set_value(50);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Phần thưởng Trồng Cây, có thể đến gặp Sứ giả Quốc Khánh để đổi lấy vật phẩm.";
}
