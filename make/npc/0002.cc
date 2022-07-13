
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return %04d; }

// 函数：构造处理
void create()
{
        set_name("%s");
        set_city_name("%s");

        set_2( "good", ([
%s
        ]) );

        setup();
}
