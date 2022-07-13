#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：叠加上限
int get_max_combined() { return 30; }

// 函数：成品编号
int get_fin_type() { return 1615; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_KEY; }

// 函数：构造处理
void create()
{
        set_name( "Chìa Khoá Huyền Thiết" );
        set_picid_1(4182);
        set_picid_2(4182);
        set_value(1600);
        set_amount(1);
        set_level(5);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Có thể mở Bảo Khố Rương Cũ Nát";
}

