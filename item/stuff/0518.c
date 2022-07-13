
// 自动生成：/make/item/make90
#include <item.h>
inherit TALISMAN;

// 函数：原料类型
int get_stuff_type() { return 518; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_GRAVER; }

// 函数：原料颜色
int get_item_color() { return 0; }

// 函数：构造处理
void create()
{
        set_name("Điêu Khắc Đao Hàn Thiết");
        set_picid_1(4907);
        set_picid_2(4907);
        set_value(9000);
        set_max_lasting(15099);
        set_lasting(15099);
        set_level(120);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Điêu Khắc đại sư sử dụng công cụ";
}
