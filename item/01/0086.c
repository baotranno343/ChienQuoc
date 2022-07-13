
inherit NECK;

// 函数：构造处理
void create()
{
        set_name("传说项链");
        set_picid_1(8613);
        set_picid_2(8613);
        set_unit("串");

        set_level(0);
        set_value(0);
        set_max_lasting(1099);
        set("hp", 30);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "传说项链";
}
