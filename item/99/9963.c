
inherit GOOD;
is_thuongnhan() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Hoàng kim");
        set_picid_1(9963);
        set_picid_2(9963);
        set_unit("包");
        set_buy_price(2000);
        set_buy_range(800);
        set_sell_price(2200);
        set_sell_range(1800);

        set_no_drop(1);
        set_no_get(1);
        set_no_give(1);
}

// 函数：获取国名
string get_city_name() { return "Sở Quốc"; }

// 函数：获取描述
string get_desc()
{
        return "［thương phẩm］ dặc sản của Sở Quốc";
}
