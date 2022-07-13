
// 自动生成：/make/item/make37d

inherit ITEM;
//  inherit COMBINED;

// 函数：叠加上限
//  int get_max_combined() { return 1; }

// 函数：构造处理
void create()
{
        set_name("象棋残局");
        set_picid_1(3791);
        set_picid_2(3791);
        set_unit("盘");
        set_value(100);
//      set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "象棋残局";
}
