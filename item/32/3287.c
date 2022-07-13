
// 自动生成：/make/item/make32b

inherit ITEM;
    inherit COMBINED;

// 函数：叠加上限
//  int get_max_combined() { return 30; }

// 函数：构造处理
void create()
{
        set_name("葡萄");
        set_picid_1(3287);
        set_picid_2(3287);
        set_unit("粒");
        set_value(20);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "水果的一种"; 
}
