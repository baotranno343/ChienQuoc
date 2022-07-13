#include <ansi.h>
#include <item.h>
#include <task.h>

inherit ITEM;
//inherit USABLE;
inherit LEGEND_ITEM;
int iOwner;

int is_xunbao() { return 1;}
//int who_can_get() { return iOwner; }
//int set_owner(int i) { return iOwner=i; }
// 函数：构造处理
void create()
{
        set_name( "Tàng Bảo Đồ" );
        set_picid_1(8000);
        set_picid_2(8000);
        set_unit( "张" );
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
//        return "Vật phẩm nhiệm vụ.野外的（88、62）暗藏着什么秘密。（到达地点后右击使用）。"; 
        return "Vật phẩm nhiệm vụ.(88, 62) Thanh Khê đang giấu bí mật gì."; 
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object item )
{
//	int x,y,z,p;
//	object obj;
	
//	if ( me->get_legend(TASK_NEWBIE_01, 8) || ( !me->get_legend(TASK_NEWBIE_01, 8) && !me->get_legend(TASK_NEWBIE_01, 5) && !me->get_legend(TASK_NEWBIE_01, 6) && !me->get_legend(TASK_NEWBIE_01, 7)))
//		return 1;
//	if ( !me->get_legend(TASK_NEWBIE_01, 7) || me->get_legend(TASK_NEWBIE_01, 8) )
//	{
//		send_user(me, "%c%s", '!', "这个藏宝图好像有什么秘密,到新手村问问");
//		return 0;
//	}
/*	z = get_z(me);x=get_x(me);y=get_y(me);

        if(    (z != 3&&z!=6&&z!=9)
        ||      abs( 88 - x ) > 2
        ||      abs( 62 - y ) > 2 )
        {
                send_user(me, "%c%s", '!', "您挖宝的位置不对。");
                return 0;
        }	
	obj = new("/item/98/9880");
        if (!obj)
        	return 0;
        item->remove_from_user();
        destruct(item);
        p =obj->move(me, -1);
        obj->add_to_user(p);
        send_user(me,"%c%s",';',"你得到"HIY"家族玉佩");
	me->set_legend(TASK_48, 9);
        USER_TASK_D->send_task_intro(me,2,TID_NEWBIE_01,104);*/
	if (me->get_legend(TASK_48, 6) && me->get_legend(TASK_48, 7) && me->get_legend(TASK_48, 8) && me->get_legend(TASK_48, 9) && me->get_legend(TASK_48, 10))	return 1;
	return 0;
}