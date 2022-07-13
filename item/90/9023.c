
// 自动生成：/make/item/make90

inherit ITEM;
inherit COMBINED;

// 函数：叠加上限
int get_max_combined() { return 5; }

// 函数：草药识别
int is_herb() { return 1; }

// 函数：构造处理
void create()
{
        set_name("洋金花");
        set_picid_1(9023);
        set_picid_2(9023);
        set_unit("朵");
        set_value(1200);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "中草药的一种";
}
