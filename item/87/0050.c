
// 自动生成：/make/equip/87b

inherit WAIST;

// 函数：构造处理
void create()
{
        set_name("Bách Luyện Đới");
        set_picid_1(8705);
        set_picid_2(8705);
        set_unit("条");

        set_level(50);
        set_value(2300);
        set_max_lasting(7299);
        set("dp", 7);
        set("pp", 7);
        set("hp%", 10);
        set("mp%", 10);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Bách Luyện Đới";
}
