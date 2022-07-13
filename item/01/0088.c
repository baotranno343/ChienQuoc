
inherit BOOTS;

// 函数：构造处理
void create()
{
        set_name("金丝履");
        set_picid_1(8812);
        set_picid_2(8812);
        set_unit("双");

        set_level(0);
        set_value(0);
        set_max_lasting(1099);
        set("dp", 3);
        set("pp", 3);
        set("sp", 15);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "金丝履";
}
