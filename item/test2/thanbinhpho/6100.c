
// 自动生成：/make/item/make90
#include <item.h>
inherit ITEM;
//inherit USABLE;

// 函数：图纸要求类别
int get_product_sort() { return 5; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_PRODUCT; }
int is_thanbinhpho() { return 1; }
int get_item_color() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Thần Binh Phổ - Hoả Thiên Côn");
        set_picid_1(9807);
        set_picid_2(9807);
        set_value(200);
}

// 函数：获取描述
string get_desc()
{
        return "Ghi ghép lại cách chế tạo thần binh tuyệt thế Hoả Thiên Côn.";
}

string get_product()
{
	return "/item/75/9130";
}

// 函数：使用效果
int get_use_effect( object me ) { return "/sys/item/product" ->get_use_effect(me, this_object()); }
