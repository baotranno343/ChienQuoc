
#include <item.h>
#include <equip.h>

inherit ITEM;
inherit COMBINED;
inherit "/inh/equip/equip";

// private int Poison;                     // 毒药毒性

// 函数：毒药识别
int is_poison() { return 1; }

int get_hide() {return 0;}

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

// 函数：自动装备类型
int is_auto_equip() { return 1; }

// 函数：毒药识别
int get_item_type() { return ITEM_TYPE_POISON; }

// 函数：获取装备类型
int get_equip_type() { return HAND_TYPE; }

// 函数：获取装备描述
string get_equip_string() { return "[Độc Dược]"; }

// 函数：获取耐久度
int get_lasting() { return 10; }

// 函数：获取最大耐久度
int get_max_lasting() { return 10; }

// 函数：适用门派
int get_family() { return 4; }
