inherit ITEM;

// 函数：物品叠加上限

int get_item_color() { return 1; }
int get_item_value() { return 900; }
int get_item_value_2() { return 900; }
int is_chietxuat1() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Búa Thanh Đồng");
        set_picid_1(201);
        set_picid_2(201);
        set_value(100);
}

// 函数：获取描述
string get_desc()
{
        return "Loại đá cần thiết để chiết xuất trang bị, có thể chiết xuất ngoại công, nội công, ngoại kháng,nội kháng, khí huyết";
}
