
// 自动生成：/make/equip/makesuit

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
string get_suit_name() { return "Tuyết Điêu"; }	//属于某某套装
// 函数：构造处理
void create()
{
        set_name("Tuyết Điêu Vũ Đới");
        set_picid_1(8713);
        set_picid_2(8713);

        set_level(55);
        set_value(10000);
        set_max_lasting(16099);
        set("ap+", 0);
        set("dp+", 72);
        set("cp+", 0);
        set("pp+", 102);
        set("sp+", 0);
        set("hp+", 77);
        set("mp+", 50);
	set_item_color(3);	//紫色
	set_bind(4);		//捡取绑定
	set_hide(0);		//已鉴定
        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tuyết Điêu Vũ Đới";
}

// 函数：获取套装描述
string get_suit_desc()
{
        return "Trang bị Tử Kim Tuyết Điêu";
}

