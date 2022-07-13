
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
        set_name("Cửa Tiệm Công Thức Giày");
        set_city_name("Chu Quốc");

        set_2( "good", ([
				"01" : "/item/product/64720",
				"02" : "/item/product/64721",
				"03" : "/item/product/64726",
				"04" : "/item/product/64727",
				"05" : "/item/product/64732",
				"06" : "/item/product/64733",
				"07" : "/item/product/64738",
				"08" : "/item/product/64739",
				"09" : "/item/product/64744",
				"10" : "/item/product/64745",
			/*	"11" : "/item/product/64750",
				"12" : "/item/product/64751",
				"13" : "/item/product/64756",
				"14" : "/item/product/64757",
				"15" : "/item/product/64762",
				"16" : "/item/product/64763",
				"17" : "/item/product/64768",
				"18" : "/item/product/64769", */
				
        ]) );
        setup();
}
