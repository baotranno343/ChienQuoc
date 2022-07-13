
// 自动生成：/make/equip/87b

inherit WAIST;
int get_item_color() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Yêu Đới");
        set_picid_1(8700);
        set_picid_2(8700);
        set_unit("条");

        set_level(14);
        set_value(100);
        set_max_lasting(2499);
        set("hp+", 25);
        set("mp+", 25);
	set_item_color(1);
        setup();
}

// 函数：获取描述
string get_desc()
{
        return "能够增强初学者能力的腰带";
}
