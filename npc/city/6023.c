
// 自动生成：/make/npc/make8020
#include <ansi.h>
#include <npc.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0451; }

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
        set_name("Sở Quốc Công Tượng");
        set_real_name("Điêu Khắc 60~79");
        set_city_name("Sở Quốc");
	set_skill(0650, 39);
        set_2( "good", ([
                "01" : "/item/product/65061",
                "02" : "/item/product/65062",
                "03" : "/item/product/65063",
                "04" : "/item/product/65064",
                "05" : "/item/product/65065",
                "06" : "/item/product/65066",
                "07" : "/item/product/65067",
                "08" : "/item/product/65068",
                "09" : "/item/product/65069",
                "10" : "/item/product/65070",
                "11" : "/item/product/65071",        
                "12" : "/item/product/65072",
                "13" : "/item/product/65073",
                "14" : "/item/product/65074",
                "15" : "/item/product/65075",      
                "16" : "/item/product/65076",
                "17" : "/item/product/65077",
                "18" : "/item/product/65078",
                "19" : "/item/product/65079",
                "20" : "/item/product/65080",
                "21" : "/item/product/65081",        
                "22" : "/item/product/65082",                                          
        ]) );	
        setup();
}

void do_look( object who )
{
        object me = this_object();
        send_user( who, "%c%c%w%s", ':', 3, 0451, 
        	sprintf("%s：\n    %s\n" 
	       	ESC "Học kĩ năng\nlearn ? %s\n" 
	       	ESC "Mua công thức Điêu Khắc cấp 60 - 79\nlist %s\n"
        	ESC "关闭\nCLOSE\n", 
        	me->get_name(), "/quest/word"->get_country_word(this_object()), me->get_char_id(), me->get_char_id() ) );
}

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 8 ); }
