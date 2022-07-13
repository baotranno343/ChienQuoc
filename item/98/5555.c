#include <item.h>
#include <ansi.h>
#include <equip.h>

inherit ITEM;
//inherit COMBINED;
inherit "/inh/item/diamond";

// 函数：宝石识别
int is_diamond_2() { return 1; }

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

int get_item_color() {return 2 ;}

// 函数：宝石识别
int get_item_type() { return ITEM_TYPE_DIAMOND_3; }

// 函数：宝石属性
string get_diamond_type() { return "forge"; }

// 宝石锻造的辩别标志
string get_forge_index() {return "4";}

int is_specal_move() {return 1;}

// 函数：构造处理
void create()
{
        set_name("Đoạn Thạch Siêu Đặc Biệt");
        set_real_name("Đoạn Thạch");
        set_picid_1(4273);
        set_picid_2(4273);
        set_unit("块");
        set_value(50);
		//set_amount(1);
        set_level(1);
}

string get_desc() 
{
	return HIY"Chỉ có thể luyện trang bị 4 sao trở lên \n"HIY"Khi luyện thất bại cũng không bị giảm sao \n"HIY"Đoạn Thạch Siêu Đặc Biệt có xác xuất \n"HIY"tinh luyện thành công là 100%.";
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
	int i, p, level, rate, soluong, soluong1;	
	if( equip->is_equip()==0 && equip->get_real_name()!="Đoạn Thạch" )  return 0;
	if( equip->is_equip())
	{
		i=equip->get_equip_type();
		if ( i!=WEAPON_TYPE&&i!=ARMOR_TYPE&&i!=HEAD_TYPE&&i!=BOOTS_TYPE&&i!=WAIST_TYPE&&i!=NECK_TYPE)
			return 0;
	}
	if (equip->get_real_name()=="Đoạn Thạch" )
	{
		if (item->get_forge_index()!=equip->get_forge_index())
			notify( "Cấp bậc không phù hợp, không thể hợp thành." );
		else
			notify( "Đoạn Thạch Siêu Đặc Biệt không cần hợp thành." );
		return 1;
	}
	forge = equip->get("forge");
	if (forge==0) level = 0;
	else level = strlen(forge);
	if (level<4)
	{
		notify( "Đoạn Thạch Siêu Đặc Biệt chỉ rèn được trang bị 4 sao trở lên." );
		return 1;
	}	
	rate = 10000;		
	for (i=4;i<=level;i++)
	{
		rate = rate * 3 / 5; 
	}
	rate = 100;
//	rate /= 100;
	if ( me->get_vip() && !me->get_save_2("vip_package.trial") )
		rate += 5;
	if (rate>100) rate = 100;	
	soluong = equip->get_amount();
	soluong1 = item->get_amount();
	if (type==1)
	{
		result = sprintf("Trang bị nếu rèn thất bại cũng không bị giảm sao, Tỷ lệ thành công là"HIR " %d%%"NOR "，\nNgươi xác định phải rèn %s không?\n"
			ESC "Chấp nhận\nmix6 0# %x# %x#\n"
			ESC "Hủy bỏ",
			rate, equip->get_name(), getoid(equip), getoid(item) );
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		return 1;
	}	
	return 1;
}