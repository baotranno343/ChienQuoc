#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;


// 函数：成品编号
int get_fin_type() { return 1526; }

// 函数：镶嵌识别
int get_item_type() { return ITEM_TYPE_SHIKE; }

// 函数：构造处理
void create()
{
        set_name( "Siêu Cấp Pháp Lực" );
        set_picid_1(4980);
        set_picid_2(4980);
        set_value(100);
        set("mpp", 400);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Giày gia tăng 400 điểm Pháp Lực";
}

