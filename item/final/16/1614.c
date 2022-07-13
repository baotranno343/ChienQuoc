#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：叠加上限
int get_max_combined() { return 1; }

// 函数：成品编号
int get_fin_type() { return 1614; }

// 函数：镶嵌识别
int get_item_type() { return ITEM_TYPE_SHIKE; }

// 函数：构造处理
void create()
{
        set_name( "Nhắm Cấu Kiện" );
        set_picid_1(4173);
        set_picid_2(4173);
        set_value(1500);
        set("double2", 100);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Trang bị vào vũ khí, đề cao 1% Bạo kích";
}

