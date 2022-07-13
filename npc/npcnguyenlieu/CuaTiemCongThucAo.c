
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
        set_name("Cửa Tiệm Công Thức Y Phục");
        set_city_name("Chu Quốc");

        set_2( "good", ([
				"01" : "/item/product/64718",
				"02" : "/item/product/64719",
				"03" : "/item/product/64724",
				"04" : "/item/product/64725",
				"05" : "/item/product/64730",
				"06" : "/item/product/64731",
				"07" : "/item/product/64736",
				"08" : "/item/product/64737",
				"09" : "/item/product/64742",
				"10" : "/item/product/64743",
			/*	"11" : "/item/product/64748",
				"12" : "/item/product/64749",
				"13" : "/item/product/64754",
				"14" : "/item/product/64755",
				"15" : "/item/product/64760",
				"16" : "/item/product/64761",
				"17" : "/item/product/64766",
				"18" : "/item/product/64767",*/
				
        ]) );
        setup();
}
