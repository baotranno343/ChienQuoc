#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

int get_item_value() {return 200 ;}
int get_item_value_2() {return 200 ;}
//int get_item_number() {return 10001018 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name( "Phục Sinh Đơn" );
        set_picid_1(9120);
        set_picid_2(9120);
	set_value(188);
//	set_save("knb2",20);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Có sức mạnh thuộc về sinh mệnh của Ki Dị Đơn, nghe nói có thể cứu những linh hồn ngừơi chết.\n Có thể giúp người chơi sống lại, tránh những tổn thất khi tử nạn.\n Người chơi có thể chọn Hồi sinh tại chỗ hoặc Hồi sinh tại 1 điểm bất kỳ trong vùng.\n Sau khi hồi sinh sẽ khôi phục toàn bộ khí huyết và pháp lực của bạn.";
}

// 函数：使用效果
int revive( object me, int type ) { return __FILE__ ->revive_call(me,this_object(), type); }

// 函数：使用效果(在线更新)
int revive_call( object me,object item, int type)
{
	int z, x, y, p;
//	object map;
//	map = get_map_object(get_z(me))
        if( me->is_die() )
        {
				set_effect(me, EFFECT_USER_DIE, 0);
                me->set_die(0);
                me->set_hp( me->get_max_hp() );
                me->set_mp( me->get_max_mp() );

                me->set_login_flag(2);    // 跳转保护
                set_invisible(me, 1);
                set_effect(me, EFFECT_USER_LOGIN, 2);
                item->add_amount(-1);
        }
        if (type==2)
        {
        	z = get_z(me);
        	p = get_jumpin(z, -1);
        	if( p )
        	{
        		x = p / 1000;  y = p % 1000;
        		me->add_to_scene(z, x, y, 3);
        	}
        }
        return 1;
}
