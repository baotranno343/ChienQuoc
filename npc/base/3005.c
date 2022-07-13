
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>
#include <ansi.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 5405; }

// 有自己的do_look函数
int is_self_look() { return 1; }

void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Chủ Tiệm Trang Phục");
	set_real_name("Lí Đoái");
        set_city_name("Triệu Quốc");

        set_2( "good", ([
                "01" : "/item/60/1020",
                "02" : "/item/60/1030",
                "03" : "/item/60/1040",
                "04" : "/item/60/1050",
                "05" : "/item/60/1060",
                "06" : "/item/61/1020",
                "07" : "/item/61/1030",
                "08" : "/item/61/1040",
                "09" : "/item/65/1020",
                "10" : "/item/65/1030",
                "11" : "/item/65/1040",
                "12" : "/item/66/1020",
                "13" : "/item/66/1030",
                "14" : "/item/66/1040",

        ]) );

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string result;
	result = sprintf("%s：\n    "+"/quest/word"->get_normal_word(me)+"\n", me->get_name() );
	result += sprintf(ESC "哪里有适合我的装备？\ntalk %x# welcome.99\n", getoid(me) ) ;        	
	result += sprintf( ESC "交易\nlist %x#\n" ESC "我只是随便看看\nCLOSE\n", getoid(me) ) ;        	
	send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(), result );
}

void do_welcome( string arg )
{
        object me = this_object();
        "/npc/base/0005"->do_welcome2(me, "99");
}