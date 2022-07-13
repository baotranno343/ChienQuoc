
// 自动生成：/make/item/make89b

inherit ITEM;

// 函数：宝石识别
int is_diamond() { return 1; }

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

// 函数：宝石属性
string get_diamond_type() { return "mp%"; }

// 函数：构造处理
void create()
{
        set_name("完美朱红晶石");
        set_picid_1(8954);
        set_picid_2(8954);
        set_unit("块");
        set_value(50000);
}

// 函数：获取描述
string get_desc() 
{ 
        return "［装备合成材料］增加法力百分比"; 
}
