inherit ITEM;

// 函数：构造处理
void create()
{
        set_name("神秘的种子");
        set_picid_1(3234);
        set_picid_2(3234);
        set_unit("只");
        set_value(10);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1); 
}

// 函数：获取描述
string get_desc() 
{ 
        return "散发出淡淡的清香，似乎可以吃。";
}
