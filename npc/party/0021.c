
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：小贩识别
int is_item_seller() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 5402; }

// 函数：构造处理
void create()
{
        set_name("道具商人２");
        set_city_name("新手村");

        set_2( "good", ([
                "01" : "/item/sell/0020",
                "02" : "/item/sell/0030",
                "03" : "/item/sell/0031",
        ]) );
        setup();
}
