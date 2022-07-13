
inherit GOOD;
is_thuongnhan() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Cỏ linh chi");
        set_picid_1(9923);
        set_picid_2(9923);
        set_unit("包");
        set_buy_price(1200);
        set_buy_range(300);
        set_sell_price(1100);
        set_sell_range(900);

        set_no_drop(1);
        set_no_get(1);
        set_no_give(1);
}

// 函数：获取国名
string get_city_name() { return "Hàn Quốc"; }

// 函数：获取描述
string get_desc()
{
        return "［thương phẩm］ đặc sản của Hàn Quốc";
}
