
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
        set_name("Hàn Quốc Công Tượng");
        set_city_name("Hàn Quốc");
	set_skill(0640, 39);
        set_2( "good", ([
                "01" : "/item/product/64116",
                "02" : "/item/product/64117",
                "03" : "/item/product/64118",
                "04" : "/item/product/64119",
                "05" : "/item/product/64120",
                "06" : "/item/product/64121",
                "07" : "/item/product/64122",
                "08" : "/item/product/64123",
                "09" : "/item/product/64124",
                "10" : "/item/product/64125",
                "11" : "/item/product/64126",        
                "12" : "/item/product/64127",
                "13" : "/item/product/64128",
                "14" : "/item/product/64129",
                "15" : "/item/product/64130",      
                "16" : "/item/product/64131",
                "17" : "/item/product/64132",
                "18" : "/item/product/64133",
                "19" : "/item/product/64134",
                "20" : "/item/product/64135",
                "21" : "/item/product/64136",        
                "22" : "/item/product/64137",
                "23" : "/item/product/64138",                                       
                "24" : "/item/product/64139",
        ]) );		
        setup();
}

void do_look( object who )
{
        object me = this_object();
        send_user( who, "%c%c%w%s", ':', 3, 0451, 
        	sprintf("%s：\n    %s\n" 
	       	ESC "Học kĩ năng\nlearn ? %s\n" 
	       	ESC "Mua công thức May Mặc 69 - 79\nlist %s\n"
        	ESC "关闭\nCLOSE\n", 
        	me->get_name(), "/quest/word"->get_country_word(this_object()), me->get_char_id(), me->get_char_id() ) );
}

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 2 ); }
