
// 自动生成：/make/item/make90
#include <item.h>
inherit ITEM;
inherit COMBINED;

// 函数：叠加上限
int get_max_combined() { return 1; }

// 函数：原料类型
int get_stuff_type() { return 100; }

int get_rate_2() { return 40; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_DIAMOND; }

// 函数：原料颜色
int get_item_color() { return 1; }
int get_item_value() {return 10 ;}
int get_item_value_2() {return 10 ;}

// 函数：构造处理
void create()
{
        set_name("Hoàn Mỹ Bổ Thiên Thạch");
        set_picid_1(8973);
        set_picid_2(8973);
        set_value(1000);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Gia tăng 40% xác xuất chế tạo vật phẩm thành công";
}
