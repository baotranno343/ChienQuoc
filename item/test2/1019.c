
inherit ITEM;
inherit COMBINED;

// 函数：物品叠加上限
int get_max_combined() { return 5000; }
int get_item_color() {return 2 ;}
// 函数：构造处理
void create()
{
        set_name( "Mảnh ghép công thức Huyết Binh" );
        set_picid_1(12268);
        set_picid_2(12268);
        set_value(10);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Sau khi thu thập đủ 199 mảnh, đến tìm gặp Trâu Diễn Đại Sư để tiến hành hợp thành Huyết dục thần binh trong truyền thuyết.";
}
