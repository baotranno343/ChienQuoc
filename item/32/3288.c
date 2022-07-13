
// 自动生成：/make/item/make32b

inherit ITEM;
    inherit COMBINED;

// 函数：叠加上限
//  int get_max_combined() { return 30; }

// 函数：构造处理
void create()
{
        set_name("龙眼");
        set_picid_1(3288);
        set_picid_2(3288);
        set_unit("颗");
        set_value(20);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "水果的一种"; 
}
