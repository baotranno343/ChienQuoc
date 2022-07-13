
#include <item.h>
#include <ansi.h>

inherit ITEM;

private int Money;
private int OrginMoney;

// 可使用
int is_usable() {return 1;}

// 函数：商人钱票
// int is_cheque() { return 1; }

// 函数：商人钱票
int get_item_type() { return ITEM_TYPE_CHEQUE2; }

// 函数：获取钱票金额
int get_money() { return Money; }

// 函数：设置钱票金额
int set_money( int gold ) { return Money = gold; }

// 函数：增加钱票金额
int add_money( int gold ) { return Money += gold; }

// 函数：获取钱票本金
int get_orgin_money() { return OrginMoney; }

// 函数：设置钱票本金
int set_orgin_money( int gold ) { return OrginMoney = gold; }

// 函数：构造处理
void create()
{
        set_name("Ngân Phiếu");
        set_picid_1(0008);
        set_picid_2(0008);
        set_unit("张");

        set_no_drop(1);
        set_no_get(1);
        set_no_give(1);
        set_no_sell(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return sprintf( "商人专用钱票，用于商人职业" ); 
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me, this_object()); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object obj)
{
        string result;
        result = sprintf("通商Ngân Phiếu（任务专用）\n原面值：  %d 金\n",  obj->get_orgin_money());
        if (obj->get_money()<=obj->get_orgin_money()/2)
                result += sprintf("现面值："HIR"  %d "NOR"金\n", obj->get_money());
        else                
        if (obj->get_money() - me->get_save_2("mastertask.targetxy") >=obj->get_orgin_money())
                result += sprintf("现面值："HIG"  %d "NOR"金\n", obj->get_money());                
        else
                result += sprintf("现面值：  %d 金\n", obj->get_money());               
        if (me->get_save_2("mastertask.type")==11)
                result += sprintf("任务要求：赚取 %d 金", me->get_save_2("mastertask.targetxy"));
        send_user( me, "%c%s", ';', result );                                

        return 0;
}