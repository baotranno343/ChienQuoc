
// 自动生成：/make/item/make90
#include <item.h>
inherit ITEM;
inherit COMBINED;

// 函数：叠加上限
int get_max_combined() { return 30; }

// 函数：原料类型
int get_stuff_type() { return 236; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_STUFF; }

// 函数：原料颜色
int get_item_color() { return 0; }

// 函数：构造处理
void create()
{
        set_name("Động Vật Bì Mao");
        set_picid_1(4106);
        set_picid_2(4106);
        set_unit("张");
        set_value(150);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Động vật trên người chống lạnh phòng hộ thân thể phu";
}
