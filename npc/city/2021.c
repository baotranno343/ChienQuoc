
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
        set_real_name("May Mặc 30~39");
        set_city_name("Hàn Quốc");
	set_skill(0640, 39);
        set_2( "good", ([
                "01" : "/item/product/64025",
                "02" : "/item/product/64026",
                "03" : "/item/product/64027",
                "04" : "/item/product/64028",
                "05" : "/item/product/64029",
                "06" : "/item/product/64030",
                "07" : "/item/product/64031",
                "08" : "/item/product/64032",
                "09" : "/item/product/64033",
                "10" : "/item/product/64034",
                "11" : "/item/product/64035",        
                "12" : "/item/product/64036",
                "13" : "/item/product/64037",
                "14" : "/item/product/64038",
                "15" : "/item/product/64039",      
                "16" : "/item/product/64040",
                "17" : "/item/product/64041",
                "18" : "/item/product/64042",
                "19" : "/item/product/64043",
                "20" : "/item/product/64044",
                "21" : "/item/product/64045",        
                "22" : "/item/product/64046",
                "23" : "/item/product/64047",                                       
        ]) );		
        setup();
}

void do_look( object who )
{
        object me = this_object();
        send_user( who, "%c%c%w%s", ':', 3, 0451, 
        	sprintf("%s：\n    %s\n" 
	       	ESC "Học kĩ năng\nlearn ? %s\n" 
	       	ESC "Mua Công thức May Mặc 30 - 39\nlist %s\n"
        	ESC "关闭\nCLOSE\n", 
        	me->get_name(), "/quest/word"->get_country_word(this_object()), me->get_char_id(), me->get_char_id() ) );
}

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 2 ); }
