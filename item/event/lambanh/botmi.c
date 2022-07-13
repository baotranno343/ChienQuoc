#include <effect.h>
inherit ITEM;
inherit COMBINED;

int get_item_color() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "Bột Mì" );
        set_picid_1(3552);
        set_picid_2(3552);
        set_value(2);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Nguyên liệu chủ yếu làm Bánh Trứng.";
}
