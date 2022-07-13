#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：叠加上限
int get_max_combined() { return 30; }

// 函数：成品编号
int get_fin_type() { return 1611; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_KEY; }

// 函数：构造处理
void create()
{
        set_name( "Chìa Khoá Tinh Thiết" );
        set_picid_1(4179);
        set_picid_2(4179);
        set_value(1200);
        set_amount(1);
        set_level(2);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Có thể mở Báo Khố Rương";
}

