
inherit ITEM;
inherit COMBINED;

// 函数：宝石识别
int is_diamond_3() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "宝石碎片" );
        set_picid_1(8900);
        set_picid_2(8900);
        set_unit( "块" );
        set_value(30000);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "［宝石合成材料］放置到残缺宝石上能合成完美宝石";
}
