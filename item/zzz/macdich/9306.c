
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
string get_diamond_type() { return "pp"; }

// 宝石打造的辩别标志
string get_diamond_index() {return "6";}

// 函数：构造处理
void create()
{
        set_name("Thủy Tinh Thạch");
        set_real_name("Thủy Tinh Thạch");
        set_picid_1(8985);
        set_picid_2(8985);
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
		value = 17;
		break;	
	case 2:
		value = 22;
		break;	
	case 3:
		value = 27;
		break;	
	case 4:
		value = 32;
		break;					
	case 5:
		value = 37;
		break;
	case 6:
		value = 42;
		break;
	case 7:
		value = 47;
		break;				
	case 8:
		value = 52;
		break;				
	case 9:
		value = 57;
		break;				
	case 10:
		value = 62;
		break;				
	}
	return value;	
}

// 函数：获取描述
string get_desc() 
{ 
	object me = this_object();
	if (!clonep(me)) return "[Tinh luyện] Nội kháng\n[Trang bị sử dụng thích hợp] Y phục, Yêu Đới, Hạng Liên, Hài, Mão";
        return sprintf("[Tinh luyện] Nội kháng %+d\n[Trang bị sử dụng thích hợp] Y phục, Yêu Đới, Hạng Liên, Hài, Mão", me->get_diamond_add()); 
}

string get_name()
{
	object me = this_object();
	if (!clonep(me)) return "Thủy Tinh Thạch";
	return sprintf("Thủy Tinh Thạch cấp %d ", me->get_level());
}