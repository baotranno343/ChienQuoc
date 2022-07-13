
inherit GOOD;
is_thuongnhan() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Bánh quả hồng");
        set_picid_1(9941);
        set_picid_2(9941);
        set_unit("包");
        set_buy_price(100);
        set_buy_range(200);
        set_sell_price(120);
        set_sell_range(380);

        set_no_drop(1);
        set_no_get(1);
        set_no_give(1);
}

// 函数：获取国名
string get_city_name() { return "Ngụy Quốc"; }

// 函数：获取描述
string get_desc()
{
        return "［thương phẩm］ đặc sản của Nguỵ Quốc";
}
