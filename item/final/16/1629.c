#include <item.h>
#include <effect.h>
#include <skill.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

inherit "/inh/equip/equip";

#define SKILL_LEVEL     0

// 函数：叠加上限
int get_max_combined() { return 1; }

// 函数：成品编号
int get_fin_type() { return 1629; }

// 函数：可对目标使用的物品
int get_item_type_2() { return ITEM_TYPE_2_USABLE3; }

// 函数：构造处理
void create()
{
        set_name( "Hỗn Thiên Nghi" );
        set_picid_1(4195);
        set_picid_2(4195);
        set_value(3000);
        set_amount(1);
        set_max_lasting(1000);
        set_lasting(1000);        
}

// 函数：获取描述
string get_desc()
{
        string color = "";
	object me = this_player();
	if (me->get_skill(660)<SKILL_LEVEL) color = HIR + sprintf("Yêu cầu Cơ quan cấp bậc： %d\n", SKILL_LEVEL);
	else color = sprintf("Yêu cầu Cơ quan cấp bậc： %d\n", SKILL_LEVEL);
        return  color + "Nhìn đặc biệt khu vực 20X20 phạm vi, số lần sử dụng 10。";
}

// 函数：使用效果
int get_use_effect( object me, int z, int x, int y ) { return __FILE__ ->get_use_effect_callout(me, this_object(), z, x, y); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object item, int z, int x, int y )
{
	int p;
	object map;
	if (time()-me->get_save("huntian")<1800)
        {
                send_user( me, "%c%s", '!', sprintf("Đạo cụ thời gian còn thừa %d giây", 1800 -time()+me->get_save("huntian")) );
                return 0;
        }	
	if( objectp( map = get_map_object( get_z(me) ) ) )
	{
		if (map->is_virtual_scene()||map->is_changping())
		{
			send_user( me, "%c%s", '!', "Nơi này không thể sử dụng hỗn thiên nghi." );
			return 0;
		}
	}
	if( objectp( map = get_map_object( z ) ) )
	{
		if (map->is_virtual_scene()||map->is_changping())
		{
			send_user( me, "%c%s", '!', "Không thể tới mục đích địa đồ." );
			return 0;
		}
	}	
	p = get_valid_xy(z, x, y, IS_CHAR_BLOCK);
	if (p==0)
	{
		send_user( me, "%c%s", '!', "Mục đích địa quá mức chen chúc." );
		return 0;
	}	
	if (item->get_max_lasting()==0)
	{
        	item->set_max_lasting(1000);
        	item->set_lasting(1000);
	}
	if (item->get_lasting()<100)
	{
		return 0;
	}
	item->add_lasting(-100);		
	me->set_save("huntian", time());
	me->set("huntian", 1);
	send_user( me, "%c%c%c%w", 0x30, get_item_type_2(), 0, 1800 );    // 更新使用间隔
	x = p / 1000; y = p % 1000;
	me->set_2("jiguan.z", get_z(me));
	me->set_2("jiguan.x", get_x(me));
	me->set_2("jiguan.y", get_y(me));
	set_invisible(me, 1);
	me->add_to_scene(z, x, y, get_d(me) );
        set_effect(me, EFFECT_PROGRESS2, 600);
        me->set_progress_file(__FILE__);
	send_user(me, "%c%c%w%s", 0x5a, 0, 600, "Hỗn thiên nghi sử dụng trung……");
        return 0;
}

// 函数：法术处理
int into_effect( object me , string arg)
{
	int p, x, y, z;
	z = me->get_2("jiguan.z");
	x = me->get_2("jiguan.x");
	y = me->get_2("jiguan.y");
	me->delete_2("jiguan");
	p = get_valid_xy(z, x, y, IS_CHAR_BLOCK);	
	x = p / 1000; y = p % 1000;
	if (p==0) MAP_D->add_to_void(me);	
	else me->add_to_scene(z, x, y, get_d(me) );
	send_user(me, "%c%c%c", 0x5a, 1, 1);
	set_invisible(me, 0);
	me->set("huntian", 0);
	return 1;
}

void effect_break(object me, string arg)
{
	int p, x, y, z;
	z = me->get_2("jiguan.z");
	x = me->get_2("jiguan.x");
	y = me->get_2("jiguan.y");
	me->delete_2("jiguan");
	p = get_valid_xy(z, x, y, IS_CHAR_BLOCK);
	x = p / 1000; y = p % 1000;
	if (p==0) MAP_D->add_to_void(me);
	else me->add_to_scene(z, x, y, get_d(me) );
	send_user(me, "%c%c%c", 0x5a, 1, 0);
	set_effect(me, EFFECT_PROGRESS2, 0 );
	set_invisible(me, 0);
	me->set("huntian", 0);
}