#include <ansi.h>
#include <equip.h>
#include <effect.h>
inherit ITEM;
inherit USABLE;

int get_item_color() { return 2; }
int get_item_value() {return 500 ;}
int get_item_value_2() {return 500 ;}

// 函数：构造处理
void create()
{
        set_name("Túi Nguyên Liệu Thần Binh");
		set_picid_1(3105);
        set_picid_2(3105);
		set_level(0);
        set_value(5000);
		set_no_give(0);		
        set_no_sell(1);
		set_no_drop(0);
}

// 函数：获取描述
string get_desc( object me ) 
{
		return "Sử dụng sẽ tùy chọn những loại vũ khí nguyên liệu cấp 75.\n";
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object me,object gift ) 
{
	string arg;
		
	"cmd/user/vktk2"->main(me,arg);
	return 0;
}