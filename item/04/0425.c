inherit ITEM;

// 函数：构造处理
void create()
{
        set_name("巧克力豆");
        set_picid_1(9971);
        set_picid_2(9971);
        set_unit("粒");
        set_value(10);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1); 
}

// 函数：获取描述
string get_desc() 
{ 
        return "上好的巧克力豆，可以用来做巧克力。";
}
