
inherit ITEM;
inherit COMBINED;
int get_item_color() { return 1; }
// 函数：构造处理
void create()
{
    set_name("Vật Tư (2)");
    set_picid_1(8503);
    set_picid_2(8503);
    set_value(10);
    set_amount(1);
}

// 函数：获取描述
string get_desc()
{
    return "Vật sở hữu đặc biệt, thu thấp đủ 5 loại có thể đổi thưởng.";
}
