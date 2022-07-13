
// 自动生成：/make/item/make89b

inherit ITEM;

// 函数：宝石识别
int is_diamond() { return 2; }

int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Hoàn Mỹ Bảo Thạch Quặng Mỏ");
        set_picid_1(4111);
        set_picid_2(4111);
        set_unit("块");
        set_value(5000);
        set_level(120);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Một loại nguyên liệu bảo thạch phân giải cung cấp cho Điêu Khắc"; 
}
