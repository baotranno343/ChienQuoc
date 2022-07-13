
inherit WAIST;

// 函数：构造处理
void create()
{
        set_name("金丝腰带");
        set_picid_1(8713);
        set_picid_2(8713);
        set_unit("条");

        set_level(0);
        set_value(0);
        set_max_lasting(1099);
        set("dp", 8);
        set("pp", 6);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "金丝腰带";
}
