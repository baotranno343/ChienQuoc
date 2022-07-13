
// 自动生成：/make/equip/makesuit

#include <equip.h>
#include <level.h>
#include <item.h>

inherit BOOTS;
//套装组件标志
int is_suit()	{ return 1;}	
//第几套
int get_equip_serial() { return 1; }	//第几套
// 函数：适用门派
int get_family() { return 1; }
//套装名字
string get_suit_name() { return "Đằng Long"; }	//属于某某套装
// 函数：构造处理
void create()
{
        set_name("Đằng Long Chi Ngoa");
        set_picid_1(8811);
        set_picid_2(8811);

        set_level(85);
        set_value(15000);
        set_max_lasting(16099);
        set("ap+", 0);
        set("dp+", 90);
        set("cp+", 0);
        set("pp+", 25);
        set("sp+", 90);
        set("hp+", 135);
        set("mp+", 0);
	set_item_color(3);	//紫色
	set_bind(4);		//捡取绑定
	set_hide(0);		//已鉴定
        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Đằng Long Chi Ngoa";
}

// 函数：获取套装描述
string get_suit_desc()
{
        return "Trang bị Tử Kim Đằng Long";
}

