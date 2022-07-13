
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
        set_name("Tần Quốc Công Tượng");
        set_real_name("Rèn Đúc 21~40");
        set_city_name("Tần Quốc");
	set_skill(0620, 39);
        set_2( "good", ([
                "01" : "/item/product/62007",
                "02" : "/item/product/62008",
                "03" : "/item/product/62009",
                "04" : "/item/product/62010",
                "05" : "/item/product/62011",
                "06" : "/item/product/62012",
                "07" : "/item/product/62013",
                "08" : "/item/product/62014",
                "09" : "/item/product/62015",
                "10" : "/item/product/62016",
                "11" : "/item/product/62017",
                "12" : "/item/product/62018",
                "13" : "/item/product/62019",
                "14" : "/item/product/62020",
                "15" : "/item/product/62021",
                "16" : "/item/product/62022",
                "17" : "/item/product/62023",
                "18" : "/item/product/62024",
                "19" : "/item/product/62025",
                "20" : "/item/product/62026",
                "21" : "/item/product/62027",
                "22" : "/item/product/62028",
        ]) );	
        setup();
}

void do_look( object who )
{
        object me = this_object();
        send_user( who, "%c%c%w%s", ':', 3, 0451, 
        	sprintf("%s：\n    %s\n" 
	       	ESC "Học kĩ năng\nlearn ? %s\n" 
	       	ESC "Mua công thức Rèn đúc cấp 21 - 40\nlist %s\n"
        	ESC "关闭\nCLOSE\n", 
        	me->get_name(), "/quest/word"->get_country_word(this_object()), me->get_char_id(), me->get_char_id() ) );
}

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 2 ); }
