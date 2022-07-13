#include <item.h>
#include <ansi.h>
#include <equip.h>

inherit ITEM;
inherit "/inh/item/diamond";

int get_item_value() {return 49 ;}
int get_item_value_2() {return 49 ;}
int get_item_number() {return 10001027 ;}

// 函数：宝石识别
int is_diamond_2() { return 1; }

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

int get_item_color() {return 1 ;}

// 函数：宝石识别
int get_item_type() { return ITEM_TYPE_DIAMOND_3; }

// 函数：宝石属性
string get_diamond_type() { return "forge"; }

// 宝石锻造的辩别标志
string get_forge_index() {return "1";}

int is_specal_move() {return 1;}

// 函数：构造处理
void create()
{
        set_name("初级锻造石");
        set_real_name("锻造石");
        set_picid_1(4270);
        set_picid_2(4270);
        set_unit("块");
        set_value(50);
        set_level(1);
        // -- 与原装备相比增加绑定属性
        set_no_give(1);
        set_no_sell(1);
        //        
}

string get_short(object me)
{
	return "只能锻造1星或以下的装备，可加强该装备的属性。\n两个初级锻造石可合成一个中级锻造石。";
}

// 函数：获取描述
string get_desc()
{
        return "只能锻造1星或以下的装备，可加强该装备的属性。\n两个初级锻造石可合成一个中级锻造石。";
}

string get_name()
{
	object me = this_object();
	if (!clonep(me)) return "初级锻造石";
	if (me->get_level()>1)
		return sprintf("%d级初级锻造石", me->get_level());
	else
		return "初级锻造石";
}

int move_item(object me, object item, object equip)
{
	return __FILE__->move_item_callout(me, item, equip, 1 );
}

int move_item2(object me, object item, object equip)
{
	return __FILE__->move_item_callout(me, item, equip, 2 );
}

int move_item_callout(object me, object item, object equip, int type)
{
	string result, forge;
	object item2;
	int i, p, level, rate;	
	if( equip->is_equip()==0 && equip->get_real_name()!="锻造石" )  return 0;
	if (item->get_level()!=1)
	{
		notify( "请找公输班将宝石分解为初级宝石" );
		return 1;
	}
	if( equip->is_equip())
	{
		i=equip->get_equip_type();
		if ( i!=WEAPON_TYPE&&i!=ARMOR_TYPE&&i!=HEAD_TYPE&&i!=BOOTS_TYPE&&i!=WAIST_TYPE&&i!=NECK_TYPE)
			return 0;
	}
	if (equip->get_real_name()=="锻造石" && item->get_forge_index()!=equip->get_forge_index())
	{
		notify( "级别不同的锻造石无法进行合成。" );
		return 1;
	}
	forge = equip->get("forge");
	if (forge==0) level = 0;
	else level = strlen(forge);
	if (i>0 && level>1)
	{
		notify( "初级锻造石只能锻造在1星以下的装备上。" );
		return 1;
	}
	rate = 100;
	if (type==1)
	{
		if (i==0 )
		{
			result = sprintf("你确定要将两个初级锻造石合成为一个中级锻造石吗？\n"
			        ESC "%c\n" ESC "\nmix2 0# %x# %x#\n"
			        , 1, getoid(item), getoid(equip) );
			send_user(me, "%c%c%s", 0x59, 1, result);
		}
		else
		{
			result = sprintf("装备锻造失败后加成的星便会清0，\n当前装备的锻造成功率为"HIR" %d％"NOR"，\n你确定要锻造%s吗？\n"
				ESC "确定\nmix3 0# %x# %x#\n"
				ESC "取消",
			        rate, equip->get_name(), getoid(equip), getoid(item) );

			send_user(me, "%c%c%w%s", ':', 3, 0, result);
		}		       			
		return 1;
	}		
	return 1;
}