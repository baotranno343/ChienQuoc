
// 自动生成：/make/item/make30

inherit ITEM;
    inherit COMBINED;

// 函数：获取装备颜色：灰色
int get_item_color() { return 0; }

// 函数：叠加上限
//  int get_max_combined() { return 30; }

// 函数：构造处理
void create()
{
        set_name("Phá Tổn Giáp");
        set_picid_1(4014);
        set_picid_2(4014);
        set_value(93);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Áo giáp đã bị rách nát, vật phẩm dùng để bán"; 
}
