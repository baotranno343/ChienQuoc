inherit ITEM;

// 函数：构造处理
void create()
{
        set_name("月老给的包裹");
        set_picid_1(4980);
        set_picid_2(4980);
        set_unit("个");
        set_value(10);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1); 
}

// 函数：获取描述
string get_desc() 
{ 
        return "沉重的包裹，里面似乎有好东西。";
}
