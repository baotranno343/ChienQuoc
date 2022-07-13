#include <equip.h>
#include <ansi.h>
inherit USABLE;
inherit ITEM;

int get_item_value() {return 10 ;}
int get_item_value_2() {return 10 ;}
//int get_item_number() {return 10001070 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name("Hạt Mè Khai Môn");
        set_picid_1(3234);
        set_picid_2(3234);
        set_value(40);
	//	set_save("knb2",10);
}

// 函数：获取描述
string get_desc()
{
        return "Là loại hạt mè rất khó tìm, thời gian nở hoa là vào cuối mùa, \nCó thể bước vào khu vực có đăng cấp thấp hơn đẳng cấp \ncủa mình mà không chịu sự giới hạn của Chiến Quốc Trận. \nMỗi lần bước vào Chiến Quốc Trận có đẳng cấp thấp \nhơn của mình thì tự động mất đi một viên Hạt Mè Khai Môn.";
}
