
// 自动生成：/make/item/make38a

inherit ITEM;
    inherit COMBINED;

// 函数：叠加上限
    int get_max_combined() { return 5; }

// 函数：构造处理
void create()
{
        set_name("《大学》");
        set_picid_1(3801);
        set_picid_2(3801);
        set_unit("本");
        set_value(2);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "书籍的一种";
}
