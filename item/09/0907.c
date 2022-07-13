
// 自动生成：/make/item/make09

#include <equip.h>
inherit FAMILY_EQUIP;

int get_item_color() { return 1; }
// 函数：构造处理
void create()
{
        set_name("Vân Môn Kỳ");
        set_picid_1(907);
        set_picid_2(907);
        set_unit("面");
        set_family_name("Vân Mộng Cốc");      
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
	return "Tín vật của môn phái Vân Mộng Cốc, \n Vân Mộng Tổ Sư sử dụng cờ bằng Phép Thuật của bản môn . \n Ấn phím phải có thể trực tiếp chuyển về Vân Mộng Cốc. \n Thời gian: 1phút \n Mỗi lần sử dụng trả 50 lượng.";
}