
// 自动生成：/make/item/make89a

#include <item.h>

inherit ITEM;
inherit "/inh/item/diamond";

// 函数：宝石识别
int is_diamond_2() { return 1; }

int get_item_value() {return 90 ;}
int get_item_value_2() {return 90 ;}
//int get_item_number() {return 10001044 ;}

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

int get_item_color() {return 1 ;}

// 函数：宝石识别
int get_item_type() { return ITEM_TYPE_DIAMOND_3; }

// 函数：宝石属性
string get_diamond_type() { return "double"; }

// 宝石打造的辩别标志
string get_diamond_index() {return "0";}

// 函数：构造处理
void create()
{
        set_name("Ám Linh Thạch");
        set_real_name("Ám Tinh Thạch");
        set_picid_1(8989);
        set_picid_2(8989);
        set_unit("块");
        set_value(700);
        set_level(1);
}

int get_diamond_add()
{
	int value, level;
	object me = this_object();
	level = me->get_level();
	switch(level)
	{
	default:
		value = 20;
		break;	
	case 2:
		value = 40;
		break;	
	case 3:
		value = 60;
		break;	
	case 4:
		value = 80;
		break;					
	case 5:
		value = 100;
		break;
	case 6:
		value = 120;
		break;
	case 7:
		value = 140;
		break;				
	case 8:
		value = 160;
		break;				
	case 9:
		value = 180;
		break;				
	case 10:
		value = 200;
		break;		
	}
	return value;	
}

// 函数：获取描述
string get_desc() 
{ 
	object me = this_object();
	if (!clonep(me)) return "Dùng để tăng cường vật liệu đặc biệt của trang bị, thuộc tính tăng thêm chịu ảnh hưởng đặc biệt từ linh thạch.\nLinh thạch cùng loại cùng cấp cũng có thể kết hợp với những tinh thạch hoặc những linh thạch cùng loại cùng cấp khác để thăng cấp.\n[Tinh luyện] Bạo Kích\n[Thích hợp với trang bị] vũ khí";
        return sprintf("Dùng để tăng cường vật liệu đặc biệt của trang bị, thuộc tính tăng thêm chịu ảnh hưởng đặc biệt từ linh thạch.\nLinh thạch cùng loại cùng cấp cũng có thể kết hợp với những tinh thạch hoặc những linh thạch cùng loại cùng cấp khác để thăng cấp.\n[Tinh luyện] Bạo Kích %+.2f ％\n[Thích hợp với trang bị] vũ khí", to_float(me->get_diamond_add())/100); 
}

string get_name()
{
	object me = this_object();
	if (!clonep(me)) return "Ám Linh Thạch";
	return sprintf("Ám Linh Thạch cấp %d ", me->get_level());
}