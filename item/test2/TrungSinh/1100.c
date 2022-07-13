#include <ansi.h>
#include <equip.h>
#include <effect.h>
inherit ITEM;
inherit USABLE;
inherit COMBINED;

int get_item_color() { return 2; }
int get_item_value() {return 1955 ;}
int get_item_value_2() {return 1955 ;}

// 函数：构造处理
void create()
{
        set_name("Thuốc Chuyển Giới");
		set_picid_1(9166);
        set_picid_2(9166);
		set_level(0);
        set_value(5000);
	//	set_save("knb",1955);
		set_amount(1);
}

// 函数：获取描述
string get_desc( object me ) 
{
		return "Viên thuốc dùng để Chuyển giới. \nNghe nói đây là viên thuốc được sản xuất từ Thái Lan với hiệu quả cao. \nSau khi sử dụng Nhân vật sẽ chuyển đổi sang giới tính khác. \nYêu cầu đẳng cấp sử dụng : 20 cấp.";
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object me,object gift ) 
{
	string arg;
		
	"cmd/user/doigt"->main(me,arg);
	return 0;
}