#include <ansi.h>
#include <equip.h>
#include <effect.h>
inherit ITEM;
inherit USABLE;
inherit COMBINED;

int get_item_color() { return 2; }
int get_item_value() {return 50000 ;}
int get_item_value_2() {return 50000 ;}

// 函数：构造处理
void create()
{
        set_name("Thuốc Trùng Sinh");
		set_picid_1(9176);
        set_picid_2(9176);
		set_level(0);
        set_value(5000);
		set_amount(1);
}

// 函数：获取描述
string get_desc( object me ) 
{
		return "Viên thuốc dùng để Trùng Sinh. \nSau khi Trùng Sinh nhân vật sẽ chuyển về Vô Môn Phái và \nĐẳng cấp nhân vật vẫn sẽ được giữ nguyên. \nĐể sử dụng yêu cầu phải đạt cấp 60 trở lên. \nLưu ý : Vô Môn Phái không thể sử dụng !";
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object me,object gift ) 
{
	string arg;
		
	"cmd/user/doiphai"->main(me,arg);
	return 0;
}