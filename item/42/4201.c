
// 自动生成：/make/item/make30

inherit ITEM;
    inherit COMBINED;

// 函数，蓝色物品
int is_grey() {return 2;}

// 函数：叠加上限
//  int get_max_combined() { return 30; }

// 函数：原料类型
int get_stuff_type() { return 194; }

// 函数：构造处理
void create()
{
        set_name("Da Hổ");
        set_picid_1(3453);
        set_picid_2(3453);
        set_unit("块");
        set_value(100);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Là một vật khiến con hổ chống lạnh"; 
}
