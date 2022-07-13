
inherit ITEM;

// 函数：构造处理
void create()
{
        set_name("Thiên Ân Lệnh");
        set_picid_1(0096);
        set_picid_2(0096);
        set_unit("块");
        set_value(50);
        set_no_give(1);
        set_no_sell(1); 
}


int get_item_color() {return 2;}

// 函数：获取描述
string get_desc() 
{ 
        return "Tín vật học kĩ năng cường hoá môn phái。\nCó vật phẩm này có thể học kĩ năng cường hoá môn phái。";
}
