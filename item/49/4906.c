
// 自动生成：/make/item/make49

inherit ITEM;
    inherit COMBINED;

// 函数：叠加上限
//  int get_max_combined() { return 30; }

// 函数：构造处理
void create()
{
        set_name("冰块");
        set_picid_1(4906);
        set_picid_2(4906);
        set_unit("块");
        set_value(40);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "冰块";
}
