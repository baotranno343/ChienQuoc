
// 自动生成：/make/item/make09

#include <equip.h>
inherit FAMILY_EQUIP;

int get_item_color() { return 1; }
// 函数：构造处理
void create()
{
        set_name("Âm dương bảo kính");
        set_picid_1(905);
        set_picid_2(905);
        set_unit("面");
        set_family_name("Mao Sơn");      
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
	return "Là tín vật của môn phái Mao sơn, \n Tương truyền là vật phẩm của Thái Thượng Lão Quân dùng để quan sát âm dương luân hồi. \n Ấn phím phải có thể trực tiếp chuyển về Mao sơn. \n Thời gian: 1phút \n Mỗi lần sử dụng trả 50 lượng.";
}