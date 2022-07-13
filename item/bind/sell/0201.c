#include <equip.h>
#include <ansi.h>
inherit USABLE;
inherit ITEM;

int is_key() {return 1;}

int get_item_value() {return 26 ;}
int get_item_value_2() {return 26 ;}
int get_item_number() {return 10001067 ;}
int get_item_color() {return 2 ;}

// 函数：构造处理
void create()
{
        set_name("青铜钥匙");
        set_picid_1(6703);
        set_picid_2(6703);
        set_level(2);
        set_value(50);
        // -- 与原装备相比增加绑定属性
        set_no_give(1);
        set_no_sell(1);
        //        
}

// 函数：获取描述
string get_desc()
{
        return "传闻能开启周王藏匿宝藏的宝箱。\n将钥匙拖放于放大状态的宝箱之上，便可将"HIR"青铜宝箱"NOR"打开。";
}
