inherit ITEM;
inherit "/inh/item/task2";

// 函数：构造处理
void create()
{
        set_name("Vật phẩm mất trộm");
        set_picid_1(4982);
        set_picid_2(4982);
        set_unit("个");
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