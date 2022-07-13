
// 脳脭露炉脡煤鲁脡拢潞/make/item/make90
#include <item.h>
inherit ITEM;
inherit USABLE;

// 潞炉脢媒拢潞脥录脰陆脨貌潞脜
int get_product_type() { return 29; }

// 潞炉脢媒拢潞脥录脰陆脪陋脟贸录录脛脺
int get_product_skill() { return 650; }

// 潞炉脢媒拢潞脥录脰陆脪陋脟贸脌脿卤冒
int get_product_sort() { return 1; }

// 潞炉脢媒拢潞脥录脰陆脪陋脟贸碌脠录露
int get_product_level() { return 38; }

// 潞炉脢媒拢潞驴脡脢鹿脫脙脦茂脝路
int get_item_type_2() { return ITEM_TYPE_2_PRODUCT; }

int get_item_color() { return 0; }

// 潞炉脢媒拢潞鹿鹿脭矛麓娄脌铆
void create()
{
        set_name("Công thức Cực Hiệu Pháp Lực");
        set_picid_1(9807);
        set_picid_2(9807);
        set_value(200);
}

// 潞炉脢媒拢潞禄帽脠隆脙猫脢枚
string get_desc()
{
        return "Học làm Cực Hiệu Pháp Lực";
}

string get_product()
{
	return "/item/final/15/1506";
}

// 潞炉脢媒拢潞脢鹿脫脙脨搂鹿没
int get_use_effect( object me ) { return "/sys/item/product" ->get_use_effect(me, this_object()); }
