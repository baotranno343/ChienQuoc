inherit ITEM;

// 函数：构造处理
void create()
{
        set_name("忘情婆婆要的胭脂");
        set_picid_1(3550);
        set_picid_2(3550);
        set_unit("盒");
        set_value(10);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1); 
}

// 函数：获取描述
string get_desc() 
{ 
        return "忘情婆婆想要的能使她变漂亮的化妆品。";
}
