inherit ITEM;

// 函数：物品叠加上限

int get_item_color() { return 3; }
int get_item_value() { return 900; }
int get_item_value_2() { return 900; }

// 函数：构造处理
void create()
{
        set_name("Thiên Ấn Toàn Năng");
        set_picid_1(12047);
        set_picid_2(12047);
        set_value(10);
}

// 函数：获取描述
string get_desc()
{
        return "Dùng cho Pháp Bảo. Pháp bảo sẽ nhận được thêm sức mạnh từ ấn";
}
