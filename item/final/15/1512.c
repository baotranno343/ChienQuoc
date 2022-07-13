#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;


// 函数：成品编号
int get_fin_type() { return 1512; }

// 函数：镶嵌识别
int get_item_type() { return ITEM_TYPE_SHIKE; }

// 函数：构造处理
void create()
{
        set_name( "Cao Cấp Khí Huyết" );
        set_picid_1(4980);
        set_picid_2(4980);
        set_value(100);
        set("hpp", 60);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Yêu Đới gia tăng 60 điểm Khí Huyết";
}

