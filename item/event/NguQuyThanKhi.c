
inherit ITEM;
inherit COMBINED;

// 函数：物品叠加上限
int get_max_combined() { return 5000; }
int get_item_color() {return 2 ;}
// 函数：构造处理
void create()
{
        set_name( "Ngũ Quy Thần Khí" );
		set_picid_1(9811);
        set_picid_2(9811);
        set_value(10);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Là một cái Vòng Đá ẩn chứa Thần Khí hợp thành từ 5 món Thần khí thượng cổ \nKính Côn Lôn \nĐá Nữ Oa \nĐàn Phục Hy \nĐỉnh Thần Nông \nẤn Không Động";
}
