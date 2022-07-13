
inherit ITEM;
inherit COMBINED;

int get_item_color() {return 2 ;}
// 函数：构造处理
void create()
{
        set_name( "Ác Quỷ(vương)" );
        set_picid_1(8114);
        set_picid_2(8114);
        set_value(10);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Sau khi thu thập đủ số lượng có thể đến Tiên Cô Thiên Sứ \nTiểu Long Nữ để đổi những phần thưởng quý giá.";
}
