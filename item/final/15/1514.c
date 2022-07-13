#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;


// 函数：成品编号
int get_fin_type() { return 1514; }

// 函数：镶嵌识别
int get_item_type() { return ITEM_TYPE_SHIKE; }

// 函数：构造处理
void create()
{
        set_name( "Cao Cấp Ngoại Công" );
        set_picid_1(4980);
        set_picid_2(4980);
        set_value(100);
        set("app", 30);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Vũ Khí gia tăng 30 điểm Ngoại Công";
}

