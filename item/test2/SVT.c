
// 自动生成：/make/item/make31c
#include <item.h>
#include <ansi.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;   

int get_item_value() {return 75 ;}
int get_item_value_2() {return 75 ;}
int get_item_color() {return 1 ;}
// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_PET; }
//宠物物品
int is_pet_item() { return 1;}
// 函数：构造处理
void create()
{
        set_name("Sủng Vật Thạch");
        set_picid_1(4236);
        set_picid_2(4236);
        set_unit("个");
        set_value(400);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{
	string desc;
	return desc = "Linh Thạch chuyên dụng cho Bảo Thú, sau khi sử dụng \nhồi phục cho Bảo Thú 100 Khí Huyết và 100 Pháp Lực, \nhiệu quả Linh Thạch kéo dài trong 30 phút.";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__->get_use_effect_call(me, this_object()); }

int get_use_effect_call(object me,object item)
{
	object owner;
	if ( !me->is_pet() )
		return 0;
	owner = me->get_owner();
	if ( me->get_save("sungvatthach") > 0 )
	{
		send_user(owner,"%c%s",'!',me->get_name()+" vẫn còn hiệu quả Linh Thạch.");
		return 0;	
	}
	write_user(owner,me->get_name()+" đã nhận được hiệu quả Linh Thạch trong 30 phút.");
    me->set_save("sungvatthach",3600);
	return 1;	
}