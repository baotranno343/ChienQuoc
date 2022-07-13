
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
        set_name("Tề Quốc Công Tượng");
        set_real_name("Cơ Quan 41~60");
        set_city_name("Tề Quốc");
	set_skill(0660, 39);
        set_2( "good", ([
                "01" : "/item/product/66018",
                "02" : "/item/product/66019",
                "03" : "/item/product/66020",
                "04" : "/item/product/66021",
                "05" : "/item/product/66022",
                "06" : "/item/product/66023",
                "07" : "/item/product/66024",
                "08" : "/item/product/66025",
                "09" : "/item/product/66026",
                "10" : "/item/product/66027",
                "11" : "/item/product/66028",        
                "12" : "/item/product/66030",
                "13" : "/item/product/66031",
                "14" : "/item/product/66032",
                "15" : "/item/product/66033",      
                "16" : "/item/product/66034",
                "17" : "/item/product/66035",
                "18" : "/item/product/66036",                                      
        ]) );	                         
        setup();                         
}                                        

void do_look( object who )
{
        object me = this_object();
        send_user( who, "%c%c%w%s", ':', 3, 0450, 
        	sprintf("%s：\n    %s\n" 
	       	ESC "学习技能\nlearn ? %s\n" 
	       	ESC "购买Cơ Quan 技能等级41-60级的配方\nlist %s\n"
        	ESC "关闭\nCLOSE\n", 
        	me->get_name(), "/quest/word"->get_country_word(this_object()), me->get_char_id(), me->get_char_id() ) );
}

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 4 ); }
