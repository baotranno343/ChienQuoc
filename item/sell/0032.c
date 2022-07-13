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
        set_name("Sơ Cấp Đoạn Thạch");
        set_real_name("Đoạn Thạch");
        set_picid_1(4270);
        set_picid_2(4270);
        set_unit("块");
        set_value(2000);
        set_level(1);
}

string get_short(object me)
{
	return "Chỉ Có thể rèn trang bị 1 ngôi sao hoặc thấp hơn, có thể tăng cường thuộc tính trang bị.\n Hai Sơ Cấp Đoạn Thạch có thể tạo thành một Trung Cấp Đoạn Thạch.";
}

// 函数：获取描述
string get_desc()
{
        return "Chỉ Có thể rèn trang bị 1 ngôi sao hoặc thấp hơn, có thể tăng cường thuộc tính trang bị.\n Hai Sơ Cấp Đoạn Thạch có thể tạo thành một Trung Cấp Đoạn Thạch.";
}

string get_name()
{
	object me = this_object();
	if (!clonep(me)) return "Sơ Cấp Đoạn Thạch";
	if (me->get_level()>1)
		return sprintf("Sơ Cấp Đoạn Thạch cấp %d ", me->get_level());
	else
		return "Sơ Cấp Đoạn Thạch";
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
	if( equip->is_equip()==0 && equip->get_real_name()!="Đoạn Thạch" )  return 0;
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
	if (equip->get_real_name()=="Đoạn Thạch" && item->get_forge_index()!=equip->get_forge_index())
	{
		notify( "Cấp bậc không phù hợp, không thể hợp thành." );
		return 1;
	}
	forge = equip->get("forge");
	if (forge==0) level = 0;
	else level = strlen(forge);
	if (i>0 && level>1)
	{
		notify( "Sơ Cấp Đoạn Thạch chỉ có thể rèn trang bị 1 sao." );
		return 1;
	}
	rate = 100;
	if (type==1)
	{
		if (i==0 )
		{
			result = sprintf("Ngươi muốn hợp thành 2 Sơ Cấp Đoạn Thạch để có 1 Trung Cấp Đoạn Thạch không?\n"
			        ESC "%c\n" ESC "\nmix2 0# %x# %x#\n"
			        , 1, getoid(item), getoid(equip) );
			send_user(me, "%c%c%s", 0x59, 1, result);
		}
		else
		{
			result = sprintf("Trang bị nếu rèn thất bại sẽ giảm xuống 0 sao, Tỷ lệ thành công là"HIR " %d%%"NOR "，\nNgươi xác định phải rèn %s không?\n"
				ESC "Chấp nhận\nmix3 0# %x# %x#\n"
				ESC "Hủy bỏ",
			        rate, equip->get_name(), getoid(equip), getoid(item) );

			send_user(me, "%c%c%w%s", ':', 3, 0, result);
		}		       			
		return 1;
	}		
	return 1;
}