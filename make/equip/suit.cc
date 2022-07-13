
// 自动生成：/make/equip/makesuit

#include <equip.h>
#include <level.h>
#include <item.h>

inherit %s;
//套装组件标志
int is_suit()	{ return 1;}	
//第几套
int get_equip_serial() { return %d; }	//第几套
// 函数：适用门派
int get_family() { return %d; }
//套装名字
string get_suit_name() { return "%s"; }	//属于某某套装
// 函数：构造处理
void create()
{
        set_name("%s");
        set_picid_1(%04d);
        set_picid_2(%04d);

        set_level(%d);
        set_value(%d);
        set_max_lasting(%d);
        set("ap+", %d);
        set("dp+", %d);
        set("cp+", %d);
        set("pp+", %d);
        set("sp+", %d);
        set("hp+", %d);
        set("mp+", %d);
	set_item_color(3);	//紫色
	set_bind(4);		//捡取绑定
	set_hide(0);		//已鉴定
        setup();
}

// 函数：获取描述
string get_desc()
{
        return "%s";
}

// 函数：获取套装描述
string get_suit_desc()
{
        return "%s";
}

