#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

#define ITEM_USE_TYPE 	"add_mp"
#define ITEM_USE_TIME	2

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_ADD_MP; }

int get_max_combined() { return 10000; }
int get_item_value() {return 30 ;} //80
int get_item_value_2() {return 30 ;} //60
//int get_item_number() {return 10001010 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name( "Phục Dược" );
        set_picid_1(4257);
        set_picid_2(4257);
        set_value(200);
	//	set_save("knb",10);
        set_amount(1);
        set_record(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Thuốc nước pháp lực trang bị thông thừơng, có thể ngay lập tức khôi phục 2000 điểm lực pháp lực. Thời gian tác dụng 2 giây.";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me )
{
	int type;
	if (get_item_type_2()== ITEM_TYPE_2_ADD_HP) type = EFFECT_USE_ITEM_1;
	else type = EFFECT_USE_ITEM_2 ;
        if (get_effect(me, type))
      	{
      		send_user( me, "%c%s", '!', sprintf("Thời gian đóng băng của vật phẩm còn %d giây", get_effect(me, type)) );
              	return 0;
      	}        
      	set_effect(me, type, ITEM_USE_TIME);
	send_user( me, "%c%c%c%w", 0x30, get_item_type_2(), 0, ITEM_USE_TIME );    // 更新使用间隔  

        me->add_mp( 2000 * ( 100 + me->get_healing_rate() ) / 100 );
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE );      
        return 1;
}
