
// 自动生成：/make/item/make98c

inherit ITEM;

// 函数：构造处理
void create()
{
        set_name("%s");
        set_picid_1(%d);
        set_picid_2(%d);
        set_unit("%s");
        set_value(1);
	
	set_no_drop(1);
        set_no_give(1);
        set_no_sell(1);        
}

// 函数：获取描述
string get_desc() 
{ 
        return "%s"; 
}
