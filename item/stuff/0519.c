
// 自动生成：/make/item/make90
#include <item.h>
inherit TALISMAN;

// 函数：原料类型
int get_stuff_type() { return 519; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_GRAVER; }

// 函数：原料颜色
int get_item_color() { return 0; }

// 函数：构造处理
void create()
{
        set_name("Điêu Khắc Đao Tinh Xảo");
        set_picid_1(4907);
        set_picid_2(4907);
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
