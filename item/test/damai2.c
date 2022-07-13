inherit ITEM;
inherit COMBINED;

// 函数：物品叠加上限
int get_max_combined() { return 5000; }
int get_item_color() { return 1; }
int get_item_value() {return 900 ;}
int get_item_value_2() {return 900 ;}

// 函数：构造处理
void create()
{
        set_name("Đá Mài Lam Linh");
        set_picid_1(202);
        set_picid_2(202);
        set_value(10);
        set_amount(1);
}

// 函数：获取描述
string get_desc()
{
        return "Loại đá cần thiết để gỡ và hủy bảo thạch của trang bị. Có thể gỡ bảo thạch của Áo, Yêu đới và Giày.";
}
