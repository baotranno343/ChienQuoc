#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;


// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_STUFF; }

// 函数：原料类型
int get_stuff_type() { return 171; }

// 函数：构造处理
void create()
{
        set_name("鸡蛋");
        set_picid_1(3251);
        set_picid_2(3251);
        set_unit("个");
        set_value(50);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "酒食生活技能所需材料"; 
}
