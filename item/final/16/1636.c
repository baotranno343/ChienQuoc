#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

inherit "/inh/equip/equip";

#define PICID	11

// 函数：叠加上限
int get_max_combined() { return 1; }

// 函数：成品编号
//int get_fin_type() { return 0011; }

// 函数：构造处理
void create()
{
        set_name( "兔娃娃" );
        set_picid_1(3569);
        set_picid_2(3569);
        set_value(3200);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
	if ( "sys/main/main"->get_host_type() != 2 )
        	return "嫦娥赠送的中秋节礼物，10月15日后消失。";
        else
        	return "嫦娥赠送的中秋节礼物，10月25日后消失。";
        	
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me, this_object()); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object item )
{
	int type,iTime;
	object * objs, who, npc;
	int i, size, x, y, z, p;	
	objs = me->get("zombie");
	size = sizeof(objs);
	if ( "sys/main/main"->get_host_type() != 2 )
		iTime = mktime(2006,10,15,0,0,0);
	else
		iTime = mktime(2006,10,25,0,0,0);
		
	if (size>0)
	{
		for (i=0;i<size;i++)
		{
			who = objs[i];
			if (!objectp(who)) continue;
			send_user( get_scene_object_2(who, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, get_x(who), get_y(who), 9414, 1, OVER_BODY, PF_ONCE );
			send_user(me, "%c%c%d", 0x2c, 0, getoid(who));
			who->remove_from_scene();
			destruct(who);			
		}
		item->set_no_drop(0);
		item->set_no_give(0);
		item->set_no_sell(0);
		item->set_no_get(0);
		me->delete("zombie");
		if ( time() > iTime )
		{
			return 1;	
		}
		return 0;
	}
	if ( time() > iTime )
	{
		return 1;	
	}
	item->set_no_drop(1);
	item->set_no_give(1);
	item->set_no_sell(1);
	item->set_no_get(1);
	npc = new ("/npc/std/jiguan");
	npc->set_name(get_name());
	npc->set_char_picid(PICID);
	npc->upgrade_level(1);
        npc->set_owner(me);
        npc->set_action_mode(2);
	npc->set_head_color(0x51a5);
	z = get_z(me); x = get_x(me); y = get_y(me);
	p = get_valid_xy(z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK) ;
	x = p / 1000;  y = p % 1000;
	npc->add_to_scene( z, x, y, 3);
        me->add("zombie", ({ npc }) );
        return 0;
}
