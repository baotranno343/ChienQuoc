// 注意：装备、武器不允许是组合物品，因为它们有特殊属性

#include <equip.h>

#define MAX_COMBINED    10000              // 叠加上限

private int Amount;                     // 道具个数

// 函数：叠加物品识别
int is_combined() { return 1; }

// 函数：物品叠加上限
int get_max_combined() { return MAX_COMBINED; }

// 函数：获取道具数量
int get_amount() { return Amount; }

// 函数：设置道具数量
int set_amount( int num ) 
{ 
        object who, item, item2;
        string name;

        item = this_object();

        if( num < 1 )
        {
                if(     item->is_auto_equip()    // 自动装备类型
                &&      objectp( who = item->get_owner() )    // 获取装备主人
                &&      who->get_equip(HAND_TYPE) == item    // 装备在法宝栏
                &&      objectp( item2 = present( item->get_name(), who, 1, MAX_CARRY ) ) )    // 道具栏有同样物品
                        who->use_equip(item2);    // 自动装备毒药、阵旗

                Amount = 0;
                if( environment() ) item->remove_from_user();
                else if( who = item->get_owner() ) send_user( who, "%c%d", 0x2d, getoid(item) );
                else item->remove_from_scene();
                destruct(item);
        }
        else 
        {
                Amount = range_value( num, 1, get_max_combined() );
                if( who = environment() ) 
                        send_user( who, "%c%d%w", 0x4e, getoid(item), Amount );
                else if( who = item->get_owner() )
                        send_user( who, "%c%d%w", 0x4e, getoid(item), Amount );
                else    send_user( get_scene_object_2(item, USER_TYPE), "%c%d%w", 0x4e, getoid(item), Amount );
        }

        return Amount;
}

// 函数：增加道具数量
int add_amount( int num ) { return set_amount( Amount + num ); }
