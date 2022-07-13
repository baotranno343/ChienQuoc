#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;


//圣诞节物品
int is_christmas() { return 1;}

void reset()
{
        if( gone_time( get_drop_time() ) > 7200 )    // 2小时
        {
                remove_from_scene();
                destruct( this_object() );
        }
}
// 函数：构造处理
void create()
{
        set_name("Vớ dài");
        set_picid_1(9983);
        set_picid_2(9983);
        set_unit("条");
        set_value(50);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{
	return "Lễ Giáng Sinh khi dùng để trang lễ vật vớ. \n nhưng giao cho ông già Noel đổi lễ vật.";
}

