
// 自动生成：/make/item/make30

inherit ITEM;
inherit COMBINED;
// 函数：叠加上限
int get_max_combined() { return 30; }

// 函数：构造处理
void create()
{
        set_name("切好的猪肉");
        set_picid_1(4218);
        set_picid_2(4218);
        set_value(50);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "切好的，制作粽子用的猪肉"; 
}

void reset()
{
        if( gone_time( get_drop_time() ) > 2400 )    // 40分钟
        {
                remove_from_scene();
                destruct( this_object() );
        }
}