#include <ansi.h>
#include <effect.h>
#include <skill.h>

inherit COMBINED;
inherit ITEM;

int get_item_value() {return 225 ;}
int get_item_value_2() {return 200 ;}
int get_item_number() {return 10001003 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name("Tiểu Pháp Lực Thạch");
        set_picid_1(4232);
        set_picid_2(4232);
        set_value(80);
		set_no_give(1);
        set_amount(1);
        set_record(1);
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "Một loại Lam Sắc Tinh Thạch kỳ lạ, khi sử dụng sẽ liên tục hồi phục 40 điểm Pháp Lực sau mỗi 2 giây. Hiệu quả kéo dài trong 60 phút."; 
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object item) 
{
	if ( get_effect(who, EFFECT_FALISHI_MP) )
	{
		send_user( who, "%c%c%w%s", ':', 3, 0,sprintf("Bạn xác dụng muốn sử dụng đè lên không ?\n"ESC"Chấp nhận\nuse ! %x#\n"ESC"Hủy bỏ",getoid(item))); 
		return 0;
	}
	set_effect_2(who, EFFECT_FALISHI_MP,  1800, 2);
	who->set_save("stone_mp", 40);
	send_user( who, "%c%w%w%c", 0x81, 4, 3600, EFFECT_GOOD );
	return 1;
}

void into_effect(object me)
{
	me->add_mp(me->get_save("stone_mp"));	
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE );
	if (get_effect_3(me, EFFECT_FALISHI_MP)==0) me->set_save("stone_mp", 0);
}
// 函数：使用效果
int confirm_use( object me ) { return __FILE__ ->confirm_use_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int confirm_use_callout( object who, object item )
{
	set_effect_2(who, EFFECT_FALISHI_MP,  1800, 2);
	who->set_save("stone_mp", 40);
	send_user( who, "%c%w%w%c", 0x81, 4, 3600, EFFECT_GOOD );
	send_user( who, "%c%w%s", 0x82, 4, CHAR_CHAR_D->get_loop_desc(who, 4) );
	return 1;
}
