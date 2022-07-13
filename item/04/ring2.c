
#include <equip.h>
#include <effect.h>
#include <ansi.h>
inherit TALISMAN;

// 函数：法宝识别
int get_talisman_type() { return 13; }

int get_item_color() { return 2; }

int get_gender() { return 2; }

// 函数：构造处理
void create()
{
        set_name( "情比金坚戒" );
        set_picid_1(0908);
        set_picid_2(0908);
        set_unit( "个" );

        set_level(1);
        set_value(1998);
        set_max_lasting(17099);
        set("ap", 30);  
        set("cp", 30);  
        set("hp", 120);  
        set("sp", 30);  
        set_no_give(1);
//        set_no_drop(1);
        set_no_sell(1);  
	set_bind(4);
        setup();
}

// 函数：获取描述
string get_desc() 
{ 
        return sprintf("增加人物属性\n"HIC"牛郎织女赠送的戒指，拥有神奇的力量\n装备要求："HIR"女性\n"HIB"七夕活动纪念");
}


