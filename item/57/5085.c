
// 自动生成：/make/equip/makesuit

#include <equip.h>
#include <level.h>
#include <item.h>

inherit NECK;
//套装组件标志
int is_suit()	{ return 1;}	
//第几套
int get_equip_serial() { return 1; }	//第几套
// 函数：适用门派
int get_family() { return 5; }
//套装名字
string get_suit_name() { return "Chiến Lang"; }	//属于某某套装
// 函数：构造处理
void create()
{
        set_name("Chiến Lang Hạng Liên");
        set_picid_1(8662);
        set_picid_2(8662);

        set_level(85);
        set_value(15000);
        set_max_lasting(16099);
        set("ap+", 0);
        set("dp+", 25);
        set("cp+", 208);
        set("pp+", 141);
        set("sp+", 0);
        set("hp+", 95);
        set("mp+", 140);
	set_item_color(3);	//紫色
	set_bind(4);		//捡取绑定
	set_hide(0);		//已鉴定
        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Chiến Lang Hạng Liên";
}

// 函数：获取套装描述
string get_suit_desc()
{
        return "Trang bị Tử Kim Chiến Lang";
}

