
// 自动生成：/make/item/make89b

inherit ITEM;

// 函数：宝石识别
int is_diamond() { return 2; }

int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Liệt Chất Bảo Thạch Khoáng");
        set_picid_1(8900);
        set_picid_2(8900);
        set_unit("块");
        set_value(2000);
        set_level(20);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Một loại nguyên liệu bảo thạch phân giải cung cấp cho Điêu Khắc"; 
}
