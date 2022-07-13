
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
        set_name("Cửa Tiệm Công Thức Nón");
        set_city_name("Chu Quốc");

        set_2( "good", ([
				"01" : "/item/product/64722",
				"02" : "/item/product/64723",
				"03" : "/item/product/64728",
				"04" : "/item/product/64729",
				"05" : "/item/product/64734",
				"06" : "/item/product/64735",
				"07" : "/item/product/64740",
				"08" : "/item/product/64741",
				"09" : "/item/product/64746",
				"10" : "/item/product/64747",
			/*	"11" : "/item/product/64752",
				"12" : "/item/product/64753",
				"13" : "/item/product/64758",
				"14" : "/item/product/64759",
				"15" : "/item/product/64764",
				"16" : "/item/product/64765",
				"17" : "/item/product/64770",
				"18" : "/item/product/64771", */
				
        ]) );
        setup();
}
