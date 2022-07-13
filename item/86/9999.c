
// 自动生成：/make/equip/86b

inherit NECK;
int get_item_color() { return 1; }
// 函数：构造处理
void create()
{
        set_name("Tân Thủ Hạng Liên");
        set_picid_1(8608);
        set_picid_2(8608);
        set_unit("串");

        set_level(0);
        set_value(80);
        set_max_lasting(2599);
//        set("cp%", 5);
        set("ap", 15);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tân Thủ Hạng Liên";
}
