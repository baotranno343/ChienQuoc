
inherit ITEM;

int get_item_color() { return 1; }
// 函数：构造处理
void create()
{
        set_name( "Góc Dưới Tàng Bảo Đồ" );
        set_picid_1(8003);
        set_picid_2(8003);
        set_unit( "张" );
        set_value(100);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Thông qua nó có thể tìm được bảo tàng"; 
}
