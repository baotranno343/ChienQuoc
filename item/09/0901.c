
// 自动生成：/make/item/make09

#include <equip.h>
inherit FAMILY_EQUIP;

int get_item_color() { return 1; }
// 函数：构造处理
void create()
{
        set_name("Đào Mộc Tâm");
        set_picid_1(901);
        set_picid_2(901);
        set_unit("个");
        set_family_name("Đào Hoa Nguyên");      
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
	return "Tín vật của môn phái Đào Hoa Nguyên, \n Tương truyền là dùng cây đào ngàn năm của Đào Hoa Đảo khắc thành. \n Ấn phím phải có thể trực tiếp chuyển về. \n Thời gian: 1phút \n Mỗi lần sử dụng trả 50 lượng.";
}