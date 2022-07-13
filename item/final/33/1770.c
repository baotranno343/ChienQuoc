
// 自动生成：/make/item/make31c
#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;   

// 函数：叠加上限
//  int get_max_combined() { return 30; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_PET; }
//宠物物品
int is_pet_item() { return 1;}

// 函数：成品编号
int get_fin_type() { return 1770; }

// 函数：构造处理
void create()
{
        set_name("Thần Bí Qủa");
        set_picid_1(3289);
        set_picid_2(3289);
        set_unit("个");
        set_value(1700);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{
	string desc;
	return desc = "Mỗi lần sử dụng Bảo thú gia tăng tuổi thọ 50, tuy nhiên có 1％ tỷ lệ trúng độc";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__->get_use_effect_call(me, this_object()); }

int get_use_effect_call(object me,object item)
{
	object owner;
	if ( !me->is_pet() )
		return 0;
	me->add_life(50);
	owner = me->get_owner();
	tell_user(owner,"你的"+me->get_name()+"寿命增加50点");
	if( !random100() )
	{
		me->add_life(-200);
		send_user(owner,"%c%s",'!',"你的"+me->get_name()+"中毒了！");
	}
	return 1;	
}