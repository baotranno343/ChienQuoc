
// 自动生成：/make/equip/86b

inherit NECK;

// 函数：构造处理
void create()
{
        set_name("%s");
        set_picid_1(%d);
        set_picid_2(%d);
        set_unit("%s");

        set_level(%d);
        set_value(%d);
        set_max_lasting(%d);
        set("cp%%", %d);
        set("pp", %d);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "%s";
}
