
inherit BOOTS;

// 函数：构造处理
void create()
{
        set_name("学徒鞋");
        set_picid_1(8802);
        set_picid_2(8802);
        set_unit("双");

        set_level(0);
        set_value(10);
        set_max_lasting(2199);
        set("dp", 2);
        set("pp", 2);
        set("X@%", 5);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "学徒鞋";
}
