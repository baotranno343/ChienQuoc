
// 自动生成：/make/item/make90
#include <item.h>
inherit TALISMAN;

// 函数：原料类型
int get_stuff_type() { return 502; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_HAMMER; }

// 函数：原料颜色
int get_item_color() { return 0; }

// 函数：构造处理
void create()
{
        set_name("Búa Huyền Thiết");
        set_picid_1(3410);
        set_picid_2(3410);
        set_value(7000);
        set_max_lasting(12599);
        set_lasting(12599);
        set_level(90);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Rèn đúc sử dụng loại công này";
}
