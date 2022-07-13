
// 自动生成：/make/item/make90
#include <item.h>
inherit ITEM;
inherit USABLE;

// 函数：图纸序号
int get_product_type() { return %d; }

// 函数：图纸要求技能
int get_product_skill() { return %d; }

// 函数：图纸要求类别
int get_product_sort() { return %d; }

// 函数：图纸要求等级
int get_product_level() { return %d; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_PRODUCT; }

int get_item_color() { return %d; }

// 函数：构造处理
void create()
{
        set_name("%s");
        set_picid_1(%d);
        set_picid_2(%d);
        set_value(%d);
}

// 函数：获取描述
string get_desc()
{
        return "%s";
}

string get_product()
{
	return "%s";
}

// 函数：使用效果
int get_use_effect( object me ) { return "/sys/item/product" ->get_use_effect(me, this_object()); }
