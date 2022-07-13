
// 自动生成：/make/item/make31b

inherit ITEM;
    inherit COMBINED;

// 函数：叠加上限
//  int get_max_combined() { return 30; }

// 函数：构造处理
void create()
{
        set_name("云雾茶叶");
        set_picid_1(3115);
        set_picid_2(3115);
        set_unit("片");
        set_value(20);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "茶叶的一种"; 
}
