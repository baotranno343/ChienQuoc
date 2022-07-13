
inherit ITEM;
inherit COMBINED;

// 函数:物品叠加上限
int get_max_combined() { return 10000; }

// 函数:构造处理
void create()
{
        set_name( "Bùa Giấy" );
        set_picid_1(0401);
        set_picid_2(0401);
        set_unit( "张" );
        set_value(10);
        set_amount(1);
}

// 函数:获取描述
string get_desc() 
{ 
        return "Là vật cần thiết để sử dụng phép thuật";
}
