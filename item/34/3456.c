
// 自动生成：/make/item/make34b

inherit ITEM;
    inherit COMBINED;

// 函数：叠加上限
//  int get_max_combined() { return 30; }

// 函数：构造处理
void create()
{
        set_name("法笔");
        set_picid_1(3456);
        set_picid_2(3456);
        set_unit("支");
        set_value(50);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "祭拜用品的一种"; 
}
