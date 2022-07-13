
// 自动生成：/make/item/make90
#include <item.h>
inherit TALISMAN;

// 函数：原料类型
int get_stuff_type() { return %d; }

// 函数：可使用物品
int get_item_type_2() { return %s; }

// 函数：原料颜色
int get_item_color() { return %d; }

// 函数：构造处理
void create()
{
        set_name("%s");
        set_picid_1(%d);
        set_picid_2(%d);
        set_value(%d);
        set_max_lasting(%d);
        set_lasting(%d);
        set_level(%d);
}

// 函数：获取描述
string get_desc() 
{ 
        return "%s";
}
