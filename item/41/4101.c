
// 自动生成：/make/item/make30

inherit ITEM;
    inherit COMBINED;

// 函数：叠加上限
//  int get_max_combined() { return 30; }

// 函数：原料类型
int get_stuff_type() { return 238; }

// 函数：构造处理
void create()
{
        set_name("Nhung Cầu");
        set_picid_1(4101);
        set_picid_2(4101);
        set_unit("团");
        set_value(20);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Là một vật thiêu từ lông tơ mà thành"; 
}
