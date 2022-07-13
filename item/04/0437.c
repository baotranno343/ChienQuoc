#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;

int iFinish = 0;	//活动是否结束
// 函数：构造处理
void create()
{
        set_name( "天使小宠物" );
        set_picid_1(8115);
        set_picid_2(8115);
        set_value(50);
	set_no_give(1);
	set_no_sell(1);
	set_no_get(1);
}

int get_item_color() { return 1; }
// 函数：获取描述
string get_desc() 
{ 
        return "鼠标右键点击它，可召唤出一只可爱的小天使宠物。";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me, this_object()); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object item )
{
	int type;
	object * objs, who, npc;
	int i, size, x, y, z, p;	
	objs = me->get("zombie");
	size = sizeof(objs);
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
		me->delete("zombie");
		me->delete_2("jiguan");
		return 0;
	}
	if ( iFinish )		//到期不能使用
	{
		return 1;	
	}
	npc = new ("/npc/std/jiguan");
	npc->set_name(get_name());
	npc->set_char_picid(8115);
	npc->upgrade_level(1);
        npc->set_owner(me);
        npc->set_action_mode(2);
	z = get_z(me); x = get_x(me); y = get_y(me);
	p = get_valid_xy(z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK) ;
	x = p / 1000;  y = p % 1000;
	npc->add_to_scene( z, x, y, 3);
        me->add("zombie", ({ npc }) );
        me->delete_2("jiguan");
        me->set_2("jiguan.pp", 2);
        return 0;
}
