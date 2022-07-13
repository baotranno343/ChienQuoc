
// 自动生成：/make/npc/make8020
#include <ansi.h>
#include <npc.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5417; }

// 函数：师父识别
int is_master() { return 1; }

// 函数：师父识别(武教头)
int is_basic_master() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Chu Quốc Ngự Trù");
        set_city_name("Tề Quốc");
//	set_skill(0610, 80);
        setup();
}

void do_look( object who )
{
        object me = this_object();
        send_user( who, "%c%c%w%s", ':', 3, 5416, 
        	sprintf("%s：\n    %s\n" 
//	       	ESC "学习技能\nlearn ? %s\n" 
        	ESC "关闭\nCLOSE\n", 
        	me->get_name(), "/quest/word"->get_country_word(this_object()), me->get_char_id() ) );
}

