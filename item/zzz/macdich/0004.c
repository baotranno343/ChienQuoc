#include <ansi.h>
#include <effect.h>
#include <skill.h>

inherit COMBINED;
inherit ITEM;

int get_item_value() {return 450 ;}
int get_item_value_2() {return 400 ;}
int get_item_number() {return 10001004 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name("Đại Pháp Lực Thạch");
        set_picid_1(4233);
        set_picid_2(4233);
        set_value(80);
	//	set_save("knb",18);
		set_no_give(1);
        set_amount(1);
        set_record(1);
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "Một loại tinh thạch màu xanh kỳ dị, khi sử dụng sẽ hồi phục 100 điểm Pháp Lực sau mỗi 2 giây. Tác dụng duy trì liên tục trong 60 phút."; 
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object item) 
{
	if ( get_effect(who, EFFECT_FALISHI_MP) )
	{
		send_user( who, "%c%c%w%s", ':', 3, 0,sprintf("Bạn vẫn còn hiệu quả Pháp Lực Thạch, bạn muốn sử dụng đè lên không ?\n"ESC"Xác nhận\nuse ! %x#\n"ESC"Huỷ bỏ",getoid(item))); 
		return 0;
	}
	set_effect_2(who, EFFECT_FALISHI_MP,  1800, 2);
	who->set_save("stone_mp", 100);
	send_user( who, "%c%w%w%c", 0x81, 4, 3600, EFFECT_GOOD );
	return 1;
}

void into_effect(object me)
{
	me->add_mp(me->get_save("stone_mp"));	
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE );
	if (get_effect_3(me, EFFECT_FALISHI_MP)==0) me->set_save("stone_mp", 0);
}

string get_loop_desc(object me)
{
	if (me->get_save("stone_mp")==40)
		return sprintf("Tiểu Pháp Lực Thạch:\n    Mỗi 2 giây hồi phục %d Pháp Lực", me->get_save("stone_mp"));
	else
		return sprintf("Đại Pháp Lực Thạch:\n    Mỗi 2 giây hồi phục %d Pháp Lực", me->get_save("stone_mp"));
}
// 函数：使用效果
int confirm_use( object me ) { return __FILE__ ->confirm_use_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int confirm_use_callout( object who, object item )
{
	set_effect_2(who, EFFECT_FALISHI_MP,  1800, 2);
	who->set_save("stone_mp", 100);
	send_user( who, "%c%w%w%c", 0x81, 4, 3600, EFFECT_GOOD );
	send_user( who, "%c%w%s", 0x82, 4, CHAR_CHAR_D->get_loop_desc(who, 4) );
	return 1;
}