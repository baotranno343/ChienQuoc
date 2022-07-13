#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;   

int is_zhongqiu() { return 1;}
int get_item_type_2() { return ITEM_TYPE_2_CON_ALL; }
int get_recover_count() { return 10; }
// 函数：构造处理
void create()
{
        set_name("月饼");
        set_picid_1(3570);
        set_picid_2(3570);
        set_unit("个");
        set_value(100);
        set_amount(1);      
	set("add_hp", 400);	        
	set("add_mp", 400);
          
}

void reset()
{
        if( gone_time( get_drop_time() ) > 3000 )    // 50分钟
        {
                remove_from_scene();
                destruct( this_object() );
        }
}

// 函数：获取描述
string get_desc() 
{
	return "中秋节传统食物，20秒内恢复400点气血值和400点法力值。";    	
}

// 函数：使用效果
int get_use_effect( object me ) { return "/sys/item/food" ->get_use_effect(me, this_object()); }