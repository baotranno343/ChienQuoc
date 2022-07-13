
inherit ITEM;
inherit USABLE;

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

int get_item_value() {return 500 ;}
int get_item_value_2() {return 450 ;}
int get_item_number() {return 10001019 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name( "八仙丹" );
        set_picid_1(9166);
        set_picid_2(9166);
        set_unit( "粒" );
        set_value(50);
        // -- 与原装备相比增加绑定属性
        set_no_give(1);
        set_no_sell(1);
        //       
}

// 函数：获取描述
string get_desc() 
{ 
        return "相传八仙归位后，集合八人神力炼制而成。\n能使体力完全恢复。冷却时间30秒。";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me )
{
      	if( gone_time( me->get_time("eat_bx") ) < 30 )
        {
                send_user( me, "%c%s", '!', sprintf("服用八仙丹还需等候%d秒", 30 - gone_time( me->get_time("eat_bx") ) ) );
                return 0;
        }
        if (me->get_strength()>=200)
        {
                send_user( me, "%c%s", '!', "您的体力已满。" );
                return 0;
        }        
        me->set_time( "eat_bx", time() );  

        me->add_strength(200);

        return 1;
}
