
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
	set_real_name("Cơ Tư");
        set_city_name("Tề Quốc");

        set_2( "good", ([
                "01" : "/item/60/5020",
                "02" : "/item/60/5030",
                "03" : "/item/60/5040",
                "04" : "/item/60/5050",
                "05" : "/item/60/5060",
                "06" : "/item/61/5020",
                "07" : "/item/61/5030",
                "08" : "/item/61/5040",
                "09" : "/item/61/5050",
                "10" : "/item/61/5060",
                "11" : "/item/65/5020",
                "12" : "/item/65/5030",
                "13" : "/item/65/5040",
                "14" : "/item/66/5020",
                "15" : "/item/66/5030",
                "16" : "/item/66/5040",
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