
// 自动生成：/make/item/make35a

inherit ITEM;
    inherit COMBINED;

// 函数：叠加上限
//  int get_max_combined() { return 30; }

// 函数：原料类型
int get_stuff_type() { return 213; }

// 函数：构造处理
void create()
{
        set_name("碟子");
        set_picid_1(3506);
        set_picid_2(3506);
        set_unit("个");
        set_value(50);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "日常用品的一种"; 
}
