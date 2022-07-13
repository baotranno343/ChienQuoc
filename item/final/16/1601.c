#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：叠加上限
int get_max_combined() { return 30; }

// 函数：成品编号
int get_fin_type() { return 1601; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_KEY; }

// 函数：构造处理
void create()
{
        set_name( "Chìa Khóa Đồng" );
        set_picid_1(4178);
        set_picid_2(4178);
        set_value(200);
        set_amount(1);
        set_level(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Chìa khóa có thể mở những chiếc hộp đựng bảo bối";
}

