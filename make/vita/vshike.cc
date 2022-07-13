#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;


// 函数：成品编号
int get_fin_type() { return %d; }

// 函数：镶嵌识别
int get_item_type() { return ITEM_TYPE_SHIKE; }

// 函数：构造处理
void create()
{
        set_name( "%s" );
        set_picid_1(%d);
        set_picid_2(%d);
        set_value(%d);
}

// 函数：获取描述
string get_desc() 
{ 
        return "%s";
}

