
// 自动生成：/make/item/make33

inherit ITEM;
    inherit COMBINED;

// 函数：叠加上限
//  int get_max_combined() { return 30; }

// 函数：小吃识别
int is_snack() { return 1; }

// 函数：构造处理
void create()
{
        set_name("臭豆腐");
        set_picid_1(3322);
        set_picid_2(3322);
        set_unit("块");
        set_value(20);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "小吃的一种"; 
}
