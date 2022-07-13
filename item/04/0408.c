#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;   

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_CON_ALL; }

int get_recover_count() { return 5; }

int is_zhongqiu() { return 1;}

void reset()
{
        if( gone_time( get_drop_time() ) > 7200 )    // 2小时
        {
                remove_from_scene();
                destruct( this_object() );
        }
}
// 函数：构造处理
void create()
{
        set_name("月饼");
        set_picid_1(3570);
        set_picid_2(3570);
        set_unit("个");
        set_value(50);
        set_amount(1);
        set("add_hp", 350);	        
	set("add_mp", 400);	        
}

// 函数：获取描述
string get_desc() 
{
	return "忍不住想一口咬下去的中秋月饼，十分美味。\n可交给嫦娥姐姐兑换中秋礼物。\n月饼能在10秒内回复350点气血与400点法术力。";    	
}

// 函数：使用效果
int get_use_effect( object me ) { return "/sys/item/food" ->get_use_effect(me, this_object()); }