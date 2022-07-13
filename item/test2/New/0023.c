#include <item.h>
#include <ansi.h>
#include <effect.h>
#include <skill.h>

inherit COMBINED;
inherit ITEM;

int get_item_value() {return 15 ;}
int get_item_value_2() {return 15 ;}
int get_item_color() {return 1 ;}

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_PET; }
//宠物物品
int is_pet_item() { return 1;}
// 函数：构造处理
void create()
{
        set_name("Sủng Vật Pháp Thạch");
        set_picid_1(4237);
        set_picid_2(4237);
        set_value(2);
        set_amount(1);
        set_record(1);
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "Pháp thạch chuyên dụng cho Bảo Thú, sau khi sử dụng, mỗi 2 giây hồi phục 100 Pháp Lực, kéo dài 60 trong phút."; 
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object item) 
{
	object owner;
	if ( !who->is_pet() )
		return 0;
	owner = who->get_owner();
	if ( get_effect(who, EFFECT_FALISHI_MP) )
	{
		send_user( owner, "%c%c%w%s", ':', 3, 0,sprintf("Trên người bảo thú đã có sử dụng vật phẩm này， bạn muốn sử dụng đè lên không ?\n"ESC"Chấp nhận\nuse ! %x#\n"ESC"Hủy bỏ",getoid(item))); 
		return 0;
	}
	set_effect_2(who, EFFECT_FALISHI_MP,  1800, 2);
	who->set_save("stone_hp", 100);
	send_user( who, "%c%w%w%c", 0x81, 2, 3600, EFFECT_GOOD );
	return 1;
}

void into_effect(object me)
{
	me->add_hp(me->get_save("stone_mp"));	
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE );
	if (get_effect_3(me, EFFECT_FALISHI_MP)==0) me->set_save("stone_mp", 0);
}
// 函数：使用效果
int confirm_use( object me ) { return __FILE__ ->confirm_use_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int confirm_use_callout( object who, object item )
{
	set_effect_2(who, EFFECT_FALISHI_MP,  1800, 2);
	who->set_save("stone_mp", 100);
	send_user( who, "%c%w%w%c", 0x81, 2, 3600, EFFECT_GOOD );
	send_user( who, "%c%w%s", 0x82, 2, CHAR_CHAR_D->get_loop_desc(who, 2) );
	return 1;
}