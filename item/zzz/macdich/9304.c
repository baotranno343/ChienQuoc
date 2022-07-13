
// 自动生成：/make/item/make89a

#include <item.h>

inherit ITEM;
inherit "/inh/item/diamond";

// 函数：宝石识别
int is_diamond_2() { return 1; }

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

int get_item_color() {return 1 ;}

// 函数：宝石识别
int get_item_type() { return ITEM_TYPE_DIAMOND_3; }

// 函数：宝石属性
string get_diamond_type() { return "dp"; }

// 宝石打造的辩别标志
string get_diamond_index() {return "4";}

// 函数：构造处理
void create()
{
        set_name("Kim Tinh Thạch");
        set_real_name("Kim Tinh Thạch");
        set_picid_1(8983);
        set_picid_2(8983);
        set_unit("块");
        set_value(40000);
		set_no_give(1);
	//	set_save("knb2",10);
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
		value = 15;
		break;	
	case 2:
		value = 20;
		break;	
	case 3:
		value = 25;
		break;	
	case 4:
		value = 30;
		break;					
	case 5:
		value = 35;
		break;
	case 6:
		value = 40;
		break;
	case 7:
		value = 45;
		break;				
	case 8:
		value = 50;
		break;				
	case 9:
		value = 55;
		break;				
	case 10:
		value = 60;
		break;				
	}
	return value;	
}

// 函数：获取描述
string get_desc() 
{ 
	object me = this_object();
	if (!clonep(me)) return "[Tinh luyện] Ngoại kháng\n[Trang bị sử dụng thích hợp] Y phục, Yêu Đới, Hạng Liên, Hài, Mão";
        return sprintf("[Tinh luyện] Ngoại kháng %+d\n[Trang bị sử dụng thích hợp] Y phục, Yêu Đới, Hạng Liên, Hài, Mão", me->get_diamond_add()); 
}

string get_name()
{
	object me = this_object();
	if (!clonep(me)) return "Kim Tinh Thạch";
	return sprintf("Kim Tinh Thạch cấp %d ", me->get_level());
}