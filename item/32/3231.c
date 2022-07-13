
// 自动生成：/make/item/make32a

inherit ITEM;
    inherit COMBINED;

// 函数：叠加上限
//  int get_max_combined() { return 30; }

int get_max_combined() { return 10000; }

// 函数：原料类型
int get_stuff_type() { return 160; }

// 函数：构造处理
void create()
{
        set_name("Đậu Nành");
        set_picid_1(3231);
        set_picid_2(3231);
        set_unit("颗");
        set_value(400);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Một loại sản phảm nông nghiệp"; 
}
