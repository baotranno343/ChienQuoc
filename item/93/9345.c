
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
string get_diamond_type() { return "cp"; }

// 宝石打造的辩别标志
string get_diamond_index() {return "5";}

// 函数：宝石精炼装备最高级别
int get_mix_level() { return 20; }

// 函数：构造处理
void create()
{
        set_name("火晶石");
        set_picid_1(8984);
        set_picid_2(8984);
        set_unit("块");
        set_value(50);
        set_level(1);
        set_no_give(1);
        set_no_sell(1); 
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
	}
	return value;	
}

// 函数：获取描述
string get_desc() 
{ 
	object me = this_object();
	if (!clonep(me)) return "［精炼］ 法攻\n［适用装备］ 武器、项链，限20级以下装备。";
        return sprintf("［精炼］ 法攻 %+d\n［适用装备］ 武器、项链，限20级以下装备。", me->get_diamond_add()); 
}

string get_name()
{
	object me = this_object();
	if (!clonep(me)) return "新手火晶石";
	return sprintf("新手%d级火晶石", me->get_level());
}