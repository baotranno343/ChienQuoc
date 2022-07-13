#include <ansi.h>
#include <equip.h>
#include <effect.h>
inherit ITEM;
inherit USABLE;

int get_item_color() { return 2; }
int get_item_value() { return 120; }
int get_item_value_2() { return 120; }

// 函数：构造处理
void create()
{
	set_name("Túi Hoàng Kim cấp 60");
	set_picid_1(3102);
	set_picid_2(3102);
	set_value(100);
	set_save("tbpt", 100);
	set_no_give(1);
	set_no_sell(1);
}

// 函数：获取描述
string get_desc(object me)
{
	return "Sau khi sử dụng có thể nhận được một bộ trang bị Hoàng Kim cấp 60 tương ứng giới tính, môn phái.";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object gift)
{
	int p, level, i;
	object item;
	string *nTmp, cFile, forge = "";
	level = 60;

	if (who->get_fam_name() == "" || !who->get_fam_name())
	{
		send_user(who, "%c%s", '!', "Hãy gia nhập môn phái");
		return 0;
	}

	if (USER_INVENTORY_D->get_free_count(who) < 6)
	{
		send_user(who, "%c%s", '!', "Hành trang không đủ chỗ.");
		return 0;
	}

	gift->remove_from_user();
	destruct(gift);
	nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(), who->get_gender(), level, HEAD_TYPE);
	cFile = nTmp[random(sizeof(nTmp))];
	if (load_object(cFile))
	{
		item = new (cFile);
		forge = "";
		ITEM_EQUIP_D->init_equip_prop_3(item);
		for (i = 0; i < 6; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_no_sell(1);
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
	}
	nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(), who->get_gender(), level, NECK_TYPE);
	cFile = nTmp[random(sizeof(nTmp))];
	if (load_object(cFile))
	{
		item = new (cFile);
		forge = "";
		ITEM_EQUIP_D->init_equip_prop_3(item);
		for (i = 0; i < 6; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_no_sell(1);
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
	}
	nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(), who->get_gender(), level, WEAPON_TYPE);
	cFile = nTmp[random(sizeof(nTmp))];
	if (load_object(cFile))
	{
		item = new (cFile);
		forge = "";
		ITEM_EQUIP_D->init_equip_prop_3(item);
		for (i = 0; i < 6; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_no_sell(1);
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
	}
	nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(), who->get_gender(), level, ARMOR_TYPE);
	cFile = nTmp[random(sizeof(nTmp))];
	if (load_object(cFile))
	{
		item = new (cFile);
		forge = "";
		ITEM_EQUIP_D->init_equip_prop_3(item);
		for (i = 0; i < 6; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_no_sell(1);
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
	}
	nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(), who->get_gender(), level, WAIST_TYPE);
	cFile = nTmp[random(sizeof(nTmp))];
	if (load_object(cFile))
	{
		item = new (cFile);
		forge = "";
		ITEM_EQUIP_D->init_equip_prop_3(item);
		for (i = 0; i < 6; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_no_sell(1);
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
	}
	nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(), who->get_gender(), level, BOOTS_TYPE);
	cFile = nTmp[random(sizeof(nTmp))];
	if (load_object(cFile))
	{
		item = new (cFile);
		forge = "";
		ITEM_EQUIP_D->init_equip_prop_3(item);
		for (i = 0; i < 6; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_no_sell(1);
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
	}
	return 0;
}