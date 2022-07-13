#include <ansi.h>
#include <effect.h>
#include <skill.h>

inherit COMBINED;
inherit ITEM;

int get_item_value() {return 225 ;}
int get_item_value_2() {return 200 ;}
int get_item_number() {return 10001001 ;}
int get_item_color() {return 1 ;}


// 函数：构造处理
void create()
{
        set_name("Tiểu Huyết Thạch");
        set_picid_1(4234);
        set_picid_2(4234);
        set_value(50);
		set_no_give(1);
        set_amount(1);
        set_record(1);
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "Một loại Hồng Sắc Tinh Thạch kỳ lạ, khi sử dụng sẽ liên tục hồi phục 40 điểm Khí Huyết sau mỗi 2 giây. Hiệu quả kéo dài trong 60 phút."; 
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object item) 
{
	if ( get_effect(who, EFFECT_XUESHI_HP) )
	{
		send_user( who, "%c%c%w%s", ':', 3, 0,sprintf("Bạn xác nhận muốn sử dụng đè lên không ?\n"ESC"Chấp nhận\nuse ! %x#\n"ESC"Hủy bỏ",getoid(item))); 
		return 0;
	}
	set_effect_2(who, EFFECT_XUESHI_HP,  1800, 2);
	who->set_save("stone_hp", 40);
	send_user( who, "%c%w%w%c", 0x81, 2, 3600, EFFECT_GOOD );
	return 1;
}

void into_effect(object me)
{
	me->add_hp(me->get_save("stone_hp"));	
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE );
	if (get_effect_3(me, EFFECT_XUESHI_HP)==0) me->set_save("stone_hp", 0);
}
// 函数：使用效果
int confirm_use( object me ) { return __FILE__ ->confirm_use_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int confirm_use_callout( object who, object item )
{
	set_effect_2(who, EFFECT_XUESHI_HP,  1800, 2);
	who->set_save("stone_hp", 40);
	send_user( who, "%c%w%w%c", 0x81, 2, 3600, EFFECT_GOOD );
	send_user( who, "%c%w%s", 0x82, 2, CHAR_CHAR_D->get_loop_desc(who, 2) );
	return 1;
}