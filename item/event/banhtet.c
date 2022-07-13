
inherit ITEM;
inherit COMBINED;

// 函数：物品叠加上限
int get_max_combined() { return 5000; }
int get_item_color() {return 1 ;}
// 函数：构造处理
void create()
{
        set_name( "Bánh Tết" );
        set_picid_1(3304);
        set_picid_2(3304);
        set_value(10);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Loại bánh mà dịp Tết mọi người mọi nhà hay ăn với nhau mỗi khi sum họp.";
}
