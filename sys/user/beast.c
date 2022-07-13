//宠物(召唤兽)相关
#include <item.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <ansi.h>
#define PET_NPC "npc/std/pet"

// 函数：生成二进制码
void SAVE_BINARY() {}

void create()
{
}

//是否宠物
int is_pet(object owner, object pet)
{
	if (!owner || !pet || !pet->is_pet() || pet->get_owner() != owner)
		return 0;
	return 1;
}
//是否有捕捉技能
int can_perform(object who)
{
	return 1;
}
//能携带的召唤兽数量
int max_carry(object who)
{
	if (sizeof(who->get_fam_name()))
		return 4;
	return 3;
}
//检查是否能召唤
int check_show_beast(object me, object pet)
{
	int time;
	mapping mpInfo;

	if (!is_pet(me, pet))
		return 0;
	if (strstr(pet->get_name(), "%") != -1)
	{
		send_user(me, "%c%s", '!', "Tên của bảo thú có từ ngữ mẫn cảm!");
		return 0;
	}
	if (!mapp(mpInfo = "quest/pet"->get_beast_info(pet->get_firstname())))
	{
		return 0;
	}
	if ((!pet->get_save("ignore_level") && me->get_level() < mpInfo["level"]) || me->get_level() < pet->get_level())
	{
		send_user(me, "%c%s", '!', "Năng lực của ngươi không đủ để khống chế sủng vật");
		return 0;
	}
	if (pet->get_life() < 100)
	{
		send_user(me, "%c%s", '!', sprintf("Bảo thú của ngươi %s Khí huyết quá thấp,không thể tham gia chiến đấu!", pet->get_name()));
		return 0;
	}
	if (pet->get_faith() < 10)
	{
		send_user(me, "%c%s", '!', sprintf("Bảo thú của ngươi %s trung thành quá thấp,hãy nâng độ trung thành rồi hãy gọi ra!", pet->get_name()));
		return 0;
	}

	if (pet->is_die())
	{
		send_user(me, "%c%s", '!', sprintf("Bảo thú của ngươi %s đã chết,không thể gọi về!", pet->get_name()));
		return 0;
	}
	if ((time = pet->get_dead_time()) && (time = gone_time(time)) < 600)
	{
		send_user(me, "%c%s", '!', sprintf("Báo thú của ngươi %s lần trước chiến đấu bị trọng thương, hãy chờ %d phút rồi gọi ra.", pet->get_name(), 10 - time / 60));
		return 0;
	}
	return 1;
}

void show_beast_perform(object me, object pet)
{
	if (!is_pet(me, pet))
		return;
	if (check_show_beast(me, pet) != 1)
		return;
	send_user(me, "%c%c%w%s", 0x5a, 0, 3, "Đang kêu gọi Bảo...");
	me->set_2("conjure.type", 9999);
	me->set_2("conjure.pet", pet);
	set_effect(me, EFFECT_CONJURE, 3);
}
//宠物
void hide_beast(object me, object pet)
{
	int i, size, *nSkill, p;
	object nSki;
	if (!is_pet(me, pet) || !pet->get("show"))
		return;
	//宠物技能的影响
	nSkill = ({74216, 74217, 74218, 74219, 74220});
	for (i = 0, size = sizeof(nSkill); i < size; i++)
	{
		if (!pet->get_skill(p = nSkill[i]))
			continue;
		nSki = load_object(SKILL->get_perform_file(p));
		if (!nSki)
			continue;
		nSki->remove_show_effect(pet, me);
	}
	send_user(get_scene_object_2(pet, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, get_x(pet), get_y(pet), 9414, 1, OVER_BODY, PF_ONCE);
	pet->remove_from_scene();
	pet->delete ("show");
	pet->delete ("show_time");
	me->delete ("showbeast");
	send_user(me, "%c%c%d%c", 0xA1, 3, getoid(pet), 0);
}
//宠物参战, 发送给客户端的信息
void show_beast_client(object me, object pet)
{
	int i, size;
	string *nKey;
	object nSki;
	mapping mpSkill;

	send_user(me, "%c%c%d%s", 0x2c, 1, getoid(pet), pet->get_name());
	send_user(me, "%c%c%d%w%w%w", 0x2c, 2, getoid(pet), 1, 2, 3);
	send_user(me, "%c%c%d%c", 0x2c, 3, getoid(pet), 50);
	send_user(me, "%c%c%d%c", 0x2c, 4, getoid(pet), 50);
	send_user(me, "%c%c%d%c", 0x2c, 5, getoid(pet), 2);
	send_user(me, "%c%c%d%c", 0x2c, 6, getoid(pet), 2);
	send_user(me, "%c%c%d%w%w", 0x2c, 7, getoid(pet), get_x(pet), get_y(pet));
	send_user(me, "%c%c%d%d", 0x2c, 8, getoid(pet), pet->get_char_picid());

	send_user(me, "%c%c%d%c", 0xA1, 3, getoid(pet), 1);
	//发送技能剩余冷冻时间
	mpSkill = pet->get_skill_dbase();
	if (mpSkill)
	{
		nKey = keys(mpSkill);
		for (i = 0, size = sizeof(nKey); i < size; i++)
		{
			nSki = load_object(SKILL->get_perform_file(to_int(nKey[i])));
			if (!nSki)
				continue;
			nSki->perform_lasting(pet);
		}
	}
	CHAR_CHAR_D->send_loop_perform(pet, get_scene_object_2(pet, USER_TYPE));   // 显示持续效果
	CHAR_CHAR_D->send_loop_perform_2(pet, get_scene_object_2(pet, USER_TYPE)); // 显示持续图标
}
void show_beast(object me, object pet)
{
	int time, p, x, y, z, x0, y0, *nSkill, i, size;
	object pet1, nSki;
	string *nKey;
	mapping mpSkill;

	if (check_show_beast(me, pet) != 1)
		return;
	if (pet->get_faith() <= 20 && random(100) > pet->get_faith())
	{
		send_user(me, "%c%s", '!', sprintf("Bảo thú của ngươi %s trung thành quá thấp,hãy nâng độ trung thành rồi hãy gọi ra!", pet->get_name()));
		return;
	}
	if (pet->get("show"))
		return;
	pet1 = me->get("showbeast");
	if (pet1)
		hide_beast(me, pet1);
	z = get_z(me);
	x0 = get_x(me);
	y0 = get_y(me);
	p = get_valid_xy(z, x0 + random(3) - 1, y0 + random(3) - 1, IS_CHAR_BLOCK);
	x = p / 1000;
	y = p % 1000;
	pet->set_action_mode(2);
	pet->add_to_scene(z, x, y, get_front_xy(x, y, x0, y0));
	send_user(get_scene_object_2(pet, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(pet),
			  41341, 1, OVER_BODY, 41342, 1, OVER_BODY, 41343, 1, UNDER_FOOT, PF_ONCE);
	pet->set("show", 1);
	pet->set("show_time", time());

	pet->set_city_name(me->get_city_name()); // 用于战场
	pet->set_manager(me->get_manager());
	pet->set_org_name(me->get_org_name());

	//        send_user(me, "%c%c%d%s", 0x2c, 1, getoid(pet), pet->get_name() );
	//        send_user(me, "%c%c%d%w%w%w", 0x2c, 2, getoid(pet), 1, 2, 3 );
	//        send_user(me, "%c%c%d%c", 0x2c, 3, getoid(pet), 50 );
	//        send_user(me, "%c%c%d%c", 0x2c, 4, getoid(pet), 50 );
	//        send_user(me, "%c%c%d%c", 0x2c, 5, getoid(pet), 2 );
	//        send_user(me, "%c%c%d%c", 0x2c, 6, getoid(pet), 2 );
	//        send_user(me, "%c%c%d%w%w", 0x2c, 7, getoid(pet), get_x(pet), get_y(pet) );
	//        send_user(me, "%c%c%d%d", 0x2c, 8, getoid(pet), pet->get_char_picid() );
	//
	//	send_user(me,"%c%c%d%c", 0xA1,3,getoid(pet),1);

	me->set("showbeast", pet);
	//宠物技能的影响
	nSkill = ({74216, 74217, 74218, 74219, 74220});
	for (i = 0, size = sizeof(nSkill); i < size; i++)
	{
		if (!pet->get_skill(p = nSkill[i]))
			continue;
		nSki = load_object(SKILL->get_perform_file(p));
		if (!nSki)
			continue;
		nSki->show_effect(pet, me);
	}
	//	//发送技能剩余冷冻时间
	//	mpSkill = pet->get_skill_dbase();
	//	if ( mpSkill )
	//	{
	//		nKey = keys(mpSkill);
	//		for(i=0,size=sizeof(nKey);i<size;i++)
	//		{
	//			nSki = load_object(SKILL->get_perform_file(to_int(nKey[i])));
	//			if ( !nSki )
	//				continue;
	//			nSki->perform_lasting(pet);
	//		}
	//	}
	//        CHAR_CHAR_D->send_loop_perform(pet, get_scene_object_2(pet, USER_TYPE));    // 显示持续效果
	//        CHAR_CHAR_D->send_loop_perform_2(pet, get_scene_object_2(pet, USER_TYPE));    // 显示持续图标
	show_beast_client(me, pet);
}
//宠物移离主人
int remove_from_user(object owner, object pet)
{
	if (!is_pet(owner, pet))
		return 0;
	owner->remove_beast(pet);
	if (pet->get("show"))
		hide_beast(owner, pet);
	//刷新客户端显示
	send_user(owner, "%c%c%d", 0xA1, 10, getoid(pet));
	return 1;
}
//捕获宠物
int capture_beast(object me, object npc)
{
	int rate, baobao;
	string Id, name;
	object pet;

	if (!npc->is_npc())
		return 0;
	pet = new (PET_NPC);
	if (!pet)
		return 0;
	if (npc->get("is_baobao"))
		baobao = 1;
	else
	{
		rate = random(100);
		baobao = rate ? 0 : 1;
	}
	if (NPC_PET_D->generate_pet(pet, npc->get_name(), npc->get_level(), baobao) != 1)
		return 0;

	pet->set_owner(me);
	pet->set_char_picid(npc->get_char_picid());
	pet->set_portrait(npc->get_char_picid());
	pet->set_head_color(npc->get_head_color());
	if (!me->add_beast(pet))
	{
		destruct(pet);
		return 0;
	}
	pet->send_info();
	//log_file("pet.txt",sprintf("%s %s(%d) bắt được %s %s Bảo Bảo:%d\n",short_time(),me->get_name(),me->get_number(), pet->get_name(),pet->get_pet_id(),baobao));
	if (baobao)
		"/sys/sys/count"->add_pet("Bắt được " + pet->get_name() + " Bảo Bảo", 1);
	else
		"/sys/sys/count"->add_pet("Bắt được " + pet->get_name(), 1);
	return 1;
}
//删除宠物
void destruct_pet(object me, object pet)
{
	if (!is_pet(me, pet))
		return;
	remove_from_user(me, pet);
	destruct(pet);
}
//释放宠物
void free_beast(object me, object pet)
{
	if (!is_pet(me, pet))
		return;
	if (pet->get("store"))
	{
		send_user(me, "%c%s", '!', pet->get_name() + " Ngươi đã rao bán,không thể phóng sinh!");
		return;
	}
	remove_from_user(me, pet);
	//log_file("pet.txt", sprintf("%s %s(%d) phóng sinh %s(%s) %s\n", short_time(), me->get_name(), me->get_number(), pet->get_name(), pet->get_firstname(), pet->get_pet_id()));
	destruct(pet);
}

//宠物改名
string change_name(object owner, object pet, string cName)
{
	if (!is_pet(owner, pet))
		return;
	replace_string(cName, " ", "");
	if (sizeof(cName) > 15)
	{
		send_user(owner, "%c%s", '!', "Tên không thể vượt quá 15 ký tự!");
		return;
	}
	if (strstr(cName, "Bảo Bảo") != -1 || strstr(cName, "|") != -1 || strstr(cName, "%") != -1 || strstr(cName, ".") != -1)
	{
		send_user(owner, "%c%s", '!', "Từ ngữ phi pháp!");
		send_user(owner, "%c%c%d%s", 0xA1, 9, getoid(pet), pet->get_name());
		return;
	}

	cName = pet->set_name(cName);
	send_user(owner, "%c%c%d%s", 0xA1, 9, getoid(pet), cName);
	return cName;
}
//拥有类型宠物
object have_beast(object who, string cName)
{
	int i, size;
	object pet, *AllBeast;

	AllBeast = who->get_all_beast();
	for (i = 0, size = sizeof(AllBeast); i < size; i++)
	{
		if (!objectp(pet = AllBeast[i]))
			continue;
		if (pet->get_name() == cName && pet->get_firstname() == cName)
			break;
	}
	if (i < size)
		return pet;
	else
		return 0;
}
//给予玩家宠物
object give_pet(object me, string cName, int baobao, int level, int picid, int flag)
{
	object pet;

	pet = new (PET_NPC);
	if (!pet)
		return 0;
	if (NPC_PET_D->generate_pet(pet, cName, 0, baobao) != 1)
		return 0;
	pet->set_owner(me);
	pet->set_char_picid(picid);
	pet->set_portrait(picid);

	pet->set_owner(me);
	if (!me->add_beast(pet))
	{
		destruct(pet);
		return 0;
	}
	pet->set_level(level);
	pet->set_giftpoint(level * 4);
	pet->add_con(level);
	pet->add_spi(level);
	pet->add_str(level);
	pet->add_cps(level);
	pet->add_dex(level);
	NPC_PET_D->set_pet_info(pet);
	if (flag)
		pet->send_info();
	return pet;
}
//使用神兽道具
int use_shenshou_item(object who, object item)
{
	int picid;
	string name;
	mapping mpInfo;
	object pet;

	if (who->get_beast_amount() >= who->get_beast_max_amount())
	{
		send_user(who, "%c%s", '!', "Bảo thú của ngươi đã đầy,không thể có thêm được nữa");
		return 0;
	}
	name = item->get_name();
	picid = item->get("picid");
	pet = new (PET_NPC);
	if (!pet)
		return 0;
	if (NPC_PET_D->generate_shenshou(pet, name) != 1)
	{
		destruct(pet);
		return 0;
	}
	pet->set_owner(who);
	pet->set_char_picid(picid);
	pet->set_portrait(picid);
	pet->set_save("no_give", 1);
	pet->set_save("no_fuse", 1);
	pet->save();
	if (!who->add_beast(pet))
	{
		destruct(pet);
		return 0;
	}
	pet->send_info();
	send_user(who, "%c%s", '!', "Ngươi đạt được Thần thú " HIR + pet->get_name());
	return 1;
}