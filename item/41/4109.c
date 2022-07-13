
// 自动生成：/make/item/make30

inherit ITEM;
    inherit COMBINED;

// 函数：叠加上限
//  int get_max_combined() { return 30; }

// 函数：原料类型
int get_stuff_type() { return 320; }

// 函数：构造处理
void create()
{
        set_name("Lam Ma Lệ");
        set_picid_1(8915);
        set_picid_2(8915);
        set_unit("个");
        set_value(400);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Tương truyền là hình thành từ những giọt lệ"; 
}
