
// 自动生成：/make/item/make35a

inherit ITEM;
    inherit COMBINED;

// 函数：叠加上限
//  int get_max_combined() { return 30; }

// 函数：构造处理
void create()
{
        set_name("菜刀");
        set_picid_1(3512);
        set_picid_2(3512);
        set_unit("把");
        set_value(50);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "日常用品的一种"; 
}
