
#include <equip.h>
inherit USABLE;
inherit ITEM;

int get_item_value() {return 1 ;}
int get_item_value_2() {return 1 ;}
int get_item_number() {return 10001073 ;}

// 函数：构造处理
void create()
{
        set_name("储备箱");
        set_picid_1(0080);
        set_picid_2(0080);
        // -- 与原装备相比增加绑定属性
        set_no_give(1);
        set_no_sell(1);
        //
        set_value(1);
}

// 函数：获取描述
string get_desc()
{
        return "可替代帮派帐房先生储备所需物品的箱子，得到后给予帐房先生便可完成储备任务。";
}
