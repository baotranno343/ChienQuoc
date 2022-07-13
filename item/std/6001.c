#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit USABLE;   

int get_item_value() {return 350 ;}
int get_item_value_2() {return 280 ;}
int get_item_number() {return 23 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name( "百宝囊" );
        set_picid_1(7113);
        set_picid_2(7113);
        set_value(2000);
        set("bag", 12);
        set_record(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "传说装满了无数珍宝的口袋，\n可增加使用者12格的背包空间。\n百宝囊30天后会自动损坏。"; 
}

// 函数：使用效果
int get_use_effect( object me ) { return "/cmd/std/bag" ->get_use_effect(me, this_object()); }
