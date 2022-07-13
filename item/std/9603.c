
#include <equip.h>
#include <effect.h>

inherit TALISMAN;

// 函数：法宝识别
int get_talisman_type() { return 13; }

int get_item_color() { return 2; }

int get_gender() { return 2; }

// 函数：构造处理
void create()
{
        object me = this_object();

        set_name( "凤镯" );
        set_picid_1(99);
        set_picid_2(99);
        set_unit( "个" );

        set_level(1);
        set_value(50);
        set_max_lasting(25099);

        setup();
	set_no_give(1);
	set_no_sell(1);
	set_no_get(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "缘分手镯的一只，相传只要与一位佩带龙镯的玩家组队，\n双方的气血魔法恢复将会增加10%";
}
