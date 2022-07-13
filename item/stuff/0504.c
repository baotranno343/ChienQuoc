
// 自动生成：/make/item/make90
#include <item.h>
inherit TALISMAN;

// 函数：原料类型
int get_stuff_type() { return 504; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_HAMMER; }

// 函数：原料颜色
int get_item_color() { return 0; }

// 函数：构造处理
void create()
{
        set_name("Tinh Chế Hàn Thiết Chuỳ");
        set_picid_1(3410);
        set_picid_2(3410);
        set_value(20000);
        set_max_lasting(17599);
        set_lasting(17599);
        set_level(120);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Công cụ truyền thuyết";
}
