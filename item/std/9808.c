
// 自动生成：/make/item/make98a

inherit ITEM;
inherit COMBINED;

int get_max_combined() { return 10000; }

// 函数：构造处理
void create()
{
        set_name("Chu Thiên Tâm Pháp");
        set_picid_1(9808);
        set_picid_2(9808);
        set_unit("本");
        set_value(2000);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Bộ sách ghi lại tâm pháp Chu Thiên Tụng Văn \nThục Sơn lợi dụng sách này để thi triển Đại Chu Thiên。"; 
}
