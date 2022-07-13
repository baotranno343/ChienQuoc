
// 自动生成：/make/item/make31c
#include <item.h>
#include <ansi.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;   

int get_item_value() {return 45 ;}
int get_item_value_2() {return 45 ;}
int get_item_color() {return 1 ;}
// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_PET; }
//宠物物品
int is_pet_item() { return 1;}
// 函数：构造处理
void create()
{
        set_name("Sủng Vật Trị Dược");
        set_picid_1(9976);
        set_picid_2(9976);
        set_unit("个");
        set_value(400);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{
	string desc;
	return desc = "Sau khi sử dụng có thể lập tức hồi phục cho Bảo Thú 2000 Khí huyết. \nTái sử dụng sau 10 giây.";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__->get_use_effect_call(me, this_object()); }

int get_use_effect_call(object me,object item)
{
	object owner;
	if ( !me->is_pet() )
		return 0;
	owner = me->get_owner();
	if ( gone_time(me->get("svd" )) < 10 )
	{
		send_user(owner,"%c%s",'!',sprintf("Tái sử dụng sau %d giây",10-gone_time(me->get("svd" )) ));
		return 0;	
	}
	me->add_hp( 2000 );
	me->set("svd", time() );	
    send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE );
	return 1;	
}