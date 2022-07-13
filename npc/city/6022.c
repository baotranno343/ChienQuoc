
// 自动生成：/make/npc/make8020
#include <ansi.h>
#include <npc.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0450; }

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
        set_real_name("Điêu Khắc 47~59");
        set_city_name("Sở Quốc");
	set_skill(0650, 39);
        set_2( "good", ([
                "01" : "/item/product/65043",
                "02" : "/item/product/65044",
                "03" : "/item/product/65045",
                "04" : "/item/product/65046",
                "05" : "/item/product/65047",
                "06" : "/item/product/65048",
                "07" : "/item/product/65049",
                "08" : "/item/product/65050",
                "09" : "/item/product/65051",
                "10" : "/item/product/65052",
                "11" : "/item/product/65053",        
                "12" : "/item/product/65054",
                "13" : "/item/product/65055",
                "14" : "/item/product/65056",
                "15" : "/item/product/65057",      
                "16" : "/item/product/65058",
                "17" : "/item/product/65059",
                "18" : "/item/product/65060",                                          
        ]) );	
        setup();
}

void do_look( object who )
{
        object me = this_object();
        send_user( who, "%c%c%w%s", ':', 3, 0451, 
        	sprintf("%s：\n    %s\n" 
	       	ESC "Học kĩ năng\nlearn ? %s\n" 
	       	ESC "Mua công thức Điêu Khắc cấp 47 - 59\nlist %s\n"
        	ESC "关闭\nCLOSE\n", 
        	me->get_name(), "/quest/word"->get_country_word(this_object()), me->get_char_id(), me->get_char_id() ) );
}

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 4 ); }
