#include <ansi.h>
inherit ITEM;
inherit COMBINED;

// 函数：物品叠加上限
int get_max_combined() { return 10000; }
int get_item_value() {return 10 ;}
int get_item_value_2() {return 10 ;}
int get_item_color() {return 2 ;}
// 函数：构造处理
void create()
{
        set_name( "Hoa Hồng" );
        set_picid_1(3005);
        set_picid_2(3005);
        set_value(10);
	//	set_save("knb2",10);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Trong ngày Lễ đám cưới của các đôi tình nhân \ncần sử dụng 20 đoá Hoa Hồng để bày tỏ Tình yêu.";
}
