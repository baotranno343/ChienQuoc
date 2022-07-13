
inherit ITEM;
inherit COMBINED;

// 函数：物品叠加上限
int get_max_combined() { return 5000; }
int get_item_color() {return 2 ;}
// 函数：构造处理
void create()
{
        set_name( "Kính Côn Lôn" );
		set_picid_1(3564);
        set_picid_2(3564);
        set_value(10);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Một trong năm món Thần khí thượng cổ";
}
