
inherit ITEM;

// 函数：构造处理
void create()
{
        set_name( "食物" );
        set_picid_1(0034);
        set_picid_2(0034);
        set_unit( "份" );
        set_value(50);
}

// 函数：获取描述
string get_desc() 
{ 
        return "送到城中四处的工地上"; 
}
