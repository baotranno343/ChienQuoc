#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;


// 函数：成品编号
int get_fin_type() { return 1507; }

// 函数：镶嵌识别
int get_item_type() { return ITEM_TYPE_SHIKE; }

// 函数：构造处理
void create()
{
        set_name( "Trung Cấp Ngoại Công" );
        set_picid_1(4980);
        set_picid_2(4980);
        set_value(100);
        set("app", 20);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Vũ khí gia tăng 20 điểm Ngoại Công";
}

