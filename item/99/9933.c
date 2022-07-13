
inherit GOOD;
is_thuongnhan() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Ngọc điêu");
        set_picid_1(9933);
        set_picid_2(9933);
        set_unit("包");
        set_buy_price(2000);
        set_buy_range(1000);
        set_sell_price(2500);
        set_sell_range(2000);

        set_no_drop(1);
        set_no_get(1);
        set_no_give(1);
}

// 函数：获取国名
string get_city_name() { return "Triệu Quốc"; }

// 函数：获取描述
string get_desc()
{
        return "［thương phẩm］ đặc sản của Triệu Quốc";
}
