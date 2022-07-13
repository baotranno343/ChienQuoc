inherit ITEM;

// 函数：物品叠加上限

int get_item_color() { return 2; }
int get_item_value() { return 500; }
int get_item_value_2() { return 500; }

// 函数：构造处理
void create()
{
        set_name("Phá Thiên Lệnh");
        set_picid_1(4984);
        set_picid_2(4984);
        set_value(10);
}

// 函数：获取描述
string get_desc()
{
        return "Lệnh bài đặc biệt có thể được thêm quyền hạn tham gia phó bản Phá thiên tháp thêm 1 lần nữa trong ngày.";
}
