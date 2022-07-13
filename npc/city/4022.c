
// 自动生成：/make/npc/make8020
#include <ansi.h>
#include <npc.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0452; }

// 函数：师父识别
int is_master() { return 1; }

// 函数：师父识别(武教头)
int is_basic_master() { return 2; }

int is_self_look() { return 1; }

// 函数：小贩识别
int is_seller() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Ngụy Quốc Công Tượng");
        set_real_name("Luyện Đơn 41~60");
        set_city_name("Ngụy Quốc");
	set_skill(0630, 39);
        set_2( "good", ([
                "01" : "/item/product/63015",
                "02" : "/item/product/63016",
                "03" : "/item/product/63017",
                "04" : "/item/product/63018",
                "05" : "/item/product/63019",
                "06" : "/item/product/63020",
                "07" : "/item/product/63021",
                "08" : "/item/product/63022",                
        ]) );	
        setup();
}

void do_look( object who )
{
        object me = this_object();
        send_user( who, "%c%c%w%s", ':', 3, 0451, 
        	sprintf("%s：\n    %s\n" 
	       	ESC "学习技能\nlearn ? %s\n" 
	       	ESC "购买Luyện Đơn 技能等级41-60级的配方\nlist %s\n"
        	ESC "关闭\nCLOSE\n", 
        	me->get_name(), "/quest/word"->get_country_word(this_object()), me->get_char_id(), me->get_char_id() ) );
}

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 4 ); }
