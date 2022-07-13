
inherit GOOD;
is_thuongnhan() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Muối biển");
        set_picid_1(9911);
        set_picid_2(9911);
        set_unit("包");
        set_buy_price(150);
        set_buy_range(150);
        set_sell_price(250);
        set_sell_range(350);

        set_no_drop(1);
        set_no_get(1);
        set_no_give(1);
}

// 函数：获取国名
string get_city_name() { return "Tề Quốc"; }

// 函数：获取描述
string get_desc()
{
        return "[thương phẩm] đặc sản của Tề Quốc";
}
