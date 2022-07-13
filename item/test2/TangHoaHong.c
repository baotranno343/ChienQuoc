
inherit ITEM;
inherit COMBINED;

// 函数：物品叠加上限
int get_max_combined() { return 10000; }
int get_item_color() {return 2 ;}
// 函数：构造处理
void create()
{
        set_name( "Tàng Hoa Hồng" );
        set_picid_1(3005);
        set_picid_2(3005);
        set_value(10);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Sau khi thu thập đủ 100 cái có thể đến \nSứ Giả Hoạt Động để đổi 1 đoá Hoa Hồng.";
}
