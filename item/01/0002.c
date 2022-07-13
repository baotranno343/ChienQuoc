
inherit ITEM;
inherit LEGEND_ITEM;
// 函数：构造处理
void create()
{
        set_name("灵石");
        set_picid_1(4940);
        set_picid_2(4940);
        set_unit("块");
        set_value(10);
        set_no_drop(1);
        set_no_get(1);
        set_no_give(1);
        set_no_sell(1);        
}

// 函数：获取描述
string get_desc() 
{ 
        return "一块充满灵气的灵石，据传有清神醒脑的妙用。";
}
