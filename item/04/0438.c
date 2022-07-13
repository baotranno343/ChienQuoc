#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;

// 函数：物品叠加上限
int get_max_combined() { return 200; }
int get_item_color() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Huy Chương Điểm Danh");
        set_picid_1(3859);
        set_picid_2(3859);
        set_value(50);
        set_amount(1);
		set_no_give(1);
}

// 函数：获取描述
string get_desc() 
{
	return "Vật phẩm có được khi điểm danh hằng ngày. Thu thập đủ 30 cái sẽ đổi được trang bị vai vĩnh viễn.";    	
}