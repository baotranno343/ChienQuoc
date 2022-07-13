
inherit ITEM;
inherit "/inh/item/task2";

// 函数：构造处理
void create()
{
        set_name("Lá Trà");
        set_picid_1(9858);
        set_picid_2(9858);
        set_unit("包");
        set_value(1);

//      set_no_drop(1);
//      set_no_get(1);
        set_no_give(1);
        set_no_sell(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ"; 
}
