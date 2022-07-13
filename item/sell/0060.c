
#include <effect.h>
#include <skill.h>
#include <ansi.h>

inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

int get_item_value() {return 150 ;}
int get_item_value_2() {return 150 ;}
//int get_item_number() {return 10001075 ;}
int get_item_color() {return 2 ;}

// 函数：构造处理
void create()
{
        set_name( "Nhân Sâm Vương" );
        set_picid_1(9943);
        set_picid_2(9943);
        set_unit( "粒" );
        set_value(800);
        set_amount(1);
        set_record(1);
        set("effect", 2000);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Tương truyền đây là loại nhân sâm do một người đào sâm lâu năm đào được trên Trường Bạch Sơn, có công hiệu sinh ra cơ thịt, xương cốt. \n Liên tục trong 1 giờ làm cho khí huyết của người chơi tăng 2000 điểm. \n Thời gian làm giảm nhiệt độ là 2 giây.";
}

string get_short()
{
	return "Tương truyền đây là loại nhân sâm do một người đào sâm lâu năm đào được trên Trường Bạch Sơn, có công hiệu sinh ra cơ thịt, xương cốt. \n Liên tục trong 1 giờ làm cho khí huyết của người chơi tăng 2000 điểm. \n Thời gian làm giảm nhiệt độ là 2 giây.";
}

// 函数：使用效果
int get_use_effect( object me ) { return "/item/sell/0006"->get_use_effect_callout(me,this_object()); }


// 函数：使用效果
int confirm_use( object me ) { return "/item/sell/0006" ->confirm_use_callout( me, this_object() ); }
