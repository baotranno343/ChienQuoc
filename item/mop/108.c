//活动编号1016
//奖品编号101601
#include <time.h>
#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;

inherit "/inh/equip/equip";

#define RIDE_ID	4

// 函数：构造处理
void create()
{
        set_name( "巨犀" );
        set_picid_1(13);
        set_picid_2(13);
        set_value(500);
        set_hide(0);
        set_bind(4);
        set_no_give(1);
}

// 函数：获取描述
string get_desc() 
{ 
	object item = this_object();
	if (item->get_lock_time()==0) item->set_lock_time(time()+30*24*3600);
        return "犀牛为大话战国骑宠系列的佼佼者，\n外型威猛神武，跑动起来气势磅礴，\n蔚蓝色的牛角闪闪发亮\n与古铜色的皮肤形成鲜明的对比，不愧为\n新一代骑宠中的霸主！使用期限为30天。";
}


// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me, this_object()); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object item )
{
	int type;
	object who, npc;
	int i, size, x, y, z, p;
	if (item->get_lock_time()==0) item->set_lock_time(time()+30*24*3600);
	if (item->get_lock_time()<time())
	{
		send_user(me, "%c%s", '!', "道具已过期");
		return 0;		
	}	
	if (me->get_fam_name()==""||!me->get_fam_name())
	{
		send_user(me, "%c%s", '!', "需要加入门派后才能使用这个道具。");
		return 0;
	}	
	if (me->get_ride())
	{
		me->set_ride(0);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));		
		return 0;
	}
	me->set_ride(RIDE_ID);
	me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
        return 0;
}
