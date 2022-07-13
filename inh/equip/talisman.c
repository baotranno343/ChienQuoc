
#include <item.h>
#include <equip.h>

inherit ITEM;
inherit "/inh/equip/equip";

// 函数：法宝识别
// int is_talisman() { return 1; }

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

int get_hide() {return 0;}

int get_record() {return 1;}

// 函数：法宝识别
int get_item_type() { return ITEM_TYPE_TALISMAN; }

// 函数：获取装备类型
int get_equip_type() { return HAND_TYPE; }

// 函数：获取装备描述
string get_equip_string() { return "[Pháp Bảo]"; }

int get_item_color()
{
        int level = get_level();
        switch(level)
        {
        case 1:  return ITEM_COLOR_0; break;                
        case 2:  return ITEM_COLOR_1; break;
        default: return ITEM_COLOR_2; break;                                
        }        
}
