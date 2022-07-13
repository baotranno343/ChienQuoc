
// 自动生成：/make/equip/60b

#include <equip.h>
#include <level.h>
#include <item.h>

inherit WAIST;

//套装组件标志
int is_suit()	{ return 1;}	
//第几套
int get_equip_serial() { return 1; }	//第几套
// 函数：适用门派
int get_family() { return 6; }
//套装名字
string get_suit_name() { return "Thiên Long"; }	//属于某某套装

// 函数：构造处理
void create()
{
        set_name("Thiên Long Yêu Đới");
        set_picid_1(8704);        set_picid_2(8704);

        set_level(200);        set_value(39500);
        set_max_lasting(50099);
        set("dp+", 450);
        set("pp+", 450);
		set("hp+", 35500);
		set("hpp", 10000);
		set("mp+", 50000);
		set("mpp", 10000);
		set("hp%+", 300);
		set("mp%+", 300);
		set("sp+", 280);
		set_item_color(2);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thiên Long Yêu Đới";
}
// 函数：获取套装描述
string get_suit_desc()
{
        return "Thiên Long Yêu Đới";
}