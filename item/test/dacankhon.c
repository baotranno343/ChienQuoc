#include <item.h>
#include <ansi.h>

inherit ITEM;
inherit "/inh/item/diamond";
inherit COMBINED;

int get_item_value() {return 99 ;}
int get_item_value_2() {return 88 ;}

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_DIAMOND_4; }
// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

int get_item_color() {return 1 ;}

// 函数：原料类型
int get_stuff_type() { return 326; }

// 函数：构造处理
void create()
{
        set_name("Đá Càn Khôn");
        set_picid_1(8970);
        set_picid_2(8970);
        set_value(7000);
        set_amount(1);
}

string get_loop_desc(object me)
{
	return "";
}

// 函数：获取描述
string get_desc() 
{
	return "Theo truyền thuyết đây là vật liệu hiếm có, được bậc thầy đúc kiếm thời xa xưa sử dụng để đúc luyện vũ khí sắc bén.";
}

