
#include <effect.h>
#include <skill.h>
#include <ansi.h>

inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

int get_item_value() {return 15 ;}
int get_item_value_2() {return 15 ;}
int get_item_number() {return 10001075 ;}
int get_item_color() {return 2 ;}

// 函数：构造处理
void create()
{
        set_name( "人参王" );
        set_picid_1(9943);
        set_picid_2(9943);
        set_unit( "粒" );
        set_value(800);
        set_amount(1);
        set_record(1);
        // -- 与原装备相比增加绑定属性
        set_no_give(1);
        set_no_sell(1);
        //        
        set("effect", 2000);
}

// 函数：获取描述
string get_desc() 
{ 
        return "传说是经验丰富的老参农在长白山挖到的人参之王，有生肌肉白骨的功效。\n持续1小时内可提升玩家2000点气血上限。\n冷却时间2秒。";
}

string get_short()
{
	return "持续1小时内可提升玩家2000点气血上限。";
}

// 函数：使用效果
int get_use_effect( object me ) { return "/item/sell/0006"->get_use_effect_callout(me,this_object()); }


// 函数：使用效果
int confirm_use( object me ) { return "/item/sell/0006" ->confirm_use_callout( me, this_object() ); }
