#include <ansi.h>
#include <item.h>

inherit ITEM;

// 函数：构造处理
void create()
{
        set_name( "玉玺" );
        set_picid_1(97);
        set_picid_2(97);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1); 
        set("dodolook",1); 
}
// 函数：获取描述
string get_desc() 
{ 
        return "王侯权力的凭证。"; 
}