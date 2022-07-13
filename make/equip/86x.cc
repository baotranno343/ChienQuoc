
// 自动生成：/make/equip/86x

inherit NECK;

// 函数：适用门派
int get_family() { return 1; }

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
        set("ap", %d);
        set("pp", %d);
        set("spec.??%%", %d);
        set("spec.X@%%", %d);
        set("spec./%%", %d);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "%s";
}
