#include <item.h>
#include <ansi.h>
#include <equip.h>
inherit SKILL;

// 函数：命令处理
int main( object me, object npc, object item )
{
	int ret;
	if (!npc) return 1;
	if (!item) return 1;
	if (item->get_item_type()!=ITEM_TYPE_DIAMOND_3) if (npc->get_name()!="Chủ Tiệm Sửa Chữa") return 1;
	else if (item->get_item_type()==ITEM_TYPE_DIAMOND_3) if (npc->get_name()!="Can Tương") return 1;
	if( !inside_screen_2(me, npc) ) return 1;
	if (item->if_in_user(me)==0) return 1;
	if ( item->get_item_type()!=ITEM_TYPE_DIAMOND_3 )
	"/sys/item/product"->make_stuff(me, npc, item);
	else
	"/sys/item/product"->phangiai_dt(me, npc, item);
	return 1;		
}