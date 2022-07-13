#include <ansi.h>
#include <effect.h>
#include <skill.h>

inherit COMBINED;
inherit ITEM;

int get_item_value() {return 450 ;}
int get_item_value_2() {return 400 ;}
int get_item_number() {return 10001002 ;}
int get_item_color() {return 1 ;}


// 函数：构造处理
void create()
{
        set_name("大血石");
        set_picid_1(4235);
        set_picid_2(4235);
        set_value(50);
        set_amount(1);
        set_record(1);
        // -- 与原装备相比增加绑定属性
        set_no_give(1);
        set_no_sell(1);
        //        
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "一种奇异的红色晶石，使用后每2秒可恢复90点气血值。效果持续60分钟。"; 
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object item) 
{
	if ( get_effect(who, EFFECT_XUESHI_HP) )
	{
		send_user( who, "%c%c%w%s", ':', 3, 0,sprintf("你身上已经有一个血石在产生作用，你确定要覆盖它的效果吗？\n"ESC"确定\nuse ! %x#\n"ESC"取消",getoid(item))); 
		return 0;
	}
	set_effect_2(who, EFFECT_XUESHI_HP,  1800, 2);
	who->set_save("stone_hp", 90);
	send_user( who, "%c%w%w%c", 0x81, 2, 3600, EFFECT_GOOD );
	return 1;
}

void into_effect(object me)
{
	me->add_hp(me->get_save("stone_hp"));	
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE );
	if (get_effect_3(me, EFFECT_XUESHI_HP)==0) me->set_save("stone_hp", 40);
}

string get_loop_desc(object me)
{
	if (me->get_save("stone_hp")==40)
		return sprintf("小血石：\n    使用后每2秒可恢复%d点气血值", me->get_save("stone_hp"));
	else
		return sprintf("大血石：\n    使用后每2秒可恢复%d点气血值", me->get_save("stone_hp"));
}
// 函数：使用效果
int confirm_use( object me ) { return __FILE__ ->confirm_use_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int confirm_use_callout( object who, object item )
{
	set_effect_2(who, EFFECT_XUESHI_HP,  1800, 2);
	who->set_save("stone_hp", 90);
	send_user( who, "%c%w%w%c", 0x81, 2, 3600, EFFECT_GOOD );
	send_user( who, "%c%w%s", 0x82, 2, CHAR_CHAR_D->get_loop_desc(who, 2) );
	return 1;
}