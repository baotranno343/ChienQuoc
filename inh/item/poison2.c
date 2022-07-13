
#include <item.h>

inherit ITEM;
inherit USABLE;

private int Poison;                     // 毒粉毒性

// 函数：毒粉识别
// int is_poison_2() { return 1; }

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

// 函数：毒粉识别
int get_item_type() { return ITEM_TYPE_POISON_2; }

// 函数：获取毒性点数
int get_poison() { return Poison; }

// 函数：设置毒性点数
int set_poison( int point ) { return Poison = range_value(point, 0, MAX_NUMBER); }

// 函数：增添毒性点数
int add_poison( int point ) { return set_poison( get_poison() + point ); }
