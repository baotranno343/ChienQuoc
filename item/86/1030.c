
// 自动生成：/make/equip/86x

inherit NECK;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Trân Châu Hạng Liên");
        set_picid_1(8603);
        set_picid_2(8603);
        set_unit("串");

        set_level(30);
        set_value(6500);
        set_max_lasting(6699);
        set("ap", 4);
        set("pp", 4);
        set("spec.??%", 5);
        set("spec.X@%", 5);
        set("spec./%", 3);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Trân Châu Hạng Liên";
}
