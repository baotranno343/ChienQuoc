
// 自动生成：/make/equip/86b

inherit NECK;

// 函数：构造处理
void create()
{
        set_name("Thanh Đồng Hạng Liên");
        set_picid_1(8602);
        set_picid_2(8602);
        set_unit("串");

        set_level(20);
        set_value(2200);
        set_max_lasting(3999);
        set("cp%", 7);
        set("pp", 20);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thanh Đồng Hạng Liên";
}
