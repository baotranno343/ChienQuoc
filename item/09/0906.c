
// 自动生成：/make/item/make09

#include <equip.h>
inherit FAMILY_EQUIP;

int get_item_color() { return 1; }
// 函数：构造处理
void create()
{
        set_name("Như Ý Ngọc Bài");
        set_picid_1(906);
        set_picid_2(906);
        set_unit("个");
        set_family_name("Côn Luân");      
        set_max_lasting(1099);
        set_lasting(1099);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);          

}

// 函数：获取描述
string get_desc() 
{ 
        return sprintf("Tín Vật Môn Phái Cấp %d ",get_item_level()); 
}

string get_family_desc() 
{ 
	return "Tín vật của phái Côn Luân, \n Dùng Ngọc Như Ý của Thiên Tử ban thưởng điêu khắc. \n Ấn phím phải có thể trực tiếp chuyển về Côn Luân Sơn. \n Thời gian: 1phút \n Mỗi lần sử dụng trả 50 lượng.";
}