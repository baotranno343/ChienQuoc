
// 自动生成：/make/item/make31c
#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;

// 函数：构造处理
void create()
{
        set_name("Phế Phẩm");
        set_picid_1(4905);
        set_picid_2(4905);
        set_unit("个");
        set_value(500);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{
	string desc;
	desc = "Chế tạo ra Phế Phẩm";
	return desc;
}
