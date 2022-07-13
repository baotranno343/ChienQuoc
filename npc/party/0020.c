
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
        set_name("道具商人");
        set_city_name("新手村");

        set_2( "good", ([
                "01" : "/item/08/0003",
                "02" : "/item/sell/0002",
                "03" : "/item/08/0004",
                "04" : "/item/sell/0004",
                "05" : "/item/91/9166",
                "06" : "/item/sell/0006",
                "07" : "/item/sell/0007",
                "08" : "/item/sell/0008",
		"09" : "/item/sell/0009",
		"10" : "/item/sell/0010",
		"11" : "/item/91/9178",
		"12" : "/item/sell/0012",
		"13" : "/item/08/0001",
		"14" : "/item/08/0002",
		"15" : "/item/sell/0015",
		"16" : "/item/sell/0016",
		"17" : "/item/sell/0017",
		"18" : "/item/sell/0018",                
		"19" : "/item/sell/0019",
		"20" : "/item/04/0405",
		"21" : "/item/std/9513",
		"22" : "/item/std/6001",
		"23" : "/item/std/6002",		
		"24" : "/item/sell/0025",
        ]) );
        setup();
}
