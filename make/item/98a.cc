
// 自动生成：/make/item/make98a

inherit ITEM;
inherit "/inh/item/task";

// 函数：构造处理
void create()
{
        set_name("%s");
        set_picid_1(%d);
        set_picid_2(%d);
        set_unit("%s");
        set_value(%d);
}

// 函数：获取描述
string get_desc() 
{ 
        return "使命任务物品"; 
}
