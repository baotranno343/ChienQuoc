
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：小贩识别
int is_item_seller() { return 1; }
int is_seller() { return 1; }
int is_self_look() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 5402; }

// 函数：构造处理
void create()
{
        set_name("Cửa Tiệm Công Thức Vũ Khí");
        set_city_name("Chu Quốc");

        set_2( "good", ([
				"01" : "/item/product/62157",
				"02" : "/item/product/62158",
				"03" : "/item/product/62159",
				"04" : "/item/product/62160",
				"05" : "/item/product/62161",
				"06" : "/item/product/62162",
				"07" : "/item/product/62175",
				"08" : "/item/product/62176",
				"09" : "/item/product/62177",
				"10" : "/item/product/62178",
				"11" : "/item/product/62179",
				"12" : "/item/product/62180",
				"13" : "/item/product/62199",
				"14" : "/item/product/62200",
				"15" : "/item/product/62201",
				"16" : "/item/product/62202",
				"17" : "/item/product/62203",
				"18" : "/item/product/62204",
				"19" : "/item/product/62360",
				"20" : "/item/product/62361",
				"21" : "/item/product/62362",
				"22" : "/item/product/62363",
				"23" : "/item/product/62364",
				"24" : "/item/product/62365",
				
        ]) );
        setup();
}
