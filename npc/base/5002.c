
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 5; }

// 函数：获取人物造型
int get_char_picid() { return 5402; }

// 函数：构造处理
void create()
{
        set_name("Chủ Tiệm Tạp Hóa");
	set_real_name("Chương Dung");
        set_city_name("Tần Quốc");

        set_2( "good", ([
                "01" : "/item/std/0401",
                "02" : "/item/std/0407",
                "04" : "/item/std/0409",
                "05" : "/item/std/0413",
                "06" : "/item/std/0591",
                "07" : "/item/32/3231",
                "08" : "/item/98/9871",
		"09" : "/item/std/9808",
		"10" : "/item/std/9819",
		"11" : "/item/std/9820",
		"12" : "/item/stuff/0500",
		"13" : "/item/stuff/0501",	
		"14" : "/item/49/4900",		
		"15" : "/item/std/0410",
		"16" : "/item/08/0010",
		"17" : "/item/08/0011",
		"18" : "/item/08/0012",
		"19" : "/item/44/4403",
		"20" : "/item/44/4406",
		"21" : "/item/stuff/0502",
        ]) );

        setup();
}

// 函数：对话处理
void do_look( object who )
{
	"/quest/help"->send_help_tips(who, 41);
        "/cmd/std/look"->main( who, sprintf( "%x#", getoid( this_object() ) ) );
}
