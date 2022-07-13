
// 自动生成：/make/item/make89a

#include <item.h>

inherit ITEM;
inherit "/inh/item/diamond";

// 函数：宝石识别
int is_diamond_2() { return 1; }

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

// 函数：宝石识别
int get_item_type() { return ITEM_TYPE_DIAMOND_2; }

// 函数：宝石属性
string get_diamond_type() { return "hp"; }

// 函数：构造处理
void create()
{
        set_name("残缺橙晶石");
        set_picid_1(8901);
        set_picid_2(8901);
        set_unit("块");
        set_value(20000);
        set_bonus_value(4000);
}

// 函数：获取描述
string get_desc() 
{ 
        return "［宝石合成材料］增加气血"; 
}

// 函数：生成宝石文件
string get_diamond_file()
{
        return __DIR__ "8951";
}
