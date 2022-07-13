
// 自动生成：/make/equip/86b

inherit NECK;

// 函数：构造处理
void create()
{
        set_name("Sơ Học Giả Hạng Liên");
        set_picid_1(8600);
        set_picid_2(8600);
        set_unit("串");

        set_level(5);
        set_value(1);
        set_max_lasting(1899);
        set("cp%", 2);
        set("pp", 10);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Sơ Học Giả Hạng Liên";
}
