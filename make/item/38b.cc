
// 自动生成：/make/item/make38b

inherit ITEM;
%s  inherit COMBINED;

// 函数：叠加上限
%s  int get_max_combined() { return %d; }

// 函数：构造处理
void create()
{
        set_name("%s");
        set_picid_1(%d);
        set_picid_2(%d);
        set_unit("%s");
        set_value(%d);
%s      set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "%s";
}
