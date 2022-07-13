
#include <equip.h>
#include <effect.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 2108; }

// 有自己的do_look函数
int is_self_look() { return 1; }

// 函数：构造处理
void create()
{
	set_name("Bảo Rương");
	set("boxname", "Sư Môn Bảo Rương");
	setup();
}

// 函数：对话处理
void do_look(object who)
{
	if (get_effect(who, EFFECT_OPEN_BOX))
		return;
	send_user(who, "%c%c%w%s", 0x5a, 0, 10, "Đang mở……");
	set_effect_2(who, EFFECT_OPEN_BOX, 1, 10);
	who->set("openbox", this_object());
}

void into_effect(object who, object me)
{
	int rate, p, oldz, x, y, z, level;
	string file, *nTmp;
	object item;

	if (me->get("user") != who->get_number())
		return;

	level = me->get("level");
	if (level > 120)
		level = 120;

	rate = random(100);
	//	if ( rate < 93 )
	//	{
	//               if( random(2) )
	//                        nTmp = WEAPON_FILE->get_family_equip( who->get_fam_name(),who->get_gender(),level,WEAPON_TYPE );
	//                else    nTmp = WEAPON_FILE->get_family_equip( who->get_fam_name(),who->get_gender(),level,ARMOR_TYPE );
	//                file = nTmp[random(sizeof(nTmp))];
	//                if( load_object(file) )
	//                {
	//                        item = new( file );
	//			ITEM_EQUIP_D->init_equip_prop_1(item);
	//                }
	//	}
	//	else if ( rate < 94 )
	//	{
	//               if( random(2) )
	//                        nTmp = WEAPON_FILE->get_family_equip( who->get_fam_name(),who->get_gender(),level,WEAPON_TYPE );
	//                else    nTmp = WEAPON_FILE->get_family_equip( who->get_fam_name(),who->get_gender(),level,ARMOR_TYPE );
	//                file = nTmp[random(sizeof(nTmp))];
	//                if( load_object(file) )
	//                {
	//                        item = new( file );
	//			ITEM_EQUIP_D->init_equip_prop_3(item);
	//                }
	//	}
	if (rate < 94)
	{
		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(), who->get_gender(), level, ARMOR_TYPE);
		file = nTmp[random(sizeof(nTmp))];
		if (load_object(file))
		{
			item = new (file);
			ITEM_EQUIP_D->init_equip_prop_3(item);
		}
	}
	else if (rate < 99)
	{
		if (load_object(file = STONE_FILE->get_diamond_file()))
		{
			item = new (file);
			item->set_level(3);
		}
	}
	else
	{
		if (load_object(file = STONE_FILE->get_diamond_file()))
		{
			item = new (file);
			item->set_level(4);
		}
	}
	if (!item)
		return;
	p = item->move(who, -1);
	if (!p)
	{
		destruct(item);
		send_user(who, "%c%s", '!', "Hành trang không đủ chỗ !");
		return;
	}
	me->remove_from_scene();
	destruct(me);
	send_user(who, "%c%s", '!', sprintf("Ngươi mở Bảo Rương nhận được %s", item->get_name()));
	tell_user(who, sprintf("Ngươi mở Bảo Rương nhận được %s", item->get_name()));
	item->add_to_user(p);

	who->delete_save_2("masterfight");
	if (who->get_fam_order() <= 0)
		who->set_fam_order(4);
	else
		who->set_fam_order(who->get_fam_order() - 1);
	z = who->get_2("masterfight.z");
	x = who->get_2("masterfight.x");
	y = who->get_2("masterfight.y");
	who->delete_2("masterfight");
	who->delete_2("masterfight");
	if (!(p = get_valid_xy(z, x, y, IS_CHAR_BLOCK)))
		return;
	x = p / 1000;
	y = p % 1000;
	who->add_to_scene(z, x, y, 3);
}
