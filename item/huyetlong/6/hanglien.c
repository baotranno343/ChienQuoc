
// 自动生成：/make/equip/makesuit

#include <equip.h>
#include <level.h>
#include <item.h>
#include <ansi.h>
inherit NECK;
//套装组件标志
int is_suit()	{ return 1;}	
//第几套
int get_equip_serial() { return 1; }	//第几套
// 函数：适用门派
int get_family() { return 6; }
//套装名字
string get_suit_name() { return "Khai Sơn"; }	//属于某某套装
// 函数：构造处理
void create()
{
        set_name("Huyết Long - Khai Sơn Liên");
        set_picid_1(8614);
        set_picid_2(8614);

        set_level(105);
        set_value(15000);
        set_max_lasting(20099);
        set("ap+", 195);
        set("dp+", 25);
        set("cp+", 195);
        set("pp+", 174);
        set("sp+", 0);
        set("hp+", 112);
        set("mp+", 110);
		set_item_color(5);	
	set_bind(3);		
	set_hide(0);	
        setup();
}

// 函数：获取描述
string get_desc()
{
         return HIR"Huyết Long Set";
}

// 函数：获取套装描述
string get_suit_desc()
{
        return "Trang bị Huyết Long - Khai Sơn";
}

