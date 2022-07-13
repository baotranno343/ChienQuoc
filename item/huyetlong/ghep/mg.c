
inherit ITEM;
inherit COMBINED;

// 函数：物品叠加上限
int get_max_combined() { return 10000; }
int get_item_color() {return 2 ;}
// 函数：构造处理
void create()
{
        set_name( "Chiếu Thư Thiên Tử" );
        set_picid_1(3855);
        set_picid_2(3855);
        set_value(10);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Sau khi thu thập đủ có thể đến \nTiên Tri Đàn để hợp thành trang bị Huyết Long.";
}
