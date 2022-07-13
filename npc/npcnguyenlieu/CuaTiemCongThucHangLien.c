
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
        set_name("Cửa Tiệm Công Thức Hạng Liên");
        set_city_name("Chu Quốc");

        set_2( "good", ([
				"01" : "/item/product/65708",
				"02" : "/item/product/65709",
				"03" : "/item/product/65710",
				"04" : "/item/product/65711",
				"05" : "/item/product/65712",
				"06" : "/item/product/65713",
				"07" : "/item/product/65714",
				"08" : "/item/product/65715",
				
        ]) );
        setup();
}
